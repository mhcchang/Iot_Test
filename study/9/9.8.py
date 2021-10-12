#coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、python
	完善项目
2、sql
	链接：https://blog.csdn.net/fashion2014/article/details/78826299/
	sql中使用伪列计数：
		select (@i:=@i+1) as rownum, Student.s_sex  from Student, (select @i:=0) as init;
	21、查询不同老师所教不同课程平均分从高到低显示 
			
	SELECT Teacher.t_id,Teacher.t_name,ff.c_name,ff.avg FROM
		Teacher,
	(SELECT c.t_id,c.c_name,a.avg FROM
		Course c,
	(SELECT c_id,AVG(s_score) as avg FROM Score GROUP BY c_id) as a
	WHERE c.c_id=a.c_id) as ff
	WHERE Teacher.t_id=ff.t_id ORDER BY  ff.avg DESC
'''