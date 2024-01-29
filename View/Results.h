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
        void refresh();
        void clear();
        std::vector<unsigned int> convertId(unsigned int);

        signals:
        void editSensor(Core::Sensor* sensor);
        void showSensor(Core::Sensor* sensor);
        void deleteSensor(Core::Sensor* sensor);
        void searchId(std::vector<Core::Sensor*>& results_vector);

        public slots:
        void receiveId(unsigned int id);
        void showAll();
        void showResults(std::vector<Core::Sensor*>& results_vector);
    };
};

#endif