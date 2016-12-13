#ifndef SYGNALIK_H
#define SYGNALIK_H
#include <QString>
#include <QVector>
class sygnalik
{
public:
    enum MOD_TYPE{ASK, PSK, FSK};
    sygnalik();
    sygnalik(double Amplituda, int czestotliwosc, double czestotliwoscProbkowania, double kat = 0 );	// amplituda, częstotliwość, częstotliwość próbkowania, kąt
    sygnalik(QString stringSignal,
             MOD_TYPE typModulacji,
             double czasTrwaniaBitu,
             int jakasLiczbaNaturalna,
             double amplituda = 1.0);
    ~sygnalik();
    void liczSin(double time);
    double liczSinOne(double time);
    void widmoAmplitudowe();
    void widmoMocy();
    void saveToFile(QString outFile);

    void set_fi(double);
    double get_fi() const;

    void set_A(double);
    double get_A() const;

    void set_f(int sf);
    int get_f() const;

    void set_fs(double sfs);
    double get_fs() const;

    void set_x(QVector<double> sx);
    QVector<double> get_x() const;

    void set_dftAmpF(QVector<double> val);
    QVector<double> get_dftAmpF() const;

    void set_dftAmpZ(QVector<double> val);
    QVector<double> get_dftAmpZ() const;

    void set_dftMocF(QVector<double> val);
    QVector<double> get_dftMocF() const;

    void set_dftMocZ(QVector<double> val);
    QVector<double> get_dftMocZ() const;




private:
    double A;
    int f;
    double fs;
    double fi;
    int N;
    QVector<double> x;

    QVector<double> dftAmpF;
    QVector<double> dftAmpZ;

    QVector<double> dftMocF;
    QVector<double> dftMocZ;
};


#endif // SYGNALIK_H
