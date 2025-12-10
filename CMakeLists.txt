cmake_minimum_required(VERSION 3.15)

# 强制 C++14 标准（匹配你的需求，且确保移动语义正常）
set(CMAKE_CXX_STANDARD 14) #标准一定要为14才能关闭RVO
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS -fno-elide-constructors)

# 关闭返回值优化（兼容 GCC/Clang/MSVC，移除冗余配置）
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fno-elide-constructors) # 仅 GCC/Clang 有效
elseif (MSVC)
    add_compile_options(/Od) # MSVC 关闭优化，间接关闭 RVO
endif()

add_subdirectory(Base1_const)
add_subdirectory(base2_rval_quote)
add_subdirectory(base3_arr_fun_ptr)
add_subdirectory(base4_class_layout)
add_subdirectory(base5_RTTI)
add_subdirectory(base6_class_cast)
add_subdirectory(clause1_template_derivation)
add_subdirectory(clause2_auto_derivation)
add_subdirectory(clause3_decltype)
add_subdirectory(clause7_initial)
add_subdirectory(clause9_using_typedef)
add_subdirectory(clause23_move_forward)