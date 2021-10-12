#coding:utf-8
'''
author:
function:注册SDK
param:
other
'''
from API.base.sdk_base import  SdkBase
from config.normal import *
from util.log import *
from case.common import *
from API.Device.fore_two_three.device import *

class register_iot(SdkBase):
	def __init__(self):
		# super().__init__(ARGS)
		super().__init__(ARGS)
		self.message_call()
		code = super().start_server()
		self.log = log_txt(loggername=__name__).log_init()
		if code == 0:
			self.log.info("{} 接口返回值为:{} 对应值为 : {}".format("IOT_Startup",code,super().get_error_msg(code)))
		else:
			self.log.error("{} 接口返回值为:{} 对应值为 : {}".format("IOT_Startup",code,super().get_error_msg(code)))
	def delete_all(self):
		#获取设备列表
		result=IOT_GetDeviceList(args={}).run()
		if result['code'] == 0:
			self.log.info("获取列表成功")
			self.log.info(result)
			for device_id in result['data']['result']:
				#强制删除
				res=IOT_DeleteDevice3(args={'dev_id' : (device_id['id']),'force_delete':1}).run()
				assert res['code'] == 0
				self.log.info("删除成功")

		else:
			self.log.error("获取列表失败！"+result)
	def message_call(self):
		pass
		# #回调
		# result=IOT_SetMessageCallback(args={}).run()
		# if result['code'] == 0:
		# 	self.log.info("回调成功")
		#
		# else:
		# 	self.log.error("回调失败！")

