cmake_minimum_required(VERSION 3.16.3)

project(splitter_wxwidgets)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_C_COMPILER "clang")
set (CMAKE_CXX_COMPILER "clang++")
set (CMAKE_VERBOSE_MAKEFILE ON)
set (WX_INCLUDE_DIR "/home/yjh/MYSOFTWARE/wxwidgets_3_1_4/include/wx-3.1")
set (WX_LIBRARY_DIR "/home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib")

# 通过执行 wx-config --cxxflags 获得
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/wx/include/gtk3-unicode-static-3.1")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/home/yjh/MYSOFTWARE/wxwidgets_3_1_4/include/wx-3.1")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -pthread")

set (SOURCES 
    src/main.cpp
)

add_executable( ${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories( ${PROJECT_NAME} 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
        ${WX_INCLUDE_DIR}
)

# 需要为 wx widgets 准备的所有的链接库文件
# 为什么不使用 set (CMAKE_LINKER_FALGS "XXX") 而使用下面的这个函数：
# 因为 set (CMAKE_LINKER_FALGS "XXX") 将下面的库文件全部写在目标文件的前面，导致
# ld 在进行链接的时候，无法找到相应的库文件(这是一个 bug，linux 下存在这个问题)

# 需要的库通过 wx-config --libs 获得
target_link_libraries( ${PROJECT_NAME}
    ${WX_LIBRARY_DIR}/libwx_gtk3u_xrc-3.1.a
    ${WX_LIBRARY_DIR}/libwx_gtk3u_qa-3.1.a
    ${WX_LIBRARY_DIR}/libwx_baseu_net-3.1.a
    ${WX_LIBRARY_DIR}/libwx_gtk3u_html-3.1.a
    ${WX_LIBRARY_DIR}/libwx_gtk3u_core-3.1.a
    ${WX_LIBRARY_DIR}/libwx_baseu_xml-3.1.a
    ${WX_LIBRARY_DIR}/libwx_baseu-3.1.a
    ${WX_LIBRARY_DIR}/libwxtiff-3.1.a
    ${WX_LIBRARY_DIR}/libwxjpeg-3.1.a
    ${WX_LIBRARY_DIR}/libwxregexu-3.1.a
    ${WX_LIBRARY_DIR}/libwxscintilla-3.1.a
    gthread-2.0
    X11
    SM
    gtk-3
    gdk-3
    pangocairo-1.0
    atk-1.0
    cairo-gobject
    cairo
    gdk_pixbuf-2.0
    Xtst 
    pangoft2-1.0 
    pango-1.0 
    harfbuzz 
    fontconfig 
    freetype  
    expat 
    png 
    z 
    dl 
    secret-1 
    gio-2.0 
    gobject-2.0 
    glib-2.0 
    m
)