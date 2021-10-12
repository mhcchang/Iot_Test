#coding:utf-8
'''
author:
function:
param:
other
'''
#class to  json
from  marshmallow import fields,post_load,Schema,post_dump

#ZDR list
class ZdrList(Schema):
	RXSFYQID = fields.String()
	RKLX = fields.String()
	ZDRID = fields.String()
	TZSJ = fields.String()
	ZHXGSJ = fields.String()
	TZZL = fields.String()
	SFZXBS = fields.Integer()
	ZXSJ = fields.Integer()
#person obejct
class zdrObj(Schema):
	data = fields.List(fields.Nested(ZdrList))


