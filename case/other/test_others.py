#coding:utf-8
'''
author:
function:
	1、获取各个厂商的SDK版本
	2、开启onvif
param:
other
'''
#coding:utf-8

import os,sys

current=os.path.abspath('../')
sys.path.append(current)
from API.Device.fore_two_three.device import *
import allure
from case.common import *
from API.Device.fore_two_three.device import *
from API.Device.fore_two_three.others import *

from  config.normal import *
import  copy
dev_id_info = []


class Test_other():
	@allure.title("获取设备厂商的SDK版本信息")
	@allure.step("step:获取设备厂商的SDK版本信息")
	@pytest.mark.smoke
	@pytest.mark.order(1)
	def test_IOT_GetVendorSdkVersion(self):
		with allure.step('step1:注冊'):
			self.sdk=register_iot()
		with allure.step('step2:清除设备环境'):
			self.sdk.delete_all()
			time.sleep(2)
		with allure.step('step:获取SDK版本信息：海康'):
			result = IOT_GetVendorSdkVersion(args={"vendor_id":2}).run()
			assert result['code'] == 0,result
		with allure.step('step:获取SDK版本信息：大华'):
			result = IOT_GetVendorSdkVersion(args={"vendor_id": 2}).run()
			assert result['code'] == 0, result

		with allure.step('step:获取SDK版本信息：华为'):
			result = IOT_GetVendorSdkVersion(args={"vendor_id": 5}).run()
			assert result['code'] == 0, result
		with allure.step('step:获取SDK版本信息：宇视'):
			result = IOT_GetVendorSdkVersion(args={"vendor_id": 6}).run()
			assert result['code'] == 0, result
		with allure.step('step:获取SDK版本信息：科达'):
			result = IOT_GetVendorSdkVersion(args={"vendor_id": 7}).run()
			assert result['code'] == 0, result
		with allure.step('step:获取SDK版本信息：旷视T系列相机'):
			result = IOT_GetVendorSdkVersion(args={"vendor_id": 51}).run()
			assert result['code'] == 0, result
		with allure.step('step:获取SDK版本信息：旷视X系列相机'):
			result = IOT_GetVendorSdkVersion(args={"vendor_id": 52}).run()
			assert result['code'] == 0, result



# #
# if __name__ == '__main__':
# 	pytest.main(["-s","../"])