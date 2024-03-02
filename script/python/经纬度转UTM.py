import pyproj

# 创建UTM坐标系对象
utm_crs = pyproj.CRS.from_epsg(32650)  # EPSG 32650对应的是WGS84的UTM Zone 50N

# 创建经纬度坐标系对象
lat_lon_crs = pyproj.CRS('EPSG:4326')  # WGS84经纬度坐标系

# 创建转换器
transformer = pyproj.Transformer.from_crs(lat_lon_crs, utm_crs, always_xy=True)

# 定义经纬度坐标
lon, lat = 117.02101, 35.21265

# 将经纬度坐标转换成UTM坐标
x, y = transformer.transform(lon, lat)

print("UTM东坐标：", x)
print("UTM北坐标：", y)


# from pyproj import CRS, Transformer
#
# def UTMtoLatLon(utm_x, utm_y):
#     crs_utm = CRS.from_string("EPSG:32650")  # UTM 49N的EPSG代码为32649
#     crs_latlon = CRS.from_string("EPSG:4326")  # WGS84经纬度坐标的EPSG代码为4326
#     transformer = Transformer.from_crs(crs_utm, crs_latlon)
#     lon, lat = transformer.transform(utm_x, utm_y)
#     return lat, lon
#
# utm_x = 586385.782842
# utm_y = 4140674.76063
# lat, lon = UTMtoLatLon(utm_x, utm_y)
#
# print("Latitude:", lat)
# print("Longitude:", lon)
