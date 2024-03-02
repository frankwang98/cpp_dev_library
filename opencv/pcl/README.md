# pcl-basic
学习pcl基础，以及相关的Qt、VTK、OpenGL等

## 学习路线
入门
- 可视化
- 输入输出
进阶
- 滤波
- 降采样
高级
- 矩阵等数学概念
- ICP/NDT配准

## pcl_viewer工具
`pcl_viewer xxxxx.pcd`

帮助：在界面中输入h，可以在控制台看到帮助信息

退出：界面中输入q

放大缩小：鼠标滚轮 或 Alt + [+/-]

平移：Shift+鼠标拖拽

旋转：Ctrl+鼠标拖拽

修改点颜色：数字1,2,3,4,5....9，重复按1可切换不同颜色方便观察

放大缩小点：放大Ctrl+Shift+加号，缩小 Ctrl+减号

保存截图：j

显示颜色尺寸：u

显示比例尺寸：g

在控制列出所有几何和颜色信息：l

鼠标选点打印坐标

选点模式进入：`pcl_viewer -use_point_picking bunny.pcd`

选择指定点：shift+鼠标左键

双屏对比：`pcl_viewer -multiview 1  1.pcd 2.pcd`

## pcl_octree_viewer工具
a -> 增加显示深度（减小体素大小）
z -> 降低显示深度 （增加体素大小）
v -> 隐藏或显示octree立方体
b -> 隐藏或显示体素中心店
n -> 隐藏或显示原始点云
q -> 退出

测试数据：阿里云盘-测试数据