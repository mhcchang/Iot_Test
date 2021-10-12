#coding:utf-8
'''
author:
function:
param:
other
'''
'''
代码题：
	1、写个函数判断两个json字符串是否相同？
		思路:
			a.要判斷key对应的value是什么类型。
			b.使用递归。
	知识点记录：
		a.sorted()  zip(可传入字典)
		b.递归思想
'''
import json
#递归比较
def json_com(src,dest,key =None):
	if isinstance(src,dict):#判断传入的是不是字典
		for key in dest:
			if key not in src:
				print("src key is not exists:" + key)
		for key in src:
			if key in dest:
				json_com(src[key],dest[key],key)
	if isinstance(src,list):#判断传入的是不是列表
		if len(src) != len(dest):
			print('len is not equals')
		for src,dest in zip(sorted(src),sorted(dest)):
			json_com(src,dest)
	else:
		if str(src) != str(dest):#判断字符串是不是相等
			print("key值为: %s:  not equal"%(key))
j1 = {"t":2,"r":3}
j2 = {"t":2,"r":22}
print(json_com(j1,j2))
#简单比较,把json的value值直接转化为字符换，打印出来key值相对于的值
for x,y in (zip(j1,j2)):
	if str(j1[x]) != str(j2[y]) :
		print(x,j1[x],j2[y])

import  random
random.random()
j = [1,2,3,4]
print(random.choice(j))
print(random.randint(1,2000))
print("1111111111111")
class T:
	def __repr__(self):
		print("11")
	def __init__(self):
		print("init")
T()