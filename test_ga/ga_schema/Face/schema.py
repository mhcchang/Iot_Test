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



#face list
class FL(Schema):
	FaceID = fields.String()
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
#face obejct
class FO(Schema):
	FaceObject = fields.List(fields.Nested(FL))
#face list object
class FLO(Schema):
	FaceListObject = fields.Nested(FO)



