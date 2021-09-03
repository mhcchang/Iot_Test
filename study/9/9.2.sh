#!/bin/bash
set>>/dev/null

#--------------------------2021 09 02-----------------------------------------------
#数组操作

echo "********字符串数组********"
num1=(this is a good day)
for i in ${num1[@]}
do
echo $i
done
echo ${num1[@]}
echo ${num1[*]}
echo ${#num1[*]}
echo ${#num1[@]}
echo ${num1[2]}
echo "********字符串数组********"
#声明时后面不要注释，要不然就解析成了字符串
arr=(1 2 3 )

#数组赋值
for x in {1..10}
do
#数组赋值的时候不要加$引用符号
arr[$x]=$x
done

#遍历数据
for x in ${arr[*]}
do
echo $x
done
#数组长度${#arr[@]} 数组长度，把#去了就是数组
echo ${#arr[@]}
echo ${#arr[*]}
#截取数组字符 分片,若使用()包裹 则又是一个新数组
echo ar1=${arr[*]:0:3}
#替换元素
echo ${arr[*]/7/10}
#删除数组
unset arr
#删除数组元素
unset arr[0]

exit

#各种循环语法

#while 循环写法
#1、循环写法
i=1
while(($i<5))
do
let i+=1
echo $i
done


exit 0
#2、表达式写法
min=1
max=100
while [ $min -le $max ]
do
echo $min
let min=min+1
done



exit 0





#for 字符性循环---------------------------------------------------其实就是循环对象换了而已
#1、
for x in `ls`
do
echo $x
done
echo '================'
#2、
for x in $*
do
echo $x
done
#3、


exit 0
# for 数字性循环-------------------------------------------------
#1、
for x  in {1..2}
do
echo  $x
done
#2、
for x in `seq 0 10`
do
echo $x
done
#3、
for((i=0;i<10;i++))
do
echo
done
#4、
awk 'BEGIN{for(i=1;i<=10;i++)print i}'











exit
#------------------------------------------------2021 08 30------------------------------------------------------------------------------------
#写一个 bash脚本以统计一个文本文件 nowcoder.txt中字母数小于8的单词

read line < nowcoder.txt
for n in $line
do
if [ "${#n}" -lt 8 ]
then
    echo "${n}"
fi
done


exit 0
cat nowcoder.txt | awk '{
for (i=1;i<=NF;i++){
        if (length($i) < 8)
                print $i
}
}'



exit 0
#写一个 bash脚本以去掉一个文本文件 nowcoder.txt中的空行
count=0
while read value
do
let count+=1
if [[ ${value} != "" ]];then
echo  $value
fi
done



exit 0

#写一个 bash脚本以输出一个文本文件 nowcoder.txt中空行的行号,可能连续,从1开始
count=0
while read value
do
let count+=1
if [[ ${value} == "" ]];then
echo  $count
fi
done


exit 0
#写一个 bash脚本以输出一个文本文件 nowcoder.txt 中第5行的内容。
array=()
count=0
while read value
do
let count+=1
if [ $count -eq 5 ];then
echo $value
exit
fi
done






exit 0
#写一个 bash脚本以输出数字 0 到 500 中 7 的倍数(0 7 14 21...)的命令
for x in `seq 0 7 100`;do
    echo $x
done
for(( i=0;i<=500;i=i+7))
do
echo $i
done

for



exit 0

# set -vx
set first second third
echo $3 $2 $1
# Usage: formatSeconds 70 -> 1m 10s
# Credit: https://unix.stackexchange.com/a/27014
function formatSeconds {
    local T=$1
    local D=$((T/60/60/24))
    local H=$((T/60/60%24))
    local M=$((T/60%60))
    local S=$((T%60))
    local result=""

    (( D > 0 )) && result="${D}d "
    (( H > 0 )) && result="${result}${H}h "
    (( M > 0 )) && result="${result}${M}m "
    (( S > 0 )) && result="${result}${S}s "
    echo -e "${result}" | sed -e 's/[[:space:]]*$//'
}
# formatSeconds 70
line=0
while read value
do
let line+=1
done
echo $line