cmake_minimum_required(VERSION 3.10)

include_directories(
        ./       
        ./sol      
        ./lua/plugins
)

project(usesol LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
        add_definitions( -D_CRT_SECURE_NO_WARNINGS )
endif()

add_subdirectory(lua)

include_directories(${PROJECT_SOURCE_DIR}/lua)

add_executable (usesol main.cpp)
target_link_libraries (usesol lualib socket_core mime_core)

install(
        TARGETS usesol
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/dist
)

install(
        FILES
        test.lua
        DESTINATION ${PROJECT_SOURCE_DIR}/dist/data/luascripts
)