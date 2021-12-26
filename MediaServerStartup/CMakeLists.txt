cmake_minimum_required(VERSION 3.14)
project(MediaServerStartup)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME}
    mainwindow.cpp    
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
        )

install(TARGETS ${PROJECT_NAME} DESTINATION "${DEFAULT_INSTALL_PREFIX}/bin")


