
# -*- coding: utf-8 -*-
import sys,os
sys.path.append(os.path.abspath('../../'))
from  GA.task import http_req
from  GA.config.url import *
import  time
count = 0
while True:
	time.sleep(2)
	NonMotorVehicles_Body['NonMotorVehicleListObject']['NonMotorVehicleObject'][0]['NonMotorVehicleID']=str(int(NonMotorVehicles_Body['NonMotorVehicleListObject']['NonMotorVehicleObject'][0]['NonMotorVehicleID'])+count)

	NonMotorVehicles_Body['NonMotorVehicleListObject']['NonMotorVehicleObject'][0]['MarkTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	NonMotorVehicles_Body['NonMotorVehicleListObject']['NonMotorVehicleObject'][0]['AppearTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	NonMotorVehicles_Body['NonMotorVehicleListObject']['NonMotorVehicleObject'][0]['DisappearTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	NonMotorVehicles_Body['NonMotorVehicleListObject']['NonMotorVehicleObject'][0]['SubImageList']['SubImageInfoObject'][0]['ShotTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	NonMotorVehicles_Body['NonMotorVehicleListObject']['NonMotorVehicleObject'][0]['DeviceID']="33010300001190000006"
	http_req.delay(ip + NonMotorVehicles, NonMotorVehicles_Body, header=header)
	print("非机动车采集第{}张,id:{}".format(str(count),str(int(NonMotorVehicles_Body['NonMotorVehicleListObject']['NonMotorVehicleObject'][0]['NonMotorVehicleID'])+count)))
	count+=1
