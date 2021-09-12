#coding:utf-8
'''
author:
function:
param:
other
'''
from  enum import Enum,unique

@unique
class Status(Enum):
	SUCC = 0
	ERROR = 1
	OTHER = 2
