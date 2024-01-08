#include "Editor.h"
#include <QGridLayout>
#include <QLabel>
#include <QFormLayout>
#include <QIcon>
#include <QVBoxLayout>

namespace View
{
    Editor::Editor(MainWindow* mainwindow, Core::Sensor& sensor, QWidget* parent) : 
    mainwindow(mainwindow), sensor(sensor), QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        QLabel* id = new QLabel("Id: " + QString::fromStdString(sensor.getId()));
        layout->addWidget(id);

        QFormLayout* form_layout = new QFormLayout();
        form_layout->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        name = new QLineEdit(QString::fromStdString(sensor.getName()));
        form_layout->addRow("Name:", name);

        description = new QTextEdit();
        description->setText(QString::fromStdString(sensor.getDescription()));
        form_layout->addRow("Description:", description);

        age = new QSpinBox();
        age->setMinimum(1);
        age->setMaximum(110);
        age->setSingleStep(1);
        age->setValue(sensor.getAge());
        form_layout->addRow(age);

        height = new QDoubleSpinBox();
        height->setMinimum(0);
        height->setMaximum(2.5);
        height->setSingleStep(1);
        height->setValue(sensor.getHeight());
        form_layout->addRow(height);

        weight = new QDoubleSpinBox();
        weight->setMinimum(0);
        weight->setMaximum(200);
        height->setSingleStep(1);
        weight->setValue(sensor.getWeight());
        form_layout->addRow(weight);

        training_time = new QDoubleSpinBox();
        training_time->setMinimum(0);
        training_time->setValue(sensor.getTrainingTime());
        form_layout->addRow(training_time);

        training_type = new QComboBox();
        training_type->setPlaceholderText(QString::fromStdString(sensor.getTrainingTypeToString()));
        training_type->addItem(QIcon("../Assets/Light.svg"), "Light");
        training_type->addItem(QIcon("../Assets/Moderate.svg"), "Moderate");
        training_type->addItem(QIcon("../Assets/High.svg"), "High");
        training_type->addItem(QIcon("../Assets/Very High.png"), "Very High");
        training_type->addItem(QIcon("../Assets/Maximum.jpg"), "Maximum");

        layout->addLayout(form_layout);
        layout->addWidget(training_type);
    }
};