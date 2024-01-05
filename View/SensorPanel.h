#ifndef PANEL
#define PANEL

#include "SensorInfo.h"

namespace View
{
    class SensorPanel : public QWidget
    {
        Q_OBJECT

        private:
        Core::Sensor& sensor;
        QLabel* artwork;
        Info* info;

        public:
        SensorPanel(Core::Sensor& sensor, QWidget* parent = 0);

        // Solo dichiarazione: la funzione chiama la MainWindow per aprire sul lato il viewer
        void openViewer();

        signals:
        // onclick su this apre il viewer (openViewer) con le informazioni aggiuntive
    };
};

#endif