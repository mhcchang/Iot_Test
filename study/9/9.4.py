#coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、python
	学习目标：flask常用库
	基本用法：
	常用库：
		a、from flask import request
			request库：
				作用：获取前端参数
				request.method   #请求方式
					request.form 	#存储的是所有FormData中的所有数据,使用request.form.to_dict()可以转为字典输出
					request.args 	#存储的是所有URL中的所有数据,使用request.args.to_dict()可以转为字典输出
					request.json 	#Content-Type: application/json 存放在request.json中
					request.data 	#当Content-Type无法被解析时，存放原始数据
					request.url		#请求地址
					request.path 	#url路由地址
					request.host 	#主机地址
					request.host_url 	#将主机地址转换为http url
					request.headers 	#存储的是所有header信息
					request.values      #存储的是post提交的form和url中后的键值(例如:?id=666&net=888),一般不使用. 因为存在问题:form表单和url有同名键值时,后者会覆盖前者.
					request.files    # 获取文件,获取后保存用request.save
					request.remote_addr    # 获取访问者ip
		b、flask-restful
			安装：pip3 install flask-restful
			定义：在flask基础上进行一些封装，主要用于实现restful接口。
			理解：
				1、URI（统一资源标识符）：每一个URI代表一种资源,restful接口对资源进行增删改查。
				2、客户端和服务器之间，传递这种资源的某种表现层。
				3、客户端通过四个HTTP状态，对服务资源进行操作。
			使用步骤：
				api = API(传入flask返回的app)
				每个类继承Resource
		c、和校验一起用
			复习装饰器:https://www.cnblogs.com/JetpropelledSnake/p/8909136.html#_label1
			1、函数装饰器可以装饰类函数。
			2、类中的装饰器可以装饰函数
		d、from webargs.flaskparser import use_args
			这个库主要是用来校验前端传的参数
			
	知识点记录：
		1、初始化参数，如果传入一个就只记录一个。
		2、上下文：https://blog.csdn.net/zwqjoy/article/details/91432737  明天看
2、shell脚本
	读取文件内容：
		有三种，尽量不要用管道在中定义变量，因为会有子shell影响
3、sql	
	    学习链接：https://blog.csdn.net/fashion2014/article/details/78826299/
        –1.学生表
		Student(s_id,s_name,s_birth,s_sex) --学生编号,学生姓名, 出生年月,学生性别
		–2.课程表
		Course(c_id,c_name,t_id) – --课程编号, 课程名称, 教师编号
		–3.教师表
		Teacher(t_id,t_name) --教师编号,教师姓名
		–4.成绩表
		Score(s_id,c_id,s_score) --学生编号,课程编号,分数
		14、查询没学过"张三"老师讲授的任一门课程的学生姓名 
			select a.* from Student a where a.s_id not in(select s_id from Score  where c_id =  (SELECT Course.c_id FROM Course WHERE Course.t_id=(SELECT  Teacher.t_id FROM Teacher WHERE Teacher.t_name="zhangsan")))
		15、查询两门及其以上不及格课程的同学的学号，姓名及其平均成绩 .
		SELECT s.*,f.avg  FROM  Student s,(SELECT  s.s_id,AVG(s.s_score)  avg FROM Score  s WHERE  s.s_id in
		(SELECT a.s_id FROM Student a INNER  JOIN Score s on a.s_id=s.s_id WHERE s.s_score<60 GROUP BY a.s_id  HAVING COUNT(a.s_id)>=2) GROUP BY s.s_id ) f  WHERE s.s_id=f.s_id
		

		16、检索"01"课程分数小于60，按分数降序排列的学生信息
		SELECT a.* FROM  Student a INNER JOIN Score s  on a.s_id=s.s_id WHERE s.c_id=01 AND s.s_score<60 ORDER BY s.s_score DESC
;
		17、按平均成绩从高到低显示所有学生的所有课程的成绩以及平均成绩
		明天学习：ROUND
'''
from webargs.flaskparser import use_args
from  flask import  Flask
from  flask import request
from functools import wraps

from  flask_restful import Api,Resource
app = Flask(__name__)
#flask_restful用法
api = Api(app)
#类中的装饰器可以装饰函数
class t:
	def __init__(self,func):
		print("init")
	@classmethod
	def test(cls,func):
		return func()
@t.test
def tt():
	print("111111")

#装饰类的函数时候，执行子函数时会自动初始化类
from  marshmallow import fields,post_load,Schema,post_dump

class UserSchema(Schema):
	id = fields.String()

	class Meta:
		strict = True
	@post_dump
	def clear_none(self, data,**kwargs):
		print(data)
		return data
def ext(func):#
	@wraps(func)
	def wrapper(*args,**kwargs):
		print(args)
		print(kwargs)
		return  func(*args,**kwargs)
	return wrapper
class test_flask(Resource):
	def __init__(self):
		# print("init")
		super().__init__()
	@use_args(UserSchema)
	def post(self,args):
		# print(id)
		return {'1':1}

# @ext
# def test():
# 	print("11111")
# test()


class test_tflask(Resource):
	def get(self,id):
		print(id)
		return {'1':1}
#传递参数，这个参数要和http方法参数名  以下展示两种参数名
api.add_resource(test_flask,'/t')
api.add_resource(test_tflask,'/tt/<id>/t')


#基本用法
@app.route('/test')
def test():
	print(request.remote_addr)
	print(request.url)
	print(request.path)
	print(request.headers)
	print(request.json)
	print(request.data)

	print(request.args.to_dict())

	return '1'
app.run(host="0.0.0.0",port=8888)