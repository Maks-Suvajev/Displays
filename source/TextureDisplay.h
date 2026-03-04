#ifndef TEXTURE_DISPLAY_H
#define TEXTURE_DISPLAY_H

#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushbutton>
#include <QList>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QDesktopServices>

#include "TextureModel.h"
#include "TextureManager.h"
#include "UIColours.h"

static constexpr std::string_view constTitle =  "Texture Loader";
static constexpr int constTitleFontSize =  15;
static constexpr int constSpacing =  15;


class TextureDisplay : public QWidget
{
    Q_OBJECT

    public:
        explicit TextureDisplay(gfx::TextureManager* textureManager, QWidget* parent = nullptr);

    private:

        // Button control functions
        void refreshPressed();
        void loadTexturePressed();
        void loadAllTexturesPressed();
        void unloadTexturePressed();
        void unloadAllTexturesPressed();
        void changeDirectoryPressed();
        void openExplorerPressed();

        void createTitle(QLayout* parentLayout);
        void createListViewWithControls(gfx::TextureManager* textureManager, QVBoxLayout* parentLayout);
        void addCurrDirectoryDisplay(QVBoxLayout* parentLayout);
        void addChangeDirectoryButton(QVBoxLayout* parentLayout);
        void createButtonPanel(QHBoxLayout* parentLayout);

        template<typename FuncType>
        void addButtonToPanel(QLayout* layout, QString label, FuncType function);

        void setButtonColours(QWidget* widget);

        std::unique_ptr<QLabel>         m_directoryDisplayLabel;
        QString                         m_currentDirectory;
        std::unique_ptr<QVBoxLayout>    m_mainLayout; // Main connector layout
        std::unique_ptr<QListView>      m_managerView;
        std::unique_ptr<QLabel>         m_detailsLabel; // Hovering data on list member
        std::unique_ptr<TextureModel>   m_model;

};


#endif