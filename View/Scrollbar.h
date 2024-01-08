#ifndef SCROLLBAR
#define SCROLLBAR

#include "../Core/Container.h"
#include "../ContainerObserverInterface.h"
#include "SensorPanel.h"
#include "MainWindow.h"
#include <vector>
#include <QScrollArea>
#include <QVBoxLayout>

namespace View {

class Scrollbar : public QWidget, public Core::ContainerObserverInterface
{
    Q_OBJECT
    
    private:
    MainWindow* mainwindow;
    Core::Container& container;
    QVBoxLayout* vector_layout;
    std::vector<SensorPanel*> panel_vector;
    QWidget* content;

    public:
    Scrollbar(MainWindow* mainwindow, Core::Container& container, QWidget* parent = 0);
    virtual void notifyAdd(Core::Container& cont);
    virtual void notifyRemove(Core::Container& cont, Core::Sensor& sensor);

    void openViewer(Core::Sensor& sensor);
};
};

#endif