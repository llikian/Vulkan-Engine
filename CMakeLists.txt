# Global Project Configuration
cmake_minimum_required(VERSION 3.26)
project(Vulkan-Engine)

# Find Packages


# Sources, Includes & Libraries
set(LIBRARY_SOURCES

)

set(SOURCES
        # Classes


        # Other Sources


        # Libraries
        ${LIBRARY_SOURCES}
)

set(INCLUDES
        include

        # Libraries

)

set(LIBRARIES

)

# Compiler Options
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

set_source_files_properties(${LIBRARY_SOURCES} PROPERTIES COMPILE_FLAGS "-w") # Don't Show Warnings for Library Sources

# CMake Options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Output compile_commands.json

# Set Directory for Binary Files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Executable
add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})

