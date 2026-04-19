#include "ShaderDisplay.h"

namespace gui
{

ShaderDisplay::ShaderDisplay(gfx::ShaderManager* shaderManager, QWidget* parent)
    : QWidget(parent)
{
    m_layout = std::make_unique<QVBoxLayout>(this);
    m_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);

    QLabel* title = new QLabel("Shader Manager");

    
    title->setAlignment(Qt::AlignCenter);

    QFont font = title->font();
    font.setPointSize(constTitleFontSize);
    title->setFont(font);
    
    m_sourceDisplay = std::make_unique<ShaderSourceDisplay>(shaderManager, this);
    m_compiledDisplay = std::make_unique<ShaderCompiledDisplay>(shaderManager, this);

    m_layout->addWidget(title);
    m_layout->addWidget(m_sourceDisplay.get());
    m_layout->addWidget(m_compiledDisplay.get());

    connect(m_sourceDisplay.get(), &ShaderSourceDisplay::shaderProgramLinked, m_compiledDisplay.get(), &ShaderCompiledDisplay::shaderProgramLinked);
}

}