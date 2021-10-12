# coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、python
	云图相关
2、sql+shell
比较好的学习链接：数据结构	http://data.biancheng.net/view/107.html
	分布式+哈希+链表+etcd+mybits（java框架）
		哈希：https://zhuanlan.zhihu.com/p/63527627
			哈希的英文是Hash,中文可翻译成散列或者哈希，它其实就是一个算法，最简单的算法就是加减乘除，比方，我设计个数字算法，输入+5=输出，比如我输入1，输出为6；输入2，输出为7。
			哈希算法不过是一个更为复杂的运算，它的输入可以是字符串，可以是数据，可以是任何文件，经过哈希运算后，变成一个固定长度的输出，该输出就是哈希值。但是哈希算法有一个很大的特点，就是你不能从结果推算出输入。
		哈希表（散列表）：
			散列表（Hash table，也叫哈希表），是根据关键码值(Key value)而直接进行访问的数据结构。也就是说，它通过把关键码值映射到表中一个位置来访问记录，以加快查找的速度。这个映射函数叫做散列函数，存放记录的数组叫做散列表。
给定表M，存在函数f(key)，对任意给定的关键字值key，代入函数后若能得到包含该关键字的记录在表中的地址，则称表M为哈希(Hash）表，函数f(key)为哈希(Hash) 函数。
			key不能重复
		哈希函数：
			1、是单向函数
		关联：python中的哈希：
			1、字典中的key值就是使用率哈希查找方式，O(1)的时间复杂度。
		
		
		etcd:
			etcd是CoreOS团队于2013年6月发起的开源项目，它的目标是构建一个高可用的分布式键值(key-value)数据库。etcd内部采用raft协议作为一致性算法，etcd基于Go语言实现。
		安装：sudo apt intall etcd
		查看版本：etcdctl -verison
		作用：etcd是一个类似于zk的工具，用于保存值，节点-值这种映射关系的。
		查看集群成员列表：sudo etcdctl member list
		学习链接：		https://www.tizi365.com/archives/557.html
						http://t.zoukankan.com/ilifeilong-p-11625151.html
		小结
			ETCD是个键值存储数据库，主要功能和特点总结如下：
				（1）可对在ETCD上注册的服务进行监控健康状态，并及时反馈
				（2）确保访问ETCD的集群都能正常连接和访问
				（3）应用中用到的一些配置信息放到etcd上进行集中管理
				（4）分布式搜索服务中，索引的元信息和服务器集群机器的节点状态存放在etcd中，供各个客户端订阅使用。
				（5）etcd的核心节点都可以处理用户的请求。
				（6）ETCD监控多个节点，有请求发过来后，根据节点的情况进行分配派发。


'''


# 实现hash表
class HashTable:
	def __init__(self, size):
		self.elem = [None for x in range(size)]
		self.count = size

	def hash(self, key):
		return key % self.count  # 散列函数（也称哈希函数）

	def insert_hash(self, key, value):
		add = self.hash(key)
		while self.elem[add]:
			add = (add + 1) % self.count
		self.elem[add] = value

	def search_hash(self, key):
		star = add = self.hash(key)
		while self.elem[add] != key:
			add = (add + 1) % self.count
			if not self.elem[add] or add == star:
				return False
		return True


# h = HashTable(20)
# h.insert_hash(1,2)
# print(h.search_hash(1))
# l = [None]


class HashTable:
	def __init__(self, size):
		self.elem = [None for i in range(size)]  # 使用list数据结构作为哈希表元素保存方法
		self.count = size  # 最大表长

	def hash(self, key):
		return key % self.count  # 散列函数采用除留余数法

	def insert_hash(self, key, value):
		"""插入关键字到哈希表内"""
		address = self.hash(key)  # 求散列地址
		while self.elem[address]:  # 当前位置已经有数据了，发生冲突。
			address = (address + 1) % self.count  # 线性探测下一地址是否可用
		self.elem[address] = value  # 没有冲突则直接保存。

	def search_hash(self, key):
		"""查找关键字，返回布尔值"""
		star = address = self.hash(key)
		# while self.elem[address] != key:
		# 	print(self.elem[address])
		# 	address = (address + 1) % self.count
		# 	if not self.elem[address] or address == star:  # 说明没找到或者循环到了开始的位置
		# 		return False
		# return True
		if self.elem[star]:
			return True
		else:
			while self.elem[address]:
				address = (address + 1) % self.count
			return False

h = HashTable(20)
for x in range(10):
	h.insert_hash(1,x**2)
print(h.elem)
print(h.search_hash(2))
# import pprint
#
#
# class Hashtable:
# 	def __init__(self, elements):
# 		self.bucket_size = len(elements)
# 		self.buckets = [[] for i in range(self.bucket_size)]
# 		self._assign_buckets(elements)
#
# 	def _assign_buckets(self, elements):
# 		for key, value in elements:
# 			hashed_value = hash(key)
# 			index = hashed_value % self.bucket_size
# 			self.buckets[index].append((key, value))
#
# 	def get_value(self, input_key):
# 		hashed_value = hash(input_key)
# 		index = hashed_value % self.bucket_size
# 		bucket = self.buckets[index]
# 		for key, value in bucket:
# 			if key == input_key:
# 				return (value)
# 		return None
#
# 	def __str__(self):
# 		return pprint.pformat(self.buckets)  # here pformat is used to return a printable representation of the object
#
#
# if __name__ == "__main__":
# 	capitals = [
# 		('France', 'Paris'),
# 		('United States', 'Washington D.C.'),
# 		('Italy', 'Rome'),
# 		('Canada', 'Ottawa')
# 	]
# hashtable = Hashtable(capitals)
# print(hashtable)
# print(f"The capital of Italy is {hashtable.get_value('Italy')}")
