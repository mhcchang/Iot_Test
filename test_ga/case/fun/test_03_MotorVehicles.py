# coding:utf-8
'''
author:
function:
param:
other
'''
'''
测试内容:
	1、机动车增删改查。
'''
from  test_ga.case.common import *

u_id = {}
@allure.feature('人员信息')
class Test_MotorVehicles():
	@allure.title("添加采集设备")
	@pytest.mark.order(1)
	def test_addDevice(self):
		with allure.step('step1:添加采集设备'):
			u_id = str(uuid.uuid1())
			deviceInfo = ApLo().dumps(APEListObject())
			r_redis.set(u_id, deviceInfo)
			r = request.post(url=ape, data=deviceInfo)
		with allure.step('step2:注册'):
			key_value(json.loads(r_redis.get(u_id)), 'Password')
			rsp = request.post(url=register, headers=header, data=json.dumps(register_body), auth=HTTPDigestAuth(
				'admin', l[0]))
		with allure.step('step3:保活'):
			rsp = request.post(url=keep, headers=header, data=json.dumps(keep_body), auth=HTTPDigestAuth(
				'admin', l[0]))
		with allure.step('step4:校时'):
			pass

	@allure.title('订阅')
	@pytest.mark.order(2)
	@pytest.mark.skip('本次跳过')
	def test_sub(self):
		pass
		# with allure.step('step1:建立订阅'):
		# 	s = sub().dumps(SubscribeListObject())
		# 	u = str(uuid.uuid1())
		# 	u_id.setdefault(self.test_sub.__name__, u)
		# 	r_redis.set(u, s)
		# 	r = request.post(url=sub_url, header=header, data=s)
		# 	assert r['status_code'] == 201, print(r)
		# 	pass
		pass

	@allure.title('布控')
	@pytest.mark.order(2)
	def test_dispoint(self):
		pass

	@allure.title("机动车信息")
	@pytest.mark.order(4)
	def test_motorvehicles(self):
		MotorInfo = MotorListObj().dumps(MotorVehicleListObject())
		u_id = str(uuid.uuid1())
		r_redis.set(u_id, MotorInfo)
		uuid_ope(name=self.test_motorvehicles.__name__, uuid=u_id)
		header = {
			"User-Identify": "11010800001190000001"
		}
		with allure.step('step1:添加机动车采集信息'):
			r = request.post(url=motorvehicles, headers=header, data=MotorInfo)
			print('------------')
			import json
			print(json.loads(r['_content']))
			if r.get('status_code', None) == None:
				assert 0 == 200, print(r)
			else:
				assert r.get('status_code', None) == 201, print(r)
		with allure.step('step2:修改机动车信息'):
			r = request.put(url=motorvehicles, headers=header, data=MotorInfo)
			if r.get('status_code', None) == None:
				assert 0 == 200, print(r)
			else:
				assert r.get('status_code', None) == 200, print(r)
		with allure.step('step3:查询机动车采集信息'):
			time.sleep(5)
			key_value(json.loads(r_redis.get(u_id)), 'MotorVehicleID')
			r = request.get(url=motorvehicles + '?(MotorVehicles.MotorVehicleID={})'.format(l[0]), headers=header)
			assert type(r) != None, print(r)
			if r.get('status_code', None) == None:
				assert 0 == 200, print(r)
			else:
				assert r.get('status_code', None) == 200, print(r)
		with allure.step('step4:删除机动车信息'):
			time.sleep(5)
			r = request.delete(url=motorvehicles + '?IDList={}'.format(l[0]), headers=header)
			if r.get('status_code', None) == None:
				assert 0 == 200, print(r)
			else:
				assert r.get('status_code', None) == 200, print(r)

	@allure.title('订阅后续操作')
	@pytest.mark.skip('本次跳过')
	@pytest.mark.order(7)
	def test_subD(self):
		s_id = key_value(json.loads(r_redis.get(u_id['test_sub'])), 'SubscribeID')
		k = json.loads(r_redis.get(u_id['test_sub']))
		with allure.step('step1:撤销订阅'):
			k['SubscribeListObject']['SubscribeObject'][0]['OperateType'] = 1
			r = request.put(url=sub_url + '/' + l[0], header=header, data=json.dumps(k))
			if r.get('status_code', None) == None:
				assert 0 == 200, print(r)
			else:
				assert r.get('status_code', None) == 200, print(r)
		with allure.step('step2:查询订阅'):
			k['SubscribeListObject']['SubscribeObject'][0]['OperateType'] = 1
			#
			r = request.get(url=sub_url + '?(SubscribeObject.SubscribeID={})'.format(l[0]), header=header)
			if r.get('status_code', None) == None:
				assert 0 == 200, print(r)
			else:
				assert r.get('status_code', None) == 200, print(r)
		with allure.step('step:查询推送数据数量及内容是否一致'):
			f = sql.query(Uuid_to, name='test_person')
			assert type(f) != None,print('订阅数据未推送~~~')
			assert f.other == 'pass', print(f.__dict__)
		with allure.step('step3:删除订阅'):
			k['SubscribeListObject']['SubscribeObject'][0]['OperateType'] = 1
			r = request.delete(url=sub_url + '?IDList={}'.format(l[0]), header=header)
			if r.get('status_code', None) == None:
				assert 0 == 200, print(r)
			else:
				assert r.get('status_code', None) == 200, print(r)

	@allure.title('设备后续操作')
	@pytest.mark.order(8)
	def test_devD(self):
		with allure.step('step1:注销设备'):
			pass
		with allure.step('step2:删除设备'):
			device = flush_redis.get('deviceId')
			r = request.delete(url=ape+'/'+device, header=header)
			if r.get('status_code', None) == None:
				assert 0 == 200, print(r)
			else:
				assert r.get('status_code', None) == 200, print(r)
