#include "SceneModelDisplay.h"

namespace gui
{

SceneModelDisplay::SceneModelDisplay(gfx::SceneModelManager* sceneModelManager, QOpenGLWidget* viewport, QWidget* parent)
    : m_viewport(viewport)
{
    init(sceneModelManager, std::string(titleSceneModelDisplay));
    AddDirNavigationPanel(m_mainLayout.get());
}

void SceneModelDisplay::createButtonPanel(QHBoxLayout* parentLayout)
{
    QVBoxLayout* buttonPanel = new QVBoxLayout();
    buttonPanel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    buttonPanel->setSpacing(0);
    buttonPanel->setContentsMargins(0,0,0,0);

    addButtonToPanel(buttonPanel, "Load", &SceneModelDisplay::loadModelPressed);

    parentLayout->addLayout(buttonPanel);
}

void SceneModelDisplay::loadModelPressed()
{
    QModelIndexList selectedIndices = m_managerView->selectionModel()->selectedIndexes();

    m_viewport->makeCurrent();

    for (const auto& index : selectedIndices)
    {
        QString key = index.data(SceneModelModel::FilePathRole).toString();
        m_model->loadModel(key.toStdString());
        emit m_model->dataChanged(index, index);
    }

    m_viewport->doneCurrent();
}

}