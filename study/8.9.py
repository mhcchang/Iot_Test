#coding:utf-8
'''
author:
function:主要是对于闭包及装饰器进行理解及应用
param:
other
'''

'''
一、定义
	如果再一个函数的内部定义了另一个函数，外部的函数叫它外函数，内部的函数它内函数
	1、闭包条件
			a.在一个外函数中定义了一个内函数。
			b、内函数里运用了外函数的临时变量。
			c、外函数的返回值是内函数的饿引用。
		备注：一般情况下，如果一个函数结束，函数的内部所有东西都会释放掉，还给内存，局部变量都会消失，但是“闭包”是一种特殊情况，如果外函数在结束的时候发现自己的临时变量将在内部函数中用到，就把这个临时变量绑定给了内部函数，然后自己再结束
		A、外函数返回了内函数的引用：(解释了外部函数为什么会返回函数名)
			引用：在python中一切都是对象，函数、数据类型都是对象，所谓引用就是把内存地址转给其它变量
			x---->
			y---->  指向同一个地址------->地址中有存储的值（或代码或数据）[类似于c语言中的指针]
			z---->
			对于一个函数，如果函数名后面跟着一对括号，说明现在就要调用这个函数，如果不跟括号，只是一个函数的名字，里面存了函数所在位置的引用。
		B、外函数把临时变量绑定给函内函数
			外函数里创建了一个函数，我们每次调用外函数，它都创建一个内函数，虽然代码一样，但是却创建了不同的对象，并且把每次传入的临时变量数值绑定给内函数，再把内函数引用返回。虽然内函数代码是一样的，但其实，我们每次调用外函数，都返回不同的实例对象的引用，他们的功能是一样的，但是它们实际上不是同一个函数对象。
			备注：使用locals()函数可以查看，若c没有在内函数中使用到则在外函数在执行完后就会释放此变量，其它两个变量则不会释放。
			{'inner': <function outer.<locals>.inner at 0x7efcd58fb488>, 'c': 1, 'b': 10, 'a': 5}
			{'b': 10, 'a': 5}
	2、闭包中内函数修改外函数局部变量
		在闭包函数中，可以随意使用外函数绑定的临时变量，但是如果修改外函数零食变量则会出现问题
		python中，一个函数可以随意读取全部变量，但是修改则有两种方法：
			a.global 申明全局变量
			b.全局变量是可变类型数据的时候可以修改
　		在闭包内函数也是类似的情况。在内函数中想修改闭包变量（外函数绑定给内函数的局部变量）的时候：			　　1 在python3中，可以用nonlocal 关键字声明 一个变量， 表示这个变量不是局部变量空间的变量，需要向上一层变量空间找这个变量。

　　			  2 在python2中，没有nonlocal这个关键字，可以把闭包变量改成可变类型数据进行修改，比如列表。
ex:
		#a和b都是临时函数变量
		def outer(a):
			b = 10
			c = 1
			def inner():
				print(id(c))
				print(c+1)
			print(id(c))
			print(locals())
			return inner
		if __name__ == '__main__':
			demo = outer(5)#外函数结束的时候会发现内部函数使用到了自己的临时变量，这两个临时变量就不会释放，会绑定给这个背部函数
		
			demo()

闭包用途

3.1 装饰器！装饰器是做什么的？其中一个应用就是，我们工作中写了一个登录功能，我们想统计这个功能执行花了多长时间，我们可以用装饰器装饰这个登录模块，装饰器帮我们完成登录函数执行之前和之后取时间。

3.2 面向对象！经历了上面的分析，我们发现外函数的临时变量送给了内函数。大家回想一下类对象的情况，对象有好多类似的属性和方法，所以我们创建类，用类创建出来的对象都具有相同的属性方法。闭包也是实现面向对象的方法之一。在python当中虽然我们不这样用，在其他编程语言入比如avaScript中，经常用闭包来实现面向对象编程

3.3 实现单利模式！ 其实这也是装饰器的应用。单利模式毕竟比较高大，需要有一定项目经验才能理解单利模式到底是干啥用的，我们就不探讨了。

装饰器：
	作用：主要是在函数执行前或者给函数增加其他功能，类似于公共方法
 1 装饰器的原型
 	在函数遇到@表示先执行下外函数，不需要不需要传入参数
 		ex:
 		import  time
		def showtime(func):
			print("showtime")
			def wrapper(a,b):
				start_time = time.time()
				func(a,b)
				end_time = time.time()
				print('spend is {}'.format(end_time-start_time))
			return wrapper
		@showtime   #foo = showtime(foo)
		def foo(a,b):
			print('foo')
			time.sleep(3)
		foo(1,2)
2 装饰函数
		import  time
		def test(a=0):
			def showtime(func):
				print("showtime")
				def wrapper(a,b):
					start_time = time.time()
					func(a,b)
					end_time = time.time()
					print('spend is {}'.format(end_time-start_time))
				return wrapper
			return showtime
		@test(2)   #foo = showtime(foo)
		def foo(a,b):
			print('foo')
			time.sleep(3)
		foo(1,2)
缺点：
	1.位置错误的代码 不能在装饰器之外添加逻辑功能
	2.不能装饰@staticmethod 或者 @classmethod已经装饰过的方法
	3.装饰器会对原函数的元信息进行更改,比如函数的docstring,__name__,参数列表
注解:wraps本身也是一个装饰器,他能把函数的元信息拷贝到装饰器函数中使得装饰器函数与原函数有一样的元信息
ex:
		import time
		from  functools import wraps
		
		def showtime(func):
			print("showtime")
			@wraps(func)
			def wrapper():
				start_time = time.time()
				func()
				end_time = time.time()
				print('spend is {}'.format(end_time - start_time))
		
			return wrapper
		@showtime
		def foo():
			print('foo')
			time.sleep(3)
		def doo():
			print('doo')
		print(foo.__name__)
		print(doo.__name__)
'''

