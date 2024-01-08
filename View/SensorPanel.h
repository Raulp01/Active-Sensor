#ifndef PANEL
#define PANEL

#include "Info.h"
#include "Scrollbar.h"
namespace View
{
    class SensorPanel : public QWidget
    {
        Q_OBJECT

        private:
        Core::Sensor& sensor;
        Scrollbar* scrollbar;
        QLabel* artwork;
        Info* info;

        public:
        SensorPanel(Scrollbar* scrollbar, Core::Sensor& sensor, QWidget* parent = 0);

        // Solo dichiarazione: la funzione chiama la MainWindow per aprire sul lato il viewer
        Core::Sensor* getSensor();

        public slots:
        void openViewer();
    };
};

#endif