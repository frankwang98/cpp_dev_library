@echo off

::1.创建bat脚本，示例如下
::执行bat脚本
::start 1.bat
::执行cmd命令
start cmd /k "echo hello1"

::2.创建完成后，将脚本放在windows自启动目录即可
::自启动目录——Windows+R，输入shell:startup即可打开
