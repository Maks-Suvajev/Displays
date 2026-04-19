#ifndef SCENE_MODEL_DISPLAY_H
#define SCENE_MODEL_DISPLAY_H

#include <QVBoxLayout>

#include <QPushbutton>
#include <QList>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QDesktopServices>
#include <QOpenGLWidget>

#include "Display.h"
#include "SceneModelModel.h"
#include "SceneModelManager.h"


namespace gui
{

constexpr std::string_view titleSceneModelDisplay =  "Model Loader";

class SceneModelDisplay : public Display<gfx::SceneModelManager, SceneModelModel>
{
    Q_OBJECT

    public:
        explicit SceneModelDisplay(gfx::SceneModelManager* sceneModelManager, QOpenGLWidget* viewport, QWidget* parent = nullptr);

    private:
        QOpenGLWidget* m_viewport;

        // Buttons
        void loadModelPressed();


        void createButtonPanel(QHBoxLayout* parentLayout) override;

};
}

#endif