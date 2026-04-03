#ifndef SHADER_SOURCE_DISPLAY_H
#define SHADER_SOURCE_DISPLAY_H

#include "Display.h"
#include "ShaderSourceModel.h"
#include "ShaderManager.h"

constexpr std::string_view titleShaderSource =  "Shader Sources";

class ShaderSourceDisplay : public Display<gfx::ShaderManager, ShaderSourceModel>
{
    Q_OBJECT

    public:
        explicit ShaderSourceDisplay(gfx::ShaderManager* shaderManager, QWidget* parent = nullptr);

    signals:
        void shaderProgramLinked();

    private:
        // Texture specific button control functions
        void compileSource();
        void compileAllSources();
        void unloadShader();
        void unloadAllShaders();

        void linkIntoProgram(const std::string& name);
        
        // Texture specific layout
        void createButtonPanel(QHBoxLayout* parentLayout) override;
};


#endif