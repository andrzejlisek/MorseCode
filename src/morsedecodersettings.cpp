#include "morsedecodersettings.h"
#include "ui_morsedecodersettings.h"

MorseDecoderSettings::MorseDecoderSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MorseDecoderSettings)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
    ui->setupUi(this);
}

MorseDecoderSettings::~MorseDecoderSettings()
{
    delete ui;
}

void MorseDecoderSettings::on_MorseLastSignalsT_textEdited(const QString &arg1)
{
    Settings_->CalcMorseLastSignals = Eden::ToInt(arg1);
}

void MorseDecoderSettings::on_MorseLengthFactorS_valueChanged(int value)
{
    Settings_->CalcMorseLengthFactor = ui->MorseLengthFactorS->value();
    ui->MorseLengthFactorV->setText(Eden::ToQStr(value));
}

void MorseDecoderSettings::on_PauseShortFactorT_textEdited(const QString &arg1)
{
    Settings_->CalcPauseShortFactor = Eden::ToInt(arg1);
}

void MorseDecoderSettings::on_PauseLongFactorT_textEdited(const QString &arg1)
{
    Settings_->CalcPauseLongFactor = Eden::ToInt(arg1);
}

void MorseDecoderSettings::on_MorseCalcB_clicked()
{
    MorseDecoderCore_->Calc();
}

void MorseDecoderSettings::on_BufferLastT_textEdited(const QString &arg1)
{
    Settings_->MorseBufferLast = Eden::ToInt(arg1);
}

void MorseDecoderSettings::on_AutoCalcC_toggled(bool checked)
{
    Settings_->AutoCalcC = checked;
}

void MorseDecoderSettings::on_AutoCalcT_textEdited(const QString &arg1)
{
    Settings_->AutoCalc = Eden::ToInt(arg1);
}

void MorseDecoderSettings::on_TestModeC_toggled(bool checked)
{
    Settings_->MorseTestMode = checked;
}

void MorseDecoderSettings::on_WPMStandardT_currentIndexChanged(int index)
{
    Settings_->MorseWPMStandard = index;
}

void MorseDecoderSettings::Init()
{
    ui->WPMStandardT->setCurrentIndex(Settings_->MorseWPMStandard);
    ui->GenVolumeS->setValue(Settings_->MorseVolume);
    ui->TestModeC->setChecked(Settings_->MorseTestMode);

    ui->MorseLastSignalsT->setText(Eden::ToQStr(Settings_->CalcMorseLastSignals));
    ui->MorseLengthFactorS->setValue(Settings_->CalcMorseLengthFactor);
    ui->PauseShortFactorT->setText(Eden::ToQStr(Settings_->CalcPauseShortFactor));
    ui->PauseLongFactorT->setText(Eden::ToQStr(Settings_->CalcPauseLongFactor));
    ui->AutoCalcC->setChecked(Settings_->AutoCalcC);
    ui->AutoCalcT->setText(Eden::ToQStr(Settings_->AutoCalc));
    ui->BufferLastT->setText(Eden::ToQStr(Settings_->MorseBufferLast));

    ui->MuteTransmitC->setChecked(Settings_->MuteTransmit);
    ui->MuteTransmitT->setText(Eden::ToQStr(Settings_->MuteTransmitC_MS));
    ui->TransmitBufLatencyT->setText(Eden::ToQStr(Settings_->TransmitBufLatency));
    ui->TransmitFadeT->setText(Eden::ToQStr(Settings_->TransmitSignalFade_MS));

    ui->SoundFreqC->setChecked(Settings_->GeneratorFreqEnable);
    ui->SoundFreqT->setText(Eden::ToQStr(Settings_->GeneratorFreq));
}

void MorseDecoderSettings::on_GenVolumeS_valueChanged(int value)
{
    Settings_->MorseVolume = value;
    ui->GenVolumeV->setText(Eden::ToQStr(value));
}


void MorseDecoderSettings::on_MuteTransmitC_toggled(bool checked)
{
    Settings_->MuteTransmit = checked;
}

void MorseDecoderSettings::on_MuteTransmitT_textEdited(const QString &arg1)
{
    Settings_->MuteTransmitC_MS = Eden::ToInt(arg1);
}

void MorseDecoderSettings::on_TransmitBufLatencyT_textEdited(const QString &arg1)
{
    Settings_->TransmitBufLatency = Eden::ToInt(arg1);
}

void MorseDecoderSettings::on_TransmitFadeT_textEdited(const QString &arg1)
{
    Settings_->TransmitSignalFade_MS = Eden::ToInt(arg1);
}

void MorseDecoderSettings::on_SoundFreqC_toggled(bool checked)
{
    Settings_->GeneratorFreqEnable = checked;
    Settings_->GeneratorRecalc = true;
}

void MorseDecoderSettings::on_SoundFreqT_textEdited(const QString &arg1)
{
    Settings_->GeneratorFreq = Eden::ToInt(arg1);
    Settings_->GeneratorRecalc = true;
}
