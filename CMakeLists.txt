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
    ${CORE_MOC_FILES}
) 

target_include_directories(DisplaysLib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source/Texture
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source/Shader
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source/Material
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_link_libraries(DisplaysLib
    PUBLIC 
        ModelsLib
        Qt6::Widgets
)