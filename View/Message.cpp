#include "Message.h"
#include <QVBoxLayout>

namespace Core {
namespace View {

Message::Message(std::string message) : string(message)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignVCenter | Qt::AlignTop);

    label = new QLabel();
    layout->addWidget(label);

    ok_button = new QPushButton("Ok");
    layout->addWidget(ok_button);
    connect(ok_button, &QPushButton::pressed, this, &Message::close);
    this->show();
}

void Message::show()
{
    label->setText("Messaggio: " + QString::fromStdString(string));
}

void Message::exit()
{
    this->close();
}

};
};