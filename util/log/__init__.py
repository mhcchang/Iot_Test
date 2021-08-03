#coding:utf-8
'''
日志工具库
loggername为了保证多个文件调用logger
'''
import logging
import colorlog
import datetime,os
log_colors_config = {
    'DEBUG': 'cyan',
    'INFO': 'green',
    'WARNING': 'yellow',
    'ERROR': 'red',
    'CRITICAL': 'red',
}
class log_txt:
	def __init__(self,type=1,loggername=None):
		current = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
		filename = current+'/logs/sys_%s.txt' % datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d')
		log_format = '%(asctime)s[%(levelname)s]-%(funcName)s: %(message)s'
		self.logger = logging.getLogger(loggername)
		# 保存日志文件
		fh = logging.FileHandler(filename, mode='a+')
		fh.setLevel(logging.INFO)
		formatter = logging.Formatter(log_format)
		fh.setFormatter(formatter)
		if not self.logger.handlers:
			# 输出控制台
			ch = logging.StreamHandler()
			ch.setLevel(logging.INFO)
			self.formatter = colorlog.ColoredFormatter(
			'%(log_color)s[%(asctime)s] [%(filename)s:%(lineno)d] [%(module)s:%(funcName)s] [%(levelname)s]- %(message)s',
			log_colors=log_colors_config)
			ch.setFormatter(self.formatter)
			self.logger.addHandler(ch)
			self.logger.addHandler(fh)
		self.logger.setLevel(logging.INFO)

	def	log_init(self):
		return self.logger
	# def log_error(self,text):
	# 	self.logger.error()
	# def log_warn(self,text):
	# 	self.logger.warning()
	# def log_info(self,text):
	# 	self.logger.info()
# log_txt().log_init().info(111111111)