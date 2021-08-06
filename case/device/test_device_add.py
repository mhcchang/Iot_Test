#coding:utf-8
'''
author:
function:
		添加设备  IOT_AddDevice
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
from API.Device.device import IOT_AddDevice
@allure.feature("设备相关")
class Test_Device_add():
	'''IOT_AddDevice接口测试'''
	@allure.title('注册到服务器')
	def setup(self):
		with allure.step('step1:注冊'):
			self.sdk=register_iot()
		with allure.step('step2:若有设备则全部刪除'):
			self.sdk.delete_all()
			pass
	@allure.step("step3:添加设备")
	@pytest.mark.parametrize("args",[{"addr": "10.171.129.5","video_port": 554,"password":"admin123","vendor": 51,"username": "admin","type": 2,"port": 3000}])
	def test_a_IOT_OpenLiveStream(self,args):
		result = IOT_AddDevice(args=args).run()
		assert result['code'] == 0
		self.log = log_txt(loggername=__name__).log_init()
		self.log.info(result)
	@allure.step("step:开视频流")
	def test_b_(self):
		pass

	# def teardown(self):
	# 	unregister_iot()
# if __name__ == '__main__':
# 	pytest.main(["-s","test_device_add.py"])