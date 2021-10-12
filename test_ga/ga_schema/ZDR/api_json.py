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
import json
from test_ga.ga_schema.ZDR.schema import  zdrObj
from test_ga.ga_schema.ZDR.model import Zdr_param



#{zdr}
class Zdr_data:
	def __init__(self):
		self.data = [Zdr_list()]
#[]
class Zdr_list:
	def __init__(self):
		l = len(sql.query_all(Zdr_param))
		if l ==0 :
			with open('api.json','r',encoding='gbk') as f :
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
				except Exception as e :
					print(e.args)
				finally:
					kwagrs = d
					print(sql.add(Zdr_param,**kwagrs))

			pass
		else:
			for x in sql.query_all(Zdr_param):
				arg = x.name
				self.__dict__[arg] = (fun_type_se(x))
p = Zdr_data()
print(zdrObj().dumps(p))


