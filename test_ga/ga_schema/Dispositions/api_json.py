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
from test_ga.ga_schema.Dispositions.model import Dispositions_param
from test_ga.ga_schema.Dispositions.schema import DispositionListObject as scDisposition

import json
from test_ga.ga_schema.Face.model import SubImageList as sl

#subimagelist
class SubImageList:
	def __init__(self):
		self.SubImageInfoObject=[SubImageInfo()]
class SubImageInfo:
	def __init__(self):
		for x in sql.query_all(sl):
			arg = x.name
			self.__dict__[arg] = (fun_type_se(x))
#Disposition body
class DispositionListObject():
	def __init__(self):
		self.DispositionListObject = DispositionObject()
		pass
#{DispositionObject}
class DispositionObject:
	def __init__(self):
		self.DispositionObject = [Disposition()]
#[]
class Disposition:
	def __init__(self):
		l = len(sql.query_all(Dispositions_param))
		# self.SubImageList =SubImageList()
		if l ==0 :
			with open('apes.json','r') as f :
				ape = (json.load(f))
			for x in ape['rules']:
				d = dict()
				d['name'] = x.get('name',None)
				d['type'] =  x.get('type',None)
				d['required'] = x.get('required',None)
				d['funcType'] = x.get('funcType',None)
				print()
				if x.get('funcArgs',None):
					if isinstance(x['funcArgs'],int):
						d['funcArgs'] = str(x['funcType'])
					elif isinstance(x['funcArgs'],list):
						d['funcArgs'] = ",".join(list(map(lambda x:str(x),x['funcArgs'])))
				else:
					pass
				kwagrs = d
				print(sql.add(Dispositions_param,**kwagrs))
		else:
			for x in sql.query_all(Dispositions_param):
				arg = x.name
				self.__dict__[arg] = (fun_type_se(x))
p = DispositionListObject()
print(scDisposition().dumps(p))
