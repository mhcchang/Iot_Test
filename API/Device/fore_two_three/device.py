# coding:utf-8
'''
author:
function: 设备操作相关 V4.2.3
param:
other
'''
from API.base.sdk_base import *
from API.base.version.fore_two_three.structure import *
import time
# log
from config.normal import *
from util.log import *

log = log_txt(loggername=__name__).log_init()

# 添加设备
class IOT_AddDevice(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		log.info("1111111111111111")
		log.info(args)
		self.dev = (args.get('dev', None))
		self.dev_id = create_string_buffer(24)
		self.dev = struct_IotDeviceConfig()
		self.dev.vendor = int(args.get('vendor', 0))
		self.dev.type = int(args.get('type', 0))
		self.dev.parent_id = (args.get('parent_id', '')).encode('utf-8')
		self.dev.extra_info = (args.get('extra_info', '')).encode('utf-8')
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
		dev = self.format_res(self.dev)  # 结果格式化 使用递归
		if isinstance(dev, dict):
			dev['dev_id'] = self.dev_id.value.decode()
		return self.result(code, {"dev": dev, "dev_id": self.dev_id.value.decode()})

	def result(self, code, res=None):
		return super().result(code, res)


# 获取设备列表

class IOT_GetDeviceList(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.user_data = (args.get('user_data', None))
		CALLBACK = CFUNCTYPE(c_int, POINTER(struct_IotDeviceInfo), c_int, c_char_p)
		self.system_define_cb = CALLBACK(self.system_define_cb_func)
		self.status = False

	def run(self):
		self.SdkCdll.IOT_GetDeviceList.argtype = (c_int, c_char_p)
		self.SdkCdll.IOT_GetDeviceList.restype = c_int
		code = self.SdkCdll.IOT_GetDeviceList(self.system_define_cb, self.user_data)

		if code == 0:
			self.system_define_wait_func()
		else:
			return self.result(code)

		return self.result(code, {'result': self.res})

	def result(self, code, res=None):
		return super().result(code, res)

	def system_define_wait_func(self):
		timestamp = int(time.time()) + 25
		while 1:
			time.sleep(0.2)
			if self.status or int(time.time()) >= timestamp:
				break

	def system_define_cb_func(self, dev_list, dev_num, user_data):
		return self.real_cb_func(dev_list, dev_num, user_data)

	def real_cb_func(self, dev_list, dev_num, user_data):
		key_list = [x[0] for x in struct_IotDeviceInfo._fields_]
		res = []
		try:
			for i in range(dev_num):
				tmp = {}
				for key in key_list:
					d = self.format_res(dev_list[i].__getattribute__(key))
					if not isinstance(d, dict):
						tmp[key] = d
					else:
						for d_key, d_value in d.items():
							tmp[d_key] = d_value
				res.append(tmp)
		except Exception as e:

			res = 'No data: {}'.format(str(e))

		self.res = res
		self.status = True
		return 0


# 从IoT系统的服务器中删除设备
class IOT_DeleteDevice(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')

	def run(self):
		self.SdkCdll.IOT_DeleteDevice.argtype = (c_char_p)
		self.SdkCdll.IOT_DeleteDevice.restype = c_int
		code = self.SdkCdll.IOT_DeleteDevice(self.dev_id)
		return self.result(code)

	def result(self, code, res=None):
		return super().result(code, res)


# 从IoT系统的服务器中删除设备（扩展接口版本2）
class IOT_DeleteDevice2(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.force_delete = int(args.get('force_delete', 0))

	def run(self):
		self.cdll.IOT_DeleteDevice2.argtype = (c_char_p, c_int)
		self.cdll.IOT_DeleteDevice2.restype = c_int
		code = self.cdll.IOT_DeleteDevice2(self.dev_id, self.force_delete)
		return self.result(code)

	def result(self, code, res=None):
		return super().result(code, res)


# 从IoT系统的服务器中删除设备（扩展接口版本3，v4.0新增）
class IOT_DeleteDevice3(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.force_delete = int(args.get('force_delete', 0))
		self.delete_channels = int(args.get('delete_channels', 0))

	def run(self):
		self.SdkCdll.IOT_DeleteDevice3.argtype = (c_char_p, c_int, c_int)
		self.SdkCdll.IOT_DeleteDevice3.restype = c_int
		code = self.SdkCdll.IOT_DeleteDevice3(self.dev_id, self.force_delete, self.delete_channels)
		return self.result(code)

	def result(self, code, res=None):
		return super().result(code, res)


# 更新设备
class IOT_UpdateDevice(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.dev = (args.get('dev', None))
		self.syn_flag = int(args.get('syn_flag', 0))
		self.dev = struct_IotDeviceConfig()

		self.dev.vendor = int(args.get('vendor', 0))
		self.dev.type = int(args.get('type', 0))
		self.dev.anon_union = union_IotDeviceConfig()

		if self.dev.type == 0:
			self.dev.anon_union.rtsp_url = (args.get('rtsp_url', '')).encode('utf-8')

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

		self.SdkCdll.IOT_UpdateDevice.argtype = (c_char_p, POINTER(struct_IotDeviceConfig), c_int)
		self.SdkCdll.IOT_UpdateDevice.restype = c_int
		code = self.SdkCdll.IOT_UpdateDevice(self.dev_id, pointer(self.dev), self.syn_flag)
		dev = self.format_res(self.dev)
		return self.result(code, {"dev": dev})

	def result(self, code, res=None):
		return super().result(code, res)


# 设备版本查询
class IOT_GetDeviceVersion(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.info = struct_IotDeviceVersionInfo()

	def run(self):
		self.SdkCdll.IOT_GetDeviceVersion.argtype = (c_char_p, POINTER(struct_IotDeviceVersionInfo))
		self.SdkCdll.IOT_GetDeviceVersion.restype = c_int
		code = self.SdkCdll.IOT_GetDeviceVersion(self.dev_id, pointer(self.info))
		info = self.format_res(self.info)
		return self.result(code, {"info": info})

	def result(self, code, res=None):
		return super().result(code, res)


# 获取设备算法信息
class IOT_GetDeviceAlgorithmInfo(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.info = struct_IotDeviceAlgorithmInfo()

	def run(self):
		self.SdkCdll.IOT_GetDeviceAlgorithmInfo.argtype = (c_char_p, POINTER(struct_IotDeviceAlgorithmInfo))
		self.SdkCdll.IOT_GetDeviceAlgorithmInfo.restype = c_int
		code = self.SdkCdll.IOT_GetDeviceAlgorithmInfo(self.dev_id, pointer(self.info))
		status = self.format_res(self.info).get('status', 0)
		return self.result(code, {"status": status})

	def result(self, code, res=None):
		return super().result(code, res)


# 获取单个设备状态信息
class IOT_GetDeviceStatus(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.status = struct_IotDeviceStatus()

	def run(self):
		self.SdkCdll.IOT_GetDeviceStatus.argtype = (c_char_p, POINTER(struct_IotDeviceStatus))
		self.SdkCdll.IOT_GetDeviceStatus.restype = c_int
		code = self.SdkCdll.IOT_GetDeviceStatus(self.dev_id, pointer(self.status))
		status = self.format_res(self.status)
		return self.result(code, status)

	def result(self, code, res=None):
		return super().result(code, res)


# 获取IoT系统服务器中的单个设备的参数信息
class IOT_GetDeviceInfo(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.dev = (args.get('dev', None))
		self.dev = struct_IotDeviceConfig()

	def run(self):
		self.SdkCdll.IOT_GetDeviceInfo.argtype = (c_char_p, POINTER(struct_IotDeviceConfig))
		self.SdkCdll.IOT_GetDeviceInfo.restype = c_int
		code = self.SdkCdll.IOT_GetDeviceInfo(self.dev_id, pointer(self.dev))
		dev = self.format_res(self.dev)
		return self.result(code, {"dev": dev})

	def result(self, code, res=None):
		return super().result(code, res)


# 开视频流
class IOT_OpenLiveStream(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.user_data = (args.get('user_data', None))
		self.handle = c_int()
		CALLBACK = CFUNCTYPE(c_int, c_int, POINTER(struct_IotVideoFrameInfo), POINTER(c_uint8), c_int, c_char_p)
		self.system_define_cb = CALLBACK(self.system_define_cb_func)

	def run(self):
		self.SdkCdll.IOT_OpenLiveStream.argtype = (c_char_p, c_int, c_char_p, POINTER(c_int))
		self.SdkCdll.IOT_OpenLiveStream.restype = c_int
		code = self.SdkCdll.IOT_OpenLiveStream(self.dev_id, self.system_define_cb, self.user_data, pointer(self.handle))
		if code == 0:
			self.system_define_wait_func()
		else:
			return self.result(code)
		return self.result(code, {"handle": self.handle.value})

	def result(self, code, res=None):
		return super().result(code, res)

	def system_define_wait_func(self):
		time.sleep(2)

	def system_define_cb_func(self, handle, info, buf, len, user_data):
		return self.real_cb_func(handle, info, buf, len, user_data)

	def real_cb_func(self, handle, info, buf, len, user_data):

		_tmp = ''
		_res_list = []
		# print('>>>>>>')

		_key_list = [x[0] for x in struct_IotVideoFrameInfo._fields_]

		try:
			for i in range(1):
				_tmp = {}
				for _key in _key_list:
					_val_fixed = self.format_res(info[i].__getattribute__(_key))
					# _tmp[i].__setattr__(_key,_val_fixed)
					_tmp.update({_key: _val_fixed})
				_res_list.append(_tmp)
		# print(_tmp)
		except Exception as e:
			print(str(e))
			_res_list = ['No data: {}'.format(str(e))]

		# print('<<<<<<')
		self.res = _res_list

		return 0


# 关流
class IOT_CloseLiveStream(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.handle = int(args.get('handle', 0))

	def run(self):
		self.SdkCdll.IOT_CloseLiveStream.argtype = (c_int)
		self.SdkCdll.IOT_CloseLiveStream.restype = c_int
		code = self.SdkCdll.IOT_CloseLiveStream(self.handle)
		return self.result(code)

	def result(self, code, res=None):
		return super().result(code, res)


# 推流
class IOT_StartPushStream(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.stream_type = int(args.get('stream_type', 0))
		self.stream_way = int(args.get('stream_way', 0))
		self.profile_type = int(args.get('profile_type', 0))
		self.dest_addr = (args.get('dest_addr', '')).encode('utf-8')
		self.ext_info = (args.get('ext_info', '')).encode('utf-8')
		self.session_id = create_string_buffer(128)

	def run(self):
		self.SdkCdll.IOT_StartPushStream.argtype = (c_char_p, c_int, c_int, c_int, c_char_p, c_char_p, c_char_p)
		self.SdkCdll.IOT_StartPushStream.restype = c_int
		code = self.SdkCdll.IOT_StartPushStream(self.dev_id, self.stream_type, self.stream_way, self.profile_type,
												self.dest_addr, self.ext_info, self.session_id)
		return self.result(code, {"session_id": self.session_id.value.decode()})

	def result(self, code, res=None):
		return super().result(code, res)


# 查询推流配置参数信息
class IOT_QueryPushStreamInfo(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.session_id = (args.get('session_id')).encode('utf-8')
		self.ext_info = (args.get('ext_info', '123')).encode('utf-8')
		self.info_str = create_string_buffer(2 * 1024)
		self.info_len = 1024 * 1024 * 10240
		print("======================", args)

	def run(self):
		buf_len = c_int()
		buf_len.value = 10 * 1024
		self.SdkCdll.IOT_QueryPushStreamInfo.argtype = (c_char_p, c_char_p, POINTER(c_int), c_char_p)
		code = self.SdkCdll.IOT_QueryPushStreamInfo(self.session_id, self.info_str, pointer(buf_len), self.ext_info, )
		return self.result(code, {"info_str": self.info_str.value.decode()})

	def result(self, code, res=None):
		return super().result(code, res)


# 开启图片流
class IOT_OpenPictureStream(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.user_data = (args.get('user_data', None))
		self.handle = c_int()
		CALLBACK = CFUNCTYPE(c_int, c_int, POINTER(struct_IotCapPicturesInfo), c_char_p)
		self.system_define_cb = CALLBACK(self.system_define_cb_func)

	def run(self):

		self.SdkCdll.IOT_OpenPictureStream.argtype = (c_char_p, c_int, c_char_p, POINTER(c_int))
		self.SdkCdll.IOT_OpenPictureStream.restype = c_int
		code = self.SdkCdll.IOT_OpenPictureStream(self.dev_id, self.system_define_cb, self.user_data,
												  pointer(self.handle))
		if code == 0:
			self.system_define_wait_func()
		else:
			return self.result(code)
		return self.result(code, {"handle": self.handle.value})

	def result(self, code, res=None):
		return super().result(code, res)

	def system_define_wait_func(self):
		time.sleep(2)

	def system_define_cb_func(self, handle, info, user_data):
		return self.real_cb_func(handle, info, user_data)

	def real_cb_func(self, handle, info, user_data):

		_tmp = ''
		_res_list = []
		print('>>>>>>')
		_key_list = [x[0] for x in struct_IotCapPicturesInfo._fields_]
		try:
			for i in range(1):
				_tmp = {}
				for _key in _key_list:
					_val_fixed = self.format_res(info[i].__getattribute__(_key))

					# _tmp[i].__setattr__(_key,_val_fixed)
					_tmp.update({_key: _val_fixed})
				_res_list.append(_tmp)
		except Exception as e:
			print(str(e))
			_res_list = ['No data: {}'.format(str(e))]

		print('<<<<<<')
		self.res = _res_list

		return 0


# 开启图片流扩展接口2
class IOT_OpenPictureStream2(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.syn_flag = int(args.get('syn_flag', 0))
		self.user_data = (args.get('user_data', None))
		self.handle = c_int()
		CALLBACK = CFUNCTYPE(c_int, c_int, c_char_p, c_int, c_char_p, c_int, c_char_p)
		self.system_define_cb = CALLBACK(self.system_define_cb_func)

	def run(self):

		self.SdkCdll.IOT_OpenPictureStream2.argtype = (c_char_p, c_int, c_int, c_char_p, POINTER(c_int))
		self.SdkCdll.IOT_OpenPictureStream2.restype = c_int
		code = self.SdkCdll.IOT_OpenPictureStream2(self.dev_id, self.syn_flag, self.system_define_cb, self.user_data,
												   pointer(self.handle))

		if code == 0:
			self.system_define_wait_func()
		else:
			return self.result(code)

		return self.result(code, {"handle": self.handle.value})

	def result(self, code, res=None):
		return super().result(code, res)

	def system_define_wait_func(self):
		time.sleep(2)

	def system_define_cb_func(self, handle, text_buf, text_len, buf, buf_len, user_data):
		return self.real_cb_func(handle, text_buf, text_len, buf, buf_len, user_data)

	def real_cb_func(self, handle, text_buf, text_len, buf, buf_len, user_data):

		_tmp = ''
		_res_list = []
		print('>>>>>>')
		print("buf_len", buf_len)
		print("text_buf", text_buf)
		import json
		print("text_len", text_len)
		print("buf", json.dumps(buf))

		print('<<<<<<')
		self.res = _res_list

		return 0


# 关闭图片流
class IOT_ClosePictureStream(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.handle = int(args.get('handle', 0))

	def run(self):
		self.SdkCdll.IOT_ClosePictureStream.argtype = (c_int)
		self.SdkCdll.IOT_ClosePictureStream.restype = c_int
		code = self.SdkCdll.IOT_ClosePictureStream(self.handle)
		return self.result(code)

	def result(self, code, res=None):
		return super().result(code, res)


# 开启设备录像
class IOT_StartDeviceRecord(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		print(11111)
		print(args)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.record_type = int(args.get('record_type', 2))  # 默认磁盘缓存
		self.period = int(args.get('period', 30))  # 默认30s
		self.res = (args.get('res', '')).encode('utf-8')

	def run(self):
		self.SdkCdll.IOT_StartDeviceRecord.argtype = (c_char_p, c_int, c_int, c_char_p)
		self.SdkCdll.IOT_StartDeviceRecord.restype = c_int
		code = self.SdkCdll.IOT_StartDeviceRecord(self.dev_id, self.record_type, self.period, self.res)
		return self.result(code)

	def result(self, code, res=None):
		return super().result(code, res)


# 关闭录像
class IOT_StopDeviceRecord(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.record_type = int(args.get('record_type', 2))  # 默认磁盘

	def run(self):
		self.SdkCdll.IOT_StopDeviceRecord.argtype = (c_char_p, c_int)
		self.SdkCdll.IOT_StopDeviceRecord.restype = c_int
		code = self.SdkCdll.IOT_StopDeviceRecord(self.dev_id, self.record_type)
		return self.result(code)

	def result(self, code, res=None):
		return super().result(code, res)


# 获取录像信息
class IOT_GetDeviceRecordInfo(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.record_type = int(args.get('record_type', 2))  # 默认获取磁盘
		self.period = c_int()
		self.cfg = create_string_buffer(24)

	def run(self):
		self.SdkCdll.IOT_GetDeviceRecordInfo.argtype = (c_char_p, c_int, POINTER(c_int), c_char_p)
		self.SdkCdll.IOT_GetDeviceRecordInfo.restype = c_int
		code = self.SdkCdll.IOT_GetDeviceRecordInfo(self.dev_id, self.record_type, pointer(self.period), self.cfg)
		return self.result(code, {"period": self.period.value, "cfg": self.cfg.value.decode()})

	def result(self, code, res=None):
		return super().result(code, res)


# 设置录像信息
class IOT_SetDeviceRecordInfo(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.record_type = int(args.get('record_type', 2))
		self.period = int(args.get('period', 15))
		self.cfg = (args.get('cfg', '')).encode('utf-8')

	def run(self):
		self.SdkCdll.IOT_SetDeviceRecordInfo.argtype = (c_char_p, c_int, c_int, c_char_p)
		self.SdkCdll.IOT_SetDeviceRecordInfo.restype = c_int
		code = self.SdkCdll.IOT_SetDeviceRecordInfo(self.dev_id, self.record_type, self.period, self.cfg)

		return self.result(code)

	def result(self, code, res=None):
		return super().result(code, res)


# 批量更新推流配置参数信息
class IOT_BatchUpdatePushStreamInfo(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)
		print("-----------------")
		print(args)

		self.req_info = (args.get('req_info')).encode('utf-8')

		self.ext_info = (args.get('ext_info', ' ')).encode('utf-8')

	def run(self):
		self.SdkCdll.IOT_BatchUpdatePushStreamInfo.argtype = (c_char_p, c_char_p)

		code = self.SdkCdll.IOT_BatchUpdatePushStreamInfo(self.req_info, self.ext_info)

		return self.result(code)

	def result(self, code, res=None):
		return super().result(code, res)


# 打开图片流  支持1400
class IOT_OpenPictureStream4(SdkBase):
	def __init__(self, args=None):
		super().__init__(ARGS)

		self.chan_id = (args.get('chan_id', '')).encode('utf-8')

		self.sync_flag = int(args.get('sync_flag', 0))

		self.user_data = (args.get('user_data', None))

		self.handle = c_int()

		self.ext_info = (args.get('ext_info', '')).encode('utf-8')

		CALLBACK = CFUNCTYPE(c_int, c_int, c_char_p, POINTER(c_int), POINTER(c_uint8), c_char_p)
		self.system_define_cb = CALLBACK(self.system_define_cb_func)

	def run(self):

		self.SdkCdll.IOT_OpenPictureStream4.argtype = (c_char_p, c_int, c_int, c_char_p, POINTER(c_int), c_char_p)
		self.SdkCdll.IOT_OpenPictureStream4.restype = c_int
		code = self.SdkCdll.IOT_OpenPictureStream4(self.chan_id, self.sync_flag, self.system_define_cb, self.user_data,
												   pointer(self.handle), self.ext_info)

		if code == 0:
			self.system_define_wait_func()
		else:
			return self.result(code)

		return self.result(code, {"handle": self.handle.value})

	def result(self, code, res=None):
		return super().result(code, res)

	def system_define_wait_func(self):
		time.sleep(5)

	def system_define_cb_func(self, handle, pic_info, pic_len, pic_data, user_data):
		return self.real_cb_func(handle, pic_info, pic_len, pic_data, user_data)

	def real_cb_func(self, handle, pic_info, pic_len, pic_data, user_data):

		_tmp = ''
		_res_list = []
		print('>>>>>>')
		print(pic_info)

		print('<<<<<<')
		self.res = _res_list

		return 0


# 获取关键帧
class IOT_GetKeyFrame(SdkBase):
	'''
		获取关键帧
		args:
			dev_id:
			len:
			buf:
		returns:
			成功返回0，失败返回相应错误码
	'''

	def __init__(self, args=None):
		super().__init__(ARGS)
		self.log.info(args)
		self.dev_id = (args.get('dev_id', '')).encode('utf-8')
		self.len = args.get('len', 10 * 1024 * 1024)
		self.info = struct_IotVideoFrameInfo()

	def run(self):

		buf_buf = (c_uint8 * self.len)()
		buf_len = c_int()
		buf_len.value = self.len
		self.SdkCdll.IOT_GetKeyFrame.argtype = (
			c_char_p, POINTER(struct_IotVideoFrameInfo), POINTER(c_int), POINTER(c_int))
		code = self.SdkCdll.IOT_GetKeyFrame(self.dev_id, pointer(self.info), pointer(buf_buf), pointer(buf_len))

		return self.result(code, (buf_len.value, buf_buf))

	def result(self, code, res=None):

		if code:
			return super().result(code, None)
		else:
			(buf_len, buf) = res
			r = super().result(code, res)
			file_name = '/tmp/iframe-' + self.dev_id.decode('utf-8')
			# 这块赋值有问题, 应该是二进制写入, 转了之后有差异, 需要后期完善, 文件方可使用
			with open(file_name, 'wb') as fp:
				write_buf = ''.join([str(x) for x in buf[:buf_len + 1]])
				fp.write(write_buf.encode('utf-8'))

			r['data'] = {'len': buf_len, 'iframe_addr': file_name}

			return r


# 批量获取设备装

class IOT_BatchGetDeviceStatus(SdkBase):
	'''
		获取设备状态接口(批量)
		args:
			dev_list: 设备id列表
			dev_num: 设备数量
		returns:
			返回格式化之后的信息列表, list类型, list中的每项为dict类型
	'''

	def __init__(self, args):
		super().__init__(ARGS)
		self.dev_list = args.get('dev_list')
		self.dev_num = len(self.dev_list)

	def run(self):
		c_dev_list = ((c_char * 24) * 100)()
		dev_infos = (struct_IotDeviceStatus * self.dev_num)()
		self.SdkCdll.VIOT_BatchGetDeviceStatus.argtype = (c_int, c_char_p, POINTER(struct_IotDeviceStatus * self.dev_num))

		for index, _dev_id in enumerate(self.dev_list):
			c_dev_list[index].value = _dev_id.encode('utf-8')
			print("[python][" + str(index) + "] dev_id = " + str(c_dev_list[index].value.decode()))

		code = self.SdkCdll.VIOT_BatchGetDeviceStatus(self.dev_num, c_dev_list, pointer(dev_infos))
		dev_infos = self.format_res(dev_infos)
		return self.result(code, dev_infos)

	def result(self, code, res=None):
		res_dict = super().result(code, res)

		if not res_dict['code']:
			for index, _dev in enumerate(self.dev_list):
				res_dict['data'][index]['dev_id'] = _dev

		return res_dict


#获取视频参数
class IOT_GetVideoParam(SdkBase):
    def __init__(self, args=None):
        super().__init__(ARGS)
        self.dev_id = (args.get('dev_id','')).encode('utf-8')
        self.profile_type = int(args.get('profile_type',0))
        self.info = (args.get('info',None))
        self.info = struct_IotVideoStreamParam()

    def run(self):
        self.SdkCdll.IOT_GetVideoParam.argtype = (c_char_p,c_int,POINTER(struct_IotVideoStreamParam))
        self.SdkCdll.IOT_GetVideoParam.restype = c_int
        code = self.SdkCdll.IOT_GetVideoParam(self.dev_id,self.profile_type, pointer(self.info))
        info = self.format_res(self.info)
        info.pop('res', None)
        return self.result(code, info)

    def result(self, code, res=None):
        return super().result(code,res)


#PTZ预置点设置
class IOT_PtzPreset(SdkBase):
    def __init__(self, args=None):
        super().__init__(ARGS)
        self.dev_id = (args.get('dev_id','')).encode('utf-8')
        self.chan_no = int(args.get('chan_no',0))
        self.cmd = int(args.get('cmd',0))
        self.index = int(args.get('index',1))
        self.param1 = int(args.get('param1',0))
        self.param2 = int(args.get('param2',0))
        self.param3 = c_int()

    def run(self):
        self.SdkCdll.IOT_PtzPreset.argtype = (c_char_p,c_int,c_int,c_int,c_int,c_int,POINTER(c_int))
        self.SdkCdll.IOT_PtzPreset.restype = c_int
        code = self.SdkCdll.IOT_PtzPreset(self.dev_id,self.chan_no,self.cmd,self.index,self.param1,self.param2,pointer(self.param3))
        return self.result(code, {"param3": self.param3.value})

    def result(self, code, res=None):
        return super().result(code,res)
#设备云台 镜头控制
class IOT_PtzControl(SdkBase):
    def __init__(self, args=None):
        super().__init__(ARGS)
        self.dev_id = (args.get('dev_id','')).encode('utf-8')
        self.chan_no = int(args.get('chan_no',0))
        self.ptz_cmd = int(args.get('ptz_cmd',0))
        self.speed = int(args.get('speed',0))
        self.stop = int(args.get('stop',0))

    def run(self):
        self.SdkCdll.IOT_PtzControl.argtype = (c_char_p,c_int,c_int,c_int,c_int)
        self.SdkCdll.IOT_PtzControl.restype = c_int
        code = self.SdkCdll.IOT_PtzControl(self.dev_id,self.chan_no,self.ptz_cmd,self.speed,self.stop)
        return self.result(code)

    def result(self, code, res=None):
        return super().result(code,res)
#获取设备分辨率能力集
class IOT_GetResolutionCap(SdkBase):
    def __init__(self, args=None):
        super().__init__(ARGS)

        self.dev_id = (args.get('dev_id','')).encode('utf-8')
        self.profile_type = int(args.get('profile_type',0))
        self.info = (args.get('info', None))
        self.info = struct_IotResolutionCapability()

    def run(self):
        self.SdkCdll.IOT_GetResolutionCap.argtype = (c_char_p,c_int,POINTER(struct_IotResolutionCapability))
        self.SdkCdll.IOT_GetResolutionCap.restype = c_int
        code = self.SdkCdll.IOT_GetResolutionCap(self.dev_id,self.profile_type,pointer(self.info))
        info = self.format_res(self.info)
        # info.pop('list', None)
        return self.result(code, info)

    def result(self, code, res=None):
        return super().result(code,res)

#获取设备模式能力集
class IOT_GetCameraModeCap(SdkBase):
    def __init__(self, args=None):
        super().__init__(ARGS)

        self.dev_id = (args.get('dev_id','')).encode('utf-8')
        self.info = (args.get('info',None))
        self.info = struct_IotCameraModeCapability()

    def run(self):
        self.SdkCdll.IOT_GetCameraModeCap.argtype = (c_char_p,POINTER(struct_IotCameraModeCapability))
        self.SdkCdll.IOT_GetCameraModeCap.restype = c_int
        code = self.SdkCdll.IOT_GetCameraModeCap(self.dev_id,pointer(self.info))
        info = self.format_res(self.info)
        info.pop('list', None)
        return self.result(code, info)

    def result(self, code, res=None):
        return super().result(code,res)

#获取相机模式参数
class IOT_GetCameraMode(SdkBase):
    def __init__(self, args=None):
        super().__init__(ARGS)
        self.dev_id = (args.get('dev_id','')).encode('utf-8')
        self.mode = c_int()
        self.res = create_string_buffer(24)

    def run(self):
        self.SdkCdll.IOT_GetCameraMode.argtype = (c_char_p,POINTER(c_int),c_char_p)
        self.SdkCdll.IOT_GetCameraMode.restype = c_int
        code = self.SdkCdll.IOT_GetCameraMode(self.dev_id,pointer(self.mode),self.res)
        return self.result(code,{"mode":self.mode.value,"res":self.res.value.decode()})

    def result(self, code, res=None):
        return super().result(code, res)

# 设置相机模式参数
class IOT_SetCameraMode(SdkBase):
    def __init__(self, args=None):
        super().__init__(ARGS)
        self.dev_id = (args.get('dev_id','')).encode('utf-8')
        self.mode = int(args.get('mode',0))
        self.res = (args.get('res', '')).encode('utf-8')

    def run(self):
        self.SdkCdll.IOT_SetCameraMode.argtype = (c_char_p,c_int,c_char_p)
        self.SdkCdll.IOT_SetCameraMode.restype = c_int
        code = self.SdkCdll.IOT_SetCameraMode(self.dev_id,self.mode,self.res)
        return self.result(code)

    def result(self, code, res=None):
        return super().result(code,res)

#获取设备报警输入端子配置信息
class IOT_GetAlarmInConfig(SdkBase):
    def __init__(self, args=None):
        super().__init__(ARGS)
        self.dev_id = (args.get('dev_id','')).encode('utf-8')
        self.chan_no = int(args.get('chan_no',0))
        self.cfg = (args.get('cfg',None))
        self.cfg = struct_IotAlarmInConfig()

    def run(self):
        self.SdkCdll.IOT_GetAlarmInConfig.argtype = (c_char_p,c_int,POINTER(struct_IotAlarmInConfig))
        self.SdkCdll.IOT_GetAlarmInConfig.restype = c_int
        code = self.SdkCdll.IOT_GetAlarmInConfig(self.dev_id,self.chan_no,pointer(self.cfg))
        cfg = self.format_res(self.cfg)
        cfg.pop('res', None)
        return self.result(code, cfg)

    def result(self, code, res=None):
        return super().result(code,res)


#设置设备报警输入端子配置信息
class IOT_SetAlarmInConfig(SdkBase):
    def __init__(self, args=None):
        super().__init__(ARGS)
        self.dev_id = (args.get('dev_id','')).encode('utf-8')
        self.chan_no = int(args.get('chan_no',0))
        self.cfg = struct_IotAlarmInConfig()
        self.cfg.alarm_mode = args.get('cfg', {}).get('alarm_mode', 0)
        self.cfg.enabled = args.get('cfg', {}).get('enabled', 0)

    def run(self):

        self.SdkCdll.IOT_SetAlarmInConfig.argtype = (c_char_p,c_int,POINTER(struct_IotAlarmInConfig))
        self.SdkCdll.IOT_SetAlarmInConfig.restype = c_int
        code = self.SdkCdll.IOT_SetAlarmInConfig(self.dev_id, self.chan_no,pointer(self.cfg))
        cfg = self.format_res(self.cfg)
        cfg.pop('res', None)
        return self.result(code, cfg)

    def result(self, code, res=None):
        return super().result(code,res)
# from config.normal import *
# from API.Other.Message_callback import *
# #
# sdk_ = SdkBase(args=ARGS)
# # IOT_SetMessageCallback(args = ARGS).run()
# sdk_.start_server()
# rst = IOT_BatchGetDeviceStatus({'dev_list': ['101234200300000011']}).run()
# print(rst)
# print(rst)
# while 1:
# 	pass
