#coding:utf-8
'''
author:
function: 主要对于python异常学习
param:
other
'''
'''
什么是异常：
	异常即是一个事件，该事件会在程序执行过程中发生，影响程序的正常执行。
异常处理：
		try/except语句用来检测try语句块中的错误，从而让except语句捕获异常信息并处理
	一般用法：try....except....else
		try:
			语句
		except <名字>：
			语句：发生异常执行此代码
		else：
			语句：如果没有异常执行此代码
用法场景
	1、使用except而不带任何异常类型：
		try:
			正常操作
		except:
			发生异常，执行此代码
		else:
			如果没有异常，执行此代码
	缺点：try-except语句捕获所有发生的异常，不能识别具体信息。
	2、使用except而带有多种异常类型
		try:
			正常操作
		except(Exception1[,Exception2..]):
			发生异常，执行此代码
		else:
			如果有异常执行此代码
	3、try-finally
		try:
			正常操作
		finally:
			退出try总会执行
		raise
raise:
		语法：
			raise [exceptionName [(reason)]]
			其中，用 [] 括起来的为可选参数，其作用是指定抛出的异常名称，以及异常信息的相关描述。如果可选参数全部省略，则 raise 会把当前错误原样抛出；如果仅省略 (reason)，则在抛出异常时，将不附带任何的异常描述信息。
		raise：单独一个 raise。该语句引发当前上下文中捕获的异常（比如在 except 块中），或默认引发 RuntimeError 异常。	
		raise 异常类名称：raise 后带一个异常类名称，表示引发执行类型的异常。
		raise 异常类名称(描述信息)：在引发指定类型的异常的同时，附带异常的描述信息。
'''
# a = input()
# try:
# 	if int(a) == 0:
# 		raise ValueError('1')
# except RuntimeError as e:
# 	raise
class T:
	def test(self):
		print('111')
	def t(cls):
		cls.test()
T().t()