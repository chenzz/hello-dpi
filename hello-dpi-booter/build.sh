#!/bin/bash
macdeployqt ../build-hello-dpi-worker-Desktop_Qt_5_8_0_clang_64bit-Release/HelloDpiWorker.app
cp -a ../build-hello-dpi-worker-Desktop_Qt_5_8_0_clang_64bit-Release/HelloDpiWorker.app/Contents/Frameworks ../build-hello-dpi-Desktop_Qt_5_8_0_clang_64bit-Release/HelloDpi.app/Contents/
cp -a ../build-hello-dpi-worker-Desktop_Qt_5_8_0_clang_64bit-Release/HelloDpiWorker.app/Contents/PlugIns ../build-hello-dpi-Desktop_Qt_5_8_0_clang_64bit-Release/HelloDpi.app/Contents/
