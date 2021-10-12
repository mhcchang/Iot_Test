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
from test_ga.ga_schema.NonMotorVehicles.model import NonMotorVehicles
import json
from test_ga.ga_schema.Face.model import SubImageList as sl
from test_ga.ga_schema.NonMotorVehicles.schema import NonMotorListObj
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

class NonMotorVehicleListObject():
	def __init__(self):
		self.NonMotorVehicleListObject = NonMotorVehicleObject()
		pass
#{PersonObject}
class NonMotorVehicleObject:
	def __init__(self):
		self.NonMotorVehicleObject = [NonMotorVehicle()]
#[]
class NonMotorVehicle:
	def __init__(self):
		l = len(sql.query_all(NonMotorVehicles))
		self.SubImageList =SubImageList()
		if l ==0 :
			with open('api.json','r') as f :
				ape = (json.load(f))
			for x in ape['rules']:
				d = dict()
				d['name'] = x['name']
				d['type'] = x['type']
				d['required'] = x['required']
				d['funcType'] = x.get('funcType',None)
				try:
					if isinstance(x['funcArgs'], int):
						d['funcArgs'] = str(x['funcType'])
					elif isinstance(x['funcArgs'], list):
						d['funcArgs'] = ",".join(list(map(lambda x: str(x), x['funcArgs'])))
					kwagrs = d

				except Exception as e :
					print(e.args)
				finally:
					print(sql.add(NonMotorVehicles, **kwagrs))
			pass
		else:
			for x in sql.query_all(NonMotorVehicles):
				arg = x.name
				self.__dict__[arg] = (fun_type_se(x))
# NonMotorVehicle()
# p = NonMotorVehicleListObject()
# print(NonMotorListObj().dumps(p))
