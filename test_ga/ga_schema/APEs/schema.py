#coding:utf-8
'''
author:
function:
param:
other
'''
#class to  json
from  marshmallow import fields,post_load,Schema,post_dump


#采集设备
class APE(Schema):
	ApeID = fields.String()
	Name = fields.String()
	Model = fields.String()
	IPAddr = fields.String()
	IPV6Addr = fields.String()
	Port = fields.Integer()
	Longitude = fields.Number()
	Latitude = fields.Number()
	PlaceCode = fields.String()
	Place = fields.String()
	IsOnline = fields.String()
	UserId = fields.String()
	Password = fields.String()
	FunctionType = fields.String()
class APEObject(Schema):
	APEObject = fields.List(fields.Nested(APE))


class APEListObject(Schema):
	APEListObject = fields.Nested(APEObject)



#保活注册


