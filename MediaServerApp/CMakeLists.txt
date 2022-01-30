cmake_minimum_required(VERSION 3.13)
project(MediaServerApp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5DBus REQUIRED)
find_package(QtSystemd REQUIRED)


add_executable(${PROJECT_NAME}
    src/ViewModel/ftpconfig.cpp
    src/ViewModel/alarmconfig.cpp
    src/ViewModel/quotes.cpp
    src/ViewModel/screensaver.cpp    
    src/ViewModel/sambaconfig.cpp
    src/ViewModel/massstorage.cpp
    src/ViewModel/sambaconfigexternaldevice1.cpp
    src/ViewModel/sambaconfigexternaldevice2.cpp
    src/ViewModel/sambaconfigexternaldevice3.cpp
    src/ViewModel/settingsscreensaver.cpp
    src/ViewModel/multimediaconfig.cpp  
    src/ViewModel/sambaconfiglocal.cpp
    src/ViewModel/sambaconfigglobal.cpp
    src/ViewModel/napimanager.cpp
    src/ViewModel/settingsStatus.cpp
    src/ViewModel/settingspackages.cpp
    src/ViewModel/settingsscreensaver.cpp
    src/ViewModel/mainwindow.cpp    
    src/bluetoothctl.cpp
    src/screensavermanager.cpp
    src/start.cpp    
    resources/qml.qrc
)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
  ../MediaServerLib
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        MediaServerLib
        QtSystemd
        Qt5::Quick
        Qt5::Widgets
        Qt5::DBus
        pthread
)

install(TARGETS ${PROJECT_NAME} DESTINATION "/opt")

