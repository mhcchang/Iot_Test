#coding:utf-8
'''
author:
function:
param:
other
'''
#返回字段信息
import random,time,datetime
from test_ga.caseConfig.config import r_redis,orgCode
device = r_redis.get('deviceId')
print(device)
print('------------')
def fun_type_se(obj):
	'''

	:return:
	'''
	if obj.funcType == '12':
		return  time_re(obj)
	elif  obj.funcType == '4':
		return str_re(obj)
	elif  obj.funcType == '6':
		return str_six(obj)
	elif  obj.funcType == '3':
		return str_three(obj)

	elif  obj.funcType == '11':
		return str_ev(obj)

	elif  obj.funcType == '1':
		return str_one(obj)

	elif  obj.funcType == '24':
		return str_tf(obj)
	elif  obj.funcType == '7':
		return str_sev(obj)
	elif  obj.funcType == '2':
		return str_two(obj)
	elif  obj.funcType == '5':
		return str_five(obj)
	elif  obj.funcType == '13':
		return time_rt(obj)


#funcType == 1 生成args中长度的list，再随机返回一个  和7类似
def str_one(obj):
	len_l = int(max(obj.funcArgs.split(",")))
	l = []
	min = int(max(obj.funcType.split(',')))
	l = [random.randint(min,len_l)*'1']
	return  l
#funcType == 2 返回arg中所有的值，字符串形式
def str_two(obj):
	return ','.join(obj.funcArgs.split(","))
#funcType == 3 表示需要在args中任意取值，如果是number则取随机数，如果是string则取随机字符串
def str_three(obj):
	if obj.type == 'string':
		return  random.choice(obj.funcArgs.split(","))
	elif obj.type == 'number':
		i = obj.funcArgs.split(",")
		return random.randint(int(i[0]),int(i[-1]))

#funcType == 4 标识取值范围是在args中
def str_re(obj):
	return random.choice(obj.funcArgs.split(","))
#funcType == 5 返回配置文件中的值
def str_five(obj):
	return 'http://10.122.48.196:8084/VIID/SubscribeNotifications'
#funcType  == 6 标识需要和device一起，具体多少位查看args中参数
def str_six(obj):
	if obj.name == 'ImageID':
		return device+str(random.randint(10,99))+str(random.randint(10000000,99999999))+str(random.randint(10000000000,99999999999))
	if obj.name == 'FaceID':
		return  device+str(random.randint(10,99))+(
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))+str(random.randint(100000000000,999999999999))
	if obj.name == 'SourceID':
		return device+str(random.randint(10,99))+(
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))+str(random.randint(10000,99999))
	if obj.name == 'SubscribeID':
		return orgCode + '032019070912131' + str(random.randint(99999,999999))
	if obj.name == 'PersonID':
		return  device+str(random.randint(10,99))+(
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))+str(random.randint(100000000000,999999999999))
	if obj.name == 'DispositionID':
		return  orgCode + '032019070912131' + str(random.randint(99999,999999))
	if obj.name == 'MotorVehicleID':
		return  device+str(random.randint(10,99))+(
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))+str(random.randint(100000000000,999999999999))
	if obj.name == 'NonMotorVehicleID':
		return  device+str(random.randint(10,99))+(
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))+str(random.randint(100000000000,999999999999))
#funcType == 7 取值长度长度为args中的值
def str_sev(obj):
	len_l = int(obj.funcArgs)
	l = []
	for x in range(len_l):
		l.append(str(x)*len_l)
	return random.choice(l)

#funcType == 11 表示设备ID
def str_ev(obj):
	return device

#funcType == 12 表示时间相关
def time_re(obj):
	return (time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
#funcType == 13  时间取值未来七天后
def time_rt(obj):
	return ((datetime.datetime.now() + datetime.timedelta(days=7)).strftime("%Y%m%d%H%M%S"))

#funcType == 20 代表对象
def str_tw(obj):
	return "11111111111111111"

#funcType == 24 则是图片的base64值
def str_tf(obj):
	global fs
	import  os,base64
	fs = []
	import  sys,os
	images = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))+'/pic/'
	for root, dirs, f in (os.walk(images)):
		fs.append(f)
	with open(images + random.choice(fs[0]), 'rb') as f:
		small = base64.b64encode(f.read())
	with open(images + random.choice(fs[0]), 'rb') as f:
		large = base64.b64encode(f.read())
	return str(large,encoding='utf-8')
