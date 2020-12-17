#!/usr/bin/env python
#coding=utf-8
#以下为获取网络ip的Python代码,其中方法一自己编写，方法二、三参考网上并改进

#方法一，将shell命令“ip addr”的输出作为文本输入函数，通过字符串的截取实现
print "The first method（一行对应一组）："

import sys
import subprocess

res = subprocess.check_output(['ip','addr'])

def inet_name(str):
	i = -1
	j = 1
	strp = ':'
	while str[i] !=':' :
		strp += str[i]
		i -= 1
		j += 1
	print strp[::-1],

def inet_ip(str):
	if str.find(': <') > str.find('inet ') or str.find(': <') == -1:
		str2 = str.partition('inet ')[2]
		k = 0
		while str2[k] !='/' :
			sys.stdout.write(str2[k])
			k += 1
	else :
		print "it's unavailable",
	print ' '	

def find_inet(str):
	p= str.find(': <')
	if p != -1 :
		str0 = str.partition(': <')[0]
		str = str.partition(': <')[2]
		inet_name(str0) 
		inet_ip(str)	
		find_inet(str)
	else :
		return 0

if __name__ == "__main__":
	find_inet(res)


#方法二，调用模块实现,只能指定名称
print "\n",
print "The second method（需指定名称得到ip）:"

import socket
import fcntl
import struct
import os

print "available name list:"
m = os.system("route -n | grep ^0.0.0.0 | awk '{print $8}'")

def get_ip_address(ifname):
  while (1):
    if ifname == 'end':
        break
    else :
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        print socket.inet_ntoa(fcntl.ioctl(
            s.fileno(),
            0x8915,  # SIOCGIFADDR
            struct.pack('256s', ifname[:15])
        )[20:24])
        get_ip_address(input("请以字符串方式指定名称或输入'end'退出:"))
	break
get_ip_address(input("请以字符串方式指定名称或输入'end'退出:"))


#方法三：调用模块实现，相当于shell,名称和ip前后对应
print "\n",
print "The third method（名称和ip先后对应）:"

import os
m = os.system("route -n | grep ^0.0.0.0 | awk '{print $8}'")
m = os.system("ifconfig -a|grep inet|grep -v 127.0.0.1|grep -v inet6|awk '{print $2}'")
























