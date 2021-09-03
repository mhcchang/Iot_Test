#coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、python salachl
	a。在以前的基礎上新增：增刪改查功能，架构重新调整了下,目录如下：
		test_db
			model
				utils 操作目录
				model_table.py 数据库表
			o_table	后面直接封装成这个方法，在这个里面调用
		sqlalchemy基本操作方法:https://www.cnblogs.com/wspblog/p/5998517.html
	b.总结
		1、类实例初始化的时候：
			new(返回值cls.__new())--->init(没有返回值,中的self就是new返回的)
			类、函数、方法以及实例都是对象，并且无论何时你将一对括号放在他们名字后，就会调用他们的__call__:
			python一切都是对象，使用dir()查看包含的值
				自我理解：
					类是抽象的，实例过程是把抽象转化未实际，就是可以直接使用，也可以理解成梦想转为现实
					类就好比是一类事物的抽象，是一个模板，拥有这一类事物的属性和功能。但是对于“人类”这个类来说，每个人的属性和要做的事又是不一样的，
			实例化时.
			class是type的一个对象并且调用__call__ 返回一个class
		2、cls和self
			self标识具体的实例本身。
			cls表示这个类本身
			博客链接：https://blog.csdn.net/mall_lucy/article/details/104489036/
		3、最终结论：
			实例和属性改变值是两回事，互不影响，类始终是模板，最好不要动，直接实例更好
	下次学习：schema 
2、sql
	
	        –1.学生表
		Student(s_id,s_name,s_birth,s_sex) --学生编号,学生姓名, 出生年月,学生性别
		–2.课程表
		Course(c_id,c_name,t_id) – --课程编号, 课程名称, 教师编号
		–3.教师表
		Teacher(t_id,t_name) --教师编号,教师姓名
		–4.成绩表
		Score(s_id,c_id,s_score) --学生编号,课程编号,分数
		11、查询没有学全所有课程的同学的信息 
			SELECT  a.*,COUNT(a.s_id) as co FROM Student a ,Score s WHERE a.s_id =s.s_id GROUP BY a.s_id HAVING co< (SELECT COUNT(*) FROM Course)
			学习到的:group后面和面跟着having可以直接用函数，配合使用
		12、查询至少有一门课与学号为"01"的同学所学相同的同学的信息 
			SELECT DISTINCT a.s_id,a.s_name,a.s_birth,a.s_sex  FROM Student a  LEFT   JOIN Score  s on a.s_id=s.s_id WHERE s.c_id in  (SELECT s.c_id  FROM Student a  LEFT   JOIN Score  s on a.s_id=s.s_id WHERE a.s_id=01 ) and s.s_id!=01 
		13、查询和"01"号的同学学习的课程完全相同的其他同学的信息
		SELECT Customer,OrderDate,SUM(OrderPrice) FROM Orders
GROUP BY Customer,OrderDate
			学习到的：group 
			待解决
'''
def fun(self):
	print("fun")
class c_test():
	def __init__(self):
		print("c_test")
class test(object):
	def __init__(self):#初始化使用
		self.id = 1
		print("init")
	def __call__(cls, *args, **kwargs):#实例对象的对象方法
		print("call")
	def __repr__(self):#只是定义返回的名称而已  实际还是类
		return "%s"%(self.id)
	def __new__(cls, *args, **kwargs):#创建实例前使用，主要添加属性，一般不用
		cls.f = fun#可以定义方法，方法需要加入self
		cls.p = 1 #可以定义变量
		cls.c = c_test #可以定义类
		dir(cls)#查看属性
		return super().__new__(cls)
	def __iter__(self):# @summary: 迭代器，生成迭代对象时调用，__iter__的返回值只要是一个迭代器就行
		return self
	def __next__(self):#把类作为一个迭代器,使其有迭代属性,返回的是一个生成器
		for x in range(1000):
			yield x#yield代表生成器
			print(x)
		pass
	def __enter__(self):#使用with的时候使用，with开始时使用
		pass
	def __exit__(self, exc_type, exc_val, exc_tb):#在使用with的时候 with结束后调用
		pass
	def __str__(self):#重写返回值和—__repr__一样
		return '%1'%(self.id)
	def __eq__(self):#如果这个方法补充协议，默认比较的是内层地址  == 会调用对象的 __eq__ 方法，获取这个方法的比较结果
		return super().__eq__()
	# def __getattr__(self, item):#当调用不存在的属性时访问这个方法
	# 	'''
	# 	t = test()
	# 	t.ss
	# 	:param item:
	# 	:return:
	# 	'''
	# 	# print("__getattr__")
	# 	# return 0
	# 	pass
	# def __setattr__(self, key, value):#通过此方法可以设置key和value值
	# 	# print("__setattr__")
	# 	'''
	#
	# 	:param key:
	# 	:param value:
	# 	:return:
	# 	'''
	# 	pass
	@classmethod
	def t_set(cls):#这个方法可以增加类属性的中的值
		print(cls)
	@property
	def t_p(self):#如果设置这个装饰器则只能读
		return self.id
	@staticmethod#和classmethod类似，如果要改变类的话 但是需要传参数cls
	def s_m(cls):
		print(cls)
		print("111111")
#使用staticmethod装饰器

test.s_m(test)
test.t_set()#用法一样
#共同点：都不要实例化
#不同：staticmethod中如果要传参数则需要传，classmethod第一个参数为cls类本身

exit(0)

#增加property，只读
# test.t_set()
t = test()
# t.t_p = 1000#不能设置
print(t.t_p)

exit(0)

#增加classmethod试验，先改变属性，再实例  结果：还是按照实例中的走
test.t_set()
t = test()
print(t.id)

#改变参数后再实例,改变参数后再实例，就是操作类的本身，增加属性，这个相当于直接改变类，所以部分属性需要@property
t1 = test
# print(t1.id)
t1.id1 =3
t2 = test()
print(t2.id1)

#实例后改变参数，实例完成后 再实例上修改，相当于可变性多
t = test()
print(t.id)
setattr(t,'id',"11111111")
print(t.id)

#先改变类的属性,再实例 结果：是按照实例中的走

s = test
s.id = 100
s1 = test()
print(s1.id)

#先实例改改变类的属性 结果：还是按照实例化的走
s2 = test()
print(dir(s2))
test.id = 1000
print(dir(test))
print(s2.id)