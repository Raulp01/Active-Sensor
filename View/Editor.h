#ifndef EDITOR
#define EDITOR

#include <QWidget>
#include "../IVisitor.h"
#include "../Core/Activity.h"
#include "MainWindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QStackedLayout>
#include <QVector>

namespace View {

    class Editor : public QWidget
    {
        Q_OBJECT

        private:
        MainWindow* mainwindow;
        std::vector<Core::Sensor*>& vector;
        Core::Sensor* sensor;
        QVBoxLayout* layout;
        QWidget* widget;
        QPushButton* save;
        QSpinBox* id_input;
        QLineEdit* name_input;
        QTextEdit* description_input;
        QSpinBox* age_input;
        QDoubleSpinBox* height_input;
        QDoubleSpinBox* weight_input;
        QComboBox* training_type_input;
        QDoubleSpinBox* training_time_input;
        QDoubleSpinBox* distance_input;
        QComboBox* type;
        QStackedLayout* stacked_editors;
        QVector<SensorEditor::EditSensor*> editors;

        public:
        Editor(MainWindow* mainwindow, std::vector<Core::Sensor*>& vector, Core::Sensor* sensor, QWidget* parent = 0);

        public slots:
        void showType(int index);
        void apply();
    };

};

#endif