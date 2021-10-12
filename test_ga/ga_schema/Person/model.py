#coding:utf-8
'''
author:
function:
param:
other
'''
from test_ga.model.utils.BaseModel import  Base_model
from test_ga.model.utils.Colume_Type import  *
#人员采集body
class Person_param(Base_model):
	__tablename__ = 'person_param'
	name = Column(String(255))
	type = Column(String(255))
	funcType = Column(String(255))
	required = Column(String(255))
	describe = Column(String(255))
	funcArgs = Column(String(255))
# #subimage中的body
# class SubImageList(Base_model):
# 	__tablename__ = 'subimagelist'
# 	name = Column(String(255))
# 	type = Column(String(255))
# 	funcType = Column(String(255))
# 	required = Column(String(255))
# 	describe = Column(String(255))
# 	funcArgs = Column(String(255))