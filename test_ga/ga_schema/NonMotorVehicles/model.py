#coding:utf-8
'''
author:
function:
param:
other
'''
from test_ga.model.utils.BaseModel import  Base_model
from test_ga.model.utils.Colume_Type import  *
#非机动车采集body
class NonMotorVehicles(Base_model):
	__tablename__ = 'nonnotorvehicle'
	name = Column(String(255))
	type = Column(String(255))
	funcType = Column(String(255))
	required = Column(String(255))
	describe = Column(String(255))
	funcArgs = Column(String(255))
