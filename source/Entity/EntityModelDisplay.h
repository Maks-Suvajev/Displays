#ifndef ENTITY_MODEL_DISPLAY_H
#define ENTITY_MODEL_DISPLAY_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QTreeView>
#include <QPushbutton>
#include <QLineEdit>
#include <QFileDialog>
#include <QDesktopServices>

#include "UIColours.h"

#include "EntityModel.h"
#include "EntityManager.h"

namespace gui
{

constexpr std::string_view titleEntityModelDisplay =  "Entity Component View";

class EntityModelDisplay : public QWidget
{
    public:
        explicit EntityModelDisplay(EntityManager* entityManager, QWidget* parent = nullptr);
        ~EntityModelDisplay() = default;

        void init(EntityManager* manager, const std::string& title);

    protected:
        // Generic button control functions
        void refreshPressed();

        // Interface creation
        void createTitle(std::string title, QLayout* parentLayout);
        void createTreeViewWithControls(EntityManager* entityManager, QVBoxLayout* parentLayout);

        EntityModel* getModel();

        void createButtonPanel(QHBoxLayout* parentLayout);
        void setButtonColours(QWidget* widget);

        template<typename FuncType>
        void addButtonToPanel(QLayout* layout, QString label, FuncType function);

        std::unique_ptr<QVBoxLayout>    m_mainLayout; // Main connector layout
        std::unique_ptr<QTreeView>      m_managerView;
        std::unique_ptr<EntityModel>    m_model;
};

}

#endif