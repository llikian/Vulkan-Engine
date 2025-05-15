# Global Project Configuration
cmake_minimum_required(VERSION 3.26)
project(Vulkan-Engine)

# Find packages


# Compiler options
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Set sources and includes
set(SOURCES
        src/main.cpp

        # Classes
        src/Application.cpp
        src/Window.cpp

        # Other Sources

        # Libraries

)

set(INCLUDES
        include

        # Libraries

)

set(LIBRARIES
        vulkan
        glfw
        dl
        pthread
        X11
        Xxf86vm
        Xrandr
        Xi
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})

# Creates a macro called 'DEBUG' when program is launched in debug mode
target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:DEBUG>)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)