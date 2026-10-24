cmake_minimum_required(VERSION 3.11)

add_subdirectory(hogdir)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
endif()

add_executable(
    HogMaker
    HogMaker/HogFormat.cpp
    HogMaker/HogMaker.cpp
)

target_include_directories(HogMaker PRIVATE
    HogMaker
    ${CMAKE_SOURCE_DIR}/lib
    ${PROJECT_BINARY_DIR}/lib
)

export(TARGETS HogMaker FILE "${CMAKE_BINARY_DIR}/HogMakerConfig.cmake")
