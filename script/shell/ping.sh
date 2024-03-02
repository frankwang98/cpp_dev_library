#!/bin/bash
# get ping value between ids and router & autoclean log 1 day ago
# @wangzf
# usage: bash ping.sh

net_path="./network/"
target_host="192.168.1.109" # need config

# if folder exist
if [ ! -d "$net_path" ]; then
    mkdir -p "$net_path"
    echo "folder not exist: $net_path"
else
    echo "folder exist: $net_path"
fi

# get timestamp
get_timestamp() {
    date +"%Y-%m-%d %H:%M:%S"
}

# autoclean
if  [ -d "${net_path}" ]; then 
echo start delete log 1 days ago...
    find "${net_path}"/* -name '*.txt' -mtime +0 -exec rm -rf {} \;
echo end delete log ...	
fi

# get ping value
filename_prefix="${net_path}ping"
filename="${filename_prefix}_${timestamp}.txt"

while true; do
    timestamp=$(get_timestamp)  # timestamp loop
    ping_result=$(ping -c 1 $target_host | grep time= | awk -F 'time=' '{print $2}' | cut -d ' ' -f 1)
    
    echo "$timestamp - Ping: $ping_result ms"   # display
    echo "$timestamp - Ping: $ping_result ms" >> "$filename"    # log
    
    sleep 1
done
