#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "audioplayer.h"
#include "appcore.h"
#include <iostream>
#include "audiorecorder.h"
#include "wavefile.h"
#include "morsedecodersettings.h"
#include "soundsettings.h"
#include <QCloseEvent>
#include "printtext.h"
#include "inputtext.h"
#include "progtimer.h"
#include "settings.h"
#include "spectrumfull.h"
#include "spectrumsettings.h"
#include <QSlider>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Settings * Settings_;
    QThread * ProgTimer__;
    ProgTimer * ProgTimer_;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void DrawSpectrogram();
    AppCore Core;
    EdenClass::AudioRecorder * AR;
    EdenClass::AudioPlayer * AP;
    QImage * SpectrogramBmp;
    SoundSettings SS;
    PrintText PT;
    InputText IT;
    SpectrumFull SpecF;
    SpectrumSettings SpecS;
    MorseDecoderSettings MDS;
    void closeEvent(QCloseEvent *event);
    short * AudioTempP;
    int PlayerInputChunkSize = 5000;
    short * RecordBuf = NULL;
    //int RecordBuf = 0;
    int RecordBufL = 0;
    void RefreshVisible(bool Force);

private slots:
    void on_SoundStart_clicked();

    void on_SoundStop_clicked();

    void AudioTimerTick();

    void GuiChange();

    void on_SpectrogramAmpT_valueChanged(int value);

    void on_SpectrogramResolutionT_valueChanged(int value);

    void on_SpectrogramZoomT_valueChanged(int value);

    void on_VUAmpT_valueChanged(int value);

    void on_VUSizeT_valueChanged(int value);

    void on_CalcThrAttackT_valueChanged(int value);

    void on_CalcThrDecayT_valueChanged(int value);

    void on_ProcessCountAttackT_valueChanged(int value);

    void on_ProcessCountDecayT_valueChanged(int value);

    void on_WithRefC_toggled(bool checked);

    void on_SpectrogramStepT_valueChanged(int value);

    void on_SoundSettings_clicked();

    void on_SpectrogramL_MouseMove(int Btn, int X, int Y);

    void on_SpectrogramL_MousePress(int Btn, int X, int Y);

    void on_SpectrogramL_MouseRelease(int Btn, int X, int Y);

    void on_PrintText_clicked();

    void on_MorseCalcB_clicked();

    void on_MorseBufferClear_clicked();

    void on_MorseBufferBegin_clicked();

    void on_MorseSettingsB_clicked();

    void on_MorseRealTime_toggled(bool checked);

    void on_MorseBufferCurrent_clicked();

    void on_BufSpeedS_valueChanged(int value);

    void on_BufPrev_clicked();

    void on_BufPrevLong_clicked();

    void on_BufPrevShort_clicked();

    void on_BufNext_clicked();

    void on_BufNextLong_clicked();

    void on_BufNextShort_clicked();

    void on_BufPlay_clicked();

    void on_BufPause_clicked();

    void on_MorseWork_toggled(bool checked);

    void on_MorseBufferLast_clicked();

    void on_InputText_clicked();

    void on_SoundSpectrumFull_clicked();

    void on_SpectrogramSettings_clicked();

    void on_SpectrogramBaseT_valueChanged(int value);

    void on_SpectrogramOffsetT_valueChanged(int value);

    void on_SpectrogramWindowT_valueChanged(int value);

    void on_BufSpeed1L_MousePress(int X, int Y, int B);

    void on_BufSpeed2L_MousePress(int X, int Y, int B);

    void on_SpectrogramAmpL_MousePress(int X, int Y, int B);

    void on_SpectrogramAmpV_MousePress(int X, int Y, int B);

    void on_SpectrogramResolutionL_MousePress(int X, int Y, int B);

    void on_SpectrogramResolutionV_MousePress(int X, int Y, int B);

    void on_SpectrogramWindowL_MousePress(int X, int Y, int B);

    void on_SpectrogramWindowV_MousePress(int X, int Y, int B);

    void on_SpectrogramZoomL_MousePress(int X, int Y, int B);

    void on_SpectrogramZoomV_MousePress(int X, int Y, int B);

    void on_SpectrogramOffsetL_MousePress(int X, int Y, int B);

    void on_SpectrogramOffsetV_MousePress(int X, int Y, int B);

    void on_SpectrogramStepL_MousePress(int X, int Y, int B);

    void on_SpectrogramStepV_MousePress(int X, int Y, int B);

    void on_SpectrogramBaseL_MousePress(int X, int Y, int B);

    void on_SpectrogramBaseV_MousePress(int X, int Y, int B);

    void on_VUAmpL_MousePress(int X, int Y, int B);

    void on_VUAmpV_MousePress(int X, int Y, int B);

    void on_VUSizeL_MousePress(int X, int Y, int B);

    void on_VUSizeV_MousePress(int X, int Y, int B);

    void on_CalcThrAttackL_MousePress(int X, int Y, int B);

    void on_CalcThrAttackV_MousePress(int X, int Y, int B);

    void on_CalcThrDecayL_MousePress(int X, int Y, int B);

    void on_CalcThrDecayV_MousePress(int X, int Y, int B);

    void on_ProcessCountAttackL_MousePress(int X, int Y, int B);

    void on_ProcessCountAttackV_MousePress(int X, int Y, int B);

    void on_ProcessCountDecayL_MousePress(int X, int Y, int B);

    void on_ProcessCountDecayV_MousePress(int X, int Y, int B);

    void on_SpectrogramLinesL_MousePress(int X, int Y, int B);

    void on_SpectrogramLinesV_MousePress(int X, int Y, int B);

    void on_SpectrogramMinMaxL_MousePress(int X, int Y, int B);

    void on_SpectrogramMinMaxV_MousePress(int X, int Y, int B);

    void on_SpectrogramLinesT_valueChanged(int value);

    void on_DrawMode_currentIndexChanged(int index);

    void on_DrawVU_currentIndexChanged(int index);

    void on_VUMode_currentIndexChanged(int index);

    void on_DecodeCorrectionC_toggled(bool checked);

    void on_SpectrogramMinMaxT_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    volatile bool AudioWork = false;
    int SampleRate;
    bool IsSpectrumFull();
    void SettingsLoad();
    void SettingsSave();
    EdenClass::ConfigFile CFP;
    void SliderInc(QSlider *S);
    void SliderDec(QSlider *S);
    void SetLabels();
};

#endif // MAINWINDOW_H
