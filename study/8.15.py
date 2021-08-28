# coding:utf-8
'''
author:
function:1、对于多线程及多进程进行详细学习
param:
other
'''
# 多线程启动的时候，本来就有一个进程，进程里面本身就有有一个线程，然后我有启动了10个线程，所有共有11个线程
# 进程里面本来的线程交主线程，主线程的任务时执行代码
# 子线程就是执行我们手动设置的10个线程的代码，所以运行时间只有0.002是因为打印的是主线程的时间
# 线程之间是互不影响的
# 跟cpu有关，cpu是几核，就能同时运行几个线程
# python里面多线程，连多喝cpu也利用不了，但看起来的确是同时运行的。
# d多线程利用不了多核cpu，多事多进程可以
# 多线程里面，每个线程的数据都是共享的，多进程里面，每个进程之间的数据是疏离的

# 多进程：cpu密集型任务
# 多线程：io密集型任务
#
'''

1、threading文件中含有以下几种类：
操作链接：https://blog.csdn.net/l835311324/article/details/86608850
	Thread类
	方法类：
		threading.current_thread()	#获取当前线程信息
	对象数据属性：
			name	线程名
			ident	线程的标识符
			daemon	布尔类型，表示这个进程是否是守护进程
		thread = threading.Thread(target=function_name,(args1,args2....)) #初始化线程函数
		thread.run()	#此线程开始运行
		thread.run()	#定义线程功能的方法，在子类中被开发者重写，线程启动时会自动调用此方法
		thread.join(timeout=None)	#直至启动的线程终止之前会一直挂起,除非给出timeout秒，否则会一直阻塞
		thread.getName()	#返回线程名
		thread.setName()	#设置线程名
		isAlivel/is_alive()	#布尔标志，标识这个线程是否还存活
		isDeamon()			#是否是守护进程
		setDaemon(deamoic)	#把线程守护标志设定为布尔值，必须要在start()之前调用
		注意：多个线程的时候，调用start()
		使用方法：
			1、直接调用初始化Tread()实例。
			2、集成threading.Thread
	LOCK类
		对象方法：
			lock = threading.Lock()	#初始化锁
				lock.acquire()  #获取锁(阻塞或非阻塞)
				lock.release()	#释放锁
		缺点:耗费CPU资源
	Condition类
		对象方法：
			acpurie()	#获取锁
			release()	#释放锁
			wait()	#将当前线程处于等待状态，并释放锁，可以被其它线程使用notify和notify_all函数唤醒，被唤醒后继续等待上锁，上锁后继续执行下面代码
			notify()	#通知正在等待的某个进程，默认是第一个等待的进程
			notify_all()	#通知所有正在等待的现场，notify和notify_all不会释放锁，并且在release()之前调用
	
	
2、线程池
链接：https://www.cnblogs.com/xiaozi/p/6182990.html
		threadpool:
			threadpool文件中有四个类：（需要单独安装）
					__all__ = [
						'makeRequests',
						'NoResultsPending',
						'NoWorkersAvailable',
						'ThreadPool',
						'WorkRequest',
						'WorkerThread'
					]
			线程池使用到了ThreadPool这个类(本质上还是集成了threading.Thread)：
				task_tool = threadpool.ThreadPool(3) #创建线程池
					req = threadpool.makeRequests(callable_=t_pool, args_list=[1,1,1], callback=pool_callback,exc_callback=exe_b) #创建线程池处理的任务
					[task_tool.putRequest(req) for req in  req]	#将线程加入到队列
					task_tool.wait()	#阻塞进行
		ThreadPool:https://www.jianshu.com/p/b9b3d66aa0be
				T = ThreadPoolExecutor(max_workers=5) #创建最大线程数
					f = T.submit(test_lock,(T._thread_name_prefix)) #执行线程，submit是非阻塞方法 
						可使用add_done_callback()作为回调函数-->回调函数中可以调用result()/exception等方法
					f.done() #判断任务是否结束
					f.cancle() #取消提交的任务
				as_completed(seq) #获取结果
					#from  concurrent.futures import  ThreadPoolExecutor,as_completed,wait 
					for x in range(5):
						s = T.submit(test_lock,(T._thread_name_prefix))
						task.append(s)
					for x in as_completed(task):
						print(x.result())
				map() 获取结果
							def get_html(times):
								time.sleep(times)
								print("get page {}s finished".format(times))
								return times
							
							executor = ThreadPoolExecutor(max_workers=2)
							urls = [3, 2, 4] # 并不是真的url
							
							for data in executor.map(get_html, urls):
								print("in main: get page {}s success".format(data))
				
				wait()	#让主线程阻塞
					wait(fs)#执行task任务的集合列表
			备注：使用回到函数和获取结果互斥，返回对象只能用一次
					
					
	区别：
		标准库提供为我们提供了concurrent.futures模块，它提供了ThreadPoolExecutor和ProcessPoolExecutor两个类，实现了对threading和multiprocessing的进一步抽象
		threadpool线程池子，直接开线程
		ThreadPool 异步执行的线程池,使用了队列
	学习总结：
		1、ThreadPool使用了队列模式模式，底层还是用的threading.Thread
		2、TreadPool这个类重写了_base.Executor类中的submit方法，返回的值是Executor的对象，在源码中return f，很好的解决了互锁问题，因为内部会判断锁子，一般不需要人为设置。
		3、首先创建_WorkItem对象加入到队列中，然后再创建进程，在进程中把刚才队列中对象取出，然后进行运行run方法，运行结果也放在队列里面，每次运行结束后就唤醒其它的所有锁，使用condition.
		4、取结果用as_completed，若线程阻塞则yield,使用的队列是先进先出。
	注意：进程池由于GIL问题无法利用多核CPU
		
进程池：
	使用方法 map,submit,add_done_callback,result，用法ThreadPool相似都是继承_base.feature

		
	
'''

# 生产者与消费者使用互锁典型例子
# 作为threading库的例子
# producter用于赚钱，并且规定每个线程只需要工作10此即可，customer用于消费
import threading, random, time

gMoney = 1000
gCondition = threading.Condition()
gTotalTimes = 2
gTime = 0
print("threading-------start ")


class Producer(threading.Thread):
	def run(self):
		global gMoney, gTime
		while True:
			money = random.randint(100, 1000)
			gCondition.acquire()
			if gTime >= gTotalTimes:
				gCondition.release()
				break
			gMoney = gMoney + money
			print("%s生产者生产了%d元，总额%d元" % (threading.current_thread(), money, gMoney))
			gTime += 1
			gCondition.notifyAll()  # 生产完下面的代码，并不需要公用变量了，因此释放锁
			gCondition.release()
			time.sleep(0.5)


class Consumer(threading.Thread):
	def run(self):
		global gMoney
		while True:
			price = random.randint(500, 1000)
			gCondition.acquire()
			while gMoney < price:
				if gTime >= gTotalTimes:
					gCondition.release()
					return
				print("%s消费者准备消费%d元,剩余%d元,不足" % (threading.current_thread(), price, gMoney))
				gCondition.wait()
			gMoney -= price
			print('%s消费者消费了%d元，剩余%d元' % (threading.current_thread(), price, gMoney))
			gCondition.release()
			time.sleep(0.5)


def main():
	for x in range(3):
		t = Consumer(name='消费者线程%d' % x)
		t.start()
	for x in range(3):
		t = Producer(name='生产者线程%d' % x)
		t.start()


print("threading-------end ")

print("threadpool-------start ")

# 线程池
import threadpool


def t_pool(t):
	print("t_pool")


# 回调函数
def pool_callback(t1, t2):
	print(type(t1.callable))
	print("pool_callback")


# 异常函数
def exe_b(t1, t2):
	print(t1.exception)
	print(t2)
	print("exe_b")


#
def pool():
	task_tool = threadpool.ThreadPool(3)
	req = threadpool.makeRequests(callable_=t_pool, args_list=[1, 1, 1], callback=pool_callback, exc_callback=exe_b)
	print(req)
	[task_tool.putRequest(req) for req in req]

	task_tool.wait()


print("threadpool-------end ")

# pool()
# 线程池库ThreadPoolExecutor
# 测试线程池的锁机制
print("ThreadPoolExecutor-------start ")
from concurrent.futures import ThreadPoolExecutor, as_completed, wait

T = ThreadPoolExecutor(max_workers=5)
count = 0


def test_lock(thread_info):
	global count
	# raise  ValueError('aaa')
	return 1


def callback(fn):
	if fn.exception():  # 打印异常
		print("exception")
		print(fn.exception())
	else:
		print(fn.result())  # 打印结果


print(T._thread_name_prefix)
print(T._shutdown_lock)
print(T._work_queue)
task = []
for x in range(5):
	s = T.submit(test_lock, (T._thread_name_prefix)).add_done_callback(callback)
# 	print(s)
# 	task.append(s)
# wait(task)
# for x in as_completed(task):
# 	print(x.result())
print("ThreadPoolExecutor-------end ")

# 进程
# Process 利用Process新建一个子进程，在子进程执行任务
import datetime

print("Process-------start ")
from multiprocessing import Pool, Process


def job():
	def run():
		print('{}'.format(datetime.datetime.now().strftime('%Y-%m-%d  %H:%M%S.%f')))

	counter = 0
	while counter < 5:
		run()
		time.sleep(2)
		counter += 1
	print("sub process done")


def main():
	p = Process(target=job)
	p.start()
	print('main -done')  # 主进程先结束


print("Process-------end ")

# Pool 进程池可以理解成一个队列，该队列可以容易指定数量的子进程，当队列被任务占满之后，后续新增的任务就得排队，直到旧的进程有任务执行完空余出来，才会去执行新的任务。
print("Pool-------start ")
import random
from multiprocessing import Pool, Process


def job2(msg):
	def run():
		print('[Child-{}][{}]'.format(msg, datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')))

	# 模拟一个耗时任务
	time.sleep(random.randint(1, 3))
	run()


# if __name__ == '__main__':
# 	pool_size = 2
# 	# 进程池
# 	pool = Pool(pool_size)
# 	[pool.apply_async(job2, args=(i,)) for i in range(6)]
# 	pool.close()
# 	pool.join()
# 	print("main is donw")
print("Pool-------end ")
# ProcessPoolExecutor ProcessPoolExecutor是concurrent.futures里面的一个多进程解决方案，对多进程进行了一些便利的封装，用起来跟Java的ThreadPoolExecutor感觉很类似。
print("ProcessPoolExecutor-------start ")

from datetime import datetime
import time
import random
from concurrent.futures import ProcessPoolExecutor, wait


def job3(msg):
	def run():
		print('[Child-{}][{}]'.format(msg, datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')))

	# 模拟一个耗时任务
	time.sleep(random.randint(1, 5))
	run()


if __name__ == '__main__':
	# 进程池大小
	pool_size = 2
	# 进程池
	pool = ProcessPoolExecutor(pool_size)
	# 添加任务, 假设我们要添加6个任务，由于进程池大小为2，每次能只有2个任务并行执行，其他任务排队
	tasks = [pool.submit(job3, i) for i in range(6)]
	### 等待任务执行完, 也可以设置一个timeout时间
	wait(tasks)
	#
	print('main process done')
