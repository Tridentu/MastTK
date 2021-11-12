 
cmake_minimum_required(VERSION 3.10)

project(mast_tk)

find_package(Curses REQUIRED)
find_package(PkgConfig REQUIRED)


find_package(LibNotify REQUIRED)
pkg_search_module(GTK2 REQUIRED gtk+-3.0)
find_library(MENU_LIBRARY menu)

SET(CURSES_USE_NCURSES TRUE)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${LIBNOTIFY_INCLUDE_DIRS})
include_directories(${GTK2_INCLUDE_DIRS})
include_directories(${CMAKE_INSTALL_PREFIX}/include/termox)

include_directories("./src")
file(GLOB MTK_SRCS src/*.cpp)
file(GLOB MTK_HDRS src/*.h src/*.hpp)


link_directories(${GTK2_LIBRARY_DIRS})


add_definitions(${GTK2_CFLAGS_OTHER})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_library(mast_tk SHARED ${MTK_SRCS})
set( CMAKE_POSITION_INDEPENDENT_CODE ON)
target_link_libraries(
    mast_tk
    PUBLIC
        ${CURSES_LIBRARIES}
	${MENU_LIBRARY}
	${GTK2_LIBRARIES}
	notify
	gobject-2.0
    PRIVATE
	TermOx
)

install(TARGETS mast_tk DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${MTK_HDRS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/mast_tk)
