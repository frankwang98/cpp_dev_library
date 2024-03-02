from selenium import webdriver
import time

# 创建 Chrome 浏览器的 WebDriver 实例
driver = webdriver.Chrome()

# 打开网页
driver.get("https://frankwang98.top")

time.sleep(3)

# 关闭浏览器
driver.quit()
