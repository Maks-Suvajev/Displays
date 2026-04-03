#ifndef SHADER_DISPLAY_H
#define SHADER_DISPLAY_H

#include "ShaderSourceDisplay.h"
#include "ShaderCompiledDisplay.h"

#include "ShaderManager.h"

constexpr std::string_view titleShaderDisplay =  "Shader Manager";

class ShaderDisplay : public QWidget
{
    Q_OBJECT

    public:
        explicit ShaderDisplay(gfx::ShaderManager* shaderManager, QWidget* parent = nullptr);

    private:
        std::unique_ptr<QVBoxLayout>         m_layout; // Main connector layout
        std::unique_ptr<ShaderSourceDisplay> m_sourceDisplay;
        std::unique_ptr<ShaderCompiledDisplay> m_compiledDisplay;
};


#endif