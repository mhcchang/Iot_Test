# coding:utf-8
'''
author:
function:
param:
other
'''
import os, sys

current = os.path.abspath('../../')
print("path", current)
sys.path.append(current)
import smtplib, base64, sys, os
from email.mime.text import MIMEText
# 设置服务器所需信息
from jinja2 import Environment, FileSystemLoader

email_host = "smtp.partner.outlook.cn"
email_port = 587
send_user = "haobingzhong@megvii.com"
password = "201467.h"
username = "郝炳钟" + "<" + send_user + ">"
user_list = ['haobingzhong@megvii.com', ]

import jenkins
import time
import sys
import json

print('------------')
print(sys.argv)

def jenkis_job(**kwargs):
	jenkins_url = 'http://10.122.48.196:8081/'
	username = 'haobingzhong'
	password = '1111111a'
	Jenkins_url = 'http://10.122.48.196:8081'
	jobs = {}
	job_name = sys.argv[1]
	result = Jenkins_url + "/job/pytest-allure/{}/allure/"
	server = jenkins.Jenkins(jenkins_url, username=username, password=password)
	return server.get_job_info(sys.argv[1])['lastBuild']['number']
# (server.get_job_info('pytest-allure'))#获取job信息
# jen_jobs=(server.build_job('pytest-allure',parameters={'version':"4.2.3"}))#启动构建
# print(jen_jobs)
# time.sleep(5)
# running_number = server.get_job_info(job_name)['nextBuildNumber'] - 1
# status = (server.get_build_info(job_name, running_number)['building'])  # 判断job是否在执行中
# while 1 :
# 	if server.get_job_info(job_name)['inQueue']:
# 		return (result.format(jen_jobs))
# 	else:
# 		pass
# print(result.format(jen_jobs))
# (server.get_queue_info()[0])#产线队列
# print(server.get_build_console_output('pytest-allure',server.get_job_info('pytest-allure')['lastBuild']['number']))#获取最后一次构建日志信息
# result=jenkis_job()
class SendEmail:

	def send_mail(self, sub, content, send_list=[]):
		message = MIMEText(content, _subtype='html', _charset='utf-8')
		message['Subject'] = sub
		message['From'] = username
		if send_list:
			message['To'] = ";".join(send_list)
		else:
			message['To'] = ";".join(user_list)

		try:
			# print("准备连接邮件服务器...")
			server = smtplib.SMTP(email_host, email_port)
			# server.connect(email_host, email_port)
			server.ehlo()
			server.starttls()
			# print("正在登陆邮件服务器...")
			server.login(send_user, password)
			# print("登陆邮件服务器成功")
			# print("准备发送邮件...")
			t = server.sendmail(username, user_list, message.as_string())
			print(t)
			# print("发送邮件成功")
			server.close()
		except Exception as e:
			print(e.args)
			print('发邮件失败')
			pass

	def send_main(self, title, htmlreport, send_list=[]):
		"""
		发邮件主程序
		:param title: 邮件标题
		:param htmlreport: 报告内容，string格式
		:return:
		"""
		sub = title
		self.send_mail(sub, htmlreport, send_list)

	def _generate_html(self, template_file="test_report.html", sender_name=None):
		path = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
		template_path = os.path.join(path, "template")
		print(template_path)
		loader = FileSystemLoader(template_path)
		env = Environment(loader=loader)
		template = env.get_template(template_file)
		testcase_total, testcase_pass, testcase_failed, testcase_skipped, test_result = self.get_testcase_outcome()
		auto_pass_rate = str(round(float(testcase_pass) / (testcase_total - testcase_skipped) * 100, 2)) + "%"
		# class_model_outcome = self.get_final_class_result()
		class_model_outcome = 10
		pass_rate = str(round(float(testcase_pass) / testcase_total * 100, 2)) + "%"
		html_str = template.render(server_ip='10.172.198.63', test_result=test_result, total=testcase_total,
								   pass_count=testcase_pass, failed_count=testcase_failed,
								   skipped_count=testcase_skipped, rate=pass_rate, auto_rate=auto_pass_rate,
								   report_url='http://10.122.48.196:8081/job/{}/{}/allure/#'.format(
									   sys.argv[1],str(
									   jenkis_job())),
								   class_module_output='')
		# html_str = template.render(total=testcase_total, pass_count=testcase_pass, failed_count=testcase_failed,
		#                            skipped_count=testcase_skipped, rate=pass_rate, report_url=self.report_url)
		return html_str

	def get_testcase_outcome(self):
		"""
		获取总测试用例执行情况
		:return:
		"""
		# 测试用例总数, 测试用例成功数，测试用例失败数， 测试用例忽略数
		# self.outcome = [1,2,3]
		# testcase_total, testcase_pass, testcase_failed, testcase_skipped = 0, 0, 0, 0
		# # 测试用例总数
		# testcase_total = len(self.outcome)
		# for testcase_id, testcase_info in self.outcome.items():
		#     try:
		#         if testcase_info["setup"] == "skipped" or testcase_info["call"] == "skipped" or testcase_info["teardown"] == "skipped":
		#             testcase_skipped += 1
		#         elif testcase_info["setup"] == "passed" and testcase_info["call"] == "passed" and testcase_info["teardown"] == "passed":
		#             testcase_pass += 1
		#         else:
		#             testcase_failed += 1
		#     except KeyError as e:
		#         print("-------", testcase_info, e)
		#         testcase_failed += 1
		# test_result = "通过" if testcase_pass == testcase_total else "失败"v
		# print("testcase_total: {}, testcase_pass: {}, testcase_failed: {}, testcase_skipped: {}, test_result: {}".
		#       format(testcase_total, testcase_pass, testcase_failed, testcase_skipped, test_result))
		return 10, 1, 1, 1, 1


t = SendEmail()._generate_html()
SendEmail().send_main(title='测试邮件', htmlreport=t, send_list=user_list)
