##coding:utf-8
from  ctypes import  *
import os
from util.log import *
import os

class SdkBase(object):
		'''
			初始化sdk接口
		'''
		def __init__(self,args):
			#{"ip":"","port":"","user":"","pwd":"","version":"4.2.3"}
			# log_colors = log_colors_config
			current_path = os.path.abspath(os.path.dirname(os.path.dirname(os.path.dirname(__file__))))
			print(current_path)
			from config.normal import SDK_VERSION
			Base_url = '''/version/''' + SDK_VERSION + '/'
			os.environ['LD_LIBRARY_PATH'] = current_path +Base_url

			current=os.path.abspath(os.path.dirname(os.path.dirname(os.path.dirname(__file__))))
			self.log = log_txt(loggername=__name__).log_init()
			version=args.get('version','4.2.3')
			if version == '3.3' :
				path=''
			elif version == '4.1':
				path=current+Base_url + '/libiotcenterclient.so'
			elif version == '4.2':
				path=''
			elif version == '4.2.3':
				path=current + Base_url + '/libiotcenterclient.so'
			SdkCdll=cdll.LoadLibrary(path)
			self.SdkCdll = SdkCdll
			self.ip = args.get("ip")
			self.port = args.get('_port')
			self.usr = args.get('_user')
			self.pwd = args.get('_pwd')
		def start_server(self):
			self.SdkCdll.IOT_Startup()
			self.SdkCdll.IOT_SetConnectInfo(2000, 2, 1)
			code = self.SdkCdll.IOT_Register(self.ip.encode('utf-8'), int(self.port),
										  self.usr.encode('utf-8'),self.pwd.encode('utf-8'))
			return code

		def close_server(self):

			code = self.SdkCdll.IOT_Unregister()
			return code
		def clear_UP(self):
			code = self.SdkCdll.IOT_Cleanup()
			return code

		def get_error_msg(self, code):
			'''
				通过给定的错误码返回相应的错误描述
				args:
					code: 错误码 int类型
				returns:
					错误描述  string类型
			'''
			self.SdkCdll.IOT_GetErrorDescription.argtype = c_int
			self.SdkCdll.IOT_GetErrorDescription.restype = c_char_p
			error_msg = self.SdkCdll.IOT_GetErrorDescription(int(code))
			return error_msg.decode()

		def format_res(self, res):
			'''
				结果格式化
			'''
			if res is None:
				return []

			if isinstance(res, bytes):
				res = str(res, encoding="utf-8")

			if isinstance(res, list):
				new_res = []
				for r in res:
					if isinstance(r, bytes):
						new_r = str(r, encoding="utf-8")
						new_res.append(new_r)
					else:
						new_res.append(r)

				formated_res = res
			else:
				formated_res = res

			if isinstance(res, (Structure)):
				formated_res = self._format_res(res)

			if isinstance(res, Array):
				res_l = []

				for r in res:
					res_l.append(self._format_res(r))

				formated_res = res_l

			if isinstance(res, dict):
				formated_res = []
				for _k, _v in res.items():
					formated_res.append({_k: self.format_res(_v)})


			return formated_res

		def _format_res(self, res):
			'''
				结果格式化
			'''
			type_list = ['type', 'pic_type']
			if isinstance(res, Structure):
				res_d = {}
				for _n, _t in res._fields_:

					x = res.__getattribute__(_n)
					if isinstance(x, Union):

						union_data = self.format_union(x)
						res_d.update(union_data)
					else:
						if isinstance(_n, bytes):
							_n = str(_n, encoding='utf-8')
						# 	res_d.update(self.format_res(res))
						# else:
						res_d[_n] = self.format_res(x) if isinstance(x, (Structure, Array)) else x
						if isinstance(res_d[_n], bytes):
							# res_d[_n] = res_d[_n].encode()
							res_d[_n] = "".join(map(chr, res_d[_n]))

			else:
				res_d = res

			return res_d
		def format_union(self, res):
			data = {}
			for u_key, u_value in res._fields_:
				u_data = res.__getattribute__(u_key)
				union_data = self.format_res(u_data)
				if union_data and isinstance(union_data, dict):
					data.update(union_data)
			return data
		def result(self, code, res):
			res_dict = {
				"code": code,
				"data": res,
				"msg": self.get_error_msg(code) if code else "success"
			}
			return res_dict
# SdkBase({"ip":"10.172.198.43","_port":"8500","_user":"admin","_pwd":"admin","version":"4.2.3"}).start_server()