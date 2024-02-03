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
        layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QFormLayout* form_layout = new QFormLayout();
        form_layout->setLabelAlignment(Qt::AlignCenter | Qt::AlignTop);

        id_input = new QSpinBox();
        id_input->setMinimum(1);
        id_input->setMaximum(INT_MAX);
        id_input->setSingleStep(1);
        form_layout->addRow("Id:", id_input);

        name_input = new QLineEdit();
        form_layout->addRow("Name:", name_input);

        description_input = new QTextEdit();
        form_layout->addRow("Description:", description_input);

        age_input = new QSpinBox();
        age_input->setMinimum(1);
        age_input->setMaximum(110);
        age_input->setSingleStep(1);
        form_layout->addRow("Age:", age_input);

        height_input = new QDoubleSpinBox();
        height_input->setMinimum(0.6);
        height_input->setMaximum(2.5);
        height_input->setSingleStep(1);
        form_layout->addRow("Height:", height_input);

        weight_input = new QDoubleSpinBox();
        weight_input->setMinimum(5);
        weight_input->setMaximum(200);
        height_input->setSingleStep(5);
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

        layout->addStretch();

        const QSize apply_size = QSize(120, 80);

        QPushButton* apply = new QPushButton("Apply");
        apply->setIcon(QIcon(QPixmap(":/Assets/apply.png")));
        apply->setMinimumSize(apply_size);
        layout->addWidget(apply);

        if(sensor != nullptr)
        {
            id_input->setValue(sensor->getId());
            name_input->setText(QString::fromStdString(sensor->getName()));
            description_input->setText(QString::fromStdString(sensor->getDescription()));
            age_input->setValue(sensor->getAge());
            height_input->setValue(sensor->getHeight());
            weight_input->setValue(sensor->getWeight());
        }

        connect(type, qOverload<int>(&QComboBox::currentIndexChanged), this, &Editor::changedIndex);
        connect(apply, &QPushButton::pressed, this, &Editor::apply);
    }

    /* 
        Si è scelto di cambiare il tipo di sensore in un nuovo sensore o di uno già esistente
        attraverso il QComboBox type
    */
    void Editor::changedIndex()
    {
        // Vengono salvati i dati raccolti dai vari widget nel costruttore
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
            sensor = new Core::HeartSensor(
                id,
                name.toStdString(),
                description.toStdString(),
                age, height,
                weight,
                training_type
            );
            break;
        case 1:
            sensor = new Core::CaloriesCounter(
                id,
                name.toStdString(),
                description.toStdString(),
                age,
                height,
                weight,
                training_type
            );
            break;
        case 2:
            sensor = new Core::Speedometer(
                id,
                name.toStdString(),
                description.toStdString(),
                age,
                height,
                weight,
                training_type
            );
            break;
        case 3:
            sensor = new Core::Activity(
                id,
                name.toStdString(),
                description.toStdString(),
                age,
                height,
                weight,
                training_type
            );
            break;
        }
        vector.push_back(sensor);
    }

    //Slot per il tasto Apply
    void Editor::apply()
    {
        unsigned int id = id_input->value();
        QString name = name_input->text();
        QString description = description_input->toPlainText();
        unsigned int age = age_input->value();
        float height = height_input->value();
        float weight = weight_input->value();
        unsigned int training_type = training_type_input->currentIndex() + 1;

        //Sensore creato scegliendo il tipo selezionato sul QComboBox
        if(sensor == nullptr)
        {
            switch (type->currentIndex())
            {
            case 0:
                sensor = new Core::HeartSensor(
                    id,
                    name.toStdString(),
                    description.toStdString(),
                    age,
                    height,
                    weight,
                    training_type
                );
                break;
            case 1:
                sensor = new Core::CaloriesCounter(
                    id,
                    name.toStdString(),
                    description.toStdString(),
                    age,
                    height,
                    weight,
                    training_type
                );
                break;
            case 2:
                sensor = new Core::Speedometer(
                    id,
                    name.toStdString(),
                    description.toStdString(),
                    age,
                    height,
                    weight,
                    training_type
                );
                break;
            case 3:
                sensor = new Core::Activity(id,
                name.toStdString(),
                description.toStdString(),
                age,
                height,
                weight,
                training_type
            );
                break;
            }

            vector.push_back(sensor);
        }
        else
        {
            //Sensore esistente: chiamati i metodi per aggiornarlo
            sensor->setId(id);
            sensor->setName(name.toStdString());
            sensor->setDescription(description.toStdString());
            sensor->setAge(age);
            sensor->setHeight(height);
            sensor->setWeight(weight);
            sensor->setTrainingType(training_type);
            sensor->reset();
        }

        emit save(vector);
    }
};