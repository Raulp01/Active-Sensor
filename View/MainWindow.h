#ifndef MAINWINDOW
#define MAINWINDOW

#include "../Core/Sensor.h"
#include "Results.h"
#include "Viewer.h"
#include "../Core/Json/DataMapper/JsonFile.h"
#include <QMainWindow>
#include <QStackedWidget>
#include "Editor.h"
#include "Search.h"

namespace View {

  class MainWindow: public QMainWindow 
  {
    Q_OBJECT

    private:
      bool has_unsaved_changes;
      QToolBar* toolbar;
      std::vector<Core::Sensor*>& vector;
      Core::Json::DataMapper::JsonFile& json_file;
      Search* search;
      QStackedWidget* left_stacked_widget;
      QStackedWidget* right_stacked_widget;
    
    public:
      explicit MainWindow(std::vector<Core::Sensor*>& vector, Core::Json::DataMapper::JsonFile& json_file, QWidget *parent = 0);
    
    private:
      void clearStack();

    public slots:
      void newDataset();
      void openDataset();
      void saveDataset();
      void searchById(unsigned int id);
      void searchByFilter(std::string filter);
      void createSensor();
      void showSensor(Core::Sensor* sensor);
      void editSensor(Core::Sensor* sensor);
      void deleteSensor(const Core::Sensor* sensor);
      void reloadData(const std::vector<Core::Sensor*>& reload_vector);
      void showAllData();
      void close();
  };

}

#endif