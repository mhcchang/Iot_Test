#coding:utf-8
'''
author:
function: 添加设备
param:
other
'''
from API.base.sdk_base import *
from API.base.structure import *
class IOT_AddDevice(SdkBase):
	def __init__(self,args=None):
		super().__init__(args)
		# self.dev = (args['dev'])
		self.dev_id =create_string_buffer(24)
		self.dev=struct_IotDeviceConfig()
		self.dev.vendor = int(args.get('vendor', 0))
		self.dev.type = int(args.get('type', 0))
		self.dev.anon_union = union_IotDeviceConfig()

		if self.dev.type == 1:
			_arg = struct_IotIpcConfig()
			_arg.addr = (args.get('addr', '')).encode('utf-8')
			_arg.port = int(args.get('port', 0))
			_arg.username = (args.get('username', '')).encode('utf-8')
			_arg.password = (args.get('password', '')).encode('utf-8')
			_arg.chan_no = int(args.get('chan_no', 0))
			_arg.chan_profile = int(args.get('chan_profile', 0))
			_arg.model = (args.get('model', '')).encode('utf-8')
			_arg.rtsp_url = (args.get('rtsp_url', '')).encode('utf-8')
			self.dev.anon_union.ipc = _arg

		if self.dev.type == 2:
			_arg = struct_IotSmartIpcConfig()
			_arg.addr = (args.get('addr', '')).encode('utf-8')
			_arg.port = int(args.get('port', 0))
			_arg.video_port = int(args.get('video_port', 0))
			_arg.username = (args.get('username', '')).encode('utf-8')
			_arg.password = (args.get('password', '')).encode('utf-8')
			_arg.chan_no = int(args.get('chan_no', 0))
			_arg.chan_profile = int(args.get('chan_profile', 0))
			_arg.model = (args.get('model', '')).encode('utf-8')
			_arg.rtsp_url = (args.get('rtsp_url', '')).encode('utf-8')
			_arg.platform_id = (args.get('platform_id', '')).encode('utf-8')
			_arg.device_code = (args.get('device_code', '')).encode('utf-8')
			self.dev.anon_union.smart_ipc = _arg

		if self.dev.type == 3:
			_arg = struct_IotGbIpcConfig()
			_arg.platform_id = (args.get('platform_id', '')).encode('utf-8')
			_arg.device_code = (args.get('device_code', '')).encode('utf-8')
			self.dev.anon_union.gb_ipc = _arg

		if self.dev.type == 4:
			_arg = struct_IotBoxConfig()
			_arg.addr = (args.get('addr', '')).encode('utf-8')
			_arg.port = int(args.get('port', 0))
			_arg.username = (args.get('username', '')).encode('utf-8')
			_arg.password = (args.get('password', '')).encode('utf-8')
			_arg.chan_num = int(args.get('chan_num', 0))
			_arg.model = (args.get('model', '')).encode('utf-8')
			_arg.platform_id = (args.get('platform_id', '')).encode('utf-8')
			_arg.device_code = (args.get('device_code', '')).encode('utf-8')
			self.dev.anon_union.box = _arg

		if self.dev.type == 5:
			_arg = struct_IotCloudIpcConfig()
			_arg.addr = (args.get('addr', '')).encode('utf-8')
			_arg.port = int(args.get('port', 0))
			_arg.video_port = int(args.get('video_port', 0))
			_arg.username = (args.get('username', '')).encode('utf-8')
			_arg.password = (args.get('password', '')).encode('utf-8')
			_arg.chan_no = int(args.get('chan_no', 0))
			_arg.chan_num = int(args.get('chan_num', 0))
			_arg.chan_profile = int(args.get('chan_profile', 0))
			_arg.model = (args.get('model', '')).encode('utf-8')
			_arg.rtsp_url = (args.get('rtsp_url', '')).encode('utf-8')
			_arg.platform_id = (args.get('platform_id', '')).encode('utf-8')
			_arg.device_code = (args.get('device_code', '')).encode('utf-8')
			self.dev.anon_union.cloud_ipc = _arg

		if self.dev.type == 6:
			_arg = struct_IotGbIpcConfig()
			_arg.platform_id = (args.get('platform_id', '')).encode('utf-8')
			_arg.device_code = (args.get('device_code', '')).encode('utf-8')
			self.dev.anon_union.gb_ipc = _arg

		if self.dev.type == 7:
			_arg = struct_IotKafkaIpcConfig()
			_arg.addr = (args.get('addr', '')).encode('utf-8')
			_arg.port = int(args.get('port', 0))
			_arg.username = (args.get('username', '')).encode('utf-8')
			_arg.password = (args.get('password', '')).encode('utf-8')
			_arg.model = (args.get('model', '')).encode('utf-8')
			_arg.url = (args.get('url', '')).encode('utf-8')
			_arg.topic_name = (args.get('topic_name', '')).encode('utf-8')
			self.dev.anon_union.kafka_ipc = _arg
	def run(self):
		self.SdkCdll.IOT_AddDevice.argtype = (POINTER(struct_IotDeviceConfig), c_char_p)
		self.SdkCdll.IOT_AddDevice.restype = c_int
		code = self.SdkCdll.IOT_AddDevice(pointer(self.dev), self.dev_id)
		dev = self.format_res(self.dev)#结果格式化 使用递归
		if isinstance(dev, dict):
			dev['dev_id'] = self.dev_id.value.decode()
		return self.result(code, {"dev": dev, "dev_id": self.dev_id.value.decode()})
	def result(self, code, res=None):
		return super().result(code, res)

# param = {"addr": "10.171.129.18", "port": 34567, "type": 2, "model": "xm_fun_01", "vendor": 52, "chan_no": 0,
# 	   "chan_num": 0, "password": "admin123", "username": "admin", "video_port": 554, "device_code": "",
# 	   "platform_id": "", "chan_profile": 0,'ip':'10.122.48.196','_port':"8500","_user":"admin","_pwd":"admin","version":"4.2.3"}
# start=IOT_AddDevice(param).start_server()
# resutl=IOT_AddDevice(param).run()
# print(resutl)