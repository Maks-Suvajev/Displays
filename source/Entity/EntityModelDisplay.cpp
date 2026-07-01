#include "EntityModelDisplay.h"

namespace gui
{

EntityModelDisplay::EntityModelDisplay(EntityManager* entityManager, QWidget* parent)
    : QWidget(parent)
{
    init(entityManager, std::string(titleEntityModelDisplay));
}

void EntityModelDisplay::init(EntityManager* manager, const std::string& title)
{
    m_mainLayout = std::make_unique<QVBoxLayout>(this);
    
    m_mainLayout->setAlignment(Qt::AlignLeft);

    createTitle(title, m_mainLayout.get());

    createTreeViewWithControls(manager, m_mainLayout.get());
}

void EntityModelDisplay::createTitle(std::string title, QLayout* parentLayout)
{
    QLabel* titleLabel = new QLabel(QString::fromStdString(title));

    titleLabel->setAlignment(Qt::AlignCenter);

    QFont font = titleLabel->font();
    font.setPointSize(constTitleFontSize);
    titleLabel->setFont(font);
    
    parentLayout->addWidget(titleLabel);
}

void EntityModelDisplay::createTreeViewWithControls(EntityManager* entityManager, QVBoxLayout* parentLayout)
{
    QVBoxLayout* layout = new QVBoxLayout();

    m_managerView = std::make_unique<QTreeView>(this);
    m_model = std::make_unique<EntityModel>(entityManager, nullptr);

    m_managerView->setModel(m_model.get());
    m_managerView->setMouseTracking(true);
    m_managerView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_managerView->setHeaderHidden(true);

    layout->addWidget(m_managerView.get(), 1);

    QHBoxLayout* viewWithButtonPanel = new QHBoxLayout();
    viewWithButtonPanel->addLayout(layout);

    createButtonPanel(viewWithButtonPanel);

    parentLayout->addLayout(viewWithButtonPanel);
}


void EntityModelDisplay::createButtonPanel(QHBoxLayout* parentLayout)
{
    QVBoxLayout* buttonPanel = new QVBoxLayout();
    buttonPanel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    buttonPanel->setSpacing(0);
    buttonPanel->setContentsMargins(0,0,0,0);

    addButtonToPanel(buttonPanel, "Refresh", &EntityModelDisplay::refreshPressed);

    parentLayout->addLayout(buttonPanel);
}

void EntityModelDisplay::refreshPressed()
{
    m_model->refreshElements();
}

template<typename FuncType>
void EntityModelDisplay::addButtonToPanel(QLayout* layout, QString label, FuncType function)
{
    QPushButton* button = new QPushButton(label);
    setButtonColours(button);
    button->setText(label);
    connect(button, &QPushButton::clicked, this, function);
    layout->addWidget(button);
}

void EntityModelDisplay::setButtonColours(QWidget* widget)
{
    QPalette palette = widget->palette();

    palette.setColor(QPalette::Window, backgroundColour);
    palette.setColor(QPalette::Base, backgroundColour);
    palette.setColor(QPalette::Button, buttonColour);

    widget->setPalette(palette);
    widget->setAutoFillBackground(true);
}


}