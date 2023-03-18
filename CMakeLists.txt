cmake_minimum_required(VERSION 3.1)

project(unredacted)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release) 

find_package( OpenCV REQUIRED )

add_executable( jpguncrop jpguncrop.cpp  )
target_link_libraries( jpguncrop ${OpenCV_LIBS} )
