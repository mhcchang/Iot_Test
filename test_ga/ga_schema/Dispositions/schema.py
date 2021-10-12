#coding:utf-8
'''
author:
function:
param:
other
'''
#class to  json
from  marshmallow import fields,post_load,Schema,post_dump
#subimage
class sublist(Schema):
	ImageID = fields.String()
	Type = fields.String()
	InfoKind = fields.Integer()
	ImageSource = fields.String()
	EventSort = fields.Integer()
	DeviceID = fields.String()
	FileFormat = fields.String()
	ShotTime = fields.String()
	Title = fields.String()
	ContentDescription = fields.String()
	ShotPlaceFullAdress = fields.String()
	SecurityLevel = fields.String()
	Width = fields.Integer()
	Height = fields.Integer()
	FileSize = fields.Integer()
	Data = fields.String()

class SubImageInfoObject(Schema):
	SubImageInfoObject =fields.List(fields.Nested(sublist))



##Disposition list
class Disposition(Schema):
	DispositionID = fields.String()
	Title = fields.String()
	DispositionCategory = fields.String()
	TargetFeature = fields.String()
	TargetImageURI = fields.String()
	PriorityLevel = fields.Integer()
	ApplicantName = fields.String()
	ApplicantOrg = fields.String()
	ApplicantInfo = fields.String()
	BeginTime = fields.String()
	EndTime = fields.String()
	CreatTime = fields.String()
	OperateType = fields.Integer()
	DispositionStatus = fields.Integer()
	DispositionRange = fields.String()
	TollgateList = fields.String()
	DispositionArea = fields.String()
	ReceiveAddr = fields.String()
	ReceiveMobile = fields.String()
	Reason = fields.String()
	DispositionRemoveOrg = fields.String()
	DispositionRemovePerson = fields.String()
	DispositionRemoveTime = fields.String()
	DispositionRemoveReason = fields.String()
	SubImageList = fields.Nested(SubImageInfoObject)



#DispositionObject
class DispositionObject(Schema):
	DispositionObject = fields.List(fields.Nested(Disposition))
#DispositionListObject
class DispositionListObject(Schema):
	DispositionListObject = fields.Nested(DispositionObject)



