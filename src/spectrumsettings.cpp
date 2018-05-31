#include "spectrumsettings.h"
#include "ui_spectrumsettings.h"

SpectrumSettings::SpectrumSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpectrumSettings)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
    ui->setupUi(this);
}

SpectrumSettings::~SpectrumSettings()
{
    delete ui;
}

void SpectrumSettings::Init()
{
    EventEnabled = false;
    ui->SpecNegativeW->setChecked(Settings_->SpectrogramNegative);
    ui->SpecFullStripT->setText(Eden::ToQStr(Settings_->SpectrogramStrip));
    ui->SpecFullLayoutS->setCurrentIndex(Settings_->SpectrogramLayoutOrientation);
    ui->SpecFullLayoutT->setText(Eden::ToQStr(Settings_->SpectrogramLayoutSize));
    ui->SpecFullScrollT->setText(Eden::ToQStr(Settings_->SpectrogramScrollCycle));
    ui->SpecFullGammaTW->setText(Eden::ToQStr(Settings_->DisplayGamma));
    ui->SpecFullMarkersC->setChecked(Settings_->SpectrogramMarkersEnable);
    ui->SpecFullMarkersText->setPlainText(Eden::ToQStr(Settings_->SpectrogramMarkers));
    ui->SpecMouseGraph->setChecked(Settings_->SpectrogramMouseGraph);
    ui->SpecMouseButtons->setChecked(Settings_->SpectrogramMouseButtons);
    ui->SpecDecimationT->setText(Eden::ToQStr(Settings_->CalcDecimation));
    ui->SpecDecimationC->setChecked(Settings_->CalcDecimationConst);
    ui->SpecOverThrT->setText(Eden::ToQStr(Settings_->OverloadThreshold));
    ui->SpecFullHalfT->setText(Eden::ToQStr(Settings_->HalfMarkSize));
    ui->SpecDispRW->setCurrentIndex(Settings_->SpectrumDisplayR);
    ui->SpecDispGW->setCurrentIndex(Settings_->SpectrumDisplayG);
    ui->SpecDispBW->setCurrentIndex(Settings_->SpectrumDisplayB);
    ui->SpecWindowS->setCurrentIndex(Settings_->WindowType);

    if (ui->SpecFullPaletteCW->count() == 0)
    {
        ui->SpecFullPaletteCW->addItem(Eden::ToQStr("(none)"));
        for (uint I = 0; I < Settings_->SpectrumPaletteName.size(); I++)
        {
            ui->SpecFullPaletteCW->addItem(Eden::ToQStr(Settings_->SpectrumPaletteName[I]));
        }
    }
    if (Settings_->SpectrumPaletteName.size() >= (uint)Settings_->SpectrumPaletteSelected)
    {
        ui->SpecFullPaletteCW->setCurrentIndex(Settings_->SpectrumPaletteSelected);
    }
    else
    {
        ui->SpecFullPaletteCW->setCurrentIndex(0);
    }
    EventEnabled = true;
}

void SpectrumSettings::on_SpecFullStripT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        if (Eden::ToInt(arg1) >= 0)
        {
            Settings_->SpectrogramStrip = Eden::ToInt(arg1);
        }
    }
}

void SpectrumSettings::on_SpecFullStripColor_clicked()
{
    QColor C;
    C.setRgb(Settings_->SpectrogramStripColorR, Settings_->SpectrogramStripColorG, Settings_->SpectrogramStripColorB);
    C = QColorDialog::getColor(C, this, "", 0);
    Settings_->SpectrogramStripColorR = C.red();
    Settings_->SpectrogramStripColorG = C.green();
    Settings_->SpectrogramStripColorB = C.blue();
}

void SpectrumSettings::on_SpecFullScrollT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        if (Eden::ToInt(arg1) > 0)
        {
            Settings_->SpectrogramScrollCycle = Eden::ToInt(arg1);
        }
    }
}

void SpectrumSettings::on_SpecFullLayoutS_currentIndexChanged(int index)
{
    if (EventEnabled)
    {
        Settings_->SpectrogramLayoutOrientation = index;
    }
}

void SpectrumSettings::on_SpecFullLayoutT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        if (Eden::ToInt(arg1) > 0)
        {
            Settings_->SpectrogramLayoutSize = Eden::ToInt(arg1);
        }
    }
}

void SpectrumSettings::on_SpecFullMarkersC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->SpectrogramMarkersEnable = checked;
        Settings_->SpectrogramMarkersUpdate = true;
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecFullMarkersText_textChanged()
{
    if (EventEnabled)
    {
        Settings_->SpectrogramMarkers = Eden::ToStr(ui->SpecFullMarkersText->toPlainText());
        Settings_->SpectrogramMarkersUpdate = true;
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecMouseGraph_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->SpectrogramMouseGraph = checked;
    }
}

void SpectrumSettings::on_SpecMouseButtons_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->SpectrogramMouseButtons = checked;
    }
}

void SpectrumSettings::on_SpecDecimationT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        if (Eden::ToInt(arg1) > 0)
        {
            Settings_->CalcDecimation = Eden::ToInt(arg1);
            Settings_->WholeRepaint = true;
        }
    }
}

void SpectrumSettings::on_SpecDecimationC_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->CalcDecimationConst = checked;
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecOverThrT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        Settings_->OverloadThreshold = Eden::ToInt(arg1);
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecOverThrColor_clicked()
{
    if (EventEnabled)
    {
        QColor C;
        C.setRgb(Settings_->OverloadColorR, Settings_->OverloadColorG, Settings_->OverloadColorB);
        C = QColorDialog::getColor(C, this, "", 0);
        Settings_->OverloadColorR = C.red();
        Settings_->OverloadColorG = C.green();
        Settings_->OverloadColorB = C.blue();
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecFullHalfColor_clicked()
{
    if (EventEnabled)
    {
        QColor C;
        C.setRgb(Settings_->HalfMarkColorR, Settings_->HalfMarkColorG, Settings_->HalfMarkColorB);
        C = QColorDialog::getColor(C, this, "", 0);
        Settings_->HalfMarkColorR = C.red();
        Settings_->HalfMarkColorG = C.green();
        Settings_->HalfMarkColorB = C.blue();
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecFullHalfT_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        Settings_->HalfMarkSize = Eden::ToInt(arg1);
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecDispRW_currentIndexChanged(int index)
{
    if (EventEnabled)
    {
        Settings_->SpectrumDisplayR = index;
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecDispGW_currentIndexChanged(int index)
{
    if (EventEnabled)
    {
        Settings_->SpectrumDisplayG = index;
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecDispBW_currentIndexChanged(int index)
{
    if (EventEnabled)
    {
        Settings_->SpectrumDisplayB = index;
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecFullGammaTW_textEdited(const QString &arg1)
{
    if (EventEnabled)
    {
        if (Eden::ToInt(arg1) > 0)
        {
            Settings_->DisplayGamma = Eden::ToInt(arg1);
            Settings_->DisplayGammaUpdate = true;
            Settings_->WholeRepaint = true;
        }
    }
}

void SpectrumSettings::on_SpecFullPaletteCW_currentIndexChanged(int index)
{
    if (EventEnabled)
    {
        Settings_->SpectrumPaletteSelected = index;
        Settings_->DisplayGammaUpdate = true;
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecWindowS_currentIndexChanged(int index)
{
    if (EventEnabled)
    {
        Settings_->WindowType = index;
        Settings_->SpectrogramChanged = true;
        Settings_->WholeRepaint = true;
    }
}

void SpectrumSettings::on_SpecNegativeW_toggled(bool checked)
{
    if (EventEnabled)
    {
        Settings_->SpectrogramNegative = checked;
        Settings_->WholeRepaint = true;
    }
}


