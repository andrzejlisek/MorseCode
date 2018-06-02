#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Settings_ = NEW(Settings, Settings());
    Core.Settings_ = Settings_;
    SS.Settings_ = Settings_;
    SpecF.Settings_ = Settings_;
    Core.MorseEncoderCore_.Settings_ = Settings_;
    Core.MorseDecoderCore_.Settings_ = Settings_;

    SettingsLoad();

    on_SpectrogramAmpT_valueChanged(ui->SpectrogramAmpT->value());
    on_VUAmpT_valueChanged(ui->VUAmpT->value());
    on_SpectrogramResolutionT_valueChanged(ui->SpectrogramResolutionT->value());
    on_SpectrogramZoomT_valueChanged(ui->SpectrogramZoomT->value());
    on_SpectrogramWindowT_valueChanged(ui->SpectrogramWindowT->value());
    on_SpectrogramOffsetT_valueChanged(ui->SpectrogramOffsetT->value());
    on_VUSizeT_valueChanged(ui->VUSizeT->value());
    on_CalcThrAttackT_valueChanged(ui->CalcThrAttackT->value());
    on_CalcThrDecayT_valueChanged(ui->CalcThrDecayT->value());
    on_ProcessCountAttackT_valueChanged(ui->ProcessCountAttackT->value());
    on_ProcessCountDecayT_valueChanged(ui->ProcessCountDecayT->value());
    on_SpectrogramStepT_valueChanged(ui->SpectrogramStepT->value());
    on_SpectrogramBaseT_valueChanged(ui->SpectrogramBaseT->value());
    on_SpectrogramLinesT_valueChanged(ui->SpectrogramLinesT->value());
    on_VUMode_currentIndexChanged(ui->VUMode->currentIndex());
    on_SpectrogramMinMaxT_valueChanged(ui->SpectrogramMinMaxT->value());

    Core.CreateFilter(Core.FilterWindow, 0, 0.5);
    Core.CreateFilter(Core.FilterWindowRef, 0, 0.5);
    Core.MorseEncoderCore_.CalcPeriod(0, 0.5);

    Core.MorseDecoderCore_.MorseEncoderCore_ = &(Core.MorseEncoderCore_);

    AR = NEW(EdenClass::AudioRecorder, EdenClass::AudioRecorder());
    AP = NEW(EdenClass::AudioPlayer, EdenClass::AudioPlayer());

    SpectrogramBmp = NEW(QImage, QImage(Core.SpectrogramFullMaxW, Core.SpectrogramFullMaxH, QImage::Format_RGB32));
    DrawSpectrogram();

    SS.Core = &Core;
    SS.Init(AR->GetDeviceList(), AP->GetDeviceList(), AR, AP);
    QObject::connect(&SS, SIGNAL(GuiChange()), this, SLOT(GuiChange()));


    MDS.MorseDecoderCore_ = &(Core.MorseDecoderCore_);
    MDS.MorseEncoderCore_ = &(Core.MorseEncoderCore_);
    MDS.Settings_ = Settings_;
    MDS.Init();
    IT.Settings_ = Settings_;
    IT.Init();
    IT.MorseEncoderCore_ = &(Core.MorseEncoderCore_);
    IT.MorseDecoderCore_ = &(Core.MorseDecoderCore_);

    AudioTempP = NEWARR(short, short[AudioBufferSize]);

    RefreshVisible(true);
}

MainWindow::~MainWindow()
{
    SettingsSave();
    ui->SpectrogramL->ImgX = NULL;
    DEL(QImage, SpectrogramBmp);
    DEL(Settings, Settings_);
    DEL(EdenClass::AudioRecorder, AR);
    DEL(EdenClass::AudioPlayer, AP);
    DELARR(short, AudioTempP);
    delete ui;
}

bool MainWindow::IsSpectrumFull()
{
    if (SpecF.isHidden())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void MainWindow::DrawSpectrogram()
{
    if (IsSpectrumFull())
    {
        SpecF.DrawSpectrum(SpectrogramBmp);
    }
    else
    {
        ui->SpectrogramL->ImgX = SpectrogramBmp;
        ui->SpectrogramL->repaint();
    }
}

void MainWindow::on_SoundStart_clicked()
{
    Settings_->SpectrogramMarkersUpdate = true;

    if (AudioWork)
    {
        return;
    }

    if (RecordBufL > 0)
    {
        RecordBufL = 0;
        DELARR(short, RecordBuf);
    }
    RecordBufL = 2;
    RecordBuf = NEWARR(short, short[4]);

    AP->SelectDevice(Settings_->DeviceO);
    AR->SelectDevice(Settings_->DeviceI);

    Settings_->CalcSampleRate();

    Core.AudioFileBufferSession = Settings_->AudioFileBuffer;
    Settings_->SpectrogramChanged = true;
    Core.F.Init(SpectrumResolutionFactor >> Core.SpectrogramResolution, Settings_->WindowType, Core.WindowFactor);
    Settings_->DisplayGammaUpdate = true;
    Core.SetGamma(IsSpectrumFull());

    SampleRate = Settings_->SampleRate;
    Core.MorseEncoderCore_.BufReset();

    PlayerInputChunkSize = Settings_->PlayerInputChunkSize;

    AR->StereoMode = Settings_->StereoMode + 1;
    AR->SetParams(SampleRate, 2, 1, Settings_->AudioBufferR, 0);
    if (Settings_->PlayerEnabled)
    {
        AP->SetParams(SampleRate, 2, 1, Settings_->AudioBufferP, 0);
    }

    DELARRNULL(short, Core.ReplayBuffer);
    if (!Settings_->AudioFileBuffer)
    {
        Core.ReplayBufferP = 0;
        Core.ReplayBufferF = 0;
        Core.ReplayBufferL = Settings_->ReplayBufferSize;
        if (Core.ReplayBufferL > 0)
        {
            Core.ReplayBuffer = NEWARRINIT(short, short[Core.ReplayBufferL], Core.ReplayBufferL, 0);
        }
    }

    if (Core.BufOpen(SampleRate))
    {
        if (ProgTimer__ != NULL)
        {
            //delete ProgTimer_;
            delete ProgTimer__;
        }
        //!!! ProgTimer_ = NEW(ProgTimer, ProgTimer(Settings_->RefreshPeriod, AR, AP));
        //!!! ProgTimer__ = NEW(QThread, QThread(this));
        ProgTimer_ = new ProgTimer(Settings_->RefreshPeriod, AR, AP);
        ProgTimer__ = new QThread(this);

        ProgTimer_->moveToThread(ProgTimer__);
        QObject::connect(ProgTimer_, SIGNAL(TimerEvent()), this, SLOT(AudioTimerTick()));
        ProgTimer__->start();

        AudioWork = true;
        AR->BufferFlush();
        AR->RecordStart();
        if (Settings_->PlayerEnabled)
        {
            AP->BufferFlush();
            AP->PlayStart();
        }
    }
}

void MainWindow::on_SoundStop_clicked()
{
    if (!AudioWork)
    {
        return;
    }

    ProgTimer_->deleteLater();
    ProgTimer__->quit();;
    ProgTimer__->wait();

    AudioWork = false;
    AR->RecordStop();
    if (Settings_->PlayerEnabled)
    {
        AP->PlayStop();
    }
    Core.BufClose();
    if (RecordBufL > 0)
    {
        RecordBufL = 0;
        DELARR(short, RecordBuf);
    }
    //!!! DEL(ProgTimer, ProgTimer_);
    //!!! DEL(QThread, ProgTimer__);
    DELNULL(short, Core.ReplayBuffer);
}

void MainWindow::AudioTimerTick()
{
    RefreshVisible(false);

    Core.FilterSize = Settings_->FilterSize;
    Core.SetGamma(IsSpectrumFull());


    // Przetwarzanie kolejki czynnosci
    while (!SpecF.KeyRequests.empty())
    {
        int KeyRequest_ = SpecF.KeyRequests.front();
        SpecF.KeyRequests.pop();
        switch (KeyRequest_)
        {
            case 11: ui->SpectrogramAmpT->setValue(ui->SpectrogramAmpT->value() + 1); break;
            case 12: ui->SpectrogramAmpT->setValue(ui->SpectrogramAmpT->value() - 1); break;
            case 21: ui->SpectrogramResolutionT->setValue(ui->SpectrogramResolutionT->value() + 1); break;
            case 22: ui->SpectrogramResolutionT->setValue(ui->SpectrogramResolutionT->value() - 1); break;
            case 23: ui->SpectrogramWindowT->setValue(ui->SpectrogramWindowT->value() + 1); break;
            case 24: ui->SpectrogramWindowT->setValue(ui->SpectrogramWindowT->value() - 1); break;
            case 31: ui->SpectrogramZoomT->setValue(ui->SpectrogramZoomT->value() + 1); break;
            case 32: ui->SpectrogramZoomT->setValue(ui->SpectrogramZoomT->value() - 1); break;
            case 33: ui->SpectrogramOffsetT->setValue(ui->SpectrogramOffsetT->value() + 1); break;
            case 34: ui->SpectrogramOffsetT->setValue(ui->SpectrogramOffsetT->value() - 1); break;
            case 41: ui->SpectrogramStepT->setValue(ui->SpectrogramStepT->value() + 1); break;
            case 42: ui->SpectrogramStepT->setValue(ui->SpectrogramStepT->value() - 1); break;
            case 43: ui->SpectrogramBaseT->setValue(ui->SpectrogramBaseT->value() + 1); break;
            case 44: ui->SpectrogramBaseT->setValue(ui->SpectrogramBaseT->value() - 1); break;
            case 45: ui->SpectrogramMinMaxT->setValue(ui->SpectrogramMinMaxT->value() + 1); break;
            case 46: ui->SpectrogramMinMaxT->setValue(ui->SpectrogramMinMaxT->value() - 1); break;
            case 50:
            {
                int X = ui->DrawMode->currentIndex();
                if ((X >= 5) || (X < 0))
                {
                    ui->DrawMode->setCurrentIndex(0);
                }
                else
                {
                    if (X >= 0)
                    {
                        ui->DrawMode->setCurrentIndex(X + 1);
                    }
                }
                break;
            }
            case 51: ui->SpectrogramLinesT->setValue(ui->SpectrogramLinesT->value() + 1); break;
            case 52: ui->SpectrogramLinesT->setValue(ui->SpectrogramLinesT->value() - 1); break;
            case 53:
            {
                if (ui->BufSpeedS->value() > 0)
                {
                    ui->BufSpeedS->setValue(0);
                }
                else
                {
                    ui->BufSpeedS->setValue(100);
                    Core.BufNext(0);
                }
                break;
            }
        }
    }

    int X;
    if (Settings_->PlayerEnabled)
    {
        X = AP->GetAudioRemaining();
        if (X <= PlayerInputChunkSize)
        {
            Core.GetPlaybackSamples(AudioTempP, PlayerInputChunkSize);
            Core.MorseEncoderCore_.GetSamples(AudioTempP, PlayerInputChunkSize);
            AP->PutToBuffer(AudioTempP, PlayerInputChunkSize);
        }
    }

    X = AR->GetAudioRemaining();
    if (X > 0)
    {
        if (Settings_->SpectrogramChanged)
        {
            Core.F.Init(SpectrumResolutionFactor >> Core.SpectrogramResolution, Settings_->WindowType, Core.WindowFactor);
            Settings_->SpectrogramChanged = false;
        }


        if (X > RecordBufL)
        {
            DELARR(short, RecordBuf);
            RecordBuf = NEWARR(short, short[X << 1]);
            RecordBufL = X;
        }
        RecordBuf = AR->GetFromBuffer16(X, RecordBuf);
        if (AudioWork)
        {
            if (Settings_->FileAudioWork)
            {
                for (int I = 0; I < X; I++)
                {
                    Core.AudioTempX[I] = Core.FileAudioData[Core.FileAudioPointer];
                    Core.FileAudioPointer++;
                    if (Core.FileAudioPointer >= Core.FileAudioLength)
                    {
                        Core.FileAudioPointer = 0;
                    }
                }

                // Processing audio
                Core.ProcessAudio(Core.AudioTempX, X);
            }
            else
            {
                memcpy(Core.AudioTempX, RecordBuf, X << 1);
                //for (int I = 0; I < X; I++)
                //{
                //    Core.AudioTempX[I] = RecordBuf[I];
                //}

                // Processing audio
                Core.ProcessAudio(Core.AudioTempX, X);
            }

            // Invoking timer event and drawing spectrogram
            if (IsSpectrumFull())
            {
                Core.AudioTimerTrigger(SpectrogramBmp->bits(), SpecF.PicW(), SpecF.PicH());
            }
            else
            {
                Core.AudioTimerTrigger(SpectrogramBmp->bits(), ui->SpectrogramL->width(), ui->SpectrogramL->height());
            }

            // Displaying spectrogram
            DrawSpectrogram();

            // Displaying received text
            Core.MorseEncoderCore_.ProcessBuffer();
            PT.Print(Core.MorseBufGet());

            // Displaying rerecord buffer time to current time
            QString T1 = Eden::ToQStr(Core.BufTime / 60);
            QString T2 = Eden::ToQStr(Core.BufTime % 60);
            if (T1.size() < 2) { T1 = "0" + T1; };
            if (T2.size() < 2) { T2 = "0" + T2; };
            ui->BufSpeed1L->setText(T1 + ":" + T2);
        }
    }
}

void MainWindow::on_SpectrogramAmpT_valueChanged(int value)
{
    Core.SpectrogramAmp = pow(2, value);
    ui->SpectrogramAmpV->setText(Eden::ToQStr((int)Core.SpectrogramAmp));
    Core.WholeRepaint = 1;
    SetLabels();
}

void MainWindow::on_SpectrogramResolutionT_valueChanged(int value)
{
    int ValueX = 8 - value;
    Core.SpectrogramResolution = ValueX;
    Settings_->SpectrogramChanged = true;
    ui->SpectrogramResolutionV->setText(Eden::ToQStr((SpectrumResolutionFactor / 2) >> Core.SpectrogramResolution));
    Core.ClearBuffers();
    SetLabels();
}

void MainWindow::on_SpectrogramZoomT_valueChanged(int value)
{
    Core.SpectrogramZoom = value;
    /*if (value >= 0)
    {
        ui->SpectrogramZoomV->setText(Eden::ToQStr((int)(pow(2, value))) + "/1");
    }
    else
    {
        ui->SpectrogramZoomV->setText("1/" + Eden::ToQStr((int)(pow(2, 0 - value))));
    }*/
    if (value >= 0)
    {
        ui->SpectrogramZoomV->setText(Eden::ToQStr((int)(512 * pow(2, value))));
    }
    else
    {
        ui->SpectrogramZoomV->setText(Eden::ToQStr((int)(512 / pow(2, 0 - value))));
    }
    Core.ClearBuffers();
    SetLabels();
}

void MainWindow::on_SpectrogramOffsetT_valueChanged(int value)
{
    Core.SpectrogramOffset = value * 16;
    ui->SpectrogramOffsetV->setText(Eden::ToQStr(value) + "/64");
    Core.WholeRepaint = 1;
    SetLabels();
}

void MainWindow::on_VUAmpT_valueChanged(int value)
{
    Core.VUAmp = pow(2, value);
    ui->VUAmpV->setText(Eden::ToQStr((int)Core.VUAmp));
    Core.WholeRepaint = 1;
}

void MainWindow::on_VUSizeT_valueChanged(int value)
{
    Core.VUSize = value;
    ui->VUSizeV->setText(Eden::ToQStr(value));
}

void MainWindow::on_CalcThrAttackT_valueChanged(int value)
{
    if (value < ui->CalcThrDecayT->value())
    {
        ui->CalcThrDecayT->setValue(value);
    }
    double Val = value;
    Val = Val / 100.0;
    Core.VUCalcAttackThreshold = Val;
    ui->CalcThrAttackV->setText(Eden::ToQStr(value * 4));
}

void MainWindow::on_CalcThrDecayT_valueChanged(int value)
{
    if (value > ui->CalcThrAttackT->value())
    {
        ui->CalcThrAttackT->setValue(value);
    }
    double Val = value;
    Val = Val / 100.0;
    Core.VUCalcDecayThreshold = Val;
    ui->CalcThrDecayV->setText(Eden::ToQStr(value * 4));
}

void MainWindow::on_ProcessCountAttackT_valueChanged(int value)
{
    Core.VUCalcAttackL = value;
    ui->ProcessCountAttackV->setText(Eden::ToQStr(value));
}

void MainWindow::on_ProcessCountDecayT_valueChanged(int value)
{
    Core.VUCalcDecayL = value;
    ui->ProcessCountDecayV->setText(Eden::ToQStr(value));
}

void MainWindow::on_WithRefC_toggled(bool checked)
{
    Core.WithRef = checked;
}

void MainWindow::on_SpectrogramStepT_valueChanged(int value)
{
    Core.SpectrogramStep = powl(2, value);
    ui->SpectrogramStepV->setText(Eden::ToQStr(Core.SpectrogramStep));
    Core.WholeRepaint = 1;
    SetLabels();
}

void MainWindow::on_SoundSettings_clicked()
{
    SS.show();
    SS.activateWindow();
    SS.raise();
    SS.setFocus();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    AudioWork = false;
    Core.BufClose();
    event++;
    event--;

    SpecF.close();
    MDS.close();
    SS.close();
    IT.close();
    PT.close();
    SpecS.close();
}

void MainWindow::on_SpectrogramL_MouseMove(int Btn, int X, int Y)
{
    if (!IsSpectrumFull())
    {
        Core.MouseOperation(Btn, X, Y, SpectrogramBmp->bits());
    }
}

void MainWindow::on_SpectrogramL_MousePress(int Btn, int X, int Y)
{
    if (!IsSpectrumFull())
    {
        Core.MouseOperation(Btn, X, Y, SpectrogramBmp->bits());
    }
}

void MainWindow::on_SpectrogramL_MouseRelease(int Btn, int X, int Y)
{
    if (!IsSpectrumFull())
    {
        Core.MouseOperation(Btn, X, Y, SpectrogramBmp->bits());
    }
}

void MainWindow::on_PrintText_clicked()
{
    PT.show();
    PT.activateWindow();
    PT.raise();
    PT.setFocus();
}

void MainWindow::on_MorseCalcB_clicked()
{
    Core.MorseDecoderCore_.Calc();
}

void MainWindow::on_MorseBufferClear_clicked()
{
    Core.MorseDecoderCore_.BufferClear();
}

void MainWindow::on_MorseBufferBegin_clicked()
{
    Core.MorseDecoderCore_.GetWhole();
}

void MainWindow::on_MorseSettingsB_clicked()
{
    MDS.show();
    MDS.activateWindow();
    MDS.raise();
    MDS.setFocus();
}

void MainWindow::on_MorseRealTime_toggled(bool checked)
{
    Core.MorseDecoderCore_.ProcessBuffer();
    Core.MorseDecoderCore_.RealTime = checked;
}

void MainWindow::on_MorseBufferCurrent_clicked()
{
    Core.MorseDecoderCore_.ProcessBuffer();
}

void MainWindow::on_BufSpeedS_valueChanged(int value)
{
    ui->BufSpeed2L->setText(Eden::ToQStr(value) + "%");
    Core.BufSpeed = value;
}

void MainWindow::on_BufPrev_clicked()
{
    Core.BufPrev(0);
}

void MainWindow::on_BufPrevLong_clicked()
{
    Core.BufPrev(180);
}

void MainWindow::on_BufPrevShort_clicked()
{
    Core.BufPrev(15);
}

void MainWindow::on_BufNext_clicked()
{
    Core.BufNext(0);
}

void MainWindow::on_BufNextLong_clicked()
{
    Core.BufNext(180);
}

void MainWindow::on_BufNextShort_clicked()
{
    Core.BufNext(15);
}

void MainWindow::on_BufPlay_clicked()
{
    ui->BufSpeedS->setValue(100);
}

void MainWindow::on_BufPause_clicked()
{
    ui->BufSpeedS->setValue(0);
}

void MainWindow::on_MorseWork_toggled(bool checked)
{
    Core.MorseWork = checked;
}

void MainWindow::on_MorseBufferLast_clicked()
{
    Core.MorseDecoderCore_.ProcessLast(Settings_->MorseBufferLast);
}

void MainWindow::on_InputText_clicked()
{
    IT.show();
    IT.activateWindow();
    IT.raise();
    IT.setFocus();
}

void MainWindow::on_SoundSpectrumFull_clicked()
{
    SpecF.SetMouse();
    SpecF.ApplySettings(Settings_->SpectrogramLayoutSize, Settings_->SpectrogramLayoutOrientation);
    SpecF.show();
    SpecF.activateWindow();
    SpecF.raise();
    SpecF.setFocus();
}

void MainWindow::on_SpectrogramSettings_clicked()
{
    SpecS.Settings_ = Settings_;
    SpecS.Init();
    SpecS.show();
    SpecS.activateWindow();
    SpecS.raise();
    SpecS.setFocus();
}

void MainWindow::on_SpectrogramBaseT_valueChanged(int value)
{
    Core.SpectrogramBase = value;
    ui->SpectrogramBaseV->setText(Eden::ToQStr(Core.SpectrogramBase) + "/64");
    Core.WholeRepaint = 1;
    SetLabels();
}

void MainWindow::SettingsLoad()
{
    CFP.FileLoad(Eden::ApplicationDirectory() + "Params.txt");

    int X;

    X = -1; CFP.ParamGet("SpectrogramAmpT", X); if (X >= 0) { ui->SpectrogramAmpT->setValue(X); }
    X = -1; CFP.ParamGet("SpectrogramResolutionT", X); if (X >= 0) { ui->SpectrogramResolutionT->setValue(X); }
    X = -100; CFP.ParamGet("SpectrogramZoomT", X); if (X >= -99) { ui->SpectrogramZoomT->setValue(X); }
    X = -1; CFP.ParamGet("SpectrogramWindowT", X); if (X >= 0) { ui->SpectrogramWindowT->setValue(X); }
    X = -1; CFP.ParamGet("SpectrogramOffsetT", X); if (X >= 0) { ui->SpectrogramOffsetT->setValue(X); }
    X = -1; CFP.ParamGet("SpectrogramStepT", X); if (X >= 0) { ui->SpectrogramStepT->setValue(X); }
    X = -1; CFP.ParamGet("SpectrogramBaseT", X); if (X >= 0) { ui->SpectrogramBaseT->setValue(X); }
    X = -1; CFP.ParamGet("SpectrogramLinesT", X); if (X >= 0) { ui->SpectrogramLinesT->setValue(X); }
    X = -100; CFP.ParamGet("SpectrogramMinMaxT", X); if (X >= -99) { ui->SpectrogramMinMaxT->setValue(X); }
    X = -1; CFP.ParamGet("DrawMode", X); if (X >= 0) { ui->DrawMode->setCurrentIndex(X); }
    X = -1; CFP.ParamGet("DrawVU", X); if (X >= 0) { ui->DrawVU->setCurrentIndex(X); }

    X = -1; CFP.ParamGet("WithRefC", X); if (X >= 0) { ui->WithRefC->setChecked(X == 1); }
    X = -1; CFP.ParamGet("VUMode", X); if (X >= 0) { ui->VUMode->setCurrentIndex(X); }
    X = -1; CFP.ParamGet("VUAmpT", X); if (X >= 0) { ui->VUAmpT->setValue(X); }
    X = -1; CFP.ParamGet("VUSizeT", X); if (X >= 0) { ui->VUSizeT->setValue(X); }
    X = -1; CFP.ParamGet("CalcThrAttackT", X); if (X >= 0) { ui->CalcThrAttackT->setValue(X); }
    X = -1; CFP.ParamGet("CalcThrDecayT", X); if (X >= 0) { ui->CalcThrDecayT->setValue(X); }
    X = -1; CFP.ParamGet("ProcessCountAttackT", X); if (X >= 0) { ui->ProcessCountAttackT->setValue(X); }
    X = -1; CFP.ParamGet("ProcessCountDecayT", X); if (X >= 0) { ui->ProcessCountDecayT->setValue(X); }
    X = -1; CFP.ParamGet("DecodeCorrectionC", X); if (X >= 0) { ui->DecodeCorrectionC->setChecked(X == 1); }
}

void MainWindow::SettingsSave()
{
    CFP.ParamClear();

    CFP.ParamSet("SpectrogramAmpT", ui->SpectrogramAmpT->value());
    CFP.ParamSet("SpectrogramResolutionT", ui->SpectrogramResolutionT->value());
    CFP.ParamSet("SpectrogramZoomT", ui->SpectrogramZoomT->value());
    CFP.ParamSet("SpectrogramWindowT", ui->SpectrogramWindowT->value());
    CFP.ParamSet("SpectrogramOffsetT", ui->SpectrogramOffsetT->value());
    CFP.ParamSet("SpectrogramStepT", ui->SpectrogramStepT->value());
    CFP.ParamSet("SpectrogramBaseT", ui->SpectrogramBaseT->value());
    CFP.ParamSet("SpectrogramLinesT", ui->SpectrogramLinesT->value());
    CFP.ParamSet("SpectrogramMinMaxT", ui->SpectrogramMinMaxT->value());
    CFP.ParamSet("DrawMode", ui->DrawMode->currentIndex());
    CFP.ParamSet("DrawVU", ui->DrawVU->currentIndex());

    CFP.ParamSet("WithRefC", ui->WithRefC->isChecked());
    CFP.ParamSet("VUMode", ui->VUMode->currentIndex());
    CFP.ParamSet("VUAmpT", ui->VUAmpT->value());
    CFP.ParamSet("VUSizeT", ui->VUSizeT->value());
    CFP.ParamSet("CalcThrAttackT", ui->CalcThrAttackT->value());
    CFP.ParamSet("CalcThrDecayT", ui->CalcThrDecayT->value());
    CFP.ParamSet("ProcessCountAttackT", ui->ProcessCountAttackT->value());
    CFP.ParamSet("ProcessCountDecayT", ui->ProcessCountDecayT->value());
    CFP.ParamSet("DecodeCorrectionC", ui->DecodeCorrectionC->isChecked());

    CFP.FileSave(Eden::ApplicationDirectory() + "Params.txt");
}

void MainWindow::on_SpectrogramWindowT_valueChanged(int value)
{
    int P = value & 3;
    int ValX = value >> 2;
    double X, XX, X1, X2, XX1, XX2;
    X1 = pow(2, ValX + 0);
    X2 = pow(2, ValX + 1);
    XX1 = pow(2, 10 - 0 - ValX);
    XX2 = pow(2, 10 - 1 - ValX);
    switch (P)
    {
        case 0: X = X1 * X1 * X1 * X1; XX = XX1 * XX1 * XX1 * XX1; break;
        case 1: X = X1 * X1 * X1 * X2; XX = XX1 * XX1 * XX1 * XX2; break;
        case 2: X = X1 * X1 * X2 * X2; XX = XX1 * XX1 * XX2 * XX2; break;
        case 3: X = X1 * X2 * X2 * X2; XX = XX1 * XX2 * XX2 * XX2; break;
    }

    X = sqrt(sqrt(X));
    XX = sqrt(sqrt(XX));

    Core.WindowFactor = X;
    Settings_->SpectrogramChanged = true;
    int Val = round(XX * 100.0);
    ui->SpectrogramWindowV->setText("100/" + Eden::ToQStr(Val));
    Core.ClearBuffers();
    SetLabels();
}

void MainWindow::SliderInc(QSlider * S)
{
    if (S->value() < S->maximum())
    {
        S->setValue(S->value() + 1);
    }
}

void MainWindow::SliderDec(QSlider * S)
{
    if (S->value() > S->minimum())
    {
        S->setValue(S->value() - 1);
    }
}

void MainWindow::SetLabels()
{
    SpecF.SetLabels(ui->SpectrogramAmpV->text(), ui->SpectrogramResolutionV->text(), ui->SpectrogramWindowV->text(), ui->SpectrogramZoomV->text(), ui->SpectrogramOffsetV->text(), ui->SpectrogramStepV->text(), ui->SpectrogramBaseV->text(), ui->SpectrogramMinMaxV->text(), Eden::ToQStr(Core.SpectrogramDisplayLines));
}

void MainWindow::on_BufSpeed1L_MousePress(int X, int Y, int B) { SliderDec(ui->BufSpeedS); X++; Y++; B++; }
void MainWindow::on_BufSpeed2L_MousePress(int X, int Y, int B) { SliderInc(ui->BufSpeedS); X++; Y++; B++; }

void MainWindow::on_SpectrogramAmpL_MousePress(int X, int Y, int B) { SliderDec(ui->SpectrogramAmpT); X++; Y++; B++; }
void MainWindow::on_SpectrogramAmpV_MousePress(int X, int Y, int B) { SliderInc(ui->SpectrogramAmpT); X++; Y++; B++; }
void MainWindow::on_SpectrogramResolutionL_MousePress(int X, int Y, int B) { SliderDec(ui->SpectrogramResolutionT); X++; Y++; B++; }
void MainWindow::on_SpectrogramResolutionV_MousePress(int X, int Y, int B) { SliderInc(ui->SpectrogramResolutionT); X++; Y++; B++; }
void MainWindow::on_SpectrogramWindowL_MousePress(int X, int Y, int B) { SliderDec(ui->SpectrogramWindowT); X++; Y++; B++; }
void MainWindow::on_SpectrogramWindowV_MousePress(int X, int Y, int B) { SliderInc(ui->SpectrogramWindowT); X++; Y++; B++; }
void MainWindow::on_SpectrogramZoomL_MousePress(int X, int Y, int B) { SliderDec(ui->SpectrogramZoomT); X++; Y++; B++; }
void MainWindow::on_SpectrogramZoomV_MousePress(int X, int Y, int B) { SliderInc(ui->SpectrogramZoomT); X++; Y++; B++; }
void MainWindow::on_SpectrogramOffsetL_MousePress(int X, int Y, int B) { SliderDec(ui->SpectrogramOffsetT); X++; Y++; B++; }
void MainWindow::on_SpectrogramOffsetV_MousePress(int X, int Y, int B) { SliderInc(ui->SpectrogramOffsetT); X++; Y++; B++; }
void MainWindow::on_SpectrogramStepL_MousePress(int X, int Y, int B) { SliderDec(ui->SpectrogramStepT); X++; Y++; B++; }
void MainWindow::on_SpectrogramStepV_MousePress(int X, int Y, int B) { SliderInc(ui->SpectrogramStepT); X++; Y++; B++; }
void MainWindow::on_SpectrogramBaseL_MousePress(int X, int Y, int B) { SliderDec(ui->SpectrogramBaseT); X++; Y++; B++; }
void MainWindow::on_SpectrogramBaseV_MousePress(int X, int Y, int B) { SliderInc(ui->SpectrogramBaseT); X++; Y++; B++; }
void MainWindow::on_SpectrogramLinesL_MousePress(int X, int Y, int B) { SliderDec(ui->SpectrogramLinesT); X++; Y++; B++; }
void MainWindow::on_SpectrogramLinesV_MousePress(int X, int Y, int B) { SliderInc(ui->SpectrogramLinesT); X++; Y++; B++; }
void MainWindow::on_SpectrogramMinMaxL_MousePress(int X, int Y, int B) { SliderDec(ui->SpectrogramMinMaxT); X++; Y++; B++; }
void MainWindow::on_SpectrogramMinMaxV_MousePress(int X, int Y, int B) { SliderInc(ui->SpectrogramMinMaxT); X++; Y++; B++; }

void MainWindow::on_VUAmpL_MousePress(int X, int Y, int B) { SliderDec(ui->VUAmpT); X++; Y++; B++; }
void MainWindow::on_VUAmpV_MousePress(int X, int Y, int B) { SliderInc(ui->VUAmpT); X++; Y++; B++; }
void MainWindow::on_VUSizeL_MousePress(int X, int Y, int B) { SliderDec(ui->VUSizeT); X++; Y++; B++; }
void MainWindow::on_VUSizeV_MousePress(int X, int Y, int B) { SliderInc(ui->VUSizeT); X++; Y++; B++; }
void MainWindow::on_CalcThrAttackL_MousePress(int X, int Y, int B) { SliderDec(ui->CalcThrAttackT); X++; Y++; B++; }
void MainWindow::on_CalcThrAttackV_MousePress(int X, int Y, int B) { SliderInc(ui->CalcThrAttackT); X++; Y++; B++; }
void MainWindow::on_CalcThrDecayL_MousePress(int X, int Y, int B) { SliderDec(ui->CalcThrDecayT); X++; Y++; B++; }
void MainWindow::on_CalcThrDecayV_MousePress(int X, int Y, int B) { SliderInc(ui->CalcThrDecayT); X++; Y++; B++; }
void MainWindow::on_ProcessCountAttackL_MousePress(int X, int Y, int B) { SliderDec(ui->ProcessCountAttackT); X++; Y++; B++; }
void MainWindow::on_ProcessCountAttackV_MousePress(int X, int Y, int B) { SliderInc(ui->ProcessCountAttackT); X++; Y++; B++; }
void MainWindow::on_ProcessCountDecayL_MousePress(int X, int Y, int B) { SliderDec(ui->ProcessCountDecayT); X++; Y++; B++; }
void MainWindow::on_ProcessCountDecayV_MousePress(int X, int Y, int B) { SliderInc(ui->ProcessCountDecayT); X++; Y++; B++; }

void MainWindow::RefreshVisible(bool Force)
{
    if (Force || (ui->SpectrogramG->isVisible() != Settings_->VisibleSpectrogramG))
    {
        ui->SpectrogramG->setVisible(Settings_->VisibleSpectrogramG);
    }
    if (Force || (ui->ProcG->isVisible() != Settings_->VisibleProcG))
    {
        ui->ProcG->setVisible(Settings_->VisibleProcG);
    }
    bool ToolbarPanel1Vis = Settings_->VisibleSpectrogramG || Settings_->VisibleProcG;
    if (Force || (ui->ToolbarPanel1->isVisible() != ToolbarPanel1Vis))
    {
        ui->ToolbarPanel1->setVisible(ToolbarPanel1Vis);
    }
    if (Force || (ui->BufG->isVisible() != Settings_->VisibleBufG))
    {
        ui->BufG->setVisible(Settings_->VisibleBufG);
    }
    if (Force || (ui->BufSpeedG->isVisible() != Settings_->VisibleBufSpeedG))
    {
        ui->BufSpeedG->setVisible(Settings_->VisibleBufSpeedG);
    }
    if (Force || (ui->MorseG->isVisible() != Settings_->VisibleMorseG))
    {
        ui->MorseG->setVisible(Settings_->VisibleMorseG);
    }
}

void MainWindow::on_SpectrogramLinesT_valueChanged(int value)
{
    Core.SpectrogramDisplayLines = value;
    Core.DispHeightLast = 0;
    ui->SpectrogramLinesV->setText(Eden::ToQStr(value));
    Core.WholeRepaint = 1;
    SetLabels();
}

void MainWindow::on_DrawMode_currentIndexChanged(int index)
{
    if ((index >= 0) && (index <= 2))
    {
        Core.SpectrogramDrawMode = index;
        Core.SpectrogramDrawVolume = false;
    }
    if ((index >= 3) && (index <= 5))
    {
        Core.SpectrogramDrawMode = index - 3;
        Core.SpectrogramDrawVolume = true;
    }
    Core.DispHeightLast = 0;
}

void MainWindow::on_DrawVU_currentIndexChanged(int index)
{
    if ((index >= 0) && (index <= 3))
    {
        Core.SpectrogramDrawVU = index;
    }
    Core.DispHeightLast = 0;
}

void MainWindow::on_VUMode_currentIndexChanged(int index)
{
    Core.VUMode = index;
}


void MainWindow::on_DecodeCorrectionC_toggled(bool checked)
{
    Core.DecodeCorrection = checked;
}

void MainWindow::GuiChange()
{
    RefreshVisible(true);
}

void MainWindow::on_SpectrogramMinMaxT_valueChanged(int value)
{
    Core.SpectrogramMinMax = value;
    if (value >= 0)
    {
        Core.SpectrogramMinMaxX = value;
    }
    else
    {
        Core.SpectrogramMinMaxX = 0 - value;
    }
    ui->SpectrogramMinMaxV->setText(Eden::ToQStr(value));
    Core.WholeRepaint = 1;
    SetLabels();
}


void MainWindow::on_SoundAbout_clicked()
{
    About_.show();
    About_.activateWindow();
    About_.raise();
    About_.setFocus();
}
