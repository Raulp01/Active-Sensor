#include "Editor.h"
#include <QGridLayout>
#include <QLabel>
#include <QFormLayout>
#include <QIcon>
#include <QVBoxLayout>

namespace View
{
    Editor::Editor(std::vector<Core::Sensor*>& vector, Core::Sensor* sensor) : vector(vector), sensor(sensor)
    {
        std::cout << "Editor::Editor Costruttore Editor vector = " << vector.size() << std::endl;
        layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QFormLayout* form_layout = new QFormLayout();
        form_layout->setLabelAlignment(Qt::AlignCenter | Qt::AlignTop);

        id_input = new QSpinBox();
        id_input->setMinimum(1);
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
        height_input->setMinimum(0.6);
        height_input->setMaximum(2.5);
        height_input->setSingleStep(1);
        if(sensor != nullptr)
        {
            height_input->setValue(sensor->getHeight());
        }
        form_layout->addRow("Height:", height_input);

        weight_input = new QDoubleSpinBox();
        weight_input->setMinimum(5);
        weight_input->setMaximum(200);
        height_input->setSingleStep(5);
        if(sensor != nullptr)
        {
            weight_input->setValue(sensor->getWeight());
        }
        form_layout->addRow("Weight:", weight_input);

        training_type_input = new QComboBox();
        training_type_input->addItem(QIcon(QPixmap(":/Assets/Light.svg")), "Light");
        training_type_input->addItem(QIcon(QPixmap(":/Assets/Moderate.svg")), "Moderate");
        training_type_input->addItem(QIcon(QPixmap(":/Assets/High.svg")), "High");
        training_type_input->addItem(QIcon(QPixmap(":/Assets/Very High.png")), "Very High");
        training_type_input->addItem(QIcon(QPixmap(":/Assets/Maximum.jpg")), "Maximum");
        if(sensor != nullptr)
        {
            training_type_input->setPlaceholderText(QString::fromStdString(sensor->getTrainingTypeToString()));
        }
        form_layout->addRow("Training Type:", training_type_input);
        
        layout->addLayout(form_layout);
        
        QFormLayout* type_form = new QFormLayout();
        type_form->setLabelAlignment(Qt::AlignCenter | Qt::AlignTop);
        type = new QComboBox();
        type->addItem(QIcon(QPixmap(":/Assets/HeartSensor.png")), "HeartSensor");
        type->addItem(QIcon(QPixmap(":/Assets/CaloriesCounter.png")), "CaloriesCounter");
        type->addItem(QIcon(QPixmap(":/Assets/Speedometer.png")), "Speedometer");
        type->addItem(QIcon(QPixmap(":/Assets/Activity.png")), "Activity");
        if(sensor != nullptr)
        {
            type->setPlaceholderText(QString::fromStdString(sensor->getType()));
        }
        type_form->addRow("Type:", type);
        layout->addLayout(type_form);
        std::cout << "Editor::Editor Dimensione vector prima degli EditSensor = " << vector.size() << std::endl;


        layout->addStretch();

        QPushButton* apply = new QPushButton("Apply");
        layout->addWidget(apply);

        connect(type, qOverload<int>(&QComboBox::currentIndexChanged), this, &Editor::changedIndex);
        connect(apply, &QPushButton::pressed, this, &Editor::apply);
    }

    void Editor::changedIndex()
    {
        //Si è scelto di cambiare il tipo di sensore

        unsigned int id = id_input->value();
        QString name = name_input->text();
        QString description = description_input->toPlainText();
        unsigned int age = age_input->value();
        float height = height_input->value();
        float weight = weight_input->value();
        unsigned int training_type = training_type_input->currentIndex() + 1;

        // Sensore esistente: viene tolto dal vettore, ricreato e aggiunto al vettore

        if(sensor != nullptr)
        {
            auto it = vector.begin();
            while(it != vector.end())
            {
                if(*it == sensor)
                {
                    vector.erase(it);
                    delete sensor;
                    break;
                }
                it++;
            }
        }

        // Sensore nuovo: viene creato e aggiunto al vettore

        switch (type->currentIndex())
        {
        case 0:
            sensor = new Core::HeartSensor(id, name.toStdString(), description.toStdString(), age, height, weight, training_type);
            std::cout << "Editor::changedIndex creazione HeartSensor 1 index: " << type->currentIndex() << std::endl;
            break;
        case 1:
            sensor = new Core::CaloriesCounter(id, name.toStdString(), description.toStdString(), age, height, weight, training_type);
            std::cout << "Editor::changedIndex creazione CaloriesCounter 2 index: " << type->currentIndex() << std::endl;
            break;
        case 2:
            sensor = new Core::Speedometer(id, name.toStdString(), description.toStdString(), age, height, weight, training_type);
            std::cout << "Editor::changedIndex creazione Speedometer 3 index: " << type->currentIndex() << std::endl;
            break;
        case 3:
            std::cout << "Editor::changedIndex creazione Activity 4 index: " << type->currentIndex() << std::endl;
            sensor = new Core::Activity(id, name.toStdString(), description.toStdString(), age, height, weight, training_type);
            break;
        }
        vector.push_back(sensor);
        std::cout << "Editor::changedIndex Dimensione attuale di vector (dopo push_back() in Editor) " << vector.size() << std::endl;
    }

    void Editor::apply()
    {
        //Slot per il tasto Apply

        unsigned int id = id_input->value();
        QString name = name_input->text();
        QString description = description_input->toPlainText();
        unsigned int age = age_input->value();
        float height = height_input->value();
        float weight = weight_input->value();
        unsigned int training_type = training_type_input->currentIndex() + 1;

        //Sensore creato scegliendo il tipo di default sul QComboBox

        if(sensor == nullptr)
        {
            switch (type->currentIndex())
            {
            case 0:
                std::cout << "Editor::apply case 1, index: " << type->currentIndex() << std::endl;
                sensor = new Core::HeartSensor(id, name.toStdString(), description.toStdString(), age, height, weight, training_type);
                break;
            case 1:
                std::cout << "Editor::apply case 2, index: " << type->currentIndex() << std::endl;
                sensor = new Core::CaloriesCounter(id, name.toStdString(), description.toStdString(), age, height, weight, training_type);
                break;
            case 2:
                std::cout << "Editor::apply case 3, index: " << type->currentIndex() << std::endl;
                sensor = new Core::Speedometer(id, name.toStdString(), description.toStdString(), age, height, weight, training_type);
                break;
            case 3:
                std::cout << "Editor::apply case 4, index: " << type->currentIndex() << std::endl;
                sensor = new Core::Activity(id, name.toStdString(), description.toStdString(), age, height, weight, training_type);
                break;
            }

            vector.push_back(sensor);
            std::cout << "Editor::apply Dimensione attuale di vector (dopo push_back() in Editor) " << vector.size() << std::endl; 
        }
        else
        {
            //Sensore esistente: chiamati i metodi per aggiornarlo

            sensor->setId(id);
            std::cout << "Editor::apply id: " << sensor->getId() << std::endl;
            sensor->setName(name.toStdString());
            std::cout << "Editor::apply name: " << sensor->getName() << std::endl;
            sensor->setDescription(description.toStdString());
            sensor->setAge(age);
            std::cout << "Editor::apply age: " << sensor->getAge() << std::endl;
            sensor->setHeight(height);
            std::cout << "Editor::apply height: " << sensor->getHeight() << std::endl;
            sensor->setWeight(weight);
            std::cout << "Editor::apply weight: " << sensor->getWeight() << std::endl;
            sensor->setTrainingType(training_type);
            std::cout << "Editor::apply training_type: " << sensor->getTrainingType() << std::endl;
            std::cout << "Editor::apply Dimensione attuale di vector (dopo modifica in Editor) " << vector.size() << std::endl;
            sensor->reset();
        }

        emit save(vector);
        std::cout << "Editor::apply DOPO save in Editor" << std::endl;
    }
};