#ifndef MAINWINDOW
#define MAINWINDOW

#include "../Core/Container.h"
#include "Scrollbar.h"
#include "Viewer.h"
#include "../Core/Json/DataMapper/JsonFile.h"
#include <QMainWindow>
#include <QStackedWidget>

namespace View {

class MainWindow: public QMainWindow {
    Q_OBJECT
  private:
    bool has_unsaved_changes;
    QAction* create_item;
    QToolBar* toolbar;
    Core::Container& container;
    Core::Json::DataMapper::JsonFile& json_file;
    //SearchWidget* search_widget;
    QStackedWidget* stacked_widget;
    //ResultsWidget* results_widget;
    Viewer* viewer_wiget;
  
  public:
    explicit MainWindow(Core::Container& container, Core::Json::DataMapper::JsonFile& json_file, QWidget *parent = 0);
    Core::Container& getContainer();
    MainWindow& reloadData();
    //SearchWidget* getSearchWidget();
  
  private:
    void clearStack();

  public slots:
    void newDataset();
    void openDataset();
    void saveDataset();
    void saveAsDataset();
    void toggleToolbar();
    void showStatus(QString message);
    //void search(Engine::Query query);
    void createSensor();
    void showSensor(const Core::Sensor* sensor);
    void editSensor(Core::Sensor* sensor);
    void deleteSensor(Core::Sensor* sensor);
    void close();
};

}

#endif