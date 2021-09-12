#coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、复习shell脚本，已完成。
2、sql
	链接：https://blog.csdn.net/fashion2014/article/details/78826299/
	22、查询所有课程的成绩第2名到第3名的学生信息及该课程成绩
		no
	24、查询学生平均成绩及其名次
		SELECT  (@i:=@i+1) as '排名',a.s_name,sg.ag FROM Student a , (select @i:=0) as init,
		(SELECT  s.s_id,AVG(s.s_score) as ag FROM Score  s GROUP BY s.s_id)
		as 
		sg
		
		WHERE a.s_id=sg.s_id ORDER BY sg.ag DESC
	25、查询各科成绩前三名的学生信息
	26、查询每门课程被选修的学生数 
			SELECT c_id,COUNT(s_id)  FROM Score GROUP BY c_id
	28、查询男生、女生人数
			  SELECT  s.s_sex,COUNT(s_id)  FROM Student  s GROUP BY s.s_sex
	29、查询名字中含有"风"字的学生信息
		SELECT * FROM Student a WHERE a.s_name like 's%'
	30、查询同名同性学生名单，并统计同名人数 
		SELECT a.s_sex,a.s_name,COUNT(a.s_id) FROM Student a GROUP BY a.s_sex,a.s_name HAVING COUNT(a.s_id)>1;
	31、查询1990年出生的学生名单
		SELECT *  FROM Student a WHERE a.s_birth LIKE '1990%'
	32、查询每门课程的平均成绩，结果按平均成绩降序排列，平均成绩相同时，按课程编号升序排列 
		SELECT  s.c_id,avg(s.s_score) as ag FROM Score s GROUP BY s.c_id   ORDER BY ag DESC,  s.c_id ASC
		ASC是升序
	33、查询平均成绩大于等于85的所有学生的学号、姓名和平均成绩 
		
		SELECT a.* ,f.ag as "平均分" FROM Student a ,(SELECT  a.s_id,avg(a.s_score) AS ag FROM Score a GROUP BY a.s_id HAVING ag>85) as f WHERE a.s_id=f.s_id
	34、查询课程名称为"数学"，且分数低于60的学生姓名和分数
		SELECT  * FROM Score s WHERE s.c_id=(SELECT c.c_id  FROM Course c WHERE c.c_name='shuxue') and s.s_score<60
	35、查询所有学生的课程及分数情况
	36、查询任何一门课程成绩在70分以上的姓名、课程名称和分数； 
		
'''