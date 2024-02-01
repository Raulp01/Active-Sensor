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

        std::cout << "MainWindow::MainWindow Prima di splitter" << std::endl;

        QSplitter* splitter = new QSplitter(this);
        setCentralWidget(splitter);

        std::cout << "MainWindow::MainWindow Creato Splitter" << std::endl;

        QWidget* widget = new QWidget(this);
        splitter->addWidget(widget);

        std::cout << "MainWindow::MainWindow Aggiunto widget a sinistra" << std::endl;

        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        widget->setLayout(layout);

        std::cout << "MainWindow::MainWindow Layout widget a sinistra" << std::endl;

        search = new Search();
        layout->addWidget(search);

        std::cout << "MainWindow::MainWindow Aggiunto search" << std::endl;

        left_stacked_widget = new QStackedWidget();
        layout->addWidget(left_stacked_widget);

        std::cout << "MainWindow::MainWindow Parte sinistra" << std::endl;

        results = new Results(vector, left_stacked_widget);
        left_stacked_widget->addWidget(results);

        right_stacked_widget = new QStackedWidget();
        splitter->addWidget(right_stacked_widget);

        std::cout << "MainWindow::MainWindow Parte destra" << std::endl;

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

        std::cout << "MainWindow::MainWindow Collegati tutti i signal-slots" << std::endl;

        // Status bar
        std::cout << "MainWindow::MainWindow Pronto per le operazioni" << std::endl;
    }

    void MainWindow::reloadData() {
        std::cout << "MainWindow::reloadData" << std::endl;
        clearStack();
        std::cout << "MainWindow::reloadData preparazione risultati..." << std::endl;
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        std::cout << "MainWindow::reloadData results creato in MainWindow" << std::endl;
        scroll_area->setWidget(results);
        results->showResults(vector);
        std::cout << "MainWindow::reloadData Fine showResults" << std::endl;
        left_stacked_widget->addWidget(scroll_area);
        left_stacked_widget->setCurrentIndex(1);
        right_stacked_widget->setCurrentIndex(0);
        std::cout << "MainWindow::reloadData reloadData avvenuto con successo" << std::endl;
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
        std::cout << "MainWindow::clearStack Pulizia clearStack destro" << std::endl;
        QWidget* right_widget = right_stacked_widget->widget(1);
        while (right_widget) {
            std::cout << "MainWindow::clearStackPulizia stack destro" << std::endl;
            right_stacked_widget->removeWidget(right_widget);
            delete right_widget;
            right_widget = right_stacked_widget->widget(1);
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
        
        std::cout << "MainWindow::newDataset Nuovo Dataset. Dimensione vettore = " << vector.size() << std::endl;
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
        std::cout << "MainWindow::openDataset Data successfully loaded from " << path.toStdString() << "." << std::endl;
        reloadData();
    }

     void MainWindow::saveDataset() {
        if(json_file.getPath() == "")
        {
            return;
        }
        json_file.store(vector);
        has_unsaved_changes = false;
        std::cout << "MainWindow::saveDataset Dataset saved." << std::endl;
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
        std::cout << "MainWindow::saveAsDataset saved as \"" << path.toStdString() << "\"." << std::endl;
    }

    void MainWindow::toggleToolbar() 
    {
        toolbar->setVisible(!toolbar->isVisible());
        std::cout << "MainWindow::toggleToolbar rimossa" << std::endl;
    }

    

    void MainWindow::searchById(unsigned int id) 
    {
        std::cout << "MainWindow::searchById" << std::endl;
        clearStack();
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        scroll_area->setWidget(results);
        std::cout << "MainWindow::searchById settato il widget in scroll_area" << std::endl;
        results->showResultsById(id);
        std::cout << "MainWindow::searchById fine showResultsById (Results)" << std::endl;
        left_stacked_widget->addWidget(scroll_area);
        left_stacked_widget->setCurrentIndex(1);
        right_stacked_widget->setCurrentIndex(0);
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
        std::cout << "MainWindow::createSensor Inizio createSensor" << std::endl;
        clearStack();
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        std::cout << "MainWindow::createSensor Prima di Editor" << std::endl;
        Editor* editor = new Editor(vector, nullptr);
        std::cout << "MainWindow::createSensor Dopo Editor" << std::endl;
        scroll_area->setWidget(editor);
        right_stacked_widget->addWidget(scroll_area);
        right_stacked_widget->setCurrentIndex(1);
        has_unsaved_changes = true;
        std::cout << "MainWindow::createSensor Creating a new item." << std::endl;
        connect(editor, &Editor::save, this, &MainWindow::reloadResults);
    }

    void MainWindow::showSensor(Core::Sensor* sensor) {
        clearStack();
        std::cout << "MainWindow::showSensor" << std::endl;
        Viewer* viewer_wiget = new Viewer(vector, *sensor);
        std::cout << "MainWindow::showSensor Viewer creato" << std::endl;
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        scroll_area->setWidget(viewer_wiget);
        std::cout << "MainWindow::showSensor Settato widget in scroll_area" << std::endl;
        right_stacked_widget->addWidget(scroll_area);
        right_stacked_widget->setCurrentIndex(1);
        connect(viewer_wiget, &Viewer::showViewer, this, &MainWindow::showSensor);
        std::cout << "MainWindow::showSensor Showing sensor " + QString::number(sensor->getId()).toStdString() << std::endl;
    }

    void MainWindow::editSensor(Core::Sensor* sensor) {
        std::cout << "MainWindow::editSensor" << std::endl;
        clearStack();
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        Editor* editor = new Editor(vector, sensor);
        std::cout << "MainWindow::editSensor Creato editor per editSensor" << std::endl;
        scroll_area->setWidget(editor);
        right_stacked_widget->addWidget(scroll_area);
        right_stacked_widget->setCurrentIndex(1);
        has_unsaved_changes = true;
        std::cout << "MainWindow::editSensor Editing sensor " << QString::fromStdString(sensor->getName()).toStdString() << "." << std::endl;
        connect(editor, &Editor::save, this, &MainWindow::reloadResults);
    }

    void MainWindow::deleteSensor(Core::Sensor* sensor) {
        std::cout << "MainWindow::deleteSensor" << std::endl;
        auto it = vector.begin();
        while(it != vector.end() && *it != sensor)
        {
            std::cout << "MainWindow::deleteSensor nel ciclo while" << std::endl;
            it++;
        }
        if(it != vector.end())
        {
            Core::Sensor* hold = *it;
            vector.erase(it);
            delete hold;
            std::cout << "MainWindow::deleteSensor " << QString::fromStdString(sensor->getName()).toStdString() << " removed." << std::endl;
        }
        else
        {
            std::cout << "MainWindow::deleteSensor nessun sensore trovato" << std::endl;
        }
        std::cout << "MainWindow::deleteSensor lista aggiornata dopo deleteSensor. Dim = " << vector.size() << std::endl;
        // Chiamata per aggiornare la lista
        reloadData();
        std::cout << "MainWindow::deleteSensro reloadData avvenuto" << std::endl;
        has_unsaved_changes = true;
    }

    void MainWindow::close() {
        if (has_unsaved_changes) {
            QMessageBox::StandardButton exit_message;
            exit_message = QMessageBox::question(
                this,
                "Quit?",
                "There are unsaved changes.\nUnsaved data will be lost.\nDo you really want to quit?",
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