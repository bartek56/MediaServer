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
    src/ViewModel/FtpConfig.cpp
    src/ViewModel/AlarmConfig.cpp
    src/ViewModel/ScreenSaver.cpp
    src/ViewModel/SambaConfig.cpp
    src/ViewModel/MassStorage.cpp
    src/ViewModel/SambaConfigExternalDevice1.cpp
    src/ViewModel/SambaConfigExternalDevice2.cpp
    src/ViewModel/SambaConfigExternalDevice3.cpp
    src/ViewModel/SettingsScreensaver.cpp
    src/ViewModel/MultimediaConfig.cpp
    src/ViewModel/SambaConfigLocal.cpp
    src/ViewModel/SambaConfigGlobal.cpp
    src/ViewModel/NapiManager.cpp
    src/ViewModel/SettingsStatus.cpp
    src/ViewModel/SettingsPackages.cpp
    src/ViewModel/SettingsScreensaver.cpp
    src/ViewModel/MainWindow.cpp
    src/Bluetoothctl.cpp
    src/ScreenSaverManager.cpp
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

