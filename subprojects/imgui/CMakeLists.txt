cmake_minimum_required(VERSION 3.5)
project(Imgui)
set(CMAKE_CXX_STANDARD 17)

# find_package(glfw3 REQUIRED FATAL_ERROR)
# Set where the ImGui files are stored
set(IMGUI_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    
# Compile as static library 
file(GLOB IMGUI_SOURCES 
    ${IMGUI_PATH}/GraphEditor.cpp
    ${IMGUI_PATH}/ImCurveEdit.cpp
    ${IMGUI_PATH}/ImGradient.cpp
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/ImGuizmo.cpp
    ${IMGUI_PATH}/ImSequencer.cpp

    ${IMGUI_PATH}/imgui_impl_opengl3.cpp
    ${IMGUI_PATH}/imgui_impl_sdl2.cpp

    ${IMGUI_PATH}/textEditor/TextEditor.cpp
    ${IMGUI_PATH}/textEditor/LanguageDefinitions.cpp
) 
set(IMGUI_ICONS
        icons/icons.cpp
        icons/folder.cpp
        icons/fontaudio.cpp
        icons/fa_brands.cpp
        icons/fa_regular.cpp
        icons/fa_solid.cpp
        icons/webfont.cpp
        icons/fork_webfont.cpp
        icons/material_icons.cpp
        icons/kenney.cpp
        icons/StepMath.cpp
    )
set(IMGUI_INC_DIRS
    ${IMGUI_PATH}
    ${IMGUI_PATH}/ImGuiFileDialog
    ${IMGUI_PATH}/icons
)

set(BOOST_REGEX_STANDALONE TRUE)
add_subdirectory(${IMGUI_PATH}/textEditor/vendor/regex)

add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_ICONS} ImGuiFileDialog/ImGuiFileDialog.cpp)
find_package(SDL2 REQUIRED)
target_include_directories(imgui PUBLIC ${IMGUI_INC_DIRS} ${SDL2_INCLUDE_DIRS})
# target_link_libraries(imgui PUBLIC glfw)
target_link_libraries(imgui PUBLIC ${SDL2_LIBRARIES} Boost::regex)