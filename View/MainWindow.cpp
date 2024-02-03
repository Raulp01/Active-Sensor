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
            QIcon(QPixmap((":/Assets/open_file.png"))),
            "Open"
        );
        open->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
        QAction* save = new QAction(
            QIcon(QPixmap((":/Assets/save.png"))),
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

        // Sets toolbar
        toolbar = addToolBar("Toolbar");
        toolbar->addAction(create);
        toolbar->addAction(open);
        toolbar->addAction(save);
        toolbar->addAction(save_as);
        toolbar->addSeparator();
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

        const QSize button_size = QSize(120, 40);

        QPushButton* new_sensor = new QPushButton("New Sensor");
        new_sensor->setIcon(QIcon(QPixmap(":/Assets/new_item.png")));
        new_sensor->setMinimumSize(button_size);
        layout->addWidget(new_sensor);

        search = new Search();
        layout->addWidget(search);

        std::cout << "MainWindow::MainWindow Aggiunto search" << std::endl;

        left_stacked_widget = new QStackedWidget();
        layout->addWidget(left_stacked_widget);

        std::cout << "MainWindow::MainWindow Parte sinistra" << std::endl;

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
        //connect(togge_toolbar, &QAction::triggered, this, &MainWindow::toggleToolbar);
        connect(search, &Search::searchSensorId, this, &MainWindow::searchById);
        connect(search, &Search::filterSensor, this, &MainWindow::searchByFilter);
        connect(search, &Search::showAll, this, &MainWindow::showAllData);
        connect(new_sensor, &QPushButton::pressed, this, &MainWindow::createSensor);

        reloadData(vector);

        std::cout << "MainWindow::MainWindow Collegati tutti i signal-slots" << std::endl;

        std::cout << "MainWindow::MainWindow Pronto per le operazioni" << std::endl;
    }

    //Slot che aggiorna la lista di sensori con il vettore passato per parametro
    void MainWindow::reloadData(std::vector<Core::Sensor*>& reload_vector) {
        std::cout << "MainWindow::reloadData" << std::endl;
        clearStack();
        std::cout << "MainWindow::reloadData preparazione risultati..." << std::endl;
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        std::cout << "MainWindow::reloadData results creato in MainWindow" << std::endl;
        if(reload_vector.empty())
        {
            QLabel* label = new QLabel("No sensors available at the moment");
            scroll_area->setWidget(label);   
            label->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        }
        else
        {
            Results* results = new Results(reload_vector, left_stacked_widget);
            scroll_area->setWidget(results);
            results->showResults(reload_vector);

            connect(results, &Results::showSensor, this, &MainWindow::showSensor);
            connect(results, &Results::editSensor, this, &MainWindow::editSensor);
            connect(results, &Results::deleteSensor, this, &MainWindow::deleteSensor);
        }
        std::cout << "MainWindow::reloadData Fine showResults" << std::endl;
        left_stacked_widget->addWidget(scroll_area);
        left_stacked_widget->setCurrentIndex(1);
        right_stacked_widget->setCurrentIndex(0);
        std::cout << "MainWindow::reloadData reloadData avvenuto con successo" << std::endl;
        
        has_unsaved_changes = true;
    }

    //Prende i segnali che non passano parametri e che vogliono aggiornare la lista di sensori
    void MainWindow::showAllData()
    {
        reloadData(vector);
    }

    //Rimuove il widget di destra e pulisce lo stack dell'interfaccia
    void MainWindow::clearStack() 
    {
        std::cout << "MainWindow::clearStack Pulizia clearStack destro" << std::endl;
        //right_stacked_widget->removeWidget(right_stacked_widget->currentWidget());
        QWidget* right_widget = right_stacked_widget->widget(0);
        while (right_widget) {
            std::cout << "MainWindow::clearStackPulizia stack destro" << std::endl;
            right_stacked_widget->removeWidget(right_widget);
            delete right_widget;
            right_widget = right_stacked_widget->widget(1);
        }

        QWidget* left_widget = left_stacked_widget->widget(1);
        while (left_widget) {
            std::cout << "MainWindow::clearStack Pulizia stack sinistro" << std::endl;
            left_stacked_widget->removeWidget(left_widget);
            delete left_widget;
            left_widget = left_stacked_widget->widget(1);
        }
    }


    //Crea un nuovo file
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
        create_item->setEnabled(true);
        reloadData(vector);
        
        std::cout << "MainWindow::newDataset Nuovo Dataset. Dimensione vettore = " << vector.size() << std::endl;
    }

    //Apre un file esistente
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
        create_item->setEnabled(true);
        std::cout << "MainWindow::openDataset Data successfully loaded from " << path.toStdString() << "." << std::endl;
        reloadData(vector);
    }

    /*
        Salva nel file aperto o creato i sensori in vector
        Se non è disponibile un file, apre saveAsDataset
    */
    void MainWindow::saveDataset() {
        if(json_file.getPath() == "")
        {
           saveAsDataset();
        }
        json_file.store(vector);
        has_unsaved_changes = false;
        std::cout << "MainWindow::saveDataset Dataset saved." << std::endl;
    }

    //Salva in un nuovo file i sensori in vector
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

    /*
        Viene costruito un nuovo results per invocare la funzione showResultsById e ritornare 
        il vettore con solo gli elementi che iniziano per quell'id
    */
    void MainWindow::searchById(unsigned int id) 
    {
        std::cout << "MainWindow::searchById" << std::endl;
        clearStack();
        Results* results = new Results(vector);
        std::cout << "MainWindow::searchById settato il widget in scroll_area" << std::endl;
        std::vector<Core::Sensor*> id_vector = results->showResultsById(id);
        std::cout << "MainWindow::searchById fine showResultsById (Results)" << std::endl;
        reloadData(id_vector);
        has_unsaved_changes = true;
    }

    /*
        Viene costruito un nuovo results per invocare la funzione showResultsByFilter e ritornare 
        il vettore con solo gli elementi di tipo filter
    */
    void MainWindow::searchByFilter(std::string filter)
    {
        std::cout << "MainWindow::searchByFilter" << std::endl;
        clearStack();
        Results* results = new Results(vector);
        std::cout << "MainWindow::searchByFilter settato il widget in scroll_area" << std::endl;
        std::vector<Core::Sensor*> filter_vector = results->showResultsByFilter(filter);
        std::cout << "MainWindow::searchById fine showResultsById (Results)" << std::endl;
        reloadData(filter_vector);
        has_unsaved_changes = true;
    }

    void MainWindow::createSensor() 
    {
        std::cout << "MainWindow::createSensor Inizio createSensor" << std::endl;
        reloadData(vector);
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
        connect(editor, &Editor::save, this, &MainWindow::reloadData);
    }

    void MainWindow::showSensor(Core::Sensor* sensor) {
        reloadData(vector);
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
        connect(viewer_wiget, &Viewer::reloadViewer, this, &MainWindow::showSensor);
        std::cout << "MainWindow::showSensor Showing sensor " + QString::number(sensor->getId()).toStdString() << std::endl;
    }

    void MainWindow::editSensor(Core::Sensor* sensor) {
        std::cout << "MainWindow::editSensor" << std::endl;
        reloadData(vector);
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
        connect(editor, &Editor::save, this, &MainWindow::reloadData);
    }

    void MainWindow::deleteSensor(Core::Sensor* sensor) {
        clearStack();
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
        reloadData(vector);
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