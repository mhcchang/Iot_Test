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
import os,sys,time
import allure

from case.common import *
import sys

import copy
dev_id_info = []

from util.log import *
dev_ = dev_info[0]
dev_is = dev_['device']
dev_param = dev_['param']
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
		result = IOT_AddDevice(args=dev_is).run()
		global dev_id_info
		dev_id_info = copy.deepcopy(dev_is)
		log.info(result)
		assert result['code'] == 0
		dev_id_info.setdefault('dev_id',result['data']['dev']['dev_id'])

	@allure.title('更新设备')
	@allure.step('step:更新设备')
	@pytest.mark.order(2)
	@pytest.mark.smoke
	def test_IOT_UpdateDevice(self):
		global dev_id_info
		result = IOT_UpdateDevice(args=dev_id_info).run()
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
	@pytest.mark.skipif(condition=(dev_param['GetDeviceVersion']=='false'),reason='设备不支持')
	def test_IOT_GetDeviceVersion(self):
		result = IOT_GetDeviceVersion(args={'dev_id':dev_id_info.get('dev_id','')}).run()
		log.info(result)
		assert result['code'] == 0



	@allure.title('获取设备算法信息')
	@allure.step('step:获取设备算法信息')
	@pytest.mark.order(4)
	@pytest.mark.flaky(returns=2)
	@pytest.mark.skipif(condition=(dev_param['version']=='false'),reason='设备不支持')
	@pytest.mark.smoke
	def test_IOT_GetDeviceAlgorithmInfo(self):
		time.sleep(1)
		log.info(dev_id_info)
		result = IOT_GetDeviceAlgorithmInfo(args={'dev_id':dev_id_info.get('dev_id','')}).run()
		assert result['code'] == 0,result



	@allure.title('获取单个设备状态信息')
	@allure.step('step:获取单个设备状态信息')
	@pytest.mark.order(3)
	@pytest.mark.skipif(condition=(dev_param['version']=='false'),reason='设备不支持')
	@pytest.mark.smoke
	def test_IOT_GetDeviceStatus(self):
		result = IOT_GetDeviceStatus(args={'dev_id':dev_id_info.get('dev_id','')}).run()
		assert result['code'] == 0,result



	@allure.title('获取单个设备的参数信息')
	@allure.step('step:获取单个设备的参数信息')
	@pytest.mark.skipif(condition=(dev_param['version']=='false'),reason='设备不支持')
	@pytest.mark.order(3)
	@pytest.mark.smoke
	def test_IOT_GetDeviceStatus(self):
		result = IOT_GetDeviceInfo(args={'dev_id':dev_id_info.get('dev_id','')}).run()
		# allure.attach.file('/home/haobingzhong/Study_Test/Iot_Test/case/device/11.txt', 'name', attachment_type=allure.attachment_type.TEXT)
		assert result['code'] == 0,result


	@allure.title('开视频流操作')
	@allure.step('step：开视频流操作')
	@pytest.mark.order(4)
	@pytest.mark.flaky(returns=2)
	def test_IOT_OpenLiveStream(self):
		result = IOT_OpenLiveStream(args={'dev_id':dev_id_info.get('dev_id','')}).run()
		assert result['code'] == 0,result
		dev_id_info.setdefault('handle', result['data']['handle'])



	@allure.title('关视频流操作')
	@allure.step('step：关视频流操作')
	@pytest.mark.order(5)
	@pytest.mark.flaky(returns=1)
	def test_IOT_CloseLiveStream(self):

		result = IOT_CloseLiveStream(args={'handle':dev_id_info.get('handle','')}).run()
		assert result['code'] == 0,result


	@allure.title('转存core')
	@allure.step('step：转存core')
	@pytest.mark.order(6)
	@pytest.mark.flaky(returns=1)
	def test_IOT_StartPushStream(self):

		result = IOT_StartPushStream(args={'dev_id':dev_id_info.get('dev_id',''),'dest_addr':"http://10.235.97.220:8021/"}).run()
		assert result['code'] == 0,result
		dev_id_info.setdefault('session', result['data']['session_id'])



	@allure.title('查询推流配置参数信息')
	@allure.step('step：查询推流配置参数信息')
	@pytest.mark.order(7)
	@pytest.mark.flaky(returns=1)
	@pytest.mark.four_two
	# @pytest.mark.skip(reason='接口有问题')
	def test_IOT_QueryPushStreamInfo(self):

		result = IOT_QueryPushStreamInfo(args={'session_id':dev_id_info.get('session','')}).run()
		assert result['code'] == 0,result
		log.info(result)



	@allure.title('批量更新推流配置参数信息')
	@allure.step('step：批量更新推流配置参数信息')
	@pytest.mark.order(8)
	@pytest.mark.flaky(returns=1)
	@pytest.mark.skip(reason='接口有问题')
	def test_IOT_BatchUpdatePushStreamInfo(self):
		req_info = '''[{
			/'session/':,'''+str(dev_id_info.get('session',''))+'''
			/"streamType/": 0,
			/"profileType/": 0,
			/"streamWay/": 0,
			/"dest_addr/": "http://10.235.97.220:8021/",
			/'faceFullBucket/':"11",
			/"faceCapBucket/":"11",
			/"personFullBucket/":"11",
			/"personCapBucket":"11",
			/"motorFullBucket/":"11",
			/"motorCapBucket/":"11",
			"nonmotorFullBucket":"11",
			"nonmotorCapBucket":"11"

		}]
		'''
		result = IOT_BatchUpdatePushStreamInfo(args={'req_info':req_info}).run()
		assert result['code'] == 0,result
		log.info(result)




	@allure.title('开启图片流')
	@allure.step('step：开启图片流')
	@pytest.mark.order(8)
	@pytest.mark.flaky(returns=1)
	def test_IOT_OpenPictureStream(self):

		result = IOT_OpenPictureStream(args={'dev_id':dev_id_info.get('dev_id','')}).run()
		assert result['code'] == 0,result
		dev_id_info['handle'] = result['data']['handle']



	@allure.title('关闭图片流')
	@allure.step('step：关闭图片流')
	@pytest.mark.order(9)
	@pytest.mark.flaky(returns=2)
	def test_IOT_ClosePictureStream(self):
		log.info(dev_id_info)
		result = IOT_ClosePictureStream(args={'handle':dev_id_info.get('handle','')}).run()
		assert result['code'] == 0,result


	@allure.title('开启设备录像')
	@allure.step('step：开启设备录像')
	@pytest.mark.order(10)
	@pytest.mark.flaky(returns=2)
	def test_IOT_StartDeviceRecord(self):
		log.info(dev_id_info)
		result = IOT_StartDeviceRecord(args={'dev_id':dev_id_info.get('dev_id','')}).run()
		assert result['code'] == 0,result


	@allure.title('获取录像参数')
	@allure.step('step：获取录像参数')
	@pytest.mark.order(11)
	@pytest.mark.flaky(returns=2)
	def test_IOT_StopDeviceRecord(self):
		log.info(dev_id_info)
		result = IOT_GetDeviceRecordInfo(args={'dev_id':dev_id_info.get('dev_id','')}).run()
		assert result['code'] == 0,result




	@allure.title('设置录像参数')
	@allure.step('step：设置录像参数')
	@pytest.mark.order(12)
	@pytest.mark.flaky(returns=2)
	def test_IOT_SetDeviceRecordInfo(self):
		log.info(dev_id_info)
		result = IOT_SetDeviceRecordInfo(args={'dev_id':dev_id_info.get('dev_id','')}).run()
		assert result['code'] == 0,result


	@allure.title('关闭设备录像')
	@allure.step('step：关闭设备录像')
	@pytest.mark.order(13)
	@pytest.mark.flaky(returns=2)
	def test_IOT_StopDeviceRecord(self):
		log.info(dev_id_info)
		result = IOT_StopDeviceRecord(args={'dev_id':dev_id_info.get('dev_id','')}).run()
		assert result['code'] == 0,result


	@allure.title('获取关键帧')
	@allure.step('step:获取关键帧')
	@pytest.mark.order(14)
	def	test_IOT_GetKeyFrame(self):
		time.sleep(3)
		result = IOT_GetKeyFrame(args={'dev_id':dev_id_info.get('dev_id','')}).run()
		assert result['code'] == 0, result

	@allure.title('批量获取设备状态')
	@allure.step('step:批量获取设备状态')
	@pytest.mark.order(15)
	def	test_IOT_BatchGetDeviceStatus(self):
		time.sleep(3)
		result = IOT_BatchGetDeviceStatus(args={'dev_list':[dev_id_info.get('dev_id','')]}).run()
		assert result['code'] == 0, result


	@allure.title('获取设备视频参数')
	@pytest.mark.skipif(condition=(dev_param['sdk_param']=='false'),reason='设备不支持')
	@pytest.mark.order(16)
	def test_IOT_GetVideoParam(self):
		args = {'dev_id': dev_id_info.get('dev_id', ''),'profile_type':0}

		allure.attach("传入参数", "{0}".format(args))

		with allure.step('step1:获取主码流视频参数'):
			result = IOT_GetVideoParam(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step2:获取子码流视频参数'):
			args['profile_type'] = 1
			result = IOT_GetVideoParam(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step3:获取三码流视频参数'):
			args['profile_type'] = 2
			result = IOT_GetVideoParam(args=args).run()
			assert result['code'] == 0, result

	@allure.title('设备云台预置位控制')
	@pytest.mark.skipif(condition=(dev_param['ptz']=='false'),reason='设备不支持')
	@pytest.mark.order(17)
	def test_IOT_PtzPreset(self):
		args = {'dev_id': dev_id_info.get('dev_id', ''), 'cmd': 1}
		allure.attach("传入参数", "{0}".format(args))
		with allure.step('step1:cmd=1'):
			result = IOT_PtzPreset(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:cmd=2'):
			args['cmd'] = 2
			result = IOT_PtzPreset(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:cmd=3'):
			args['cmd'] = 3
			result = IOT_PtzPreset(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:cmd=4'):
			args['cmd'] = 4
			result = IOT_PtzPreset(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:cmd=5'):
			args['cmd'] = 5
			result = IOT_PtzPreset(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:cmd=6'):
			args['cmd'] = 6
			result = IOT_PtzPreset(args=args).run()
			assert result['code'] == 0, result


	@allure.title('设备云台、镜头控制')
	@pytest.mark.skipif(condition=(dev_param['ptz']=='false'),reason='设备不支持')
	@pytest.mark.order(18)
	def test_IOT_PtzControl(self):
		args = {'dev_id': dev_id_info.get('dev_id', ''), 'ptz_cmd': 1,'speed':1,'stop':0}
		allure.attach("传入参数", "{0}".format(args))
		with allure.step('step1:PTZ向上运动'):
			args['ptz_cmd'] = 1
			result = IOT_PtzControl(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:PTZ向下运动'):
			args['ptz_cmd'] = 2
			result = IOT_PtzControl(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:PTZ向左运动'):
			args['ptz_cmd'] = 3
			result = IOT_PtzControl(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:PTZ向右运动'):
			args['ptz_cmd'] = 4
			result = IOT_PtzControl(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:PTZ向左上运动'):
			args['ptz_cmd'] = 5
			result = IOT_PtzControl(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:PTZ焦距变大（变倍+）'):
			args['ptz_cmd'] = 6
			result = IOT_PtzControl(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:PTZ光圈扩大'):
			args['ptz_cmd'] = 6
			result = IOT_PtzControl(args=args).run()
			assert result['code'] == 0, result
		with allure.step('step1:PTZ设置预置点'):
			args['ptz_cmd'] = 6
			result = IOT_PtzControl(args=args).run()
			assert result['code'] == 0, result

	@allure.title('获取设备分辨率')
	@pytest.mark.skipif(condition=(dev_param['sdk_param']=='false'),reason='设备不支持')
	@pytest.mark.order(19)
	def test_IOT_GetResolutionCap(self):
		args = {'dev_id': dev_id_info.get('dev_id', ''), 'profile_type': 0}
		allure.attach("传入参数", "{0}".format(args))
		with allure.step('step1:获取设备分辨率'):
			result = IOT_GetResolutionCap(args=args).run()
			assert result['code'] == 0, result

	@allure.title('获取设备模式能力集')
	@pytest.mark.skipif(condition=(dev_param['sdk_param']=='false'),reason='设备不支持')
	@pytest.mark.order(20)
	def test_IOT_GetCameraModeCap(self):
		args = {'dev_id': dev_id_info.get('dev_id', '')}
		allure.attach("传入参数", "{0}".format(args))
		with allure.step('step1:获取设备模式能力集'):
			result = IOT_GetCameraModeCap(args=args).run()
			assert result['code'] == 0, result

	@allure.title('获取相机模式参数')
	@pytest.mark.skipif(condition=(dev_param['sdk_param']=='false'),reason='设备不支持')
	@pytest.mark.order(21)
	def test_IOT_GetCameraMode(self):
		args = {'dev_id': dev_id_info.get('dev_id', '')}
		allure.attach("传入参数", "{0}".format(args))
		with allure.step('step1:获取设备模式能力集'):
			result = IOT_GetCameraMode(args=args).run()
			assert result['code'] == 0, result

	@allure.title('设置相机模式参数')
	@pytest.mark.skipif(condition=(dev_param['sdk_param']=='false'),reason='设备不支持')
	@pytest.mark.order(21)
	def test_IOT_SetCameraMode(self):
		args = {'dev_id': dev_id_info.get('dev_id', '')}
		allure.attach("传入参数", "{0}".format(args))
		with allure.step('step1:设置人脸抓拍模式mode=0'):
			result = IOT_SetCameraMode(args=args).run()
			assert result['code'] == 0, result


	@allure.title('获取设备报警输入端子配置信息')
	@pytest.mark.skipif(condition=(dev_param['sdk_param']=='false'),reason='设备不支持')
	@pytest.mark.order(22)
	def test_IOT_GetAlarmInConfig(self):
		args = {'dev_id': dev_id_info.get('dev_id', '')}
		allure.attach("传入参数", "{0}".format(args))
		with allure.step('step1:获取设备报警输入端子配置信息'):
			result = IOT_GetAlarmInConfig(args=args).run()
			assert result['code'] == 0, result

	@allure.title('设置设备报警输入端子配置信息')
	@pytest.mark.skipif(condition=(dev_param['sdk_param']=='false'),reason='设备不支持')
	@pytest.mark.order(22)
	def test_IOT_SetAlarmInConfig(self):
		args = {'dev_id': dev_id_info.get('dev_id', ''),"cfg": {"enabled": 1, "alarm_mode": 0}}
		allure.attach("传入参数", "{0}".format(args))
		with allure.step('step1:设置设备报警输入端子配置信息'):
			result = IOT_SetAlarmInConfig(args=args).run()
			assert result['code'] == 0, result

# if __name__ == '__main__':
# 	pytest.main(["-s",sys.argv[0] ])
# if __name__ == '__main__':
#     Test_Device().test_IOT_AddDevice()