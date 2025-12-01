cmake_minimum_required(VERSION 3.15)
project(base2_rval_quote)

# 强制 C++17 标准（匹配你的需求，且确保移动语义正常）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 关闭返回值优化（兼容 GCC/Clang/MSVC，移除冗余配置）
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fno-elide-constructors) # 仅 GCC/Clang 有效
elseif (MSVC)
    add_compile_options(/Od) # MSVC 关闭优化，间接关闭 RVO
endif()

# 添加可执行文件
add_executable(base2 base2.cpp)