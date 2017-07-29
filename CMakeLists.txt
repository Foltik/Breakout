cmake_minimum_required(VERSION 3.7)
project(breakout)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/include/freetype2/)

set(SOURCE_FILES main.cpp breakout.cpp breakout.h Level.cpp Level.h Paddle.cpp Paddle.h Ball.cpp Ball.h CObject.h Tile.cpp Tile.h)

add_executable(breakout ${SOURCE_FILES})

target_link_libraries(breakout GL GLEW glfw assimp SOIL freetype k5)

add_custom_command(TARGET breakout POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/models
        $<TARGET_FILE_DIR:breakout>/models)

add_custom_command(TARGET breakout POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:breakout>/shaders)

add_custom_command(TARGET breakout POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:breakout>/textures)

add_custom_command(TARGET breakout POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/fonts
        $<TARGET_FILE_DIR:breakout>/fonts)

add_custom_command(TARGET breakout POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:breakout>/resources)