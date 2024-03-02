import sys
import cv2

from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QFileDialog

from PyQt5.QtCore import pyqtSlot, Qt

from PyQt5.QtGui import QImage, QPixmap

from PyQt5.QtMultimedia import (QCameraInfo, QCameraImageCapture,
                                QImageEncoderSettings, QMultimedia, QVideoFrame, QSound, QCamera)

from ui_MainWindow import Ui_MainWindow


class QmyMainWindow(QMainWindow):

    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_MainWindow()  # 创建UI对象
        self.ui.setupUi(self)  # 构造UI界面

        self.__LabCameraState = QLabel("摄像头state:")
        self.__LabCameraState.setMinimumWidth(150)
        self.ui.statusBar.addWidget(self.__LabCameraState)

        self.__LabImageID = QLabel("图片文件ID:")
        self.__LabImageID.setMinimumWidth(100)
        self.ui.statusBar.addWidget(self.__LabImageID)

        self.__LabImageFile = QLabel("")  # 保存的图片文件名
        self.ui.statusBar.addPermanentWidget(self.__LabImageFile)

        self.camera = None  # QCamera对象
        cameras = QCameraInfo.availableCameras()  # list[QCameraInfo]


        print(str(len(cameras)) + " camera find!")
        if len(cameras) > 0:
            self.__iniCamera()  # 初始化摄像头
            self.__iniImageCapture()  # 初始化静态画图
            self.camera.start()

    def __iniCamera(self):  # 创建 QCamera对象
        camInfo = QCameraInfo.defaultCamera()  # 获取缺省摄像头
        #camInfo = QCameraInfo.availableCameras()  # 获取所有摄像头

        self.ui.comboCamera.addItem(camInfo.description())  # 摄像头描述
        #self.ui.comboCamera.addItem(camInfo.)

        self.ui.comboCamera.setCurrentIndex(0)
        self.camera = QCamera(camInfo)  # 创建摄像头对象
        self.camera.setViewfinder(self.ui.viewFinder)  # 设置取景框预览
        self.camera.setCaptureMode(QCamera.CaptureStillImage)  # 抓取静态图片模式

        self.camera.stateChanged.connect(self.do_cameraStateChanged)

    def __iniImageCapture(self):  ##创建 QCameraImageCapture对象
        self.capturer = QCameraImageCapture(self.camera)
        settings = QImageEncoderSettings()  # 拍照设置
        settings.setCodec("image/jpeg")  # 设置抓图图形编码
        settings.setResolution(640, 480)  # 分辨率
        settings.setQuality(QMultimedia.HighQuality)  # 图片质量
        self.capturer.setEncodingSettings(settings)

        self.capturer.setBufferFormat(QVideoFrame.Format_Jpeg)  # 缓冲区格式

        dest = QCameraImageCapture.CaptureToFile  # 保存到文件（必定执行）

        self.capturer.setCaptureDestination(dest)  # 保存目标

        self.capturer.readyForCaptureChanged.connect(self.do_imageReady)

        self.capturer.imageCaptured.connect(self.do_imageCaptured)

    @pyqtSlot()  # 拍照
    def on_actCapture_triggered(self):
        self.camera.searchAndLock()  # 快门半按下时锁定摄像头参数
        self.capturer.capture()  # 拍照
        self.camera.unlock()  # 快门按钮释放时解除锁定

    @pyqtSlot()  # 打开摄像头
    def on_actStartCamera_triggered(self):
        self.camera.start()
        print("打开摄像头")

    @pyqtSlot()  # 关闭摄像头
    def on_actStopCamera_triggered(self):
        self.camera.stop()
        print("关闭摄像头")

    def do_cameraStateChanged(self, state):
        if (state == QCamera.UnloadedState):
            self.__LabCameraState.setText("摄像头状态: UnloadedState")
        elif (state == QCamera.LoadedState):
            self.__LabCameraState.setText("摄像头状态: LoadedState")
        elif (state == QCamera.ActiveState):
            self.__LabCameraState.setText("摄像头状态: ActiveState")

        self.ui.actStartCamera.setEnabled(state != QCamera.ActiveState)
        self.ui.actStopCamera.setEnabled(state == QCamera.ActiveState)

    def do_imageReady(self, ready):
        self.ui.actCapture.setEnabled(ready)
        print("摄像头可以拍照")

    def do_imageCaptured(self, imageID, preview):  # 图片被抓取到内存
        print("捕捉图片")
        # preview是 QImage
        # H = self.ui.LabImage.height()
        # W = self.ui.LabImage.width()
        H = 1200
        W = 900

        scaledImage = preview.scaled(W, H,
                                     Qt.KeepAspectRatio, Qt.SmoothTransformation)

        self.ui.LabImage.setPixmap(QPixmap.fromImage(scaledImage))
        self.__LabImageID.setText("图片文件ID:%d" % imageID)
        self.__LabImageFile.setText("图片正在保存")

        file_path = QFileDialog.getSaveFileName(self, "保存文件", "C:\\Users\\zty\\Desktop",
                                                "jpeg files (*.jpeg);;all files(*.*)")

        scaledImage.save(file_path[0], "jpeg")

    def do_imageSaved(self, imageID, fileName):  # 图片被保存
        try:
            self.__LabImageID.setText("图片文件ID:%d" % imageID)
            self.__LabImageFile.setText("图片保存为： " + fileName)
            resize_img = cv2.resize(imageID, dsize=(1200, 900))
            cv2.imwrite(fileName, resize_img)
            print("保存图片")
        except:
            print("未选择保存文件")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = QmyMainWindow()
    form.show()
    sys.exit(app.exec_())
