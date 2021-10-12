#coding:utf-8
'''
author:
function:
param:
other
'''
import requests
import json
def post_ga(url,body,header):
	try:
		resp = requests.post(url=url,headers=header,data=json.dumps(body))
		assert json.loads(resp.text)['ResponseStatusListObject']['ResponseStatusObject'][0]['StatusCode'] == 0
	except Exception as e:
		print(e.args)
