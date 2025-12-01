cmake_minimum_required(VERSION 3.15)

# 强制 C++17 标准（匹配你的需求，且确保移动语义正常）
project(clause7_initial)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS -fno-elide-constructors)

# 关闭返回值优化（兼容 GCC/Clang/MSVC，移除冗余配置）
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fno-elide-constructors) # 仅 GCC/Clang 有效
elseif (MSVC)
    add_compile_options(/Od) # MSVC 关闭优化，间接关闭 RVO
endif()

add_executable(item7 item7.cpp)