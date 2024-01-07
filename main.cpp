#include "Core/Container.h"
#include <QApplication>
#include "View/MainWindow.h"

int main(int argc, char* argv[])
{
    Core::Container container;

    //Attività
    Core::Activity activity("Io", "Percorso naturalistico", 22, 1.83, 93, Core::TrainingType::light, 2, 2);
    activity.getAge();
    activity.setAge(18);
    std::cout << "Training type:" << activity.getTrainingType() << std::endl;
    for(int i = 0; i < 10; i++)
    {
        std::cout << "Bpm: " << activity.getBpm() << std::endl;
        std::cout << "Calories: " << activity.getCalories() << std::endl;
        std::cout << "Speed: " << activity.getAvarageSpeed() << std::endl;

        activity.simulate();
    }

    //Conta Calorie
    Core::CaloriesCounter calories("Carlo","Palestra", 43, 1.67, 85, Core::TrainingType::moderate, 1.5);


    //BPM
    Core::HeartSensor heartsens("Il Papa", "Corsa Tapis-roulant", 26, 1.73, 70, Core::TrainingType::maximum, 0.5);

    //Tachimetro
    Core::Speedometer speed("Berlusca", "Maratona", 30, 1.75, 70, Core::TrainingType::high, 3, 42);

    container.add(&calories);
    container.add(&activity);
    container.add(&speed);
    container.add(&heartsens);

    for(auto it = container.vector.begin(); it != container.vector.end(); ++it)
    {
        std::cout << (*it)->getId() << std::endl;
    }

    QApplication app(argc, argv);

    View::MainWindow main_window(activity);

    main_window.resize(1920,1080);

    main_window.show();

    return app.exec();
}