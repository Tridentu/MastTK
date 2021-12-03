 
cmake_minimum_required(VERSION 3.10)

project(mast_tk)

find_package(Curses REQUIRED)
find_package(PkgConfig REQUIRED)


find_package(LibNotify REQUIRED)
find_package(X11 REQUIRED)
pkg_search_module(GTK2 REQUIRED gtk+-3.0)
find_library(MENU_LIBRARY menu)

SET(CURSES_USE_NCURSES TRUE)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${LIBNOTIFY_INCLUDE_DIRS})
include_directories(${GTK2_INCLUDE_DIRS})
include_directories(${CMAKE_INSTALL_PREFIX}/include/termox)
include_directories(/usr/include/esc )
include_directories("./src/core")
include_directories("/src/termox")
include_directories("/src/ncurses")
include_directories("/src/wmtk")

file(GLOB MTK_SRCS src/core/*.cpp)

file(GLOB MTK_TX_SRCS src/termox/*.cpp)

file(GLOB MTK_NC_SRCS src/ncurses/*.cpp)

file(GLOB MTK_CORE_HDRS src/core/*.h src/core/*.hpp)

file(GLOB MTK_TX_HDRS src/termox/*.h src/termox/*.hpp)

file(GLOB MTK_NC_HDRS src/ncurses/*.h src/ncurses/*.hpp)

link_directories(${GTK2_LIBRARY_DIRS})


add_definitions(${GTK2_CFLAGS_OTHER})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_library(mast_tk_core SHARED
   ${MTK_SRCS}
)

add_library(mast_tk_tx SHARED
    ${MTK_TX_SRCS}
)

add_library(mast_tk_nc SHARED
   ${MTK_NC_SRCS}
)
set( CMAKE_POSITION_INDEPENDENT_CODE ON)
target_link_libraries(
    mast_tk_core
    PUBLIC
	${GTK2_LIBRARIES}
	notify
	gobject-2.0
)

target_link_libraries(
  mast_tk_tx
  PUBLIC
	mast_tk_core
  PRIVATE
	TermOx
	escape
)

target_link_libraries(
   mast_tk_nc
   PUBLIC
       mast_tk_core
   PRIVATE
       ncurses
)


install(TARGETS mast_tk_core DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS mast_tk_tx DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS mast_tk_nc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${MTK_CORE_HDRS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/mast_tk/core)
install(FILES ${MTK_TX_HDRS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/mast_tk/termox)
install(FILES ${MTK_NC_HDRS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/mast_tk/ncurses)
