# -*- coding: utf-8 -*-
import sys,os
sys.path.append(os.path.abspath('../../'))
from  GA.task import http_req
from  GA.config.url import *
import  time
count = 0
while True:
	time.sleep(2)
	print("机动车采集第{}张".format(str(count)))

	MotorVehicles_Body['MotorVehicleListObject']['MotorVehicleObject'][0]['MotorVehicleID']=str(int(MotorVehicles_Body['MotorVehicleListObject']['MotorVehicleObject'][0]['MotorVehicleID'])+count)

	MotorVehicles_Body['MotorVehicleListObject']['MotorVehicleObject'][0]['MarkTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	MotorVehicles_Body['MotorVehicleListObject']['MotorVehicleObject'][0]['AppearTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	MotorVehicles_Body['MotorVehicleListObject']['MotorVehicleObject'][0]['DisappearTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	MotorVehicles_Body['MotorVehicleListObject']['MotorVehicleObject'][0]['SubImageList']['SubImageInfoObject'][0]['ShotTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	MotorVehicles_Body['MotorVehicleListObject']['MotorVehicleObject'][0]['DeviceID']="33010300001190000006"
	http_req.delay(ip + MotorVehicles, MotorVehicles_Body, header=header)
	count+=1
