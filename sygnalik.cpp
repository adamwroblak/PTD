#include "sygnalik.h"
#include "funkcje.h"
#include <QFile>
#include <QTextStream>

sygnalik::sygnalik()
    :A(1), f(5), fs(1000), fi(0) {liczSin(1);}

sygnalik::sygnalik(double Amplituda, int czestotliwosc, double czestotliwoscProbkowania, double kat)
    :A(Amplituda), f(czestotliwosc), fs(czestotliwoscProbkowania), fi(kat) {}

sygnalik::sygnalik(QString stringSignal, MOD_TYPE typModulacji,
                   double czasTrwaniaBitu, int jakasLiczbaNaturalna,
                   double amplituda)
    :A(amplituda), fi(0)
{
    // Od jakiejś liczby naturalnej będzie zależeć częśtotliwość
    // Czas trwania bitu = Tb
    /*Amplitudę, fazę mogę dobrać dowolnie
      częstotliwość, częstotliwość próbkowania, czas całej symulacji muszę obliczyć
      częstotliwość próbkowania to ilość okresów na sekundę
    */
    QTextStream cout(stdout);
    this->fs = 1000; // to chyba też trzeba ustalić w konstruktorze
    switch(typModulacji)
    {
        case MOD_TYPE::ASK :
            this->f = jakasLiczbaNaturalna * 1.0 / czasTrwaniaBitu;
            this->fi = 0;
            for (int i = 0; i < stringSignal.size(); ++i)
            {
                if (stringSignal[i] == '1')
                {
                    QVector<double> xx = liczSinF(A,f,czasTrwaniaBitu,fs,fi);
                    for (int j = 0; j < xx.size(); ++j)
                        this->x.push_back(xx[j]);
                }
                else if(stringSignal[i] == '0')
                {
                    QVector<double> xx = liczSinF(A/2.0,f,czasTrwaniaBitu,fs,fi);
                    for (int k = 0; k < xx.size(); ++k)
                        this->x.push_back(xx[k]);
                }
            }
            break;

            case MOD_TYPE::PSK :
            {
                double fi1 = 0;
                double fi2 = M_PI;
                this->A = 1;
                this->f = jakasLiczbaNaturalna * 1.0 / czasTrwaniaBitu;
                for (int i = 0; i < stringSignal.size(); ++i)
                {
                    if (stringSignal[i] == '1')
                    {
                        QVector<double> xx = liczSinF(A,f,czasTrwaniaBitu,fs,fi1);
                        for (int j = 0; j < xx.size(); ++j)
                            this->x.push_back(xx[j]);
                    }
                    else if(stringSignal[i] == '0')
                    {
                        QVector<double> xx = liczSinF(A,f,czasTrwaniaBitu,fs,fi2);
                        for (int k = 0; k < xx.size(); ++k)
                            this->x.push_back(xx[k]);
                    }
                }
            }
            break;

            case MOD_TYPE::FSK :
            {
                double f1 = (jakasLiczbaNaturalna + 1) / czasTrwaniaBitu;
                double f2 = (jakasLiczbaNaturalna + 2) / czasTrwaniaBitu;
                this->A = 1;
                this->fi = 0;
                for (int i = 0; i < stringSignal.size(); ++i)
                {
                    if (stringSignal[i] == '1')
                    {
                        QVector<double> xx = liczSinF(A,f2,czasTrwaniaBitu,fs,fi);
                        for (int j = 0; j < xx.size(); ++j)
                            this->x.push_back(xx[j]);
                    }
                    else if(stringSignal[i] == '0')
                    {
                        QVector<double> xx = liczSinF(A,f1,czasTrwaniaBitu,fs,fi);
                        for (int k = 0; k < xx.size(); ++k)
                            this->x.push_back(xx[k]);
                    }
                }
            }
            break;
    } // koniec switcha
} // koniec konstruktora

sygnalik::~sygnalik() {}

void sygnalik::liczSin(double time)
{
   N = static_cast<int>(time * fs);
   for (int t = 0; t < N; ++t)
       x.push_back(liczSinOne(t));
}

double sygnalik::liczSinOne(double time)
{
    return(A * sin(2.0 * M_PI *  f * time / fs + fi));
}

void sygnalik::saveToFile(QString outFile)
{
    QFile file(outFile);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file);
        for (int t = 0; t < x.size(); ++t)
            stream << x[t] << endl;
    }
}

void sygnalik::set_fi(double sfi) { fi = sfi;}
double sygnalik::get_fi() const { return fi;}

void sygnalik::set_A(double sA) { A = sA; }
double sygnalik::get_A() const { return A; }

void sygnalik::set_f(int sf) { f = sf; }
int sygnalik::get_f() const { return f; }

void sygnalik::set_fs(double sfs) { fs = sfs; }
double sygnalik::get_fs() const { return fs; }

void sygnalik::set_x(QVector<double> sx) { x = sx; }
QVector<double> sygnalik::get_x() const { return x; }

void sygnalik::set_dftAmpF(QVector<double> val) { dftAmpF = val; }
QVector<double> sygnalik::get_dftAmpF() const { return dftAmpF; }

void sygnalik::set_dftAmpZ(QVector<double> val) { dftAmpZ = val; }
QVector<double> sygnalik::get_dftAmpZ() const { return dftAmpZ; }

void sygnalik::set_dftMocF(QVector<double> val) { dftMocF = val; }
QVector<double> sygnalik::get_dftMocF() const  { return dftMocF; }

void sygnalik::set_dftMocZ(QVector<double> val) { dftMocZ = val; }
QVector<double> sygnalik::get_dftMocZ() const { return dftMocZ; }

void sygnalik::widmoAmplitudowe()
{
    int N = x.size();

    // DFT ----------------------------------------------------------
    double *a = new double[N];
    double *b = new double[N];
    double sum1 = 0;
    double sum2 = 0;

    for (int k = 0; k < N; ++k)
    {
        sum1 = 0;
        sum2 = 0;
        for (int n = 0; n < N; ++n)
        {
            sum1 += x[n] * cos(-2.0 * n * k * M_PI / N);
            sum2 += x[n] * sin(-2.0 * n * k * M_PI / N);
        }
        a[k] = sum1;
        b[k] = sum2;
    }
    //------------------------------------------------------------------

    // Moduł z liczb zespolonych ---------------------------------------
    for (int i = 0; i < N / 2 - 1; ++i) dftAmpZ.push_back(sqrt(a[i] * a[i] + b[i] * b[i]));
    //------------------------------------------------------------------

    // f[i] ------------------------------------------------------------
    for (int i = 0; i < N / 2 - 1; ++i) dftAmpF.push_back(i * fs / N);
    //------------------------------------------------------------------

    delete[] a;
    delete[] b;
}

void sygnalik::widmoMocy()
{
    int N = x.size();

    // DFT ----------------------------------------------------------
    double *a = new double[N];
    double *b = new double[N];
    double sum1 = 0;
    double sum2 = 0;

    for (int k = 0; k < N; ++k)
    {
        sum1 = 0;
        sum2 = 0;
        for (int n = 0; n < N; ++n)
        {
            sum1 += x[n] * cos(-2.0 * n * k * M_PI / N);
            sum2 += x[n] * sin(-2.0 * n * k * M_PI / N);
        }
        a[k] = sum1;
        b[k] = sum2;
    }
    //------------------------------------------------------------------

    // Moduł z liczb zespolonych ---------------------------------------
    for (int i = 0; i < N / 2 - 1; ++i)
    {
        dftMocZ.push_back(a[i] * a[i] + b[i] * b[i]);
        dftMocZ[i] = 10.0 * log10(dftMocZ[i]);
    }

    //------------------------------------------------------------------

    // f[i] ------------------------------------------------------------
    for (int i = 0; i < N / 2 - 1; ++i) dftMocF.push_back(i * fs / N);
    //------------------------------------------------------------------


    double max = dftMocZ[0];
    for (int i = 0; i < dftMocZ.size(); ++i)
    {
        if (max < dftMocZ[i])
            max = dftMocZ[i];
    }
    for (int i = 0; i < dftMocZ.size(); ++i)
    {
        dftMocZ[i] -= max;
    }

    delete[] a;
    delete[] b;
}
