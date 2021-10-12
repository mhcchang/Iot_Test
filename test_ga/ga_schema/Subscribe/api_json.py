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
from test_ga.ga_schema.Subscribe.model import Sub
from  test_ga.ga_schema.Subscribe.schema import SubscribeListObject as sub
import json
class SubscribeListObject:
	def __init__(self):
		self.SubscribeListObject=SubscribeObject()
class SubscribeObject:
	def __init__(self):
		self.SubscribeObject = [SUB()]
class SUB:
	def __init__(self):
		l = len(sql.query_all(Sub))
		if l ==0 :
			with open('apes.json','r') as f :
				ape = json.load(f)
			for x in ape['rules']:
				d = dict()
				d['name'] = x.get('name',None)
				d['type'] = x.get('type',None)
				d['required'] = x.get('required',None)
				d['funcType'] = x.get('funcType',None)
				if isinstance(x.get('funcType',None),int):
					d['funcArgs'] = str(x.get('funcType',None))
				elif isinstance(x.get('funcType',None),list):
					d['funcArgs'] = ",".join(list(map(lambda x:str(x),x.get('funcType',None))))
				kwagrs = d
				print(sql.add(Sub,**kwagrs))
			pass
		else:
			for x in sql.query_all(Sub):
				arg = x.name
				self.__dict__[arg] = (fun_type_se(x))

