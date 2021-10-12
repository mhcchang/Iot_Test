cd /home/haobingzhong/gb_lite_linux

#read -p 'test IP : ' ip
if [ $# -gt 1 ];then
	echo "Please input test ip!!!!"
fi	
#sed  -i  '6d' param.json
#sed -i "5a 'upper_ip':"$1"," param.json 

port_tcp=$(sudo netstat -nlp |grep 5088  |awk  -F '/'  '{print $1}' |awk '{print $7}')
if [ -z "$port_tcp" ];then
	echo "gb is not running"
	echo "start run gb_server....."
	`sudo bash run.sh `
	if $! ;then
		echo "gb_server running is OK!!!!"
	else
		echo "gb_server running is Fail!!!"
	fi

else
	echo "gb_server stoping!!!"
	sudo 	kill $port_tcp
	if $! ;then
		echo "$port_tcp is killed,gb_server is stop!!!"
	fi
fi

