# 描述


## 1. 动机

偶然在 Youtube 上看见的一个C++界面编程的工具。感觉挺有意思的。使用操作系统原生的界面进行编程。

## 2. 更新

1. 安装从源码进行安装，wxwidget 拥有自己的 github 仓库，

* 仓库的地址为：https://github.com/wxWidgets/wxWidgets。

* 其官方的网站为: https://www.wxwidgets.org/

1. 源码安装之后，库的 cmake 配置文件存在问题，本人也不知道怎么弄。所以在cmake当中干脆直接引用库的安装地址了。后面通过在安装目录下手写了一个config 文件解决了这个问题。

2. wx-config 命令是 wxwidget 提供的一个命令行工具。可以告诉我们如何引用它，以及需要使用哪些库




## 补充:

例如使用命令 ```wx-config --cxxflags``` 它在我的 ubuntu-20.04 上面的输出如下：

```
-I/home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/wx/include/gtk3-unicode-static-3.1 -I/home/yjh/MYSOFTWARE/wxwidgets_3_1_4/include/wx-3.1 -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -pthread
```

使用命令 ```wx-config --libs``` 其输出如下：

```
-L/home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib -pthread   /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_gtk3u_xrc-3.1.a /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_gtk3u_qa-3.1.a /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_baseu_net-3.1.a /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_gtk3u_html-3.1.a /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_gtk3u_core-3.1.a /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_baseu_xml-3.1.a /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_baseu-3.1.a -lgthread-2.0 -pthread -lX11 -lSM -lgtk-3 -lgdk-3 -lpangocairo-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lXtst -lpangoft2-1.0 -lpango-1.0 -lharfbuzz -lfontconfig -lfreetype -lwxtiff-3.1 -lwxjpeg-3.1 -lwxregexu-3.1 -lwxscintilla-3.1 -lexpat -lpng -lz -ldl -lsecret-1 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lm
```