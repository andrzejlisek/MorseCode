#include "spectrumfull.h"
#include "ui_spectrumfull.h"

SpectrumFull::SpectrumFull(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpectrumFull)
{
    ui->setupUi(this);
    connect(ui->SpectrumScreen, SIGNAL(KeyPress(QKeyEvent*)), this, SLOT(KeyPress(QKeyEvent*)));
    connect(ui->SpectrumScreen, SIGNAL(KeyRelease(QKeyEvent*)), this, SLOT(KeyRelease(QKeyEvent*)));

    // Black background
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);
    ui->SpectrumScreen->setText("");

    SetLabels("?", "?", "?", "?", "?", "?", "?", "?", "?");
}

SpectrumFull::~SpectrumFull()
{
    delete ui;
}

void SpectrumFull::KeyPress(QKeyEvent * event)
{
    //qDebug() << event->key();

    if (event->key() == 81) // Q - Gain+
    {
        KeyRequests.push(11);
    }
    if (event->key() == 65) // A - Gain-
    {
        KeyRequests.push(12);
    }
    if (event->key() == 87) // W - Resolution+
    {
        KeyRequests.push(21);
    }
    if (event->key() == 83) // S - Resolution-
    {
        KeyRequests.push(22);
    }
    if (event->key() == 69) // E - Window+
    {
        KeyRequests.push(23);
    }
    if (event->key() == 68) // D - Window-
    {
        KeyRequests.push(24);
    }
    if (event->key() == 82) // R - Zoom+
    {
        KeyRequests.push(31);
    }
    if (event->key() == 70) // F - Zoom-
    {
        KeyRequests.push(32);
    }
    if (event->key() == 84) // T - Offset+
    {
        KeyRequests.push(33);
    }
    if (event->key() == 71) // G - Offset-
    {
        KeyRequests.push(34);
    }
    if (event->key() == 89) // Y - Step+
    {
        KeyRequests.push(41);
    }
    if (event->key() == 72) // H - Step-
    {
        KeyRequests.push(42);
    }
    if (event->key() == 85) // U - Base+
    {
        KeyRequests.push(43);
    }
    if (event->key() == 74) // J - Base-
    {
        KeyRequests.push(44);
    }
    if (event->key() == 73) // I - Min/Max+
    {
        KeyRequests.push(45);
    }
    if (event->key() == 75) // K - Min/Max-
    {
        KeyRequests.push(46);
    }
    if (event->key() == 79) // O - Line+
    {
        KeyRequests.push(51);
    }
    if (event->key() == 76) // L - Line-
    {
        KeyRequests.push(52);
    }
    if (event->key() == 90) // Z - Display mode
    {
        KeyRequests.push(50);
    }
    if (event->key() == 88) // X - Pause and resume display
    {
        KeyRequests.push(53);
    }
    if (event->key() == 67) // C - Full screen
    {
        hide();
        if (isFullScreen())
        {
            showNormal();
        }
        else
        {
            showFullScreen();
        }
    }
    SetFocus();
}

void SpectrumFull::KeyRelease(QKeyEvent * event)
{
    event++;
    event--;
    SetFocus();
}

void SpectrumFull::DrawSpectrum(QImage * Pic)
{
    ui->SpectrumScreen->ImgX = Pic;
    ui->SpectrumScreen->repaint();
}

int SpectrumFull::PicW()
{
    return ui->SpectrumScreen->width();
}

int SpectrumFull::PicH()
{
    return ui->SpectrumScreen->height();
}

void SpectrumFull::ApplySettings(int LayoutSize, int LayoutOrientation)
{
    ui->BtnNGainDn->setMinimumHeight(LayoutSize);
    ui->BtnNGainDn->setMaximumHeight(LayoutSize);
    ui->BtnNGainUp->setMinimumHeight(LayoutSize);
    ui->BtnNGainUp->setMaximumHeight(LayoutSize);
    ui->BtnNResoDn->setMinimumHeight(LayoutSize);
    ui->BtnNResoDn->setMaximumHeight(LayoutSize);
    ui->BtnNResoUp->setMinimumHeight(LayoutSize);
    ui->BtnNResoUp->setMaximumHeight(LayoutSize);
    ui->BtnNWindDn->setMinimumHeight(LayoutSize);
    ui->BtnNWindDn->setMaximumHeight(LayoutSize);
    ui->BtnNWindUp->setMinimumHeight(LayoutSize);
    ui->BtnNWindUp->setMaximumHeight(LayoutSize);
    ui->BtnNZoomDn->setMinimumHeight(LayoutSize);
    ui->BtnNZoomDn->setMaximumHeight(LayoutSize);
    ui->BtnNZoomUp->setMinimumHeight(LayoutSize);
    ui->BtnNZoomUp->setMaximumHeight(LayoutSize);
    ui->BtnNOffsDn->setMinimumHeight(LayoutSize);
    ui->BtnNOffsDn->setMaximumHeight(LayoutSize);
    ui->BtnNOffsUp->setMinimumHeight(LayoutSize);
    ui->BtnNOffsUp->setMaximumHeight(LayoutSize);
    ui->BtnNStepDn->setMinimumHeight(LayoutSize);
    ui->BtnNStepDn->setMaximumHeight(LayoutSize);
    ui->BtnNStepUp->setMinimumHeight(LayoutSize);
    ui->BtnNStepUp->setMaximumHeight(LayoutSize);
    ui->BtnNBaseDn->setMinimumHeight(LayoutSize);
    ui->BtnNBaseDn->setMaximumHeight(LayoutSize);
    ui->BtnNBaseUp->setMinimumHeight(LayoutSize);
    ui->BtnNBaseUp->setMaximumHeight(LayoutSize);
    ui->BtnNMiMaDn->setMinimumHeight(LayoutSize);
    ui->BtnNMiMaDn->setMaximumHeight(LayoutSize);
    ui->BtnNMiMaUp->setMinimumHeight(LayoutSize);
    ui->BtnNMiMaUp->setMaximumHeight(LayoutSize);
    ui->BtnNLineDn->setMinimumHeight(LayoutSize);
    ui->BtnNLineDn->setMaximumHeight(LayoutSize);
    ui->BtnNLineUp->setMinimumHeight(LayoutSize);
    ui->BtnNLineUp->setMaximumHeight(LayoutSize);
    ui->BtnNMode__->setMinimumHeight(LayoutSize);
    ui->BtnNMode__->setMaximumHeight(LayoutSize);
    ui->BtnNPaus__->setMinimumHeight(LayoutSize);
    ui->BtnNPaus__->setMaximumHeight(LayoutSize);
    ui->BtnNFull__->setMinimumHeight(LayoutSize);
    ui->BtnNFull__->setMaximumHeight(LayoutSize);
    ui->BtnNClos__->setMinimumHeight(LayoutSize);
    ui->BtnNClos__->setMaximumHeight(LayoutSize);

    ui->BtnSGainDn->setMinimumHeight(LayoutSize);
    ui->BtnSGainDn->setMaximumHeight(LayoutSize);
    ui->BtnSGainUp->setMinimumHeight(LayoutSize);
    ui->BtnSGainUp->setMaximumHeight(LayoutSize);
    ui->BtnSResoDn->setMinimumHeight(LayoutSize);
    ui->BtnSResoDn->setMaximumHeight(LayoutSize);
    ui->BtnSResoUp->setMinimumHeight(LayoutSize);
    ui->BtnSResoUp->setMaximumHeight(LayoutSize);
    ui->BtnSWindDn->setMinimumHeight(LayoutSize);
    ui->BtnSWindDn->setMaximumHeight(LayoutSize);
    ui->BtnSWindUp->setMinimumHeight(LayoutSize);
    ui->BtnSWindUp->setMaximumHeight(LayoutSize);
    ui->BtnSZoomDn->setMinimumHeight(LayoutSize);
    ui->BtnSZoomDn->setMaximumHeight(LayoutSize);
    ui->BtnSZoomUp->setMinimumHeight(LayoutSize);
    ui->BtnSZoomUp->setMaximumHeight(LayoutSize);
    ui->BtnSOffsDn->setMinimumHeight(LayoutSize);
    ui->BtnSOffsDn->setMaximumHeight(LayoutSize);
    ui->BtnSOffsUp->setMinimumHeight(LayoutSize);
    ui->BtnSOffsUp->setMaximumHeight(LayoutSize);
    ui->BtnSStepDn->setMinimumHeight(LayoutSize);
    ui->BtnSStepDn->setMaximumHeight(LayoutSize);
    ui->BtnSStepUp->setMinimumHeight(LayoutSize);
    ui->BtnSStepUp->setMaximumHeight(LayoutSize);
    ui->BtnSBaseDn->setMinimumHeight(LayoutSize);
    ui->BtnSBaseDn->setMaximumHeight(LayoutSize);
    ui->BtnSBaseUp->setMinimumHeight(LayoutSize);
    ui->BtnSBaseUp->setMaximumHeight(LayoutSize);
    ui->BtnSMiMaDn->setMinimumHeight(LayoutSize);
    ui->BtnSMiMaDn->setMaximumHeight(LayoutSize);
    ui->BtnSMiMaUp->setMinimumHeight(LayoutSize);
    ui->BtnSMiMaUp->setMaximumHeight(LayoutSize);
    ui->BtnSLineDn->setMinimumHeight(LayoutSize);
    ui->BtnSLineDn->setMaximumHeight(LayoutSize);
    ui->BtnSLineUp->setMinimumHeight(LayoutSize);
    ui->BtnSLineUp->setMaximumHeight(LayoutSize);
    ui->BtnSMode__->setMinimumHeight(LayoutSize);
    ui->BtnSMode__->setMaximumHeight(LayoutSize);
    ui->BtnSPaus__->setMinimumHeight(LayoutSize);
    ui->BtnSPaus__->setMaximumHeight(LayoutSize);
    ui->BtnSFull__->setMinimumHeight(LayoutSize);
    ui->BtnSFull__->setMaximumHeight(LayoutSize);
    ui->BtnSClos__->setMinimumHeight(LayoutSize);
    ui->BtnSClos__->setMaximumHeight(LayoutSize);

    ui->BtnEGainDn->setMinimumWidth(LayoutSize);
    ui->BtnEGainDn->setMaximumWidth(LayoutSize);
    ui->BtnEGainUp->setMinimumWidth(LayoutSize);
    ui->BtnEGainUp->setMaximumWidth(LayoutSize);
    ui->BtnEResoDn->setMinimumWidth(LayoutSize);
    ui->BtnEResoDn->setMaximumWidth(LayoutSize);
    ui->BtnEResoUp->setMinimumWidth(LayoutSize);
    ui->BtnEResoUp->setMaximumWidth(LayoutSize);
    ui->BtnEWindDn->setMinimumWidth(LayoutSize);
    ui->BtnEWindDn->setMaximumWidth(LayoutSize);
    ui->BtnEWindUp->setMinimumWidth(LayoutSize);
    ui->BtnEWindUp->setMaximumWidth(LayoutSize);
    ui->BtnEZoomDn->setMinimumWidth(LayoutSize);
    ui->BtnEZoomDn->setMaximumWidth(LayoutSize);
    ui->BtnEZoomUp->setMinimumWidth(LayoutSize);
    ui->BtnEZoomUp->setMaximumWidth(LayoutSize);
    ui->BtnEOffsDn->setMinimumWidth(LayoutSize);
    ui->BtnEOffsDn->setMaximumWidth(LayoutSize);
    ui->BtnEOffsUp->setMinimumWidth(LayoutSize);
    ui->BtnEOffsUp->setMaximumWidth(LayoutSize);
    ui->BtnEStepDn->setMinimumWidth(LayoutSize);
    ui->BtnEStepDn->setMaximumWidth(LayoutSize);
    ui->BtnEStepUp->setMinimumWidth(LayoutSize);
    ui->BtnEStepUp->setMaximumWidth(LayoutSize);
    ui->BtnEBaseDn->setMinimumWidth(LayoutSize);
    ui->BtnEBaseDn->setMaximumWidth(LayoutSize);
    ui->BtnEBaseUp->setMinimumWidth(LayoutSize);
    ui->BtnEBaseUp->setMaximumWidth(LayoutSize);
    ui->BtnEMiMaDn->setMinimumWidth(LayoutSize);
    ui->BtnEMiMaDn->setMaximumWidth(LayoutSize);
    ui->BtnEMiMaUp->setMinimumWidth(LayoutSize);
    ui->BtnEMiMaUp->setMaximumWidth(LayoutSize);
    ui->BtnELineDn->setMinimumWidth(LayoutSize);
    ui->BtnELineDn->setMaximumWidth(LayoutSize);
    ui->BtnELineUp->setMinimumWidth(LayoutSize);
    ui->BtnELineUp->setMaximumWidth(LayoutSize);
    ui->BtnEMode__->setMinimumWidth(LayoutSize);
    ui->BtnEMode__->setMaximumWidth(LayoutSize);
    ui->BtnEPaus__->setMinimumWidth(LayoutSize);
    ui->BtnEPaus__->setMaximumWidth(LayoutSize);
    ui->BtnEFull__->setMinimumWidth(LayoutSize);
    ui->BtnEFull__->setMaximumWidth(LayoutSize);
    ui->BtnEClos__->setMinimumWidth(LayoutSize);
    ui->BtnEClos__->setMaximumWidth(LayoutSize);

    ui->BtnWGainDn->setMinimumWidth(LayoutSize);
    ui->BtnWGainDn->setMaximumWidth(LayoutSize);
    ui->BtnWGainUp->setMinimumWidth(LayoutSize);
    ui->BtnWGainUp->setMaximumWidth(LayoutSize);
    ui->BtnWResoDn->setMinimumWidth(LayoutSize);
    ui->BtnWResoDn->setMaximumWidth(LayoutSize);
    ui->BtnWResoUp->setMinimumWidth(LayoutSize);
    ui->BtnWResoUp->setMaximumWidth(LayoutSize);
    ui->BtnWWindDn->setMinimumWidth(LayoutSize);
    ui->BtnWWindDn->setMaximumWidth(LayoutSize);
    ui->BtnWWindUp->setMinimumWidth(LayoutSize);
    ui->BtnWWindUp->setMaximumWidth(LayoutSize);
    ui->BtnWZoomDn->setMinimumWidth(LayoutSize);
    ui->BtnWZoomDn->setMaximumWidth(LayoutSize);
    ui->BtnWZoomUp->setMinimumWidth(LayoutSize);
    ui->BtnWZoomUp->setMaximumWidth(LayoutSize);
    ui->BtnWOffsDn->setMinimumWidth(LayoutSize);
    ui->BtnWOffsDn->setMaximumWidth(LayoutSize);
    ui->BtnWOffsUp->setMinimumWidth(LayoutSize);
    ui->BtnWOffsUp->setMaximumWidth(LayoutSize);
    ui->BtnWStepDn->setMinimumWidth(LayoutSize);
    ui->BtnWStepDn->setMaximumWidth(LayoutSize);
    ui->BtnWStepUp->setMinimumWidth(LayoutSize);
    ui->BtnWStepUp->setMaximumWidth(LayoutSize);
    ui->BtnWBaseDn->setMinimumWidth(LayoutSize);
    ui->BtnWBaseDn->setMaximumWidth(LayoutSize);
    ui->BtnWBaseUp->setMinimumWidth(LayoutSize);
    ui->BtnWBaseUp->setMaximumWidth(LayoutSize);
    ui->BtnWMiMaDn->setMinimumWidth(LayoutSize);
    ui->BtnWMiMaDn->setMaximumWidth(LayoutSize);
    ui->BtnWMiMaUp->setMinimumWidth(LayoutSize);
    ui->BtnWMiMaUp->setMaximumWidth(LayoutSize);
    ui->BtnWLineDn->setMinimumWidth(LayoutSize);
    ui->BtnWLineDn->setMaximumWidth(LayoutSize);
    ui->BtnWLineUp->setMinimumWidth(LayoutSize);
    ui->BtnWLineUp->setMaximumWidth(LayoutSize);
    ui->BtnWMode__->setMinimumWidth(LayoutSize);
    ui->BtnWMode__->setMaximumWidth(LayoutSize);
    ui->BtnWPaus__->setMinimumWidth(LayoutSize);
    ui->BtnWPaus__->setMaximumWidth(LayoutSize);
    ui->BtnWFull__->setMinimumWidth(LayoutSize);
    ui->BtnWFull__->setMaximumWidth(LayoutSize);
    ui->BtnWClos__->setMinimumWidth(LayoutSize);
    ui->BtnWClos__->setMaximumWidth(LayoutSize);

    ui->BtnNGainDn->setVisible(false);
    ui->BtnNGainUp->setVisible(false);
    ui->BtnNResoDn->setVisible(false);
    ui->BtnNResoUp->setVisible(false);
    ui->BtnNWindDn->setVisible(false);
    ui->BtnNWindUp->setVisible(false);
    ui->BtnNZoomDn->setVisible(false);
    ui->BtnNZoomUp->setVisible(false);
    ui->BtnNOffsDn->setVisible(false);
    ui->BtnNOffsUp->setVisible(false);
    ui->BtnNStepDn->setVisible(false);
    ui->BtnNStepUp->setVisible(false);
    ui->BtnNBaseDn->setVisible(false);
    ui->BtnNBaseUp->setVisible(false);
    ui->BtnNMiMaDn->setVisible(false);
    ui->BtnNMiMaUp->setVisible(false);
    ui->BtnNLineDn->setVisible(false);
    ui->BtnNLineUp->setVisible(false);
    ui->BtnNMode__->setVisible(false);
    ui->BtnNPaus__->setVisible(false);
    ui->BtnNFull__->setVisible(false);
    ui->BtnNClos__->setVisible(false);

    ui->BtnSGainDn->setVisible(false);
    ui->BtnSGainUp->setVisible(false);
    ui->BtnSResoDn->setVisible(false);
    ui->BtnSResoUp->setVisible(false);
    ui->BtnSWindDn->setVisible(false);
    ui->BtnSWindUp->setVisible(false);
    ui->BtnSZoomDn->setVisible(false);
    ui->BtnSZoomUp->setVisible(false);
    ui->BtnSOffsDn->setVisible(false);
    ui->BtnSOffsUp->setVisible(false);
    ui->BtnSStepDn->setVisible(false);
    ui->BtnSStepUp->setVisible(false);
    ui->BtnSBaseDn->setVisible(false);
    ui->BtnSBaseUp->setVisible(false);
    ui->BtnSMiMaDn->setVisible(false);
    ui->BtnSMiMaUp->setVisible(false);
    ui->BtnSLineDn->setVisible(false);
    ui->BtnSLineUp->setVisible(false);
    ui->BtnSMode__->setVisible(false);
    ui->BtnSPaus__->setVisible(false);
    ui->BtnSFull__->setVisible(false);
    ui->BtnSClos__->setVisible(false);

    ui->BtnEGainDn->setVisible(false);
    ui->BtnEGainUp->setVisible(false);
    ui->BtnEResoDn->setVisible(false);
    ui->BtnEResoUp->setVisible(false);
    ui->BtnEWindDn->setVisible(false);
    ui->BtnEWindUp->setVisible(false);
    ui->BtnEZoomDn->setVisible(false);
    ui->BtnEZoomUp->setVisible(false);
    ui->BtnEOffsDn->setVisible(false);
    ui->BtnEOffsUp->setVisible(false);
    ui->BtnEStepDn->setVisible(false);
    ui->BtnEStepUp->setVisible(false);
    ui->BtnEBaseDn->setVisible(false);
    ui->BtnEBaseUp->setVisible(false);
    ui->BtnEMiMaDn->setVisible(false);
    ui->BtnEMiMaUp->setVisible(false);
    ui->BtnELineDn->setVisible(false);
    ui->BtnELineUp->setVisible(false);
    ui->BtnEMode__->setVisible(false);
    ui->BtnEPaus__->setVisible(false);
    ui->BtnEFull__->setVisible(false);
    ui->BtnEClos__->setVisible(false);

    ui->BtnWGainDn->setVisible(false);
    ui->BtnWGainUp->setVisible(false);
    ui->BtnWResoDn->setVisible(false);
    ui->BtnWResoUp->setVisible(false);
    ui->BtnWWindDn->setVisible(false);
    ui->BtnWWindUp->setVisible(false);
    ui->BtnWZoomDn->setVisible(false);
    ui->BtnWZoomUp->setVisible(false);
    ui->BtnWOffsDn->setVisible(false);
    ui->BtnWOffsUp->setVisible(false);
    ui->BtnWStepDn->setVisible(false);
    ui->BtnWStepUp->setVisible(false);
    ui->BtnWBaseDn->setVisible(false);
    ui->BtnWBaseUp->setVisible(false);
    ui->BtnWMiMaDn->setVisible(false);
    ui->BtnWMiMaUp->setVisible(false);
    ui->BtnWLineDn->setVisible(false);
    ui->BtnWLineUp->setVisible(false);
    ui->BtnWMode__->setVisible(false);
    ui->BtnWPaus__->setVisible(false);
    ui->BtnWFull__->setVisible(false);
    ui->BtnWClos__->setVisible(false);

    switch (LayoutOrientation)
    {
        case 1:
        {
            ui->BtnNGainDn->setVisible(true);
            ui->BtnNGainUp->setVisible(true);
            ui->BtnNResoDn->setVisible(true);
            ui->BtnNResoUp->setVisible(true);
            ui->BtnNWindDn->setVisible(true);
            ui->BtnNWindUp->setVisible(true);
            ui->BtnNZoomDn->setVisible(true);
            ui->BtnNZoomUp->setVisible(true);
            ui->BtnNOffsDn->setVisible(true);
            ui->BtnNOffsUp->setVisible(true);
            ui->BtnNStepDn->setVisible(true);
            ui->BtnNStepUp->setVisible(true);
            ui->BtnNBaseDn->setVisible(true);
            ui->BtnNBaseUp->setVisible(true);
            ui->BtnNMiMaDn->setVisible(true);
            ui->BtnNMiMaUp->setVisible(true);
            ui->BtnNLineDn->setVisible(true);
            ui->BtnNLineUp->setVisible(true);
            ui->BtnNMode__->setVisible(true);
            ui->BtnNPaus__->setVisible(true);
            ui->BtnNFull__->setVisible(true);
            ui->BtnNClos__->setVisible(true);
            break;
        }
        case 2:
        {
            ui->BtnSGainDn->setVisible(true);
            ui->BtnSGainUp->setVisible(true);
            ui->BtnSResoDn->setVisible(true);
            ui->BtnSResoUp->setVisible(true);
            ui->BtnSWindDn->setVisible(true);
            ui->BtnSWindUp->setVisible(true);
            ui->BtnSZoomDn->setVisible(true);
            ui->BtnSZoomUp->setVisible(true);
            ui->BtnSOffsDn->setVisible(true);
            ui->BtnSOffsUp->setVisible(true);
            ui->BtnSStepDn->setVisible(true);
            ui->BtnSStepUp->setVisible(true);
            ui->BtnSBaseDn->setVisible(true);
            ui->BtnSBaseUp->setVisible(true);
            ui->BtnSMiMaDn->setVisible(true);
            ui->BtnSMiMaUp->setVisible(true);
            ui->BtnSLineDn->setVisible(true);
            ui->BtnSLineUp->setVisible(true);
            ui->BtnSMode__->setVisible(true);
            ui->BtnSPaus__->setVisible(true);
            ui->BtnSFull__->setVisible(true);
            ui->BtnSClos__->setVisible(true);
            break;
        }
        case 3:
        {
            ui->BtnEGainDn->setVisible(true);
            ui->BtnEGainUp->setVisible(true);
            ui->BtnEResoDn->setVisible(true);
            ui->BtnEResoUp->setVisible(true);
            ui->BtnEWindDn->setVisible(true);
            ui->BtnEWindUp->setVisible(true);
            ui->BtnEZoomDn->setVisible(true);
            ui->BtnEZoomUp->setVisible(true);
            ui->BtnEOffsDn->setVisible(true);
            ui->BtnEOffsUp->setVisible(true);
            ui->BtnEStepDn->setVisible(true);
            ui->BtnEStepUp->setVisible(true);
            ui->BtnEBaseDn->setVisible(true);
            ui->BtnEBaseUp->setVisible(true);
            ui->BtnEMiMaDn->setVisible(true);
            ui->BtnEMiMaUp->setVisible(true);
            ui->BtnELineDn->setVisible(true);
            ui->BtnELineUp->setVisible(true);
            ui->BtnEMode__->setVisible(true);
            ui->BtnEPaus__->setVisible(true);
            ui->BtnEFull__->setVisible(true);
            ui->BtnEClos__->setVisible(true);
            break;
        }
        case 4:
        {
            ui->BtnWGainDn->setVisible(true);
            ui->BtnWGainUp->setVisible(true);
            ui->BtnWResoDn->setVisible(true);
            ui->BtnWResoUp->setVisible(true);
            ui->BtnWWindDn->setVisible(true);
            ui->BtnWWindUp->setVisible(true);
            ui->BtnWZoomDn->setVisible(true);
            ui->BtnWZoomUp->setVisible(true);
            ui->BtnWOffsDn->setVisible(true);
            ui->BtnWOffsUp->setVisible(true);
            ui->BtnWStepDn->setVisible(true);
            ui->BtnWStepUp->setVisible(true);
            ui->BtnWBaseDn->setVisible(true);
            ui->BtnWBaseUp->setVisible(true);
            ui->BtnWMiMaDn->setVisible(true);
            ui->BtnWMiMaUp->setVisible(true);
            ui->BtnWLineDn->setVisible(true);
            ui->BtnWLineUp->setVisible(true);
            ui->BtnWMode__->setVisible(true);
            ui->BtnWPaus__->setVisible(true);
            ui->BtnWFull__->setVisible(true);
            ui->BtnWClos__->setVisible(true);
            break;
        }
    }

    SetFocus();
}

void SpectrumFull::SetMouse()
{
    QCursor X = Qt::ArrowCursor;
    if (Settings_->SpectrogramMouseGraph)
    {
        X = Qt::BlankCursor;
    }
    ui->SpectrumScreen->setCursor(X);

    X = Qt::ArrowCursor;
    if (Settings_->SpectrogramMouseButtons)
    {
        X = Qt::BlankCursor;
    }

    ui->BtnNGainDn->setCursor(X);
    ui->BtnSGainDn->setCursor(X);
    ui->BtnEGainDn->setCursor(X);
    ui->BtnWGainDn->setCursor(X);

    ui->BtnNGainUp->setCursor(X);
    ui->BtnSGainUp->setCursor(X);
    ui->BtnEGainUp->setCursor(X);
    ui->BtnWGainUp->setCursor(X);

    ui->BtnNResoDn->setCursor(X);
    ui->BtnSResoDn->setCursor(X);
    ui->BtnEResoDn->setCursor(X);
    ui->BtnWResoDn->setCursor(X);

    ui->BtnNResoUp->setCursor(X);
    ui->BtnSResoUp->setCursor(X);
    ui->BtnEResoUp->setCursor(X);
    ui->BtnWResoUp->setCursor(X);

    ui->BtnNWindDn->setCursor(X);
    ui->BtnSWindDn->setCursor(X);
    ui->BtnEWindDn->setCursor(X);
    ui->BtnWWindDn->setCursor(X);

    ui->BtnNWindUp->setCursor(X);
    ui->BtnSWindUp->setCursor(X);
    ui->BtnEWindUp->setCursor(X);
    ui->BtnWWindUp->setCursor(X);

    ui->BtnNZoomDn->setCursor(X);
    ui->BtnSZoomDn->setCursor(X);
    ui->BtnEZoomDn->setCursor(X);
    ui->BtnWZoomDn->setCursor(X);

    ui->BtnNZoomUp->setCursor(X);
    ui->BtnSZoomUp->setCursor(X);
    ui->BtnEZoomUp->setCursor(X);
    ui->BtnWZoomUp->setCursor(X);

    ui->BtnNOffsDn->setCursor(X);
    ui->BtnSOffsDn->setCursor(X);
    ui->BtnEOffsDn->setCursor(X);
    ui->BtnWOffsDn->setCursor(X);

    ui->BtnNOffsUp->setCursor(X);
    ui->BtnSOffsUp->setCursor(X);
    ui->BtnEOffsUp->setCursor(X);
    ui->BtnWOffsUp->setCursor(X);

    ui->BtnNStepDn->setCursor(X);
    ui->BtnSStepDn->setCursor(X);
    ui->BtnEStepDn->setCursor(X);
    ui->BtnWStepDn->setCursor(X);

    ui->BtnNStepUp->setCursor(X);
    ui->BtnSStepUp->setCursor(X);
    ui->BtnEStepUp->setCursor(X);
    ui->BtnWStepUp->setCursor(X);

    ui->BtnNBaseDn->setCursor(X);
    ui->BtnSBaseDn->setCursor(X);
    ui->BtnEBaseDn->setCursor(X);
    ui->BtnWBaseDn->setCursor(X);

    ui->BtnNBaseUp->setCursor(X);
    ui->BtnSBaseUp->setCursor(X);
    ui->BtnEBaseUp->setCursor(X);
    ui->BtnWBaseUp->setCursor(X);

    ui->BtnNLineDn->setCursor(X);
    ui->BtnSLineDn->setCursor(X);
    ui->BtnELineDn->setCursor(X);
    ui->BtnWLineDn->setCursor(X);

    ui->BtnNLineUp->setCursor(X);
    ui->BtnSLineUp->setCursor(X);
    ui->BtnELineUp->setCursor(X);
    ui->BtnWLineUp->setCursor(X);

    ui->BtnNMiMaDn->setCursor(X);
    ui->BtnSMiMaDn->setCursor(X);
    ui->BtnEMiMaDn->setCursor(X);
    ui->BtnWMiMaDn->setCursor(X);

    ui->BtnNMiMaUp->setCursor(X);
    ui->BtnSMiMaUp->setCursor(X);
    ui->BtnEMiMaUp->setCursor(X);
    ui->BtnWMiMaUp->setCursor(X);

    ui->BtnNMode__->setCursor(X);
    ui->BtnSMode__->setCursor(X);
    ui->BtnEMode__->setCursor(X);
    ui->BtnWMode__->setCursor(X);

    ui->BtnNPaus__->setCursor(X);
    ui->BtnSPaus__->setCursor(X);
    ui->BtnEPaus__->setCursor(X);
    ui->BtnWPaus__->setCursor(X);

    ui->BtnNFull__->setCursor(X);
    ui->BtnSFull__->setCursor(X);
    ui->BtnEFull__->setCursor(X);
    ui->BtnWFull__->setCursor(X);

    ui->BtnNClos__->setCursor(X);
    ui->BtnSClos__->setCursor(X);
    ui->BtnEClos__->setCursor(X);
    ui->BtnWClos__->setCursor(X);
}

void SpectrumFull::on_BtnNGainDn_clicked() { on_Btn_GainDn_clicked(); }
void SpectrumFull::on_BtnNGainUp_clicked() { on_Btn_GainUp_clicked(); }
void SpectrumFull::on_BtnNResoDn_clicked() { on_Btn_ResoDn_clicked(); }
void SpectrumFull::on_BtnNResoUp_clicked() { on_Btn_ResoUp_clicked(); }
void SpectrumFull::on_BtnNWindDn_clicked() { on_Btn_WindDn_clicked(); }
void SpectrumFull::on_BtnNWindUp_clicked() { on_Btn_WindUp_clicked(); }
void SpectrumFull::on_BtnNZoomDn_clicked() { on_Btn_ZoomDn_clicked(); }
void SpectrumFull::on_BtnNZoomUp_clicked() { on_Btn_ZoomUp_clicked(); }
void SpectrumFull::on_BtnNOffsDn_clicked() { on_Btn_OffsDn_clicked(); }
void SpectrumFull::on_BtnNOffsUp_clicked() { on_Btn_OffsUp_clicked(); }
void SpectrumFull::on_BtnNStepDn_clicked() { on_Btn_StepDn_clicked(); }
void SpectrumFull::on_BtnNStepUp_clicked() { on_Btn_StepUp_clicked(); }
void SpectrumFull::on_BtnNBaseDn_clicked() { on_Btn_BaseDn_clicked(); }
void SpectrumFull::on_BtnNBaseUp_clicked() { on_Btn_BaseUp_clicked(); }
void SpectrumFull::on_BtnNMiMaDn_clicked() { on_Btn_MiMaDn_clicked(); }
void SpectrumFull::on_BtnNMiMaUp_clicked() { on_Btn_MiMaUp_clicked(); }
void SpectrumFull::on_BtnNLineDn_clicked() { on_Btn_LineDn_clicked(); }
void SpectrumFull::on_BtnNLineUp_clicked() { on_Btn_LineUp_clicked(); }
void SpectrumFull::on_BtnNMode___clicked() { on_Btn_Mode___clicked(); }
void SpectrumFull::on_BtnNPaus___clicked() { on_Btn_Paus___clicked(); }
void SpectrumFull::on_BtnNFull___clicked() { on_Btn_Full___clicked(); }
void SpectrumFull::on_BtnNClos___clicked() { on_Btn_Clos___clicked(); }

void SpectrumFull::on_BtnSGainDn_clicked() { on_Btn_GainDn_clicked(); }
void SpectrumFull::on_BtnSGainUp_clicked() { on_Btn_GainUp_clicked(); }
void SpectrumFull::on_BtnSResoDn_clicked() { on_Btn_ResoDn_clicked(); }
void SpectrumFull::on_BtnSResoUp_clicked() { on_Btn_ResoUp_clicked(); }
void SpectrumFull::on_BtnSWindDn_clicked() { on_Btn_WindDn_clicked(); }
void SpectrumFull::on_BtnSWindUp_clicked() { on_Btn_WindUp_clicked(); }
void SpectrumFull::on_BtnSZoomDn_clicked() { on_Btn_ZoomDn_clicked(); }
void SpectrumFull::on_BtnSZoomUp_clicked() { on_Btn_ZoomUp_clicked(); }
void SpectrumFull::on_BtnSOffsDn_clicked() { on_Btn_OffsDn_clicked(); }
void SpectrumFull::on_BtnSOffsUp_clicked() { on_Btn_OffsUp_clicked(); }
void SpectrumFull::on_BtnSStepDn_clicked() { on_Btn_StepDn_clicked(); }
void SpectrumFull::on_BtnSStepUp_clicked() { on_Btn_StepUp_clicked(); }
void SpectrumFull::on_BtnSBaseDn_clicked() { on_Btn_BaseDn_clicked(); }
void SpectrumFull::on_BtnSBaseUp_clicked() { on_Btn_BaseUp_clicked(); }
void SpectrumFull::on_BtnSMiMaDn_clicked() { on_Btn_MiMaDn_clicked(); }
void SpectrumFull::on_BtnSMiMaUp_clicked() { on_Btn_MiMaUp_clicked(); }
void SpectrumFull::on_BtnSLineDn_clicked() { on_Btn_LineDn_clicked(); }
void SpectrumFull::on_BtnSLineUp_clicked() { on_Btn_LineUp_clicked(); }
void SpectrumFull::on_BtnSMode___clicked() { on_Btn_Mode___clicked(); }
void SpectrumFull::on_BtnSPaus___clicked() { on_Btn_Paus___clicked(); }
void SpectrumFull::on_BtnSFull___clicked() { on_Btn_Full___clicked(); }
void SpectrumFull::on_BtnSClos___clicked() { on_Btn_Clos___clicked(); }

void SpectrumFull::on_BtnEGainDn_clicked() { on_Btn_GainDn_clicked(); }
void SpectrumFull::on_BtnEGainUp_clicked() { on_Btn_GainUp_clicked(); }
void SpectrumFull::on_BtnEResoDn_clicked() { on_Btn_ResoDn_clicked(); }
void SpectrumFull::on_BtnEResoUp_clicked() { on_Btn_ResoUp_clicked(); }
void SpectrumFull::on_BtnEWindDn_clicked() { on_Btn_WindDn_clicked(); }
void SpectrumFull::on_BtnEWindUp_clicked() { on_Btn_WindUp_clicked(); }
void SpectrumFull::on_BtnEZoomDn_clicked() { on_Btn_ZoomDn_clicked(); }
void SpectrumFull::on_BtnEZoomUp_clicked() { on_Btn_ZoomUp_clicked(); }
void SpectrumFull::on_BtnEOffsDn_clicked() { on_Btn_OffsDn_clicked(); }
void SpectrumFull::on_BtnEOffsUp_clicked() { on_Btn_OffsUp_clicked(); }
void SpectrumFull::on_BtnEStepDn_clicked() { on_Btn_StepDn_clicked(); }
void SpectrumFull::on_BtnEStepUp_clicked() { on_Btn_StepUp_clicked(); }
void SpectrumFull::on_BtnEBaseDn_clicked() { on_Btn_BaseDn_clicked(); }
void SpectrumFull::on_BtnEBaseUp_clicked() { on_Btn_BaseUp_clicked(); }
void SpectrumFull::on_BtnEMiMaDn_clicked() { on_Btn_MiMaDn_clicked(); }
void SpectrumFull::on_BtnEMiMaUp_clicked() { on_Btn_MiMaUp_clicked(); }
void SpectrumFull::on_BtnELineDn_clicked() { on_Btn_LineDn_clicked(); }
void SpectrumFull::on_BtnELineUp_clicked() { on_Btn_LineUp_clicked(); }
void SpectrumFull::on_BtnEMode___clicked() { on_Btn_Mode___clicked(); }
void SpectrumFull::on_BtnEPaus___clicked() { on_Btn_Paus___clicked(); }
void SpectrumFull::on_BtnEFull___clicked() { on_Btn_Full___clicked(); }
void SpectrumFull::on_BtnEClos___clicked() { on_Btn_Clos___clicked(); }

void SpectrumFull::on_BtnWGainDn_clicked() { on_Btn_GainDn_clicked(); }
void SpectrumFull::on_BtnWGainUp_clicked() { on_Btn_GainUp_clicked(); }
void SpectrumFull::on_BtnWResoDn_clicked() { on_Btn_ResoDn_clicked(); }
void SpectrumFull::on_BtnWResoUp_clicked() { on_Btn_ResoUp_clicked(); }
void SpectrumFull::on_BtnWWindDn_clicked() { on_Btn_WindDn_clicked(); }
void SpectrumFull::on_BtnWWindUp_clicked() { on_Btn_WindUp_clicked(); }
void SpectrumFull::on_BtnWZoomDn_clicked() { on_Btn_ZoomDn_clicked(); }
void SpectrumFull::on_BtnWZoomUp_clicked() { on_Btn_ZoomUp_clicked(); }
void SpectrumFull::on_BtnWOffsDn_clicked() { on_Btn_OffsDn_clicked(); }
void SpectrumFull::on_BtnWOffsUp_clicked() { on_Btn_OffsUp_clicked(); }
void SpectrumFull::on_BtnWStepDn_clicked() { on_Btn_StepDn_clicked(); }
void SpectrumFull::on_BtnWStepUp_clicked() { on_Btn_StepUp_clicked(); }
void SpectrumFull::on_BtnWBaseDn_clicked() { on_Btn_BaseDn_clicked(); }
void SpectrumFull::on_BtnWBaseUp_clicked() { on_Btn_BaseUp_clicked(); }
void SpectrumFull::on_BtnWMiMaDn_clicked() { on_Btn_MiMaDn_clicked(); }
void SpectrumFull::on_BtnWMiMaUp_clicked() { on_Btn_MiMaUp_clicked(); }
void SpectrumFull::on_BtnWLineDn_clicked() { on_Btn_LineDn_clicked(); }
void SpectrumFull::on_BtnWLineUp_clicked() { on_Btn_LineUp_clicked(); }
void SpectrumFull::on_BtnWMode___clicked() { on_Btn_Mode___clicked(); }
void SpectrumFull::on_BtnWPaus___clicked() { on_Btn_Paus___clicked(); }
void SpectrumFull::on_BtnWFull___clicked() { on_Btn_Full___clicked(); }
void SpectrumFull::on_BtnWClos___clicked() { on_Btn_Clos___clicked(); }

void SpectrumFull::on_Btn_GainDn_clicked()
{
    KeyRequests.push(12);
    SetFocus();
}

void SpectrumFull::on_Btn_GainUp_clicked()
{
    KeyRequests.push(11);
    SetFocus();
}

void SpectrumFull::on_Btn_ResoDn_clicked()
{
    KeyRequests.push(22);
    SetFocus();
}

void SpectrumFull::on_Btn_ResoUp_clicked()
{
    KeyRequests.push(21);
    SetFocus();
}

void SpectrumFull::on_Btn_WindDn_clicked()
{
    KeyRequests.push(24);
    SetFocus();
}

void SpectrumFull::on_Btn_WindUp_clicked()
{
    KeyRequests.push(23);
    SetFocus();
}

void SpectrumFull::on_Btn_ZoomDn_clicked()
{
    KeyRequests.push(32);
    SetFocus();
}

void SpectrumFull::on_Btn_ZoomUp_clicked()
{
    KeyRequests.push(31);
    SetFocus();
}

void SpectrumFull::on_Btn_OffsDn_clicked()
{
    KeyRequests.push(34);
    SetFocus();
}

void SpectrumFull::on_Btn_OffsUp_clicked()
{
    KeyRequests.push(33);
    SetFocus();
}

void SpectrumFull::on_Btn_StepDn_clicked()
{
    KeyRequests.push(42);
    SetFocus();
}

void SpectrumFull::on_Btn_StepUp_clicked()
{
    KeyRequests.push(41);
    SetFocus();
}

void SpectrumFull::on_Btn_BaseDn_clicked()
{
    KeyRequests.push(44);
    SetFocus();
}

void SpectrumFull::on_Btn_BaseUp_clicked()
{
    KeyRequests.push(43);
    SetFocus();
}

void SpectrumFull::on_Btn_MiMaDn_clicked()
{
    KeyRequests.push(46);
    SetFocus();
}

void SpectrumFull::on_Btn_MiMaUp_clicked()
{
    KeyRequests.push(45);
    SetFocus();
}

void SpectrumFull::on_Btn_LineDn_clicked()
{
    KeyRequests.push(52);
    SetFocus();
}

void SpectrumFull::on_Btn_LineUp_clicked()
{
    KeyRequests.push(51);
    SetFocus();
}

void SpectrumFull::on_Btn_Mode___clicked()
{
    KeyRequests.push(50);
    SetFocus();
}

void SpectrumFull::on_Btn_Paus___clicked()
{
    KeyRequests.push(53);
    SetFocus();
}

void SpectrumFull::on_Btn_Full___clicked()
{
    hide();
    if (isFullScreen())
    {
        showNormal();
    }
    else
    {
        showFullScreen();
    }
    SetFocus();
}

void SpectrumFull::on_Btn_Clos___clicked()
{
    this->hide();
    SetFocus();
}

void SpectrumFull::SetFocus()
{
    ui->SpectrumScreen->setFocus();
}

void SpectrumFull::SetLabels(QString _G, QString _R, QString _W, QString _Z, QString _O, QString _S, QString _B, QString _M, QString _L)
{
    QString EOL = "\n";

    ui->BtnNGainDn->setText("G-" + EOL + _G);
    ui->BtnNGainUp->setText("G+" + EOL + _G);
    ui->BtnNResoDn->setText("R-" + EOL + _R);
    ui->BtnNResoUp->setText("R+" + EOL + _R);
    ui->BtnNWindDn->setText("W-" + EOL + _W);
    ui->BtnNWindUp->setText("W+" + EOL + _W);
    ui->BtnNZoomDn->setText("Z-" + EOL + _Z);
    ui->BtnNZoomUp->setText("Z+" + EOL + _Z);
    ui->BtnNOffsDn->setText("O-" + EOL + _O);
    ui->BtnNOffsUp->setText("O+" + EOL + _O);
    ui->BtnNStepDn->setText("S-" + EOL + _S);
    ui->BtnNStepUp->setText("S+" + EOL + _S);
    ui->BtnNBaseDn->setText("B-" + EOL + _B);
    ui->BtnNBaseUp->setText("B+" + EOL + _B);
    ui->BtnNMiMaDn->setText("M-" + EOL + _M);
    ui->BtnNMiMaUp->setText("M+" + EOL + _M);
    ui->BtnNLineDn->setText("L-" + EOL + _L);
    ui->BtnNLineUp->setText("L+" + EOL + _L);

    ui->BtnSGainDn->setText("G-" + EOL + _G);
    ui->BtnSGainUp->setText("G+" + EOL + _G);
    ui->BtnSResoDn->setText("R-" + EOL + _R);
    ui->BtnSResoUp->setText("R+" + EOL + _R);
    ui->BtnSWindDn->setText("W-" + EOL + _W);
    ui->BtnSWindUp->setText("W+" + EOL + _W);
    ui->BtnSZoomDn->setText("Z-" + EOL + _Z);
    ui->BtnSZoomUp->setText("Z+" + EOL + _Z);
    ui->BtnSOffsDn->setText("O-" + EOL + _O);
    ui->BtnSOffsUp->setText("O+" + EOL + _O);
    ui->BtnSStepDn->setText("S-" + EOL + _S);
    ui->BtnSStepUp->setText("S+" + EOL + _S);
    ui->BtnSBaseDn->setText("B-" + EOL + _B);
    ui->BtnSBaseUp->setText("B+" + EOL + _B);
    ui->BtnSMiMaDn->setText("M-" + EOL + _M);
    ui->BtnSMiMaUp->setText("M+" + EOL + _M);
    ui->BtnSLineDn->setText("L-" + EOL + _L);
    ui->BtnSLineUp->setText("L+" + EOL + _L);

    ui->BtnEGainDn->setText("G-" + EOL + _G);
    ui->BtnEGainUp->setText("G+" + EOL + _G);
    ui->BtnEResoDn->setText("R-" + EOL + _R);
    ui->BtnEResoUp->setText("R+" + EOL + _R);
    ui->BtnEWindDn->setText("W-" + EOL + _W);
    ui->BtnEWindUp->setText("W+" + EOL + _W);
    ui->BtnEZoomDn->setText("Z-" + EOL + _Z);
    ui->BtnEZoomUp->setText("Z+" + EOL + _Z);
    ui->BtnEOffsDn->setText("O-" + EOL + _O);
    ui->BtnEOffsUp->setText("O+" + EOL + _O);
    ui->BtnEStepDn->setText("S-" + EOL + _S);
    ui->BtnEStepUp->setText("S+" + EOL + _S);
    ui->BtnEBaseDn->setText("B-" + EOL + _B);
    ui->BtnEBaseUp->setText("B+" + EOL + _B);
    ui->BtnEMiMaDn->setText("M-" + EOL + _M);
    ui->BtnEMiMaUp->setText("M+" + EOL + _M);
    ui->BtnELineDn->setText("L-" + EOL + _L);
    ui->BtnELineUp->setText("L+" + EOL + _L);

    ui->BtnWGainDn->setText("G-" + EOL + _G);
    ui->BtnWGainUp->setText("G+" + EOL + _G);
    ui->BtnWResoDn->setText("R-" + EOL + _R);
    ui->BtnWResoUp->setText("R+" + EOL + _R);
    ui->BtnWWindDn->setText("W-" + EOL + _W);
    ui->BtnWWindUp->setText("W+" + EOL + _W);
    ui->BtnWZoomDn->setText("Z-" + EOL + _Z);
    ui->BtnWZoomUp->setText("Z+" + EOL + _Z);
    ui->BtnWOffsDn->setText("O-" + EOL + _O);
    ui->BtnWOffsUp->setText("O+" + EOL + _O);
    ui->BtnWStepDn->setText("S-" + EOL + _S);
    ui->BtnWStepUp->setText("S+" + EOL + _S);
    ui->BtnWBaseDn->setText("B-" + EOL + _B);
    ui->BtnWBaseUp->setText("B+" + EOL + _B);
    ui->BtnWMiMaDn->setText("M-" + EOL + _M);
    ui->BtnWMiMaUp->setText("M+" + EOL + _M);
    ui->BtnWLineDn->setText("L-" + EOL + _L);
    ui->BtnWLineUp->setText("L+" + EOL + _L);
}
