cmake_minimum_required(VERSION 3.16.3)

project(wxYield_IdelEvents)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_C_COMPILER clang-14)
set (CMAKE_CXX_COMPILER clang++-14)
set (CMAKE_VERBOSE_MAKEFILE ON)

# 在不同的电脑主机上，安装目录的位置有所不同。以实际情况为准
# 下面的安装位置是编译安装的默认位置
set (WX_INCLUDE_DIR "/usr/local/include/wx-3.2")
set (WX_LIBRARY_DIR "/usr/local/lib")

# 通过执行 wx-config --cxxflags 获得
# -I/usr/local/lib/wx/include/gtk3-unicode-3.2 -I/usr/local/include/wx-3.2 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXGTK__
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${WX_LIBRARY_DIR}/wx/include/gtk3-unicode-3.2")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${WX_INCLUDE_DIR}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXGTK__ -pthread -g")

add_definitions(-w) # 禁止编译器的警告输出

set (SOURCES
    src/main.cpp
    src/MyFrame.cpp
)

add_executable( ${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC
        ${WX_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/include
)


# 需要为 wx widgets 准备的所有的链接库文件
# 为什么不使用 set (CMAKE_LINKER_FALGS "XXX") 而使用下面的这个函数：
# 因为 set (CMAKE_LINKER_FALGS "XXX") 将下面的库文件全部写在目标文件的前面，导致
# ld 在进行链接的时候，无法找到相应的库文件(这是一个 bug，linux 下存在这个问题)

# 需要的库通过 wx-config --libs 获得
# 这里重新编译了 wxwidget 库，从使用 gtk 改为了使用x11,所以下面的 config 结果发生了变化
# 基于 gtk 编译的 wxwidgets bug 就要少了很多
target_link_libraries( ${PROJECT_NAME}
    ${WX_LIBRARY_DIR}/libwx_gtk3u_xrc-3.2.so
    ${WX_LIBRARY_DIR}/libwx_gtk3u_html-3.2.so
    ${WX_LIBRARY_DIR}/libwx_gtk3u_qa-3.2.so
    ${WX_LIBRARY_DIR}/libwx_gtk3u_core-3.2.so 
    ${WX_LIBRARY_DIR}/libwx_baseu_xml-3.2.so 
    ${WX_LIBRARY_DIR}/libwx_baseu_net-3.2.so 
    ${WX_LIBRARY_DIR}/libwx_baseu-3.2.so
    # pthread
)
