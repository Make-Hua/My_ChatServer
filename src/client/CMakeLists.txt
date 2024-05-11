# 定义一个SRC_LIST变量，包含该目录下的源文件
aux_source_directory(. SRC_LIST)

# 生成可执行文件 ChatServer , 由 SRC_LIST 变量定义的源文件编译而来
add_executable(ChatClient ${SRC_LIST})

# 指定文件编译时所需依赖
target_link_libraries(ChatClient pthread)