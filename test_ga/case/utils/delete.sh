#!/bin/bash
user=haobingzhong
ip=10.172.198.38
password=KLUIPhjelgYugEVq
/usr/bin/expect <<EOF

set timeout 10
spawn ssh  -tt $user@$ip
expect {
    "yes/no" { send "yes\n";exp_continue }
    "password" { send "$password\n" }
}
expect "]#"
send "cd /mnt/data/  \r
shopt -s extglob \r
sudo rm -rf !(megvii-devops|megvii|lost+found) \r
sudo rm -rf /mnt/data-important/* \r \n"
expect eof
EOF
