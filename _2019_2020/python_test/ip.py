#!/usr/bin/env python
# coding=utf-8
'''
import socket
import fcntl
import struct
  
def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', ifname[:15])
    )[20:24])
print get_ip_address('wlp7s0')
'''
import subprocess
res = subprocess.check_output(['ip','addr'])
'''
if res.find('inet ') != -1 :
	print 'yes0'
	tup1 = res.partition('inet ')
else :
	print 'not0'
if tup1[2].find('inet ') != -1 :
	print 'yes1'
	tup2 = tup1[2].partition('inet ')
else :
	print 'not1'
if tup2[2].find('inet ') != -1 :
	print 'yes2'
	tup3 = tup2[2].partition('inet ')
else :
	print 'not2'
'''
'''
import sys
def find_inet(str):
	place = str.find('inet ')
	if place != -1 :
		#print '\n'
		str = str.partition('inet ')[2]
		j = 0
		while str[j] !='/' :
			sys.stdout.write(str[j])
			j += 1
		print ' '
		find_inet(str)
	else :
		#print 'not'
		return 0

find_inet(res)
'''

import sys
def find_inet(str):
	p= str.find(': <')
	if p != -1 :
		str0 = str.partition(': <')[0]
		str = str.partition(': <')[2]
		i = -1
		j = 1
		strp = ':'
		while str0[i] !=':' :
			strp += str0[i]
			i -= 1
			j += 1
		print strp[::-1],
		if str.find(': <') > str.find('inet ') or str.find(': <') == -1:
			str2 = str.partition('inet ')[2]
			k = 0
			while str2[k] !='/' :
				sys.stdout.write(str2[k])
				k += 1
		else :
			print "it's unavailable",
		print ' '	
		find_inet(str)
	else :
		#print 'not'
		return 0

if __name__ == "__main__":
	find_inet(res)
















