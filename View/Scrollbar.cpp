#include "Scrollbar.h"

namespace View
{
    Scrollbar::Scrollbar(MainWindow* mainwindow, std::vector<Core::Sensor*>&, QWidget* parent) :
    mainwindow(mainwindow), vector(vector), QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        content = new QWidget();

        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area->setWidgetResizable(true);
        scroll_area->setWidget(content);
        layout->addWidget(scroll_area);

        vector_layout = new QVBoxLayout(content);
        vector_layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    }
};