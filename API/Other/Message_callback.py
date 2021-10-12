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


class IOT_SetMessageCallback(SdkBase):
	def __init__(self, args=None):
		super().__init__(args)
		self.user_data = (args.get('user_data', None))
		self.res = []
		CALLBACK = CFUNCTYPE(c_int, c_int, c_char_p, c_int, c_char_p)
		self.system_define_cb = CALLBACK(self.system_define_cb_func)

	def run(self):
		self.SdkCdll.IOT_SetMessageCallback.argtype = (c_int, c_char_p)
		self.SdkCdll.IOT_SetMessageCallback.restype = c_int
		code = self.SdkCdll.IOT_SetMessageCallback(self.system_define_cb, self.user_data)

		if code == 0:
			self.system_define_wait_func()
		else:
			return self.result(code)

		return self.result(code, {'res': self.res})

	def result(self, code, res=None):
		return super().result(code, res)

	def system_define_wait_func(self):
		time.sleep(2)

	def system_define_cb_func(self, msg_type, content, content_len, user_data):
		return self.real_cb_func(msg_type, content, content_len, user_data)

	def real_cb_func(self, msg_type, content, content_len, user_data):

		_tmp = ''
		_res_list = []
		print('>>>>>>')
		if(isinstance(content,bytes)):
			content = content.decode('utf-8','ignore')
			log.info("回调消息:")
			log.info(self._format_res(msg_type))
			# if msg_type == 50:
			# 	# self.info = pointer(POINTER(struct_IotDeviceAlarmInfo(content)))
			# 	s=struct_IotDeviceAlarmInfo()
			# 	struct.unpack("dev_id",(content))
			# 	# memmove(addressof(s),bin,100000)
			# 	# print(hex(s.chan_no))
			# 	# print(self.info)
			# 	pass
		# log.info(self._format_res(content))
		elif(isinstance(content,object)):
			print("object:-----")
			print((content))
		print('<<<<<<')
		self.res = _res_list
		return 0

def query_megage(code):
	return code
