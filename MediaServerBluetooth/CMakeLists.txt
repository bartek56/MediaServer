cmake_minimum_required(VERSION 3.13)
project(MediaServerBluetooth)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt5 REQUIRED COMPONENTS Core DBus)

add_executable(${PROJECT_NAME}    
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::DBus
    pthread
)

install(TARGETS ${PROJECT_NAME} DESTINATION "/opt")
