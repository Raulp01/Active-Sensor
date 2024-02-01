#ifndef EDITOR
#define EDITOR

#include <QWidget>
#include "../IVisitor.h"
#include "../Core/Sensor.h"
#include "MainWindow.h"
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
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
        QComboBox* type;

        public:
        Editor(std::vector<Core::Sensor*>& vector, Core::Sensor* sensor);

        public slots:
        void apply();
        void changedIndex();

        signals:
        void save(std::vector<Core::Sensor*>& reload_vector);
    };

}

#endif