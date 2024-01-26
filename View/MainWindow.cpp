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

        // Sets main panel
        QSplitter* splitter = new QSplitter(this);
        setCentralWidget(splitter);

        //Widget che contiene searchbar, lista di widget e pulsante per aggiungere widget
        QWidget* widget = new QWidget();

        std::cout << "Creato il widget nel MainWindow" << std::endl;

        QVBoxLayout* v_layout = new QVBoxLayout();
        //searchbar
        //v_layout->addWidget(searchbar);

        results = new Results(vector);
        v_layout->addWidget(results);

        widget->setLayout(v_layout);

        stacked_widget = new QStackedWidget(this);
        splitter->addWidget(stacked_widget);
        stacked_widget->addWidget(widget);

        /*
        search_widget = new SearchWidget();
        splitter->addWidget(search_widget);
        */

       std::cout << "Finito con lo splitter" << std::endl;

        splitter->setSizes(QList<int>() << 1000 << 3000);

        // Connects signals
        connect(create, &QAction::triggered, this, &MainWindow::newDataset);
        connect(open, &QAction::triggered, this, &MainWindow::openDataset);
        connect(save, &QAction::triggered, this, &MainWindow::saveDataset);
        connect(save_as, &QAction::triggered, this, &MainWindow::saveAsDataset);
        connect(close, &QAction::triggered, this, &MainWindow::close);
        connect(togge_toolbar, &QAction::triggered, this, &MainWindow::toggleToolbar);
        //connect(search_widget, &SearchWidget::search_event, this, &MainWindow::search);
        //connect(results_widget, &ResultsWidget::refreshResults, search_widget, &SearchWidget::search);
        //connect(results_widget, &ResultsWidget::showItem, this, &MainWindow::showItem);
        connect(create_item, &QAction::triggered, this, &MainWindow::createSensor);
        //connect(results_widget, &ResultsWidget::editItem, this, &MainWindow::editItem);
        //connect(results_widget, &ResultsWidget::deleteItem, this, &MainWindow::deleteItem);
        connect(results, &Results::showSensor, this, &MainWindow::showSensor);
        connect(results, &Results::editSensor, this, &MainWindow::editSensor);
        connect(results, &Results::deleteSensor, this, &MainWindow::deleteSensor);

        std::cout << "Collegati tutti i signal-slots" << std::endl;

        // Status bar
        showStatus("Ready.");
    }

    MainWindow& MainWindow::reloadData() {
        clearStack();
        // NO: devo impostare una nuova scrollarea con la scrollbar
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        results = new Results(vector);
        scroll_area->setWidget(results);
        return *this;
        
        /* engine.clear();
        std::vector<Item::AbstractItem*> items(repository->readAll());
        for (
            std::vector<Item::AbstractItem*>::const_iterator it = items.begin();
            it != items.end();
            it++
        ) {
            engine.add(*it);
        }
        return *this; */
    }

    /* SearchWidget* MainWindow::getSearchWidget() {
        return search_widget;
    } */

    void MainWindow::clearStack() {
        QWidget* widget = stacked_widget->widget(1);
        while (widget) {
            stacked_widget->removeWidget(widget);
            delete widget;
            widget = stacked_widget->widget(1);
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
        //reloadData
        
        showStatus("New dataset created.");
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
        showStatus("Data successfully loaded from " + path + ".");
    }

     void MainWindow::saveDataset() {
        if(json_file.getPath() == "")
        {
            return;
        }
        json_file.store(vector);
        has_unsaved_changes = false;
        showStatus("Dataset saved.");
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
        showStatus("Dataset saved as \"" + path + "\".");
    }

    void MainWindow::toggleToolbar() {
        toolbar->setVisible(!toolbar->isVisible());
        showStatus("Toolbar toggled.");
    }

    void MainWindow::showStatus(QString message) {
        statusBar()->showMessage(message);
    }

    /* void MainWindow::search(Engine::Query query) {
        showStatus("Running query for \"" + QString::fromStdString(query.getText()) + "\".");
        results_widget->showResults(query, engine.search(query));
        stacked_widget->setCurrentIndex(0);
        clearStack();
    } */

    void MainWindow::createSensor() {
        std::cout << "Inizio createSensor" << std::endl;
        clearStack();
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        std::cout << "Prima di EditSensor" << std::endl;
        Editor* editor = new Editor(vector, nullptr);
        std::cout << "Dopo Editor" << std::endl;
        scroll_area->setWidget(editor);
        stacked_widget->addWidget(scroll_area);
        stacked_widget->setCurrentIndex(1);
        has_unsaved_changes = true;
        showStatus("Creating a new item.");
        connect(editor, &Editor::save, results, &Results::showAll);
    }

    void MainWindow::showSensor(Core::Sensor* sensor) {
        clearStack();
        Viewer* viewer_wiget = new Viewer(vector, *sensor);
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        scroll_area->setWidget(viewer_wiget);
        stacked_widget->addWidget(scroll_area);
        stacked_widget->setCurrentIndex(1);
        showStatus("Showing sensor " + QString::number(sensor->getId()));
    }

    void MainWindow::editSensor(Core::Sensor* sensor) {
        clearStack();
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        Editor* editor = new Editor(vector, sensor);
        scroll_area->setWidget(editor);
        stacked_widget->addWidget(scroll_area);
        stacked_widget->setCurrentIndex(1);
        has_unsaved_changes = true;
        showStatus("Editing sensor " + QString::fromStdString(sensor->getName()) + ".");
        connect(editor, &Editor::save, results, &Results::showAll);
    }

    void MainWindow::deleteSensor(Core::Sensor* sensor) {
        showStatus("Sensor " + QString::fromStdString(sensor->getName()) + " removed.");
        std::vector<Core::Sensor*>::iterator it = vector.begin();
        while(*it != sensor || it != vector.end())
        {
            ++it;
        }
        if(it != vector.end())
        {
            vector.erase(it);
        }
        else
        {
            return;
        }
        // Chiamata per aggiornare la lista
        results->refresh();
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