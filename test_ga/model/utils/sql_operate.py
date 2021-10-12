# coding:utf-8
'''
author:
function:
param:
other
'''
import sys, os

sys.path.append(os.path.abspath('../'))
from test_ga.model.model_table import *
from  test_ga.ga_schema.Face.model import Face_param,SubImageList
from test_ga.model.utils.db_session import engine
from  test_ga.model.utils.status_code import Status
from test_ga.ga_schema.uuid_to.model import Uuid_to

class sql_operate(object):

	@classmethod
	def query(cls, table, **kwargs):  # 查询方法，精确查询
		'''
		:param table:传入的表名，ex:User
		:param kwargs:传入查询的参数，ex:{id=11,name=11}
		:return:
		'''
		with table() as session:
			for k in list(kwargs.keys()):
				if kwargs[k] == None:
					kwargs.pop(k)
			sql_str = [("%s.%s ==  '%s'" % (table.__name__, k, v)) for k, v in kwargs.items()]
			sql = 'session.query(%s)' % (table.__name__) + "".join(
				[".%s" % ("filter" + "(" + i + ")") for i
				 in sql_str]) + ".first()"
			#
			f = eval(sql)
			import copy
			f = copy.deepcopy(f)
			return f

	@classmethod
	def query_all(cls, table, page=1, per_page=200):
		'''
		:param table:
		:param page:查询第多少页
		:param per_page:每次查多少
		:return:
		'''
		with table() as session:
			f = session.query(table).filter().limit(per_page).offset((page - 1) * per_page).all()
			import copy
			f = copy.deepcopy(f)
			return f

	@classmethod
	def query_by_id(cls, table, id):
		'''
		根据id查找
		:param table:
		:param id:
		:return:
		'''
		with table():
			f = table.session.query(table).filter(table.id == id).first()

		return f

	@classmethod
	def add(cls, table, **kwargs):
		'''

		:param table:
		:param kwargs:
		:return:
		'''
		with table() as session:
			# t_ = ['%s=%s' % (k, v) for k, v in kwargs.items()]
			try:
				# u = eval((('%s(%s)' % (table.__name__, (','.join(t_))))))
				# print(table(**kwargs))
				u = table(**kwargs)
				import copy
				f = copy.deepcopy(u)

				session.add(u)
				session.commit()
			except Exception as e:
				return cls.res_msg({"code":Status.ERROR.value,'mag':'%s'%(e)})
			return f

	@classmethod
	def update(cls, table, **kwargs):
		'''
		:param table:
		:param kwargs:
		:return:
		'''

		with table() as session:
			f = session.query(table).filter(table.id == kwargs['id']).first()
			for k, v in kwargs.items():
				if hasattr(f, k):
					setattr(f, k, v)
			ff = session.commit()
			print(ff)
			return f

	@classmethod
	def delete(cls, table, **kwargs):
		'''

		:param table:
		:param kwargs:
		:return:
		'''

		with table() as session:
			sql_str = [("%s.%s ==  %s" % (table.__name__, k, v)) for k, v in kwargs.items()]
			sql = 'session.query(%s)' % (table.__name__) + "".join(
				[".%s" % ("filter" + "(" + i + ")") for i
				 in sql_str]) + ".delete()"
			f = eval(sql)
			session.commit()
			return f

	@classmethod
	def res_msg(cls,msg):
		return msg