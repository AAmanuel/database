find_package(GTest REQUIRED)

function(add_dbtest name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} ${GTEST_BOTH_LIBRARIES})
    target_include_directories(${name} PRIVATE ${GTEST_INCLUDE_DIRS})
    GTEST_ADD_TESTS(${name} "" ${ARGN})
endfunction(add_dbtest)
