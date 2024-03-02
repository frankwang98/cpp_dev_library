import hashlib

def generate_md5(input_string):
    # 创建 MD5 哈希对象
    md5_hash = hashlib.md5()

    # 更新哈希对象的数据
    md5_hash.update(input_string.encode('utf-8'))

    # 获取十六进制表示的 MD5 值
    md5_value = md5_hash.hexdigest()

    return md5_value

# 示例用法
input_string = 'Hello, World!'
md5_result = generate_md5(input_string)

print(f'Input: {input_string}')
print(f'MD5: {md5_result}')
