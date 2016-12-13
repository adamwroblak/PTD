#include <QApplication>
#include "sygnalik.h"
#include "funkcje.h"
#include "qcustomplot.h"
#include <QInputDialog>



int main(int argc, char **argv)
{

    QApplication app(argc, argv);
/*
    sygnalik modSignalPSK("10110011", sygnalik::MOD_TYPE::PSK, 0.125, 2); // utwórz sygnał zmodulowany
    sygnalik modSignalASK("10110110011", sygnalik::MOD_TYPE::ASK, 0.125, 2);
    sygnalik modSignalFSK("10110011", sygnalik::MOD_TYPE::FSK, 0.125, 2);
    plotFromVector(modSignalPSK.get_x()); // narysuj i pokaż
    plotFromVector(modSignalASK.get_x()); // narysuj i pokaż
    plotFromVector(modSignalFSK.get_x()); // narysuj i pokaż
*/
    QTextStream cin(stdin);
    QTextStream cout(stdout);

    QInputDialog dialog;
    double liczba = dialog.getDouble(0,"Dajesz malina", "Podaj jakas liczbe");
    cout << "Podales " << liczba << endl;




    return app.exec();
}
