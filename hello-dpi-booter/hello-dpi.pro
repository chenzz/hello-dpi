TEMPLATE = app
CONFIG -= qt
TARGET = HelloDpi

SOURCES += main.cpp

HelloDpiBooter.files = HelloDpiBooter.scpt
HelloDpiBooter.path = Contents/Resources

HelloDpiWorker.files = /Users/chenzz/QtProject/hello-dpi/build-hello-dpi-worker-Desktop_Qt_5_8_0_clang_64bit-Release/HelloDpiWorker.app/Contents/MacOS/HelloDpiWorker
HelloDpiWorker.path = Contents/MacOS

SampleConfigFile.files = /Users/chenzz/QtProject/hello-dpi/build-hello-dpi-worker-Desktop_Qt_5_8_0_clang_64bit-Release/HelloDpiWorker.app/Contents/Resources/DisplayProductID-a02e
SampleConfigFile.path = Contents/Resources


QMAKE_BUNDLE_DATA += HelloDpiBooter HelloDpiWorker SampleConfigFile

ICON = HelloDpi.icns
