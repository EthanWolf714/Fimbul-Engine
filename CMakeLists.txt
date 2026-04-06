cmake_minimum_required(VERSION 3.15)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall)
endif()

# -------------------------------------------------------
# Raylib: always use FetchContent for consistent versions
# -------------------------------------------------------
include(FetchContent)

if(EMSCRIPTEN)
    # Emscripten bundles its own GL/GLFW, so build raylib from source
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP true
    )
    FetchContent_MakeAvailable(raylib)

elseif(WIN32)
    # Manual setup - no cmake config files in this install
    include_directories(C:/raylib/include)
    link_directories(C:/raylib/lib)
    add_library(raylib STATIC IMPORTED)
    set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION "C:/raylib/lib/libraylib.a"
    )
    

else()
     # Linux/Mac - try system install first, fall back to FetchContent
    find_package(raylib 5.0 QUIET)
    if(NOT raylib_FOUND)
        FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
            DOWNLOAD_EXTRACT_TIMESTAMP true
        )
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

# Build ImGui as a static library manually
add_library(imgui STATIC
        libs/imgui/imgui.cpp
        libs/imgui/imgui_demo.cpp
        libs/imgui/imgui_draw.cpp
        libs/imgui/imgui_tables.cpp
        libs/imgui/imgui_widgets.cpp
    )
target_include_directories(imgui PUBLIC libs/imgui)

# Build rlImGui as a static library
add_library(rlimgui STATIC
        libs/rlimgui/rlImGui.cpp
    )
target_include_directories(rlimgui PUBLIC
        libs/rlimgui
        libs/imgui
    )
target_link_libraries(rlimgui PUBLIC raylib imgui)
# -------------------------------------------------------
# Executable
# -------------------------------------------------------
file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/main.cpp"
    "${CMAKE_SOURCE_DIR}/Engine/Core/*.cpp"
    "${CMAKE_SOURCE_DIR}/Engine/Renderer/*.cpp"
    "${CMAKE_SOURCE_DIR}/Engine/Resources/*.cpp"
    "${CMAKE_SOURCE_DIR}/Game/Core/*.cpp"
    "${CMAKE_SOURCE_DIR}/Game/map/*.cpp"
    "${CMAKE_SOURCE_DIR}/Game/entities/*.cpp"
    "${CMAKE_SOURCE_DIR}/Editor/Core/*.cpp"
    "${CMAKE_SOURCE_DIR}/Editor/Panels/*.cpp"
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/imgui
    ${CMAKE_SOURCE_DIR}/libs/rlimgui
)

# -------------------------------------------------------
# Platform-specific linking and settings
# -------------------------------------------------------
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    set(EMSCRIPTEN_FLAGS
        "-s USE_GLFW=3"
        "-s ASSERTIONS=1"
        "-s WASM=1"
        "-s ASYNCIFY"
        "--shell-file ${CMAKE_SOURCE_DIR}/web/shell.html"
    )

    if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
        list(APPEND EMSCRIPTEN_FLAGS
            "--preload-file ${CMAKE_SOURCE_DIR}/assets@assets"
        )
    endif()

    target_link_libraries(${PROJECT_NAME} raylib)
    target_compile_options(${PROJECT_NAME} PUBLIC ${EMSCRIPTEN_FLAGS})
    target_link_options(${PROJECT_NAME} PUBLIC ${EMSCRIPTEN_FLAGS})

    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/web
    )

elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} raylib imgui rlimgui opengl32 gdi32 winmm)

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
        target_compile_options(${PROJECT_NAME} PRIVATE -O2)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE -g)
    endif()

elseif(UNIX AND NOT APPLE)
    # Linux (Fedora, Ubuntu, etc.)
    target_link_libraries(${PROJECT_NAME} raylib imgui rlimgui
        GL X11 Xrandr Xinerama Xcursor Xi
        m dl pthread
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(${PROJECT_NAME} PRIVATE -O2)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE -g)
    endif()

elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} raylib imgui rlimgui
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(${PROJECT_NAME} PRIVATE -O2)
    elseif(CMAKE_BUILD_TYPE PRIVATE -g)
    endif()

endif()

# Desktop output directory
if(NOT EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)