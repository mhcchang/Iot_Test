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



#person list
class PersonList(Schema):
	PersonID = fields.String()
	InfoKind = fields.Integer()
	DeviceID = fields.String()
	SubImageList = fields.Nested(SubImageInfoObject)
	SourceID = fields.String()
	LeftTopX = fields.Integer()
	LeftTopY = fields.Integer()
	RightBtmX = fields.Integer()
	RightBtmY = fields.Integer()
	IsDriver = fields.Integer()
	IsSuspectedTerrorist = fields.Integer()
	IsCriminalInvolved = fields.Integer()
	IsDetainees = fields.Integer()
	IsSuspiciousPerson = fields.Integer()
	IsVictim = fields.Integer()
	LocationMarkTime = fields.String()
	IsForeigner = fields.Integer()
#person obejct
class PersonObj(Schema):
	PersonObject = fields.List(fields.Nested(PersonList))
#person list object
class PersonListObj(Schema):
	PersonListObject = fields.Nested(PersonObj)



