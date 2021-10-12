#coding:utf-8
'''
author:
function: 对于python内置函数进行学习
param:
other
'''
'''
链接：https://www.cnblogs.com/wangxiongbing/p/9818337.html
seq 是python内置类型，三种基本的Sequence Type是list（表），tuple（定值表，或翻译为元组），range（范围）  set
1、反射相关
	hasattr 根据字符串的形式去判断对象中是否有此成员，此处的成员是方法
		ex：hasattr(object,name)
	getattr  根据字符串的形式，去对象中找成员,返回成员的类型，此处的成员是方法
		ex: getattr(object,name,default)
	setattr 根据字符串的形式，动态的设置一个成员（在内存中）（三个参数，第一个参数要设置的变量，第三个参数要设置的值）,主要是设置变量，不能设置方法
		ex:setattr(object,name,value)
	delattr  根据提供的值进行属性删除
		ex: delatr(object,name)
2、基础数据类型相关
	bool  布尔类型，True False,一般用于isinstance type比较实用
	bool() 布尔函数：把传入的参数转为bool类型，用处不大
	
	int  整数类型：1,2,3,4....,一般用于isinstance type比较实用
	int() 整形函数：将传入的参数转为整形
	
	float 浮点类型：1.001001.... ,一般用于isinstance type比较实用
	float() 浮点类型函数：将传入参数换位浮点类型
	
	complex  复数类型：用处少
	comple() 复数函数：
	
	bin()  函数：将整型转为二进制，bin(int)
	
	oct() 函数：将整型转为八进制,oct(int)
	
	hex() 函数：整型转为十六进制，hex(int)
	
	abs() 函数：求绝对值  abs(x)
	
	divmod() 函数：除/余数  没用过
	
	round()  函数：取小数点后几位  round(number, ndigits=None)  ndigits取多少位 round(1.222,3) 取小数点后3为
	
	pow() 函数：幂运算   pow(2,3) 2的三次方
	
	sum() 函数：求和 sum(迭代器类型) sum([1,2,3])  sum({1,2,3}  sum((1,2,3)) sum(可以迭代的class)
	
	max() 函数：求最大值   max(*args) 使用max(1,2,3)
	
	min()  函数：求最小值  min(*agrs) 使用min(1,2,3)
	
	list() 函数:  将序列化参数转为列表，list(seq={})  list({1,2,3}) 
	
	tuple() 函数： 将序列化参数转为列表，list(seq={})  list({1,2,3}) 
	
	reversed() 函数： 返回反向的迭代器对象(list/dict/tuple/set/)。      重点关注
	
	slice() 函数：切片  slice(start, end, step) 字符串使用
	
	str() 函数：转为字符串
	
	bytes  二进制数据类型,一般用在isinstance
	bytes() 函数：转为bytes  
	
	bytearry:待研究
	
	memoryview:待研究
	
	ord(): 函数主要返回对应字符串的ASCII码  __c代表字符    ord('a')--->97  ,
	
	chr():函数主要标识ascil码对应的字符，输入可以是数字，可以是十进制，也可以是16进制
	
	ascii():函数 主要是将任何对象（字符串/列表/数组等）返回转义字符   ，没用过
	
	repr()：函数将对象转化为供解释器读取的形式且返回一个string对象格式。repr(__object)---此方法以后可以把列表/字典/对象转为字符串
	
	dict():初始化一个字典，或者把字典字符串转为字典,dict(seq=None)
	
	set():初始化一个集合,set(seq=())
	
	frozenset():返回一个冻结的集合，　冻结后集合不能再添加或删除任何元素,frozenset()
	
	len():获取长度集合,传入__object,len(__object)
	
	sorted():函数对于可迭代的对象进行排序操作，								重点关注
								sorted(iterable,key=None,reverse=False)
									iterable  可迭代对象。
									key  主要是用来进行比较元素，只有一个参数，具体的函数的参数
									reverse -- 排序规则，reverse = True 降序 ， reverse = False 升序（默认）
									示例：
										array = [{"age":20,"name":"a"},{"age":25,"name":"b"},{"age":10,"name":"c"}]
										array = sorted(array,key=lambda x:x["age"])
			和list区别：
								sort 是应用在 list 上的方法，sorted 可以对所有可迭代的对象进行排序操作。

								list 的 sort 方法返回的是对已经存在的列表进行操作，而内建函数 sorted 方法返回的是一个新的 list，而不是在原来的基础上进行的操作     重点关注
	enumerate():枚举函数用于将一个可遍历的数据对象（如列表、元祖或字符串）组合为一个索引序列，同时列出数据和数据下表，一般在for循环中使用。
				enumerate（sequence,[start=0]） 返回索引序列
									示例：
										test = [1,2,3,4]
										print(list(enumerate(test)))
										for i,element in enumerate(test):
											print(i,element)
	zip():函数用于将可替代的对象作为参数，将对象中的对应元素打包成一个元祖，然后返回由这些元祖组成的列表
				zip([iterable,....])
				备注：若传入多个列表则以最短列表长度为准
									示例：
										l1 = [1,2,34]
										z = zip(l1)
										for x in z:
											print(x)
	filter():函数接收一个函数f和一个list，这个函数f的作用是对于每个元素进行判断，返回True 或者False,filter()根据结果自动过滤掉不符合条件的元素，返回符合条件原素组成新的list--------------->python3.x 返回迭代器  python2.x 返回列表
				filter(__funtion__,__iterable__)
									示例：
										l1 = [1,2,34]
										print(list(filter(lambda x: x>2,l1)))
	
	map():函数应用于每一个可迭代的项，返回接口是迭代对象，map接收参数一个是函数，一个是序列
				map(__func__,__iterable)	
									示例：
										test = [1,2,3,4]
										print(list(map(lambda x:x**2,test)))		
	eval(): 函数用来执行一个字符传表达式，并返回表达式的值。
				eval(expression[, globals[, locals]]):
									示例：
										eval('3**2')
										>>9
3、作用域相关
	locals() :获取执行方法所在命名空间的局部变量字典。
	globals():获取全局变量字典
4、面向对象相关
	type  元类，类的最高层
	object 对象
	classmethod  修饰符对应的函数不需要实例化，不需要 self 参数，但第一个参数需要是表示自身类的 cls 参数，可以来调用类的属性，类的方法，实例化对象等。
				备注：cls代表的是类的本身，相对应的self则是类的一个实例对象。
				示例：
					class A(object):
								bar = 1
								def __init__(self):
									print("__Init__")
								def func1(self):
									print('foo')
								@classmethod
								def func2(cls):
									print('func2')
									print(cls.bar)
									cls().func1()
					A.func2()#func2不需要实例化,因此不走init
				>>>func2
				>>>1
				>>>__Init__
				>>>foo
	
	property　是可定义只读属性,就是真正意义上的私有属性(属性前双下划线的私有属性也是可以访问的
				示例：
				class A(object):
							@property
							def fun(self):
								print("111")
				print(A().fun)
	staticmethod  该方法不强制要求传递参数，
				示例：
					class C(object):
							@staticmethod
							def f():
								print('runoob');
					C.f();  # 静态方法无需实例化
					cobj = C()
					cobj.f()  # 也可以实例化后调用
	super　　类继承及方法重写
	
	issubclass  	检查第一个参数是否是第二个参数的子子孙孙类    
	
	isinstance   检查第一个参数(对象) 是否是第二个参数(类及父类)的实例.
5、迭代器/生成器相关  后续深入了解
	next():返回迭代器的下一个项目。函数要和生成迭代器的 iter() 函数一起使用。
		next(iterable[, default])
	iter():函数用来生成迭代器。
		iter(object[, sentinel])
	range():是一个生成器,他只用来存储数据的生成方式,而不直接存储数据
6、其它
	exec():动态执行python代码。也就是说exec可以执行复杂的python代码，而不像eval函数那样只能计算一个表达式的值
		返回值：永远是None
		拓展：
				eval()函数和exec()函数的区别：
					eval()函数只能计算单个表达式的值，而exec()函数可以动态运行代码段。
					eval()函数可以有返回值，而exec()函数返回值永远为None。
	complie():compile(source, filename, mode, flags=0, dont_inherit=False, optimize=-1)
		source：字符串或AST对象，表示需要进行编译的python代码
		filename：指定需要编译的代码文件，如果不是文件读取代码则传递一些可辨认的值。
					mode：用于标识必须当做那类代表来编译；如果source是由一个代码语句序列组成，则指定mode=‘exec’，如果source由单个表达式组成，则指定mode=‘eval’；如果source是由一个单独的交互式语句组成，则指定modo=‘single’。必须要制定，不然肯定会报错。
							s = """              #一大段代码
					for x in range(10):
						print(x, end='')  
					print()
					"""
					code_exec = compile(s, '<string>', 'exec')   #必须要指定mode，指定错了和不指定就会报错。
					code_eval = compile('10 + 20', '<string>', 'eval')   #单个表达式
					code_single = compile('name = input("Input Your Name: ")', '<string>', 'single')   #交互式
					a = exec(code_exec)
					b = eval(code_eval)
					c = exec(code_single)
					d = eval(code_single)
					print('a: ', a)
					print('b: ', b)
					print('c: ', c)
					print('d: ', d)
	callable():检测一个对象是否能被调用
				callable(_obj)
	dir()： 函数不带参数时，返回当前范围内的变量、方法和定义的类型列表；带参数时，返回参数的属性、方法列表。如果参数包含方法__dir__()，该方法将被调用。如果参数不包含__dir__()，该方法将最大限度地收集参数信息。
			dir()
	
'''

s = '111'


exit(0)

print(dir())


# f = frozenset([1,2,3,4])

# print(list(enumerate(test)))
# print(len(test))
# print(f)
# set()
# dict()
rs=repr({"11":222})
print(type(rs))
print(chr(0x22))
ts = [1,2,3,4]
isinstance(ts,bytes)
bytes(111)
t = 11
# print(isinstance(t,int))

print(pow(2,3))

class Test():
	def __init__(self):
		self.ip='11'
	def ip(self):
		pass
# print((getattr(Test,'ip',"11")))
# setattr(Test,'t','1')
# print(Test().__getattribute__('t'))
# print(type(getattr(Test,'t',"11")))

# print(delattr(Test,'ip'))
# print(hasattr(Test,'ip'))
