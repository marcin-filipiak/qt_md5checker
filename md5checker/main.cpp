#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*
    //wyswietlenie parametrow przy wywolaniu programu
    for(int i = 0; i < argc; i++){
        qDebug(argv[1]); // to zostanie wyświetlone w konsoli Qt Creatora
    }
    */


    QApplication a(argc, argv);
    MainWindow w;
    //przekazanie argumentu z ewentualna nazwa pliku
    w.filePath = argv[1];
    //wyswietlenie sumy kontrolnej pliku
    w.checkChecksum();

    w.show();

    return a.exec();
}
