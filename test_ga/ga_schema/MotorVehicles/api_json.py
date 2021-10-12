# coding:utf-8
'''
author:
function:
param:
other
'''
#云图采集接口所需要的的字典
#动态修改参数
from test_ga.model.utils.sql_operate import sql_operate as sql
from  test_ga.ga_schema.utils.fun_type import *
from test_ga.ga_schema.MotorVehicles.model import MotorVehicles
from test_ga.ga_schema.MotorVehicles.schema import MotorListObj
import json
from test_ga.ga_schema.Face.model import Face_param,SubImageList as sl

#subimagelist
class SubImageList:
	def __init__(self):
		self.SubImageInfoObject=[SubImageInfo()]
class SubImageInfo:
	def __init__(self):
		for x in sql.query_all(sl):
			arg = x.name
			self.__dict__[arg] = (fun_type_se(x))
#person body

class MotorVehicleListObject():
	def __init__(self):
		self.MotorVehicleListObject = MotorVehicleObject()
		pass
#{PersonObject}
class MotorVehicleObject:
	def __init__(self):
		self.MotorVehicleObject = [MotorVehicle()]
#[]
class MotorVehicle:
	def __init__(self):
		l = len(sql.query_all(MotorVehicles))
		self.SubImageList =SubImageList()
		if l ==0 :
			with open('apes.json','r') as f :
				ape = (json.load(f))
			for x in ape['rules']:
				d = dict()
				d['name'] = x['name']
				d['type'] = x['type']
				d['required'] = x['required']
				d['funcType'] = x.get('funcType',None)
				if isinstance(x['funcArgs'],int):
					d['funcArgs'] = str(x['funcType'])
				elif isinstance(x['funcArgs'],list):
					d['funcArgs'] = ",".join(list(map(lambda x:str(x),x['funcArgs'])))
				kwagrs = d
				print(sql.add(MotorVehicles,**kwagrs))

			pass
		else:
			for x in sql.query_all(MotorVehicles):
				arg = x.name
				self.__dict__[arg] = (fun_type_se(x))
# p = MotorVehicleListObject()
# print(MotorListObj().dumps(p))
