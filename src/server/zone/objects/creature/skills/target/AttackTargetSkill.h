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

#ifndef ATTACKTARGETSKILL_H_
#define ATTACKTARGETSKILL_H_

#include "../TargetSkill.h"
#include "../PassiveSkill.h"
#include "../../../tangible/wearables/Armor.h"

#include "../../../../packets/object/ShowFlyText.h"

class CombatManager;

class AttackTargetSkill : public TargetSkill {
protected:
	float damageRatio;

	int healthPoolAttackChance;
	int strengthPoolAttackChance;
	int constitutionPoolAttackChance;
	 
	int actionPoolAttackChance;
	int quicknessPoolAttackChance;
	int staminaPoolAttackChance;	
	
	int mindPoolAttackChance;
	int focusPoolAttackChance;
	int willpowerPoolAttackChance;
	
	int areaRangeDamage;
	
	int accuracyBonus;

	bool hasStateChance;

	int knockdownStateChance;
	int postureDownStateChance;
	int postureUpStateChance;

	int dizzyStateChance;
	int blindStateChance;
	int stunStateChance;
	int intimidateStateChance;
		
	int requiredWeaponType;
	
	string CbtSpamBlock;
	string CbtSpamCounter;
	string CbtSpamEvade;
	string CbtSpamHit;
	string CbtSpamMiss;

public:
	AttackTargetSkill(const string& name, const string& anim, ZoneProcessServerImplementation* serv) : TargetSkill(name, anim, ATTACK, serv) {
		healthPoolAttackChance = 0;
		strengthPoolAttackChance = 0;
		constitutionPoolAttackChance = 0;
		
		actionPoolAttackChance = 0;
		quicknessPoolAttackChance = 0;
		staminaPoolAttackChance = 0;
		
		mindPoolAttackChance = 0;
		focusPoolAttackChance = 0;
		willpowerPoolAttackChance = 0;
		
		damageRatio = 1.0f;
		
		areaRangeDamage = 0;
		
		accuracyBonus = 0;
		
		hasStateChance = false;
		
		knockdownStateChance = 0;
		postureDownStateChance = 0;
		postureUpStateChance = 0;
		dizzyStateChance = 0;
		blindStateChance = 0;
		stunStateChance = 0;
		intimidateStateChance = 0;
		
		requiredWeaponType = 0xFF; // NONE
	}

	virtual int calculateDamage(CreatureObject* creature, CreatureObject* targetCreature) = 0;
	virtual bool calculateCost(CreatureObject* creature) {
		return creature->changeMindBar(-50);
	}
	
	void doAnimations(CreatureObject* creature, CreatureObject* targetCreature, bool doAnimations = true) {
		/*
		if (secondaryAnim.size() != 0)
			player->playSecondaryAnim(secondaryAnim);
			
		if (selfMessage.size() != 0)
			player->showMessage;
		
		if (targetMessage.size() != 0)
			targetPlayer->showMessage;
		*/
	}

	int applyHealthPoolDamage(CreatureObject* attacker, CreatureObject* target, int32 damage, int part = 1) {
		
		Weapon* weapon = attacker->getWeapon();
		Armor* armor = target->getArmor(part);
				
		int reduction = 0;
		
		if (target->isPlayer())
			reduction = doArmorResists(armor, weapon, damage);
		else if (weapon != NULL)
			reduction = int(target->getArmorResist(weapon->getDamageType()) * damage / 100);
		else
			reduction = int(target->getArmorResist(WeaponImplementation::KINETIC) * damage / 100);
		
		damage = damage - reduction;
				
		target->changeHealthBar((int32) damage, true);
		
		target->addDamage(attacker, -damage);
			
		if (part < 3) {
			if (attacker->isPlayer()) {
				ShowFlyText* fly = new ShowFlyText(target, "combat_effects", "hit_body", 0xFF, 0, 0);
				((Player*)attacker)->sendMessage(fly);
			}
		} else if (part < 5) {
			if (attacker->isPlayer()) {
				ShowFlyText* fly = new ShowFlyText(target, "combat_effects", "hit_larm", 0xFF, 0, 0);
				((Player*)attacker)->sendMessage(fly);
			}
		} else {
			if (attacker->isPlayer()) { 
				ShowFlyText* fly = new ShowFlyText(target, "combat_effects", "hit_rarm", 0xFF, 0, 0);
				((Player*)attacker)->sendMessage(fly);
			}
		}
		
		if (target->isPlayer() && reduction != 0)
			target->sendCombatSpam(target,(TangibleObject*) armor, -reduction, "armor_damaged", false);
		
		int woundsRatio = 5;
		
		if (weapon != NULL) {
			woundsRatio = weapon->getWoundsRatio();
			
			if (weapon->decreasePowerupUses())
					weapon->setUpdated(true);
				else if (weapon->hasPowerup())
					weapon->removePowerup((Player*)attacker, true);
		}
		
		if (woundsRatio > System::random(100)) {
			target->changeHealthWoundsBar(1, true);
			target->changeShockWounds(1);
			if (target->isPlayer()) {
				target->sendCombatSpam(attacker, NULL, 1, "wounded", false);
				target->sendCombatSpam(attacker, NULL, 1, "shock_wound", false);
			}
			if (armor != NULL) {
				armor->setConditionDamage(armor->getConditionDamage() + 1);
				armor->setUpdated(true);
			}
			
			if (weapon != NULL && System::random(10) == 1) {
				weapon->setConditionDamage(weapon->getConditionDamage() + 1);
				weapon->setUpdated(true);
			}
		}
		
		doDotWeaponAttack(attacker, target, 0);
		
		return reduction;
	}
	
	void applyStrengthPoolDamage(CreatureObject* target, int32 damage) {
		target->changeStrengthBar((int32) damage, true);
	}
	
	void applyConstitutionPoolDamage(CreatureObject* target, int32 damage) {
		target->changeConstitutionBar((int32) damage, true);
	}

	int applyActionPoolDamage(CreatureObject* attacker, CreatureObject* target, int32 damage, int part = 7) {
		
		Weapon* weapon = attacker->getWeapon();
		Armor* armor = target->getArmor(part);

		int reduction = 0;
		
		if (target->isPlayer())
			reduction = doArmorResists(armor, weapon, damage);
		else if (weapon != NULL)
			reduction = int(target->getArmorResist(weapon->getDamageType()) * damage / 100);
		else
			reduction = int(target->getArmorResist(WeaponImplementation::KINETIC) * damage / 100);
		
		damage = damage - reduction;
		
		target->changeActionBar((int32) damage, true);
		
		target->addDamage(attacker, -damage);
		
		if (part == 7) {  // below is sending flytext for the wrong parts...
			if (attacker->isPlayer()) {
				ShowFlyText* fly = new ShowFlyText(target, "combat_effects", "hit_lleg", 0, 0xFF, 0);
				((Player*)attacker)->sendMessage(fly);
			}
		} else {
			if (attacker->isPlayer()) { 
				ShowFlyText* fly = new ShowFlyText(target, "combat_effects", "hit_rleg", 0, 0xFF, 0);
				((Player*)attacker)->sendMessage(fly);
			}
		}
		
		if (target->isPlayer() && reduction != 0)
			target->sendCombatSpam(target,(TangibleObject*) armor, -reduction, "armor_damaged", false);
		
		int woundsRatio = 5;
		
		if (weapon != NULL) {
			woundsRatio = weapon->getWoundsRatio();
			
			if (weapon->decreasePowerupUses())
					weapon->setUpdated(true);
			else if (weapon->hasPowerup())
					weapon->removePowerup((Player*)attacker, true);
		}

		
		if (woundsRatio > System::random(100)) {
			target->changeActionWoundsBar(1, true);
			target->changeShockWounds(1);
			if (target->isPlayer()) {
				target->sendCombatSpam(attacker, NULL, 1, "wounded", false);
				target->sendCombatSpam(attacker, NULL, 1, "shock_wound", false);
			}
			if (armor != NULL) {
				armor->setConditionDamage(armor->getConditionDamage() + 1);
				armor->setUpdated(true);
			}
			
			if (weapon != NULL && System::random(10) == 1) {
				weapon->setConditionDamage(weapon->getConditionDamage() + 1);
				weapon->setUpdated(true);
			}
		}

		doDotWeaponAttack(attacker, target, 0);
				
		return reduction;
	}
	
	void applyQuicknessPoolDamage(CreatureObject* target, int32 damage) {
		target->changeQuicknessBar((int32) damage, true);
	}
	
	void applyStaminaPoolDamage(CreatureObject* target, int32 damage) {
		target->changeStaminaBar((int32) damage, true);
	}	

	int applyMindPoolDamage(CreatureObject* attacker, CreatureObject* target, int32 damage) {
		
		Weapon* weapon = attacker->getWeapon();
		Armor* armor = target->getArmor(9);
		
		int reduction = 0;
		
		if (target->isPlayer())
			reduction = doArmorResists(armor, weapon, damage);
		else if (weapon != NULL)
			reduction = int(target->getArmorResist(weapon->getDamageType()) * damage / 100);
		else
			reduction = int(target->getArmorResist(WeaponImplementation::KINETIC) * damage / 100);
		
		damage -= reduction;
		
		target->changeMindBar((int32) damage, true);
		
		target->addDamage(attacker, -damage);
		
		if (attacker->isPlayer()) {
			ShowFlyText* fly = new ShowFlyText(target, "combat_effects", "hit_head", 0, 0, 0xFF);
			((Player*)attacker)->sendMessage(fly);
		}
		
		if (target->isPlayer() && reduction != 0)
			target->sendCombatSpam(target,(TangibleObject*) armor, -reduction, "armor_damaged", false);
		
		int woundsRatio = 5;
		
		if (weapon != NULL) {
			woundsRatio = weapon->getWoundsRatio();
			
			if (weapon->decreasePowerupUses())
					weapon->setUpdated(true);
			else if (weapon->hasPowerup())
					weapon->removePowerup((Player*)attacker, true);
		}
		
		if (woundsRatio > System::random(100)) {
			target->changeMindWoundsBar(1, true);
			target->changeShockWounds(1);
			if (target->isPlayer()) {
				target->sendCombatSpam(attacker, NULL, 1, "wounded", false);
				target->sendCombatSpam(attacker, NULL, 1, "shock_wound", false);
			}
			if (armor != NULL) {
				armor->setConditionDamage(armor->getConditionDamage() + 1);
				armor->setUpdated(true);
			}
			
			if (weapon != NULL && System::random(10) == 1) {
				weapon->setConditionDamage(weapon->getConditionDamage() + 1);
				weapon->setUpdated(true);
			}
		}
		
		doDotWeaponAttack(attacker, target, 0);
				
		return reduction;
	}
	
	void applyFocusPoolDamage(CreatureObject* target, int32 damage) {
		target->changeFocusBar((int32) damage, true);
	}
	
	void applyWillpowerPoolDamage(CreatureObject* target, int32 damage) {
		target->changeWillpowerBar((int32) damage, true);
	}

	void doMiss(CreatureObject* creature, CreatureObject* target, int32 damage) {
		if (hasCbtSpamMiss()) 
			creature->sendCombatSpam(target, NULL, -(int32)damage, getCbtSpamMiss());
				
		target->showFlyText("combat_effects", "miss", 0xFF, 0xFF, 0xFF);
	}

	float calculateSpeed(CreatureObject* creature) {
		Weapon* weapon = creature->getWeapon();
		float weaponSpeed;
		
		int speedMod = 0;
		
		if (creature->isPlayer())
			if (weapon == NULL)
				speedMod = ((Player*)creature)->getSkillMod("unarmed_speed");
			else switch (weapon->getObjectSubType()) {
			case TangibleObjectImplementation::MELEEWEAPON:
				speedMod = ((Player*)creature)->getSkillMod("unarmed_speed");
				break;
			case TangibleObjectImplementation::ONEHANDMELEEWEAPON:
				speedMod = ((Player*)creature)->getSkillMod("onehandmelee_speed");
				break;
			case TangibleObjectImplementation::TWOHANDMELEEWEAPON:
				speedMod = ((Player*)creature)->getSkillMod("twohandmelee_speed");
				break;
			case TangibleObjectImplementation::POLEARM:
				speedMod = ((Player*)creature)->getSkillMod("polearm_speed");
				break;
			case TangibleObjectImplementation::PISTOL:
				speedMod = ((Player*)creature)->getSkillMod("pistol_speed");
				break;
			case TangibleObjectImplementation::CARBINE:
				speedMod = ((Player*)creature)->getSkillMod("carbine_speed");
				break;
			case TangibleObjectImplementation::RIFLE:
				speedMod = ((Player*)creature)->getSkillMod("rifle_speed");
				break;
			}

		if (weapon != NULL) {
			weaponSpeed = (float)((100.0f - speedMod) / 100.0f) * speedRatio * weapon->getAttackSpeed();
		} else
			weaponSpeed = (float)((100.0f - speedMod) / 100.0f) * 1;
		
		return MAX(weaponSpeed, 1.0f);
	}

	void calculateStates(CreatureObject* creature, CreatureObject* targetCreature) {
		if (hasStateChance) {
			checkKnockDown(creature, targetCreature);	
			checkPostureDown(creature, targetCreature);	
			checkPostureUp(creature, targetCreature);
			
			if (dizzyStateChance != 0) {
				int targetDefense = targetCreature->getSkillMod("dizzy_defense");
				targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());
				
				int rand = System::random(100);
				
				if ((5 > rand) || (rand > targetDefense))
					targetCreature->setDizziedState();
			}

			if (blindStateChance != 0) {
				int targetDefense = targetCreature->getSkillMod("blind_defense");
				targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());
				
				int rand = System::random(100);
				
				if ((5 > rand) || (rand > targetDefense))
					targetCreature->setBlindedState();
			}
			
			if (stunStateChance != 0) {
				int targetDefense = targetCreature->getSkillMod("stun_defense");
				targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());
				
				int rand = System::random(100);
				
				if ((5 > rand) || (rand > targetDefense))
					targetCreature->setStunnedState();
			}
			
			if (intimidateStateChance != 0) {
				int targetDefense = targetCreature->getSkillMod("intimidate_defense");
				targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());
				
				int rand = System::random(100);

				if ((5 > rand) || (rand > targetDefense))
					targetCreature->setIntimidatedState();
			}
			
			targetCreature->updateStates();
		}
	}
	
	void checkKnockDown(CreatureObject* creature, CreatureObject* targetCreature) {
		if (knockdownStateChance != 0) {
			if (creature->isPlayer() && (targetCreature->isKnockedDown() || targetCreature->isProne())) {
				if (80 > System::random(100))
					targetCreature->setPosture(CreatureObjectImplementation::UPRIGHT_POSTURE, true);
				return;
			}
			
			if (targetCreature->checkKnockdownRecovery()) {
				int targetDefense = targetCreature->getSkillMod("knockdown_defense");
				targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());
				int rand = System::random(100);
				
				if ((5 > rand) || (rand > targetDefense)) {
					if (targetCreature->isMounted())
						targetCreature->dismount();
					
					targetCreature->setPosture(CreatureObjectImplementation::KNOCKEDDOWN_POSTURE);
					targetCreature->updateKnockdownRecovery();
					targetCreature->sendSystemMessage("cbt_spam", "posture_knocked_down");

					int combatEquil = targetCreature->getSkillMod("combat_equillibrium");

					if (combatEquil > 100)
						combatEquil = 100;

					if ((combatEquil >> 1) > (int) System::random(100))
						targetCreature->setPosture(CreatureObjectImplementation::UPRIGHT_POSTURE, true);
				}
			} else
				creature->sendSystemMessage("cbt_spam", "knockdown_fail");
		}
	}
	
	void checkPostureDown(CreatureObject* creature, CreatureObject* targetCreature) {
		if (postureDownStateChance != 0) {
			if (creature->isPlayer() && (targetCreature->isKnockedDown() || targetCreature->isProne())) {
				if (80 > System::random(100))
					targetCreature->setPosture(CreatureObjectImplementation::UPRIGHT_POSTURE, true);
				return;
			} 
			
			if (targetCreature->checkPostureDownRecovery()) {
				int targetDefense = targetCreature->getSkillMod("posture_change_down_defense");
				targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());
				
				int rand = System::random(100);
				
				if ((5 > rand) || (rand > targetDefense)) {
					if (targetCreature->isMounted())
						targetCreature->dismount();
					
					if (targetCreature->getPosture() == CreatureObjectImplementation::UPRIGHT_POSTURE)
						targetCreature->setPosture(CreatureObjectImplementation::CROUCHED_POSTURE);
					else 
						targetCreature->setPosture(CreatureObjectImplementation::PRONE_POSTURE);
						
					targetCreature->updatePostureDownRecovery();
					targetCreature->sendSystemMessage("cbt_spam", "posture_down");
					
					int combatEquil = targetCreature->getSkillMod("combat_equillibrium");
			
					if (combatEquil > 100)
						combatEquil = 100;
				
					if ((combatEquil >> 1) > (int) System::random(100))
						targetCreature->setPosture(CreatureObjectImplementation::UPRIGHT_POSTURE, true);
				}
			} else
				creature->sendSystemMessage("cbt_spam", "posture_change_fail");
		}
	}
	
	void checkPostureUp(CreatureObject* creature, CreatureObject* targetCreature) {
		if (postureUpStateChance != 0 && targetCreature->checkPostureUpRecovery()) {
			int targetDefense = targetCreature->getSkillMod("posture_change_up_defense");
			targetDefense -= (int)(targetDefense * targetCreature->calculateBFRatio());
			
			int rand = System::random(100);
			
			if ((5 > rand) || (rand > targetDefense)) {
				if (targetCreature->isMounted())
					targetCreature->dismount();
				
				if (targetCreature->getPosture() == CreatureObjectImplementation::PRONE_POSTURE) {
					targetCreature->setPosture(CreatureObjectImplementation::CROUCHED_POSTURE);
					targetCreature->updatePostureUpRecovery();
				} else if (targetCreature->getPosture() ==  CreatureObjectImplementation::CROUCHED_POSTURE) {
					targetCreature->setPosture(CreatureObjectImplementation::UPRIGHT_POSTURE);
					targetCreature->updatePostureUpRecovery();
				}
			}
		} else if (!targetCreature->checkPostureUpRecovery())
			creature->sendSystemMessage("cbt_spam", "posture_change_fail");
	}
	
	void calculateDamageReduction(CreatureObject* creature, CreatureObject* targetCreature, float& damage) {
		server->getCombatManager()->calculateDamageReduction(creature, targetCreature, damage);
	}
	
	void checkMitigation(CreatureObject* creature, CreatureObject* targetCreature, float& minDamage, float& maxDamage) {
		server->getCombatManager()->checkMitigation(creature, targetCreature, minDamage, maxDamage);
	}
	
	void doDodge(CreatureObject* creature, CreatureObject* defender) {
		server->getCombatManager()->doDodge(creature, defender);
	}
	
	void doCounterAttack(CreatureObject* creature, CreatureObject* defender) {
		server->getCombatManager()->doCounterAttack(creature, defender);
	}
	
	void doBlock(CreatureObject* creature, CreatureObject* defender) {
		server->getCombatManager()->doBlock(creature, defender);
	}
	
	int checkSecondaryDefenses(CreatureObject* creature, CreatureObject* targetCreature) {
		return server->getCombatManager()->checkSecondaryDefenses(creature, targetCreature);
	}
	
	int getHitChance(CreatureObject* creature, CreatureObject* targetCreature) {
		return server->getCombatManager()->getHitChance(creature, targetCreature, accuracyBonus);
	}
	
	float getWeaponAccuracy(float currentRange, Weapon* weapon) {
		return server->getCombatManager()->getWeaponAccuracy(currentRange, weapon);
	}
	
	float getTargetDefense(CreatureObject* creature, CreatureObject* targetCreature, Weapon* weapon) {
		return server->getCombatManager()->getTargetDefense(creature, targetCreature, weapon);
	}

	void doDotWeaponAttack(CreatureObject* creature, CreatureObject* targetCreature, bool areaHit) {
		Weapon* weapon = creature->getWeapon();
		
		int resist = 0;
		
		if (weapon != NULL) {
			if (weapon->getDot0Uses() != 0) {
				switch (weapon->getDot0Type()) {
				case 1:
					resist = targetCreature->getSkillMod("resistance_bleeding");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot0Potency() - resist))
						targetCreature->setBleedingState(weapon->getDot0Strength(), weapon->getDot0Attribute(), weapon->getDot0Duration());
					break;	
				case 2:
					resist = targetCreature->getSkillMod("resistance_disease");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot0Potency() - resist))
					targetCreature->setDiseasedState(weapon->getDot0Strength(), weapon->getDot0Attribute(), weapon->getDot0Duration());
					break;	
				case 3:
					resist = targetCreature->getSkillMod("resistance_fire");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot0Potency() - resist))
					targetCreature->setOnFireState(weapon->getDot0Strength(), weapon->getDot0Attribute(), weapon->getDot0Duration());
					break;	
				case 4:
					resist = targetCreature->getSkillMod("resistance_poison");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot0Potency() - resist))
					targetCreature->setPoisonedState(weapon->getDot0Strength(), weapon->getDot0Attribute(), weapon->getDot0Duration());
					break;	
				}
			
				if (areaHit == 0 && weapon->decreaseDot0Uses()) {
					weapon->setUpdated(true);
				}
			}
			
			if (weapon->getDot1Uses() != 0) {
				switch (weapon->getDot1Type()) {
				case 1:
					resist = targetCreature->getSkillMod("resistance_bleeding");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot1Potency() - resist))
						targetCreature->setBleedingState(weapon->getDot1Strength(), weapon->getDot1Attribute(), weapon->getDot1Duration());
					break;	
				case 2:
					resist = targetCreature->getSkillMod("resistance_disease");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot1Potency() - resist))
					targetCreature->setDiseasedState(weapon->getDot1Strength(), weapon->getDot1Attribute(), weapon->getDot1Duration());
					break;	
				case 3:
					resist = targetCreature->getSkillMod("resistance_fire");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot1Potency() - resist))
					targetCreature->setOnFireState(weapon->getDot1Strength(), weapon->getDot1Attribute(), weapon->getDot1Duration());
					break;	
				case 4:
					resist = targetCreature->getSkillMod("resistance_poison");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot1Potency() - resist))
					targetCreature->setPoisonedState(weapon->getDot1Strength(), weapon->getDot1Attribute(), weapon->getDot1Duration());
					break;	
				}
				
				if (areaHit == 0 && weapon->decreaseDot1Uses()) {
					weapon->setUpdated(true);
				}
			}
			
			if (weapon->getDot2Uses() != 0) {
				switch (weapon->getDot2Type()) {
				case 1:
					resist = targetCreature->getSkillMod("resistance_bleeding");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot2Potency() - resist))
						targetCreature->setBleedingState(weapon->getDot2Strength(), weapon->getDot2Attribute(), weapon->getDot2Duration());
					break;	
				case 2:
					resist = targetCreature->getSkillMod("resistance_disease");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot2Potency() - resist))
					targetCreature->setDiseasedState(weapon->getDot2Strength(), weapon->getDot2Attribute(), weapon->getDot2Duration());
					break;	
				case 3:
					resist = targetCreature->getSkillMod("resistance_fire");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot2Potency() - resist))
					targetCreature->setOnFireState(weapon->getDot2Strength(), weapon->getDot2Attribute(), weapon->getDot2Duration());
					break;	
				case 4:
					resist = targetCreature->getSkillMod("resistance_poison");
					if (resist > 25) 
						resist = 25;
					
					if ((int) System::random(100) < (weapon->getDot2Potency() - resist))
					targetCreature->setPoisonedState(weapon->getDot2Strength(), weapon->getDot2Attribute(), weapon->getDot2Duration());
					break;	
				}
				
				if (areaHit == 0 && weapon->decreaseDot2Uses()) {
					weapon->setUpdated(true);
				}
			}
		}
	}

	int doArmorResists(Armor* armor, Weapon* weapon, int dmg) {
		float resist = 0;
		int damageType = WeaponImplementation::KINETIC;
		
		if (weapon != NULL)
			damageType = weapon->getDamageType();

		if (armor != NULL)
			switch (damageType) {
			case WeaponImplementation::KINETIC:
				resist = armor->getKinetic();
				break;
			case WeaponImplementation::ENERGY:
				resist = armor->getEnergy();
				break;
			case WeaponImplementation::ELECTRICITY:
				resist = armor->getElectricity();
				break;
			case WeaponImplementation::STUN:
				resist = armor->getStun();
				break;
			case WeaponImplementation::BLAST:
				resist = armor->getBlast();
				break;
			case WeaponImplementation::HEAT:
				resist = armor->getHeat();
				break;
			case WeaponImplementation::COLD:
				resist = armor->getCold();
				break;
			case WeaponImplementation::ACID:
				resist = armor->getAcid();
				break;
			case WeaponImplementation::LIGHTSABER:
				resist = armor->getLightSaber();
				break;
			}
	
		return int(dmg*resist/100);
	}
	
	bool isArea() {
		if (areaRangeDamage != 0) {
			return true;
		} else
			return isConeSkill;
	}
	
	bool isCone() {
		return false;
	}
	
	inline void setDamageRatio(float ratio) {
		damageRatio = ratio;
	}

	inline void setHealthPoolAttackRatio(int ratio) {
		healthPoolAttackChance = ratio;
	}
	
	inline void setStrengthPoolAttackRatio(int ratio) {
		strengthPoolAttackChance = ratio;
	}
	
	inline void setConstitutionPoolAttackRatio(int ratio) {
		constitutionPoolAttackChance = ratio;
	}

	inline void setActionPoolAttackRatio(int ratio) {
		actionPoolAttackChance = ratio;
	}
	
	inline void setQuicknessPoolAttackRatio(int ratio) {
		quicknessPoolAttackChance = ratio;
	}
	
	inline void setStaminaPoolAttackRatio(int ratio) {
		staminaPoolAttackChance = ratio;
	}

	inline void setMindPoolAttackRatio(int ratio) {
		mindPoolAttackChance = ratio;
	}
	
	inline void setFocusPoolAttackRatio(int ratio) {
		focusPoolAttackChance = ratio;
	}
	
	inline void setWillpowerPoolAttackRatio(int ratio) {
		willpowerPoolAttackChance = ratio;
	}

	inline void setKnockdownChance(int chance) {
		knockdownStateChance = chance;
		hasStateChance = true;
	}
	
	inline void setPostureDownChance (int chance) {
		postureDownStateChance = chance;
		hasStateChance = true;
	}
	
	inline void setPostureUpChance (int chance) {
		postureUpStateChance = chance;
		hasStateChance = true;
	}

	inline void setDizzyChance(int chance) {
		dizzyStateChance = chance;
		hasStateChance = true;
	}

	inline void setBlindChance(int chance) {
		blindStateChance = chance;
		hasStateChance = true;
	}

	inline void setStunChance(int chance) {
		stunStateChance = chance;
		hasStateChance = true;
	}
	
	inline void setIntimidateChance(int chance) {
		intimidateStateChance = chance;
		hasStateChance = true;
	}
	
	inline void setAreaRangeDamage(int area) {
		areaRangeDamage = area;
	}
	
	void setCbtSpamBlock(const string& ename) {
		CbtSpamBlock = ename;
	}
	
	void setCbtSpamCounter(const string& ename) {
		CbtSpamCounter = ename;
	}

	void setCbtSpamEvade(const string& ename) {
		CbtSpamEvade = ename;
	}
	
	void setCbtSpamHit(const string& ename) {
		CbtSpamHit = ename;
	}
	
	void setCbtSpamMiss(const string& ename) {
		CbtSpamMiss = ename;
	}
	
	void setRequiredWeaponType(int wea) {
		requiredWeaponType = wea;
	}
	
	void setAccuracyBonus(int acc) {
		accuracyBonus = acc;
	}
	
	bool hasCbtSpamBlock() {
		return CbtSpamBlock.size() != 0;
	}
	
	bool hasCbtSpamCounter() {
		return CbtSpamCounter.size() != 0;
	}
	
	bool hasCbtSpamEvade() {
		return CbtSpamEvade.size() != 0;
	}
	
	bool hasCbtSpamHit() {
		return CbtSpamHit.size() != 0;
	}
	
	bool hasCbtSpamMiss() {
		return CbtSpamMiss.size() != 0;
	}
	
	inline string& getCbtSpamBlock() {
		return CbtSpamBlock;
	}
	
	inline string& getCbtSpamCounter() {
		return CbtSpamCounter;
	}
	
	inline string& getCbtSpamEvade() {
		return CbtSpamEvade;
	}
	
	inline string& getCbtSpamHit() {
		return CbtSpamHit;
	}
	
	inline string& getCbtSpamMiss() {
		return CbtSpamMiss;
	}
	
	inline int getAreaRange() {
		return areaRangeDamage;
	}
	
	int getRequiredWeaponType() {
		return requiredWeaponType;
	}

	friend class CombatManager;
	
};

#endif /*ATTACKTARGETSKILL_H_*/
