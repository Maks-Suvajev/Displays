# QT
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(DisplaysLib
    source/Texture/TextureDisplay.cpp
    source/Texture/TextureDisplay.h
	source/Shader/ShaderSourceDisplay.cpp
    source/Shader/ShaderSourceDisplay.h
    source/Shader/ShaderCompiledDisplay.cpp
    source/Shader/ShaderCompiledDisplay.h
    source/Shader/ShaderDisplay.cpp
    source/Shader/ShaderDisplay.h
    source/SceneModel/SceneModelDisplay.cpp
    source/SceneModel/SceneModelDisplay.h
    ${CORE_MOC_FILES}
) 


target_include_directories(DisplaysLib 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Texture
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Shader
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Material
        ${CMAKE_CURRENT_SOURCE_DIR}/source/SceneModel
)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

target_link_libraries(DisplaysLib
    PUBLIC 
        ModelsLib
        Qt6::Widgets
        Qt6::OpenGLWidgets
        UICommonLib
)