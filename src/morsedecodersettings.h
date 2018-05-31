#ifndef MORSEDECODERSETTINGS_H
#define MORSEDECODERSETTINGS_H

#include <QDialog>
#include "eden.h"
#include "morsedecodercore.h"
#include "settings.h"

namespace Ui {
class MorseDecoderSettings;
}

class MorseDecoderSettings : public QDialog
{
    Q_OBJECT

public:
    Settings * Settings_;
    MorseDecoderCore * MorseDecoderCore_;
    MorseEncoderCore * MorseEncoderCore_;
    explicit MorseDecoderSettings(QWidget *parent = 0);
    ~MorseDecoderSettings();
    void Init();

private slots:
    void on_MorseLastSignalsT_textEdited(const QString &arg1);

    void on_MorseLengthFactorS_valueChanged(int value);

    void on_PauseShortFactorT_textEdited(const QString &arg1);

    void on_PauseLongFactorT_textEdited(const QString &arg1);

    void on_MorseCalcB_clicked();

    void on_BufferLastT_textEdited(const QString &arg1);

    void on_AutoCalcC_toggled(bool checked);

    void on_AutoCalcT_textEdited(const QString &arg1);

    void on_TestModeC_toggled(bool checked);

    void on_WPMStandardT_currentIndexChanged(int index);

    void on_GenVolumeS_valueChanged(int value);

    void on_MuteTransmitC_toggled(bool checked);

    void on_MuteTransmitT_textEdited(const QString &arg1);

    void on_TransmitBufLatencyT_textEdited(const QString &arg1);

    void on_TransmitFadeT_textEdited(const QString &arg1);

    void on_SoundFreqC_toggled(bool checked);

    void on_SoundFreqT_textEdited(const QString &arg1);

private:
    Ui::MorseDecoderSettings *ui;
};

#endif // MORSEDECODERSETTINGS_H
