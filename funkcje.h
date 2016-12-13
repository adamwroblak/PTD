#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <QString>
#include "qcustomplot.h"

QVector<double> linspace(double start, double end, int howMany);
void saveToFile(QString fileName, QVector<double> out);
void saveToFile(QString fileName, QVector<double> out1, QVector<double> out2);
QVector<double> modulujAM(QVector<double> c, double kAM, double fM, double fs);
QVector<double> modulujPM(QVector<double> c, double kPM, double fM, double fs);
double max(QVector<double> vec);
double min(QVector<double> vec);
QCustomPlot* plotFromVectors(QVector<double> x, QVector<double> y);
QCustomPlot* plotFromVector(QVector<double> y);
double correctRange(double range);
QVector<double> liczSinF(double A, double f, double time, double fs, double fi );
double liczSinOneF(double A, double f, double time, double fs, double fi);
QString decToBin(int dec);
QString stringToBinaryString(QString str);

#endif // FUNKCJE_H
