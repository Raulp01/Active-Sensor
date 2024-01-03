#ifndef MESSAGE
#define MESSAGE

#include "../Core/Error.h"
#include <QWidget>
#include <QLabel>
#include <iostream>
#include <QPushButton>

namespace Core {
namespace View {

class Message : public QWidget
{
    Q_OBJECT
    private:
    std::string string;
    QLabel* label;
    QPushButton* ok_button;

    public:
    Message(std::string message);
    void show();

    public slots:
    void exit();
};

};
};

#endif