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
        src/DebugMessenger.cpp
        src/Instance.cpp
        src/Window.cpp

        src/maths/mat4.cpp
        src/maths/quaternion.cpp
        src/maths/vec2.cpp
        src/maths/vec3.cpp
        src/maths/vec4.cpp

        # Other Sources
        src/maths/geometry.cpp
        src/maths/transforms.cpp
        src/maths/trigonometry.cpp

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

target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:DEBUG>)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)