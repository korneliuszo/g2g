cmake_minimum_required(VERSION 3.3)
project (g2g)
add_executable(g2g 
	main.cpp 
	GerberDecoder.cpp 
	Poly.cpp
	Rect.cpp
	Circle.cpp
	GcodePlotter.cpp
)

include_directories ("include")
set_property(TARGET g2g PROPERTY CXX_STANDARD 11)
option(BUILD_WITH_X11 "build with X11" YES)
if(BUILD_WITH_X11)
	add_definitions(-DWITH_CIMG)
	target_link_libraries(g2g X11 pthread)
endif(BUILD_WITH_X11)
target_link_libraries(g2g yaml-cpp)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
#set(CMAKE_BUILD_TYPE Debug)
