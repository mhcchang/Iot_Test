#coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、弱引用
	许多其它的高级语言一样，Python使用了垃圾回收器来自动销毁那些不再使用的对象。每个对象都有一个引用计数，当这个引用计数为0时Python能够安全地销毁这个对象。
	使用weakref模块，你可以创建到对象的弱引用，Python在对象的引用计数为0或只存在对象的弱引用时将回收这个对象。
'''
import weakref
class T():
	'''
	11
	'''
	def __init__(self):
		self.ip = '1.1.1.1'
	def test(self):
		print(__file__)
	def __del__(self):#调用完成后会销毁这个对象
		print('delele'.format(self))
def callback(reference):#引用回调 当引用已经“死亡”而且不再引用原对象时，这个回调会接受这个引用对象作为参数。这个特性的一种用法就是从缓存中删除弱引用对象。
	print('callback'.format(reference))
t = T()
rf = weakref.ref(t,callback)
del t #删除后再调用这个对象时，会调用回调函数,也不能在调用被引用对象的函数或属性
