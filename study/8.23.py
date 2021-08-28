# coding:utf-8
'''
author:
function:
param:
other
'''
'''
python：
学习链接：https://www.w3cschool.cn/flask/   W3C
廖雪峰教程：https://www.liaoxuefeng.com/wiki/1016959663602400 
学习主要内容是：web开发
一、web开发
	1.1 HTTP协议简介
		CS架构：client/server
		BS架构：browser/server
	1.2 WSGI接口
		定义：web server gateway interface
		python内置了一个WSGI服务器,模块叫wsgiref(模拟了WSGI服务器操作实现，不考虑任何效率)
		无论多么复杂的Web应用程序，入口都是一个WSGI处理函数。HTTP请求的所有输入信息都可以通过environ获得
		from  wsgiref.simple_server import  make_server
		def application(environ, start_response):
			start_response('200 OK', [('Content-Type', 'text/html')])
			return [b'<h1>Hello, web!</h1>']
		httpd = make_server('',port=8080,application())
		httpd.serve_forever()
	1.3 web框架
		Flask
			Web框架都提供了自己的API来实现这些功能。Flask通过request.form['name']来获取表单的内容
		Django
		web.py
		bottle
		
				from flask import Flask
				from flask import request
				
				app = Flask(__name__)  # 返回对象类型，理解的是把这个py中的__name__注册到Fask
				
				
				@app.route('/', methods=['GET', 'POST'])
				def signin():
					return '<p>111</p>'
				
				
				if __name__ == '__main__':
					app.run(host='10.122.48.196',port=8083)
	1、4 使用模板
		MVC:model-view-controller ，模型-视图--控制器
		python处理的url的函数就是C：负责业务逻辑
		包含变量{{name}}模板就是V：负责显示，简单的替换一些变量
		model:是用來传给view，{'name':'111'}
		flask支持jinja2模板，所谓模板就是静态html，中间有些变量需要传递
		
		一定要把模板放到正确的templates目录下，templates和app.py在同级目录下
		
2、flask
	2.1 路由
		flask中的route()装饰器用于将URL绑定到函数中
	2.2 变量规则
		通过向规则参数添加变量部分，可以动态构建url
		构建变量类型包括：整型、浮点型、字符串、path,一般使用字符串
		注意：如果使用变量规则时，对应的函数中药传入参数
	2.3 URL构建
		url_for()函数接受函数的名称作为第一个参数，以及一个或多个关键字参数，每个参数对应于URL的变量部分。
		redirect#相当于重定向
	2.4 HTTP方法
		put/get/post/delete
		获取参数:
				post			request.form('xxx')
				get				request.get('11')
'''

from flask import Flask,redirect,url_for
from flask import request,render_template

app = Flask(__name__)  # 返回对象类型，理解的是把这个py中的__name__注册到Fask


@app.route('/<name>', methods=['GET', 'POST'])
def signin(name):
	return 	render_template("test.html",Home=name)

if __name__ == '__main__':
	app.run(host='10.122.48.196', port=8083)
'''
mysql:
w3c学习链接：https://www.w3cschool.cn/mysql/
1、创建表
	语法：CREATE TABLE table_name (column_name column_type);	
	CREATE TABLE study(
		id INT NOT NULL,
		type VARCHAR(100) NOT NULL,
		last_time DATE
)
2、插入数据：
	CURRENT_DATE:获取当前时间
	INSERT INTO study(id,type,last_time)  VALUES(1,2,CURRENT_DATE)
3、查询
	语法：
			SELECT column_name,column_name
			FROM table_name
			[WHERE Clause]
			[OFFSET M ][LIMIT N]
	示例：
	SELECT * FROM math
4、更新
	语法：
		UPDATE table_name SET field1=new-value1, field2=new-value2
	[WHERE Clause]
	示例：
		UPDATE study SET id=1 WHERE id=3
5、删除
	语法：
		DELETE FROM table_name [WHERE Clause]
	示例：
		DELETE FROM study WHERE id=1
6、排序：
	语法：
		SELECT field1, field2,...fieldN FROM table_name1, table_name2...
ORDER BY field1, [field2...] [ASC [DESC]]
	示例：
		SELECT * FROM study ORDER BY id 
7、分组
	语法：
		SELECT column_name, function(column_name)
		FROM table_name
		WHERE column_name operator value
		GROUP BY column_name;
	示例：
		SELECT id  FROM math WHERE id=1 GROUP BY id
8、连接
	右连接：如果左边不符合则为空
		SELECT * FROM study RIGHT JOIN math  on study.id=math.class
	左链接：如果右边不符合则会空
		SELECT * FROM `study`  LEFT JOIN math on study.id=math.id
	内链接：需要完全符合条件
		SELECT * FROM `study`  INNER JOIN math on study.id=math.id
	练习链接：https://blog.csdn.net/zjt980452483/article/details/82945663
	题目：https://blog.csdn.net/fashion2014/article/details/78826299/


'''