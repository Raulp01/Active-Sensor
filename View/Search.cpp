#include "Search.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>

namespace View
{
    Search::Search(QWidget* parent) : QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QLabel* title = new QLabel("Search Sensor");
        title->setAlignment(Qt::AlignHCenter);
        layout->addWidget(title);

        QPushButton* show_all = new QPushButton("Show All");
        layout->addWidget(show_all);

        QFormLayout* form = new QFormLayout();
        form->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        layout->addLayout(form);

        id_input = new QSpinBox();
        id_input->setValue(1);
        id_input->setMinimum(1);
        id_input->setSingleStep(1);
        form->addRow("ID:", id_input);

        filter_input = new QComboBox();
        filter_input->addItem("HeartSensor");
        filter_input->addItem("CaloriesCounter");
        filter_input->addItem("Speedometer");
        filter_input->addItem("Activity");
        form->addRow("Filter:", filter_input);

        QPushButton* apply_id = new QPushButton("Search ID");
        layout->addWidget(apply_id);

        QPushButton* apply_filter = new QPushButton("Filter for type");
        layout->addWidget(apply_filter);

        connect(apply_id, &QPushButton::pressed, this, &Search::search);
        connect(apply_filter, &QPushButton::pressed, this, &Search::filter);
        connect(show_all, &QPushButton::pressed, this, &Search::showAll);
    }

    void Search::search()
    {
        emit searchSensorId(id_input->value());
    }

    void Search::filter()
    {
        emit filterSensor(filter_input->currentText().toStdString());
    }
}