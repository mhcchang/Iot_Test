# -*- coding: utf-8 -*-
#采集设备接口
import sys,os
sys.path.append(os.path.abspath('../../'))
from  GA.task import http_req
from  GA.config.bm_all import bm
from  GA.config.url import *
# for x in bm:
# 	print(type(x))
# 	for y in x['areaList']:
# 		if y['areaList']:
# 			for l in y['areaList']:
# 				for z in range(100):
# 					if z >9:
# 						APEs_body['APEListObject']['APEObject'][0]['ApeID'] = l['code'] + "000011900000" + str(z)
# 					else:
# 						APEs_body['APEListObject']['APEObject'][0]['ApeID']=l['code']+"0000119000000"+str(z)
# 					http_req.delay(ip+APEs,APEs_body,header="")
# 		else:
# 			for z in range(100):
# 				if z > 9:
# 					APEs_body['APEListObject']['APEObject'][0]['ApeID'] = l['code'] + "000011900000" + str(z)
# 				else:
# 					APEs_body['APEListObject']['APEObject'][0]['ApeID'] = l['code'] + "0000119000000" + str(z)
# 				http_req.delay(ip + APEs, APEs_body, header="")

for  x in range(1000,10000):
	print(x)
	APEs_body['APEListObject']['APEObject'][0]['ApeID'] =  "3301060000118000" + str(x)
	http_req.delay(ip + APEs, APEs_body, header="")
