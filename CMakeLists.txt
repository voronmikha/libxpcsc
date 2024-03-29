cmake_minimum_required(VERSION 3.18.0)
project(xpcsc C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
        src/aids.cpp
        src/aids.hpp
        src/constants.hpp src/card.cpp src/card.hpp src/card_apps.cpp src/card_apps.hpp src/parser.cpp src/parser.hpp src/config.cpp src/config.hpp src/mifaire.cpp src/get_mifare_uid.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include
        )

# PC/SC API dependencies.

add_library(pcsc INTERFACE)
if (MSVC)
    # no extra includes required
    target_link_libraries(pcsc INTERFACE winscard)
elseif (APPLE)
    # no extra includes required
    target_link_libraries(pcsc INTERFACE "-framework PCSC")
else ()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(PCSC libpcsclite REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${PCSC_INCLUDE_DIRS})
    target_link_libraries(pcsc INTERFACE ${PCSC_LIBRARIES})
endif ()

add_executable(main src/main.cpp)
target_link_libraries(main ${PROJECT_NAME} pcsc xpcsc)

add_executable(mifaire src/mifaire.cpp)
target_link_libraries(mifaire ${PROJECT_NAME} pcsc xpcsc)

add_executable(mifare_uid src/get_mifare_uid.cpp util/print_bytes.c)
target_link_libraries(mifare_uid ${PROJECT_NAME} pcsc xpcsc)