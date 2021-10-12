# coding:utf-8
'''
author:
function:
param:
other
'''
cookies = {
	'devops-login': "MTUxNzgwMTIyMXxtd0hteE1WdTF2Z0xuYXFMWW1UWXBOYUhhdFlrd0huYXhjTzE3OElLU1QybFM3M0lMempaVGpMVVFvU2pJTzFqYVRrbzVhWTRwbGJERDUyYWRBYUZKamZma0ttOGlOS3haUmdDcHc0LXM0RjZWRnRrQTlfR3ZQVW5keTMzTDZpSmZiN1E4dHAzYnRyYlUzVGJyTUFUMWxqYmRnUE84OHlZWlFzMk9fVENXbEZlcEsyZzNOYjV3WVJMQW85ZlFDSHU0dE1rUkdFdExoeGhzYnpjREpxdER5WnJpTkh6T3JNaS1PSXVmcWNIcmJtVGVsSnZDcEVEQ1NCT1lYVkUzQlU9fCAAxNV5iKIcX-vd6FIPD2yPQqJDub-vOL_FRuXZLvcc"}
import requests, time, subprocess

host = '10.172.198.43'
deletename_all = True


# 获取服务
def deploytest():
	try:
		test_url = 'http://{}:5432/api/v1/service'.format(host)
		response = requests.get(test_url, headers=cookies, timeout=30)
		global service_name, deploy
		service_name = []
		deploy = [None for x in range(100)]
		for service in response.json():
			print(service)
			service_name1 = service["name"]
			deploy[service['rank']] = service_name1
			service_name.append(service_name1)
		if service_name == []:
			print(host + "集群未部署任何服务")
	except Exception as e:
		print(e.args)
		print(host + "环境存在问题")


def node():
	try:
		test_url = 'http://{}:5432/api/v1/node?detail=1'.format(host)
		response = requests.get(test_url, headers=cookies, timeout=30)
		global nodetest
		for nodetest in response.json():
			print(nodetest)
	except:
		print(host + "：  " + "环境存在问题")


# 停止服务
def stop_service():
	global service_name
	if service_name == [] and deletename_all == True:
		print(host + "：集群未部署任何服务")
	elif deletename_all == True:
		print(host + "：  " + "正在停止,请稍后")
		for servicename in service_name:
			test_url = 'http://{}:5432/api/v1/service/{}/stop'.format(host, servicename)
			response = requests.post(test_url, cookies=cookies)
			time.sleep(0.5)
			if str(response.json()["Status"]) == "True":
				print(host + "：  " + servicename + "：停止完成")
			else:
				continue
		for servicename in service_name:
			test_url = 'http://{}:5432/api/v1/service/{}/deploy_disable'.format(host, servicename)
			data = {
				"names": ""
			}
			response = requests.post(test_url, json=data, cookies=cookies)
			time.sleep(0.5)
			if str(response.json()["Status"]) == "True":
				print(host + "：RunOnce进行中")
			else:
				continue
	print(host + "：停止服务完成===============================")
	print(host + "：RunOnce完成===============================")


# subprocess.call(['./delete.sh'],shell=False)

def delete_service():
	global service_name
	try:
		print(host + "：是否删除环境服务？输入 yes 执行删除，输入 no 退出删除")
		delete_services = str(input())
		if delete_services == "yes":
			print(host + "：环境服务开始删除")
			if service_name == [] and deletename_all == True:
				print("删除服务操作===：" + host + "集群未部署任何服务")
			elif deletename_all == True:
				print(host + "： " + "正在删除服务,请稍后")
				for servicename in service_name:
					test_url = 'http://{}:5432/api/v1/service/{}'.format(host, servicename)
					response = requests.delete(test_url, cookies=cookies)
					time.sleep(2)
					if str(response.json()["Status"]) == "True":
						print(host + "：  " + servicename + "：删除服务完成")
					else:
						continue
		elif delete_services == "no":
			print(host + "：退出删除服务")
		else:
			print(host + "：输入不符合预期，退出")
	except:
		print("该环境有问题，请检查服务")


def deply_service():
	global service_name, deploy
	from datetime import datetime
	for i, v in enumerate(deploy):
		if v == None:
			pass
		else:
			test_json1 = 'http://{}:5432/api/v1/service/{}/deploy'.format(host, v)
			selfTest = 1  # 1等于开启健康检查，0等于关闭健康检查
			batchSize = 8  # 部署并行数，默认为8
			data = {
				"forceDeploy": "1", "onDemandDeploy": "0", "selfTest": selfTest, "batchSize": batchSize
			}
			print('rank:{},开始部署:{}'.format(i, v))
			response1 = requests.post(test_json1, json=data, cookies=cookies)
			response2 = requests.get(test_json1, cookies=cookies)
			print('-------------')
			while 1:
				time.sleep(5)
				response2 = requests.get(test_json1, cookies=cookies)
				print((datetime.now().strftime('%a, %b %d %H:%M')) + '正在部署：{}'.format(
					response2.json()['short_show_message']))
				if str(response2.json()["short_show_message"]) == "service deploy done.":
					print(host + "：检查部署结果:    " + str(response2.json()["short_show_message"]))
					break
			time.sleep(60)
		# datetime.now().strftime('')
	pass


if __name__ == '__main__':
	# deploytest()
	# stop_service()
	# # deply_service()
	# delete_service()
	s = {
		"1": '1',
		"sss": '2'
	}
	f = filter(lambda x: s[x] == '2', s.keys())
	print(f.__next__())
