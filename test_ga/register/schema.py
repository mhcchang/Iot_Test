#coding:utf-8
'''
author:
function:
param:
other
'''
from  marshmallow import fields,post_load,Schema,post_dump
#保活
class Keepalive(Schema):
	DeviceID = fields.String()
class KeepaliveObject(Schema):
	KeepaliveObject = fields.Nested(Keepalive)
	uuid = fields.String()
	date = fields.DateTime()
class KeepTo(Schema):
	id = fields.String()
	StatusCode = fields.Integer()
	StatusString = fields.String()
	LocalTime = fields.String()
	RequestURL = fields.String()


#注册
class register(Schema):
	DeviceID = fields.String()
class RegisterObject(Schema):
	RegisterObject = fields.Nested(register)
	uuid = fields.String()
	date = fields.DateTime()
class RegisterTo(Schema):
	id = fields.String()
	StatusCode = fields.Integer()
	StatusString = fields.String()
	LocalTime = fields.String()
	RequestURL = fields.String()

	class Meta:
		strict = True

#订阅
class subBody(Schema):
	id = fields.String()
	StatusCode = fields.Integer()
	StatusString = fields.String()
	LocalTime = fields.String()
	RequestURL = fields.String()
class ResponseStatus(Schema):
	KeepaliveObject = fields.List(fields.Nested(subBody))
class ResponseStatusList(Schema):
	ResponseStatusList = fields.Nested(ResponseStatus)

