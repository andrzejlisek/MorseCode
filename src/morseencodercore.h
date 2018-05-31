#ifndef MORSEENCODERCORE_H
#define MORSEENCODERCORE_H

#include "eden.h"
#include <cmath>
#include <iostream>
#include <map>
#include <list>
#include <QTextStream>
#include "settings.h"

using namespace std;

#define MaxPeriodSize 5000

class MorseEncoderCore
{
public:
    QString * TextBuf = 0;
    int * TextBufTX = 0;
    int TransferDirection = 0;
    int WPMStandardSize[2];
    map<QString, QString> SymbolDict;
    MorseEncoderCore();
    ~MorseEncoderCore();
    void GetSamples(short * Smp, int ChunkSize);
    float AudioPeriodArray[MaxPeriodSize];
    int AudioPeriodL = 0;
    int AudioPeriodI = 0;
    void CalcPeriod(float FreqL, float FreqH);
    void CalcSignal(int SignalDIT, int SignalDAH);
    void CalcFromWPM(int WPM);
    int SignalLength = 0;
    int SignalLengthI;
    void Send(QString X);
    list<char> Buffer;
    char CurrentSignal;
    fstream * Ftest;
    Settings * Settings_;
    int CalcWPM;
    int TransmitStateI;
    int CalcSignalDITlen = 0;
    int CalcSignalDAHlen = 0;
    double Amplitude = 0;
    float LastFreqL = 0;
    float LastFreqH = 0.5;
    float LastAudioPeriod = 4;

    llong CurrentSample = 0;

    list<llong> BufQueueT;
    list<QString> BufQueueS;

    void BufReset();
    void ProcessBuffer();
};

#endif // MORSEENCODERCORE_H
