#coding:utf-8
'''
author:
function: 设备操作相关
param:
other
'''
from API.base.sdk_base import *
from API.base.structure import *
import time
#log
from util.log import *
log = log_txt(loggername=__name__).log_init()


#添加设备
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


#获取设备列表

class IOT_GetDeviceList(SdkBase):
    def __init__(self, args=None):
        super().__init__(args)
        self.user_data = (args.get('user_data',None))
        CALLBACK = CFUNCTYPE(c_int, POINTER(struct_IotDeviceInfo),c_int,c_char_p)
        self.system_define_cb = CALLBACK(self.system_define_cb_func)
        self.status = False

    def run(self):
        self.SdkCdll.IOT_GetDeviceList.argtype = (c_int,c_char_p)
        self.SdkCdll.IOT_GetDeviceList.restype = c_int
        code = self.SdkCdll.IOT_GetDeviceList(self.system_define_cb,self.user_data)

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
        return self.real_cb_func(dev_list,dev_num,user_data)

    def real_cb_func(self, dev_list,dev_num, user_data):
        key_list = [ x[0] for x in struct_IotDeviceInfo._fields_ ]
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

#删除设备
class IOT_DeleteDevice(SdkBase):
    def __init__(self, args=None):
        super().__init__(args)
        self.dev_id = (args.get('dev_id','')).encode('utf-8')

    def run(self):
        self.SdkCdll.IOT_DeleteDevice.argtype = (c_char_p)
        self.SdkCdll.IOT_DeleteDevice.restype = c_int
        code = self.SdkCdll.IOT_DeleteDevice(self.dev_id)
        return self.result(code)

    def result(self, code, res=None):
        return super().result(code,res)

