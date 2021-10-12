# coding:utf-8
'''
author:
function:
param:
other
'''
import sys,os
sys.path.append(os.path.abspath('../../'))
from test_ga.model.utils.db_session import *
#工具类
class sql_:
	# def __new__(cls, *args, **kwargs):#示例创建前调用 .若__new__()没有正确返回当前类cls的实例，那__init__()将不会被调用
	# 	Session_Class = sessionmaker(bind=engine)  # 示例和engine绑定
	# 	session = Session_Class()
	# 	return super().__new__(cls)#这个参数返回给init了
	def __enter__(self):
		Session_Class = sessionmaker(bind=engine)  # 示例和engine绑定
		self.session = Session_Class()
		Base.metadata.create_all(engine)
		return self.session
	def __exit__(self, exc_type, exc_val, exc_tb):
		self.session.rollback()  # 回滚
		self.session.close()

#父类
class Base_model(Base,sql_):
	__abstract__ = True

	id = Column(Integer, primary_key=True)

	pass



