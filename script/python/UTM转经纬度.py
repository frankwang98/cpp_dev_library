import pyproj

def utm_to_latlon(easting, northing, zone_number, zone_letter):
    proj = pyproj.Proj(proj='utm', zone=zone_number, ellps='WGS84', north=bool(zone_letter >= 'N'))
    lon, lat = proj(easting, northing, inverse=True)
    return lat, lon

# 示例 UTM 坐标：Zone 18N, Easting: 500000, Northing: 4500000
easting = 464101.487
northing = 4378816.449
zone_number = 49
zone_letter = 'N'

latitude, longitude = utm_to_latlon(easting, northing, zone_number, zone_letter)
print("经度（Longitude）：", longitude)
print("纬度（Latitude）：", latitude)

'''
示例：
经度（Longitude）： 106.95852846840508
纬度（Latitude）： 39.52917331736357
'''
