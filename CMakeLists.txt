cmake_minimum_required(VERSION 3.14)
project(MediaServer)

find_package(Qt5 COMPONENTS Core Widgets Quick)
#set(Qt5Core_DIR "/opt/qt5.15.2/lib/cmake/Qt5Core")
#set(Qt5_DIR "/opt/qt5.15.2/lib/cmake/Qt5")
#set(QT_QMAKE_EXECUTABLE "/opt/qt5.15.2/bin/qmake")

add_subdirectory(MediaServerLib)
add_subdirectory(MediaServerStartup)
add_subdirectory(MediaServerApp)
add_subdirectory(Alarm)
