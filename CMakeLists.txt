project(database)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME}-server server.cpp storage.cpp)
add_executable(${PROJECT_NAME}-import import.cpp storage.cpp)

set (Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}-server ${Boost_LIBRARIES})

#enable_testing()
#add_subdirectory(tests)

