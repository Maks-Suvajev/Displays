#include "ShaderCompiledDisplay.h"

ShaderCompiledDisplay::ShaderCompiledDisplay(gfx::ShaderManager* shaderManager, QWidget* parent)
    : Display<gfx::ShaderManager, ShaderCompiledModel>(parent)
{
    init(shaderManager, std::string(titleShaderCompiled));
    AddDirNavigationPanel(m_mainLayout.get());
}

// Button functions
void ShaderCompiledDisplay::unloadShaderProgram()
{
    QModelIndexList selectedIndices = m_managerView->selectionModel()->selectedIndexes();

    for (const auto& index : selectedIndices)
    {
        QString key = index.data(ShaderCompiledModel::NameRole).toString();
        m_model->unloadShaderProgram(key.toStdString());
    }
}


void ShaderCompiledDisplay::createButtonPanel(QHBoxLayout* parentLayout)
{
    QVBoxLayout* buttonPanel = new QVBoxLayout();
    buttonPanel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    buttonPanel->setSpacing(0);
    buttonPanel->setContentsMargins(0,0,0,0);

    addButtonToPanel(buttonPanel, "Refresh", &ShaderCompiledDisplay::refreshCompiled);
    addButtonToPanel(buttonPanel, "Unload Program", &ShaderCompiledDisplay::unloadShaderProgram);


    parentLayout->addLayout(buttonPanel);
} 

void ShaderCompiledDisplay::refreshCompiled()
{
    m_model->refreshCompiledView();
}


void ShaderCompiledDisplay::shaderProgramLinked()
{
    refreshCompiled();
}
