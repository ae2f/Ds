cmake_minimum_required(VERSION 3.20)
project(Ds VERSION 1.10.2)
enable_testing()
include(cmake/Core.cmake)

if(NOT TARGET ${PROJECT_NAME})

ae2f_CoreLibFetch(ae2f err Rel-v3.9.7)

# Namespace Package
include(GNUInstallDirs)

ae2f_CoreLibTent(
    ${PROJECT_NAME}
    ${ae2f_LIBPREFIX}
    include ae2f

    "include/ae2f/Ds/Alloc.h"
    "include/ae2f/Ds/Alloc.hpp"
    "include/ae2f/Ds/Alloc/Err.h"
    "src/Alloc.c"
    "src/Alloc/Linear.c"

    "include/ae2f/Ds/Arr.h"
    "include/ae2f/Ds/Arr.hpp"
    "include/ae2f/Ds/Arr/Err.h"
    "include/ae2f/Ds/Arr/Defs.hpp"
    "include/ae2f/Ds/Arr/Pack.hpp"
    "src/Arr.c"
)

target_link_libraries(${PROJECT_NAME} PUBLIC err)
ae2f_CoreTestTent(${PROJECT_NAME} test/src)

endif()