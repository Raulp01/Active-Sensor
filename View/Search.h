#ifndef SEARCH
#define SEARCH

#include <QWidget>
#include <iostream>
#include <QSpinBox>
#include <QComboBox>

namespace View
{
    class Search : public QWidget
    {
        Q_OBJECT

        private:
        QSpinBox* id_input;
        QComboBox* filter_input;

        public:
        Search(QWidget* parent = 0);

        signals:
        void searchSensorId(unsigned int id);
        void filterSensor(std::string type);

        public slots:
        void search();
        void filter();
    };
}

#endif