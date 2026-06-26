#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QListView>
#include <QPushbutton>
#include <QLineEdit>
#include <QFileDialog>
#include <QDesktopServices>

#include "UIColours.h"

namespace gui
{

template<typename Tmanager, typename Tmodel>
class Display : public QWidget
{
    public:
        explicit Display(QWidget* parent = nullptr);
        virtual ~Display() = default;

        void init(Tmanager* manager, std::string title);

    protected:
        // Generic button control functions
        void refreshPressed();
        void changeDirectoryPressed();
        void openExplorerPressed();

        // Interface creation
        void createTitle(std::string title, QLayout* parentLayout);
        void createListViewWithControls(Tmanager* manager, QVBoxLayout* parentLayout);

        void addCurrDirectoryDisplay(QVBoxLayout* parentLayout);
        void addChangeDirectoryButton(QVBoxLayout* parentLayout);
        void AddDirNavigationPanel(QLayout* parentLayout);

        Tmodel* getModel();

        virtual void createButtonPanel(QHBoxLayout* parentLayout) = 0;

        template<typename FuncType>
        void addButtonToPanel(QLayout* layout, QString label, FuncType function);

        template<typename FuncType>
        void addButtonToPanelWithTextInput(QLayout* layout, QString label, FuncType function);

        // Styling (TODO: Replace with QSS)
        void setButtonColours(QWidget* widget);

        std::unique_ptr<QLabel>         m_directoryDisplayLabel;
        QString                         m_currentDirectory;
        std::unique_ptr<QVBoxLayout>    m_mainLayout; // Main connector layout
        std::unique_ptr<QListView>      m_managerView;
        std::unique_ptr<Tmodel>         m_model;
};

template<typename Tmanager, typename Tmodel>
Tmodel* Display<Tmanager, Tmodel>::getModel()
{
    return m_model.get();
}

template<typename Tmanager, typename Tmodel>
Display<Tmanager, Tmodel>::Display(QWidget* parent)
    : QWidget(parent)
{
}

template<typename Tmanager, typename Tmodel>
void Display<Tmanager, Tmodel>::init(Tmanager* manager, std::string title)
{
    m_mainLayout = std::make_unique<QVBoxLayout>(this);
    
    m_mainLayout->setAlignment(Qt::AlignLeft);

    createTitle(title, m_mainLayout.get());

    createListViewWithControls(manager, m_mainLayout.get());
}

template<typename Tmanager, typename Tmodel>
void Display<Tmanager, Tmodel>::createTitle(std::string title, QLayout* parentLayout)
{
    QLabel* titleLabel = new QLabel(QString::fromStdString(title));

    titleLabel->setAlignment(Qt::AlignCenter);

    QFont font = titleLabel->font();
    font.setPointSize(constTitleFontSize);
    titleLabel->setFont(font);
    
    parentLayout->addWidget(titleLabel);
}

template<typename Tmanager, typename Tmodel>
void Display<Tmanager, Tmodel>::createListViewWithControls(Tmanager* manager, QVBoxLayout* parentLayout)
{
    QVBoxLayout* layout = new QVBoxLayout();

    m_managerView = std::make_unique<QListView>(this);
    m_model = std::make_unique<Tmodel>(manager, nullptr);

    m_managerView->setModel(m_model.get());
    m_managerView->setMouseTracking(true);
    m_managerView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    layout->addWidget(m_managerView.get(), 1);

    QHBoxLayout* viewWithButtonPanel = new QHBoxLayout();
    viewWithButtonPanel->addLayout(layout);

    createButtonPanel(viewWithButtonPanel);

    parentLayout->addLayout(viewWithButtonPanel);
}

template<typename Tmanager, typename Tmodel>
void Display<Tmanager, Tmodel>::AddDirNavigationPanel(QLayout* parentLayout)
{
    QWidget* container = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    container->setLayout(layout);

    addCurrDirectoryDisplay(layout);
    addChangeDirectoryButton(layout);

    parentLayout->addWidget(container);
}


template<typename Tmanager, typename Tmodel>
void Display<Tmanager, Tmodel>::addCurrDirectoryDisplay(QVBoxLayout* parentLayout)
{
    QHBoxLayout* layout = new QHBoxLayout();

    m_currentDirectory = QString::fromStdString(m_model->getActiveDirectory());

    QLabel* titleLabel = new QLabel("Active directory: ");
    m_directoryDisplayLabel = std::make_unique<QLabel>(m_currentDirectory); 

    layout->addWidget(titleLabel);
    layout->addWidget(m_directoryDisplayLabel.get());

    layout->setSpacing(constSpacing);
    layout->addStretch(1);

    parentLayout->addLayout(layout);
}

template<typename Tmanager, typename Tmodel>
void Display<Tmanager, Tmodel>::addChangeDirectoryButton(QVBoxLayout* parentLayout)
{
    QHBoxLayout* buttonLayout = new QHBoxLayout(); 

    addButtonToPanel(buttonLayout, "Change active directory", &Display::changeDirectoryPressed);
    addButtonToPanel(buttonLayout, "Open file explorer", &Display::openExplorerPressed);

    parentLayout->addLayout(buttonLayout);
}

template<typename Tmanager, typename Tmodel>
template<typename FuncType>
void Display<Tmanager, Tmodel>::addButtonToPanel(QLayout* layout, QString label, FuncType function)
{
    QPushButton* button = new QPushButton(label);
    setButtonColours(button);
    button->setText(label);
    connect(button, &QPushButton::clicked, this, function);
    layout->addWidget(button);
}

template<typename Tmanager, typename Tmodel>
template<typename FuncType>
void Display<Tmanager, Tmodel>::addButtonToPanelWithTextInput(QLayout* layout, QString label, FuncType function)
{
    QHBoxLayout* inputLayout = new QHBoxLayout();
    inputLayout->setSpacing(0);
    inputLayout->setContentsMargins(0,0,0,0);

    QPushButton* button = new QPushButton(label);
    setButtonColours(button);
    button->setText(label);

    QLineEdit* nameInput = new QLineEdit();

    inputLayout->addWidget(nameInput, 1);
    inputLayout->addWidget(button, 0);

    connect(button, &QPushButton::clicked, this, [function, nameInput](){
        function(nameInput->text());
        nameInput->clear();
    });

    QWidget* container = new QWidget();
    container->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
    container->setLayout(inputLayout);
        
    layout->addWidget(container);
}

template<typename Tmanager, typename Tmodel>
void Display<Tmanager, Tmodel>::setButtonColours(QWidget* widget)
{
    QPalette palette = widget->palette();

    palette.setColor(QPalette::Window, backgroundColour);
    palette.setColor(QPalette::Base, backgroundColour);
    palette.setColor(QPalette::Button, buttonColour);

    widget->setPalette(palette);
    widget->setAutoFillBackground(true);
}

// Button functionality
template<typename Tmanager, typename Tmodel>
void Display<Tmanager, Tmodel>::refreshPressed()
{
    m_model->refreshElements();
}

template<typename Tmanager, typename Tmodel>
void Display<Tmanager, Tmodel>::changeDirectoryPressed()
{
    std::string currFolder = m_model->getActiveDirectory();

    QString directory = QFileDialog::getExistingDirectory(this, "New Active Directory", QString::fromStdString(currFolder));

    if (directory.isEmpty())
    {
        return;
    }

    m_model->setActiveDirectory(directory.toStdString());

    if (currFolder != directory.toStdString())
    {
        m_currentDirectory = directory;
        m_directoryDisplayLabel.get()->setText(m_currentDirectory);
    }
}

template<typename Tmanager, typename Tmodel>
void Display<Tmanager, Tmodel>::openExplorerPressed()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_currentDirectory));
}

}

#endif