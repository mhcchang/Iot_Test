#!/bin/bash
set>>/dev/null

#--------------------------2021 09 02-----------------------------------------------
#�������

echo "********�ַ�������********"
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
echo "********�ַ�������********"
#����ʱ���治Ҫע�ͣ�Ҫ��Ȼ�ͽ��������ַ���
arr=(1 2 3 )

#���鸳ֵ
for x in {1..10}
do
#���鸳ֵ��ʱ��Ҫ��$���÷���
arr[$x]=$x
done

#��������
for x in ${arr[*]}
do
echo $x
done
#���鳤��${#arr[@]} ���鳤�ȣ���#ȥ�˾�������
echo ${#arr[@]}
echo ${#arr[*]}
#��ȡ�����ַ� ��Ƭ,��ʹ��()���� ������һ��������
echo ar1=${arr[*]:0:3}
#�滻Ԫ��
echo ${arr[*]/7/10}
#ɾ������
unset arr
#ɾ������Ԫ��
unset arr[0]

exit

#����ѭ���﷨

#while ѭ��д��
#1��ѭ��д��
i=1
while(($i<5))
do
let i+=1
echo $i
done


exit 0
#2�����ʽд��
min=1
max=100
while [ $min -le $max ]
do
echo $min
let min=min+1
done



exit 0





#for �ַ���ѭ��---------------------------------------------------��ʵ����ѭ�������˶���
#1��
for x in `ls`
do
echo $x
done
echo '================'
#2��
for x in $*
do
echo $x
done
#3��


exit 0
# for ������ѭ��-------------------------------------------------
#1��
for x  in {1..2}
do
echo  $x
done
#2��
for x in `seq 0 10`
do
echo $x
done
#3��
for((i=0;i<10;i++))
do
echo
done
#4��
awk 'BEGIN{for(i=1;i<=10;i++)print i}'











exit
#------------------------------------------------2021 08 30------------------------------------------------------------------------------------
#дһ�� bash�ű���ͳ��һ���ı��ļ� nowcoder.txt����ĸ��С��8�ĵ���

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
#дһ�� bash�ű���ȥ��һ���ı��ļ� nowcoder.txt�еĿ���
count=0
while read value
do
let count+=1
if [[ ${value} != "" ]];then
echo  $value
fi
done



exit 0

#дһ�� bash�ű������һ���ı��ļ� nowcoder.txt�п��е��к�,��������,��1��ʼ
count=0
while read value
do
let count+=1
if [[ ${value} == "" ]];then
echo  $count
fi
done


exit 0
#дһ�� bash�ű������һ���ı��ļ� nowcoder.txt �е�5�е����ݡ�
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
#дһ�� bash�ű���������� 0 �� 500 �� 7 �ı���(0 7 14 21...)������
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