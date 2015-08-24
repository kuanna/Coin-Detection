cmake_minimum_required(VERSION 2.8)
project(coins)

# find OpenCV
find_package(OpenCV REQUIRED)
set(LIBRARY_DEPS ${OpenCV_LIBS})

# INCLUDE
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB srcs "sources/*.cpp" "apps/*.cpp")
file(GLOB hdrs "include/*.hpp")
message(STATUS "----------")
message(STATUS ${srcs})
message(STATUS "----------")
message(STATUS ${hdrs})
message(STATUS "----------")
add_executable(main ${srcs} ${hdrs})
target_link_libraries(main ${LIBRARY_DEPS})

# messages
message( STATUS "   OpenCV build path:    ${OpenCV_DIR}")
