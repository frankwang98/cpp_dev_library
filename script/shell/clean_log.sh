#!/bin/bash
log_path="./log/"

# 目录存在，删除修改时间为1天前的文件
if  [ -d "${log_path}" ]; then 
echo start delete log 1 days ago...
    find "${log_path}"/* -name '*.log' -mtime +0 -exec rm -rf {} \;
echo end delete log ...	
fi