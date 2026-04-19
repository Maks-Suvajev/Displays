#ifndef SHADER_COMPILED_DISPLAY_H
#define SHADER_COMPILED_DISPLAY_H

#include "Display.h"
#include "ShaderCompiledModel.h"
#include "ShaderManager.h"

namespace gui
{

constexpr std::string_view titleShaderCompiled =  "Compiled Shader Programs";

class ShaderCompiledDisplay : public Display<gfx::ShaderManager, ShaderCompiledModel>
{
    Q_OBJECT

    public:
        explicit ShaderCompiledDisplay(gfx::ShaderManager* shaderManager, QWidget* parent = nullptr);
    
    public slots:
        void shaderProgramLinked();

    private:
        // Texture specific button control functions
        void unloadShaderProgram();
        void refreshCompiled();
        
        // Texture specific layout
        void createButtonPanel(QHBoxLayout* parentLayout) override;

};

}

#endif