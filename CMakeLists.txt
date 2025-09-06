cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

project(SRS-Engine LANGUAGES CXX)

include(FetchContent)

# Download UmbraLog
FetchContent_Declare(
  UmbraLogging
  GIT_REPOSITORY "https://github.com/UmbraEngine/logging.git"
  GIT_TAG main)

FetchContent_MakeAvailable(UmbraLogging)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp src/card/card.h src/deck/deck.h
                               src/deck/deck.cpp)

# Include and Link Umbra Libraries
target_link_libraries(${PROJECT_NAME} UmbraLogging)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG
                                                 ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE src)

# Setup system link to compile_commands directory for LSP config
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ln -sf ${CMAKE_BINARY_DIR}/compile_commands.json
          ~/.config/clangd/compile_commands/compile_commands.json)
