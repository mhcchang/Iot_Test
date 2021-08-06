#coding:utf-8
'''
author:haobingzhong
function: open_stream 开流相关接口测试
param:
other
'''
from case.common import *

class Test_Open_Stream():
	'''IOT_OpenLiveStream接口测试'''
	def setup(self):
		register_iot()
	#megconnect开流
	@pytest.mark.parametrize("deviceId",deviceId=None)
	def test_a_IOT_OpenLiveStream(self,deviceId):
		interface = eval('SdkBase().{}(args={})'.format("IOT_CloseLiveStream", deviceId))
	def teardown(self):
		unregister_iot()
if __name__ == '__main__':
    pytest.main(['-s','test_open_stream.py'])