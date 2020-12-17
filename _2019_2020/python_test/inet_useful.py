#!/usr/bin/env python
#coding=utf-8

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
		print ' '	

def find_inet(str):
	p= str.find(': <')
	if p != -1 :
		str0 = str.partition(': <')[0]
		str = str.partition(': <')[2]
		if str.find(': <') > str.find('inet ') or str.find(': <') == -1:
			inet_name(str0) 
			inet_ip(str)	
		find_inet(str)
	else :
		return 0

if __name__ == "__main__":
	find_inet(res)
