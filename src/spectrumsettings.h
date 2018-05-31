#ifndef SPECTRUMSETTINGS_H
#define SPECTRUMSETTINGS_H

#include <QDialog>
#include "eden.h"
#include "settings.h"
#include <QColorDialog>

namespace Ui {
class SpectrumSettings;
}

class SpectrumSettings : public QDialog
{
    Q_OBJECT

public:
    Settings * Settings_;
    explicit SpectrumSettings(QWidget *parent = 0);
    ~SpectrumSettings();
    void Init();

private slots:
    void on_SpecFullStripT_textEdited(const QString &arg1);

    void on_SpecFullStripColor_clicked();

    void on_SpecFullScrollT_textEdited(const QString &arg1);

    void on_SpecFullLayoutS_currentIndexChanged(int index);

    void on_SpecFullLayoutT_textEdited(const QString &arg1);

    void on_SpecFullMarkersC_toggled(bool checked);

    void on_SpecFullMarkersText_textChanged();

    void on_SpecMouseGraph_toggled(bool checked);

    void on_SpecMouseButtons_toggled(bool checked);

    void on_SpecDecimationT_textEdited(const QString &arg1);

    void on_SpecDecimationC_toggled(bool checked);

    void on_SpecOverThrT_textEdited(const QString &arg1);

    void on_SpecOverThrColor_clicked();

    void on_SpecFullHalfColor_clicked();

    void on_SpecFullHalfT_textEdited(const QString &arg1);

    void on_SpecDispRW_currentIndexChanged(int index);

    void on_SpecDispGW_currentIndexChanged(int index);

    void on_SpecDispBW_currentIndexChanged(int index);

    void on_SpecFullGammaTW_textEdited(const QString &arg1);

    void on_SpecFullPaletteCW_currentIndexChanged(int index);

    void on_SpecWindowS_currentIndexChanged(int index);

    void on_SpecNegativeW_toggled(bool checked);

private:
    bool EventEnabled = false;
    Ui::SpectrumSettings *ui;
};

#endif // SPECTRUMSETTINGS_H
