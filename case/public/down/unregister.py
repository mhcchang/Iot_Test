#coding:utf-8
'''
author:
function:注销和释放库
param:
other
'''
import pytest
from util.log import *
from API.base.sdk_base import  SdkBase
from config.normal import *
class unregister_iot(SdkBase):
	def __init__(self):
		super(unregister_iot,self).__init__(ARGS)
		code = super().close_server()
		if code == 0:
			log_txt(loggername=__name__).log_init().info("{} 接口注销返回值为:{} 对应值为 : {}".format("IOT_Unregister",code,super().get_error_msg(code)))
		else:
			log_txt(loggername=__name__).log_init().error("{} 接口注销返回值为:{} 对应值为 : {}".format("IOT_Unregister",code,super().get_error_msg(code)))
