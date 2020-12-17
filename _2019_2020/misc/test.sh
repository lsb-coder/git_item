#!bin/bash

echo "Shell 传递参数实例！";
echo "执行的文件名：$0";
echo "第一个参数为：$1";
echo "第二个参数为：$2";
echo "第三个参数为：$3";
echo "传递到脚本的参数个数：$#";
echo "以一个单字符串显示所有向脚本传递的参数：$*";
echo "与\$*相同，但是使用时加引号，并在引号中返回每个参数：$@";
echo "-- \$* 演示 ---"
for i in "$*"; do
    echo $i
done

echo "-- \$@ 演示 ---"
for i in "$@"; do
    echo $i
done
echo "脚本运行的当前进程ID号：$$";
echo "后台运行的最后一个进程的ID号：$!";
echo "显示Shell使用的当前选项：$-";
echo "显示最后命令的退出状态。0表示没有错误，其他任何值表明有错误：$?";

