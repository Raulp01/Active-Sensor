#ifndef RESULTS
#define RESLUTS

#include <QWidget>
#include <QVector>
#include "Info.h"
#include "Core/Sensor.h"

namespace View {

    class Results : public QWidget
    {
        Q_OBJECT
        
        private:
        QVector<Info*> container;
        std::vector<Core::Sensor*>& vector;
        QVBoxLayout* layout;

        
        public:
        Results(std::vector<Core::Sensor*>& vector, QWidget* parent = 0);
        void clear();
        void showResults(std::vector<Core::Sensor*>& results_vector);
        void showResultsById(unsigned int id);

        signals:
        void editSensor(Core::Sensor* sensor);
        void showSensor(Core::Sensor* sensor);
        void deleteSensor(Core::Sensor* sensor);
        void searchId(std::vector<Core::Sensor*>& results_vector);

        public slots:
        void emitShowSensor(Core::Sensor& sensor);
        void emitEditSensor(Core::Sensor& sensor);
        void emitDeleteSensor(Core::Sensor& sensor);
        
    };
};

#endif