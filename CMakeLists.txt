cmake_minimum_required(VERSION 3.16)
project(basic_block_chain)
set(CMAKE_CXX_STANDARD 17)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)
include_directories(${SODIUM_INCLUDE_DIRS})

# Set the source file for the main executable
set(SOURCE_FILE src/main.cpp)

add_executable(basic_block_chain ${SOURCE_FILE})

target_link_libraries(basic_block_chain ${SODIUM_LIBRARIES})

# Set Clang Tidy options
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

# Enable Clang Format
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
function(format_code)
    find_program(CLANG_FORMAT "clang-format")
    if(CLANG_FORMAT)
        add_custom_target(format ALL
                COMMAND ${CLANG_FORMAT} -i ${SOURCES}
                COMMENT "Formatting source files"
        )
    else()
        message(WARNING "clang-format not found! Please install it to use the formatting target.")
    endif()
endfunction()

# Call the format_code function to create the format target
format_code()
