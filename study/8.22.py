# coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、记录一道牛客网题目的解答方式

描述
	计算字符串最后一个单词的长度，单词以空格隔开，字符串长度小于5000。

输入描述：
	输入一行，代表要计算的字符串，非空，长度小于5000。

输出描述：
	输出一个整数，表示输入字符串最后一个单词的长度。

示例1
输入：	
	hello nowcoder
输出：
	8
说明：
	最后一个单词为nowcoder，长度为8
'''
'''
思路：
	1、首先把字符串最后的空格去掉。
	2、从后面开始往前面遍历，如果遇到空格就退出（这种情况是字符串之间含有空格）长度小于0就退出（这种情况是字符串中没有空格）

'''

class Solution:
	def lengthOfLastWord(self, s: str) -> int:
		s = s.rstrip()
		l = len(s)
		count = 0
		while l-1>=0:
			if s[l-1] == ' ':
				break
			else:
				l -= 1
				count +=1
		return count
# f = open()
# f.read()
print(Solution().lengthOfLastWord("day"))
#python 基础
'''
1、io编程
	定义：IO在计算机中指Input/Output，也就是输入和输出。由于程序和运行时数据是在内存中驻留，由CPU这个超快的计算核心来执行，涉及到数据交换的地方，通常是磁盘、网络等，就需要IO接口。分类有同步io，异步io
					同步io:编程简单，逻辑简单
					异步io:复杂度高于同步io
	1.1 文件操作
		在磁盘上读写文件的功能是由操作系统提供的。
		open()
		with  open as f :
			f.read()
		像open()函数返回的这种有个read()方法的对象，在Python中统称为file-like Object。除了file外，还可以是内存的字节流，网络流，自定义流等等。file-like Object不要求从特定类继承，只要写个read()方法就行。
	1.2  StringIO 和BytesiO
		StringIO顾名思义就是在内存中读写str。
		StringIO操作的只能是str，如果要操作二进制数据，就需要使用BytesIO。
	1.3  序列化
		序列化：我们把变量从内存中变成可存储或传输的过程称之为序列化，在Python中叫pickling，在其他语言中也被称之为serialization，marshalling，flattening等等，都是一个意思。
		反序列化：把变量内容从序列化的对象重新读到内存里称之为反序列化，即unpickling
		json.dumps()---序列号
		json.loads()---反序列号
		可以操作对象，
		print(json.dumps(s, default=lambda obj: obj.__dict__))
		def dict2student(d):
   			 return Student(d['name'], d['age'], d['score'])
		print(json.loads(json_str, object_hook=dict2student))
		小知识：obj.__dict__返回对象中的属性
2、常见内置模块
	2.1 datetime
		处理日期和时间的标准库
		from datetime import datetime
		datetime.now()#获取当前时间
		
		#用指定日期转时间戳
		dt = datetime(2015,4,19,12,20)
		dt.timestamp()#表示秒,表示毫秒则处理1000
		
		#timestamp转日期
		datetime.fromtimestamp(t)
		
		str转datetime
		datetime.strtime(str, '%Y-%m-%d %H:%M:%S')
		
		datetime转str
		(datetime.now().strftime('%a, %b %d %H:%M')
		
		获取utc时间：
		 utc_dt = datetime.utcnow().replace(tzinfo=timezone.utc)
	2.2 
3、常见第三方模块
	3.1	psutil
		获取服务器信息（linux）
		import  psutil
		print(psutil.cpu_count()) # CPU逻辑数量
		print(psutil.cpu_count(logical=False)) # # CPU物理核心
		
		
		print(psutil.cpu_times()) # # 统计CPU的用户／系统／空闲时间：
		print(psutil.cpu_percent(interval=1, percpu=True)) #再实现类似top命令的CPU使用率，每秒刷新一次，累计10次：
		
		
		print(psutil.virtual_memory()) #使用psutil获取物理内存和交换内存信息：
		print(psutil.swap_memory()) #使用psutil获取物理内存和交换内存信息：
		
		print(psutil.disk_partitions()) #磁盘分区信息
		print(psutil.disk_usage('/')) #磁盘分区信息
		print(psutil.disk_io_counters()) #磁盘I
'''


