cmake_minimum_required(VERSION 3.16)
project(kebab)

# set the output directory for built objects. This makes sure that the dynamic
# library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_C_FLAGS "-Werror -Wall -Wextra")
set(KEBAB_SRC src/main.c)
# set(CMAKE_BUILD_TYPE debug)

# Create your game executable target as usual
add_executable(${PROJECT_NAME} ${KEBAB_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE src/include)

# Link to the actual SDL3 library.
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
