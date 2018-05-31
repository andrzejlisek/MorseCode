#ifndef SPECTRUMFULL_H
#define SPECTRUMFULL_H

#include <QMainWindow>
#include <QPixmap>
#include <queue>
#include "settings.h"

namespace Ui {
class SpectrumFull;
}

class SpectrumFull : public QMainWindow
{
    Q_OBJECT

public:
    Settings * Settings_;
    explicit SpectrumFull(QWidget *parent = 0);
    ~SpectrumFull();
    void DrawSpectrum(QImage * Pic);
    queue<int> KeyRequests;
    int PicW();
    int PicH();
    void ApplySettings(int LayoutSize, int LayoutOrientation);
    void SetMouse();
    void SetLabels(QString _G, QString _R, QString _W, QString _Z, QString _O, QString _S, QString _B, QString _M, QString _L);

private slots:
    void KeyPress(QKeyEvent * event);
    void KeyRelease(QKeyEvent * event);
    void on_BtnNGainDn_clicked();
    void on_BtnNGainUp_clicked();
    void on_BtnNResoDn_clicked();
    void on_BtnNResoUp_clicked();
    void on_BtnNWindDn_clicked();
    void on_BtnNWindUp_clicked();
    void on_BtnNZoomDn_clicked();
    void on_BtnNZoomUp_clicked();
    void on_BtnNOffsDn_clicked();
    void on_BtnNOffsUp_clicked();
    void on_BtnNStepDn_clicked();
    void on_BtnNStepUp_clicked();
    void on_BtnNBaseDn_clicked();
    void on_BtnNBaseUp_clicked();
    void on_BtnNMiMaDn_clicked();
    void on_BtnNMiMaUp_clicked();
    void on_BtnNLineDn_clicked();
    void on_BtnNLineUp_clicked();
    void on_BtnNMode___clicked();
    void on_BtnNPaus___clicked();
    void on_BtnNFull___clicked();
    void on_BtnNClos___clicked();
    void on_BtnSGainDn_clicked();
    void on_BtnSGainUp_clicked();
    void on_BtnSResoDn_clicked();
    void on_BtnSResoUp_clicked();
    void on_BtnSWindDn_clicked();
    void on_BtnSWindUp_clicked();
    void on_BtnSZoomDn_clicked();
    void on_BtnSZoomUp_clicked();
    void on_BtnSOffsDn_clicked();
    void on_BtnSOffsUp_clicked();
    void on_BtnSStepDn_clicked();
    void on_BtnSStepUp_clicked();
    void on_BtnSBaseDn_clicked();
    void on_BtnSBaseUp_clicked();
    void on_BtnSMiMaDn_clicked();
    void on_BtnSMiMaUp_clicked();
    void on_BtnSLineDn_clicked();
    void on_BtnSLineUp_clicked();
    void on_BtnSMode___clicked();
    void on_BtnSPaus___clicked();
    void on_BtnSFull___clicked();
    void on_BtnSClos___clicked();
    void on_BtnEGainDn_clicked();
    void on_BtnEGainUp_clicked();
    void on_BtnEResoDn_clicked();
    void on_BtnEResoUp_clicked();
    void on_BtnEWindDn_clicked();
    void on_BtnEWindUp_clicked();
    void on_BtnEZoomDn_clicked();
    void on_BtnEZoomUp_clicked();
    void on_BtnEOffsDn_clicked();
    void on_BtnEOffsUp_clicked();
    void on_BtnEStepDn_clicked();
    void on_BtnEStepUp_clicked();
    void on_BtnEBaseDn_clicked();
    void on_BtnEBaseUp_clicked();
    void on_BtnEMiMaUp_clicked();
    void on_BtnEMiMaDn_clicked();
    void on_BtnELineDn_clicked();
    void on_BtnELineUp_clicked();
    void on_BtnEMode___clicked();
    void on_BtnEPaus___clicked();
    void on_BtnEFull___clicked();
    void on_BtnEClos___clicked();
    void on_BtnWGainDn_clicked();
    void on_BtnWGainUp_clicked();
    void on_BtnWResoDn_clicked();
    void on_BtnWResoUp_clicked();
    void on_BtnWWindDn_clicked();
    void on_BtnWWindUp_clicked();
    void on_BtnWZoomDn_clicked();
    void on_BtnWZoomUp_clicked();
    void on_BtnWOffsDn_clicked();
    void on_BtnWOffsUp_clicked();
    void on_BtnWStepDn_clicked();
    void on_BtnWStepUp_clicked();
    void on_BtnWBaseDn_clicked();
    void on_BtnWBaseUp_clicked();
    void on_BtnWMiMaUp_clicked();
    void on_BtnWMiMaDn_clicked();
    void on_BtnWLineDn_clicked();
    void on_BtnWLineUp_clicked();
    void on_BtnWMode___clicked();
    void on_BtnWPaus___clicked();
    void on_BtnWFull___clicked();
    void on_BtnWClos___clicked();

private:
    Ui::SpectrumFull *ui;
    void on_Btn_GainDn_clicked();
    void on_Btn_GainUp_clicked();
    void on_Btn_ResoDn_clicked();
    void on_Btn_ResoUp_clicked();
    void on_Btn_WindDn_clicked();
    void on_Btn_WindUp_clicked();
    void on_Btn_ZoomDn_clicked();
    void on_Btn_ZoomUp_clicked();
    void on_Btn_OffsDn_clicked();
    void on_Btn_OffsUp_clicked();
    void on_Btn_StepDn_clicked();
    void on_Btn_StepUp_clicked();
    void on_Btn_BaseDn_clicked();
    void on_Btn_BaseUp_clicked();
    void on_Btn_MiMaUp_clicked();
    void on_Btn_MiMaDn_clicked();
    void on_Btn_LineDn_clicked();
    void on_Btn_LineUp_clicked();
    void on_Btn_Mode___clicked();
    void on_Btn_Paus___clicked();
    void on_Btn_Full___clicked();
    void on_Btn_Clos___clicked();
    void SetFocus();
};

#endif // SPECTRUMFULL_H
