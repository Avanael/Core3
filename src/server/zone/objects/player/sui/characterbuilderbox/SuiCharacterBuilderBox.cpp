/*
 *	server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.cpp generated by engine3 IDL compiler 0.60
 */

#include "SuiCharacterBuilderBox.h"

#include "server/zone/objects/player/PlayerCreature.h"

/*
 *	SuiCharacterBuilderBoxStub
 */

enum {RPC_GENERATEMESSAGE__ = 6,RPC_ISCHARACTERBUILDERBOX__};

SuiCharacterBuilderBox::SuiCharacterBuilderBox(PlayerCreature* player, CharacterBuilderMenuNode* root) : SuiListBox(DummyConstructorParameter::instance()) {
	SuiCharacterBuilderBoxImplementation* _implementation = new SuiCharacterBuilderBoxImplementation(player, root);
	_impl = _implementation;
	_impl->_setStub(this);
}

SuiCharacterBuilderBox::SuiCharacterBuilderBox(DummyConstructorParameter* param) : SuiListBox(param) {
}

SuiCharacterBuilderBox::~SuiCharacterBuilderBox() {
}


BaseMessage* SuiCharacterBuilderBox::generateMessage() {
	SuiCharacterBuilderBoxImplementation* _implementation = (SuiCharacterBuilderBoxImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_GENERATEMESSAGE__);

		return (BaseMessage*) method.executeWithObjectReturn();
	} else
		return _implementation->generateMessage();
}

CharacterBuilderMenuNode* SuiCharacterBuilderBox::getCurrentNode() {
	SuiCharacterBuilderBoxImplementation* _implementation = (SuiCharacterBuilderBoxImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return _implementation->getCurrentNode();
}

void SuiCharacterBuilderBox::setCurrentNode(CharacterBuilderMenuNode* node) {
	SuiCharacterBuilderBoxImplementation* _implementation = (SuiCharacterBuilderBoxImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		_implementation->setCurrentNode(node);
}

bool SuiCharacterBuilderBox::isCharacterBuilderBox() {
	SuiCharacterBuilderBoxImplementation* _implementation = (SuiCharacterBuilderBoxImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_ISCHARACTERBUILDERBOX__);

		return method.executeWithBooleanReturn();
	} else
		return _implementation->isCharacterBuilderBox();
}

DistributedObjectServant* SuiCharacterBuilderBox::_getImplementation() {

	_updated = true;
	return _impl;
}

void SuiCharacterBuilderBox::_setImplementation(DistributedObjectServant* servant) {
	_impl = servant;
}

/*
 *	SuiCharacterBuilderBoxImplementation
 */

SuiCharacterBuilderBoxImplementation::SuiCharacterBuilderBoxImplementation(DummyConstructorParameter* param) : SuiListBoxImplementation(param) {
	_initializeImplementation();
}


SuiCharacterBuilderBoxImplementation::~SuiCharacterBuilderBoxImplementation() {
}


void SuiCharacterBuilderBoxImplementation::finalize() {
}

void SuiCharacterBuilderBoxImplementation::_initializeImplementation() {
	_setClassHelper(SuiCharacterBuilderBoxHelper::instance());

	_serializationHelperMethod();
	_serializationHelperMethod();
}

void SuiCharacterBuilderBoxImplementation::_setStub(DistributedObjectStub* stub) {
	_this = (SuiCharacterBuilderBox*) stub;
	SuiListBoxImplementation::_setStub(stub);
}

DistributedObjectStub* SuiCharacterBuilderBoxImplementation::_getStub() {
	return _this;
}

SuiCharacterBuilderBoxImplementation::operator const SuiCharacterBuilderBox*() {
	return _this;
}

void SuiCharacterBuilderBoxImplementation::lock(bool doLock) {
	_this->lock(doLock);
}

void SuiCharacterBuilderBoxImplementation::lock(ManagedObject* obj) {
	_this->lock(obj);
}

void SuiCharacterBuilderBoxImplementation::rlock(bool doLock) {
	_this->rlock(doLock);
}

void SuiCharacterBuilderBoxImplementation::wlock(bool doLock) {
	_this->wlock(doLock);
}

void SuiCharacterBuilderBoxImplementation::wlock(ManagedObject* obj) {
	_this->wlock(obj);
}

void SuiCharacterBuilderBoxImplementation::unlock(bool doLock) {
	_this->unlock(doLock);
}

void SuiCharacterBuilderBoxImplementation::runlock(bool doLock) {
	_this->runlock(doLock);
}

void SuiCharacterBuilderBoxImplementation::_serializationHelperMethod() {
	SuiListBoxImplementation::_serializationHelperMethod();

	_setClassName("SuiCharacterBuilderBox");

}

void SuiCharacterBuilderBoxImplementation::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);

		uint16 _varSize = stream->readShort();

		int _currentOffset = stream->getOffset();

		if(SuiCharacterBuilderBoxImplementation::readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	initializeTransientMembers();
}

bool SuiCharacterBuilderBoxImplementation::readObjectMember(ObjectInputStream* stream, const String& _name) {
	if (SuiListBoxImplementation::readObjectMember(stream, _name))
		return true;


	return false;
}

void SuiCharacterBuilderBoxImplementation::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = SuiCharacterBuilderBoxImplementation::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int SuiCharacterBuilderBoxImplementation::writeObjectMembers(ObjectOutputStream* stream) {
	String _name;
	int _offset;
	uint16 _totalSize;

	return 0 + SuiListBoxImplementation::writeObjectMembers(stream);
}

SuiCharacterBuilderBoxImplementation::SuiCharacterBuilderBoxImplementation(PlayerCreature* player, CharacterBuilderMenuNode* root) : SuiListBoxImplementation(player, SuiWindowType::CHARACTER_BUILDER_LIST, 0) {
	_initializeImplementation();
	// server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.idl():  		Logger.setLoggingName("SuiCharacterBuilderBox");
	Logger::setLoggingName("SuiCharacterBuilderBox");
	// server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.idl():  		setPromptTitle("Character Builder");
	setPromptTitle("Character Builder");
	// server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.idl():  		setPromptText("Provided below are items which the developers feel are necessary to complete the current testing objectives. Please select only the items which you require.");
	setPromptText("Provided below are items which the developers feel are necessary to complete the current testing objectives. Please select only the items which you require.");
	// server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.idl():  		rootNode = root;
	rootNode = root;
	// server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.idl():  		currentNode = root;
	currentNode = root;
}

bool SuiCharacterBuilderBoxImplementation::isCharacterBuilderBox() {
	// server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.idl():  		return true;
	return true;
}

/*
 *	SuiCharacterBuilderBoxAdapter
 */

SuiCharacterBuilderBoxAdapter::SuiCharacterBuilderBoxAdapter(SuiCharacterBuilderBoxImplementation* obj) : SuiListBoxAdapter(obj) {
}

Packet* SuiCharacterBuilderBoxAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case RPC_GENERATEMESSAGE__:
		resp->insertLong(generateMessage()->_getObjectID());
		break;
	case RPC_ISCHARACTERBUILDERBOX__:
		resp->insertBoolean(isCharacterBuilderBox());
		break;
	default:
		return NULL;
	}

	return resp;
}

BaseMessage* SuiCharacterBuilderBoxAdapter::generateMessage() {
	return ((SuiCharacterBuilderBoxImplementation*) impl)->generateMessage();
}

bool SuiCharacterBuilderBoxAdapter::isCharacterBuilderBox() {
	return ((SuiCharacterBuilderBoxImplementation*) impl)->isCharacterBuilderBox();
}

/*
 *	SuiCharacterBuilderBoxHelper
 */

SuiCharacterBuilderBoxHelper* SuiCharacterBuilderBoxHelper::staticInitializer = SuiCharacterBuilderBoxHelper::instance();

SuiCharacterBuilderBoxHelper::SuiCharacterBuilderBoxHelper() {
	className = "SuiCharacterBuilderBox";

	Core::getObjectBroker()->registerClass(className, this);
}

void SuiCharacterBuilderBoxHelper::finalizeHelper() {
	SuiCharacterBuilderBoxHelper::finalize();
}

DistributedObject* SuiCharacterBuilderBoxHelper::instantiateObject() {
	return new SuiCharacterBuilderBox(DummyConstructorParameter::instance());
}

DistributedObjectServant* SuiCharacterBuilderBoxHelper::instantiateServant() {
	return new SuiCharacterBuilderBoxImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* SuiCharacterBuilderBoxHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new SuiCharacterBuilderBoxAdapter((SuiCharacterBuilderBoxImplementation*) obj->_getImplementation());

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

