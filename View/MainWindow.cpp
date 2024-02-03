#include "MainWindow.h"
#include "../Core/Json/Reader.h"
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include <QToolBar>
#include <QIcon>
#include <QAction>
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
        // Creazione delle Actions che compariranno nella toolbar
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
        toolbar->addSeparator();
        toolbar->addSeparator();
        toolbar->addAction(close);

        // Divisione dello schermo a metà
        QSplitter* splitter = new QSplitter(this);
        setCentralWidget(splitter);

        QWidget* widget = new QWidget(this);
        splitter->addWidget(widget);

        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
        widget->setLayout(layout);

        // Crea il pulsante "New Sensor" impostandogli una dimensione e un'icona
        const QSize button_size = QSize(120, 40);

        QPushButton* new_sensor = new QPushButton("New Sensor");
        new_sensor->setIcon(QIcon(QPixmap(":/Assets/new_item.png")));
        new_sensor->setMinimumSize(button_size);
        layout->addWidget(new_sensor);

        search = new Search();
        layout->addWidget(search);

        left_stacked_widget = new QStackedWidget();
        layout->addWidget(left_stacked_widget);

        right_stacked_widget = new QStackedWidget();
        splitter->addWidget(right_stacked_widget);

        splitter->setSizes(QList<int>() << 1000 << 3000);

        // Collegamento segnali
        connect(create, &QAction::triggered, this, &MainWindow::newDataset);
        connect(open, &QAction::triggered, this, &MainWindow::openDataset);
        connect(save, &QAction::triggered, this, &MainWindow::saveDataset);
        connect(close, &QAction::triggered, this, &MainWindow::close);
        connect(search, &Search::searchSensorId, this, &MainWindow::searchById);
        connect(search, &Search::filterSensor, this, &MainWindow::searchByFilter);
        connect(search, &Search::showAll, this, &MainWindow::showAllData);
        connect(new_sensor, &QPushButton::pressed, this, &MainWindow::createSensor);

        reloadData(vector);
    }

    //Slot che aggiorna la lista di sensori con il vettore passato nel parametro
    void MainWindow::reloadData(const std::vector<Core::Sensor*>& reload_vector) {
        clearStack();
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
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
        left_stacked_widget->addWidget(scroll_area);
        left_stacked_widget->setCurrentIndex(1);
        right_stacked_widget->setCurrentIndex(0);
        
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
        //right_stacked_widget->removeWidget(right_stacked_widget->currentWidget());
        QWidget* right_widget = right_stacked_widget->widget(0);
        while (right_widget) {
            right_stacked_widget->removeWidget(right_widget);
            delete right_widget;
            right_widget = right_stacked_widget->widget(1);
        }

        QWidget* left_widget = left_stacked_widget->widget(1);
        while (left_widget) {
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
        reloadData(vector);
    }

    //Apre un file esistente
    void MainWindow::openDataset() {
        QString path = QFileDialog::getOpenFileName(
            this,
            "Open a Dataset",
            "./",
            "JSON files *.json"
        );
        if(path.isEmpty())
        {
            return;
        }
        dynamic_cast<Core::Json::Reader&>(const_cast<Core::Json::IReader&>(json_file.getConverter().getReader())).clear();
        json_file.setPath(path.toStdString());
        vector = json_file.load();
        reloadData(vector);
    }

    
    // Salva nel file, aperto o creato, i sensori in vector.
    void MainWindow::saveDataset() {
        if(json_file.getPath() == "")
        {
           return;
        }
        json_file.store(vector);
        has_unsaved_changes = false;
    }

    /*
        Viene costruito un nuovo results per invocare la funzione showResultsById e ritornare 
        il vettore con solo gli elementi che iniziano per quell'id
    */
    void MainWindow::searchById(unsigned int id) 
    {
        clearStack();
        Results* results = new Results(vector);

        std::vector<Core::Sensor*> id_vector = results->showResultsById(id);

        reloadData(id_vector);
        has_unsaved_changes = true;
    }

    /*
        Viene costruito un nuovo results per invocare la funzione showResultsByFilter e ritornare 
        il vettore con solo gli elementi di tipo filter
    */
    void MainWindow::searchByFilter(std::string filter)
    {
        clearStack();
        Results* results = new Results(vector);

        std::vector<Core::Sensor*> filter_vector = results->showResultsByFilter(filter);

        reloadData(filter_vector);
        has_unsaved_changes = true;
    }

    void MainWindow::createSensor() 
    {
        reloadData(vector);

        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);

        Editor* editor = new Editor(vector, nullptr);

        scroll_area->setWidget(editor);
        right_stacked_widget->addWidget(scroll_area);
        right_stacked_widget->setCurrentIndex(1);
        has_unsaved_changes = true;

        connect(editor, &Editor::save, this, &MainWindow::reloadData);
    }

    void MainWindow::showSensor(Core::Sensor* sensor) {
        // Pulisce gli stacked_widget
        reloadData(vector);

        // Crea una nuova QScrollArea
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);

        // Crea il viewer
        Viewer* viewer_wiget = new Viewer(*sensor);
        
        scroll_area->setWidget(viewer_wiget);
        right_stacked_widget->addWidget(scroll_area);
        right_stacked_widget->setCurrentIndex(1);

        // Connette i segnali
        connect(viewer_wiget, &Viewer::reloadViewer, this, &MainWindow::showSensor);
    }

    void MainWindow::editSensor(Core::Sensor* sensor) {
        reloadData(vector);

        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);

        Editor* editor = new Editor(vector, sensor);

        scroll_area->setWidget(editor);
        right_stacked_widget->addWidget(scroll_area);
        right_stacked_widget->setCurrentIndex(1);
        has_unsaved_changes = true;

        connect(editor, &Editor::save, this, &MainWindow::reloadData);
    }

    // Distrugge il sensore passato
    void MainWindow::deleteSensor(const Core::Sensor* sensor) {
        clearStack();

        auto it = vector.begin();
        while(it != vector.end() && *it != sensor)
        {
            it++;
        }
        if(it != vector.end())
        {
            Core::Sensor* hold = *it;
            vector.erase(it);
            delete hold;
        }

        // Chiamata per aggiornare la lista
        reloadData(vector);
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