#coding:utf-8
'''
author:
function: 获取错误码信息
param:
other
'''
from API.base.sdk_base import *

class get_code_meg(SdkBase):

	def get_meg(self,code):
		return self.get_error_msg(code)

