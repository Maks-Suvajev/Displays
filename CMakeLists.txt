# QT
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(DisplaysLib
    source/TextureDisplay.cpp
    source/TextureDisplay.h
    ${CORE_MOC_FILES}
) 

target_include_directories(DisplaysLib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_link_libraries(DisplaysLib
    PUBLIC 
        ModelsLib
        Qt6::Widgets
)