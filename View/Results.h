#ifndef RESULTS
#define RESLUTS

#include <QWidget>

namespace View {

    class Results : public QWidget
    {
        Q_OBJECT
        
        private:
        QWidget* content;

        public:
        Results(QWidget* parent = 0);
    };
};

#endif