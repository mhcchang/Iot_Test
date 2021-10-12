#coding:utf-8
'''
author:
function:
param:
other
'''
import sys
from test_ga.ga_schema import *

from test_ga.caseConfig.config import ape,register,keep,face,face_url,r_redis,keep_body,header,register_body,sub_url,\
	person,motorvehicles,nonNotorVehicle
import pytest
from requests.auth import HTTPDigestAuth
from test_ga.case.utils.req import request
from test_ga.case.utils.req import Uuid_to
from test_ga.caseConfig.redis_config import r_redis as flush_redis
import allure, json
import uuid
from test_ga.case.utils.req import key_value, l, uuid_ope
#-------------------------------------------------------------
from test_ga.ga_schema.APEs.api_json import *
from test_ga.ga_schema.Face.face_base import *
from test_ga.ga_schema.Subscribe.api_json import *
from test_ga.ga_schema.Person.api_json import *
from test_ga.ga_schema.MotorVehicles.api_json import *

from test_ga.ga_schema.NonMotorVehicles.api_json import *
