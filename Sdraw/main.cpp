#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <iostream>
int main(int argc, char *argv[])
{
    std::cout<<"argc="<<argc<<"argv="<<argv[0]<<argv[1];
    //QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    if(argc>1)
    {
        w.GetParament(argv[1],argv[2]);
        w.readText();
        w.close();
        a.exit(0);
    }
    else
    {
        return a.exec();
    }

}
