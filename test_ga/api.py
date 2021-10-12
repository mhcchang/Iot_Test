#coding:utf-8
'''
author:
function:
param:
other
'''
from  flask import  Flask
import sys, os

sys.path.append(os.path.abspath('../'))
from  test_ga.register.restApi import *
app = Flask(__name__)
api = Api(app)

#case
api.add_resource(add_case,'/case')
#云图标准接口----认证保活----------------------------------------------------------
#保活接口
api.add_resource(System_keep,'/VIID/System/Keepalive')
#校时接口
# api.add_resource(System_keep,'/VIID/System/Time')
# #注册接口
api.add_resource(System_Register,'/VIID/System/Register')
# #注销接口
# api.add_resource(System_keep,'/VIID/System/Unregister')


#云图标准接口------订阅--------------------------------------------------------

api.add_resource(SubInfo,'/VIID/SubscribeNotifications')



app.run(host='0.0.0.0',port=8084)



