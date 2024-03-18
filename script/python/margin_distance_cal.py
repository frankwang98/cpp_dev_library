"""
地图数据处理
"""
import math
import matplotlib.pyplot as plt

def point_to_line_distance(A, B, P):
    x1, y1 = A
    x2, y2 = B
    x0, y0 = P
    
    distance = abs((x2 - x1) * (y1 - y0) - (x1 - x0) * (y2 - y1)) / math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    
    return distance

def read_points_from_file(file_path):
    points = []
    
    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            if line.strip():
                x, y = map(float, line.strip().split()[:2])  # 仅读取前两列数据
                points.append((x, y))
    
    return points

# 继续优化算法
def calculate_distances(traj_points, road_boundary):
    distances = []
    dist_lines = []
    
    for traj_point in traj_points:
        min_left_distance = float('inf')
        min_right_distance = float('inf')
        left_line = None
        right_line = None
        
        for i in range(len(road_boundary) - 1):
            dist = point_to_line_distance(road_boundary[i], road_boundary[i+1], traj_point)
            
            # 判断点在线段左侧还是右侧
            if (road_boundary[i][1] <= traj_point[1] <= road_boundary[i+1][1]) or (road_boundary[i+1][1] <= traj_point[1] <= road_boundary[i][1]):
                if dist < min_left_distance:
                    min_left_distance = dist
                    left_line = ((road_boundary[i][0], road_boundary[i+1][0]), (road_boundary[i][1], road_boundary[i+1][1]))
            else:
                if dist < min_right_distance:
                    min_right_distance = dist
                    right_line = ((road_boundary[i][0], road_boundary[i+1][0]), (road_boundary[i][1], road_boundary[i+1][1]))
        
        distances.append((min_left_distance, min_right_distance))
        dist_lines.append((left_line, right_line))
    
    return distances, dist_lines

def write_distances_to_file(distances, output_file):
    with open(output_file, 'w') as file:
        for distance_pair in distances:
            file.write(f"{distance_pair[0]} {distance_pair[1]}\n")

# 示例数据
traj_points = read_points_from_file('./1.txt')
road_boundary = read_points_from_file('./border_point.txt')  # 道路边界点坐标

distances, dist_lines = calculate_distances(traj_points, road_boundary)

# 绘图
plt.figure()
for point in road_boundary:
    plt.plot(point[0], point[1], 'ko')  # 黑色边界点

for point in traj_points:
    plt.plot(point[0], point[1], 'bo')  # 蓝色轨迹点

plt.gca().set_aspect('equal', adjustable='box')
plt.show()

# 将左右边界距离写入到新的 txt 文件
write_distances_to_file(distances, 'boundary_distances.txt')

print('program end.')