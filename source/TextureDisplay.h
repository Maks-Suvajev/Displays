#ifndef TEXTURE_DISPLAY_H
#define TEXTURE_DISPLAY_H

#include <QVBoxLayout>



#include <QPushbutton>
#include <QList>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QDesktopServices>

#include "Display.h"
#include "TextureModel.h"
#include "TextureManager.h"

constexpr std::string_view titleTextureDisplay =  "Texture Loader";

class TextureDisplay : public Display<gfx::TextureManager, TextureModel>
{
    Q_OBJECT

    public:
        explicit TextureDisplay(gfx::TextureManager* textureManager, QWidget* parent = nullptr);

    private:
        // Texture specific button control functions
        void loadTexturePressed();
        void loadAllTexturesPressed();
        void unloadTexturePressed();
        void unloadAllTexturesPressed();

        // Texture specific layout
        void createButtonPanel(QHBoxLayout* parentLayout) override;

};


#endif