#coding:utf-8
'''
author:
function:
param:
other
'''
import sys, os

sys.path.append(os.path.abspath('../'))
from flask import request
from  flask_restful import  Api,Resource
from webargs.flaskparser import use_args
from test_ga.caseConfig.config import *
from test_ga.register.schema import *
class add_case(Resource):

	def get(self):
		return "00"
	def post(self):
		return "00"
	def delete(self):
		return "00"
from test_ga.model.utils.sql_operate import sql_operate as sql
from test_ga.register.model import Register
from test_ga.ga_schema.uuid_to.model import Uuid_to
from datetime import datetime
import uuid
print(datetime.now())
#保活
class System_keep(Resource):
	@use_args(KeepaliveObject)
	def post(self,args):
		d = dict()
		for k,v in args.items():
			d[k] = str(v)
		d['uuid'] = str(uuid.uuid1())
		d['date'] = datetime.now()
		kwargs = d
		# print(",".join([ '%s=%s'%(k,d[k]) for k,v in d.items()]))
		o = sql.add(Register, **kwargs)
		setattr(o,'id',args['KeepaliveObject']['DeviceID'])
		setattr(o,'RequestURL','/VIID/System/Keepalive')
		setattr(o,'StatusCode',0)
		setattr(o,'StatusString',"0")
		setattr(o,'LocalTime',str(datetime.now().strftime('%Y%m%d%H%M%S')))
		g = KeepTo().dump(o)
		return g

class System_Time(Resource):
	def get(self):
		pass
#接收注册，作为上级的时候
class System_Register(Resource):
	@use_args(RegisterObject)
	def post(self,args):
		Register = type('Register',(),{"id":args['RegisterObject']['DeviceID'],"StatusCode":0,"StatusString":"0","LocalTime":"","RequestURL":"/VIID/System/Register",})
		return RegisterTo().dump(Register())
#注销
class System_Unregister(Resource):
	def post(self):
		pass

#订阅相关
import json
from  test_ga.case.utils.req import key_value,l
class SubInfo(Resource):
	def post(self,**kwargs):

		self.get_key()
		#redis中查询生成的数值
		ResponseStatus = type('ResponseStatus',(),{'ResponseStatusList':{"ResponseStatus":[{'id':11,
																							'RequestURL':'/VIID/SubscribeNotifications','StatusCode':'11',
																	'StatusString':0,'LocalTime':str(datetime.now().strftime('%Y%m%d%H%M%S'))}]}})
		d = dict()
		d['ResponseStatusList'] = ResponseStatus.__dict__['ResponseStatusList']
		return d
	def get_key(self,case={'test_face':'FaceID','test_person':'PersonID'}):
		'''
		:param case:
		:return:
		'''
		print('sssss')
		from copy import deepcopy
		for k,v in case.items():
			r = sql.query(Uuid_to,name=k)
			f = key_value(json.loads(r_redis.get(r.uuid)),v)
			id = deepcopy(l)
			key_value(request.json,v)
			r_id = deepcopy(l)
			print('-----------------start')
			print('k',k)
			print('v',v)
			print('id',id)
			print('r_id',r_id)
			print('------------------stop')
			if id[0] == r_id[0]:
				r.other = 'pass'
			else:
				r.other = 'fail'
				pass
			kwargs=r.__dict__
			del kwargs['_sa_instance_state']
			sql.update(Uuid_to, **kwargs)


	# 110100000000032019070912131400005