#coding:utf-8
'''
author:
function:国标/1400接口测试
param:
other
'''
import pytest
import os,sys
import allure
current=os.path.abspath('../')
print("path",current)
sys.path.append(current)
from util.log import *
from case.common import *
from API.Device.device import *
import copy
dev_id_info = []

@allure.title("国标相关")
class Test_gb:

	pass

