#coding:utf-8
'''
author:
function:
param:
other
'''
import sys, os

sys.path.append(os.path.abspath('../'))
from test_ga.model.utils.sql_operate import sql_operate as sql
from  test_ga.model.model_table import *


class operate_sql:

	def add(self,table,**kwargs):
		sql.add(table,kwargs)
