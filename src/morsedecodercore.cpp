#include "morsedecodercore.h"

MorseDecoderCore::MorseDecoderCore()
{
    // Loading symbol dictionary
    string FileName = Eden::ApplicationDirectory() + "Symbols.txt";
    QFile file(Eden::ToQStr(FileName));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        while(!in.atEnd())
        {
            QString line = in.readLine();
            SymbolDict[line.split('\t')[0]] = line.split('\t')[1].split('|')[0];
        }
    }
    BufferClear();
}

MorseDecoderCore::~MorseDecoderCore()
{

}

void MorseDecoderCore::SignalBufferPut(int Val)
{
    SignalBuffer[SignalBufferI] = Val;
    SignalBufferI++;
    if (SignalBufferI == SignalBufferSize)
    {
        SignalBufferI = 0;
    }
    SignalBufferCountAll++;
    SignalBufferCountLast++;
    if (SignalBufferCountAll == SignalBufferSize)
    {
        SignalBufferO++;
        if (SignalBufferO == SignalBufferSize)
        {
            SignalBufferO = 0;
        }
        SignalBufferCountAll--;
    }
    if (SignalBufferCountLast == SignalBufferSize)
    {
        SignalBufferOLast++;
        if (SignalBufferOLast == SignalBufferSize)
        {
            SignalBufferOLast = 0;
        }
        SignalBufferCountLast--;
    }
}


///
/// \brief MorseDecoderCore::BufferClear - Clearing buffer
///
void MorseDecoderCore::BufferClear()
{
    if (TextBuf != 0)
    {
        TextBuf->clear();
    }
    CharBuf.clear();
    LastChar = 0;
    SignalBufferI = 0;
    SignalBufferO = 0;
    SignalBufferOLast = 0;
    SignalBufferCountAll = 0;
    SignalBufferCountLast = 0;
}

///
/// \brief MorseDecoderCore::BufferAdd - Adding element to buffer
/// \param Val
///
void MorseDecoderCore::BufferAdd(int Val)
{
    // Val > 0 => Signal length.
    // Val < 0 => Break length.
    // Val = 0 => Once, only after positive value, as a information o posibility to decode last signal
    if ((Val > 0) || (Val < 0))
    {
        LastChar = Val;
        SignalBufferPut(Val);
    }
    if (Val == 0)
    {
        if (LastChar > 0)
        {
            LastChar = 0;
            SignalBufferPut(0);
        }
    }

    if (SignalBufferCountLast > 0)
    {
        if (SignalThreshold > 0)
        {
            if (RealTime)
            {
                ProcessBuffer();
            }
        }
    }

    if (Settings_->AutoCalcC)
    {
        if (Val > 0)
        {
            AutoCalcI++;
            if (AutoCalcI >= Settings_->AutoCalc)
            {
                Calc();
                AutoCalcI = 0;
            }
        }
    }
    else
    {
        AutoCalcI = 0;
    }
}

void MorseDecoderCore::ProcessBuffer()
{
    while (SignalBufferCountLast > 0)
    {
        int Val = SignalBuffer[SignalBufferOLast];
        SignalBufferOLast++;
        if (SignalBufferOLast == SignalBufferSize)
        {
            SignalBufferOLast = 0;
        }
        SignalBufferCountLast--;


        if (Val > 0)
        {
            if (Val < SignalThreshold)
            {
                CharBuf.append(".");
            }
            else
            {
                CharBuf.append("-");
            }
        }
        else
        {
            if ((Val < PauseShortThreshold) || (Val == 0))
            {
                QString TextBufTemp = "";
                if (CharBuf.size() > 0)
                {
                    if (SymbolDict.count(CharBuf) > 0)
                    {
                        TextBufTemp.append(SymbolDict[CharBuf]);
                    }
                    else
                    {
                        TextBufTemp.append("{");
                        TextBufTemp.append(CharBuf);
                        TextBufTemp.append("}");
                    }
                    CharBuf.clear();
                }
                if (Val < PauseLongThreshold)
                {
                    TextBufTemp.append(" ");
                }


                if (TextBufTemp != "")
                {
                    if (TextBufTX[0] == 1)
                    {
                        TextBuf->append("\r\n");
                    }
                    TextBufTX[0] = 2;
                    TextBuf->append(TextBufTemp);
                }
            }
        }
    }
    //SignalBuffer.PointerO = TempPointer;
}

///
/// \brief MorseDecoderCore::Calc - Obliczanie parametrow dekodowania
///
void MorseDecoderCore::Calc()
{
    int NumElements = Settings_->CalcMorseLastSignals;
    if (NumElements <= 0) { return; };
    if (Settings_->CalcPauseShortFactor <= 0) { return; };
    if (Settings_->CalcPauseLongFactor <= 0) { return; };

    map<int,int> Stats;
    std::map<int, int>::iterator StatsI;

    // Counting single signal lengths
    bool Good = false;
    int LenMin = -1;
    int LenMax = -1;

    int BufCountI = SignalBufferCountAll;
    int SignalBufferI_ = SignalBufferI;
    while ((BufCountI >= 0) && (NumElements > 0))
    {
        int Val = SignalBuffer[SignalBufferI_];
        if (Val > 0)
        {
            Good = true;
            if (Stats.count(Val) > 0)
            {
                LenMin = Val;
                LenMax = Val;
                Stats[Val]++;
            }
            else
            {
                Stats[Val] = 0;
            }
            NumElements--;
        }
        BufCountI--;
        if (SignalBufferI_ == 0)
        {
            SignalBufferI_ = SignalBufferSize;
        }
        SignalBufferI_--;
    }

    // If there is no enough data, calculating is not possible
    if (!Good)
    {
        return;
    }


    // Searching minimal and maximal length
    for(StatsI = Stats.begin(); StatsI != Stats.end(); StatsI++)
    {
        int K = StatsI->first;
        if (LenMin > K) { LenMin = K; }
        if (LenMax < K) { LenMax = K; }
    }

    // Calculating theoretical DIT/DAH threshold
    SignalThreshold = LenMin + (((LenMax - LenMin) * Settings_->CalcMorseLengthFactor) / 100);

    // Searching dominant length both above (DAH) and below (DIT) length threshold
    int SignalDITlen = LenMin;
    int SignalDITmax = 0;
    int SignalDAHlen = LenMax;
    int SignalDAHmax = 0;
    for(StatsI = Stats.begin(); StatsI != Stats.end(); StatsI++)
    {
        int K = StatsI->first;
        int V = StatsI->second;
        if (K < SignalThreshold)
        {
            if (SignalDITmax < V)
            {
                SignalDITmax = V;
                SignalDITlen = K;
            }
        }
        else
        {
            if (SignalDAHmax < V)
            {
                SignalDAHmax = V;
                SignalDAHlen = K;
            }
        }
    }

    // Calculating length thresholds based on signal lengths
    CalcFromLength(SignalDITlen, SignalDAHlen);

    // Calculating generator parameters
    MorseEncoderCore_->CalcSignal(SignalDITlen, SignalDAHlen);
}

///
/// \brief MorseDecoderCore::CalcFromWPM - Calculating parameters based on signal lengths
/// \param SignalDITlen
/// \param SignalDAHlen
///
void MorseDecoderCore::CalcFromLength(int SignalDITlen, int SignalDAHlen)
{
    // Calculating threshold based on signal lengths
    SignalThreshold = SignalDITlen + (((SignalDAHlen - SignalDITlen) * Settings_->CalcMorseLengthFactor) / 100);

    // Calculating length threshold based on DIT signal
    PauseShortThreshold = 0 - ((SignalDITlen * Settings_->CalcPauseShortFactor) / 100);
    PauseLongThreshold = 0 - ((SignalDITlen * Settings_->CalcPauseLongFactor) / 100);
    PauseLongThresholdX = (0 - PauseLongThreshold) / 100;
}

///
/// \brief MorseDecoderCore::GetWhole - Processing whole buffer
///
void MorseDecoderCore::GetWhole()
{
    CharBuf.clear();
    SignalBufferOLast = SignalBufferO;
    SignalBufferCountLast = SignalBufferCountAll;
    TextBuf->append("\r\n");
    ProcessBuffer();
}

///
/// \brief MorseDecoderCore::ProcessLast - Processing last signals
/// \param SignalCount
///
void MorseDecoderCore::ProcessLast(int SignalCount)
{
    if (SignalCount <= 0) { return; }
    if (PauseShortThreshold >= 0) { return; }
    if (PauseLongThreshold >= 0) { return; }
    int PauseSignal = max(PauseShortThreshold, PauseLongThreshold);

    // At starting process, there is place after last signal
    SignalBufferOLast = SignalBufferI;
    SignalBufferCountLast = 0;
    int ProcessSignalCount = 0;

    // Encounting signals from last signal
    int Work = 1;
    while (Work > 0)
    {
        if (Work == 1)
        {
            if (SignalBuffer[SignalBufferOLast] > 0)
            {
                ProcessSignalCount++;
            }
            if (ProcessSignalCount >= SignalCount)
            {
                Work = 2;
            }
        }
        if (Work == 2)
        {
            if (SignalBuffer[SignalBufferOLast] <= PauseSignal)
            {
                Work = 0;
            }
        }
        if (SignalBufferCountLast >= SignalBufferCountAll)
        {
            Work = 0;
        }
        if (Work > 0)
        {
            if (SignalBufferOLast == 0)
            {
                SignalBufferOLast = SignalBufferSize;
            }
            SignalBufferOLast--;
            SignalBufferCountLast++;
        }
    }

    CharBuf.clear();
    TextBuf->append("\r\n");
    ProcessBuffer();
}
