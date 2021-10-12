# coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、sql学习
	a、group by
		含义：根据 by后面的字段进行分组
		使用注意事项：
				 出现在select后面的字段 要么是是聚合函数中的,要么就是group by 中的. 如果select 的字段多于group by的字段可能会正常运行，但取值会混乱，可以理解为多组值，只取了其中第一条。关系型数据库是不允许这样的，这样就无法形成严格的关系约束条件了，所以会报
				 要筛选结果 可以先使用where 再用group by 或者先用group by 再用having
		单列聚合：
			select a.s_sex,count(a.name) From Student a group by a.sex #标识a.sex下所有a.name有多少个，先把a.sex数据都聚合起来 然后再放到聚合函数中
						表
						id	name	num					虚拟表：id	name	num
						1	aa		n1							1	aa		n1
						2	aa		n2			----->			2			n2	----->产生的虚拟表中，再从aa中聚合数据
						3	bb		n3							3	bb		n3
		多列聚合：
			SELECT  a.s_sex,a.s_name,COUNT(a.s_id) FROM  Student a GROUP BY a.s_sex,a.s_name#把sex和name看做整体的字段，如果有重复将其合并
						表
						id	name	num					虚拟表：id	name	num
						1	aa		n1							1	aa		n1
						2	aa		n1			----->			2				----->产生的虚拟表中，再从aa,n1中聚合数据
						3	bb		n3							3	bb		n3
			
		使用操作：
			聚合函数，就是用来输入多个数据，输出一个数据的，如count(id)， sum(number)，每个聚合函数的输入就是每一个多数据的单元格。
		对应聚合函数：
					Max               求最大
					Min                求最小
					Sum               求总和
	 				Avg                求平均
			 		Count            计算总行数
	b、having
		注意事项：
			1、having 中不能使用未参与分列的组，having 不能替代where 作用不一样，having是对组进行过滤，where是每条记录进行过滤。
			2、having 是对Group By 的条件分组后的数据进行筛选（与where类似，都是筛选，只不过having是用来筛选分组后的组）。
		用法：
			SELECT  a.s_sex,a.s_name,COUNT(a.s_id) FROM  Student a GROUP BY a.s_sex,a.s_name HAVING COUNT(a.s_id) >1
	c、字段链接
		concat
			功能：将多个字符串连接成一个字符串。
			语法1：concat(str1, str2,...)
			返回结果为连接参数产生的字符串，如果有任何一个参数为null，则返回值为null。
			语法2：concat(str1, seperator,str2,seperator,...)
			返回结果为连接参数产生的字符串并且有分隔符，如果有任何一个参数为null，则返回值为null。
			示例：SELECT  a.s_sex,a.s_name,COUNT(a.s_id),CONCAT(a.s_sex,"-",a.s_name) FROM  Student a GROUP BY a.s_sex,
			a.s_name 
		concat_ws
			功能：和concat()一样，将多个字符串连接成一个字符串，但是可以一次性指定分隔符（concat_ws就是concat with separator）
			语法：concat_ws(separator, str1, str2, ...)
			说明：第一个参数指定分隔符。需要注意的是分隔符不能为null，如果为null，则返回结果为null。
			示例：SELECT  a.s_sex,a.s_name,COUNT(a.s_id),concat_ws("-",a.s_sex,a.s_name) FROM  Student a GROUP BY a.s_sex,a.s_name 
		group_concat
			功能：将group by产生的同一个分组中的值连接起来，返回一个字符串结果。
			语法：group_concat( [distinct] 要连接的字段 [order by 排序字段 asc/desc ] [separator '分隔符'] )
			说明：通过使用distinct可以排除重复值；如果希望对结果中的值进行排序，可以使用order by子句；separator是一个字符串值，缺省为一个逗号。
			示例：SELECT  a.s_sex,COUNT(a.s_id),group_concat(a.s_sex,a.s_name) FROM  Student a GROUP BY a.s_sex

	13、查询和"01"号的同学学习的课程完全相同的其他同学的信息
SELECT * FROM  Student as t WHERE  (SELECT GROUP_CONCAT(c_id ORDER BY c_id,"-") as t1  FROM Student a  LEFT JOIN Score s on 
a.s_id=s.s_id WHERE a.s_id=t.s_id  GROUP BY s.s_id)=(SELECT GROUP_CONCAT(c_id ORDER BY c_id,"-")  FROM Student a  LEFT JOIN Score s on a.s_id=s.s_id WHERE a.s_id=01 GROUP BY s.s_id) and t.s_id!=02
2、python
	Iterable:可迭代对象
	前提：函数或者方法中要有可迭代的环境
	可迭代对象：
		dir方法返回存在__iter()__函数,没有__next__方法
		要想使用next(l) 或者l.__next()则需要转为迭代器。
	迭代器：
		内部包含__iter()和__next__()函数
	转换为迭代器：
			通过iter()把可迭代对象转为迭代器，
			迭代器使用next(l)方法
			迭代器使用l.__next__()

	生成器:
		有yield的为生成器，返回生成器对象
		优点：
			1、节省空间。
		理解：
			1、简单版的迭代器，每次返回生成器对象，用户是否要用，如果不用则不取。
		不同：
			1、迭代器如果使用true则都会迭代完成，生成器返回生成器对象给用户。
	类的迭代器生成器：
		1、定义__iter__ __next__(),有三种方式如下
	高级函数：
		变量可以指向函数
		map(f,iterable)  
				python3 返回结果是迭代器，
				返回结果可以使用list()转换
				返回结果可以for
				返回结果可以f1.__next__() 可以使用while 或者for
				返回结果可以next(f1)
3、jmeter报告格式：https://www.cnblogs.com/imyalost/p/10239317.html
4、shell
	1、SHELL8 统计所有进程占用内存大小的和
	


'''
from functools import wraps

def ext(func):#
	@wraps(func)
	def wrapper(*args,**kwargs):
		return  func(*args,**kwargs)
	return wrapper
class t:
	def __init__(self):
		print("1111")
	@ext
	def test(self):
		print("2111111111")

t().test()
exit(0)
s = '1234'
class test:
	def __init__(self):
		self.id = 0
	def __iter__(self):
		print("iter")
		return self
	def __next__(self):
		#第一种写法
		self.id = self.id +1
		return  self.id
		#第二种写法
		# while True:
		# 	if self.id<100:
		# 		self.id = self.id + 1
		# 		return self.id
		# 	else:
		# 		break
		#第三种写法 使用yield返回生成器，返回后的生成器再调用__next__即可（注意第二次调用next则不是这个类的next）
		# self.id = self.id +1
		# yield self.id
t = test()
l = list()
for x in range(100):
	l.append(t)
def t(x):
	print(type(x))
	setattr(x,'tt','tttt')
	return x

#使用map 给迭代器修改
m = map(t,l)
print(m.__next__().tt)




# for x in l:
# 	print(x.__next__())
# for x in [ t for x in range(100)]:
# 	print(x.__next__())
# while True:
# 	try:
# 		t.__next__()
# 	except StopIteration:
# 		break


exit(0)
def f(x):
	return x+"0"
f1 = list(map(f,s))#list(iterable) -> new list initialized from iterable's items ,
print(f1)
exit(0)
while True:
	try:
		print(f1.__next__())#使用迭代器的方法 或者next(f1)
	except StopIteration:
		break

exit(0)
def test():
	print("test")
def t(f1,f2):
	f2()
	print(f1)
t(1,test)

exit(0)
# 实现伪装的for函数
class for_all:
	@property
	def get_iter(self):
		return self

	@classmethod
	def for_iter(cls, it):
		it = iter(it)
		while True:
			try:
				print((cls.__name__))
				# print(id(it.__next__()))
				yield next(it)
			except StopIteration:
				break


s = [1, 2, 3, 4]
for x in (for_all.for_iter(s)):
	print(x)
exit(0)
for x in s:
	print(x)
exit(0)
s = set()
print(dir(s))
