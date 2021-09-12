#coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、python
	学习点:
		a.把学习到的知识补充到小项目中
		b.把接口补充到项目中了
2、 把python知识重新整理
	ok
3、sql

	学习点：
		round 取第几位小数
		limit i,n 从第i条开始查，返回n条
		case condition then  else end
	ROUND 函数用于把数值字段舍入为指定的小数位数。
		SELECT ProductName, ROUND(UnitPrice,0) as UnitPrice FROM Products
		18.查询各科成绩最高分、最低分和平均分：以如下形式显示：
		课程ID，课程name，最高分，最低分，平均分，及格率，中等率，优良率，优秀率 及格为>=60，中等为：70-80，优良为：80-90，优秀为：>=90
			CASE WHEN condition THEN result:https://blog.csdn.net/rongtaoup/article/details/82183743
			 
			[WHEN...THEN...]
			 
			ELSE result
			 
			END
			SELECT
				STUDENT_NAME,
				(CASE WHEN score < 60 THEN '不及格'
					WHEN score >= 60 AND score < 80 THEN '及格'
					WHEN score >= 80 THEN '优秀'
					ELSE '异常' END) AS REMARK
			FROM
				TABLE
				SELECT
		STUDENT_NAME,
		(CASE WHEN score < 60 THEN '不及格'
			WHEN score >= 60 AND score < 80 THEN '及格'
			WHEN score >= 80 THEN '优秀'
			ELSE '异常' END) AS REMARK
		FROM
		TABLE
	select a.c_id,b.c_name,MAX(s_score),MIN(s_score),ROUND(AVG(s_score),2),
		ROUND(100*(SUM(case when a.s_score>=60 then 1 else 0 end)/SUM(case when a.s_score then 1 else 0 end)),2) as 及格率,
		ROUND(100*(SUM(case when a.s_score>=70 and a.s_score<=80 then 1 else 0 end)/SUM(case when a.s_score then 1 else 0 end)),2) as 中等率,
		ROUND(100*(SUM(case when a.s_score>=80 and a.s_score<=90 then 1 else 0 end)/SUM(case when a.s_score then 1 else 0 end)),2) as 优良率,
		ROUND(100*(SUM(case when a.s_score>=90 then 1 else 0 end)/SUM(case when a.s_score then 1 else 0 end)),2) as 优秀率
		from score a left join course b on a.c_id = b.c_id GROUP BY a.c_id,b.c_name	
	明天任务：case when 好好学

'''
with open('9.1.py','r') as f :
	if '#coding:utf-8\n' in f.readlines():
		print("111111")