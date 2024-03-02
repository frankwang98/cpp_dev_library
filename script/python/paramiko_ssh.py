import paramiko
import scp

"""
一键上传本地代码到多个生产环境
"""

# 远程目标主机信息
hosts = [
    # {
    #     'hostname': '10.10.8.56',
    #     'username': 'ubuntu',
    #     'password': 'wangzf',
    # },
    {
        'hostname': '10.10.6.120',
        'username': 'nvidia',
        'password': 'nvidia',
    },
    {
        'hostname': '10.10.6.150',
        'username': 'nvidia',
        'password': 'nvidia',
    },
    {
        'hostname': '10.10.6.110',
        'username': 'nvidia',
        'password': 'nvidia',
    },
    {
        'hostname': '10.10.6.130',
        'username': 'nvidia',
        'password': 'nvidia',
    },
    {
        'hostname': '10.10.6.140',
        'username': 'nvidia',
        'password': 'nvidia',
    },
    {
        'hostname': '10.10.6.160',
        'username': 'nvidia',
        'password': 'nvidia',
    },
    {
        'hostname': '10.10.6.170',
        'username': 'nvidia',
        'password': 'nvidia',
    },
    {
        'hostname': '10.10.6.180',
        'username': 'nvidia',
        'password': 'nvidia',
    },
    # 可以添加更多的主机信息
]

# 本地zip文件路径
local_file_path = 'C:/Users/dev/Documents/sensor_roadside_info_router/sensor_roadside_info_router.zip'
# 远程目标路径
remote_path = '/home/nvidia'
# 工作路径
work_path = '/home/nvidia/sensor_roadside_info_router'
# 解压文件名称
file_name = 'sensor_roadside_info_router.zip'

# 连接并上传文件到远程主机
def upload_file(hostname, username, password):
    # 创建SSH客户端
    ssh_client = paramiko.SSHClient()
    ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

    # 连接远程主机
    ssh_client.connect(hostname=hostname, username=username, password=password)

    # 创建SCP客户端
    scp_client = scp.SCPClient(ssh_client.get_transport())

    try:
        # 上传文件
        scp_client.put(local_file_path, remote_path)

        # 执行远程命令
        stdin, stdout, stderr = ssh_client.exec_command(f'cd {remote_path} && rm -rf sensor_roadside_info_router'
                                                        f'&& echo "nvidia" | sudo -S apt install -y libmodbus-dev'
                                                        f'&& unzip -d sensor_roadside_info_router {file_name} && rm {file_name}')

        # 输出执行结果
        print(f'=== Output on {hostname} ===')
        print(stdout.read().decode())
        print(stderr.read().decode())
        print(f'=== success {hostname} ===')
        print('=' * 30)
    finally:
        # 关闭连接
        scp_client.close()
        ssh_client.close()


# 依次上传文件到每个远程主机并执行操作
for host in hosts:
    upload_file(host['hostname'], host['username'], host['password'])
