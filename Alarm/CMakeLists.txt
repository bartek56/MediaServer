cmake_minimum_required(VERSION 3.13)
project(Alarm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME}
    ViewModel/AlarmView.cpp
    main.cpp
    resources/qml.qrc
)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    ${CMAKE_SOURCE_DIR}/MediaServerLib
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    MediaServerLib
    Qt5::Quick
    Qt5::Widgets
    QtSystemd
    Qt5::DBus
)

install(TARGETS ${PROJECT_NAME} DESTINATION "/opt")


