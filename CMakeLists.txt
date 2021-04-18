 
cmake_minimum_required(VERSION 2.8)

project(mast_tk)

find_package(Curses REQUIRED)
SET(CURSES_USE_NCURSES TRUE)
include_directories(${CURSES_INCLUDE_DIR})

include_directories("./src")
file(GLOB MTK_SRCS src/*.cpp)
file(GLOB MTK_HDRS src/*.h src/*.hpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcurses -lmenu -lform")
add_library(mast_tk SHARED ${MTK_SRCS})

target_link_libraries(
    mast_tk
    PUBLIC
        ncurses
)

install(TARGETS mast_tk DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${MTK_HDRS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/mast_tk)
