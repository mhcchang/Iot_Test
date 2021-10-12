# coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、关于各种数据库
	mongoDB：
		（1）Mongodb的不足之处
				1、在集群分片中的数据分布不均匀
				2、单机可靠性比较差
				3、大数据量持续插入，写入性能有较大波动
				4、磁盘空间占用比较大
		（2）Mongodb的过人之处
				1、无模式
				2、查询与索引方式灵活，是最像SQL的Nosql
				3、支持复制集、主备、互为主备、自动分片等特性
	安装：
		docker 拉取：docker pull mongo:latest
	运行：
		docker run -itd --name mongo -p 27017:27017 mongo --auth
	连接使用:
		robot工具
	python调用：
		安装库：pip3 install pymongo
		注意: 在 MongoDB 中，数据库只有在内容插入后才会创建! 就是说，数据库创建后要创建集合(数据表)并插入一个文档(记录)，数据库才会真正创建。
		orm使用pymongo:
			安装：pip3 install mongoengine
			使用orm:
				import pymongo
				
				myclient = pymongo.MongoClient("mongodb://10.235.97.220:27017/")
				mydb = myclient["runoobdb"]
				# ----
				# ORM模式中使用mongodb
				from mongoengine import *
				
				connect('runoobdb', host='10.235.97.220', port=27017)
				
				
				class Users(Document):
					name = StringField(required=True, max_length=200)
					age = IntField(required=True)
				
				user1 = Users(
				 name='jack',
				 age= 21
				)
				user1.save()
				users = Users.objects.all()  # 返回所有的文档对象列表
	redis:
		优点：
			速度快
			支持丰富数据类型: String ，List，Set，Sorted Set，Hash 。
			丰富的特性
			持久化存储
		缺点：
			1、由于 Redis 是内存数据库，所以，单台机器，存储的数据量，跟机器本身的内存大小。虽然 Redis 本身有 Key 过期策略，但是还是需要提前预估和节约内存。如果内存增长过快，需要定期删除数据。
			2、redis是单线程的，单台服务器无法充分利用多核服务器的CPU
		使用：
			https://www.runoob.com/w3cnote/python-redis-intro.html
		分布式锁：
			https://www.cnblogs.com/angelyan/p/11523846.html
	redis和mongodb区别：
		https://www.cnblogs.com/java-spring/p/9488227.html
'''
# 创建数据库

