#coding:utf-8
'''
author:
function:添加设备  IOT_AddDevice
param:
other
'''
import pytest
import os,sys
from util.log import *
current=os.path.abspath('../../../')
sys.path.append(current)
from case.common import *
from API.Device.device import IOT_AddDevice
class Test_Device_add():
	'''IOT_AddDevice接口测试'''
	def setup(self):
		register_iot()
	@pytest.mark.parametrize("args",[{"addr": "10.169.241.64","video_port": 554,"password":"admin123","vendor": 51,"username": "admin","type": 2,"port": 3000}])
	def test_a_IOT_OpenLiveStream(self,args):
		result = IOT_AddDevice(args=args).run()
		self.log = log_txt(loggername=__name__).log_init()
		self.log.info(result)
	def teardown(self):
		unregister_iot()
if __name__ == '__main__':
	pytest.main(["-s","test_device_add.py"])