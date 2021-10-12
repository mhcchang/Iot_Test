#coding:utf-8
'''
公共库

'''
import  pytest,sys,os

from case.public.down.unregister import unregister_iot
from case.public.setup.register import register_iot
from API.base.sdk_base import  SdkBase
from config.device_info.device import *
from  case.common.get_msgCode import get_code_meg as get_error
from config.normal import SDK_VERSION
if SDK_VERSION == '4.2.3':
	from API.Device.fore_two_three.device import *
else:
	print('不存在此版本~~~~')
	exit(0)