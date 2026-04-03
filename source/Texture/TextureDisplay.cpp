#include "TextureDisplay.h"

TextureDisplay::TextureDisplay(gfx::TextureManager* textureManager, QWidget* parent)
    : Display<gfx::TextureManager, TextureModel>(parent)
{
    init(textureManager, std::string(titleTextureDisplay));
    AddDirNavigationPanel(m_mainLayout.get());
}

void TextureDisplay::createButtonPanel(QHBoxLayout* parentLayout)
{
    QVBoxLayout* buttonPanel = new QVBoxLayout();
    buttonPanel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    buttonPanel->setSpacing(0);
    buttonPanel->setContentsMargins(0,0,0,0);

    addButtonToPanel(buttonPanel, "Refresh", &TextureDisplay::refreshPressed);
    addButtonToPanel(buttonPanel, "Load", &TextureDisplay::loadTexturePressed);
    addButtonToPanel(buttonPanel, "Load All", &TextureDisplay::loadAllTexturesPressed);
    addButtonToPanel(buttonPanel, "Unload", &TextureDisplay::unloadTexturePressed);
    addButtonToPanel(buttonPanel, "Unload All", &TextureDisplay::unloadAllTexturesPressed);

    parentLayout->addLayout(buttonPanel);
}

void TextureDisplay::loadTexturePressed()
{
    QModelIndexList selectedIndices = m_managerView->selectionModel()->selectedIndexes();

    for (const auto& index : selectedIndices)
    {
        QString key = index.data(TextureModel::FilePathRole).toString();
        m_model->loadTexture(key.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void TextureDisplay::loadAllTexturesPressed()
{
    for (int i = 0; i < m_managerView->model()->rowCount(); ++i) // Not sure if there's better way to iterate..
    {
        QModelIndex index = m_managerView->model()->index(i, 0);
        QString key = index.data(TextureModel::FilePathRole).toString();
        m_model->loadTexture(key.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void TextureDisplay::unloadTexturePressed()
{
    QModelIndexList selectedIndices = m_managerView->selectionModel()->selectedIndexes();

    for (const auto& index : selectedIndices)
    {
        QString key = index.data(TextureModel::FilePathRole).toString();
        m_model->unloadTexture(key.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void TextureDisplay::unloadAllTexturesPressed()
{
    for (int i = 0; i < m_managerView->model()->rowCount(); ++i) // Not sure if there's better way to iterate..
    {
        QModelIndex index = m_managerView->model()->index(i, 0);
        QString key = index.data(TextureModel::FilePathRole).toString();
        m_model->unloadTexture(key.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

