cmake_minimum_required(VERSION 3.25)
project(sudoku)

# 本项目的Cmake配置
cmake_minimum_required(VERSION 3.16)
project(MyProject)

# 1、设置 Google Tesk 的版本号，头文件路径，链接库路径
set(GTEST_VERSION 1.10.0)
add_subdirectory(googletest)
include_directories(googletest/include)

# 2、设置 Google Mock 的路径，头文件路径，链接库路径
set(GMOCK_DIR googletest/googlemock)
include_directories(${GMOCK_DIR}/include)
link_directories(${GMOCK_DIR}/build)

# 3、将测试代码添加到可执行文件中
add_executable(MyTest test.cpp sudoku.cpp sudoku.h)

# 4、链接 googletest 库
target_link_libraries(MyTest gtest gtest_main)

# 5、链接 Google Mock 的链接库
target_link_libraries(MyTest gmock gmock_main)

set(CMAKE_CXX_STANDARD 17)
