#include <QVector>
#include <QFile>
#include <QTextStream>

#include "qcustomplot.h"
#include "funkcje.h"

// Implementacja Matlabowej funkcji linspace
QVector<double> linspace(double start, double end, int howMany)
{
    QVector<double> vec;
    double increment = (end - start) / (howMany - 1);
    for (int i = 0; i < howMany; i++)
        vec.push_back(start + i * increment);
    return vec;
}

double abs(double X)
{
    if (X < 0) return -X;
    return X;
}

void saveToFile(QString fileName, QVector<double> out)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file);
        for (int t =0; t < out.size(); ++t)
            stream << out[t] << endl;
    }
}


void saveToFile(QString fileName, QVector<double> out1, QVector<double> out2)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file);
        for (int t =0; t < out1.size(); ++t)
            stream << out1[t] << " " << out2[t] << endl;
    }
}

QVector<double> modulujAM(QVector<double> c, double kAM, double fM, double fs)
{
    QVector<double> z;
    for ( int t = 0; t < c.size(); ++t)
        z.push_back((kAM * c[t] + 1) * sin(2.0 * M_PI * fM * static_cast<double>(t) / fs));
    // Taki sam wzór jak na tworzenie sygnału sinusoidalnego, z tą różnicą że amplituda ma wzór
    // A = 1 + kAM * c(t)
    return z;
}

QVector<double> modulujPM(QVector<double> c, double kPM, double fM, double fs)
{
    QVector<double> z;
    for (int t = 0; t < c.size(); ++t)
        z.push_back(sin((2.0 * M_PI * fM * t) / fs + kPM * c[t] ) );
        //z.push_back(sin(2.0 * M_PI * fM * static_cast<double>(t) + kPM * c[t] / fs) );
    return z;
}

double max(QVector<double> vec)
{
    double result = vec[0];
    for (int i = 0; i < vec.size(); ++i)
        if (result < vec[i])
            result = vec[i];
    return result;
}

double min(QVector<double> vec)
{
    double result = vec[0];
    for (int i = 0; i < vec.size(); ++i)
        if (result > vec[i] )
            result = vec[i];
    return result;
}

double correctRange(double range)
{
    if (range == 0)
        range += 0.1;
    return range;
}

QCustomPlot* plotFromVectors(QVector<double> x, QVector<double> y)
{
    QCustomPlot *plot = new QCustomPlot;
    QRect rec = QApplication::desktop()->screenGeometry();
    int screenHeight = rec.height() - 100;
    int screenWidth = rec.width() - 100;

    plot->addGraph();
    plot->graph(0)->setData(x, y);
    plot->setFixedSize(screenWidth, screenHeight);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


    double minXBorder = abs(min(x) * 0.1);
    double maxXBorder = abs(max(x) * 0.1);
    double minYBorder = abs(min(y) * 0.1);
    double maxYBorder = abs(max(y) * 0.1);

    minXBorder = correctRange(minXBorder);
    maxXBorder = correctRange(maxXBorder);
    minYBorder = correctRange(minYBorder);
    maxYBorder = correctRange(maxYBorder);

    plot->xAxis->setRange(min(x) - minXBorder, max(x) + maxXBorder );
    plot->yAxis->setRange(min(y) - minYBorder, max(y) + maxYBorder );

    plot->replot();
    plot->show();
    return plot;
}

QCustomPlot* plotFromVector(QVector<double> y)
{
    // najpierw wygeneruj drugi wektor x, bo QCustomPlot potrzebuje
    // dwóch wektorów do rysowania wykresów

    QVector<double> x;
    for(int i = 0; i < y.size(); ++i)
        x.push_back(i);

    QRect rec = QApplication::desktop()->screenGeometry();
    int screenHeight = rec.height() - 100;
    int screenWidth = rec.width() - 100;

    QCustomPlot *plot = new QCustomPlot;
    plot->addGraph();
    plot->graph(0)->setData(x, y);
    plot->setFixedSize(screenWidth,screenHeight);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    QCPAxisRect *rect = new QCPAxisRect(plot);
    rect->setRangeZoomAxes(plot->xAxis, 0);


    double minXBorder = abs(min(x) * 0.1);
    double maxXBorder = abs(max(x) * 0.1);
    double minYBorder = abs(min(y) * 0.1);
    double maxYBorder = abs(max(y) * 0.1);

    minXBorder = correctRange(minXBorder);
    maxXBorder = correctRange(maxXBorder);
    minYBorder = correctRange(minYBorder);
    maxYBorder = correctRange(maxYBorder);

    plot->xAxis->setRange(min(x) - minXBorder, max(x) + maxXBorder );
    plot->yAxis->setRange(min(y) - minYBorder, max(y) + maxYBorder );
    plot->replot();
    plot->show();

    return plot;
}

QVector<double> liczSinF(double A, double f, double time, double fs, double fi )
{
   int N = static_cast<int>(time * fs);
   QVector<double> x;
   for (int t = 0; t < N; ++t)
       x.push_back(liczSinOneF(A, f, t, fs, fi));
   return x;
}

double liczSinOneF(double A, double f, double time, double fs, double fi)
{
    return(A * sin(2.0 * M_PI *  f * time / fs + fi));
}

QString decToBin(int dec)
{
   QString result = "";
   int remainder = 0;

   if (dec <= 0)
       return result = "0";

   while( dec != 0 )
   {
       remainder = dec % 2;
       result.insert(0, QString::number(remainder));    // wsadź na początek stringa resztę z dzielenia całkowitego
       dec /= 2;
   }

   while ( (result.size() % 8) != 0)    // Wypchaj początek stringa zerami jeśli wartość nie jest wielokrotnością 8
   {
        result.insert(0, QString::number(0));
   }

   return result;
}

QString stringToBinaryString(QString str)
{
    QString result = "";
    for (int i = 0; i < str.size(); i++)
    {
        result.append( decToBin(str[i].unicode()) );
    }
    return result;
}
