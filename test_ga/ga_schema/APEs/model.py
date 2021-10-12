#coding:utf-8
'''
author:
function:
param:
other
'''
import sys, os
#存的表
sys.path.append(os.path.abspath('../'))
from test_ga.model.utils.BaseModel import  Base_model
from test_ga.model.utils.Colume_Type import  *
#人脸采集body
class APEs(Base_model):
	__tablename__ = 'apes'
	name = Column(String(255))
	type = Column(String(255))
	funcType = Column(String(255))
	required = Column(String(255))
	describe = Column(String(255))
	funcArgs = Column(String(255))

