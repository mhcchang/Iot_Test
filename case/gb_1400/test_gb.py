#coding:utf-8
'''
author:
function:国标/1400接口测试
param:
other
'''
import os,sys

current=os.path.abspath('../')
sys.path.append(current)
from API.Device.fore_two_three.device import *
import allure
from case.common import *
from API.Device.fore_two_three.device import *
from  config.normal import *
import  copy
dev_id_info = []
#创建gb环境
url_gb = '/home/haobingzhong' + '/gb_lite_linux'
print(url_gb)
import json

class Test_GB():
	@allure.title("添加国标设备")
	@allure.step("step:添加国标设备")
	@pytest.mark.smoke
	@pytest.mark.order(1)
	def test_IOT_AddDevice(self):

		with allure.step('step1:注冊'):
			self.sdk=register_iot()
		with allure.step('step2:清除设备环境'):
			self.sdk.delete_all()
			time.sleep(2)
			pass
		with allure.step('step3:开启gb模拟平台'):
			print(url_gb)
			import json
			with open(url_gb + '/param.json', 'r') as gb:
				gb_info = json.load(gb)
			with open(url_gb + '/param.json', 'w') as gb:
				gb_info['upper_ip'] = SDK_IP
				json.dump(gb_info, gb)
			status = os.system('sudo bash gb.sh')
			print(status)
		result = IOT_AddDevice(args=gb_device[0]).run()
		global dev_id_info
		dev_id_info = copy.deepcopy(gb_device)
		assert result['code'] == 0,result
		dev_id_info[0].setdefault('dev_id',result['data']['dev']['dev_id'])

	@allure.title('开启图片流')
	@allure.step('step：开启图片流')
	@pytest.mark.order(8)
	@pytest.mark.flaky(returns=1)
	def test_IOT_OpenPictureStream(self):

		result = IOT_OpenPictureStream(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		assert result['code'] == 0,result
		dev_id_info[0]['handle'] = result['data']['handle']



	@allure.title('关闭图片流')
	@allure.step('step：关闭图片流')
	@pytest.mark.order(9)
	@pytest.mark.flaky(returns=2)
	def test_IOT_ClosePictureStream(self):
		log.info(dev_id_info[0])
		result = IOT_ClosePictureStream(args={'handle':dev_id_info[0].get('handle','')}).run()
		assert result['code'] == 0,result


	@allure.title('开启设备录像')
	@allure.step('step：开启设备录像')
	@pytest.mark.order(10)
	@pytest.mark.flaky(returns=2)
	def test_IOT_StartDeviceRecord(self):
		log.info(dev_id_info[0])
		result = IOT_StartDeviceRecord(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		assert result['code'] == 0,result


	@allure.title('获取录像参数')
	@allure.step('step：获取录像参数')
	@pytest.mark.order(11)
	@pytest.mark.flaky(returns=2)
	def test_IOT_StopDeviceRecord(self):
		log.info(dev_id_info[0])
		result = IOT_GetDeviceRecordInfo(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		assert result['code'] == 0,result




	@allure.title('设置录像参数')
	@allure.step('step：设置录像参数')
	@pytest.mark.order(12)
	@pytest.mark.flaky(returns=2)
	def test_IOT_SetDeviceRecordInfo(self):
		log.info(dev_id_info[0])
		result = IOT_SetDeviceRecordInfo(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		assert result['code'] == 0,result


	@allure.title('关闭设备录像')
	@allure.step('step：关闭设备录像')
	@pytest.mark.order(13)
	@pytest.mark.flaky(returns=2)
	def test_IOT_StopDeviceRecord(self):
		log.info(dev_id_info[0])
		result = IOT_StopDeviceRecord(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		assert result['code'] == 0,result


	@allure.title('获取关键帧')
	@allure.step('step:获取关键帧')
	@pytest.mark.order(14)
	def	test_IOT_GetKeyFrame(self):
		time.sleep(3)
		result = IOT_GetKeyFrame(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		assert result['code'] == 0, result
#
# if __name__ == '__main__':
# 	pytest.main(["-s","test_gb.py"])