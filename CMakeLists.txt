cmake_minimum_required(VERSION 3.22)

option(BUILD_UNIT_TESTS "Build unit tests" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(BUILD_UNIT_TESTS)
    set(TARGET_NAME "unit_tests")
else()
    set(TARGET_NAME "service_template")
endif()

project(${TARGET_NAME} VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME})

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -W4
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    VERSION_MAJOR = ${PROJECT_VERSION_MAJOR}
    VERSION_MINOR = ${PROJECT_VERSION_MINOR}
    VERSION_PATCH = ${PROJECT_VERSION_PATCH}
)

add_subdirectory(externals)
add_subdirectory(src)

if(BUILD_UNIT_TESTS)
    include(CTest)
    include(GoogleTest)
    enable_testing()
    add_subdirectory(unit_tests)
else()
    target_sources(
        ${PROJECT_NAME}
        PRIVATE
        service.cpp
    )
endif()
