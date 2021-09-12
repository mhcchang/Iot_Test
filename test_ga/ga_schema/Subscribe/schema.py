#coding:utf-8
'''
author:
function:
param:
other
'''
#class to  json
from  marshmallow import fields,post_load,Schema,post_dump

#级联订阅
class sub(Schema):
	SubscribeID = fields.String()
	Title = fields.String()
	SubscribeDetail = fields.String()
	ResourceURI = fields.String()
	ApplicantName = fields.String()
	ApplicantOrg = fields.String()
	BeginTime = fields.String()
	EndTime = fields.String()
	ReceiveAddr = fields.String()
	Reason = fields.String()
	OperateType = fields.Integer()
	SubscribeStatus = fields.Integer()
	SubscribeCancelOrg = fields.String()
	SubscribeCancelPerson = fields.String()
	CancelTime = fields.String()
	CancelReason = fields.String()

class SubscribeObject(Schema):
	SubscribeObject = fields.List(fields.Nested(sub))


class SubscribeListObject(Schema):
	SubscribeListObject = fields.Nested(SubscribeObject)






