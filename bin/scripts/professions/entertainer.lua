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


---------------------Male Humanoid Items------------------------------------
mshoes = {
	owner = "",

	objectName = "Dress Shoes",

	templateName = "shoes_s01",

	objectCRC = "3549441025",

	objectType = FOOTWEAR,

	equipped = "1"
}

mpants = {
	owner = "",

	objectName = "Striped Slacks",

	templateName = "pants_s08",

	objectCRC = "597357025",

	objectType = PANTS,

	equipped = "1"
}

mshirt = {
	owner = "",

	objectName = "Muscle Shirt",

	templateName = "shirt_s42",

	objectCRC = "1500804767",

	objectType = SHIRT,

	equipped = "1"
}

entertainer_humanoid_male_items = {mshoes, mpants, mshirt}

--------------------------Female Humanoid Items---------------------------

fshoes = {
	owner = "",

	objectName = "Dress Slippers",

	templateName = "shoes_s09",

	objectCRC = "2457414407",

	objectType = FOOTWEAR,

	equipped = "1"
}

fshirt = {
	owner = "",

	objectName = "Flex-form Shirt",

	templateName = "shirt_s38",

	objectCRC = "3412040939",

	objectType = SHIRT,

	equipped = "1"
}

fpants = {
	owner = "",

	objectName = "Desert Crawlers",

	templateName = "pants_s11",

	objectCRC = "810982418",

	objectType = PANTS,

	equipped = "1"
}

entertainer_humanoid_female_items = {fshoes, fshirt, fpants}

--------------------------Male Trandoshan Items---------------------------

entertainer_trandoshan_male_items = {mpants, mshirt}

--------------------------Female Trandoshan Items------------------------

entertainer_trandoshan_female_items = {fshirt, fpants}

--------------------------Male Ithorian Items---------------------------

mishirt = {
	owner = "",

	objectName = "Ithorian Knitted Shirt",

	templateName = "ith_shirt_s03",

	objectCRC = "3897341225",

	objectType = ITHOGARB,

	equipped = "1"
}

mipants = {
	owner = "",

	objectName = "Ithorian Baggies",

	templateName = "ith_pants_s08",

	objectCRC = "1270489349",

	objectType = ITHOGARB,

	equipped = "1"
}

entertainer_ithorian_male_items = {mipants, mishirt}

--------------------------Female Ithorian Items---------------------------

fipants = {
	owner = "",

	objectName = "Ithorian Buckle Pants",

	templateName = "ith_pants_s10",

	objectCRC = "293284731",

	objectType = ITHOGARB,

	equipped = "1"
}

fishirt = {
	owner = "",

	objectName = "Ithorian Fade Dyed Shirt",

	templateName = "ith_shirt_s09",

	objectCRC = "1002405173",

	objectType = ITHOGARB,

	equipped = "1"
}

entertainer_ithorian_female_items = {fipants, fishirt}

entertainer_wookie_male_items = { }
entertainer_wookie_female_items = { }

-------------------Entertainer Items (All Species)--------------------

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

surv_knife = {
	owner = "",

	objectName = "Survival Knife",

	templateName = "object/weapon/melee/knife/shared_knife_survival.iff",

	objectCRC = 530531036,

	objectType = ONEHANDMELEEWEAPON,

	damageType = WEAPON_KINETIC,

	armorPiercing = WEAPON_NONE,
	
	certification = "",

	equipped = "0"
}

shorn = {
	owner = "",

	objectName = "a Slitherhorn",

	templateName = "obj_slitherhorn",

	objectCRC = "3533891079",

	objectType = INSTRUMENT,

	instrumentType = INSTR_SLITHERHORN,

	equipped = "0"
}

general_entertainer_items = {cdef_pistol, surv_knife, shorn}

itemContainer = {
	humanoid_male_items = entertainer_humanoid_male_items,
	humanoid_female_items = entertainer_humanoid_female_items,
	tran_male_items = entertainer_trandoshan_male_items,
	tran_female_items = entertainer_trandoshan_female_items,
	itho_male_items = entertainer_ithorian_male_items,
	itho_female_items = entertainer_ithorian_female_items,
	wook_male_items = entertainer_wookie_male_items,
	wook_female_items = entertainer_wookie_female_items,
	global_class_items = general_entertainer_items
}

addToItemMap("entertainer", itemContainer)