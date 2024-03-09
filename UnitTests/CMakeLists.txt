cmake_minimum_required(VERSION 3.10)
project(UnitTests)
add_subdirectory(googletest)
set(GTEST_DIR "${CMAKE_SOURCE_DIR}/UnitTests/googletest/googletest")
set(GTEST_MOCK_DIR "${CMAKE_SOURCE_DIR}/UnitTests/googletest/googlemock")

include_directories(${GTEST_DIR}/include ${GTEST_MOCK_DIR}/include ../MediaServerLib)

set(SOURCES
    ../MediaServerLib/Utils/VectorData.cpp
    ../MediaServerLib/ConfigFile/AlarmConfigFile.cpp
    ../MediaServerLib/ConfigFile/MpdConfigFile.cpp
    ../MediaServerLib/ConfigFile/DlnaConfigFile.cpp
    ../MediaServerLib/ConfigFile/ScreenSaverConfigFile.cpp
    ../MediaServerLib/ConfigFile/WifiConfigFile.cpp
)

set(TEST_SOURCES
    AlarmConfigFileTest.cpp
    MpdConfigFileTest.cpp
    DlnaConfigFileTest.cpp
    ScreenSaverConfigFileTest.cpp
    WifiFileConfigTest.cpp
    main.cpp
)


add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    Qt5::Quick
)

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests gtest gmock)

target_link_libraries(tests ${PROJECT_NAME})
