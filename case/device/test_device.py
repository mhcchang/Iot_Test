#coding:utf-8
'''
author:
function:
		添加设备  IOT_AddDevice
		pytest.mark.first
		order 执行顺序从小到大
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
from  json import dumps,loads
@allure.title("设备相关")
class Test_Device():
	'''IOT_AddDevice接口测试'''
	log = log_txt(loggername=__name__).log_init()
	def setup(self):
		pass
	@allure.title("添加设备")
	@allure.step("step:添加设备")
	@pytest.mark.smoke
	@pytest.mark.order(1)
	def test_IOT_AddDevice(self):
		with allure.step('step1:注冊'):
			self.sdk=register_iot()
		with allure.step('step2:清除设备环境'):
			self.sdk.delete_all()
			time.sleep(2)
			pass
		result = IOT_AddDevice(args=dev_info[0]).run()
		global dev_id_info
		dev_id_info = copy.deepcopy(dev_info)
		log.info(result)
		assert result['code'] == 0
		dev_id_info[0].setdefault('dev_id',result['data']['dev']['dev_id'])

	@allure.title('更新设备')
	@allure.step('step:更新设备')
	@pytest.mark.order(2)
	@pytest.mark.smoke
	def test_IOT_UpdateDevice(self):
		global dev_id_info
		result = IOT_UpdateDevice(args=dev_id_info[0]).run()
		log.info(result)
		assert result['code'] == 0



	@allure.title('列举设备')
	@allure.step('step:列举设备')
	@pytest.mark.order(2)
	@pytest.mark.smoke
	def test_IOT_GetDeviceList(self):
		result = IOT_GetDeviceList(args={}).run()
		log.info(result)
		assert result['code'] == 0



	@allure.title('设备版本查询')
	@allure.step('step:设备版本查询')
	@pytest.mark.order(3)
	@pytest.mark.smoke
	@pytest.mark.skipif(condition=(dev_info[1]['GetDeviceVersion']=='false'),reason='设备不支持')
	def test_IOT_GetDeviceVersion(self):
		result = IOT_GetDeviceVersion(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		log.info(result)
		assert result['code'] == 0



	@allure.title('获取设备算法信息')
	@allure.step('step:获取设备算法信息')
	@pytest.mark.order(4)
	@pytest.mark.flaky(returns=2)
	@pytest.mark.skipif(condition=(dev_info[1]['version']=='false'),reason='设备不支持')
	@pytest.mark.smoke
	def test_IOT_GetDeviceAlgorithmInfo(self):
		time.sleep(1)
		log.info(dev_id_info)
		result = IOT_GetDeviceAlgorithmInfo(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		assert result['code'] == 0,result



	@allure.title('获取单个设备状态信息')
	@allure.step('step:获取单个设备状态信息')
	@pytest.mark.order(3)
	@pytest.mark.skipif(condition=(dev_info[1]['version']=='false'),reason='设备不支持')
	@pytest.mark.smoke
	def test_IOT_GetDeviceStatus(self):
		result = IOT_GetDeviceStatus(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		assert result['code'] == 0,result



	@allure.title('获取单个设备的参数信息')
	@allure.step('step:获取单个设备的参数信息')
	@pytest.mark.skipif(condition=(dev_info[1]['version']=='false'),reason='设备不支持')
	@pytest.mark.order(3)
	@pytest.mark.smoke
	def test_IOT_GetDeviceStatus(self):
		result = IOT_GetDeviceInfo(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		allure.attach.file('/home/haobingzhong/Study_Test/Iot_Test/case/device/11.txt', 'name', attachment_type=allure.attachment_type.TEXT)
		assert result['code'] == 0,result


	@allure.title('开视频流操作')
	@allure.step('step：开视频流操作')
	@pytest.mark.order(4)
	@pytest.mark.flaky(returns=2)
	def test_IOT_OpenLiveStream(self):
		result = IOT_OpenLiveStream(args={'dev_id':dev_id_info[0].get('dev_id','')}).run()
		assert result['code'] == 0,result
		dev_id_info[0].setdefault('handle', result['data']['handle'])



	@allure.title('关视频流操作')
	@allure.step('step：关视频流操作')
	@pytest.mark.order(5)
	@pytest.mark.flaky(returns=1)
	def test_IOT_CloseLiveStream(self):

		result = IOT_CloseLiveStream(args={'handle':dev_id_info[0].get('handle','')}).run()
		assert result['code'] == 0,result


	@allure.title('转存core')
	@allure.step('step：转存core')
	@pytest.mark.order(6)
	@pytest.mark.flaky(returns=1)
	def test_IOT_StartPushStream(self):

		result = IOT_StartPushStream(args={'dev_id':dev_id_info[0].get('dev_id',''),'dest_addr':"http://10.235.97.220:8021/"}).run()
		assert result['code'] == 0,result
		dev_id_info[0].setdefault('session', result['data']['session_id'])



	@allure.title('查询推流配置参数信息')
	@allure.step('step：查询推流配置参数信息')
	@pytest.mark.order(7)
	@pytest.mark.flaky(returns=1)
	@pytest.mark.skip(reason='接口有问题')
	def test_IOT_QueryPushStreamInfo(self):

		result = IOT_QueryPushStreamInfo(args={'session_id':dev_id_info[0].get('session','')}).run()
		assert result['code'] == 0,result


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



# if __name__ == '__main__':
	# pytest.main(["-s","."])
