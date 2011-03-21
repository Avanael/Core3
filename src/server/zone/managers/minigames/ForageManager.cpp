/*
 *	server/zone/managers/minigames/ForageManager.cpp generated by engine3 IDL compiler 0.60
 */

#include "ForageManager.h"

#include "server/zone/objects/player/PlayerCreature.h"

#include "server/zone/Zone.h"

#include "server/zone/ZoneServer.h"

/*
 *	ForageManagerStub
 */

enum {RPC_DELETEFORAGEAREACOLLECTION__STRING_ = 6,RPC_STARTFORAGING__PLAYERCREATURE_BOOL_,RPC_FINISHFORAGING__PLAYERCREATURE_BOOL_FLOAT_FLOAT_INT_,RPC_FORAGEGIVEITEMS__PLAYERCREATURE_BOOL_FLOAT_FLOAT_INT_,RPC_FORAGEGIVERESOURCE__PLAYERCREATURE_FLOAT_FLOAT_INT_};

ForageManager::ForageManager(ZoneServer* server) : Observer(DummyConstructorParameter::instance()) {
	ForageManagerImplementation* _implementation = new ForageManagerImplementation(server);
	_impl = _implementation;
	_impl->_setStub(this);
}

ForageManager::ForageManager(DummyConstructorParameter* param) : Observer(param) {
}

ForageManager::~ForageManager() {
}


void ForageManager::deleteForageAreaCollection(String& playerName) {
	ForageManagerImplementation* _implementation = (ForageManagerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_DELETEFORAGEAREACOLLECTION__STRING_);
		method.addAsciiParameter(playerName);

		method.executeWithVoidReturn();
	} else
		_implementation->deleteForageAreaCollection(playerName);
}

void ForageManager::startForaging(PlayerCreature* player, bool scoutForage) {
	ForageManagerImplementation* _implementation = (ForageManagerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_STARTFORAGING__PLAYERCREATURE_BOOL_);
		method.addObjectParameter(player);
		method.addBooleanParameter(scoutForage);

		method.executeWithVoidReturn();
	} else
		_implementation->startForaging(player, scoutForage);
}

void ForageManager::finishForaging(PlayerCreature* player, bool scoutForage, float forageX, float forageY, int planet) {
	ForageManagerImplementation* _implementation = (ForageManagerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_FINISHFORAGING__PLAYERCREATURE_BOOL_FLOAT_FLOAT_INT_);
		method.addObjectParameter(player);
		method.addBooleanParameter(scoutForage);
		method.addFloatParameter(forageX);
		method.addFloatParameter(forageY);
		method.addSignedIntParameter(planet);

		method.executeWithVoidReturn();
	} else
		_implementation->finishForaging(player, scoutForage, forageX, forageY, planet);
}

void ForageManager::forageGiveItems(PlayerCreature* player, bool scoutForage, float forageX, float forageY, int planet) {
	ForageManagerImplementation* _implementation = (ForageManagerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_FORAGEGIVEITEMS__PLAYERCREATURE_BOOL_FLOAT_FLOAT_INT_);
		method.addObjectParameter(player);
		method.addBooleanParameter(scoutForage);
		method.addFloatParameter(forageX);
		method.addFloatParameter(forageY);
		method.addSignedIntParameter(planet);

		method.executeWithVoidReturn();
	} else
		_implementation->forageGiveItems(player, scoutForage, forageX, forageY, planet);
}

void ForageManager::forageGiveResource(PlayerCreature* player, float forageX, float forageY, int planet) {
	ForageManagerImplementation* _implementation = (ForageManagerImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_FORAGEGIVERESOURCE__PLAYERCREATURE_FLOAT_FLOAT_INT_);
		method.addObjectParameter(player);
		method.addFloatParameter(forageX);
		method.addFloatParameter(forageY);
		method.addSignedIntParameter(planet);

		method.executeWithVoidReturn();
	} else
		_implementation->forageGiveResource(player, forageX, forageY, planet);
}

DistributedObjectServant* ForageManager::_getImplementation() {

	_updated = true;
	return _impl;
}

void ForageManager::_setImplementation(DistributedObjectServant* servant) {
	_impl = servant;
}

/*
 *	ForageManagerImplementation
 */

ForageManagerImplementation::ForageManagerImplementation(DummyConstructorParameter* param) : ObserverImplementation(param) {
	_initializeImplementation();
}


ForageManagerImplementation::~ForageManagerImplementation() {
}


void ForageManagerImplementation::finalize() {
}

void ForageManagerImplementation::_initializeImplementation() {
	_setClassHelper(ForageManagerHelper::instance());

	_serializationHelperMethod();
	_serializationHelperMethod();
}

void ForageManagerImplementation::_setStub(DistributedObjectStub* stub) {
	_this = (ForageManager*) stub;
	ObserverImplementation::_setStub(stub);
}

DistributedObjectStub* ForageManagerImplementation::_getStub() {
	return _this;
}

ForageManagerImplementation::operator const ForageManager*() {
	return _this;
}

void ForageManagerImplementation::lock(bool doLock) {
	_this->lock(doLock);
}

void ForageManagerImplementation::lock(ManagedObject* obj) {
	_this->lock(obj);
}

void ForageManagerImplementation::rlock(bool doLock) {
	_this->rlock(doLock);
}

void ForageManagerImplementation::wlock(bool doLock) {
	_this->wlock(doLock);
}

void ForageManagerImplementation::wlock(ManagedObject* obj) {
	_this->wlock(obj);
}

void ForageManagerImplementation::unlock(bool doLock) {
	_this->unlock(doLock);
}

void ForageManagerImplementation::runlock(bool doLock) {
	_this->runlock(doLock);
}

void ForageManagerImplementation::_serializationHelperMethod() {
	ObserverImplementation::_serializationHelperMethod();

	_setClassName("ForageManager");

}

void ForageManagerImplementation::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);

		uint16 _varSize = stream->readShort();

		int _currentOffset = stream->getOffset();

		if(ForageManagerImplementation::readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	initializeTransientMembers();
}

bool ForageManagerImplementation::readObjectMember(ObjectInputStream* stream, const String& _name) {
	if (ObserverImplementation::readObjectMember(stream, _name))
		return true;

	if (_name == "zoneServer") {
		TypeInfo<ManagedWeakReference<ZoneServer* > >::parseFromBinaryStream(&zoneServer, stream);
		return true;
	}

	if (_name == "forageAreas") {
		TypeInfo<ForageMap >::parseFromBinaryStream(&forageAreas, stream);
		return true;
	}


	return false;
}

void ForageManagerImplementation::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = ForageManagerImplementation::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int ForageManagerImplementation::writeObjectMembers(ObjectOutputStream* stream) {
	String _name;
	int _offset;
	uint16 _totalSize;
	_name = "zoneServer";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<ManagedWeakReference<ZoneServer* > >::toBinaryStream(&zoneServer, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "forageAreas";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<ForageMap >::toBinaryStream(&forageAreas, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);


	return 2 + ObserverImplementation::writeObjectMembers(stream);
}

ForageManagerImplementation::ForageManagerImplementation(ZoneServer* server) {
	_initializeImplementation();
	// server/zone/managers/minigames/ForageManager.idl():  		zoneServer = server;
	zoneServer = server;
	// server/zone/managers/minigames/ForageManager.idl():  		Logger.setLoggingName("ForageManager");
	Logger::setLoggingName("ForageManager");
	// server/zone/managers/minigames/ForageManager.idl():  		Logger.setLogging(true);
	Logger::setLogging(true);
	// server/zone/managers/minigames/ForageManager.idl():  		forageAreas.setNullValue(null);
	(&forageAreas)->setNullValue(NULL);
}

void ForageManagerImplementation::deleteForageAreaCollection(String& playerName) {
	// server/zone/managers/minigames/ForageManager.idl():  		forageAreas.drop(playerName);
	(&forageAreas)->drop(playerName);
}

/*
 *	ForageManagerAdapter
 */

ForageManagerAdapter::ForageManagerAdapter(ForageManagerImplementation* obj) : ObserverAdapter(obj) {
}

Packet* ForageManagerAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case RPC_DELETEFORAGEAREACOLLECTION__STRING_:
		deleteForageAreaCollection(inv->getAsciiParameter(_param0_deleteForageAreaCollection__String_));
		break;
	case RPC_STARTFORAGING__PLAYERCREATURE_BOOL_:
		startForaging((PlayerCreature*) inv->getObjectParameter(), inv->getBooleanParameter());
		break;
	case RPC_FINISHFORAGING__PLAYERCREATURE_BOOL_FLOAT_FLOAT_INT_:
		finishForaging((PlayerCreature*) inv->getObjectParameter(), inv->getBooleanParameter(), inv->getFloatParameter(), inv->getFloatParameter(), inv->getSignedIntParameter());
		break;
	case RPC_FORAGEGIVEITEMS__PLAYERCREATURE_BOOL_FLOAT_FLOAT_INT_:
		forageGiveItems((PlayerCreature*) inv->getObjectParameter(), inv->getBooleanParameter(), inv->getFloatParameter(), inv->getFloatParameter(), inv->getSignedIntParameter());
		break;
	case RPC_FORAGEGIVERESOURCE__PLAYERCREATURE_FLOAT_FLOAT_INT_:
		forageGiveResource((PlayerCreature*) inv->getObjectParameter(), inv->getFloatParameter(), inv->getFloatParameter(), inv->getSignedIntParameter());
		break;
	default:
		return NULL;
	}

	return resp;
}

void ForageManagerAdapter::deleteForageAreaCollection(String& playerName) {
	((ForageManagerImplementation*) impl)->deleteForageAreaCollection(playerName);
}

void ForageManagerAdapter::startForaging(PlayerCreature* player, bool scoutForage) {
	((ForageManagerImplementation*) impl)->startForaging(player, scoutForage);
}

void ForageManagerAdapter::finishForaging(PlayerCreature* player, bool scoutForage, float forageX, float forageY, int planet) {
	((ForageManagerImplementation*) impl)->finishForaging(player, scoutForage, forageX, forageY, planet);
}

void ForageManagerAdapter::forageGiveItems(PlayerCreature* player, bool scoutForage, float forageX, float forageY, int planet) {
	((ForageManagerImplementation*) impl)->forageGiveItems(player, scoutForage, forageX, forageY, planet);
}

void ForageManagerAdapter::forageGiveResource(PlayerCreature* player, float forageX, float forageY, int planet) {
	((ForageManagerImplementation*) impl)->forageGiveResource(player, forageX, forageY, planet);
}

/*
 *	ForageManagerHelper
 */

ForageManagerHelper* ForageManagerHelper::staticInitializer = ForageManagerHelper::instance();

ForageManagerHelper::ForageManagerHelper() {
	className = "ForageManager";

	Core::getObjectBroker()->registerClass(className, this);
}

void ForageManagerHelper::finalizeHelper() {
	ForageManagerHelper::finalize();
}

DistributedObject* ForageManagerHelper::instantiateObject() {
	return new ForageManager(DummyConstructorParameter::instance());
}

DistributedObjectServant* ForageManagerHelper::instantiateServant() {
	return new ForageManagerImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* ForageManagerHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new ForageManagerAdapter((ForageManagerImplementation*) obj->_getImplementation());

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

