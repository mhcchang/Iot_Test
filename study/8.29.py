# coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、python学习 1小时
	知识点：面向对象高级编程	数据分装、继承和多态姿势面向对象程序设计中最基础的三个概念，在python中，面向对象还有还多高级特性。
		a、使用__slots__
			定义一个特殊的__slots__变量，来限制该class实例能添加的属性
			__slots__定义的属性仅对当前类实例起作用，对继承的子类是不起作用的
			1.实例可以绑定属性和方法(不影响下一个实例对象），

			2.实例绑定方法（s.set_age=MethedTypes(function,s)），
			
			3.也可以绑定在类上面(Student.set_age=set_age),
			
			4.__slots__=()添加可赋值的变量
		b、@property
			@property装饰器就是负责把一个方法变成属性调用的
			默认用@property是只读属性，如果先限制的花使用setter，getter,主要是对于数据的一些操作
		c、多重继承
			其实按照继承的list进行寻找，如果父类中有相同的方法则 按照MRO列表选择第一个父类，如果没有则可以正常调用
		d、定制类
			1、__str__()返回用户看到的字符串，而__repr__()返回程序开发者看到的字符串，也就是说，__repr__()是为调试服务的
			2、如果一个类想被用于for ... in循环，类似list或tuple那样，就必须实现一个__iter__(
			)方法，该方法返回一个迭代对象，然后，Python的for循环就会不断调用该迭代对象的__next__()方法拿到循环的下一个值，直到遇到StopIteration错误时退出循环。
			3、要表现得像list那样按照下标取出元素，需要实现__getitem__()方法
			4、__getattr__()方法，动态返回一个属性
					注意，只有在没有找到属性的情况下，才调用__getattr__，已有的属性，比如name，不会在__getattr__中查找。
			5、只需要定义一个__call__()方法，就可以直接对实例进行调用
				那么，怎么判断一个变量是对象还是函数呢？其实，更多的时候，我们需要判断一个对象是否能被调用，能被调用的对象就是一个Callable对象，比如函数和我们上面定义的带有__call__()的类实例
		e、枚举类
			from enum import Enum
			Month = Enum('Month', ('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'))
			这样我们就获得了Month类型的枚举类，可以直接使用Month.Jan来引用一个常量
			.value取值
		f、元类(ORM后续作为学习对象)
			但是如果我们想创建出类呢？那就必须根据metaclass创建出类，所以：先定义metaclass，然后创建类
			ORM全称“Object Relational Mapping”，即对象-关系映射，就是把关系数据库的一行映射为一个对象，也就是一个类对应一个表，这样，写代码更简单，不用直接操作SQL语句
2、sql
	练习题：https://blog.csdn.net/fashion2014/article/details/78826299/
		–1.学生表
		Student(s_id,s_name,s_birth,s_sex) --学生编号,学生姓名, 出生年月,学生性别
		–2.课程表
		Course(c_id,c_name,t_id) – --课程编号, 课程名称, 教师编号
		–3.教师表
		Teacher(t_id,t_name) --教师编号,教师姓名
		–4.成绩表
		Score(s_id,c_id,s_score) --学生编号,课程编号,分数
	2、查询"01"课程比"02"课程成绩低的学生的信息及课程分数
		SELECT f.s_name,f.s_sex,f.s_id,f.s_birth,f.s_score  FROM ((SELECT Student.s_id,Student.s_sex,Student.s_birth,Student.s_name,Score.s_score FROM Student LEFT JOIN  Score  on  Student.s_id=Score.s_id WHERE Score.c_id=1 )as f)  LEFT JOIN  ((SELECT Student.s_id,Student.s_sex,Student.s_birth,Student.s_name,Score.s_score FROM Student LEFT JOIN  Score  on  Student.s_id=Score.s_id WHERE Score.c_id=2 )as f1)  ON f.s_score < f1.s_score WHERE f.s_id=f1.s_id 
	3、查询平均成绩大于等于60分的同学的学生编号和学生姓名和平均成绩
		ROUND 函数用于把数值字段舍入为指定的小数位数。
		-- 
		SELECT s.*,av.a FROM  Student AS s LEFT JOIN  (SELECT  Score.s_id, (AVG(Score.s_score)) as a FROM Score GROUP BY Score.s_id) as av on s.s_id=av.s_id  WHERE  av.a>60  and av.a is not NULL
		-- 
		SELECT s.*,av.a FROM  Student AS s LEFT JOIN  (SELECT  Score.s_id, (AVG(Score.s_score)) as a FROM Score GROUP BY Score.s_id HAVING a>=60) as av on s.s_id=av.s_id  WHERE  av.a is not NULL
	-- 4、查询平均成绩小于60分的同学的学生编号和学生姓名和平均成绩
			-- (包括有成绩的和无成绩的)
			-- 
				SELECT s.*,av.a FROM  Student AS s LEFT JOIN  (SELECT  Score.s_id, (AVG(Score.s_score)) as a FROM Score GROUP BY Score.s_id HAVING a<60) as av on s.s_id=av.s_id  WHERE  av.a is not NULL   UNION (SELECT Student.*,0 FROM Student ,Score as c WHERE Student.s_id not in (SELECT DISTINCT  s_id   FROM Score))
		5、查询所有同学的学生编号、学生姓名、选课总数、所有课程的总成绩
		SELECT  s.s_id,s.s_name, COUNT(*) as total,SUM(c.s_score) FROM  Student as s LEFT JOIN Score AS c  on s.s_id=c.s_id GROUP BY s_id ,s.s_name
		6、查询"李"姓老师的数量 
			SELECT COUNT(*)  FROM Teacher as t WHERE  t.t_name LIKE "li%"
		7、查询学过"张三"老师授课的同学的信息 
			SELECT Student.* FROM Student, (SELECT   Teacher.t_id,Teacher.t_name,fc.c_id,fc.s_id  FROM Teacher,(SELECT Course.t_id,Score.s_id,Score.c_id FROM Score  LEFT JOIN Course  on Course.c_id=Score.c_id ) as fc WHERE fc.t_id=Teacher.t_id  and Teacher.t_name="zhangsan") AS c WHERE Student.s_id=c.s_id
3、shell	
	shell脚本练习:https://www.nowcoder.com/ta/shell?from=baidushell&bd_vid=8735837109190312598
	set 指令可根据不同的需求来设置当前所使用 shell 的执行方式.
	set：初始化位置参数
	如果不带任何参数的使用 set 命令，set 指令就会显示一列已设置的 shell 变量，包括用户定义的变量和关键字变量
	1、写一个 bash脚本以输出一个文本文件 nowcoder.txt中的行数
			line=0
			while read value
			do
			let line+=1
			done
			echo $line
		awk:NR是文本文件的行数，NF是一个文本文件中一行中的字段个数 awk "{print NR}" 
		tail: 
			-f	循环读取
			-q 不显示处理信息
			-n 显示文件尾部第多少行内容
		read:链接：https://www.runoob.com/linux/linux-comm-read.html
		标准输入输出：https://www.cnblogs.com/chengmo/archive/2010/10/20/1855805.html
	2、打印文件的最后5行
		tail -n +5 git.sh
		思路：使用数组，遍历数组，最后6行即可
		line=0
		array=()
		while read value
		do
		array[$line]=$value
		let line+=1
		done
		count=0
		for(( i=0;i<${#array[@]};i++)) do
		let c=${#array[@]}-i
		if [ ${c} -lt 6 ];then
			echo ${array[$i]};
		fi
		done;
		
'''

# python
class baseM():
	print("11")
class sub(baseM):
	def __init__(self):
		print("22")
sub()

exit(1)
class ListMetaClass(type):
	def __new__(cls,name,bases,attrs):
		attrs['add'] = lambda self,value:self.append(value)
		return type.__new__(cls,name,bases,attrs)
class mylist(list,metaclass=ListMetaClass):
	pass
l = mylist()
l.add(1)
print(l)

exit(0)

from enum import Enum, unique

Month = Enum('Month', ('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'))


@unique
class Weekday(Enum):
	Sun = 0  # Sun的value被设定为0
	Mon = 1
	Tue = 2
	Wed = 3
	Thu = 4
	Fri = 5
	Sat = 6
print(Weekday.Sun.value)


# class Student(object):
# 	pass
#
#
# s = Student()
# from types import MethodType
#
#
# # 可以绑定属性
# def test(self):
# 	print("test")
#
#
# s.t = MethodType(test, s)
# (s.t())

class Student(object):

	@property
	def score(self):
		return self._score

	@score.setter
	def score(self, value):
		print("setter")
		if not isinstance(value, int):
			raise ValueError('score must be an integer!')
		if value < 0 or value > 100:
			raise ValueError('score must between 0 ~ 100!')
		self._score = value
		self._age = 1111

	@property
	def age(self):
		return self._age

	def __str__(self):
		return "%s----" % self.__class__

	def __iter__(self):
		return self

	def __next__(self):
		self.i = 10
		return self.i

	def __getitem__(self, n):
		a, b = 1, 1
		for x in range(n):
			a, b = b, a + b
		return a

	def __getattr__(self, attr):
		if attr == 'ttt':
			return lambda: 25


# def __call__(self, *args, **kwargs):
# 	print("call")


s = Student()
print(callable(s))
print(s[2])
print(s.ttt)
print(type(s))


# s.score = 60
# print(s.score)
# print(s.age)
class Chain(object):

	def __init__(self, path=''):
		self._path = path

	def __getattr__(self, path):
		return Chain('%s/%s' % (self._path, path))

	def __str__(self):
		return self._path

	__repr__ = __str__


print(Chain().status.user.timeline.list)
