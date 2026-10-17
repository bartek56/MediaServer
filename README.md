# MediaServer [![Build Status](https://travis-ci.org/bartek56/MediaServer.svg?branch=master)](https://travis-ci.org/bartek56/MediaServer)

Qt Application which is using in [Media Server](https://github.com/bartek56/meta-mediaserver) project

Libraries:
- Qt GUI
  - EGLFS
  - OpenGL ES 2.0
- Qt Quick Controls
- Qt Network

Dependencies:
- qml-module-qtquick-controls
- qml-module-qtquick-controls2
- qml-module-qtquick-layouts
- qtvirtualkeyboard-plugin
- qml-module-qt-labs-folderlistmodel
- Qt D-Bus (provided by the selected Qt installation)


Build configuration
-------------------

CMake prefers Qt6 and falls back to Qt5 when Qt6 is not available. Qt6 builds
require Qt 6.3 or newer. Systemd integration is implemented in the project
with Qt D-Bus and does not require an external Qt systemd library.

Build with Qt6 using CMake:

- cmake -S . -B build-qt6 -DCMAKE_PREFIX_PATH=/opt/Qt/6.6.3
- cmake --build build-qt6

For the Debian/Ubuntu Qt6 packages installed under `/usr`, use:

- cmake -S . -B build-qt6 -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu -DCMAKE_IGNORE_PATH=/usr/lib/Qt
- cmake --build build-qt6

Build with Qt6 using qmake:

- qmake6 MediaServer.pro
- make

The existing Qt5 build remains available by pointing CMake/qmake at a Qt5
installation. For the original Ubuntu 18 setup:

- ./configure -prefix /opt/qt5.15.2 -skip qtwebengine -skip qtlocation -xcb
- make
- make install

