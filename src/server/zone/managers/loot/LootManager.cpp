/*
 *	server/zone/managers/loot/LootManager.cpp generated by engine3 IDL compiler 0.60
 */

#include "LootManager.h"

#include "server/zone/Zone.h"

#include "server/zone/objects/scene/SceneObject.h"

#include "server/zone/objects/player/PlayerCreature.h"

#include "server/zone/managers/crafting/CraftingManager.h"

#include "server/zone/managers/loot/lootgroup/LootGroupObject.h"

#include "server/zone/managers/loot/lootgroup/LootObject.h"

/*
 *	LootManagerStub
 */

enum {RPC_INITIALIZE__ = 6,RPC_CONTAINS__INT_,RPC_CREATELOOT__PLAYERCREATURE_SCENEOBJECT_INT_INT_INT_,RPC_TESTLOOT__PLAYERCREATURE_SCENEOBJECT_};

LootManager::LootManager(CraftingManager* craftman) : ZoneManager(DummyConstructorParameter::instance()) {
	LootManagerImplementation* _implementation = new LootManagerImplementation(craftman);
	_impl = _implementation;
	_impl->_setStub(this);
}

LootManager::LootManager(DummyConstructorParameter* param) : ZoneManager(param) {
}

LootManager::~LootManager() {
}


void LootManager::initialize() {
	LootManagerImplementation* _implementation = (LootManagerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_INITIALIZE__);

		method.executeWithVoidReturn();
	} else
		_implementation->initialize();
}

bool LootManager::contains(unsigned int lootGroup) {
	LootManagerImplementation* _implementation = (LootManagerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_CONTAINS__INT_);
		method.addUnsignedIntParameter(lootGroup);

		return method.executeWithBooleanReturn();
	} else
		return _implementation->contains(lootGroup);
}

void LootManager::createLoot(PlayerCreature* receiver, SceneObject* container, int level, unsigned int lootGroup, int objectCount) {
	LootManagerImplementation* _implementation = (LootManagerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_CREATELOOT__PLAYERCREATURE_SCENEOBJECT_INT_INT_INT_);
		method.addObjectParameter(receiver);
		method.addObjectParameter(container);
		method.addSignedIntParameter(level);
		method.addUnsignedIntParameter(lootGroup);
		method.addSignedIntParameter(objectCount);

		method.executeWithVoidReturn();
	} else
		_implementation->createLoot(receiver, container, level, lootGroup, objectCount);
}

void LootManager::createLoot(PlayerCreature* receiver, SceneObject* container, int level, Vector<unsigned int>* lootGroup) {
	LootManagerImplementation* _implementation = (LootManagerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		_implementation->createLoot(receiver, container, level, lootGroup);
}

void LootManager::testLoot(PlayerCreature* receiver, SceneObject* container) {
	LootManagerImplementation* _implementation = (LootManagerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_TESTLOOT__PLAYERCREATURE_SCENEOBJECT_);
		method.addObjectParameter(receiver);
		method.addObjectParameter(container);

		method.executeWithVoidReturn();
	} else
		_implementation->testLoot(receiver, container);
}

DistributedObjectServant* LootManager::_getImplementation() {

	_updated = true;
	return _impl;
}

void LootManager::_setImplementation(DistributedObjectServant* servant) {
	_impl = servant;
}

/*
 *	LootManagerImplementation
 */

LootManagerImplementation::LootManagerImplementation(DummyConstructorParameter* param) : ZoneManagerImplementation(param) {
	_initializeImplementation();
}


LootManagerImplementation::~LootManagerImplementation() {
}


void LootManagerImplementation::finalize() {
}

void LootManagerImplementation::_initializeImplementation() {
	_setClassHelper(LootManagerHelper::instance());

	_serializationHelperMethod();
	_serializationHelperMethod();
}

void LootManagerImplementation::_setStub(DistributedObjectStub* stub) {
	_this = (LootManager*) stub;
	ZoneManagerImplementation::_setStub(stub);
}

DistributedObjectStub* LootManagerImplementation::_getStub() {
	return _this;
}

LootManagerImplementation::operator const LootManager*() {
	return _this;
}

void LootManagerImplementation::lock(bool doLock) {
	_this->lock(doLock);
}

void LootManagerImplementation::lock(ManagedObject* obj) {
	_this->lock(obj);
}

void LootManagerImplementation::rlock(bool doLock) {
	_this->rlock(doLock);
}

void LootManagerImplementation::wlock(bool doLock) {
	_this->wlock(doLock);
}

void LootManagerImplementation::wlock(ManagedObject* obj) {
	_this->wlock(obj);
}

void LootManagerImplementation::unlock(bool doLock) {
	_this->unlock(doLock);
}

void LootManagerImplementation::runlock(bool doLock) {
	_this->runlock(doLock);
}

void LootManagerImplementation::_serializationHelperMethod() {
	ZoneManagerImplementation::_serializationHelperMethod();

	_setClassName("LootManager");

}

void LootManagerImplementation::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);

		uint16 _varSize = stream->readShort();

		int _currentOffset = stream->getOffset();

		if(LootManagerImplementation::readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	initializeTransientMembers();
}

bool LootManagerImplementation::readObjectMember(ObjectInputStream* stream, const String& _name) {
	if (ZoneManagerImplementation::readObjectMember(stream, _name))
		return true;

	if (_name == "lootGroups") {
		TypeInfo<VectorMap<unsigned int, ManagedReference<LootGroupObject* > > >::parseFromBinaryStream(&lootGroups, stream);
		return true;
	}


	return false;
}

void LootManagerImplementation::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = LootManagerImplementation::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int LootManagerImplementation::writeObjectMembers(ObjectOutputStream* stream) {
	String _name;
	int _offset;
	uint16 _totalSize;
	_name = "lootGroups";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<VectorMap<unsigned int, ManagedReference<LootGroupObject* > > >::toBinaryStream(&lootGroups, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);


	return 1 + ZoneManagerImplementation::writeObjectMembers(stream);
}

LootManagerImplementation::LootManagerImplementation(CraftingManager* craftman) : ZoneManagerImplementation("LootManager") {
	_initializeImplementation();
	// server/zone/managers/loot/LootManager.idl():  		lootGroups.setNullValue(null);
	(&lootGroups)->setNullValue(NULL);
	// server/zone/managers/loot/LootManager.idl():  		lootGroups.setNoDuplicateInsertPlan();
	(&lootGroups)->setNoDuplicateInsertPlan();
	// server/zone/managers/loot/LootManager.idl():  		craftingManager = craftman;
	craftingManager = craftman;
}

bool LootManagerImplementation::contains(unsigned int lootGroup) {
	// server/zone/managers/loot/LootManager.idl():  		return (lootGroups.contains(lootGroup));
	return ((&lootGroups)->contains(lootGroup));
}

/*
 *	LootManagerAdapter
 */

LootManagerAdapter::LootManagerAdapter(LootManagerImplementation* obj) : ZoneManagerAdapter(obj) {
}

Packet* LootManagerAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case RPC_INITIALIZE__:
		initialize();
		break;
	case RPC_CONTAINS__INT_:
		resp->insertBoolean(contains(inv->getUnsignedIntParameter()));
		break;
	case RPC_CREATELOOT__PLAYERCREATURE_SCENEOBJECT_INT_INT_INT_:
		createLoot((PlayerCreature*) inv->getObjectParameter(), (SceneObject*) inv->getObjectParameter(), inv->getSignedIntParameter(), inv->getUnsignedIntParameter(), inv->getSignedIntParameter());
		break;
	case RPC_TESTLOOT__PLAYERCREATURE_SCENEOBJECT_:
		testLoot((PlayerCreature*) inv->getObjectParameter(), (SceneObject*) inv->getObjectParameter());
		break;
	default:
		return NULL;
	}

	return resp;
}

void LootManagerAdapter::initialize() {
	((LootManagerImplementation*) impl)->initialize();
}

bool LootManagerAdapter::contains(unsigned int lootGroup) {
	return ((LootManagerImplementation*) impl)->contains(lootGroup);
}

void LootManagerAdapter::createLoot(PlayerCreature* receiver, SceneObject* container, int level, unsigned int lootGroup, int objectCount) {
	((LootManagerImplementation*) impl)->createLoot(receiver, container, level, lootGroup, objectCount);
}

void LootManagerAdapter::testLoot(PlayerCreature* receiver, SceneObject* container) {
	((LootManagerImplementation*) impl)->testLoot(receiver, container);
}

/*
 *	LootManagerHelper
 */

LootManagerHelper* LootManagerHelper::staticInitializer = LootManagerHelper::instance();

LootManagerHelper::LootManagerHelper() {
	className = "LootManager";

	Core::getObjectBroker()->registerClass(className, this);
}

void LootManagerHelper::finalizeHelper() {
	LootManagerHelper::finalize();
}

DistributedObject* LootManagerHelper::instantiateObject() {
	return new LootManager(DummyConstructorParameter::instance());
}

DistributedObjectServant* LootManagerHelper::instantiateServant() {
	return new LootManagerImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* LootManagerHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new LootManagerAdapter((LootManagerImplementation*) obj->_getImplementation());

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

