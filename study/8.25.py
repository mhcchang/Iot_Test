# coding:utf-8
'''
author:
function:
param:
other
'''
'''
初体验locust

pip3 install locust
'''
from locust import HttpLocust, TaskSet, task

from locust import HttpLocust, TaskSet, task
from locust import HttpUser




class UserTasks(TaskSet):
	# 列出需要测试的任务形式一
	# 列出需要测试的任务形式二
	@task(1)
	def page404(self):
		self.client.get("/test")


class WebsiteUser(HttpUser):
	host = "http://10.235.97.220:8021/"
	min_wait = 2000
	max_wait = 5000
	tasks = [UserTasks]