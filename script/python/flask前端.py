# 轻量级web后端框架flask
# 快速上手文档：https://dormousehole.readthedocs.io/en/latest/quickstart.html
# 安装 pip install flask -i https://pypi.tuna.tsinghua.edu.cn/simple

from flask import Flask, request, render_template

app = Flask(__name__)

# 定义路由和视图函数
@app.route('/')
def index():
    return '欢迎访问网站后台'

@app.route('/users', methods=['GET', 'POST'])
def users():
    if request.method == 'GET':
        # 处理获取用户列表的逻辑
        return '获取用户列表'
    elif request.method == 'POST':
        # 处理创建新用户的逻辑
        return '创建新用户'

@app.route('/users/<int:user_id>', methods=['GET', 'PUT', 'DELETE'])
def user(user_id):
    if request.method == 'GET':
        # 处理获取单个用户信息的逻辑
        return f'获取用户 {user_id} 的信息'
    elif request.method == 'PUT':
        # 处理更新用户信息的逻辑
        return f'更新用户 {user_id} 的信息'
    elif request.method == 'DELETE':
        # 处理删除用户的逻辑
        return f'删除用户 {user_id}'

if __name__ == '__main__':
    app.run()
