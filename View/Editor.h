#ifndef EDITOR
#define EDITOR

#include <QWidget>
#include "../IVisitor.h"
#include "../Core/Sensor.h"
#include "MainWindow.h"
#include "SensorEditor/EditSensor.h"
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QStackedLayout>
#include <QVector>

#include <QMainWindow>

namespace View {

    class Editor : public QWidget
    {
        Q_OBJECT

        private:
        std::vector<Core::Sensor*>& vector;
        Core::Sensor* sensor;
        QVBoxLayout* layout;
        QSpinBox* id_input;
        QLineEdit* name_input;
        QTextEdit* description_input;
        QSpinBox* age_input;
        QDoubleSpinBox* height_input;
        QDoubleSpinBox* weight_input;
        QComboBox* training_type_input;
        QDoubleSpinBox* training_time_input;
        QComboBox* type;
        QStackedLayout* stacked_editors;
        QVector<SensorEditor::EditSensor*> editors;

        public:
        Editor(std::vector<Core::Sensor*>& vector, Core::Sensor* sensor);

        public slots:
        void showType(int index);
        void apply();

        signals:
        void save();
    };

}

#endif