#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include "eden.h"
#include <fstream>
#include <iostream>
#include "configfile.h"

using namespace std;

class Settings
{
public:
    Settings();
    ~Settings();
    string GetRecordFileName();

    EdenClass::ConfigFile CF;

    string DeviceI = "Default";
    string DeviceO = "Default";

    int PlayerInputChunkSize = 2000;
    int PlayerInputChunkSize_MS = 250;
    int AudioBufferP = 2000;
    int AudioBufferP_MS = 250;
    int AudioBufferR = 2000;
    int AudioBufferR_MS = 250;

    int RefreshPeriod = 100;
    bool PlayerEnabled = true;
    int PlaybackMode = 0;
    int PlaybackBufSizeMin = 2200;
    int PlaybackBufSizeMin_MS = 275;
    int PlaybackBufSizeMax = 10000;
    int PlaybackBufSizeMax_MS = 1250;
    int PlaybackBufCompensation = 0;
    int SampleRate = 8000;
    bool FileAudioWork = false;
    string FileAudioName = "";
    string RecordFileName = "";

    int MorseWPM = -60;
    int MorseWPMStandard = 0;
    int MorseVolume = 50;
    bool MorseTestMode = false;

    int CalcMorseLastSignals = 20;
    int CalcMorseLengthFactor = 50;
    int CalcPauseShortFactor = 200;
    int CalcPauseLongFactor = 500;
    bool AutoCalcC = true;
    int AutoCalc = 10;
    int MorseBufferLast = 50;

    int MuteTransmitC = 8000;
    int MuteTransmitC_MS = 1000;
    bool MuteTransmit = true;

    llong TransmitBufLatency = 0;
    int TransmitSignalFade = 1000000;
    int TransmitSignalFade_MS = 10000000;

    bool SpectrogramNegative = false;
    int SpectrogramStrip = 8;
    int SpectrogramStripColorR = 255;
    int SpectrogramStripColorG = 255;
    int SpectrogramStripColorB = 255;
    int SpectrogramLayoutSize = 50;
    int SpectrogramLayoutOrientation = 0;
    int SpectrogramScrollCycle = 1;

    int DisplayGamma = 2200;
    bool DisplayGammaUpdate = true;
    bool DisplayGammaFull = false;

    bool AudioFileBuffer = false;

    bool SpectrogramMarkersEnable = false;
    string SpectrogramMarkers = "";
    bool SpectrogramMarkersUpdate = true;


    bool SpectrogramMouseGraph = false;
    bool SpectrogramMouseButtons = false;
    int CalcDecimation = 1;
    bool CalcDecimationConst = false;

    int OverloadThreshold = 30000;
    int OverloadColorR = 255;
    int OverloadColorG = 255;
    int OverloadColorB = 255;

    bool GeneratorFreqEnable = false;
    int GeneratorFreq = 600;
    bool GeneratorRecalc = false;

    int HalfMarkSize = 1;
    int HalfMarkColorR = 255;
    int HalfMarkColorG = 255;
    int HalfMarkColorB = 255;

    int SpectrumDisplayR = 0;
    int SpectrumDisplayG = 0;
    int SpectrumDisplayB = 0;

    int StereoMode = 0;

    bool FiltersEnabled = true;
    bool DrawFil = false;
    bool DrawRef = false;

    int FilterSize = 500;

    int SpectrumPaletteSelected = 0;

    vector<string> SpectrumPaletteFile;
    vector<int> SpectrumPaletteColumn;
    vector<int> SpectrumPaletteLine1;
    vector<int> SpectrumPaletteLine2;
    vector<string> SpectrumPaletteName;

    void SplitTextToLines(string RAW, vector<string> &Vec, bool Terminator);

    int WindowType = 3;

    bool SpectrogramChanged = false;

    bool VisibleSpectrogramG = true;
    bool VisibleProcG = true;
    bool VisibleBufG = true;
    bool VisibleBufSpeedG = true;
    bool VisibleMorseG = true;

    int RepaintBufferSize = 2000000;
    int RepaintBufferSize_S = 180;
    int RepaintTimeout = 50;

    bool WholeRepaint = false;

    int ReplayBufferSize = 10000000;
    int ReplayBufferSize_S = 1000;

    void CalcSampleRate();

};

#endif // SETTINGS_H
