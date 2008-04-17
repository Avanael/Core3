--Copyright (C) 2007 <SWGEmu>
 
--This File is part of Core3.
 
--This program is free software; you can redistribute 
--it and/or modify it under the terms of the GNU Lesser 
--General Public License as published by the Free Software
--Foundation; either version 2 of the License, 
--or (at your option) any later version.
 
--This program is distributed in the hope that it will be useful, 
--but WITHOUT ANY WARRANTY; without even the implied warranty of 
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
--See the GNU Lesser General Public License for
--more details.
 
--You should have received a copy of the GNU Lesser General 
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
--Linking Engine3 statically or dynamically with other modules 
--is making a combined work based on Engine3. 
--Thus, the terms and conditions of the GNU Lesser General Public License 
--cover the whole combination.
 
--In addition, as a special exception, the copyright holders of Engine3 
--give you permission to combine Engine3 program with free software 
--programs or libraries that are released under the GNU LGPL and with 
--code included in the standard release of Core3 under the GNU LGPL 
--license (or modified versions of such code, with unchanged license). 
--You may copy and distribute such a system following the terms of the 
--GNU LGPL for Engine3 and the licenses of the other code concerned, 
--provided that you include the source code of that other code when 
--and as the GNU LGPL requires distribution of source code.
 
--Note that people who make modified versions of Engine3 are not obligated 
--to grant this special exception for their modified versions; 
--it is their choice whether to do so. The GNU Lesser General Public License 
--gives permission to release a modified version without this exception; 
--this exception also makes it possible to release a modified version 
--which carries forward this exception.


-------------------Male Humanoid Items------------------------------------
mboots = {
	owner = "",

	objectName = "Paneled Boots",

	templateName = "boots_s21",

	objectCRC = "3589494086",

	objectType = FOOTWEAR,

	equipped = "1"
}

mjacket = {
	owner = "",

	objectName = "Padded Jacket",

	templateName = "jacket_s05",

	objectCRC = "3072681244",

	objectType = JACKET,

	equipped = "1"
}

mpants = {
	owner = "",

	objectName = "Pocketed Work Pants",

	templateName = "pants_s04",

	objectCRC = "1116173668",

	objectType = PANTS,

	equipped = "1"
}

marksman_humanoid_male_items = {mboots, mjacket, mpants}

--------------------------Female Humanoid Items---------------------------

fshoes = {
	owner = "",

	objectName = "Casual Shoes",

	templateName = "shoes_s02",

	objectCRC = "143099030",

	objectType = FOOTWEAR,

	equipped = "1"
}

fshirt = {
	owner = "",

	objectName = "Sports Wrap",

	templateName = "shirt_s24",

	objectCRC = "2976519446",

	objectType = SHIRT,

	equipped = "1"
}

fpants = {
	owner = "",

	objectName = "Pantaloons",

	templateName = "pants_s24",

	objectCRC = "1960275860",

	objectType = PANTS,

	equipped = "1"
}

fvest = {
	owner = "",

	objectName = "Mangy Vest",

	templateName = "vest_s10",

	objectCRC = "1655790437",

	objectType = VEST,

	equipped = "1"
}

marksman_humanoid_female_items = {fshoes, fshirt, fpants, fvest}

--------------------------Male Trandoshan Items---------------------------

marksman_trandoshan_male_items = {mpants, mjacket}

--------------------------Female Trandoshan Items------------------------

marksman_trandoshan_female_items = {fshirt, fpants, fvest}

--------------------------Male Ithorian Items---------------------------

mijacket = {
	owner = "",

	objectName = "Ithorian Cargo Jacket",

	templateName = "ith_jacket_s02",

	objectCRC = "274309091",

	objectType = ITHOGARB,

	equipped = "1"
}

mipants = {
	owner = "",

	objectName = "Ithorian Camos",

	templateName = "ith_pants_s05",

	objectCRC = "1672135181",

	objectType = ITHOGARB,

	equipped = "1"
}

mishirt = {
	owner = "",

	objectName = "Ithorian Tight Fit Shirt",

	templateName = "ith_shirt_s12",

	objectCRC = "3127500764",

	objectType = ITHOGARB,

	equipped = "1"
}

marksman_ithorian_male_items = {mijacket, mipants, mishirt}

--------------------------Female Ithorian Items---------------------------

marksman_ithorian_female_items = {mipants, mishirt}

marksman_wookie_male_items = { }
marksman_wookie_female_items = { }

----------------------Marksman Items (All Species)------------------------

cdef_pistol = {
	owner = "",

	objectName = "CDEF Pistol",

	templateName = "object/weapon/ranged/pistol/shared_pistol_cdef.iff",

	objectCRC = 937103853,

	objectType = PISTOL,

	damageType = WEAPON_ENERGY,

	armorPiercing = WEAPON_NONE,
	
	certification = "",

	equipped = "0"
}

cdef_carbine = {
	owner = "",

	objectName = "CDEF Carbine",

	templateName = "object/weapon/ranged/carbine/shared_carbine_cdef.iff",

	objectCRC = 583942574,

	objectType = CARBINE,

	damageType = WEAPON_ENERGY,

	armorPiercing = WEAPON_NONE,
	
	certification = "",

	equipped = "0"
}

cdef_rifle = {
	owner = "",

	objectName = "CDEF Rifle",

	templateName = "object/weapon/ranged/rifle/shared_rifle_cdef.iff",

	objectCRC = 3496137221,

	objectType = RIFLE,

	damageType = WEAPON_ENERGY,

	armorPiercing = WEAPON_NONE,
	
	certification = "",

	equipped = "0"
}

general_marksman_items = {cdef_pistol, cdef_carbine, cdef_rifle}

itemContainer = {
	humanoid_male_items = marksman_humanoid_male_items,
	humanoid_female_items = marksman_humanoid_female_items,
	tran_male_items = marksman_trandoshan_male_items,
	tran_female_items = marksman_trandoshan_female_items,
	itho_male_items = marksman_ithorian_male_items,
	itho_female_items = marksman_ithorian_female_items,
	wook_male_items = marksman_wookie_male_items,
	wook_female_items = marksman_wookie_female_items,
	global_class_items = general_marksman_items
}

addToItemMap("marksman", itemContainer)