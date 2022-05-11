cmake_minimum_required(VERSION 3.8.0)
project(libxpcsc)
set(CMAKE_C_STANDARD 17)
if (POLICY CMP0092)
    cmake_policy(SET CMP0092 NEW)
endif ()


# The libpcsc-cpp library itself.

add_library(${PROJECT_NAME}
        STATIC
        include/xpcsc.hpp
        src/access_bits.cpp
        src/atrparser.cpp
        src/bertlv.cpp
        src/connection.cpp
        src/debug.hpp
        src/exceptions.cpp
        src/format.cpp
        src/parse_apdu.cpp
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include
        )

target_compile_features(${PROJECT_NAME}
        PUBLIC
        cxx_std_17
        )
