#include "soundsettings.h"
#include "ui_soundsettings.h"

SoundSettings::SoundSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoundSettings)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
    SoundSampleRates = NEWARR(int, int[0]);
    ui->setupUi(this);
}

SoundSettings::~SoundSettings()
{
    DELARR(int, SoundSampleRates);
    delete ui;
}

void SoundSettings::SetSelectedSampleRate(int SampleRate)
{
    int i = 0;
    int ii = 0;
    while (SoundSampleRates[i] != 0)
    {
        if (SoundSampleRates[i] == SampleRate)
        {
            ii = i;
        }
        i++;
    }
    ui->SampleRateS->setCurrentIndex(ii);
}

int SoundSettings::GetSelectedSampleRate()
{
    return SoundSampleRates[ui->SampleRateS->currentIndex()];
}

void SoundSettings::on_FromFileB_clicked()
{
    QString FN = QFileDialog::getOpenFileName(this, "Select wave file", Core->LastPath, "Files (*)");
    SaveLastPath(FN, false);
    ui->FromFileT->setText(FN);
    Settings_->FileAudioName = Eden::ToStr(FN);
    if (ui->AudioFromFileC->isChecked())
    {
        Core->FileAudioLoad(Settings_->FileAudioName);
    }
}

void SoundSettings::on_AudioFromFileC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->FileAudioWork = checked;
        if (ui->AudioFromFileC->isChecked())
        {
            Core->FileAudioLoad(Settings_->FileAudioName);
        }
    }
}

void SoundSettings::on_ToFileB_clicked()
{
    QString FN = QFileDialog::getExistingDirectory(this, "Record directory", Core->LastPath);
    SaveLastPath(FN, false);
    ui->ToFileT->setText(Eden::CorrectDir(FN));
    Settings_->RecordFileName = Eden::ToStr(ui->ToFileT->text());
}

void SoundSettings::SaveLastPath(QString X, bool OpenDir)
{
    if (!X.isEmpty())
    {
        if (OpenDir)
        {
            Core->LastPath = QFileInfo(X).filePath();
        }
        else
        {
            Core->LastPath = QFileInfo(X).path();
        }
    }
}

void SoundSettings::Init(string *DevI, string *DevO, EdenClass::AudioRecorder * AR_, EdenClass::AudioPlayer * AP_)
{
    AR = AR_;
    AP = AP_;
    DevIList = DevI;
    DevOList = DevO;

    ui->ToFileT->setText(Eden::ToQStr(Settings_->RecordFileName));

    ui->SoundBufferRT->setText(Eden::ToQStr(Settings_->AudioBufferR_MS));
    ui->SoundBufferPT->setText(Eden::ToQStr(Settings_->AudioBufferP_MS));
    ui->SoundChunkT->setText(Eden::ToQStr(Settings_->PlayerInputChunkSize_MS));
    ui->RefreshT->setText(Eden::ToQStr(Settings_->RefreshPeriod));
    ui->PlayerEnabledC->setChecked(Settings_->PlayerEnabled);
    ui->AudioFromFileC->setChecked(Settings_->FileAudioWork);
    ui->FromFileT->setText(Eden::ToQStr(Settings_->FileAudioName));
    ui->FilterSizeT->setText(Eden::ToQStr(Settings_->FilterSize));
    ui->ToFileC->setChecked(Settings_->AudioFileBuffer);

    ui->PlaybackCompensation->setText(Eden::ToQStr(Settings_->PlaybackBufCompensation));
    ui->PlayerEnabledS->setCurrentIndex(Settings_->PlaybackMode);
    ui->PlaybackBufferMinT->setText(Eden::ToQStr(Settings_->PlaybackBufSizeMin_MS));
    ui->PlaybackBufferMaxT->setText(Eden::ToQStr(Settings_->PlaybackBufSizeMax_MS));

    ui->SoundStereoModeS->setCurrentIndex(Settings_->StereoMode);
    ui->FiltersEnabledC->setChecked(Settings_->FiltersEnabled);
    ui->FiltersDrawFilC->setChecked(Settings_->DrawFil);
    ui->FiltersDrawRefC->setChecked(Settings_->DrawRef);

    ui->RepaintTimeoutT->setText(Eden::ToQStr(Settings_->RepaintTimeout));
    ui->RepaintBufferSizeT->setText(Eden::ToQStr(Settings_->RepaintBufferSize_S));
    ui->ReplayBufferSizeT->setText(Eden::ToQStr(Settings_->ReplayBufferSize_S));

    if (ui->AudioFromFileC->isChecked())
    {
        Core->FileAudioLoad(Settings_->FileAudioName);
    }

    ui->DeviceIS->clear();
    int I = 0;
    int II = 0;
    while (DevI[I] != "")
    {
        ui->DeviceIS->addItem(Eden::ToQStr(DevI[I]));
        if (DevI[I] == Settings_->DeviceI)
        {
            II = I;
        }
        I++;
    }
    ui->DeviceIS->setCurrentIndex(II);

    ui->DeviceOS->clear();
    I = 0;
    II = 0;
    while (DevO[I] != "")
    {
        ui->DeviceOS->addItem(Eden::ToQStr(DevO[I]));
        if (DevI[I] == Settings_->DeviceO)
        {
            II = I;
        }
        I++;
    }
    ui->DeviceOS->setCurrentIndex(II);

    RefreshSampleRates();

    SetSelectedSampleRate(Settings_->SampleRate);

    ui->VisibleSpectrogramC->setChecked(Settings_->VisibleSpectrogramG);
    ui->VisibleProcC->setChecked(Settings_->VisibleProcG);
    ui->VisibleBufC->setChecked(Settings_->VisibleBufG);
    ui->VisibleBufSpeedC->setChecked(Settings_->VisibleBufSpeedG);
    ui->VisibleMorseC->setChecked(Settings_->VisibleMorseG);

    EventEnabled = true;
}

void SoundSettings::on_SoundBufferRT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        Settings_->AudioBufferR_MS = Eden::ToInt(arg1);
    }
}

void SoundSettings::on_SoundBufferPT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        Settings_->AudioBufferP_MS = Eden::ToInt(arg1);
    }
}

void SoundSettings::on_SoundChunkT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        Settings_->PlayerInputChunkSize_MS = Eden::ToInt(arg1);
    }
}

void SoundSettings::on_RefreshT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        Settings_->RefreshPeriod = Eden::ToInt(arg1);
    }
}

void SoundSettings::on_PlayerEnabledC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->PlayerEnabled = checked;
    }
}

void SoundSettings::on_SampleRateS_currentIndexChanged(int index)
{
    if (EventEnabled)
    {
        index++;
        index--;
        Settings_->SampleRate = GetSelectedSampleRate();
    }
}

void SoundSettings::on_DeviceIS_currentIndexChanged(int index)
{
    if (EventEnabled)
    {
        AR->SelectDevice(DevIList[index]);
        Settings_->DeviceI = DevIList[index];
        EventEnabled = false;
        RefreshSampleRates();
        EventEnabled = true;
    }
}

void SoundSettings::on_DeviceOS_currentIndexChanged(int index)
{
    if (EventEnabled)
    {
        AP->SelectDevice(DevOList[index]);
        Settings_->DeviceO = DevOList[index];
        EventEnabled = false;
        RefreshSampleRates();
        EventEnabled = true;
    }
}

void SoundSettings::RefreshSampleRates()
{
    int * SoundSampleRatesR = AR->GetPossibleSampleRates();
    int * SoundSampleRatesP = AP->GetPossibleSampleRates();
    int SoundSampleRatesL = 0;
    while (SoundSampleRatesR[SoundSampleRatesL] > 0)
    {
        SoundSampleRatesL++;
    }
    int I = 0;
    while (SoundSampleRatesP[I] > 0)
    {
        I++;
    }
    if (I > SoundSampleRatesL)
    {
        SoundSampleRatesL = I;
    }
    int J = 0;
    int K = 0;
    DELARR(int, SoundSampleRates);
    SoundSampleRates = NEWARR(int, int[SoundSampleRatesL + 1]);
    for (I = 0; I < SoundSampleRatesL; I++)
    {
        for (J = 0; J < SoundSampleRatesL; J++)
        {
            if (SoundSampleRatesR[J] == SoundSampleRatesP[I])
            {
                SoundSampleRates[K] = SoundSampleRatesP[I];
                K++;
            }
        }
    }
    SoundSampleRates[K] = 0;

    I = 0;
    ui->SampleRateS->clear();
    while (SoundSampleRates[I] != 0)
    {
        ui->SampleRateS->addItem(Eden::ToQStr(Eden::ToStr(SoundSampleRates[I])));
        I++;
    }

    SetSelectedSampleRate(Settings_->SampleRate);
    Settings_->SampleRate = GetSelectedSampleRate();
}

void SoundSettings::on_ToFileC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->AudioFileBuffer = checked;
    }
}

void SoundSettings::on_PlayerEnabledS_currentIndexChanged(int index)
{
    if (EventEnabled)
    {
        Settings_->PlaybackMode = index;
    }
}

void SoundSettings::on_PlaybackCompensation_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        if (Eden::ToInt(arg1) > 0)
        {
            Settings_->PlaybackBufCompensation = Eden::ToInt(arg1);
        }
    }
}

void SoundSettings::on_PlaybackBufferMinT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        if (Eden::ToInt(arg1) > 0)
        {
            Settings_->PlaybackBufSizeMin_MS = Eden::ToInt(arg1);
        }
    }
}

void SoundSettings::on_PlaybackBufferMaxT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        if (Eden::ToInt(arg1) > 0)
        {
            Settings_->PlaybackBufSizeMax_MS = Eden::ToInt(arg1);
        }
    }
}

void SoundSettings::on_SoundStereoModeS_currentIndexChanged(int index)
{
    if (EventEnabled)
    {
        Settings_->StereoMode = index;
    }
}

void SoundSettings::on_FiltersEnabledC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->FiltersEnabled = checked;
    }
}

void SoundSettings::on_FiltersDrawFilC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->DrawFil = checked;
    }
}

void SoundSettings::on_FiltersDrawRefC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->DrawRef = checked;
    }
}

void SoundSettings::on_FilterSizeT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        Settings_->FilterSize = max(min(Eden::ToInt(arg1), MaxFilterSize), 0);
    }
}

void SoundSettings::on_VisibleSpectrogramC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->VisibleSpectrogramG = checked;
        GuiChange();
    }
}

void SoundSettings::on_VisibleProcC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->VisibleProcG = checked;
        GuiChange();
    }
}

void SoundSettings::on_VisibleBufC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->VisibleBufG = checked;
        GuiChange();
    }
}

void SoundSettings::on_VisibleBufSpeedC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->VisibleBufSpeedG = checked;
        GuiChange();
    }
}

void SoundSettings::on_VisibleMorseC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->VisibleMorseG = checked;
        GuiChange();
    }
}

void SoundSettings::on_RepaintTimeoutT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        Settings_->RepaintTimeout = Eden::ToInt(arg1);
        GuiChange();
    }
}

void SoundSettings::on_RepaintBufferSizeT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        Settings_->RepaintBufferSize_S = Eden::ToInt(arg1);
        GuiChange();
    }
}

void SoundSettings::on_ReplayBufferSizeT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        Settings_->ReplayBufferSize_S = Eden::ToInt(arg1);
        GuiChange();
    }
}
