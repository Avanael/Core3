/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/

#include "events/CheckBazaarStatus.h"

#include "BazaarManagerImplementation.h"

#include "../../Zone.h"
#include "../../ZoneServer.h"

#include "BazaarTerminalDetails.h"

#include "../../packets.h"
#include "../../objects.h"
#include "../../objects/auction/AuctionController.h"
#include "../../packets/scene/AttributeListMessage.h"

#include "../../objects/tangible/ItemAttributes.h"

#include "../item/ItemManager.h"

#include "../player/PlayerManager.h"
#include "../../../chat/ChatManager.h"

BazaarManagerImplementation::BazaarManagerImplementation(ZoneServer* zoneserver, ZoneProcessServerImplementation* server) : AuctionController(),
	BazaarManagerServant(), Logger("BazaarManager") {

	processServer = server;
	zoneServer = zoneserver;
	
	setLogging(false); 
	setGlobalLogging(true);
	
	bazaarTerminals = new BazaarTerminals();
	
	info("Setting up bazaars");
	
	// Set up the bazaar planet managers
	for (int i = 0; i < 10; i++)  {
		BazaarPlanetManagerImplementation* bpmImpl = new BazaarPlanetManagerImplementation(i);
		bazaarPlanets[i] = (BazaarPlanetManager*) bpmImpl->deploy("BazaarPlanetManager", i);	
	}
	
	BazaarMap* bazaarLocations = bazaarTerminals->getBazaarMap();
	bazaarLocations->resetIterator();
	while (bazaarLocations->hasNext()) {
		BazaarTerminalDetails* bazaar = bazaarLocations->getNextValue();
		bazaarPlanets[bazaar->getPlanet()]->addBazaar(bazaar);
	}
	
	// Populate the bazaars
	info("Starting to populate the bazaars");

	for (int i = 0; i < 10; i++)  {		
		stringstream query;
		query << "SELECT * from `bazaar_items` where `planet` = " << i << ";";
		
		ResultSet* items = ServerDatabase::instance()->executeQuery(query);

		while (items->next()) {
			
			uint64 objectId = items->getUnsignedLong(0);
			AuctionItemImplementation* item  = new AuctionItemImplementation(objectId);
			
			item->vendorID = items->getLong(10);
			item->planet = i;			
			BazaarMap* bazaarLocations = bazaarTerminals->getBazaarMap();
			BazaarTerminalDetails* bazaar = bazaarLocations->get(item->vendorID);
				
			string region = bazaar->getRegion();
			string planet = PlanetNames[i];
			item->setLocation(planet, region, item->vendorID, bazaar->getX(), bazaar->getZ(), false);
			item->ownerID = items->getUnsignedLong(4);
			item->ownerName = items->getString(5);
			item->itemName = items->getString(1);
			item->itemDescription = items->getString(2);
			item->itemType = items->getUnsignedInt(3);
			item->price = items->getUnsignedInt(6);
			item->auction = items->getBoolean(7);
			item->sold = items->getBoolean(8);
			item->expireTime = items->getUnsignedInt(9);
			item->buyerID = items->getUnsignedLong(12);
			item->bidderName = items->getString(13);
			
			AuctionItem* it = item->deploy();
			if (!item->sold) {
				bazaarPlanets[i]->addBazaarItem(it);
			}
			addItem(it);
		}
		delete items;
	}
	
	info("Bazaars populated");
	
	// Setup event handling to check auction items

	checkEvent = new CheckBazaarStatus(this);
	checkAuctions();

}

bool BazaarManagerImplementation::isBazaarTerminal(uint64 objectID) {
	if (bazaarTerminals->isBazaarTerminal(objectID) != NULL)
		return true;
	else
		return false;	
}

void BazaarManagerImplementation::newBazaarRequest(uint64 bazaarID, Player* player, int planet) {
	BazaarTerminalDetails* location;
	
	bool vendor;
	
	string header;
	
	int bazaarX;
	int bazaarZ;
	
	if ((location = bazaarTerminals->isBazaarTerminal(bazaarID)) == NULL)
		vendor = true;
	else
		vendor = false;
	
	string planetString = PlanetNames[planet];
	
	if (!vendor) {
		header = location->getRegion();
		
		bazaarX = location->getX();
		bazaarZ = location->getZ();
	}

	BaseMessage* msg = new IsVendorOwnerResponseMessage(vendor, bazaarID, planetString, header, bazaarX, bazaarZ);
	player->sendMessage(msg);
	
	msg = new BazaarDisplayUI(vendor, bazaarID, player);
	player->sendMessage(msg);
}

void BazaarManagerImplementation::addSaleItem(Player* player, uint64 objectid, uint64 bazaarid, unicode& description, int price, uint32 duration, bool auction) {
	uint32 itemType;
	string identity;
	
	lock();
	
	player->wlock();
	
	// Check if the item is already for sale
	if (items.find(objectid) >= 0) {
		
		stringstream str;
		str << player->getCharacterName().c_str() << " trying to add objectid "
			<< objectid << " to the bazaar again";
		error(str.str());
		
		BaseMessage* msg = new ItemSoldMessage(objectid, 6);
		player->sendMessage(msg);
		
		player->unlock();
		unlock();
		return;
	}

	if (price > MAXPRICE) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 14);
		player->sendMessage(msg);
		
		player->unlock();
		unlock();
		return;
		
	} else if (price < 1) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 4);
		player->sendMessage(msg);
		
		player->unlock();
		unlock();
		return;
	}

	if (player->getBankCredits() < SALESFEE) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 9);
		player->sendMessage(msg);
		
		player->unlock();
		unlock();
		return;
	}
	
	int numberOfItems;
	
	try {
		stringstream query1;
		query1 << "SELECT count(*) from `bazaar_items` WHERE ownerid = " << player->getObjectID() << ";";
		ResultSet* res = ServerDatabase::instance()->executeQuery(query1);

		res->next();
		numberOfItems = res->getInt(0);

		delete res;
		
	} catch(DatabaseException& e) {
		cout << "Can't count bazaar_items for user " << player->getCharacterName().c_str() << "\n";
		player->unlock();
		unlock();
		return;
	}

	
	if (numberOfItems >= MAXSALES) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 13);
		player->sendMessage(msg);
		
		player->unlock();
		unlock();
		return;			
	}
	
	BazaarMap* bazaarLocations = bazaarTerminals->getBazaarMap();
	BazaarTerminalDetails* bazaar = bazaarLocations->get(bazaarid);
	
	TangibleObject* obj = (TangibleObject*)player->getInventoryItem(objectid);
	
	if (obj == NULL) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 2);
		player->sendMessage(msg);
		
		player->unlock();
		unlock();
		return;			
	}
	
	if (obj->isEquipped()) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 2);
		player->sendMessage(msg);
		
		player->sendSystemMessage("you must unequip your item!!");
		
		player->unlock();
		unlock();
		return;
	}
	
	itemType = obj->getObjectSubType();

	string name = obj->getName().c_str();

	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	if(!obj->isPersistent())
		itemManager->createPlayerItem(player, obj);
	if(obj->isUpdated())
		itemManager->savePlayerItem(player, obj);
		
	Time expireTime;
	expireTime.addMiliTime(duration * 1000);
	uint64 expire = expireTime.getMiliTime() / 1000;
	
	int auctionout;
	if(auction)
		auctionout = 1;
	else
		auctionout = 0;

	int planet = bazaar->getPlanet();
	
	string playername = player->getFirstName();
	String::toLower(playername);
	
	try {
		stringstream query2;
		query2 << "INSERT into `bazaar_items` (objectid, name, description, item_type, ownerid, ownername,"
			<< " price, auction, sold, expire, terminalid, planet, buyerid, bidderName) "
			<< "VALUES (" << objectid << ",'\\" << name << "','" << description.c_str() << "'," << itemType << "," 
			<< player->getObjectID() << ",'" << playername << "'," << price << "," << auctionout << ",0," 
			<< expire << "," << bazaarid << "," << planet << ",0,'');";
	
		ServerDatabase::instance()->executeStatement(query2);
		
		stringstream query3;
		query3 << "UPDATE `character_items` SET character_id = 0 where item_id = " << objectid << ";";
	
		ServerDatabase::instance()->executeStatement(query3);
		
	} catch(DatabaseException& e) {
		cout << "Can't add bazaar_item " << objectid << "\n";
		player->unlock();
		unlock();
		return;
	}
	
	AuctionItemImplementation* item  = new AuctionItemImplementation(objectid);
	
	item->planet = planet;
	item->vendorID = bazaarid;
	string region = bazaar->getRegion();
	string planetStr = PlanetNames[planet];	
	item->setLocation(planetStr, region, bazaarid, bazaar->getX(), bazaar->getZ(), false);
	item->ownerID = player->getObjectID();
	item->ownerName = playername;
	item->itemName = name;
	item->itemDescription = description.c_str();
	item->itemType = itemType;
	item->price = price;
	item->auction = auction;
	item->sold = false;
	item->expireTime = expire;
	item->buyerID = 0;
	item->bidderName = "";
	
	AuctionItem* it = item->deploy();
	bazaarPlanets[planet]->addBazaarItem(it);
	addItem(it, false);
	
	string str1 = "base_player";
	string str2 = "sale_fee";
	unicode uni = unicode("");

	player->removeInventoryItem(objectid);
	obj->finalize();
	
	BaseMessage* msg = new ChatSystemMessage(str1, str2, uni, SALESFEE, true);
	player->sendMessage(msg);
	
	msg = new ItemSoldMessage(objectid, 0);
	player->sendMessage(msg);
	
	msg = new SceneObjectDestroyMessage(objectid);
	player->sendMessage(msg);
	
	player->subtractBankCredits(SALESFEE);
	
	player->unlock();
	unlock();
}

BazaarPlanetManager* BazaarManagerImplementation::getPlanet(uint64 bazaarid) {
	BazaarTerminalDetails* location;
	
	location = bazaarTerminals->getBazaarMap()->get(bazaarid);
	int planet = location->getPlanet();
	return bazaarPlanets[planet];
}

RegionBazaar* BazaarManagerImplementation::getBazaar(uint64 bazaarid) {
	BazaarTerminalDetails* location;

	if ((location = bazaarTerminals->isBazaarTerminal(bazaarid)) != NULL) {
		return location->getTerminal();
	}
	else
		return NULL;
}

void BazaarManagerImplementation::checkAuctions() {
	lock();
	
	info("Checking auctions");

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;
	
	for (int i = 0; i < items.size(); i++) {
		AuctionItem* item = items.get(i);
		uint64 objectId = item->getId();
		
		if (item->getExpireTime() <= currentTime) {
			if (item->isSold()) {

				bazaarPlanets[item->getPlanet()]->removeBazaarItem(objectId);
				if (removeItem(objectId, false)) {
					//item->finalize(); FOR GODS SAKE WE CANT DELETE THIS HERE, the reference is still stored somewhere else
				}
				
				stringstream del1;
				del1 << "DELETE from `bazaar_items` WHERE objectid = " << objectId << ";";

				stringstream del2;
				del2 << "DELETE from `character_items` WHERE objectid = " << objectId << ";";
				
				try {
					ServerDatabase::instance()->executeStatement(del1);
					ServerDatabase::instance()->executeStatement(del2);
					
				} catch (DatabaseException& e) {
					cout << "Can't delete bazaar_item " << objectId << "\n";
					
					unlock();
					return;
				}
			} else {
				ChatManager* cman = processServer->getChatManager();

				 // retrieve failed auctions for owner
				if (item->getBidderName().length() < 1)
				{
					item->setBuyerId(item->getOwnerId());
					item->setBidderName(item->getOwnerName());
					
					stringstream message;
					unicode subject("Auction Unsuccessful");

					message << "Your auction of " << item->getItemName() <<
						" has been completed and has not been  purchased.";
					unicode body(message.str());
					
					cman->sendMail("Auctioner", subject, body, item->getOwnerName());
				
				// bidder won auction. handle transactions and send messages
				} else {
					PlayerManager* pman = zoneServer->getPlayerManager();
					pman->modifyRecipientOfflineBank(item->getOwnerName(), item->getPrice());
					
					string sender = "Auctioner";
					stringstream message1;
					unicode subject1("Auction Sale Complete");
					unicode subject2("Auction Won");
					
					message1 << "Your auction of " << item->getItemName() << " has been sold to " << item->getBidderName()
						<< " for " << item->getPrice() << " credits.";

					unicode body1(message1.str());

					cman->sendMail(sender, subject1, body1, item->getOwnerName());
					
					stringstream message2;
					
					message2 << "You have won the auction of " << item->getItemName() << " from " << item->getOwnerName() << " for " << item->getPrice() << " credits.\n"
						<< "The sale took place at " << item->getLocation();
					unicode body2(message2.str());
					cman->sendMail(sender, subject2, body2, item->getBidderName());
					
					item->setOwnerId(item->getBuyerId());
					item->setOwnerName(item->getBidderName());
				}
				
				// move to available items
				bazaarPlanets[item->getPlanet()]->removeBazaarItem(objectId);
				
				item->setSold(true);
				item->setExpireTime(availableTime);
				item->setBuyerId(item->getOwnerId());
				
				stringstream update;
				update << "UPDATE `bazaar_items` SET sold = 1, expire = " << availableTime << ", buyerid = " 
					<< item->getBuyerId() << ", bidderName = '" << item->getBidderName() << "', ownerid = "
					<< item->getOwnerId() << ", ownerName = '" << item->getOwnerName() << "' where objectid = " << item->getId() << ";";

				try {
					ServerDatabase::instance()->executeStatement(update);
				} catch (DatabaseException& e) {
					cout << "Can't update bazaar_item " << objectId << "\n";
					cout << update.str() << "\n";
					
					unlock();
					return;
				}
			}
		}
	}

	processServer->addEvent(checkEvent, CHECKEVERY * 60000);

	unlock();
}

void BazaarManagerImplementation::buyItem(Player* player, uint64 objectid, int price1, int price2) {
	try {
		lock();
		player->wlock();
	
		ChatManager *cman = processServer->getChatManager();
		PlayerManager *pman = processServer->getPlayerManager();
		AuctionItem* item = getItem(objectid, false);
	
		string playername = player->getFirstName();
		String::toLower(playername);
	
		if (item == NULL) { // send invalid item message
		
			BaseMessage* msg = new BidAuctionResponseMessage(objectid, 2);
			player->sendMessage(msg);
		
			player->unlock();
			unlock();
			return;
		}
		
		if (price1 > MAXPRICE || price2 > MAXPRICE) {
			BaseMessage* msg = new BidAuctionResponseMessage(objectid, 14);
			player->sendMessage(msg);
			
			player->unlock();
			unlock();
			return;
			
		} else if (price1 < 1 || price2 < 1) {
			BaseMessage* msg = new BidAuctionResponseMessage(objectid, 4);
			player->sendMessage(msg);
			
			player->unlock();
			unlock();
			return;
		}

		Time expireTime;
		uint64 currentTime = expireTime.getMiliTime() / 1000;
		uint64 availableTime = currentTime + 2592000;
	
		if (player->getBankCredits() < price1) { // Credit Check
		
			BaseMessage* msg = new BidAuctionResponseMessage(objectid, 9);
			player->sendMessage(msg);
		
			player->unlock();
			unlock();
			return;
		}

		if (!item->getAuction()) { // Instant buy
			item->setSold(true);
			item->setExpireTime(availableTime);
			item->setBuyerId(player->getObjectID());
			item->setBidderName(playername);

			stringstream update;
			update << "UPDATE `bazaar_items` SET sold = 1, expire = " << availableTime << ", buyerid = "
				<< item->getBuyerId() << ", bidderName='" << item->getBidderName() << "' where objectid = " << item->getId() << ";";
			try {
			
				ServerDatabase::instance()->executeStatement(update);
			
				player->subtractBankCredits(price1);

			// move to available items
				bazaarPlanets[item->getPlanet()]->removeBazaarItem(item->getId());
			
				BaseMessage* msg = new BidAuctionResponseMessage(objectid, 0);
				player->sendMessage(msg);
			
			// send the bidder a message
				stringstream body;
			
				body << "You have won the auction of " << item->getItemName() << " from " << item->getOwnerName() << " for " << price1 << " credits.\n"
					"The sale took place at " << item->getLocation();
				unicode subject1("Instant Sale Item, Puchased");
				unicode ubody1(body.str());
			
				player->sendSystemMessage(body.str());
				cman->sendMail("Auctioner", subject1, ubody1, item->getBidderName());
			
			// send the seller a message
				stringstream body2;
			
				body2 << "Your auction of  " << item->getItemName() << " has been sold to " << item->getBidderName()
					<< " for " << price1 << " credits.";
				unicode subject2("Instant Sale Complete");
				unicode ubody2(body2.str());
				cman->sendMail("Auctioner", subject2, ubody2, item->getOwnerName());
			
			// pay the seller
				Player* seller = pman->getPlayer(item->getOwnerName());
				
				if (seller != NULL) {
					try {
						if (seller != player)
							seller->wlock(player);
							
						seller->sendSystemMessage(body2.str());
						seller->addBankCredits(price1);
						
						
						if (seller != player)
							seller->unlock();
					} catch(...) {
						if (player != seller)
							seller->unlock();
						error("Unreported1 exception caught in BazaarManagerImplementation::buyItem(Player* player, uint64 objectid, int price1, int price2)");
					}
				} else {
					if (!pman->modifyRecipientOfflineBank(item->getOwnerName(), price1)) {
						player->unlock();
						unlock();
						return;
					}
				}
	

			} catch (DatabaseException& e) {
				BaseMessage* msg = new BidAuctionResponseMessage(objectid, 2);
				player->sendMessage(msg);
				cout << "Can't update bazaar_item " << item->getId() << "\n";
				cout << update.str() << "\n";
			
				player->unlock();
				unlock();
				return;
			}
		} else { // For Auction Bids
		
		// don't allow owner or last bidder bid on the item.  don't allow old auction info
		// send auctioner invalid message
			if (playername == item->getBidderName() || playername == item->getOwnerName() || price1 <= item->getPrice()) {
				BaseMessage* msg = new BidAuctionResponseMessage(objectid, 1);
				player->sendMessage(msg);
				player->unlock();
				unlock();
				return;
			}
		
		// send prior bidder their money back
			if (item->getBidderName().length() > 0) {
				stringstream body;
			
				Player* priorBidder = pman->getPlayer(item->getBidderName());
				body << playername << " outbid you on " << item->getItemName() << ".";
			
				if (priorBidder != NULL) {
					try {
						if (priorBidder != player)
							priorBidder->wlock(player);
							
							priorBidder->sendSystemMessage(body.str());
							priorBidder->addBankCredits(item->getPrice());
							
						if (priorBidder != player)
							priorBidder->unlock();
					} catch(...) {
						if (priorBidder != player)
							priorBidder->unlock();
						
						error("Unreported2 exception caught in BazaarManagerImplementation::buyItem(Player* player, uint64 objectid, int price1, int price2)");
					}
				} else {
					if(!pman->modifyRecipientOfflineBank(item->getBidderName(), item->getPrice())) {
						player->unlock();
						unlock();
						
						return;					
					}
				}
				

			// mail prior bidder with outcome
				unicode subject("Outbid");
				unicode ubody(body.str());
			
				cman->sendMail("Bazaar", subject, ubody, item->getBidderName());
				item->setPrice(price1);
				item->setBuyerId(player->getObjectID());
				item->setBidderName(playername);
			
			// take money from high bidder
				player->subtractBankCredits(price1);
			
		// no prior bidder, just take the money
			} else {
				item->setPrice(price1);
				item->setBuyerId(player->getObjectID());
				item->setBidderName(playername);
			
				player->subtractBankCredits(price1);
			}
		
			stringstream update; 
			update << "UPDATE `bazaar_items` SET price = " << price1 << ", bidderName = '" << item->getBidderName() << "', buyerid = " << player->getObjectID() << " where objectid = " << objectid << ";"; 
			try { 
	                                 
		 		ServerDatabase::instance()->executeStatement(update);
		 	
			} catch (DatabaseException& e) { 
		 		cout << "Can't update bazaar_item " << item->getId() << "\n"; 
		 		cout << update.str() << "\n"; 
		 	
		 		BaseMessage* msg = new BidAuctionResponseMessage(objectid, 2);
		 		player->sendMessage(msg);
			 	
		 		player->unlock();
		 		unlock();
		 		return; 
			} 
			BaseMessage* msg = new BidAuctionResponseMessage(objectid, 0); 
			player->sendMessage(msg);
		}
	
		player->unlock();
		unlock();
		
	} catch (Exception& e) {
		player->unlock();
		unlock();
		
		error("Unreported3 exception caught in BazaarManagerImplementation::buyItem(Player* player, uint64 objectid, int price1, int price2)");
		e.printStackTrace();
	} catch (...) {
		player->unlock();
		unlock();
		
		error("Unreported3 exception caught in BazaarManagerImplementation::buyItem(Player* player, uint64 objectid, int price1, int price2)");
	}
}

void BazaarManagerImplementation::retrieveItem(Player* player, uint64 objectid, uint64 bazaarid) {
	BaseMessage* msg;
	
	try {
		lock();
		player->wlock();
	
	// Check player is at correct bazaar
		AuctionItem* item = getItem(objectid, false);
		string playername = player->getFirstName().c_str();
	
	// object was probably already retrieved
		if (item == NULL) {
			msg = new RetrieveAuctionItemResponseMessage(objectid, 1);
			player->sendMessage(msg);
		
			player->unlock();
			unlock();
			return;
		}
	
	// only the owner can yank his own auction off the bazaar
		if (!item->isSold() && item->getOwnerName() != playername ) {
			msg = new RetrieveAuctionItemResponseMessage(objectid, 1);
			player->sendMessage(msg);
		
			player->unlock();
			unlock();
			return;
		}
	
	// the bidder is the only one who can get his auction after expiration
		if (item->isSold() && item->getBuyerId() != player->getObjectID()) {
			msg = new RetrieveAuctionItemResponseMessage(objectid, 1);
			player->sendMessage(msg);
			player->unlock();
			unlock();
			return;
		}
		BazaarTerminalDetails* location = bazaarTerminals->getBazaarMap()->get(bazaarid);
		string region = location->getRegion();
	
		if (item->getLocation().find(region) == string::npos) {
			msg = new RetrieveAuctionItemResponseMessage(objectid, 1);
			player->sendMessage(msg);
			player->unlock();
			unlock();
			return;
		}

	// Check if inventory is full
		Inventory * inventory = player->getInventory();
	
		if (inventory->objectsSize() > 79) {
			msg = new RetrieveAuctionItemResponseMessage(objectid, 12);
			player->sendMessage(msg);
			player->unlock();
			unlock();
			return;
		}
	
		try {
			stringstream update;
			update << "UPDATE `character_items` SET character_id = " << player->getCharacterID() << " WHERE item_id = " << objectid;
			stringstream delBazaar;
			delBazaar << "DELETE FROM `bazaar_items` WHERE objectid = " << objectid;
		
			ServerDatabase::instance()->executeStatement(update);
			ServerDatabase::instance()->executeStatement(delBazaar);
		
		} catch(DatabaseException& e) {
			cout << "Can't remove bazaar_item " << objectid << "\n";
			msg = new RetrieveAuctionItemResponseMessage(objectid, 1);
			player->sendMessage(msg);
			player->unlock();
			unlock();
			return;
		}

	// refund money to bidder for sniping the auction
		if (!item->isSold() && item->getBidderName().length() > 0) {
			PlayerManager* pman = processServer->getPlayerManager();
			Player* bidder = pman->getPlayer(item->getBidderName());
			ChatManager* cman = processServer->getChatManager();
		
		// send the player a mail and system message
			unicode subject("Auction Cancelled");
			stringstream mess;
			mess <<  "Your bid on " << item->getItemName() << " was retracted because the auction was cancelled by the owner.";
			unicode body(mess.str());
		
			if (bidder != NULL) {
				try {
					if (bidder != player)
						bidder->wlock(player);
						
					bidder->addBankCredits(item->getPrice());
					bidder->sendSystemMessage(mess.str());
					
					if (bidder != player)
						bidder->unlock();
				} catch (...) {
					if (bidder != player)
						bidder->unlock();
					error("Unreporeted1 exception caught in BazaarManagerImplementation::retrieveItem(Player* player, uint64 objectid, uint64 bazaarid)");
				}
			} else
				pman->modifyRecipientOfflineBank(item->getBidderName(), item->getPrice());
			
			cman->sendMail("auctioner", subject, body, item->getBidderName());
			bazaarPlanets[item->getPlanet()]->removeBazaarItem(item->getId());
		}
	
		ItemManager* itemManager = processServer->getItemManager();
		TangibleObject* tano = itemManager->getPlayerItem(player, objectid);
	
	// TODO: handle this case
		if (tano == NULL) {
			player->unlock();
			unlock();
			return;
		}
	
		tano->sendTo(player);
	
		msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
		player->sendMessage(msg);
		player->unlock();
		 
		if (removeItem(objectid, false));
			//item->finalize();  FOR GODS SAKE WE CANT DELETE THIS HERE, the reference is still stored somewhere else
	
		unlock();
	} catch (...) {
		player->unlock();
		unlock();
		
		error("Unreported2 exception caught in BazaarManagerImplementation::retrieveItem(Player* player, uint64 objectid, uint64 bazaarid)");
	}
}

void BazaarManagerImplementation::getItemAttributes(Player* player, uint64 objectid) {
	if (player == NULL)
		return;
	
	lock();
	player->wlock();
		
	ItemManager* itemManager = zoneServer->getItemManager();
	TangibleObject* object = itemManager->getPlayerItem(NULL, objectid);
	
	if (object == NULL) {
		player->unlock();
		unlock();
		return;
	}
	
	unicode description;
	AuctionItem* item = getItem(objectid, false);
	if(item == NULL)
		description = unicode("");
	else
		description = unicode(item->getItemDescription());
	
	AttributeListMessage* msg = new AttributeListMessage(objectid, description);
	
	object->addAttributes(msg);
	msg->insertInt(0);
	player->sendMessage(msg);

	object->finalize();
	player->unlock();
	unlock();
}
