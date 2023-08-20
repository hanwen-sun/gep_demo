# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.10)

# 项目信息
project (demo)

add_library(geography_ geobase.cc geoimpl.cc)
# 指定生成目标
add_executable(Impl_demo geography.cc)
target_link_libraries(Impl_demo geography_)

#target_compile_features(Impl_demo PRIVATE cxx_std_17)