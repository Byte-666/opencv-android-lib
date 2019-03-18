# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# OpenCV setup

add_subdirectory(opencv)
find_library(OpenCV REQUIRED)

# find_package(OpenCV REQUIRED)

ocv_get_all_libs(OCV_MODULES OCV_EXTRA OCV_3RDPARTY)
message(STATUS "OpenCV libraries: ${OCV_MODULES}")

set(OCV_INCLUDE_DIR "")
foreach(m ${OCV_MODULES})
    # only "public" headers need to be installed
    get_target_property(incl ${m} INCLUDE_DIRECTORIES)
    list(INSERT OCV_INCLUDE_DIR 0 ${incl})
endforeach()
ocv_list_unique(OCV_INCLUDE_DIR)
ocv_list_reverse(OCV_INCLUDE_DIR)
message(STATUS "OpenCV include_directories: ${OCV_INCLUDE_DIR}")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(parent_DIR ${CMAKE_SOURCE_DIR})
set(include_DIR ${parent_DIR}/opencv/include)
include_directories(
        ${include_DIR}
        ${include_DIR}/opencv
        ${include_DIR}/opencv2
        ${OCV_INCLUDE_DIR})

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/native-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib

        # OpenCV
        ${OCV_3RDPARTY}
        ${OCV_MODULES}
        ${OCV_EXTRA}

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})
