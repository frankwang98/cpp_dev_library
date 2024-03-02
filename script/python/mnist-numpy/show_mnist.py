import numpy as np
import matplotlib.pyplot as plt

# 读取csv
data_file = open('mnist_train_100.csv','r',encoding='utf-8-sig')
data_list = data_file.readlines()
data_file.close()

# 读取指定行
line = 2
all_values = data_list[line].split(',')
print(all_values)

# 用numpy解析手写字体
image_array = np.asfarray(all_values[1:]).reshape((28,28))
scaled_input = (np.asfarray(all_values[1:])/255*0.99)+0.01
onodes = 10
targets = np.zeros(onodes)+0.01
targets[int(all_values[0])] = 0.99
print(targets)

# 绘制识别结果
plt.imshow(image_array,cmap='Greys', interpolation='None')
plt.show()
print(len(data_list))
print(data_list[0])
