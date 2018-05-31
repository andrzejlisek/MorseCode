#include "morseencodercore.h"

MorseEncoderCore::MorseEncoderCore()
{
    BufQueueT.clear();
    BufQueueS.clear();


    TransmitStateI = 0;

    // PARIS
    WPMStandardSize[0] = 50;

    // CODEX
    WPMStandardSize[1] = 60;

    CalcWPM = 0;

    // Loading symbol dictionary
    string FileName = Eden::ApplicationDirectory() + "Symbols.txt";
    QFile file(Eden::ToQStr(FileName));
    int I;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QString Val = line.split('\t')[0];
            QStringList Token = line.split('\t')[1].split('|');
            for (I = 0; I < Token.length(); I++)
            {
                if (Token[I].startsWith("[") && Token[I].endsWith("]"))
                {
                    SymbolDict[Token[I].toUpper()] = Val;
                }
                else
                {
                    SymbolDict[Token[I]] = Val;
                }
            }
        }
    }
    SignalLengthI = 0;
    Buffer.clear();
    CurrentSignal = 0;
}

MorseEncoderCore::~MorseEncoderCore()
{
}

///
/// \brief MorseEncoderCore::CalcSignal - Calculating signal length
/// \param SignalDIT - DIT signal = number_of_samples * 100
/// \param SignalDAH - DAH signal - number_of_samples * 100
///
void MorseEncoderCore::CalcSignal(int SignalDIT, int SignalDAH)
{
    //SignalDIT = 76800;
    //SignalDAH = 208000;

    // Correcting signal length to get 1:3 DIT/DAH radio
    // This value is in sound samples
    int SignalLength_ = (SignalDIT + ((SignalDAH - (3 * SignalDIT)) / 2)) / 100;

    // Calculating number of characters per minute
    float CalcWPM1 = Settings_->SampleRate * 300;
    float CalcWPM2 = SignalLength_ * WPMStandardSize[Settings_->MorseWPMStandard];
    CalcWPM = roundf(CalcWPM1 / CalcWPM2);
}

void MorseEncoderCore::CalcFromWPM(int WPM)
{
    if (WPM < 0)
    {
        WPM = 0 - WPM;
    }
    if (WPM == 0)
    {
        CalcSignalDITlen = 0;
        CalcSignalDAHlen = 0;
        return;
    }

    Settings_->MorseWPM = WPM;

    // Calculating length of DIT signal
    float WPM_ = WPM;
    float CalcWPM1 = Settings_->SampleRate * 300 * 100;
    float CalcWPM2 = CalcWPM1 / WPM_;
    int SignalLength_ = (CalcWPM2) / WPMStandardSize[Settings_->MorseWPMStandard];
    CalcSignalDITlen = SignalLength_;

    // Length of DAH equals three times of length of DIT
    CalcSignalDAHlen = CalcSignalDITlen * 3;
}

///
/// \brief MorseEncoderCore::CalcPeriod - Generating one period sample array
/// \param FreqL - Lower filter bound from 0.0 too 0.5
/// \param FreqH - Upper filter bound from 0.0 too 0.5
/// \param SampleRate - Sample rate
///
void MorseEncoderCore::CalcPeriod(float FreqL, float FreqH)
{
    if ((FreqL < 0) || (FreqH < 0))
    {
        LastFreqL = FreqL;
        LastFreqH = FreqH;
    }
    else
    {
        FreqL = LastFreqL;
        FreqH = LastFreqH;
    }

    float AudioPeriod = 1 / ((FreqL + FreqH) / 2);

    if (Settings_->GeneratorFreqEnable)
    {
        float F1 = Settings_->SampleRate;
        float F2 = Settings_->GeneratorFreq;
        AudioPeriod = F1 / F2;
    }

    if (AudioPeriod == LastAudioPeriod)
    {
        return;
    }

    float MaxSize = MaxPeriodSize;
    float Periods = floor(MaxSize / AudioPeriod);
    float TabSize = floor(AudioPeriod * Periods);

    AudioPeriodL = TabSize;
    AudioPeriodI = 0;
    float I_;
    for (int I = 0; I < AudioPeriodL; I++)
    {
        I_ = I;
        I_ = (I_ * Periods) / TabSize;
        AudioPeriodArray[I] = sinf((2.0 * (3.1415926535897932384626433832795)) * I_);
    }

    LastAudioPeriod = AudioPeriod;
}

///
/// \brief MorseEncoderCore::GetSamples - Generating samples to play
/// \param Smp - Sample buffer
/// \param ChunkSize - Number of samples
///
void MorseEncoderCore::GetSamples(short *Smp, int ChunkSize)
{
    double AmplitudeFade = Settings_->TransmitSignalFade;
    if (AmplitudeFade < 0)
    {
        AmplitudeFade = 0;
    }
    else
    {
        AmplitudeFade = AmplitudeFade / 1000000.0;
    }
    float Vol = Settings_->MorseVolume * 320;
    CurrentSample += ChunkSize;
    if (Settings_->MorseTestMode)
    {
        for (int I = 0; I < ChunkSize; I++)
        {
            Smp[I] += (AudioPeriodArray[AudioPeriodI] * Vol);
            AudioPeriodI++;
            if (AudioPeriodI >= AudioPeriodL)
            {
                AudioPeriodI = 0;
            }
        }
    }
    else
    {
        for (int I = 0; I < ChunkSize; I++)
        {
            bool IsSignal = false;
            if (CurrentSignal == 0)
            {
                if (Buffer.size() > 0)
                {
                    if (TransmitStateI < Settings_->MuteTransmitC)
                    {
                        TransmitStateI = Settings_->MuteTransmitC;
                    }
                    TransmitStateI += SignalLength;
                    CurrentSignal = Buffer.front();
                    SignalLengthI = SignalLength;
                }
            }

            if (CurrentSignal > 0)
            {
                if (CurrentSignal == 2)
                {
                    IsSignal = true;
                }
                SignalLengthI--;
                if (SignalLengthI == 0)
                {
                    if (Buffer.size() > 0)
                    {
                        Buffer.pop_front();
                    }
                    CurrentSignal = 0;
                }
            }

            if (IsSignal)
            {
                Amplitude += AmplitudeFade;
                if (Amplitude > 1.0)
                {
                    Amplitude = 1.0;
                }
            }
            else
            {
                Amplitude -= AmplitudeFade;
                if (Amplitude < 0.0)
                {
                    Amplitude = 0.0;
                }
            }
            Smp[I] += (AudioPeriodArray[AudioPeriodI] * Vol * Amplitude);
            AudioPeriodI++;
            if (AudioPeriodI >= AudioPeriodL)
            {
                AudioPeriodI = 0;
            }
        }
    }
}

void MorseEncoderCore::BufReset()
{
    CurrentSample = 0;
    BufQueueS.clear();
    BufQueueT.clear();
    Buffer.clear();
}

void MorseEncoderCore::ProcessBuffer()
{
    QString OutText = "";

    bool Work = (BufQueueS.size() > 0);
    if (Work)
    {
        Work = (BufQueueT.front()) < CurrentSample;
    }
    while (Work)
    {
        OutText.append(BufQueueS.front());
        BufQueueS.pop_front();
        BufQueueT.pop_front();
        Work = (BufQueueS.size() > 0);
        if (Work)
        {
            Work = (BufQueueT.front()) < CurrentSample;
        }
    }

    if (OutText.size() > 0)
    {
        if (TextBufTX[0] == 2)
        {
            TextBuf->append("\r\n");
        }
        TextBufTX[0] = 1;
        TextBuf->append(OutText);
    }
}

void MorseEncoderCore::Send(QString X)
{
    int UsedWPM;
    if (Settings_->MorseWPM <= 0)
    {
        if (CalcWPM > 0)
        {
            UsedWPM = CalcWPM;
            Settings_->MorseWPM = 0 - CalcWPM;
        }
        else
        {
            UsedWPM = 0 - Settings_->MorseWPM;
        }
    }
    else
    {
        UsedWPM = Settings_->MorseWPM;
    }

    if (UsedWPM <= 0)
    {
        return;
    }

    // Removing all end-of-line characters
    X.remove(QRegExp("[\\n\\t\\r]"));

    // Writing sending text to display buffer
    float SampleLatency = Settings_->SampleRate * Settings_->TransmitBufLatency;
    SampleLatency = SampleLatency / 1000.0;
    BufQueueT.push_back(CurrentSample + SampleLatency);
    BufQueueS.push_back(X);


    float SignalLength1 = Settings_->SampleRate * 300;
    float SignalLength2 = UsedWPM * WPMStandardSize[Settings_->MorseWPMStandard];
    SignalLength = roundf(SignalLength1 / SignalLength2);

    int I = 0;
    int J;
    int L = X.length();
    QString X_ = X.toUpper();
    QString T;
    while (I < L)
    {
        if (X.at(I) == ' ')
        {
            Buffer.push_back(1);
            Buffer.push_back(1);
            Buffer.push_back(1);
            Buffer.push_back(1);
        }
        else
        {
            if (X.at(I) == '[')
            {
                I++;
                T = "";
                while ((I < L) && (X.at(I) != ']'))
                {
                    T += X_.at(I);
                    I++;
                }
                if (T.size() > 0)
                {
                    T = SymbolDict["[" + T + "]"];

                    if (T.size() > 0)
                    {
                        for (J = 0; J < T.size(); J++)
                        {
                            if (T.at(J) == '-')
                            {
                                Buffer.push_back(2);
                                Buffer.push_back(2);
                                Buffer.push_back(2);
                                Buffer.push_back(1);
                            }
                            if (T.at(J) == '.')
                            {
                                Buffer.push_back(2);
                                Buffer.push_back(1);
                            }
                        }
                        Buffer.push_back(1);
                        Buffer.push_back(1);
                    }
                }
            }
            else
            {
                if (X.at(I) == '{')
                {
                    I++;
                    while ((I < L) && (X.at(I) != '}'))
                    {
                        if (X_.at(I) == '.')
                        {
                            Buffer.push_back(2);
                            Buffer.push_back(1);
                        }
                        if (X_.at(I) == '-')
                        {
                            Buffer.push_back(2);
                            Buffer.push_back(2);
                            Buffer.push_back(2);
                            Buffer.push_back(1);
                        }
                        I++;
                    }
                    Buffer.push_back(1);
                    Buffer.push_back(1);
                }
                else
                {
                    T = X.at(I);
                    T = SymbolDict[T];
                    if (T.size() > 0)
                    {
                        for (J = 0; J < T.size(); J++)
                        {
                            if (T.at(J) == '-')
                            {
                                Buffer.push_back(2);
                                Buffer.push_back(2);
                                Buffer.push_back(2);
                                Buffer.push_back(1);
                            }
                            if (T.at(J) == '.')
                            {
                                Buffer.push_back(2);
                                Buffer.push_back(1);
                            }
                        }
                        Buffer.push_back(1);
                        Buffer.push_back(1);
                    }
                }
            }
        }
        I++;
    }
}
