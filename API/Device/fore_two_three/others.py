# coding:utf-8
'''
author:
function:
param:
other
'''
from API.base.sdk_base import *
from API.base.version.fore_two_three.structure import *
import time
# log
from util.log import *

log = log_txt(loggername=__name__).log_init()


class IOT_GetVendorSdkVersion(SdkBase):
	def __init__(self, args=None):
		super().__init__(args)

		self.vendor_id = int(args.get('vendor_id', 51))

		self.sdk_version = create_string_buffer(1024 * 1024 * 10)

		self.ext_info = (args.get('ext_info', '')).encode('utf-8')

	def run(self):
		self.SdkCdll.IOT_GetVendorSdkVersion.argtype = (c_int, c_char_p, c_char_p)
		self.SdkCdll.IOT_GetVendorSdkVersion.restype = c_int
		code = self.SdkCdll.IOT_GetVendorSdkVersion(self.vendor_id, self.sdk_version, self.ext_info)

		return self.result(code, {"sdk_version": self.sdk_version.value.decode()})

	def result(self, code, res=None):
		return super().result(code, res)


# from config.normal import *
# from API.Other.Message_callback import *
#
# #
# sdk_ = SdkBase(args=ARGS)
# # IOT_SetMessageCallback(args = ARGS).run()
# sdk_.start_server()
# rst = IOT_GetVendorSdkVersion(args={}).run()
# print(rst)
# print(rst)
# while 1:
# 	pass
