cmake_minimum_required(VERSION 3.13)
project(MediaServer)

find_package(Qt5 COMPONENTS Core Widgets Quick DBus)
# -DCMAKE_FIND_DEBUG_MODE=1

#-DCMAKE_PREFIX_PATH=/opt/qt5.15.2
#set(Qt5Core_DIR "/opt/qt5.15.2/lib/cmake/Qt5Core")
#set(Qt5_DIR "/opt/qt5.15.2/lib/cmake/Qt5")
#set(QT_QMAKE_EXECUTABLE "/opt/qt5.15.2/bin/qmake")

include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    # Ustaw maksymalną liczbę wątków na 4, jeśli liczba rdzeni nie jest równa 0
    set(THREADS_FLAG "-j${N}")
else()
    # Ustaw maksymalną liczbę wątków na 4, jeśli nie można pobrać liczby rdzeni
    set(THREADS_FLAG "-j4")
endif()

# Ustaw zmienną środowiskową MAKEFLAGS
set(ENV{MAKEFLAGS} "${THREADS_FLAG}")

add_subdirectory(MediaServerLib)
add_subdirectory(MediaServerStartup)
add_subdirectory(MediaServerApp)
add_subdirectory(Alarm)
add_subdirectory(UnitTests)
