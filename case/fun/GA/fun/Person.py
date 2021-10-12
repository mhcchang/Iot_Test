import sys,os
# -*- coding: utf-8 -*-

sys.path.append(os.path.abspath('../../'))
from  GA.task import http_req
from  GA.config.url import *
import  time
count = 1
while True:
	time.sleep(2)
	print("人员采集第{}张".format(str(count)))
	Person_Body['PersonListObject']['PersonObject'][0]['PersonID']=str(int(Person_Body['PersonListObject']['PersonObject'][0]['PersonID'])+count)
	Person_Body['PersonListObject']['PersonObject'][0]['LocationMarkTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	Person_Body['PersonListObject']['PersonObject'][0]['PersonAppearTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	Person_Body['PersonListObject']['PersonObject'][0]['PersonDisAppearTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	Person_Body['PersonListObject']['PersonObject'][0]['SubImageList']['SubImageInfoObject'][0]['ShotTime']=(time.strftime('%Y%m%d%H%M%S',time.localtime(time.time())))
	Person_Body['PersonListObject']['PersonObject'][0]['DeviceID']="33010300001190000006"
	http_req.delay(ip + Person, Person_Body, header=header)
	count+=1
