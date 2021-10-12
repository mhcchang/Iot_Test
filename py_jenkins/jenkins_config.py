#coding:utf-8
'''
author:haobingzhong
function:配置jenkins参数
param:
other
'''
jenkins_url='http://10.122.48.196:8081/'
username='haobingzhong'
password='1111111a'
jobs={}
shell = '''
#!/bin/sh
echo "设置的参数获取: "${py_test};
if [ -e ${WORKSPACE}/allure-results ];then
  echo "allure-results 存在 删除："
    sudo rm -rf ${WORKSPACE}/allure-results
fi
if [ -e ${WORKSPACE}/allure-report ];then
  echo "allure-report 存在 删除："
    sudo rm -rf ${WORKSPACE}/allure-report
fi

cd /home/haobingzhong/Study_Test/Iot_Test/test_ga/case/fun && sudo  pytest -s test_Face.py  --alluredir  ${WORKSPACE}/allure-results
'''