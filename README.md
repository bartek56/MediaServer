# MediaServer [![Build Status](https://travis-ci.org/bartek56/MediaServer.svg?branch=master)](https://travis-ci.org/bartek56/MediaServer)

Qt Application which is using in [Media Server](https://github.com/bartek56/meta-mediaserver) project

Libraries:
- Qt GUI
  - EGLFS
  - OpenGL ES 2.0
- Qt Quick Controls
- Qt Network

Dependencies:
- qml-module-qtquick-controls2
- qtvirtualkeyboard-plugin
- qml-module-qt-labs-folderlistmodel
- [QtSystemd](https://github.com/bartek56/libsystemd-qt)


Configure and build qt5.15.2 for Ubuntu 18 this app:
- ./configure -prefix /opt/qt5.15.2 -skip qtwebengine -skip qtlocation -xcb
- make
- make install

