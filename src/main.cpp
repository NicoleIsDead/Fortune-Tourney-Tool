//MIT License
//Copyright (c) 2021 NicoleIsDead
//https://github.com/NicoleIsDead

#include "constants.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
	system("echo %cd%");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
