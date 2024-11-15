link_libraries(Ds)

project(DsTest)
add_executable(
    ${PROJECT_NAME} 
    "main.c"
    "xArrTest.cpp"
    "xAllocTest.cpp"

    "ArrTest.c"
    "AllocTest.c"
)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})