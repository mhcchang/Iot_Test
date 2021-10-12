#coding:utf-8
'''
author:
function:主要是对迭代进行学习
param:
other
'''
'''

定义：python中，如果给定一个list或者tuple,我们可以通过for循环来遍历这个list或者tuple,这种遍历我们成为迭代。
解释：迭代操作就是对于衣蛾集合，无论该集合是有序还是无序，我们用for循环总是可以依次去除集合的每一个元素。
	1、有序集合：list/tuple/str/unicode
	2、无序结合：set
	3、无序集合具有key-value对：dict
	迭代是一个动词，它指的是一种操作，在python中就是for循环
什么是可迭代对象：
	一般可迭代对象：str list tuple dic set ,存在__iter__()方法的
为什么我们称他们可可迭代对象？
	遵循了可迭代协议，iterable表示可迭代的.表示可迭代协议
如何看是不是可迭代对象？
	dir(a)--》返回由__iter__标识这个类型是可迭代对象
	__iter__是帮助我们获取到 "对象" 的迭代器.我们使用迭代器中的__next__()来 "获取" 到一个迭代器的元素
	注意: 迭代器不能反复,只能向下执行
区分：
		Iterable: 可迭代对象. 内部包含__iter__()函数        
		Iterator: 迭代器. 内部包含__iter__()【返回迭代对象】同时包含__next__()【获取下一个元素】.
特点：
	1、节省内存。
	2、惰性机智。
	3、不能反复，只能向下执行。
形象的比喻：
	我们可以把要迭代的内容当成子弹，然后呢获取迭代器_iter__(),就把子弹都装在弹夹中，然后发射就是__next__()把每一个子弹（元素）打出来，也就是说，for循环的时候，一开始的时候是__iter__()来获取迭代器，后面每次获取元素都是通过__next__()来完成，当程序遇到StopIteration将结束循环。
示例：
		s = '111'
		l = s.__iter__()
		while True:
			try:
				i = l.__next__()
				print(i)
			except StopIteration:
				break
如何创建一个迭代对象？
	1、iter(list/tuple)
	2、list.__iter()__
	这两者都会返回一个迭代器对象
如何遍历：
	1、for循环直接遍历。
	2、next()或者l.__next__()
类迭代器：
	把一个类作为一个迭代器使用需要在类中实现两个方法__iter__()与__next__()
	_iter__() 方法返回一个特殊的迭代器对象， 这个迭代器对象实现了 __next__() 方法并通过 StopIteration 异常标识迭代的完成

生成器：
	在 Python 中，使用了 yield 的函数被称为生成器（generator）。
	跟普通函数不同的是，生成器是一个返回迭代器的函数，只能用于迭代操作，更简单点理解生成器就是一个迭代器。
	在调用生成器运行的过程中，每次遇到 yield 时函数会暂停并保存当前所有的运行信息，返回 yield 的值, 并在下一次执行 next() 方法时从当前位置继续运行。
	
'''
class T:
	def __init__(self):
		print('')
dir(T)



# print(dir(range))


def func(func):#
	print("")
print(func)#函数名的内存地址
a = func#内存地址不变
print(a)
lst = [func,func]#函数名可以当做容器类的元素
func(func) #函数名可以当做参数

