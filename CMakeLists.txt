cmake_minimum_required(VERSION 3.5)
project(mod-manager CXX)

set(CMAKE_CXX_STANDARD 20)

# Gather c++ files
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
    src/*.hpp
    include/*.hpp
)

set(CMAKE_EXE_LINKER_FLAGS "-rdynamic")
set(CMAKE_CXX_FLAGS "--no-pie -fPIC")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(mod-manager ${SRC_FILES} )
message("CONAN LIBS: ${CONAN_LIBS}")

conan_target_link_libraries(mod-manager ${CONAN_LIBS})
