#include "TextureDisplay.h"

TextureDisplay::TextureDisplay(gfx::TextureManager* textureManager, QWidget* parent)
    : QWidget(parent)
{
    m_mainLayout = std::make_unique<QVBoxLayout>(this);
    
    m_mainLayout->setAlignment(Qt::AlignLeft);

    createTitle(m_mainLayout.get());

    createListViewWithControls(textureManager, m_mainLayout.get());
}

void TextureDisplay::createTitle(QLayout* parentLayout)
{
    QLabel* title = new QLabel(constTitle.data());

    title->setAlignment(Qt::AlignCenter);

    QFont font = title->font();
    font.setPointSize(constTitleFontSize);
    title->setFont(font);
    
    parentLayout->addWidget(title);
}

void TextureDisplay::createListViewWithControls(gfx::TextureManager* textureManager, QVBoxLayout* parentLayout)
{
    QVBoxLayout* layout = new QVBoxLayout();

    m_managerView = std::make_unique<QListView>(this);
    m_model = std::make_unique<TextureModel>(textureManager, this);

    m_managerView->setModel(m_model.get());
    m_managerView->setMouseTracking(true);
    m_managerView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    layout->addWidget(m_managerView.get(), 1);

    addCurrDirectoryDisplay(layout);
    addChangeDirectoryButton(layout);

    QHBoxLayout* viewWithButtonPanel = new QHBoxLayout();
    viewWithButtonPanel->addLayout(layout);

    createButtonPanel(viewWithButtonPanel);

    parentLayout->addLayout(viewWithButtonPanel);
}

void TextureDisplay::addCurrDirectoryDisplay(QVBoxLayout* parentLayout)
{
    QHBoxLayout* layout = new QHBoxLayout();

    m_currentDirectory = QString::fromStdString(m_model->getCurrentTextureDirectory().string());

    QLabel* titleLabel = new QLabel("Active directory: ");
    m_directoryDisplayLabel = std::make_unique<QLabel>(m_currentDirectory); 

    layout->addWidget(titleLabel);
    layout->addWidget(m_directoryDisplayLabel.get());

    layout->setSpacing(constSpacing);
    layout->addStretch(1);

    parentLayout->addLayout(layout);
}

void TextureDisplay::addChangeDirectoryButton(QVBoxLayout* parentLayout)
{
    QHBoxLayout* buttonLayout = new QHBoxLayout(); 

    addButtonToPanel(buttonLayout, "Change active directory", &TextureDisplay::changeDirectoryPressed);
    addButtonToPanel(buttonLayout, "Open file explorer", &TextureDisplay::openExplorerPressed);

    parentLayout->addLayout(buttonLayout);
}


void TextureDisplay::setButtonColours(QWidget* widget)
{
    QPalette palette = widget->palette();

    palette.setColor(QPalette::Window, backgroundColour);
    palette.setColor(QPalette::Base, backgroundColour);
    palette.setColor(QPalette::Button, buttonColour);

    widget->setPalette(palette);
    widget->setAutoFillBackground(true);
}



template<typename FuncType>
void TextureDisplay::addButtonToPanel(QLayout* layout, QString label, FuncType function)
{
    QPushButton* button = new QPushButton(label);
    setButtonColours(button);
    button->setText(label);
    connect(button, &QPushButton::clicked, this, function);
    layout->addWidget(button);
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

void TextureDisplay::refreshPressed()
{
    m_model->refreshTextures();
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

void TextureDisplay::changeDirectoryPressed()
{
    std::filesystem::path currFolder = m_model->getCurrentTextureDirectory();

    QString directory = QFileDialog::getExistingDirectory(this, "New Texture Directory", QString::fromStdString(currFolder.string()));

    if (directory.isEmpty())
    {
        return;
    }

    m_model->updateTexturePath(directory.toStdString());

    if (currFolder.string() != directory.toStdString())
    {
        m_currentDirectory = directory;
        m_directoryDisplayLabel.get()->setText(m_currentDirectory);
    }
}

void TextureDisplay::openExplorerPressed()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_currentDirectory));
}