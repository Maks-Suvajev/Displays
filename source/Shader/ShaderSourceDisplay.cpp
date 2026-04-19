#include "ShaderSourceDisplay.h"

namespace gui
{

ShaderSourceDisplay::ShaderSourceDisplay(gfx::ShaderManager* shaderManager, QWidget* parent)
    : Display<gfx::ShaderManager, ShaderSourceModel>(parent)
{
    init(shaderManager, std::string(titleShaderSource));
}

void ShaderSourceDisplay::createButtonPanel(QHBoxLayout* parentLayout)
{
    QVBoxLayout* buttonPanel = new QVBoxLayout();
    buttonPanel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    buttonPanel->setSpacing(0);
    buttonPanel->setContentsMargins(0,0,0,0);

    addButtonToPanel(buttonPanel, "Refresh", &ShaderSourceDisplay::refreshPressed);
    addButtonToPanel(buttonPanel, "Compile Source", &ShaderSourceDisplay::compileSource);
    addButtonToPanel(buttonPanel, "Compile All Sources", &ShaderSourceDisplay::compileAllSources);
    addButtonToPanel(buttonPanel, "Unload Shader", &ShaderSourceDisplay::unloadShader);
    addButtonToPanel(buttonPanel, "Unload All Shaders", &ShaderSourceDisplay::unloadAllShaders);

    addButtonToPanelWithTextInput(buttonPanel, "Build Program", [this](QString text){
        linkIntoProgram(text.toStdString());
    });

    parentLayout->addLayout(buttonPanel);
}


void ShaderSourceDisplay::compileSource()
{
    QModelIndexList selectedIndices = m_managerView->selectionModel()->selectedIndexes();

    for (const auto& index : selectedIndices)
    {
        QString key = index.data(ShaderSourceModel::FilePathRole).toString();

        std::cout << key.toStdString() << std::endl;
        m_model->compileSource(key.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void ShaderSourceDisplay::compileAllSources()
{
    for (int i = 0; i < m_managerView->model()->rowCount(); ++i) // Not sure if there's better way to iterate..
    {
        QModelIndex index = m_managerView->model()->index(i, 0);

        QString key = index.data(ShaderSourceModel::FilePathRole).toString();
        m_model->compileSource(key.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void ShaderSourceDisplay::unloadShader()
{
    QModelIndexList selectedIndices = m_managerView->selectionModel()->selectedIndexes();

    for (const auto& index : selectedIndices)
    {
        QString key = index.data(ShaderSourceModel::FilePathRole).toString();

        m_model->unloadShader(key.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void ShaderSourceDisplay::unloadAllShaders()
{
    for (int i = 0; i < m_managerView->model()->rowCount(); ++i) // Not sure if there's better way to iterate..
    {
        QModelIndex index = m_managerView->model()->index(i, 0);

        QString key = index.data(ShaderSourceModel::FilePathRole).toString();
        m_model->unloadShader(key.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void ShaderSourceDisplay::linkIntoProgram(const std::string& name)
{
    QModelIndexList selectedIndices = m_managerView->selectionModel()->selectedIndexes();

    if (selectedIndices.length() != 2)
    {
        return;
    }

    QString keyA = selectedIndices[0].data(ShaderSourceModel::FilePathRole).toString();
    QString keyB = selectedIndices[1].data(ShaderSourceModel::FilePathRole).toString();

    m_model->linkIntoProgram(keyA.toStdString(), keyB.toStdString(), name);
    emit m_model->dataChanged(selectedIndices[0], selectedIndices[0]);
    emit m_model->dataChanged(selectedIndices[1], selectedIndices[1]);
    emit shaderProgramLinked();
}

}