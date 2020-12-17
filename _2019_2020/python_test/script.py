#!/usr/bin/env python
# coding=utf-8
#注释1：上语0等同于“# -*- coding: UTF-8 -*-”，若不添加其一，汉语将不能通过编译，注释也不行。
#文件名：script.py

'''
print("helo world")
print("你好，世界")
'''

'''
if True:
	print ("Answer")
	print "True"
else:
	print ("Answer")
	# 没有严格缩进，在执行时会报错
	print ("False")
'''

'''
#使用斜杠（\）将一行语句分为多行显示
i = 1
j = 2
k = 3
p = i\
	+\
j\
      +k
print p
'''


#单、双、三（'''或"""）引号皆可表示字符串，三引号可由多行组成。
#Triple = '''三引号'''
#print Triple
#print """三引号"""


#注释：单行用#，多行用三引号。


'''
#等待用户输入
raw_input ("按下 enter 键退出，其他任意键显示...\n") #括号不能省
'''

'''
#Python可以在同一行中使用多条语句，语句之间使用分号(;)分割
print "a";print "b";
'''

'''
#print默认输出是换行的，实现不换行可以在变量末尾加上逗号,。
print "a",
print "b"
print "a","b"
'''

"""
#使用脚本形式执行 Python 时，可以接收命令行输入的参数
'''
使用 sys 的 sys.argv 来获取命令行参数：
sys.argv 是命令行参数列表。len(sys.argv) 是命令行参数个数。
'''
import sys
print '参数个数为：',len(sys.argv[1:]),'个参数' #sys.argv[1:]忽略参数0即脚本名
print "参数列表：",str(sys.argv[1:])
'''
#使用getopt模块获取命令行参数:getopt.getopt(args, options，[long_options])
import sys, getopt

def main(argv):
   inputfile = ''
   outputfile = ''
   try:
      #opts：(option, value) 元组列表；args：非选项对应参数列表
      opts, args = getopt.getopt(argv,"hi:o:",["ifile=","ofile="])
   except getopt.GetoptError:
      print 'script.py -i <inputfile> -o <outputfile>'
      sys.exit(2)
   for opt, arg in opts:
      if opt == '-h':
         print 'script.py -i <inputfile> -o <outputfile>'
         sys.exit()
      elif opt in ("-i", "--ifile"):
         inputfile = arg
      elif opt in ("-o", "--ofile"):
         outputfile = arg
   print '输入的文件为：', inputfile
   print '输出的文件为：', outputfile
   print args 

'''当.py文件被直接运行时，if __name__ == '__main__'之下的代码块将被运行；当.py文件以模块形式被导入时，if __name__ == '__main__'之下的代码块不被运行'''
if __name__ == "__main__":
   main(sys.argv[1:])
"""

'''
多个变量赋值
Python允许同时为多个变量赋值。
例如：a = b = c = 1 
以上实例，创建一个整型对象，值为1，三个变量被分配到相同的内存空间上。
——分析1：假如我们在c语言中这样赋值 int a = b = c = 1，那么三个变量值为1，但分配在不同的三个内存空间上，这是c语言上的变量和内存的绑定，可以更改内存的值，然而在Python上，实际是没有变量的，而是名称，名称对应的是创建的对象，该对象值对应着一个值和相应的内存，对象有引用次数的属性（记录多少个名称指向该对象，为0时将被当做垃圾回收），名称更改对应的值时，只是指向拥有新值的对象（新对象引用次数+1，原来的对象引用次数-1），而不是对应的对象更改了值。对象对应唯一的值，值一样的可以是不同对象。
——分析2：如上链式赋值的正确顺序是:a=1,b=a,c=a。why???
也可以为多个对象指定多个变量。
例如：a, b, c = 1, 2, "john"
以上实例，两个整型对象 1 和 2 分别分配给变量 a 和 b，字符串对象 "john" 分配给变量 c。
'''

"""
'''
Python出于对性能的考虑，但凡是不可变对象，在同一个代码块中的对象，只有是值相同的对象，就不会重复创建，而是直接引用已经存在的对象,适用于数字字符不可变数据类型，交互模式下，只有在整型池[-5,256]内，才适用，或者同一行赋值。
列表、元组和字典，则只有通过引用才会id一致，只是赋值一样的，对象不一样。
'''
a=4444444
print(id(a))
b=4444444
print(id(b))
print(a is b)

a='4444444'
print(id(a))
b='4444444'
print(id(b))
print(a is b)

a=[1,2,3]
print(id(a))
b=[1,2,3]
print(id(b))
print(a is b)

a=(1,2,3)
print(id(a))
b=(1,2,3)
print(id(b))
print(a is b)

a={'a':1,'b':2,'c':3}
print(id(a))
b={'a':1,'b':2,'c':3}
print(id(b))
print(a is b)

a=[1,2,3]
print(id(a))
b=a;
print(id(b))
c=a[:];
print(id(c))
print(a is c)
"""


'''
python 复合布尔表达式计算采用短路规则，即如果通过前面的部分已经计算出整个表达式的值，则后面的部分不再计算。
'''
'''
a=0
b=1
if ( a > 0 ) and ( b / a > 2 ):
    print "yes"
else :
    print "no"
'''
'''
# 一个简单的条件循环语句实现汉诺塔问题
def my_print(args):
    print args

def move(n, a, b, c):
    #if 简单条件判断一行搞定:“表达式 if 条件 else 内容”——条件为真则执行表达式，否则输出else后面的内容，else自带输出效果，不用加print。
    my_print ((a, '-->', c)) if n==1 else (move(n-1,a,c,b) or move(1,a,b,c) or move(n-1,b,a,c))

move (3, 'a', 'b', 'c')
print '*******another way*******'
def m(n,a,b,c):
    if n==1:
        my_print((a,'-->',c))
    else:
        move(n-1,a,c,b)
        move(1,a,b,c)
        move(n-1,b,a,c)
m(3,'a','b','c')
'''
'''
Python 没有 switch/case 语句，如果遇到很多中情况的时候，写很多的 if/else 不是很好维护，这时可以考虑用字典映射的方法替代。
'''
'''
import os
def zero():
    return "zero"

def one():
    return "one"

def two():
    return "two"

def num2Str(arg):
    switcher={
        0:zero,
        1:one,
        2:two,
        3:lambda:"three"
    }
    func=switcher.get(arg,lambda:"nothing")
    return func()

if __name__ == '__main__':
    print num2Str(0)
    print num2Str(1)
    print num2Str(2)
    print num2Str(3)
    print num2Str(4)
'''
'''
#将列表中重复的数据放在后面，返回列表中元素去除重复后的个数：

def deduplication(nums):
    # write your code here
    exist_nums = {}  #空字典
    pointer = 0
    a=0
    for num in nums:
        if num not in exist_nums: #判断列表的数是否存在一致的键于字典中
            exist_nums[num] = True #将首个数作为键，以便后续判断去除
            nums[pointer] = num
            pointer += 1
    print nums[0:pointer]
    return pointer
print(deduplication([1,1,1,1,1,1,2,2,2,2,2,2,2,2]))
'''
'''
#八皇后问题，递归回溯思想
def queen(A, cur=0): #当前计数默认为0
    if cur == len(A):
        print (A)
        return 0 #回去继续查找新解
    for col in range(len(A)): #列数依次循环
        A[cur], flag = col, True #行对应列
        for row in range(cur):
		#判断与之前的行对应列是否一样及判断是否在对角线上
            if A[row] == col or abs(col - A[row]) == cur - row:
                flag = False
                break
        if flag:
            queen(A, cur+1)
queen([None]*8)
'''
'''
#找出列表某个值的索引
def deduplication(self, nums):
    for i in range(len(nums)):
        if nums[i]==self:
            return i
print(deduplication(1, [5,3,1,6]))
'''
'''
#将一个列表里的数奇偶划分到不同列表中
numbers = [12,37,5,42,8,3]
even = []
odd = []
while len(numbers) > 0 :
	number = numbers.pop()
	if(number % 2 == 0):
		even.append(number)
	else:
		odd.append(number)
print even, odd
'''
'''列表方法
list.pop():弹出元素，当（）内无索引数时默认弹出最后一个元素;
list.remove("")方法删除指定元素(仅删除最左边的一个），没有该元素时报错；
删除，还可以利用del[索引数] 函数删除指定索引数的元素（del是python语句，而不是列表方法，无法通过list来调用）。
list.append(ele)：添加任意一个元素到列表末尾
list.extend([list])：添加一个列表到列表末尾
list.insert(pos,ele)：添加一个元素到列表指定位置之前
'''
'''
#猜大小游戏
import random
s = int(random.uniform(1,10))
print(s)
m = int(input('输入整数:'))
while m != s:
    if m > s:
        print('大了')
        m = int(input('输入整数:')) #input()函数返回值是str型，故这里需强制转换
    if m < s:
        print('小了')
        m = int(input('输入整数:'))
    if m == s:
        print('OK')
        break;
'''
'''
#猜拳游戏
import random
while 1:
    s = int(random.randint(1, 3))
    if s == 1:
        ind = "石头"
    elif s == 2:
        ind = "剪子"
    elif s == 3:
        ind = "布"
#python raw_input() 用来获取控制台的输入。raw_input() 将所有输入作为字符串看待，返回字符串类型。input输入字符时需加引号，通常使用raw_input
    m = raw_input('输入 石头、剪子、布,输入"end"结束游戏:')
    blist = ['石头', "剪子", "布"]
    if (m not in blist) and (m != 'end'):
        print "输入错误，请重新输入！"
    elif (m not in blist) and (m == 'end'):
        print "\n游戏退出中..."
        break
    elif m == ind :
        print "电脑出了： " + ind + "，平局！"
    elif (m == '石头' and ind =='剪子') or (m == '剪子' and ind =='布') or (m == '布' and ind =='石头'):
        print "电脑出了： " + ind +"，你赢了！"
    elif (m == '石头' and ind =='布') or (m == '剪子' and ind =='石头') or (m == '布' and ind =='剪子'):
        print "电脑出了： " + ind +"，你输了！"
'''
'''
#摇色子游戏
import random
import sys
import time

result = []
while True:
    result.append(int(random.uniform(1,7)))
    result.append(int(random.uniform(1,7)))
    result.append(int(random.uniform(1,7)))
    print result
    count = 0
    index = 2
    pointStr = ""
    while index >= 0:
        currPoint = result[index]
        count += currPoint
        index -= 1
        pointStr += " "
        pointStr += str(currPoint)
    if count <= 11:
        sys.stdout.write(pointStr + " -> " + "小" + "\n")
        time.sleep( 1 )   # 睡眠一秒
    else:
        sys.stdout.write(pointStr + " -> " + "大" + "\n")
        time.sleep( 1 )   # 睡眠一秒
    result = []
'''
'''
#十进制转二进制
denum = input("输入十进制数:")
print denum,"(10)",
binnum = []
# 二进制数
while denum > 0:
    binnum.append(str(denum % 2)) # 栈压入
    denum //= 2
print '= ',
while len(binnum)>0:
    import sys
    sys.stdout.write(binnum.pop()) # 无空格输出
print ' (2)'
'''
'''
rows = int(raw_input('输入行数： '))
i = j = k = 1 #声明变量，i用于控制外层循环（图形行数），j用于控制空格的个数，k用于控制*的个数
#等腰直角三角形1
print "等腰直角三角形1"
for i in range(0, rows):
    for k in range(0, rows - i):
        print " * ", #注意这里的","，一定不能省略，可以起到不换行的作用
        k += 1
    i += 1
    print "\n"
'''
'''
#python 创建二维列表，将需要的参数写入 cols 和 rows 即可
#list_2d = [[0 for col in range(cols)] for row in range(rows)]
list_2d = [ [0 for i in range(5)] for i in range(5)]
list_2d[0].append(3)
list_2d[0].append(5)
list_2d[2].append(7)
print list_2d
'''

'''
#针对列表无法正常输出汉字的解决方法：
import json

list_words = [ '你', '我', '他' ]
print( list_words )                                        # 无法正常显示汉字
print( str(list_words).decode( 'string_escape' ) )         # 正常显示汉字

list_words_result = json.dumps( list_words, encoding='UTF-8', ensure_ascii=False )
print( list_words_result )
'''

'''
#python 字符串切片应用

s = 'abcdefg'
# 返回从起始位置到索引位置 2 处的字符串切片
print(s[:3]) # 输出 'abc'

# 返回从第三个索引位置到结尾的字符串切片
print(s[3:]) # 输出 'defg'

# 字符串逆序输出
print(s[::-1]) # 输出 'gfedcba'

# 输出从开始位置间隔一个字符组成的字符串
print(s[::2]) # 输出 'aceg'
print(range(10)[::2])  # 输出偶数：[0, 2, 4, 6, 8]

# 它们也可以相互结合使用。
# 从索引位置 6 到索引位置 2，逆向间隔一个字符
print(s[6:2:-2]) # 输出'ge'
'''

"""
'''
编写字典程序
1）用户添加单词和定义
2）查找这些单词
3）如果查不到，请让用户知道
4）循环
'''
#by myself
dict = {'word':1}
while(1):
	select = raw_input("请选择：\n1:update\n2:search\notherkey:exitselect(1,2 or other):")
	if select == '1' :
		print 1
		word = raw_input("请输入单词：")
		defined = raw_input("请输入定义：")
		dict.update({word:defined})
	elif select == '2':
		print dict.get(raw_input("请输入单词："),'undefined')
	else :
		print "exit..."
		break

#by origin
# 字典创建  while开关 字典添加   字典寻找
dictionary = {}
flag = 'a'
pape = 'a'
off = 'a'
while flag == 'a' or 'c' :
    flag = raw_input("添加或查找单词 ?(a/c)")
    if flag == "a" :                             # 开启
        word = raw_input("输入单词(key):")
        defintion = raw_input("输入定义值(value):")
        dictionary[str(word)] = str(defintion)  # 添加字典
        print "添加成功!"
        pape = raw_input("您是否要查找字典?(a/0)")   #read
        if pape == 'a':
            print dictionary
        else :
            continue
    elif flag == 'c':
        check_word = raw_input("要查找的单词:")  # 检索
        for key in sorted(dictionary.keys()):            # yes
            if str(check_word) == key:
                print "该单词存在! " ,key, dictionary[key]
                break
            else:                                       # no
                off = 'b'
        if off == 'b':
            print "抱歉，该值不存在！"
    else:                               # 停止
        print "error type"
        break
"""

'''
#Python的时间和日期
#time module
import time
#time.time():获取时间戳，以秒为单位的浮点小数
print time.time()
#time.localtime():将时间戳转换为时间元组
print time.localtime()
print time.localtime(time.time())
#time.asctime():将时间元组格式化
print time.asctime()
#time.strftime(format,time.localtime):将时间元组转化为格式化字符
print time.strftime("%a %b %Y-%m-%d %H:%M:%S %Y", time.localtime())
#time.strptime(str,format):将格式化字符转化为时间元组
a = "Sat Mar 28 22:24:24 2016"
print time.strptime(a,"%a %b %d %H:%M:%S %Y")
#time.mktime(time.localtime()):将时间元组转化为时间戳
print time.mktime(time.strptime(a,"%a %b %d %H:%M:%S %Y"))

#calendar module
import calendar
#calender.month(Y,m)输出某年某月的日历
print calendar.month(2019,10)
'''

'''
#python传递不可变对象
def ChangeInt( a ):
    a = 10
 
b = 2
ChangeInt(b)
print b # 结果是 2

#传可变对象
# 可写函数说明
def changeme( mylist ):
   "修改传入的列表"
   mylist.append([1,2,3,4]);
   print "函数内取值: ", mylist
   return
 
# 调用changeme函数
mylist = [10,20,30];
changeme( mylist );
print "函数外取值: ", mylist
'''
'''
#不定长参数
# 可写函数说明
def printinfo(*vartuple):
   "打印任何传入的参数"
   print "输出: "
   for var in vartuple:
      print var
   return;
 
# 调用printinfo 函数
printinfo( 10 );
printinfo( 70, 60, 50 );
'''

'''
#lambda函数的语法只包含一个语句：lambda [arg1,arg2,...,argn]:expression
# 可写函数说明
sum = lambda arg1, arg2: arg1 + arg2;
 
# 调用sum函数
print "相加后的值为 : ", sum( 10, 20 )
print "相加后的值为 : ", sum( 20, 20 )
'''

'''
#得出：不定长参数 * 输出一般都是元组的结构形式， ** 双星输出的都是字典形式的 结构，在传值的中也要确保值得准确匹配才行，不然会报错。
def arras(x,y,z=4,*param,**params):
    print(x,y,z);
    for i in range(len(param)):
        print(param[i]);
    for j in params:
        print(j+':'+params[j]);
        
arras(1,2,3,4,5,'Python 风格规范(Google)本项目并非Google 官方项目,.。',foo='foo1=100',h00='hoo1=200',koo='koo1=4000')
'''




















