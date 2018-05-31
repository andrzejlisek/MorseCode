#ifndef SOUNDSETTINGS_H
#define SOUNDSETTINGS_H

#include <QDialog>
#include "eden.h"
#include "appcore.h"
#include <QFileDialog>
#include <QFileInfo>
#include "settings.h"
#include "audioplayer.h"
#include "audiorecorder.h"


namespace Ui {
class SoundSettings;
}

class SoundSettings : public QDialog
{
    Q_OBJECT

public:
    Settings * Settings_;
    AppCore * Core;
    explicit SoundSettings(QWidget *parent = 0);
    ~SoundSettings();
    int GetSelectedSampleRate();
    void SetSelectedSampleRate(int SampleRate);
    void SaveLastPath(QString X, bool OpenDir);
    void Init(string *DevI, string *DevO, EdenClass::AudioRecorder *AR_, EdenClass::AudioPlayer * AP_);
    int * SoundSampleRates;
    bool EventEnabled = false;

    EdenClass::AudioPlayer * AP;
    EdenClass::AudioRecorder * AR;
    string * DevIList;
    string * DevOList;
    void RefreshSampleRates();

private slots:

    void on_FromFileB_clicked();

    void on_AudioFromFileC_toggled(bool checked);

    void on_ToFileB_clicked();

    void on_SoundBufferRT_textEdited(const QString &arg1);

    void on_SoundBufferPT_textEdited(const QString &arg1);

    void on_SoundChunkT_textEdited(const QString &arg1);

    void on_RefreshT_textEdited(const QString &arg1);

    void on_PlayerEnabledC_toggled(bool checked);

    void on_SampleRateS_currentIndexChanged(int index);

    void on_DeviceIS_currentIndexChanged(int index);

    void on_DeviceOS_currentIndexChanged(int index);

    void on_ToFileC_toggled(bool checked);

    void on_PlayerEnabledS_currentIndexChanged(int index);

    void on_PlaybackCompensation_textEdited(const QString &arg1);

    void on_PlaybackBufferMinT_textEdited(const QString &arg1);

    void on_PlaybackBufferMaxT_textEdited(const QString &arg1);

    void on_SoundStereoModeS_currentIndexChanged(int index);

    void on_FiltersEnabledC_toggled(bool checked);

    void on_FiltersDrawFilC_toggled(bool checked);

    void on_FiltersDrawRefC_toggled(bool checked);

    void on_FilterSizeT_textEdited(const QString &arg1);

    void on_VisibleSpectrogramC_toggled(bool checked);

    void on_VisibleProcC_toggled(bool checked);

    void on_VisibleBufC_toggled(bool checked);

    void on_VisibleBufSpeedC_toggled(bool checked);

    void on_VisibleMorseC_toggled(bool checked);

    void on_RepaintTimeoutT_textEdited(const QString &arg1);

    void on_RepaintBufferSizeT_textEdited(const QString &arg1);

    void on_ReplayBufferSizeT_textEdited(const QString &arg1);

private:
    Ui::SoundSettings *ui;

signals:
    void GuiChange();
};

#endif // SOUNDSETTINGS_H
