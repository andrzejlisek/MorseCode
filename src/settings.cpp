#include "settings.h"

Settings::Settings()
{
    string Buf;
    vector<string> SpectrumPaletteText;
    vector<string> SpectrumPaletteTextX;

    fstream FSpectrum(Eden::ApplicationDirectory() + "Palette.txt", ios::in);
    if (FSpectrum.is_open())
    {
        stringstream SS;
        SS << FSpectrum.rdbuf();
        Buf = SS.str();

        SplitTextToLines(Buf, SpectrumPaletteText, false);
        SpectrumPaletteFile.clear();
        SpectrumPaletteColumn.clear();
        SpectrumPaletteLine1.clear();
        SpectrumPaletteLine2.clear();
        SpectrumPaletteName.clear();
        for (uint I = 0; I < SpectrumPaletteText.size(); I++)
        {
            SpectrumPaletteTextX.clear();
            Eden::StringSplit(SpectrumPaletteText[I], '|', SpectrumPaletteTextX);
            if (SpectrumPaletteTextX.size() >= 5)
            {
                SpectrumPaletteFile.push_back(SpectrumPaletteTextX[0]);
                SpectrumPaletteColumn.push_back(Eden::ToInt(SpectrumPaletteTextX[1]));
                SpectrumPaletteLine1.push_back(Eden::ToInt(SpectrumPaletteTextX[2]));
                SpectrumPaletteLine2.push_back(Eden::ToInt(SpectrumPaletteTextX[3]));
                SpectrumPaletteName.push_back(SpectrumPaletteTextX[4]);
            }
        }
        FSpectrum.close();
    }

    fstream FM(Eden::ApplicationDirectory() + "SetMark.txt", ios::in);
    if (FM.is_open())
    {
        stringstream SS;
        SS << FM.rdbuf();
        SpectrogramMarkers = SS.str();
        FM.close();
    }

    CF.FileLoad(Eden::ApplicationDirectory() + "Settings.txt");


    CF.ParamGet("DeviceI", DeviceI);
    CF.ParamGet("DeviceO", DeviceO);

    CF.ParamGet("PlayerInputChunkSize", PlayerInputChunkSize_MS);
    CF.ParamGet("AudioBufferP", AudioBufferP_MS);
    CF.ParamGet("AudioBufferR", AudioBufferR_MS);
    CF.ParamGet("RefreshPeriod", RefreshPeriod);
    CF.ParamGet("PlayerEnabled", PlayerEnabled);
    CF.ParamGet("SampleRate", SampleRate);
    CF.ParamGet("FileAudioWork", FileAudioWork);
    CF.ParamGet("FileAudioName", FileAudioName);
    CF.ParamGet("RecordFileName", RecordFileName);

    CF.ParamGet("MorseWPM", MorseWPM);
    CF.ParamGet("MorseWPMStandard", MorseWPMStandard);
    CF.ParamGet("MorseVolume", MorseVolume);
    CF.ParamGet("MorseTestMode", MorseTestMode);

    CF.ParamGet("CalcMorseLastSignals", CalcMorseLastSignals);
    CF.ParamGet("CalcMorseLengthFactor", CalcMorseLengthFactor);
    CF.ParamGet("CalcPauseShortFactor", CalcPauseShortFactor);
    CF.ParamGet("CalcPauseLongFactor", CalcPauseLongFactor);
    CF.ParamGet("AutoCalcC", AutoCalcC);
    CF.ParamGet("AutoCalc", AutoCalc);
    CF.ParamGet("MorseBufferLast", MorseBufferLast);

    CF.ParamGet("MuteTransmitC", MuteTransmitC_MS);
    CF.ParamGet("MuteTransmit", MuteTransmit);
    CF.ParamGet("TransmitBufLatency", TransmitBufLatency);
    CF.ParamGet("TransmitSignalFade", TransmitSignalFade_MS);

    CF.ParamGet("SpectrogramStrip", SpectrogramStrip);
    CF.ParamGet("SpectrogramLayoutSize", SpectrogramLayoutSize);
    CF.ParamGet("SpectrogramLayoutOrientation", SpectrogramLayoutOrientation);
    CF.ParamGet("SpectrogramScrollCycle", SpectrogramScrollCycle);
    CF.ParamGet("DisplayGamma", DisplayGamma);

    CF.ParamGet("AudioFileBuffer", AudioFileBuffer);

    CF.ParamGet("PlaybackMode", PlaybackMode);
    CF.ParamGet("PlaybackBufCompensation", PlaybackBufCompensation);
    CF.ParamGet("PlaybackBufSizeMin", PlaybackBufSizeMin_MS);
    CF.ParamGet("PlaybackBufSizeMax", PlaybackBufSizeMax_MS);

    CF.ParamGet("SpectrogramStripColorR", SpectrogramStripColorR);
    CF.ParamGet("SpectrogramStripColorG", SpectrogramStripColorG);
    CF.ParamGet("SpectrogramStripColorB", SpectrogramStripColorB);

    CF.ParamGet("SpectrogramNegative", SpectrogramNegative);
    CF.ParamGet("SpectrogramMouseGraph", SpectrogramMouseGraph);
    CF.ParamGet("SpectrogramMouseButtons", SpectrogramMouseButtons);
    CF.ParamGet("SpectrogramMarkersEnable", SpectrogramMarkersEnable);

    CF.ParamGet("CalcDecimation", CalcDecimation);
    CF.ParamGet("CalcDecimationConst", CalcDecimationConst);

    CF.ParamGet("OverloadThreshold", OverloadThreshold);
    CF.ParamGet("OverloadColorR", OverloadColorR);
    CF.ParamGet("OverloadColorG", OverloadColorG);
    CF.ParamGet("OverloadColorB", OverloadColorB);

    CF.ParamGet("GeneratorFreqEnable", GeneratorFreqEnable);
    CF.ParamGet("GeneratorFreq", GeneratorFreq);

    CF.ParamGet("HalfMarkSize", HalfMarkSize);
    CF.ParamGet("HalfMarkColorR", HalfMarkColorR);
    CF.ParamGet("HalfMarkColorG", HalfMarkColorG);
    CF.ParamGet("HalfMarkColorB", HalfMarkColorB);

    CF.ParamGet("SpectrumDisplayR", SpectrumDisplayR);
    CF.ParamGet("SpectrumDisplayG", SpectrumDisplayG);
    CF.ParamGet("SpectrumDisplayB", SpectrumDisplayB);

    CF.ParamGet("StereoMode", StereoMode);

    CF.ParamGet("FiltersEnabled", FiltersEnabled);
    CF.ParamGet("DrawFil", DrawFil);
    CF.ParamGet("DrawRef", DrawRef);

    CF.ParamGet("FilterSize", FilterSize);

    CF.ParamGet("SpectrumPaletteSelected", SpectrumPaletteSelected);

    CF.ParamGet("VisibleSpectrogramG", VisibleSpectrogramG);
    CF.ParamGet("VisibleProcG", VisibleProcG);
    CF.ParamGet("VisibleBufG", VisibleBufG);
    CF.ParamGet("VisibleBufSpeedG", VisibleBufSpeedG);
    CF.ParamGet("VisibleMorseG", VisibleMorseG);

    CF.ParamGet("RepaintBufferSize", RepaintBufferSize_S);
    CF.ParamGet("RepaintTimeout", RepaintTimeout);

    CF.ParamGet("ReplayBufferSize", ReplayBufferSize_S);
}

Settings::~Settings()
{
    fstream FM(Eden::ApplicationDirectory() + "SetMark.txt", ios::out);
    if (FM.is_open())
    {
        FM << SpectrogramMarkers;
        FM.close();
    }

    CF.ParamClear();
    CF.ParamSet("DeviceI", DeviceI);
    CF.ParamSet("DeviceO", DeviceO);

    CF.ParamSet("PlayerInputChunkSize", PlayerInputChunkSize_MS);
    CF.ParamSet("AudioBufferP", AudioBufferP_MS);
    CF.ParamSet("AudioBufferR", AudioBufferR_MS);
    CF.ParamSet("RefreshPeriod", RefreshPeriod);
    CF.ParamSet("PlayerEnabled", PlayerEnabled);
    CF.ParamSet("SampleRate", SampleRate);
    CF.ParamSet("FileAudioWork", FileAudioWork);
    CF.ParamSet("FileAudioName", FileAudioName);
    CF.ParamSet("RecordFileName", RecordFileName);

    CF.ParamSet("MorseWPM", MorseWPM);
    CF.ParamSet("MorseWPMStandard", MorseWPMStandard);
    CF.ParamSet("MorseVolume", MorseVolume);
    CF.ParamSet("MorseTestMode", MorseTestMode);

    CF.ParamSet("CalcMorseLastSignals", CalcMorseLastSignals);
    CF.ParamSet("CalcMorseLengthFactor", CalcMorseLengthFactor);
    CF.ParamSet("CalcPauseShortFactor", CalcPauseShortFactor);
    CF.ParamSet("CalcPauseLongFactor", CalcPauseLongFactor);
    CF.ParamSet("AutoCalcC", AutoCalcC);
    CF.ParamSet("AutoCalc", AutoCalc);
    CF.ParamSet("MorseBufferLast", MorseBufferLast);

    CF.ParamSet("MuteTransmitC", MuteTransmitC_MS);
    CF.ParamSet("MuteTransmit", MuteTransmit);
    CF.ParamSet("TransmitBufLatency", TransmitBufLatency);
    CF.ParamSet("TransmitSignalFade", TransmitSignalFade_MS);

    CF.ParamSet("SpectrogramStrip", SpectrogramStrip);
    CF.ParamSet("SpectrogramLayoutSize", SpectrogramLayoutSize);
    CF.ParamSet("SpectrogramLayoutOrientation", SpectrogramLayoutOrientation);
    CF.ParamSet("SpectrogramScrollCycle", SpectrogramScrollCycle);
    CF.ParamSet("DisplayGamma", DisplayGamma);

    CF.ParamSet("AudioFileBuffer", AudioFileBuffer);

    CF.ParamSet("PlaybackMode", PlaybackMode);
    CF.ParamSet("PlaybackBufCompensation", PlaybackBufCompensation);
    CF.ParamSet("PlaybackBufSizeMin", PlaybackBufSizeMin_MS);
    CF.ParamSet("PlaybackBufSizeMax", PlaybackBufSizeMax_MS);

    CF.ParamSet("SpectrogramStripColorR", SpectrogramStripColorR);
    CF.ParamSet("SpectrogramStripColorG", SpectrogramStripColorG);
    CF.ParamSet("SpectrogramStripColorB", SpectrogramStripColorB);

    CF.ParamSet("SpectrogramNegative", SpectrogramNegative);
    CF.ParamSet("SpectrogramMouseGraph", SpectrogramMouseGraph);
    CF.ParamSet("SpectrogramMouseButtons", SpectrogramMouseButtons);
    CF.ParamSet("SpectrogramMarkersEnable", SpectrogramMarkersEnable);

    CF.ParamSet("CalcDecimation", CalcDecimation);
    CF.ParamSet("CalcDecimationConst", CalcDecimationConst);

    CF.ParamSet("OverloadThreshold", OverloadThreshold);
    CF.ParamSet("OverloadColorR", OverloadColorR);
    CF.ParamSet("OverloadColorG", OverloadColorG);
    CF.ParamSet("OverloadColorB", OverloadColorB);

    CF.ParamSet("GeneratorFreqEnable", GeneratorFreqEnable);
    CF.ParamSet("GeneratorFreq", GeneratorFreq);

    CF.ParamSet("HalfMarkSize", HalfMarkSize);
    CF.ParamSet("HalfMarkColorR", HalfMarkColorR);
    CF.ParamSet("HalfMarkColorG", HalfMarkColorG);
    CF.ParamSet("HalfMarkColorB", HalfMarkColorB);

    CF.ParamSet("SpectrumDisplayR", SpectrumDisplayR);
    CF.ParamSet("SpectrumDisplayG", SpectrumDisplayG);
    CF.ParamSet("SpectrumDisplayB", SpectrumDisplayB);

    CF.ParamSet("StereoMode", StereoMode);

    CF.ParamSet("FiltersEnabled", FiltersEnabled);
    CF.ParamSet("DrawFil", DrawFil);
    CF.ParamSet("DrawRef", DrawRef);

    CF.ParamSet("FilterSize", FilterSize);

    CF.ParamSet("SpectrumPaletteSelected", SpectrumPaletteSelected);

    CF.ParamSet("VisibleSpectrogramG", VisibleSpectrogramG);
    CF.ParamSet("VisibleProcG", VisibleProcG);
    CF.ParamSet("VisibleBufG", VisibleBufG);
    CF.ParamSet("VisibleBufSpeedG", VisibleBufSpeedG);
    CF.ParamSet("VisibleMorseG", VisibleMorseG);

    CF.ParamSet("RepaintBufferSize", RepaintBufferSize_S);
    CF.ParamSet("RepaintTimeout", RepaintTimeout);

    CF.ParamSet("ReplayBufferSize", ReplayBufferSize_S);

    CF.FileSave(Eden::ApplicationDirectory() + "Settings.txt");
}

string Settings::GetRecordFileName()
{
    if (RecordFileName == "")
    {
        return Eden::CorrectDir(Eden::ApplicationDirectory());
    }
    return Eden::CorrectDir(RecordFileName);
}

void Settings::SplitTextToLines(string RAW, vector<string> &Vec, bool Terminator)
{
    Vec.clear();
    string Buf = "";
    for (uint I = 0; I < RAW.length(); I++)
    {
        char C = RAW[I];
        if ((C == '\r') || (C == '\n'))
        {
            if (Buf != "")
            {
                if (Terminator)
                {
                    Buf += "X";
                }
                Vec.push_back(Buf);
                Buf = "";
            }
        }
        else
        {
            Buf += C;
        }
    }
    if (Buf != "")
    {
        if (Terminator)
        {
            Buf += "X";
        }
        Vec.push_back(Buf);
        Buf = "";
    }
}

void Settings::CalcSampleRate()
{
    PlayerInputChunkSize = (PlayerInputChunkSize_MS * SampleRate) / 1000;
    AudioBufferP = (AudioBufferP_MS * SampleRate) / 1000;
    AudioBufferR = (AudioBufferR_MS * SampleRate) / 1000;

    PlaybackBufSizeMin = (PlaybackBufSizeMin_MS * SampleRate) / 1000;
    PlaybackBufSizeMax = (PlaybackBufSizeMax_MS * SampleRate) / 1000;

    MuteTransmitC = (MuteTransmitC_MS * SampleRate) / 1000;

    TransmitSignalFade = (TransmitSignalFade_MS * 1000) / SampleRate;

    RepaintBufferSize = (RepaintBufferSize_S * SampleRate);

    ReplayBufferSize = (ReplayBufferSize_S * SampleRate);
}
