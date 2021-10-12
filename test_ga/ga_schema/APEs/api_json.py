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
from test_ga.ga_schema.APEs.model import APEs
from  test_ga.ga_schema.APEs.schema import APEListObject as ApLo
import json
class APEListObject:
	def __init__(self):
		self.APEListObject=APEObject()
class APEObject:
	def __init__(self):
		self.APEObject = [APE()]
class APE:
	def __init__(self):
		l = len(sql.query_all(APEs))
		if l ==0 :
			with open('apes.json','r') as f :
				ape = (json.load(f))
			for x in ape['rules']:
				d = dict()
				d['name'] = x['name']
				d['type'] = x['type']
				d['required'] = x['required']
				d['funcType'] = x['funcType']
				if isinstance(x['funcArgs'],int):
					d['funcArgs'] = str(x['funcType'])
				elif isinstance(x['funcArgs'],list):
					d['funcArgs'] = ",".join(list(map(lambda x:str(x),x['funcArgs'])))
				kwagrs = d
				print(sql.add(APEs,**kwagrs))

			pass
		else:
			for x in sql.query_all(APEs):
				print(x)
				arg = x.name
				self.__dict__[arg] = (fun_type_se(x))
