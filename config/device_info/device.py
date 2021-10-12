# coding:utf-8
'''
author:
function:设信息相关
param:
other
'''
dev_info = [{
	'device':{  # 设备参数
		"addr": "10.171.129.5",
		"video_port": 554,
		"password": "admin123",
		"vendor": 51,
		"username": "admin",
		"type": 2,
		"port": 3000,
		'extra_info': ''
	},
	'param':{#支持参数
		'ptz': 'true',  # 支持ptz
		'version': 'true',  # 支持查询版本
		'sdk_param':'true',#支持走sdk接口
		"uuid": "uuid",
		'GetDeviceVersion': 'false',  #
		"dest_addr": "http://10.235.97.220:8021/",  # 转存地址
		"stream_way": 0,  # 码流方式
		"stream_type": 0,  # 码流类型
		"profile_type": 0  #

	}
}

]

# 视图库
gb_device = [
	{  # 设备参数
		"type": 3,
		"vendor": 4,
		'platform_id': '11010800002005000011',
		'device_code': '11010800002155000001',
		'extra_info': ''
	},

]
# 国标
# 其它
