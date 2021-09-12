#coding:utf-8
'''
author:
function:
param:
other
'''
import sys, os

sys.path.append(os.path.abspath('../'))
from test_ga.model.utils.BaseModel import  Base_model
from test_ga.model.utils.Colume_Type import  *
class Register(Base_model):
	__tablename__ = 'register'
	uuid = Column(String(255))
	date = Column(DateTime)
	KeepaliveObject = Column(String(255))

