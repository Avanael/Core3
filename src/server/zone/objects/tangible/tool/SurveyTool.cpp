/*
 *	server/zone/objects/tangible/tool/SurveyTool.cpp generated by engine3 IDL compiler 0.60
 */

#include "SurveyTool.h"

#include "server/zone/objects/player/PlayerCreature.h"

#include "server/zone/packets/object/ObjectMenuResponse.h"

#include "server/zone/objects/scene/SceneObject.h"

#include "server/zone/Zone.h"

/*
 *	SurveyToolStub
 */

SurveyTool::SurveyTool() : ToolTangibleObject(DummyConstructorParameter::instance()) {
	_impl = new SurveyToolImplementation();
	_impl->_setStub(this);
}

SurveyTool::SurveyTool(DummyConstructorParameter* param) : ToolTangibleObject(param) {
}

SurveyTool::~SurveyTool() {
}


void SurveyTool::initializeTransientMembers() {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 6);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->initializeTransientMembers();
}

void SurveyTool::loadTemplateData(SharedObjectTemplate* templateData) {
	if (_impl == NULL) {
		throw ObjectNotLocalException(this);

	} else
		((SurveyToolImplementation*) _impl)->loadTemplateData(templateData);
}

void SurveyTool::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	if (_impl == NULL) {
		throw ObjectNotLocalException(this);

	} else
		((SurveyToolImplementation*) _impl)->fillObjectMenuResponse(menuResponse, player);
}

void SurveyTool::setRange(int r) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 7);
		method.addSignedIntParameter(r);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->setRange(r);
}

int SurveyTool::getRange() {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 8);

		return method.executeWithSignedIntReturn();
	} else
		return ((SurveyToolImplementation*) _impl)->getRange();
}

int SurveyTool::getPoints() {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 9);

		return method.executeWithSignedIntReturn();
	} else
		return ((SurveyToolImplementation*) _impl)->getPoints();
}

bool SurveyTool::canSampleRadioactive() {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 10);

		return method.executeWithBooleanReturn();
	} else
		return ((SurveyToolImplementation*) _impl)->canSampleRadioactive();
}

bool SurveyTool::tryGamble() {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 11);

		return method.executeWithBooleanReturn();
	} else
		return ((SurveyToolImplementation*) _impl)->tryGamble();
}

void SurveyTool::clearGamble() {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 12);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->clearGamble();
}

void SurveyTool::consentRadioactiveSample() {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 13);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->consentRadioactiveSample();
}

void SurveyTool::sendRadioactiveWarning(PlayerCreature* player) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 14);
		method.addObjectParameter(player);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->sendRadioactiveWarning(player);
}

void SurveyTool::sendRangeSui(PlayerCreature* player) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 15);
		method.addObjectParameter(player);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->sendRangeSui(player);
}

void SurveyTool::surveyCnodeMinigameSui(PlayerCreature* player) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 16);
		method.addObjectParameter(player);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->surveyCnodeMinigameSui(player);
}

void SurveyTool::surveyCnodeMinigame(PlayerCreature* player, int value) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 17);
		method.addObjectParameter(player);
		method.addSignedIntParameter(value);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->surveyCnodeMinigame(player, value);
}

Coordinate* SurveyTool::getRichSampleLocation() {
	if (_impl == NULL) {
		throw ObjectNotLocalException(this);

	} else
		return ((SurveyToolImplementation*) _impl)->getRichSampleLocation();
}

void SurveyTool::clearRichSampleLocation() {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 18);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->clearRichSampleLocation();
}

void SurveyTool::surveyGnodeMinigameSui(PlayerCreature* player) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 19);
		method.addObjectParameter(player);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->surveyGnodeMinigameSui(player);
}

void SurveyTool::surveyGnodeMinigame(PlayerCreature* player, int value) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 20);
		method.addObjectParameter(player);
		method.addSignedIntParameter(value);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->surveyGnodeMinigame(player, value);
}

int SurveyTool::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 21);
		method.addObjectParameter(player);
		method.addByteParameter(selectedID);

		return method.executeWithSignedIntReturn();
	} else
		return ((SurveyToolImplementation*) _impl)->handleObjectMenuSelect(player, selectedID);
}

void SurveyTool::sendResourceListTo(PlayerCreature* player) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 22);
		method.addObjectParameter(player);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->sendResourceListTo(player);
}

void SurveyTool::sendSurveyTo(PlayerCreature* player, const String& resname) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 23);
		method.addObjectParameter(player);
		method.addAsciiParameter(resname);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->sendSurveyTo(player, resname);
}

void SurveyTool::sendSampleTo(PlayerCreature* player, const String& resname) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 24);
		method.addObjectParameter(player);
		method.addAsciiParameter(resname);

		method.executeWithVoidReturn();
	} else
		((SurveyToolImplementation*) _impl)->sendSampleTo(player, resname);
}

/*
 *	SurveyToolImplementation
 */

SurveyToolImplementation::SurveyToolImplementation(DummyConstructorParameter* param) : ToolTangibleObjectImplementation(param) {
	_initializeImplementation();
}

SurveyToolImplementation::~SurveyToolImplementation() {
}


void SurveyToolImplementation::finalize() {
}

void SurveyToolImplementation::_initializeImplementation() {
	_setClassHelper(SurveyToolHelper::instance());

	_serializationHelperMethod();
}

void SurveyToolImplementation::_setStub(DistributedObjectStub* stub) {
	_this = (SurveyTool*) stub;
	ToolTangibleObjectImplementation::_setStub(stub);
}

DistributedObjectStub* SurveyToolImplementation::_getStub() {
	return _this;
}

SurveyToolImplementation::operator const SurveyTool*() {
	return _this;
}

void SurveyToolImplementation::lock(bool doLock) {
	_this->lock(doLock);
}

void SurveyToolImplementation::lock(ManagedObject* obj) {
	_this->lock(obj);
}

void SurveyToolImplementation::rlock(bool doLock) {
	_this->rlock(doLock);
}

void SurveyToolImplementation::wlock(bool doLock) {
	_this->wlock(doLock);
}

void SurveyToolImplementation::wlock(ManagedObject* obj) {
	_this->wlock(obj);
}

void SurveyToolImplementation::unlock(bool doLock) {
	_this->unlock(doLock);
}

void SurveyToolImplementation::runlock(bool doLock) {
	_this->runlock(doLock);
}

void SurveyToolImplementation::_serializationHelperMethod() {
	ToolTangibleObjectImplementation::_serializationHelperMethod();

	_setClassName("SurveyTool");

	addSerializableVariable("range", &range);
	addSerializableVariable("points", &points);
	addSerializableVariable("type", &type);
	addSerializableVariable("surveyType", &surveyType);
	addSerializableVariable("surveyAnimation", &surveyAnimation);
	addSerializableVariable("sampleAnimation", &sampleAnimation);
}

SurveyToolImplementation::SurveyToolImplementation() {
	_initializeImplementation();
	// server/zone/objects/tangible/tool/SurveyTool.idl(83):  		Logger.setLoggingName("SurveyTool");
	Logger::setLoggingName("SurveyTool");
	// server/zone/objects/tangible/tool/SurveyTool.idl(84):  		radioactiveOk = false;
	radioactiveOk = false;
	// server/zone/objects/tangible/tool/SurveyTool.idl(85):  		range = 0;
	range = 0;
	// server/zone/objects/tangible/tool/SurveyTool.idl(86):  		doGamble = false;
	doGamble = false;
	// server/zone/objects/tangible/tool/SurveyTool.idl(87):  		richSampleLocation = null;
	richSampleLocation = NULL;
}

void SurveyToolImplementation::initializeTransientMembers() {
	// server/zone/objects/tangible/tool/SurveyTool.idl(91):  		super.initializeTransientMembers();
	ToolTangibleObjectImplementation::initializeTransientMembers();
	// server/zone/objects/tangible/tool/SurveyTool.idl(93):  		Logger.setLoggingName("SurveyTool");
	Logger::setLoggingName("SurveyTool");
}

int SurveyToolImplementation::getRange() {
	// server/zone/objects/tangible/tool/SurveyTool.idl(110):  		return range;
	return range;
}

int SurveyToolImplementation::getPoints() {
	// server/zone/objects/tangible/tool/SurveyTool.idl(114):  		return points;
	return points;
}

bool SurveyToolImplementation::canSampleRadioactive() {
	// server/zone/objects/tangible/tool/SurveyTool.idl(118):  		return radioactiveOk;
	return radioactiveOk;
}

bool SurveyToolImplementation::tryGamble() {
	// server/zone/objects/tangible/tool/SurveyTool.idl(122):  		return doGamble == true;
	return doGamble == true;
}

void SurveyToolImplementation::clearGamble() {
	// server/zone/objects/tangible/tool/SurveyTool.idl(126):  		doGamble = false;
	doGamble = false;
}

void SurveyToolImplementation::consentRadioactiveSample() {
	// server/zone/objects/tangible/tool/SurveyTool.idl(130):  		radioactiveOk = true;
	radioactiveOk = true;
}

Coordinate* SurveyToolImplementation::getRichSampleLocation() {
	// server/zone/objects/tangible/tool/SurveyTool.idl(142):  		return richSampleLocation;
	return richSampleLocation;
}

void SurveyToolImplementation::clearRichSampleLocation() {
	// server/zone/objects/tangible/tool/SurveyTool.idl(146):  		richSampleLocation = null;
	richSampleLocation = NULL;
}

/*
 *	SurveyToolAdapter
 */

SurveyToolAdapter::SurveyToolAdapter(SurveyToolImplementation* obj) : ToolTangibleObjectAdapter(obj) {
}

Packet* SurveyToolAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case 6:
		initializeTransientMembers();
		break;
	case 7:
		setRange(inv->getSignedIntParameter());
		break;
	case 8:
		resp->insertSignedInt(getRange());
		break;
	case 9:
		resp->insertSignedInt(getPoints());
		break;
	case 10:
		resp->insertBoolean(canSampleRadioactive());
		break;
	case 11:
		resp->insertBoolean(tryGamble());
		break;
	case 12:
		clearGamble();
		break;
	case 13:
		consentRadioactiveSample();
		break;
	case 14:
		sendRadioactiveWarning((PlayerCreature*) inv->getObjectParameter());
		break;
	case 15:
		sendRangeSui((PlayerCreature*) inv->getObjectParameter());
		break;
	case 16:
		surveyCnodeMinigameSui((PlayerCreature*) inv->getObjectParameter());
		break;
	case 17:
		surveyCnodeMinigame((PlayerCreature*) inv->getObjectParameter(), inv->getSignedIntParameter());
		break;
	case 18:
		clearRichSampleLocation();
		break;
	case 19:
		surveyGnodeMinigameSui((PlayerCreature*) inv->getObjectParameter());
		break;
	case 20:
		surveyGnodeMinigame((PlayerCreature*) inv->getObjectParameter(), inv->getSignedIntParameter());
		break;
	case 21:
		resp->insertSignedInt(handleObjectMenuSelect((PlayerCreature*) inv->getObjectParameter(), inv->getByteParameter()));
		break;
	case 22:
		sendResourceListTo((PlayerCreature*) inv->getObjectParameter());
		break;
	case 23:
		sendSurveyTo((PlayerCreature*) inv->getObjectParameter(), inv->getAsciiParameter(_param1_sendSurveyTo__PlayerCreature_String_));
		break;
	case 24:
		sendSampleTo((PlayerCreature*) inv->getObjectParameter(), inv->getAsciiParameter(_param1_sendSampleTo__PlayerCreature_String_));
		break;
	default:
		return NULL;
	}

	return resp;
}

void SurveyToolAdapter::initializeTransientMembers() {
	((SurveyToolImplementation*) impl)->initializeTransientMembers();
}

void SurveyToolAdapter::setRange(int r) {
	((SurveyToolImplementation*) impl)->setRange(r);
}

int SurveyToolAdapter::getRange() {
	return ((SurveyToolImplementation*) impl)->getRange();
}

int SurveyToolAdapter::getPoints() {
	return ((SurveyToolImplementation*) impl)->getPoints();
}

bool SurveyToolAdapter::canSampleRadioactive() {
	return ((SurveyToolImplementation*) impl)->canSampleRadioactive();
}

bool SurveyToolAdapter::tryGamble() {
	return ((SurveyToolImplementation*) impl)->tryGamble();
}

void SurveyToolAdapter::clearGamble() {
	((SurveyToolImplementation*) impl)->clearGamble();
}

void SurveyToolAdapter::consentRadioactiveSample() {
	((SurveyToolImplementation*) impl)->consentRadioactiveSample();
}

void SurveyToolAdapter::sendRadioactiveWarning(PlayerCreature* player) {
	((SurveyToolImplementation*) impl)->sendRadioactiveWarning(player);
}

void SurveyToolAdapter::sendRangeSui(PlayerCreature* player) {
	((SurveyToolImplementation*) impl)->sendRangeSui(player);
}

void SurveyToolAdapter::surveyCnodeMinigameSui(PlayerCreature* player) {
	((SurveyToolImplementation*) impl)->surveyCnodeMinigameSui(player);
}

void SurveyToolAdapter::surveyCnodeMinigame(PlayerCreature* player, int value) {
	((SurveyToolImplementation*) impl)->surveyCnodeMinigame(player, value);
}

void SurveyToolAdapter::clearRichSampleLocation() {
	((SurveyToolImplementation*) impl)->clearRichSampleLocation();
}

void SurveyToolAdapter::surveyGnodeMinigameSui(PlayerCreature* player) {
	((SurveyToolImplementation*) impl)->surveyGnodeMinigameSui(player);
}

void SurveyToolAdapter::surveyGnodeMinigame(PlayerCreature* player, int value) {
	((SurveyToolImplementation*) impl)->surveyGnodeMinigame(player, value);
}

int SurveyToolAdapter::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	return ((SurveyToolImplementation*) impl)->handleObjectMenuSelect(player, selectedID);
}

void SurveyToolAdapter::sendResourceListTo(PlayerCreature* player) {
	((SurveyToolImplementation*) impl)->sendResourceListTo(player);
}

void SurveyToolAdapter::sendSurveyTo(PlayerCreature* player, const String& resname) {
	((SurveyToolImplementation*) impl)->sendSurveyTo(player, resname);
}

void SurveyToolAdapter::sendSampleTo(PlayerCreature* player, const String& resname) {
	((SurveyToolImplementation*) impl)->sendSampleTo(player, resname);
}

/*
 *	SurveyToolHelper
 */

SurveyToolHelper* SurveyToolHelper::staticInitializer = SurveyToolHelper::instance();

SurveyToolHelper::SurveyToolHelper() {
	className = "SurveyTool";

	DistributedObjectBroker::instance()->registerClass(className, this);
}

void SurveyToolHelper::finalizeHelper() {
	SurveyToolHelper::finalize();
}

DistributedObject* SurveyToolHelper::instantiateObject() {
	return new SurveyTool(DummyConstructorParameter::instance());
}

DistributedObjectServant* SurveyToolHelper::instantiateServant() {
	return new SurveyToolImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* SurveyToolHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new SurveyToolAdapter((SurveyToolImplementation*) obj->_getImplementation());

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

