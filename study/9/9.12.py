#coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、python
	项目自动化
2、shell	

'''
import smtplib,base64
from email.mime.text import MIMEText
#设置服务器所需信息
#163邮箱服务器地址
mail_host = "smtp.partner.outlook.cn"
#163用户名
send_user = 'haobingzhong@megvii.com'
#密码(部分邮箱为授权码)
password = '201467.h'
#邮件发送方邮箱地址
sender = 'haobingzhong@megvii.com'
#邮件接受方邮箱地址，注意需要[]包裹，这意味着你可以写多个邮件地址群发
receivers = ['59*****02@qq.com']
server = smtplib.SMTP(mail_host, 587)
server.ehlo()
server.starttls()
f = server.login(send_user, password)
print(f)
username = "梁奉龙" + "<" + send_user + ">"
user_list = [sender, ]
message = MIMEText("content", _subtype='html', _charset='utf-8')

server.sendmail(username, user_list, message.as_string())

# #设置email信息
# #邮件内容设置
# message = MIMEText('content','plain','utf-8')
# #邮件主题
# message['Subject'] = 'title'
# #发送方信息
# message['From'] = sender
# #接受方信息
# message['To'] = receivers[0]
# try:
#     smtpObj = smtplib.SMTP()
#     #连接到服务器
#     smtpObj.connect(mail_host,587)
#     #登录到服务器
#     smtpObj.login(mail_user,mail_pass)
#     #发送
#     # smtpObj.sendmail(
#     #     sender,receivers,message.as_string())
#     # #退出
#     smtpObj.quit()
#     print('success')
# except smtplib.SMTPException as e:
#     print('error',e) #打印错误# coding:utf-8
# import base64
# import smtplib
# from email.mime.text import MIMEText
# # from util.logger import Logger as logger
# # from util.exceptions import *
# # import settings
#
# email_host = "smtp.partner.outlook.cn"
# email_port = 587
# send_user = "liangfenglong@megvii.com"
# password = "bGZsLjExbGZs"
# username = "梁奉龙" + "<" + send_user + ">"
# user_list = ['liangfenglong@megvii.com', ]
#
#
# class SendEmail:
#
#     def send_mail(self, sub, content, send_list=[]):
#         message = MIMEText(content, _subtype='html', _charset='utf-8')
#         message['Subject'] = sub
#         message['From'] = username
#         if send_list:
#             message['To'] = ";".join(send_list)
#         else:
#             message['To'] = ";".join(user_list)
#
#         try:
#             # print("准备连接邮件服务器...")
#             server = smtplib.SMTP(email_host, email_port)
#             # server.connect(email_host, email_port)
#             server.ehlo()
#             server.starttls()
#             # print("正在登陆邮件服务器...")
#             server.login(send_user, base64.b64decode(password).decode())
#             # print("登陆邮件服务器成功")
#             # print("准备发送邮件...")
#             server.sendmail(username, user_list, message.as_string())
#             # print("发送邮件成功")
#             server.close()
#         except:
#             # print('发邮件失败')
#             pass
#
#     def send_main(self, title, htmlreport, send_list=[]):
#         """
#         发邮件主程序
#         :param title: 邮件标题
#         :param htmlreport: 报告内容，string格式
#         :return:
#         """
#         sub = title
#         self.send_mail(sub, htmlreport, send_list)