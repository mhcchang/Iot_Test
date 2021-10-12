#coding:utf-8
'''
author:
function:
param:
other
'''
#云图侧的配置
HOST = '10.201.102.104'
ssh_name = 'security'
ssh_psd = 'qN6MTqW1VbQ3iF4G'
PORT = ':80'
http = 'http://'
header = {
	"User-Identify": "11010800001190000001"
}
from test_ga.caseConfig.redis_config import *

#业务接口,获取云图行政编码
get_viid = http+HOST+PORT+'/api/viid/v1/config/system?r=1631436250305'
import requests,json,random
def get_code():
    try:
        rsp = requests.get(get_viid)
        r = json.loads(rsp.text)['data']
        viidId = r['viidId']
        orgCode = r['orgCode']
        code = viidId[:8]
        return code,orgCode
    except Exception as e:
        print(e.args)

code,orgCode = get_code()
device = code + "001190" + str(random.randint(99999,999999))
print(device)
r_redis.set('deviceId', device)

#设备相关接口=========================================
#注册
register = http+HOST+PORT+'/VIID/System/Register'
register_body = {
  "RegisterObject": {
    "DeviceID": device
  }
}
#保活
keep = http+HOST+PORT+'/VIID/System/Keepalive'
keep_body ={
    "KeepaliveObject": {
        "DeviceID": device
    }
}
#校时
Time = '/VIID/System/Time'
#注销
unregister =  http+HOST+PORT+'/VIID/System/Unregister'
face_url = ''
#APE
ape = http+HOST+PORT+'/VIID/APEs'


#采集接口=================================
#face
face = http+HOST+PORT+'/VIID/Faces'
#person
person = http+HOST+PORT+'/VIID/Persons'
#MotorVehicles
motorvehicles = http+HOST+PORT+'/VIID/MotorVehicles'
#NonMotorVehicle
nonNotorVehicle = http+HOST+PORT+'/VIID/NonMotorVehicles'

#订阅布控告警接口===========================
# 新建订阅
sub_url = http+HOST+PORT+'/VIID/Subscribes'

#布控=====================================
dispositions_url =  http+HOST+PORT+'/VIID/Dispositions'