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
from test_ga.ga_schema.Person.model import Person_param
from test_ga.ga_schema.Person.schema import PersonObj
import json
from test_ga.ga_schema.Face.model import Face_param,SubImageList as sl
from  test_ga.ga_schema.Person.schema import PersonListObj

#subimagelist
class FaceList():
	def __init__(self):
		for x in sql.query_all(Face_param):
			arg = x.name
			self.__dict__[arg] = (fun_type_se(x))
		self.SubImageList =SubImageList()
class SubImageList:
	def __init__(self):
		self.SubImageInfoObject=[SubImageInfo()]
class SubImageInfo:
	def __init__(self):
		for x in sql.query_all(sl):
			arg = x.name
			self.__dict__[arg] = (fun_type_se(x))
#person body

class PersonListObject():
	def __init__(self):
		self.PersonListObject = PersonObject()
		pass
#{PersonObject}
class PersonObject:
	def __init__(self):
		self.PersonObject = [Person()]
#[]
class Person:
	def __init__(self):
		l = len(sql.query_all(Person_param))
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
				print(sql.add(Person_param,**kwagrs))

			pass
		else:
			for x in sql.query_all(Person_param):
				arg = x.name
				self.__dict__[arg] = (fun_type_se(x))
# p = PersonListObject()
# print(PersonListObj().dumps(p))
