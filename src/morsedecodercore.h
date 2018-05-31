#ifndef MORSEDECODERCORE_H
#define MORSEDECODERCORE_H

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include "eden.h"
#include <QTextStream>
#include <QDebug>
#include "ringbuffer.h"
#include "morseencodercore.h"

using namespace std;

#define SignalBufferSize 100000

class MorseDecoderCore
{
public:
    QString * TextBuf = 0;
    int * TextBufTX = 0;
    MorseEncoderCore * MorseEncoderCore_;
    bool RealTime = false;
    MorseDecoderCore();
    ~MorseDecoderCore();
    map<QString, QString> SymbolDict;
    void BufferClear();
    void BufferAdd(int Val);
    void GetWhole();
    void Calc(int NumElements, int ThresholdFactor, int PauseShortFactor, int PauseLongFactor);
    void Calc();
    void CalcFromLength(int SignalDITlen, int SignalDAHlen);
    Settings * Settings_;

    int SignalThreshold = 0;
    int PauseShortThreshold = 0;
    int PauseLongThreshold = 0;
    int PauseLongThresholdX = 0;

    QString CharBuf;
    void ProcessBuffer();
    void ProcessLast(int SignalCount);

private:
    int AutoCalcI = 0;
    int SignalBuffer[SignalBufferSize];
    int SignalBufferI;
    int SignalBufferO;
    int SignalBufferOLast;
    int SignalBufferCountAll;
    int SignalBufferCountLast;
    int LastChar;
    void SignalBufferPut(int Val);
};

#endif // MORSEDECODERCORE_H
