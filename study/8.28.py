# coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、学习shell 时间为1小时
	知识点：expect
		定义：expect是一个自动化交互套件，主要应用于执行命令和程序时，系统以交互的形式要求输入指定字符串，实现交互通信。
		交互流程：
			spawn 启动指定进程---expect获取指定关键字---send向指定程序发送指定字符串---执行完成退出
		安装：
			sudo apt install expect
			yum install -y expect
		常用命令：
			spawn               交互程序开始后面跟命令或者指定程序
			expect              获取匹配信息匹配成功则执行expect后面的程序动作
			send exp_send       用于发送指定的字符串信息
			exp_continue        在expect中多次匹配就需要用到
			send_user           用来打印输出 相当于shell中的echo
			exit                退出expect脚本
			eof                 expect执行结束 退出
			set                 定义变量
			puts                输出变量
			set timeout         设置超时时间
					
	知识点：scp
		scp local_file remote_username@remote_ip:remote_folder #从本地复制到远程
		scp -r www.runoob.com:/home/root/others/ /home/space/music/#从远程复制到本地
2、什麽是CI/CD
	持续化集成 持续化交付 持续化测试
	自我理解：就是创建一个job然后这个job作一些以前手工繁琐的事情，比如拉代码 编译 生成镜像之类的，用过cicd可以直接运行job,得到结果，和jenkin差不多。
	
3、Python学习 时间为1小时
	异步IO（大纲）
		3.1 了解协程
			协程：又称微线程,子程序或者成为函数，比如A调用B,B在执行汇总有调用C，C执行完毕返回，B执行完毕返回，最后是A执行完毕
			优势：
				（1）最大的优势就是协程极高的执行效率。因为子程序切换不是线程切换，而是由程序自身控制，因此，没有线程切换的开销，和多线程比，线程数量越多，协程的性能优势就越明显。
				（2）第二大优势就是不需要多线程的锁机制，因为只有一个线程，也不存在同时写变量冲突，在协程中控制共享资源不加锁，只需要判断状态就好了，所以执行效率比多线程高很多。
			协程怎么调用多喝核PU：
				（1）多进程+协程
			python中的协程：
				通过generator生成器实现的
				yield就是 return 返回一个值，并且记住这个返回的位置，下次迭代就从这个位置后开始
				yield from 后面需要加的是可迭代对象，它可以是普通的可迭代对象，也可以是迭代器，甚至是生成器。
				yield 的作用就是把一个函数变成一个 generator，带有 yield 的函数不再是一个普通函数，理解好的博客：
				send方法相当于next(),__next__()只是可以修改参数
							https://www.cnblogs.com/ellisonzhang/p/10273843.html
							https://pyzh.readthedocs.io/en/latest/the-python-yield-keyword-explained.html
		3.2 asyncio（3.4版本）
				学习：https://www.cnblogs.com/lincappu/p/13409912.html
				定义：asyncio的编程模型就是一个消息循环，我们从asyncio模块中直接获取一个EventLoop的引用，然后把需要执行的协程扔到EventLoop中执行，就实现了异步IO。
			自我理解：
					1、对于一个方法如要要执行3此，要不就主线程阻塞遍历，要不就直接开3个线程，但是就效率而言还是一个线程三个异步好。
				await/async(3.5版本)：
					把@asyncio.coroutine替换为async；
					把yield from替换为await。
					备注：如果换了， 运行的时候需要加上asyncio.wait([hello(),hello()]))
				和多线程消耗时间差不多，但是没有锁的风险
		3.3 aiohttp
			asyncio可以实现单线程并发IO操作。如果仅用在客户端，发挥的威力不大。如果把asyncio用在服务器端，例如Web服务器，由于HTTP连接就是IO操作，因此可以用单线程+coroutine实现多用户的高并发支持。
4、学习sql
	创建表：
		CREATE TABLE Student(
		s_id VARCHAR(20),
		s_name VARCHAR(20) NOT NULL DEFAULT '',
		s_birth VARCHAR(20) NOT NULL DEFAULT '',
		s_sex VARCHAR(10) NOT NULL DEFAULT '',
		PRIMARY KEY(s_id)
		)
	题目：1、查询"01"课程比"02"课程成绩高的学生的信息及课程分数	
			a.首先查询课程2比课程1的学生。
			b.再通过学生查询信息。
		SELECT f.s_name,f.s_sex,f.s_id,f.s_birth,f.s_score  FROM ((SELECT Student.s_id,Student.s_sex,Student.s_birth,Student.s_name,Score.s_score FROM Student LEFT JOIN  Score  on  Student.s_id=Score.s_id WHERE Score.c_id=1 )as f)  LEFT JOIN  ((SELECT Student.s_id,Student.s_sex,Student.s_birth,Student.s_name,Score.s_score FROM Student LEFT JOIN  Score  on  Student.s_id=Score.s_id WHERE Score.c_id=2 )as f1)  ON f.s_score > f1.s_score WHERE f.s_id=f1.s_id 
	
'''
#asyncio
import  asyncio,threading,time
from  datetime import  datetime
import threadpool
@asyncio.coroutine
def hello():
	print("hello world")
	time.sleep(10)
	r = yield from asyncio.sleep(1)
	print("hell again!")
loop = asyncio.get_event_loop()

# loop.run_until_complete(asyncio.wait([hello(),hello()]))
# loop.close()

async  def test():
	print("hello world")
	r = await asyncio.sleep(10)
	print("again")
startTime = datetime.now()
s = [  eval("test()")  for x in range(100)]
# loop.run_until_complete(asyncio.wait(s))
# thre =  threadpool.ThreadPool(100)
# req = threadpool.makeRequests(callable_=test, args_list=[x for x in range(100)])
# [thre.putRequest(req) for req in req]
# thre.wait()

endTime = datetime.now()

print("spaend time %s"%(endTime-startTime))








# 使用协程来实现新的生产者消费者
def consumer():
	r = ''
	print("------------")
	while True:
		n = yield r
		if not n:
			return
		print('[CONSUMER] Consuming %s...' % n)
		r = '200 OK'


def produce(c):
	c1 = c.send(None)
	print(c1)
	n = 0
	while n < 5:
		n = n + 1
		print('[PRODUCER] Producing %s...' % n)
		r = c.send(n)
		print('[PRODUCER] Consumer return: %s' % r)
	c.close()

#
# c = consumer()
# produce(c)

