cmake_minimum_required(VERSION 3.10)
project(UnitTests)

add_subdirectory(googletest)

set(GTEST_DIR "${CMAKE_SOURCE_DIR}/UnitTests/googletest/googletest")
set(GTEST_MOCK_DIR "${CMAKE_SOURCE_DIR}/UnitTests/googletest/googlemock")

include_directories(${GTEST_DIR}/include ${GTEST_MOCK_DIR}/include ../MediaServerLib)

# app lib
set(SOURCES
    ${CMAKE_SOURCE_DIR}/MediaServerLib/Utils/VectorData.cpp
    ${CMAKE_SOURCE_DIR}/MediaServerLib/ConfigFile/AlarmConfigFile.cpp
    ${CMAKE_SOURCE_DIR}/MediaServerLib/ConfigFile/MpdConfigFile.cpp
    ${CMAKE_SOURCE_DIR}/MediaServerLib/ConfigFile/DlnaConfigFile.cpp
    ${CMAKE_SOURCE_DIR}/MediaServerLib/ConfigFile/ScreenSaverConfigFile.cpp
    ${CMAKE_SOURCE_DIR}/MediaServerLib/ConfigFile/WifiConfigFile.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    Qt5::Quick
)

# unit test binary
set(TEST_SOURCES
    AlarmConfigFileTest.cpp
    MpdConfigFileTest.cpp
    DlnaConfigFileTest.cpp
    ScreenSaverConfigFileTest.cpp
    WifiFileConfigTest.cpp
    main.cpp
)

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests ${PROJECT_NAME} gtest gmock)
