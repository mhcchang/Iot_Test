#coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、python 学习
	schema：
		schema是什么？
			校验数据
		安装？
			pip3 istall schema
		基本用法：
			1、给schema传入类型（int str float）
				Schema(int).validate("10")#传入要校验的对象，如果符合则返回校验对象，如果不符合则报错抛异常
			2、传入可调用对象（函数、带__call__的类）
				print(Schema(test()).validate(5))
			3、内置了其它的类：and or use等
				Schema(And(str,test())).validate("5")
			4、传入容器对象（list,tuple,set等）
				Schema([int,float]).validate([1,2,3])#对象中任何元素必须是int 或者 float才可以 是or的关系
			5、传入一个字典对象（常用场景）
				Schema({'name':str,'age':int}).validate({'name':'222','age':11})#首先验证key 再验证value值的类型
			6、字段数据可选则么么设置
				Schema({'name':str,Optional('age'):int}).validate({'name':'222'})#首先验证key 再验证value值的类型,age字段可以不传，可选
			6.1  想让Schema只验证传入字典中的一部分数据，可以有多余的key但是不要抱错，怎么做？
				Schema({'name': str, 'age': int}, ignore_extra_keys=True).validate({'name': 'foobar', 'age': 100, 'sex': 'male'})
			6.2 Schema抛出的异常信息不是很友好，我想自定义错误信息，怎么办？
				Schema({'name': str, 'age': Use(int, error='年龄必须是整数')}).validate({'name': 'foobar', 'age': 111})
		项目中使用:
			配合使用：marshmallow库，实现python对象和原生数据相互转换，如object-->dict objects-->list string ->dict 还提供了丰富的数据转换类型和校验API
			复习：
				序列化:把变量从内存中变成可存储或传输的过程，json.dumps()
				json.dumps把类序列化：
					json.dumps(t,default=lambda obj:obj.__dict__)
				反序列化：把变量内容从序列化的对象重新读到内存里，json.loads()
			知识点：
				类中的方法或属性：
					['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__']
					TEST.__class__代表这个类的类型是type
						TEST.__class__.__name__ 返回的是父类的类名
						TEST.__class.__base__ 返回基础类
					Test.__dict__  返回这个类的内存地址及类属性已经定义的值 {'__module__': '__main__', '__init__': <function Test.__init__ at 0x7f2769e15510>, '__dict__': <attribute '__dict__' of 'Test' objects>, '__weakref__': <attribute '__weakref__' of 'Test' objects>, '__doc__': None, 's': 2}
				实例化后的方法或属性：
					['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'id', 'name']
					t。__class__  返回这个类名（主类名）
					t。__dict__ 以字典形式返回这个类的key和value  {"id": 1, "name": 2}
			marshmallow：
				1、作用
					序列号反序列号及参数校验所用的库：教程链接：https://www.cnblogs.com/zhuchunyu/p/12017197.html
				2、包含库：fields  post_load  Schema  post_dump
					2.1 作用：
						fields:是定义字段属性。
						post_load：在反序列化后的操作。
						post_dump：在序列化后的操作
						ValidationError：定义一些错误
					2.2 用法：
						1、一般定义需要校验的字段类。
						2、实际类。
						3、具体看下面操作
					2、3 学了以后怎么用：
						1、在我们的项目中增加，明天的任务。
	flask:
	迭代器：
	生成器：
	restapi：
	高级函数：
2、shell学习
	详情见9.2.sh中学习资料

'''
#marshmallow 库学习链接：https://blog.csdn.net/haeasringnar/article/details/109339949
#这个相当于就把之前json不能做的事情做了
from  marshmallow import fields,post_load,Schema,post_dump
import  json

class UserSchema(Schema):
	name = fields.String()
	email = fields.String()
	@post_dump
	def clear_none(self, data,**kwargs):
		print(data)
		return data

class User():
	def __init__(self,name,email):
		self.name = name
		self.email = email
#Nested解决一对多，多对多 fields.Nested(User)

u = User("name","email")
print(dir(u))
u_s = UserSchema()
r = u_s.dump(u)#dump是字典
print(r,isinstance(r,dict))


exit(0)
r = u_s.dump(u)#dump是字典
print(isinstance(r,dict))
exit(0)

r = u_s.dumps(u,many=False)#dumps是json字符串
print(r,isinstance(r,str))

exit(0)





#json序列化内容
Test.X = 2
t = Test(1,2)
json.dumps(t,default=lambda obj:obj.__dict__)#把类转为json字符串
def dict2student(d):
    return Test(d['name'], d['age'], d['score'])
json_str = '{"age": 20, "score": 88, "name": "Bob"}'
print(json.loads(json_str, object_hook=dict2student))#把json字符串转为实例








exit(0)
#schema
from  schema import  Schema,And,Optional,Use
#1、
Schema(int).validate(10)
#2、
class test:
	def __call__(self, *args, **kwargs):
		print(args)
		return True
	pass
print(Schema(test()).validate(5))#会把5传给的调用参数__call__方法中，若返回True则返回传入数据，否则跑出异常

#3、内置了其它类，and or use等，需要两者都满则则返回
Schema(And(str,test())).validate("5")

#4、传入容器对象（list,tuple,set等）
Schema([int,float]).validate([1,2,3])#对象中任何元素必须是int 或者 float才可以 是or的关系

#5、传入一个字典对象（常用场景）
Schema({'name':str,'age':int}).validate({'name':'222','age':11})#首先验证key 再验证value值的类型

#6、字段数据可选则么么设置
Schema({'name':str,Optional('age'):int}).validate({'name':'222'})#首先验证key 再验证value值的类型,age字段可以不传，可选
#6.1  想让Schema只验证传入字典中的一部分数据，可以有多余的key但是不要抱错，怎么做？
Schema({'name': str, 'age': int}, ignore_extra_keys=True).validate({'name': 'foobar', 'age': 100, 'sex': 'male'})
#6.2 Schema抛出的异常信息不是很友好，我想自定义错误信息，怎么办？
Schema({'name': str, 'age': Use(int, error='年龄必须是整数')}).validate({'name': 'foobar', 'age': 111})
