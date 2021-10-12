#coding:utf-8
'''
author:haobingzhong
function:调用jenkins
param:https://www.cnblogs.com/juan-F/p/14917897.html
other
1）get_job_info(name, depth=0, fetch_all_builds=False)  获取指定Job的详细信息
2）get_job_info_regex(pattern, depth=0, folder_depth=0) 获取匹配指定Job的详细信息
3）get_job_name(name) 获取指定名字的Job，常用于判断Job是否存在
4）get_jobs()获取所有的jobs
5）debug_job_info(job_name) 以可读的方式打印Job信息
6）get_version()获取Jenkins版本信息
7）get_views() 获取所有的视图
'''
import jenkins
import time
import sys
import json
from py_jenkins.jenkins_config import *
from  config.normal import Jenkins_url,SDK_VERSION
job_list = ['Ga_Test','Iot_Test']
def get_jobs_status(job_name, server):
    try:
        server.assert_job_exists(job_name)
    except Exception as e:
        print(e)
        job_statue = '1'

    # 判断job是否处于排队状态
    inQueue = server.get_job_info(job_name)['inQueue']
    print("任务是否处于排队状态：", inQueue)
    if str(inQueue) == 'True':  # 排队
        job_statue = 'pending'
        running_number = server.get_job_info(job_name)['nextBuildNumber']
    else:
        # 没有在排队的job，获取最新一个的执行编号
        running_number = server.get_job_info(job_name)['nextBuildNumber'] - 1

        try:
            running_status = server.get_build_info(job_name, running_number)['building'] # 判断job是否在执行中
            if str(running_status) == 'True':
                job_statue = 'running'
            else:
                # 若running_status不是True说明job执行完成
                job_statue = server.get_build_info(job_name,running_number)['result']
        except Exception as e:
            # 上面假设job处于running状态的假设不成立，则job的最新number应该是['lastCompletedBuild']['number']
            lastCompletedBuild_number = server.get_job_info(job_name)['lastCompletedBuild']['number']
            job_statue = server.get_build_info(job_name, lastCompletedBuild_number)['result']

    return job_statue, running_number
def jenkis_job(**kwargs):
	job_name=job_list[0]
	server=jenkins.Jenkins(jenkins_url,username=username,password=password)
	jen_jobs=(server.build_job(job_name,parameters={'ip':"4.2.3",'email':''}))#启动构建
	print(get_jobs_status(job_name=job_name,server=server))
	while 1:
		job_statue, running_number = get_jobs_status(job_name, server)
		if job_statue in ['pending']:
			pass
		else:
			print('执行完成！')
			break
result=jenkis_job()
