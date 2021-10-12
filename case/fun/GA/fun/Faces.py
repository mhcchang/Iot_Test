# -*- coding: utf-8 -*-
import sys, os, random, base64
import multiprocessing
import multiprocessing
import requests,json
from requests.auth import HTTPDigestAuth
sys.path.append(os.path.abspath('../../'))
from GA.config.url import *
from GA.common.process import *
import time, sys

if len(sys.argv) > 1:
	ip = 'http://' + sys.argv[1] + ':' + sys.argv[2]
	device = sys.argv[3]
else:
	ip = ip
	device = device
print('url:  {}'.format(ip))
print('deviceID:  {}'.format(device))
global fs
fs = []
images = '../images/'

for root, dirs, f in (os.walk(images)):
	fs.append(f)
print("随机列表",fs)

#注册
def to_register():
	# register_body['DeviceID'] = device
	rsp = requests.post(register,headers=header,data=json.dumps(register_body),auth=HTTPDigestAuth('admin','1111111a'))
	assert json.loads(rsp.text)['ResponseStatusObject']['StatusString'] == "register succeed",print("错误")
#保活
def keep_():
	rsp = requests.post(keep,headers=header,data=json.dumps(keep_body),auth=HTTPDigestAuth('admin','1111111a'))
	assert json.loads(rsp.text)['ResponseStatusObject']['StatusString'] == "keepAlive succeed",print("错误")


def face_post():
	count = 1
	to_register()
	while True:
		time.sleep(2)

		keep_()

		with open(images + random.choice(fs[0]), 'rb') as f:
			small = base64.b64encode(f.read())
		with open(images + random.choice(fs[0]), 'rb') as f:
			large = base64.b64encode(f.read())
		print("人脸采集第{}张".format(str(count)))
		Face_Body['FaceListObject']['FaceObject'][0]['LocationMarkTime'] = (
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))
		Face_Body['FaceListObject']['FaceObject'][0]['AppearTime'] = (
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))
		Face_Body['FaceListObject']['FaceObject'][0]['DisappearTime'] = (
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))
		Face_Body['FaceListObject']['FaceObject'][0]['DisappearTime'] = (
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))
		Face_Body['FaceListObject']['FaceObject'][0]['SubImageList']['SubImageInfoObject'][0]['ShotTime'] = (
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))



		Face_Body['FaceListObject']['FaceObject'][0]['SourceID'] = device+str(random.randint(10,99))+(
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))+str(random.randint(10000,99999))

		#小图
		Face_Body['FaceListObject']['FaceObject'][0]['FaceID'] = device+str(random.randint(10,99))+(
			time.strftime('%Y%m%d%H%M%S', time.localtime(time.time())))+str(random.randint(100000000000,999999999999))
		Face_Body['FaceListObject']['FaceObject'][0]['SubImageList']['SubImageInfoObject'][0]['ImageID'] = device+str(random.randint(10,99))+str(random.randint(10000000,99999999))+str(random.randint(10000000000,99999999999))
		Face_Body['FaceListObject']['FaceObject'][0]['SubImageList']['SubImageInfoObject'][0]['ImageID'] = str(
			int(Face_Body['FaceListObject']['FaceObject'][0]['SubImageList']['SubImageInfoObject'][0]['ImageID']) + count)
		Face_Body['FaceListObject']['FaceObject'][0]['DeviceID'] = device
		Face_Body['FaceListObject']['FaceObject'][0]['SubImageList']['SubImageInfoObject'][0]['Data'] = str(small,encoding='utf-8')

		#大图

		Face_Body['FaceListObject']['FaceObject'][0]['SubImageList']['SubImageInfoObject'][1]['ImageID'] = device+str(random.randint(10,99))+str(random.randint(10000000,99999999))+str(random.randint(10000000000,99999999999))
		Face_Body['FaceListObject']['FaceObject'][0]['SubImageList']['SubImageInfoObject'][1]['ImageID'] = str(
			int(Face_Body['FaceListObject']['FaceObject'][0]['SubImageList']['SubImageInfoObject'][1]['ImageID']) + count)
		Face_Body['FaceListObject']['FaceObject'][0]['SubImageList']['SubImageInfoObject'][1]['Data'] = str(large,encoding='utf-8')

		p = multiprocessing.Process(target=post_ga,args=((ip + Faces), Face_Body, header,))
		res = p.start()
		count += 1
face_post()
