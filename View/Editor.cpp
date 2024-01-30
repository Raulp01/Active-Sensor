#include "Editor.h"
#include <QGridLayout>
#include <QLabel>
#include <QFormLayout>
#include <QIcon>
#include <QVBoxLayout>
#include "SensorEditor/EditActivity.h"
#include "SensorEditor/EditCaloriesCounter.h"
#include "SensorEditor/EditHeartSensor.h"
#include "SensorEditor/EditSpeedometer.h"
#include "SensorEditor/SensorInjector.h"

namespace View
{
    Editor::Editor(std::vector<Core::Sensor*>& vector, Core::Sensor* sensor) : vector(vector), sensor(sensor)
    {
        layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        QFormLayout* form_layout = new QFormLayout();
        form_layout->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);

        id_input = new QSpinBox();
        id_input->setMinimum(0);
        id_input->setMaximum(INT_MAX);
        id_input->setSingleStep(1);
        if(sensor != nullptr)
        {
            id_input->setValue(sensor->getId());
        }
        form_layout->addRow("Id:", id_input);

        name_input = new QLineEdit();
        if(sensor != nullptr)
        {
            name_input->setText(QString::fromStdString(sensor->getName()));
        }
        form_layout->addRow("Name:", name_input);

        description_input = new QTextEdit();
        if(sensor != nullptr)
        {
            description_input->setText(QString::fromStdString(sensor->getDescription()));
        }
        form_layout->addRow("Description:", description_input);

        age_input = new QSpinBox();
        age_input->setMinimum(1);
        age_input->setMaximum(110);
        age_input->setSingleStep(1);
        if(sensor != nullptr)
        {
            age_input->setValue(sensor->getAge());
        }
        form_layout->addRow("Age:", age_input);

        height_input = new QDoubleSpinBox();
        height_input->setMinimum(0);
        height_input->setMaximum(2.5);
        height_input->setSingleStep(1);
        if(sensor != nullptr)
        {
            height_input->setValue(sensor->getHeight());
        }
        form_layout->addRow("Height:", height_input);

        weight_input = new QDoubleSpinBox();
        weight_input->setMinimum(0);
        weight_input->setMaximum(200);
        height_input->setSingleStep(1);
        if(sensor != nullptr)
        {
            weight_input->setValue(sensor->getWeight());
        }
        form_layout->addRow("Weight:", weight_input);

        training_time_input = new QDoubleSpinBox();
        training_time_input->setMinimum(0);
        training_time_input->setSingleStep(0.5);
        if(sensor != nullptr)
        {
            training_time_input->setValue(sensor->getTrainingTime());
        }
        form_layout->addRow("Training Time:", training_time_input);

        training_type_input = new QComboBox();
        if(sensor != nullptr)
        {
            training_type_input->setPlaceholderText(QString::fromStdString(sensor->getTrainingTypeToString()));
        }
        training_type_input->addItem(QIcon("../Assets/Light.svg"), "Light");
        training_type_input->addItem(QIcon("../Assets/Moderate.svg"), "Moderate");
        training_type_input->addItem(QIcon("../Assets/High.svg"), "High");
        training_type_input->addItem(QIcon("../Assets/Very High.png"), "Very High");
        training_type_input->addItem(QIcon("../Assets/Maximum.jpg"), "Maximum");
        form_layout->addRow("Training Type:", training_type_input);
        
        layout->addLayout(form_layout);
        

        QFormLayout* type_form = new QFormLayout();
        type_form->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
        type = new QComboBox();
        type->addItem("Heart Sensor");
        type->addItem("CaloriesCounter");
        type->addItem("Speedometer");
        type->addItem("Activity");
        if(sensor != nullptr)
        {
            type->setPlaceholderText(QString::fromStdString(sensor->getType()));
        }
        type_form->addRow("Type:", type);
        layout->addLayout(type_form);

        stacked_editors = new QStackedLayout();
        layout->addLayout(stacked_editors);

        std::cout << "Dopo stackedEditors in Editor" << std::endl;

        SensorEditor::EditHeartSensor* edit_heart_sensor = new SensorEditor::EditHeartSensor();
        stacked_editors->addWidget(edit_heart_sensor);
        editors.push_back(edit_heart_sensor);

        SensorEditor::EditCaloriesCounter* edit_calories_counter = new SensorEditor::EditCaloriesCounter();
        stacked_editors->addWidget(edit_calories_counter);
        editors.push_back(edit_calories_counter);

        SensorEditor::EditSpeedometer* edit_speedometer = new SensorEditor::EditSpeedometer();
        stacked_editors->addWidget(edit_speedometer);
        editors.push_back(edit_speedometer);

        SensorEditor::EditActivity* edit_activity = new SensorEditor::EditActivity();
        stacked_editors->addWidget(edit_activity);
        editors.push_back(edit_activity);

        if(sensor != nullptr)
        {
            SensorEditor::SensorInjector sensor_injector(
                *edit_activity,
                *edit_calories_counter,
                *edit_speedometer,
                *edit_heart_sensor
            );
            sensor->accept(sensor_injector);
        }
        showType(type->currentIndex());

        layout->addStretch();

        QPushButton* apply = new QPushButton("Apply");
        layout->addWidget(apply);

        connect(apply, &QPushButton::pressed, this, &Editor::apply);
        connect(type, qOverload<int>(&QComboBox::currentIndexChanged), this, &Editor::showType);
    }

    void Editor::showType(int index)
    {
        stacked_editors->setCurrentIndex(index);
    }

    void Editor::apply()
    {
        unsigned int id = id_input->value();
        QString name = name_input->text();
        QString description = description_input->toPlainText();
        unsigned int age = age_input->value();
        float height = height_input->value();
        float weight = weight_input->value();
        unsigned int training_type = training_type_input->currentIndex();
        float training_time = training_time_input->value();

        SensorEditor::EditSensor* editor = editors[stacked_editors->currentIndex()];
        Core::Sensor* new_sensor = editor->create(id, name, description, age, height, weight, training_type, training_time);

        // To-do fare un push_back dell'item e ricaricare la lista in Mainwindow
        vector.push_back(new_sensor);
        emit save();
        this->close();
    }
};