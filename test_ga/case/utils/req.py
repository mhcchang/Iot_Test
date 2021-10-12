# coding:utf-8
'''
author:
function:
param:
other
'''
import requests
from requests.auth import HTTPDigestAuth
import json
import allure
from util.log import *

log = log_txt(loggername=__name__).log_init()

class request:

	@classmethod
	def header(cls, d):
		cls.session = requests.session
		cls.headers = d['headers']

	@classmethod
	def closeSession(cls):
		# requests.session.close()
		pass

	@classmethod
	def get(cls, **kwargs):
		import copy
		d = copy.deepcopy(kwargs)
		d['headers'] = {"User-Identify": "11010800001190000001"}
		url = d['url']
		headers = d['headers']
		data = d.get('data', None)
		cls.header(d)
		allure.attach("请求url", "{0}".format(url))
		allure.attach("请求data", "{0}".format(data))
		log.info("请求url:{}".format(url))
		try:
			rsp = requests.get(url, data=data, headers=headers)
			allure.attach("返回数据response", "{0}".format(rsp.__dict__['_content']))
			allure.attach("返回数据code", "{0}".format(rsp.__dict__['status_code']))
			log.info("返回code:{}".format(rsp.status_code))
			d = dict()
			for k, v in rsp.__dict__.items():
				if k == '_content' and v != '':
					d[k] = json.dumps(json.loads(v))
				else:
					d[k] = v
			return d
		except  Exception as e:
			print(e.args)
		finally:
			cls.closeSession()

	@classmethod
	def delete(cls, **kwargs):
		import copy
		d = copy.deepcopy(kwargs)
		d['headers'] = {"User-Identify": "11010800001190000001"}
		url = d['url']
		headers = d['headers']
		data = d.get('data', None)
		cls.header(d)
		allure.attach("请求url", "{0}".format(url))
		allure.attach("请求data", "{0}".format(data))
		log.info("请求url:{}".format(url))

		try:
			rsp = requests.delete(url, data=data, headers=headers)
			d = dict()
			log.info("返回code:{}".format(rsp.status_code))
			d['status_code'] = rsp.__dict__['status_code']
			for k, v in rsp.__dict__.items():
				if k == '_content':
					if v == '':
						d['_content'] = v
					else:
						d[k] = json.dumps(json.loads(v))
				else:
					d[k] = v
			allure.attach("返回数据response", "{0}".format(rsp.__dict__['_content']))
			allure.attach("返回数据code", "{0}".format(rsp.__dict__['status_code']))
			return d
		except  Exception as e:
			callback(arg=e, d=d, rsp=rsp)
		finally:
			cls.closeSession()
			return d

	@classmethod
	def post(cls, **kwargs):
		import copy
		d = kwargs
		d['headers'] = {"User-Identify": "11010800001190000001"}
		url = d['url']
		headers = d['headers']
		data = d['data']
		auth = d.get('auth', None)
		cls.header(d)
		allure.attach("请求url", "{0}".format(url))
		allure.attach("请求data", "{0}".format(data))
		log.info("请求url:{}".format(url))
		log.info("请求data:{}".format(data))

		try:
			rsp = requests.post(url, data=data, headers=headers, auth=auth)
			log.info("返回code:{}".format(rsp.status_code))
			allure.attach("返回数据response", "{0}".format(rsp.__dict__['_content']))
			allure.attach("返回数据code", "{0}".format(rsp.__dict__['status_code']))
			d = dict()
			for k, v in rsp.__dict__.items():
				if k == '_content' and v != '401 Unauthorized\n':
					d[k] = json.dumps(json.loads(v))
				else:
					d[k] = v
			if d['status_code'] in [201, 200]:
				return d
			else:
				return d
		except  Exception as e:
			print(e.args)
			log.info(e.args)

		finally:
			cls.closeSession()

	@classmethod
	def put(cls, **kwargs):
		import copy
		d = copy.deepcopy(kwargs)
		d['headers'] = {"User-Identify": "11010800001190000001"}
		url = d['url']
		headers = d['headers']
		data = d['data']
		cls.header(d)
		log.info("请求url:{}".format(url))
		try:
			rsp = requests.put(url, data=data, headers=headers)
			log.info("返回code:{}".format(rsp.status_code))
			d = dict()
			for k, v in rsp.__dict__.items():
				if k == '_content':
					d[k] = json.dumps(json.loads(v))
				else:
					d[k] = v
			allure.attach("请求url", "{0}".format(url))
			allure.attach("请求data", "{0}".format(data))
			allure.attach("返回数据response", "{0}".format(rsp.__dict__['_content']))
			allure.attach("返回数据code", "{0}".format(rsp.__dict__['status_code']))

			return d
		except  Exception as e:
			print('-----------------')
			print(e.args)
		finally:
			cls.closeSession()
	@classmethod
	def get_msg(cls,**kwargs):
		return 0


def callback(**kwargs):
	print('异常错误:{}'.format(kwargs.get('arg', None)))
	print('返回字典为:{}'.format(kwargs.get('d', None)))
	for k, v in kwargs['rsp'].__dict__.items():
		print('http请求返回key-value: {}:{}'.format(k, v))


l = []


# 只取一个key的值
def key_value(k, v):
	if isinstance(k, dict):
		if v in list(k.keys()):
			l.clear()
			l.append(k[v])
		for x in k:
			if isinstance(k[x], dict):
				return key_value(k[x], v)
			elif (isinstance(k[x], list)):
				return key_value(k[x], v)
	if isinstance(k, list):
		for x in k:
			if isinstance(k, dict):
				return key_value(x, v)
			elif (isinstance(k, list)):
				return key_value(x, v)


from test_ga.ga_schema.uuid_to.model import *
from test_ga.model.utils.sql_operate import sql_operate as sql


# 如果和上下级有关则存入操作业务类型及UUID
def uuid_ope(**kwargs):
	kwargs['name'] = kwargs.get('name', None)
	kwargs['uuid'] = kwargs.get('uuid', None)
	kwargs['type'] = kwargs.get('type', None)
	kwargs['other'] = kwargs.get('other', None)
	f = sql.query(Uuid_to, name=kwargs['name'])
	print(f)
	if f:
		f.uuid = kwargs['uuid']
		kwargs['id'] = f.id
		print(kwargs)
		s = sql.update(Uuid_to, **kwargs)
		print('--------')
		print(s)
	else:
		print(sql.add(Uuid_to, **kwargs))
