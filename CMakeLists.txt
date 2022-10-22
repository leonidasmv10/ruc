cmake_minimum_required(VERSION 3.16)

SET(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

SET(URL 127.0.0.1)
SET(USER root)
SET(PASS )
SET(DB test)

project(ruc)

file(GLOB_RECURSE MAIN
         RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
         ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

file(GLOB_RECURSE dao 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dao/*.h
)

file(GLOB_RECURSE data
    ${CMAKE_CURRENT_SOURCE_DIR}/src/data/*.h
)

file(GLOB_RECURSE gui  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/*.h
)

file(GLOB_RECURSE system  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/*.h
)

file(GLOB_RECURSE tool  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tool/*.h
)

file(GLOB_RECURSE zar  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/zar.h
)

source_group("Files/dao" FILES ${dao})
source_group("Files/data" FILES ${data})
source_group("Files/gui" FILES ${gui})
source_group("Files/system" FILES ${system})
source_group("Files/tool" FILES ${tool})
source_group("Files" FILES ${zar})

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(libzippp CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/vendor/include)
link_directories(${CMAKE_SOURCE_DIR}/vendor/lib)

configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_SOURCE_DIR}/config.h)

add_executable(${PROJECT_NAME} ${MAIN} ${dao} ${data} ${gui} ${system} ${tool} ${zar})

target_link_libraries(${PROJECT_NAME} PRIVATE
libcrypto libssl mysqlcppconn mysqlcppconn8) 

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE libzip::zip libzippp::libzippp)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/vendor/bin
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/Debug)
                
