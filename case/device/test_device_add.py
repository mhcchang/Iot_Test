#coding:utf-8
'''
author:
function:
		添加设备  IOT_AddDevice
		pytest.mark.first
		order 执行顺序从小到大
param:
other
'''
import pytest
import os,sys
import allure
current=os.path.abspath('../')
print("path",current)
sys.path.append(current)
from util.log import *
from case.common import *
from API.Device.device import *
import copy
dev_id_info = []
from  json import dumps,loads

@allure.title("设备相关")
class Test_Device():
	'''IOT_AddDevice接口测试'''
	log = log_txt(loggername=__name__).log_init()
	def setup(self):
		pass
	@allure.title("添加设备")
	@allure.step("step:添加设备")
	@pytest.mark.smoke
	@pytest.mark.order(1)
	def test_IOT_AddDevice(self):
		with allure.step('step1:注冊'):
			self.sdk=register_iot()
		with allure.step('step2:清除设备环境'):
			self.sdk.delete_all()
			time.sleep(2)
			pass
		result = IOT_AddDevice(args=dev_info[0]).run()
		global dev_id_info
		dev_id_info = copy.deepcopy(dev_info)
		log.info(result)
		assert result['code'] == 0
		dev_id_info[0].setdefault('dev_id',result['data']['dev']['dev_id'])

	@allure.title('更新设备')
	@allure.step('step:更新设备')
	@pytest.mark.order(2)
	@pytest.mark.smoke
	def test_IOT_UpdateDevice(self):
		global dev_id_info
		result = IOT_UpdateDevice(args=dev_id_info[0]).run()
		log.info(result)
		assert result['code'] == 0

	@allure.title('列举设备')
	@allure.step('step:列举设备')
	@pytest.mark.order(2)
	@pytest.mark.smoke
	def test_IOT_GetDeviceList(self):
		result = IOT_GetDeviceList(args={}).run()
		log.info(result)
		assert result['code'] == 0

	@allure.title('设备版本查询')
	@allure.step('step:设备版本查询')
	@pytest.mark.order(3)
	@pytest.mark.smoke
	@pytest.mark.skipif(condition=(dev_info[1]['version']=='false'),reason='设备不支持')
	def test_IOT_GetDeviceVersion(self):
		result = IOT_GetDeviceVersion(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		log.info(result)
		assert result['code'] == 0

	@allure.title('获取设备算法信息')
	@allure.step('step:获取设备算法信息')
	@pytest.mark.order(3)
	@pytest.mark.skipif(condition=(dev_info[1]['version']=='false'),reason='设备不支持')
	@pytest.mark.smoke
	def test_IOT_GetDeviceAlgorithmInfo(self):
		result = IOT_GetDeviceAlgorithmInfo(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		log.info(result)
		assert result['code'] == 0

	@allure.title('获取单个设备状态信息')
	@allure.step('step:获取单个设备状态信息')
	@pytest.mark.order(3)
	@pytest.mark.skipif(condition=(dev_info[1]['version']=='false'),reason='设备不支持')
	@pytest.mark.smoke
	def test_IOT_GetDeviceStatus(self):
		result = IOT_GetDeviceStatus(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		log.info(result)
		assert result['code'] == 0

	@allure.title('获取单个设备的参数信息')
	@allure.step('step:获取单个设备的参数信息')
	@pytest.mark.order(3)
	# @pytest.mark.skipif(condition=(dev_info[1]['version']=='false'),reason='设备不支持')
	@pytest.mark.smoke
	def test_IOT_GetDeviceStatus(self):
		result = IOT_GetDeviceInfo(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		log.info(result)
		assert result['code'] == 0



if __name__ == '__main__':
	pytest.main(["-s","test_device_add.py"])
