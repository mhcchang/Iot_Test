# -*- coding: utf-8 -*-
#采集设备接口
from  GA.task import http_req
from  GA.config.bm import bm
from  GA.config.url import *
# for x in bm:
for y in bm['areaList']:
	# print(y['code'])
	for l in y['areaList']:
		for z in range(10):
			if z >9:
				APEs_body['APEListObject']['APEObject'][0]['ApeID'] = l['code'] + "000011900000" + str(z)
			else:
				APEs_body['APEListObject']['APEObject'][0]['ApeID']=l['code']+"0000119000000"+str(z)
			http_req.delay(ip+APEs,APEs_body,header="")
	# else:
	# 	for z in range(2):
	# 		if z > 9:
	# 			APEs_body['APEListObject']['APEObject'][0]['ApeID'] = l['code'] + "000011900000" + str(z)
	# 		else:
	# 			APEs_body['APEListObject']['APEObject'][0]['ApeID'] = l['code'] + "0000119000000" + str(z)
	# 		http_req.delay(ip + APEs, APEs_body, header="")

