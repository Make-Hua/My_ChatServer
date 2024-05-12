# 开启 Bash 调试模式
set -x

# 首先删除 build 目录下的所有文件
rm -rf `pwd`/build/*

# 然后到cd到 build 目录下 
cd `pwd`/build

# 最后执行下述两个命令
cmake .. && make