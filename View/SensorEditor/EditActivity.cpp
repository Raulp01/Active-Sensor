#include "EditActivity.h"
#include <QFormLayout>

namespace View {
namespace SensorEditor {
    EditActivity::EditActivity(QWidget* parent) : EditSensor(parent) 
    {
        QFormLayout* form = new QFormLayout(this);
        form->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);

        distance = new QDoubleSpinBox();
        distance->setMinimum(0);
        form->addRow("Distance:", distance);
    }
    
    EditActivity::~EditActivity() {}

    Core::Sensor* EditActivity::create(
        unsigned int id,
        QString& name,
        QString& description,
        unsigned int age,
        float height,
        float weight,
        unsigned int training_type,
        float training_time) 
    {
        return new Core::Activity(
            id,
            name.toStdString(),
            description.toStdString(),
            age,
            height,
            weight,
            training_type,
            training_time,
            distance->value()
        );
    }

    void EditActivity::setValues(Core::Activity& activity)
    {
        distance->setValue(activity.getDistance());
    }
}
}