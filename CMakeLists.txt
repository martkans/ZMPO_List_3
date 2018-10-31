cmake_minimum_required(VERSION 3.12)
project(Lista3)

set(CMAKE_CXX_STANDARD 98)

include_directories(ApplicationRunner)
include_directories(CCommand)
include_directories(Menu)
include_directories(Table)
include_directories(Table/CTable)
include_directories(Table/CTableHandler)
include_directories(Tools)

add_executable(Lista3
        ApplicationRunner/ApplicationRunner.cpp
        ApplicationRunner/ApplicationRunner.h
        CCommand/CCommand.cpp
        CCommand/CCommand.h
        Menu/Menu.cpp
        Menu/Menu.h
        Table/CTable/CTable.cpp
        Table/CTable/CTable.h
        Table/CTableHandler/CTableHandler.cpp
        Table/CTableHandler/CTableHandler.h
        Tools/Tools.cpp
        Tools/Tools.h
        Menu/CMenuBuilder.cpp
        Menu/CMenuBuilder.h
        main.cpp)