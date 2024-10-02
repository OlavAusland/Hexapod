target_include_directories("${PROJECT_NAME}"
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

target_sources(${PROJECT_NAME}
	PUBLIC
	imgui/imgui.cpp
	imgui/imgui_demo.cpp
	imgui/imgui_draw.cpp
	imgui/imgui_impl_glfw.cpp
	imgui/imgui_impl_opengl3.cpp
	imgui/imgui_tables.cpp
	imgui/imgui_widgets.cpp
)
