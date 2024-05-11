# 定义一个SRC_LIST变量，包含该目录下的源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)

# 生成可执行文件 ChatServer , 由 SRC_LIST 变量定义的源文件编译而来
add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})

# 表示 ChatServer 这个目标程序， 需要连接 muduo_net muduo_base pthread 这3个库文件
# muduo_net muduo_base   muduo 库依赖 注意前后关系
# pthread   线程库依赖(muduo库中也用到了，用 muduo库 就得加上线程依赖)
# mysqlclient      数据库依赖
target_link_libraries(ChatServer muduo_net muduo_base mysqlclient hiredis pthread)