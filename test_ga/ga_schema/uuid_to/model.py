# coding:utf-8
'''
author:
function:
param:
other
'''
import sys, os

sys.path.append(os.path.abspath('../'))
from test_ga.model.utils.BaseModel import Base_model
from test_ga.model.utils.Colume_Type import *


# 记录每次操作web的业务类型及uuid
class Uuid_to(Base_model):
	__tablename__ = 'uuid_to'
	name = Column(String(255))
	uuid = Column(String(255))
	type = Column(String(255))
	other = Column(String(255))
