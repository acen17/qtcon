SOURCES += tst_qbluetoothlocaldevice.cpp
TARGET=tst_qbluetoothlocaldevice
CONFIG += testcase

QT = core bluetooth testlib

symbian: TARGET.CAPABILITY = ReadDeviceData LocalServices WriteDeviceData NetworkControl

CONFIG += insignificant_test    # QTBUG-22017