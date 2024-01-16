#ifndef SCROLLBAR
#define SCROLLBAR

#include "SensorPanel.h"
#include "MainWindow.h"
#include <vector>
#include <QScrollArea>
#include <QVBoxLayout>

namespace View {

class Scrollbar : public QWidget
{
    Q_OBJECT
    
    private:
    MainWindow* mainwindow;
    std::vector<Core::Sensor*>& vector;
    QVBoxLayout* vector_layout;
    std::vector<SensorPanel*> panel_vector;
    QWidget* content;

    public:
    Scrollbar(MainWindow* mainwindow, std::vector<Core::Sensor*>& vector, QWidget* parent = 0);
};
};

#endif