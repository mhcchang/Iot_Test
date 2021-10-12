# coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、解决java环境变量问题
	原因：由于源没更新导致安装java部分失败
		使用命令：
			whereis -b 命令
			which命令的原理是在PATH变量指定的路径中，搜索某个系统命令的位置，并且返回第一个搜索结果
			type命令是用来判断shell命令的类型的，如果是内部命令，没有独立可执行的文件，也就谈不上目录
		sudo apt-get update
		sudo apt install openjdk-8-jdk -y #如果不更新源可能会安装失败
	遗留问题：
		1、执行机若还有任务执行再分发则会出现忙的现象，导致执行不下去，因此在执行前应该把1099端口kill掉，然后再启动jmeter-server -D hostname
2、sql
	学习链接：https://blog.csdn.net/bingqingsuimeng/article/details/51595560
	主键:其值能唯一地标识表中的每一行。这样的一列或多列称为表的主键，通过它可强制表的实体完整性。主键不能重复。
		选择编号作为主键、自动编号主键、UUID
	外键：保持数据一致性，完整性，主要目的是控制存储在外键表中的数据。 使两张表形成关联，外键只能引用外表中的列的值！
		建立外键的前提： 本表的列必须与外键类型相同(外键必须是外表主键)。
		指定主键关键字： foreign key(列名)
		引用外键关键字： references <外键表名>(外键列名)
		创建外键：alter table 表名 add constraint FK_ID foreign key(你的外键字段名) REFERENCES 外表表名(对应的表的主键字段名);
					注意：设置的外键字段不能是主键
						所关联字段的数据类型长度一样
		constraint 外键名字  foreign key （添加外键的列名）references 参考表的名称（参考表中的列名）

		作用：主要是主键表中数据发生改变后关联到外键表中的数据操作，更新或者删除
	数据库索引：数据库索引其实就是为了使查询数据效率快。
		设置索引语句：CREATE INDEX index_name ON table_name (column_name)
				创建索引：CREATE INDEX szProxyCode on cacheList(szProxyCode)
				删除所有：ALTER TABLE table_name DROP INDEX index_name
		分为：hash索引 和BTREE 一般使用BTREE分叉树
		链接：https://blog.csdn.net/wzyaiwl/article/details/106084627
	10、查询学过编号为"01"但是没有学过编号为"02"的课程的同学的信息
		select a.* from 
	Student a 
	where a.s_id in (select s_id from Score where c_id='01' ) and a.s_id not in(select s_id from Score where c_id='02')
			
3、python(orm+flask+mysql)
	#编写一个module schema分开的场景
	
	
'''
import sqlalchemy
from sqlalchemy import create_engine, Table, MetaData
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String
from sqlalchemy.orm import mapper, sessionmaker

engine = create_engine("mysql+pymysql://root:123456@10.235.97.220:3309/study",
					   encoding='utf-8')  # 创建需要操作的sql对象，相当于创建连接池
# echo=True是否开启打印
Base = declarative_base()  # 相当于创建鸡肋对象，对于class表模型都要继承


# print(dir(Base))
# print(dir(Base.metadata))
# 第一步创建方式
class User(Base):
	__tablename__ = 'user'  # 表名
	id = Column(Integer, primary_key=True)
	name = Column(String(32))
	password = Column(String(64))
	print("user")

	def __init__(self, **kwargs):
		print("__init__")
		self.k_d = {}
		for k, v in kwargs.items():
			self.k_d[k] = v

	def __repr__(self):
		return "<User(name='%s',  password='%s')>" % (
			self.name, self.password)

	@property
	def project(self):
		print("project")
	@classmethod
	def query(cls, id):  # 现在实现了自查方法，后面需要把session close掉
		f = cls.db_connet().query(cls).filter(cls.id == id).first()
		cls.session.close()
		return f

	@classmethod
	def query_id(cls, id):
		f = cls.db_connet().query(cls).filter(cls.id == id).first()
		return f
	@classmethod
	def db_connet(cls):
		Session_Class = sessionmaker(bind=engine)  # 示例和engine绑定
		cls.session = Session_Class()
		return cls.session

	def __enter__(self):
		return eval("%s.query(%s)" % ((self.__class__.__name__), self.k_d['id']))

	def __exit__(self, exc_type, exc_val, exc_tb):
		print("exit")


print(User().query_id(30))

exit(0)
