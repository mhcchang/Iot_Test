#coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、python
	2小时云图+python:主要是订阅数据
2、shell
	shell实例操作：https://blog.csdn.net/weixin_43599906/article/details/104021784?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.no_search_link&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.no_search_link
#--------------------------2021 09 11-----------------------------------------------
# 1、【题目要求】每日一文件
		# 请按照这样的日期格式（xxxx-xx-xx）每日生成一个文件， 例如生成的文件名为2017-12-20.log， 并且把磁盘的使用情况写到到这个文件中， 不用考虑cron，仅仅写脚本即可
  		  #知识点：1、date    2、xargs    3、find
		# do_date=`date`    ==> Thu Jun  3 14:33:58 CST 2020
		# do_date=`date  +%F`    ==> 2020-06-03
		# do_date=`date -d "-1 day" +%F`    ==>2020-06-02
		# date +"%Y-%m-%d %H:%M:%S"    2020-06-03 14:20:25 
		#xargs把前面命令执行结果作为第二天的输入命令
		log=`date +"%Y-%m-%d %H:%M:%S"`
		d=`date +%F`
		dir=/data/logs/disklog
		if [ ! -d $dir ]
		then
			mkdir -p $dir
		fi
		df -h > $dir/$d.log
		find $dir/ -mtime +365 |xargs rm -rf 
		#2、根据日志统计访问量
		#uniq 命令用于检查及删除文本文件中重复出现的行列，一般与 sort 命令结合使用。:https://www.cnblogs.com/delav/p/9953330.html
		#sort :https://www.cnblogs.com/delav/p/9956819.html  sort -n -r
		#-n: numeric-sort，根据字符串数值进行排序
		#-r: reverse，反向输出排序结果
		
		cat 1.log | awk '{print $1}'| sort |uniq -c|sort -n -r
		awk '{print $1}' 1.log | sort |uniq -c|sort -n -r
		#3、题目要求 ： 统计内存占用之和
		#RSS是占内存列头
		sum=0
		for x in `sudo ps -aux | awk '{print $6}'`
		do
		sum=$[${sum}+${x}]
		done
		echo $sum
		# 4、题目要求 ： 检测机器存活
		# 设计一个脚本，监控远程的一台机器(假设ip为180.163.26.39)的存活状态，当发现down机时发一封邮件给你自己。
		# awk $NF代表最后一个域 （也就是最后一个单词）  $NT代表每行
		ping 10.122.100.213 -c4 |grep 'packet'|awk -F '%' '{print $1}'|awk '{print $NF}'
		# 5、题目要求
		
		# 找到/123目录下所有后缀名为.txt的文件
		#tar cvf FileName.tar DirName
		# 批量修改.txt为.txt.bak
		# 把所有.bak文件打包压缩为123.tar.gz
		# 批量还原文件的名字，即把增加的.bak再删除
		
		sudo rm -rf 123/* 123.tar.gz
		for x in `seq 10`;do
		touch 123/${x}.txt
		done
		array=()
		c=0
		for x in `find 123/ -type f -name '**.txt'`;do
		array[$c]=$x
		let c=c+1
		done
		for x in ${array[@]};do
		mv $x ${x}.bak
		done
		find  123/ -name '**.bak'|xargs tar -czvf 123.tar.gz >>/dev/null
		for x in ${array[@]};do
		mv   ${x}.bak   $x 
		done
		echo ${array[@]}
		
		exit 0


'''