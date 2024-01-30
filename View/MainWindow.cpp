#include "MainWindow.h"
#include "../Core/Json/Reader.h"
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QSplitter>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStackedWidget>
#include <QScrollArea>
#include <QVBoxLayout>

namespace View
{
    MainWindow::MainWindow(std::vector<Core::Sensor*>& vector, Core::Json::DataMapper::JsonFile& json_file, QWidget *parent)
    : QMainWindow(parent), has_unsaved_changes(false), vector(vector), json_file(json_file)
    {
        // Actions
        QAction* create = new QAction(
            QIcon(QPixmap((":/Assets/add.png"))),
            "New"
        );
        create->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
        QAction* open = new QAction(
            QIcon(QPixmap((":/Assets/open.png"))),
            "Open"
        );
        open->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
        QAction* save = new QAction(
            QIcon(QPixmap((":/assets/save.png"))),
            "Save"
        );
        save->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
        QAction* save_as = new QAction(
            QIcon(QPixmap((":/Assets/save_as.png"))),
            "Save As"
        );
        save_as->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
        QAction* close = new QAction(
            QIcon(QPixmap((":/Assets/close.png"))),
            "Close"
        );
        close->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
        QAction* togge_toolbar = new QAction(
            "Toolbar"
        );
        create_item = new QAction(
            QIcon(QPixmap((":/Asset/new_item.png"))),
            "New Item"
        );
        create_item->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_N));
        create_item->setEnabled(false);

        // Sets menu bar
        QMenu* file = menuBar()->addMenu("&File");
        file->addAction(create);
        file->addAction(open);
        file->addAction(save);
        file->addAction(save_as);
        file->addSeparator();
        file->addAction(close);
        QMenu* item_menu = menuBar()->addMenu("&Item");
        item_menu->addAction(create_item);
        QMenu* view = menuBar()->addMenu("&View");
        view->addAction(togge_toolbar);

        // Sets toolbar
        toolbar = addToolBar("Toolbar");
        toolbar->addAction(create);
        toolbar->addAction(open);
        toolbar->addAction(save);
        toolbar->addAction(save_as);
        toolbar->addSeparator();
        toolbar->addAction(create_item);
        toolbar->addSeparator();
        toolbar->addAction(close);

        std::cout << "Prima di splitter" << std::endl;

        QSplitter* splitter = new QSplitter(this);
        setCentralWidget(splitter);

        std::cout << "Creato Splitter" << std::endl;

        QWidget* widget = new QWidget(this);
        splitter->addWidget(widget);

        std::cout << "Aggiunto widget a sinistra" << std::endl;

        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        widget->setLayout(layout);

        std::cout << "Layout widget a sinistra" << std::endl;

        search = new Search();
        layout->addWidget(search);

        std::cout << "Aggiunto search" << std::endl;

        left_stacked_widget = new QStackedWidget();
        layout->addWidget(left_stacked_widget);

        std::cout << "Parte sinistra" << std::endl;

        results = new Results(vector);
        left_stacked_widget->addWidget(results);

        right_stacked_widget = new QStackedWidget();
        splitter->addWidget(right_stacked_widget);

        QWidget* place_holder = new QWidget();
        right_stacked_widget->addWidget(place_holder);

        std::cout << "Parte destra" << std::endl;

        splitter->setSizes(QList<int>() << 1000 << 3000);

        // Connects signals
        connect(create, &QAction::triggered, this, &MainWindow::newDataset);
        connect(open, &QAction::triggered, this, &MainWindow::openDataset);
        connect(save, &QAction::triggered, this, &MainWindow::saveDataset);
        connect(save_as, &QAction::triggered, this, &MainWindow::saveAsDataset);
        connect(close, &QAction::triggered, this, &MainWindow::close);
        connect(togge_toolbar, &QAction::triggered, this, &MainWindow::toggleToolbar);
        connect(search, &Search::searchSensorId, this, &MainWindow::searchById);
        connect(search, &Search::filterSensor, this, &MainWindow::searchByFilter);
        connect(create_item, &QAction::triggered, this, &MainWindow::createSensor);
        connect(results, &Results::showSensor, this, &MainWindow::showSensor);
        connect(results, &Results::editSensor, this, &MainWindow::editSensor);
        connect(results, &Results::deleteSensor, this, &MainWindow::deleteSensor);

        std::cout << "Collegati tutti i signal-slots" << std::endl;

        // Status bar
        std::cout << "Pronto per le operazioni" << std::endl;
    }

    void MainWindow::reloadData() {
        std::cout << "reloadData" << std::endl;
        clearStack();
        std::cout << "preparazione risultati..." << std::endl;
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        std::cout << "results creato in MainWindow" << std::endl;
        scroll_area->setWidget(results);
        results->showResults(vector);
        std::cout << "Fine showResults" << std::endl;
        left_stacked_widget->addWidget(scroll_area);
        left_stacked_widget->setCurrentIndex(1);
        std::cout << "reloadData avvenuto con successo" << std::endl;
        has_unsaved_changes = true;
    }

    void MainWindow::reloadResults()
    {
        std::cout << "reloadResults:" << std::endl;
        reloadData();
    }

    Search* MainWindow::getSearch() {
        return search;
    }

    void MainWindow::clearStack() 
    {
        std::cout << "Pulizia clearStack destro" << std::endl;
        QWidget* right_widget = right_stacked_widget->widget(1);
        while (right_widget) {
            std::cout << "Pulizia stack destro" << std::endl;
            right_stacked_widget->removeWidget(right_widget);
            delete right_widget;
            right_widget = right_stacked_widget->widget(1);
        }

        std::cout << "Pulizia clearStack sinistro" << std::endl;
        QWidget* left_widget = left_stacked_widget->widget(1);
        while (left_widget) {
            std::cout << "Pulizia stack sinistro" << std::endl;
            left_stacked_widget->removeWidget(left_widget);
            delete left_widget;
            left_widget = left_stacked_widget->widget(1);
        }
    }


    void MainWindow::newDataset() {
        QString path = QFileDialog::getSaveFileName(
            this,
            "Creates new Dataset",
            "./",
            "JSON files *.json"
        );
        if (path.isEmpty()) {
            return;
        }
        dynamic_cast<Core::Json::Reader&>(const_cast<Core::Json::IReader&>(json_file.getConverter().getReader())).clear();
        json_file.setPath(path.toStdString());
        vector = json_file.load();
        // deploy();
        create_item->setEnabled(true);
        reloadData();
        
        std::cout << "Nuovo Dataset. Dimensione vettore = " << vector.size() << std::endl;
    }

    void MainWindow::openDataset() {
        QString path = QFileDialog::getOpenFileName(
            this,
            "Creates new Dataset",
            "./",
            "JSON files *.json"
        );
        dynamic_cast<Core::Json::Reader&>(const_cast<Core::Json::IReader&>(json_file.getConverter().getReader())).clear();
        json_file.setPath(path.toStdString());
        vector = json_file.load();
        // deploy();
        //reload_item->setEnabled(true);   
        create_item->setEnabled(true);
        std::cout << "Data successfully loaded from " << path.toStdString() << "." << std::endl;
        reloadData();
    }

     void MainWindow::saveDataset() {
        if(json_file.getPath() == "")
        {
            return;
        }
        json_file.store(vector);
        has_unsaved_changes = false;
        std::cout << "Dataset saved." << std::endl;
    }

    void MainWindow::saveAsDataset() {
        QString path = QFileDialog::getSaveFileName(
            this,
            "Creates new Dataset",
            "./",
            "JSON files *.json"
        );
        if (json_file.getPath() == "")
        {
            return;
        }
        json_file.setPath(path.toStdString()).store(vector);
        has_unsaved_changes = false;
        std::cout << "Dataset saved as \"" << path.toStdString() << "\"." << std::endl;
    }

    void MainWindow::toggleToolbar() 
    {
        toolbar->setVisible(!toolbar->isVisible());
        std::cout << "Toolbar rimossa" << std::endl;
    }

    

    void MainWindow::searchById(unsigned int id) 
    {
        clearStack();
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        scroll_area->setWidget(results);
        left_stacked_widget->addWidget(scroll_area);
        left_stacked_widget->setCurrentIndex(1);
        results->showResultsById(id);
        has_unsaved_changes = true;
    }

    void MainWindow::searchByFilter(std::string filter)
    {
        //results riceve segnale e viene aggiornato.
        // setta results

        clearStack();
    }

    void MainWindow::createSensor() 
    {
        std::cout << "Inizio createSensor" << std::endl;
        clearStack();
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        std::cout << "Prima di Editor" << std::endl;
        Editor* editor = new Editor(vector, nullptr);
        std::cout << "Dopo Editor" << std::endl;
        scroll_area->setWidget(editor);
        right_stacked_widget->addWidget(scroll_area);
        right_stacked_widget->setCurrentIndex(1);
        has_unsaved_changes = true;
        std::cout << "Creating a new item." << std::endl;
        connect(editor, &Editor::save, this, &MainWindow::reloadResults);
    }

    void MainWindow::showSensor(Core::Sensor* sensor) {
        clearStack();
        Viewer* viewer_wiget = new Viewer(vector, *sensor);
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        scroll_area->setWidget(viewer_wiget);
        right_stacked_widget->addWidget(scroll_area);
        right_stacked_widget->setCurrentIndex(1);
        std::cout << "Showing sensor " + QString::number(sensor->getId()).toStdString() << std::endl;
    }

    void MainWindow::editSensor(Core::Sensor* sensor) {
        std::cout << "editSensor" << std::endl;
        clearStack();
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        Editor* editor = new Editor(vector, sensor);
        std::cout << "Creato editor per editSensor" << std::endl;
        scroll_area->setWidget(editor);
        right_stacked_widget->addWidget(scroll_area);
        right_stacked_widget->setCurrentIndex(1);
        has_unsaved_changes = true;
        std::cout << "Editing sensor " << QString::fromStdString(sensor->getName()).toStdString() << "." << std::endl;
        connect(editor, &Editor::save, this, &MainWindow::reloadResults);
    }

    void MainWindow::deleteSensor(Core::Sensor* sensor) {
        std::cout << "Sensor " << QString::fromStdString(sensor->getName()).toStdString() << " removed." << std::endl;
        std::vector<Core::Sensor*>::iterator it = vector.begin();
        while(*it != sensor || it != vector.end())
        {
            ++it;
        }
        if(it != vector.end())
        {
            vector.erase(it);
            delete sensor;
        }
        else
        {
            return;
        }
        // Chiamata per aggiornare la lista
        results->showResults(vector);
        std::cout << "lista aggiornata dopo deleteSensor" << std::endl;
        has_unsaved_changes = true;
    }

    void MainWindow::close() {
        if (has_unsaved_changes) {
            QMessageBox::StandardButton exit_message;
            exit_message = QMessageBox::question(
                this,
                "Quit?",
                "There are unsaved changes.\nDo you really want to quit?",
                QMessageBox::Yes | QMessageBox::No
            );
            if (exit_message == QMessageBox::Yes) {
                QApplication::quit();
            }
        }
        else {
            QApplication::quit();
        }
    }

}