#ifndef APPCORE_H
#define APPCORE_H

#include "eden.h"
#include "fftx.h"
#include <iostream>
#include <fstream>
#include "ringbuffer.h"
#include <QTime>
#include "wavefile.h"
#include "morsedecodercore.h"
#include "morseencodercore.h"
#include "settings.h"
#include <QImage>
#include <chrono>

#define b00000000 0
#define b00000001 1
#define b00000010 2
#define b00000011 3
#define b00000100 4

#define AudioBufferSize 100000
#define MaxFilterSize 5000
#define SpectrumLines 512
#define WindowAmplitude 65536
// SpectrumResolutionFactor=8192 <=> SpectrumResolutionFactorX 3
#define SpectrumResolutionFactor 16384
#define SpectrumResolutionFactorX 4
//#define SpectrumArraySize (2 * SpectrumLines * (SpectrumResolutionFactor / (SpectrumLines * 2)))
#define SpectrumArraySize 16384

using namespace std;

class AppCore
{
public:
    bool SpectrumMarkers = false;
    vector<uint> SpectrumMarkersPosition;
    vector<uint> SpectrumMarkersThickness;
    vector<uchar> SpectrumMarkersRed;
    vector<uchar> SpectrumMarkersGreen;
    vector<uchar> SpectrumMarkersBlue;
    vector<uint> SpectrumMarkersPositionX;
    vector<uint> SpectrumMarkersThicknessX;

    Settings * Settings_;
    EdenClass::WaveFile WF;
    AppCore();
    ~AppCore();
    int SpectrumLinesBase = SpectrumLines;

    uchar SpectrumTempMinMax_R[SpectrumArraySize];
    uchar SpectrumTempMinMax_G[SpectrumArraySize];
    uchar SpectrumTempMinMax_B[SpectrumArraySize];
    uchar SpectrumBufRaw_R[SpectrumArraySize];
    uchar SpectrumBufRaw_G[SpectrumArraySize];
    uchar SpectrumBufRaw_B[SpectrumArraySize];
    uchar SpectrumBufFil_R[SpectrumArraySize];
    uchar SpectrumBufFil_G[SpectrumArraySize];
    uchar SpectrumBufFil_B[SpectrumArraySize];
    uchar SpectrumBufRef_R[SpectrumArraySize];
    uchar SpectrumBufRef_G[SpectrumArraySize];
    uchar SpectrumBufRef_B[SpectrumArraySize];
    bool SpectrumBufOverload;
    uchar SpectrumVUFil_R;
    uchar SpectrumVUFil_G;
    uchar SpectrumVUFil_B;
    uchar SpectrumVURef_R;
    uchar SpectrumVURef_G;
    uchar SpectrumVURef_B;
    short SpectrumVUFilX;
    short SpectrumVURefX;
    uchar SpectrumVUCalc;
    FFTX F;

    RingBuffer<short> AudioSrc;
    RingBuffer<short> AudioRaw;
    RingBuffer<short> AudioFil;
    RingBuffer<short> AudioRef;

    RingBuffer<short> AudioFilVU;
    RingBuffer<short> AudioRefVU;
    RingBuffer<short> AudioCalcVU;
    RingBuffer<short> AudioPlaybackBuf;

    bool WithRef;

    double VUCalcAttackThreshold = 2.5;
    double VUCalcDecayThreshold = 2.5;
    double VUCalcFil;
    double VUCalcRef;
    double VUCalc;
    bool VUCalcAttackState;
    int VUCalcAttackL;
    int VUCalcAttackI;
    int VUCalcDecayL;
    int VUCalcDecayI;


    int VUHeight = 16;
    int VUSize = 500;
    int VUMode = 0;
    // Array size = Maximum predicted averaging value
    short VUMedianArrayFil[2000];
    short VUMedianArrayRef[2000];

    void SpectrogramGet(uchar * BmpRAW, int DispWidth, int DispHeight, char DrawCurrent, int DrawOffset);
    int SpectrogramStep;
    int SpectrogramBase = 0;
    int SpectrogramPointer__ = 0;
    float SpectrogramAmp = 1;
    float VUAmp = 1;
    int SpectrogramResolution = 0;
    int SpectrogramZoom = 0;
    int SpectrogramOffset = 0;
    double WindowFactor = 1024;
    float SpectrogramRe[SpectrumResolutionFactor];
    float SpectrogramIm[SpectrumResolutionFactor];
    short AudioTempX[AudioBufferSize];
    short AudioTempRaw[AudioBufferSize];
    short AudioTempFil[AudioBufferSize];
    short AudioTempRef[AudioBufferSize];
    short * AudioTempRaw_;
    short * AudioTempFil_;
    short * AudioTempRef_;
    void CalcSpectrum(short * BufInput, uchar * BufOutputR, uchar * BufOutputG, uchar * BufOutputB, bool CalcOver);
    void CalcVU(short * BufInput, uchar * BufOutput_R, uchar * BufOutput_G, uchar * BufOutput_B, short *BufOutputX);
    void AudioTimerTrigger(uchar * SpectrogramRAW, int DispWidth, int DispHeight);
    int DispWidthLast = 0;
    int DispHeightLast = 0;
    int SpectrogramFullMaxW = 4096;
    int SpectrogramFullMaxW4 = 16384;
    int SpectrogramFullMaxH = 4096;

    llong FilterWindow[MaxFilterSize + 1];
    llong FilterWindowRef[MaxFilterSize + 1];
    short FilterWindowWork[(MaxFilterSize * 2) + 1];
    short FilterWindowWorkFil[(MaxFilterSize * 2) + 1];
    short FilterWindowWorkRef[(MaxFilterSize * 2) + 1];
    int FilterWindowWorkSize = (MaxFilterSize * 2) + 1;
    int FilterSize = 500;

    void CreateFilter(llong * FilterRaw, double FilterLf, double FilterHf);
    double M_PIx = 3.1415926535897932384626433832795;

    void ProcessAudio(short * Buf, int N);
    int WindowPointer = 0;
    int WindowPointer1 = 0;
    int WindowPointer2 = 0;

    int FileAudioPointer;
    int FileAudioLength;
    short * FileAudioData;

    void FileAudioLoad(string FileName);

    void MouseOperation(int Btn, int X, int Y, uchar * SpectrogramPicture);
    bool MousePressed;
    int MouseX;
    int MouseY;
    int MouseMode;

    int CorrectOffset;
    double XFreqL;
    double XFreqH;
    double XFreqLRef;
    double XFreqHRef;
    int XFreqL__ = 0;
    int XFreqH__ = SpectrumLines;
    int XFreqLRef__ = 0;
    int XFreqHRef__ = SpectrumLines;


    QString LastPath;

    volatile char * DecodeBuffer;
    int DecodeBufferW = 0;
    int DecodeBufferL = 0;
    int DecodeBufferT = 0;

    void DecodeProcedure(char NextSign);
    char DecodeLastSign;
    int DecodeSignLength;
    MorseDecoderCore MorseDecoderCore_;
    MorseEncoderCore MorseEncoderCore_;
    bool MorseWork = false;

    int BufOffset;
    int BufSpeed = 100;
    int BufPos;
    int BufSize;
    int BufTime = 0;
    int BufSampleRate;
    EdenClass::WaveFile BufFile;
    bool BufOpen(int SR);
    void BufClose();
    void BufPrev(int X);
    void BufNext(int X);

    int SpectrogramDrawMode = 0;
    int SpectrogramDrawVU = 0;
    int SpectrogramDrawVUX = 0;
    bool SpectrogramDrawVolume = false;

    QString MorseBufGet();

    uchar SpectrogramTempR[SpectrumArraySize];
    uchar SpectrogramTempG[SpectrumArraySize];
    uchar SpectrogramTempB[SpectrumArraySize];

    uchar SpectrogramGammaLUT_R[70001];
    uchar SpectrogramGammaLUT_G[70001];
    uchar SpectrogramGammaLUT_B[70001];
    void SetGamma(bool Fullscreen);
    bool AudioFileBufferSession = true;

    int SpectrogramPointerScroll = 0;

    int SpectrogramMinMax = 0;
    int SpectrogramMinMaxX = 0;
    int SpectrogramDisplayLines = 1;
    int SpectrogramDisplayCurrentLine__ = 0;

    void GetPlaybackSamples(short *Smp, int ChunkSize);
    int PlaybackCompensationCounter = 0;

    void SetSpectrogramMarkers();

    void ClearBuffers();

    int SpectrogramDrawLineWidth = 0;
    int SpectrogramVolumeBarSize = 0;
    bool SpectrogramFilterMoveBand = false;
    bool DecodeCorrection = false;

    RingBuffer<short> * RepaintBufRaw = NULL;
    RingBuffer<short> * RepaintBufFil = NULL;
    RingBuffer<short> * RepaintBufRef = NULL;

    RingBuffer<short> * RepaintFilVU = NULL;
    RingBuffer<short> * RepaintRefVU = NULL;

    int RepaintBufL = 0;

    uchar WholeRepaint = 0;
    int WholeRepaintOffset = 0;
    int WholeRepaintTimeout = 20;

    short * ReplayBuffer = NULL;
    int ReplayBufferL = 0;
    int ReplayBufferP = 0;
    int ReplayBufferF = 0;

private:
    int * MorseBufTX;
    QString * MorseBuf;
    uint CalcDecimationCounter;
};

#endif // APPCORE_H
