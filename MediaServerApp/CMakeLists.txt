cmake_minimum_required(VERSION 3.18)
project(MediaServerApp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


add_executable(${PROJECT_NAME}
    ViewModel/ftpconfig.cpp
    ViewModel/quotes.cpp
    ViewModel/screensaver.cpp    
    ViewModel/sambaconfig.cpp
    ViewModel/massstorage.cpp
    ViewModel/sambaconfigexternaldevice1.cpp
    ViewModel/sambaconfigexternaldevice2.cpp
    ViewModel/sambaconfigexternaldevice3.cpp
    ViewModel/settingsscreensaver.cpp
    ViewModel/multimediaconfig.cpp  
    ViewModel/sambaconfiglocal.cpp
    ViewModel/sambaconfigglobal.cpp
    ViewModel/napimanager.cpp 
    ViewModel/settingspackages.cpp
    ViewModel/settingsscreensaver.cpp
    ViewModel/mainwindow.cpp    
    bluetoothctl.cpp
    screensavermanager.cpp
    start.cpp    
    qml.qrc
)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
  ../MediaServerLib
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        MediaServerLib
           Qt5::Quick
          Qt5::Widgets
          pthread
        )

install(TARGETS ${PROJECT_NAME} DESTINATION "/opt")


