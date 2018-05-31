#ifndef INPUTTEXT_H
#define INPUTTEXT_H

#include <QDialog>
#include <morseencodercore.h>
#include <morsedecodercore.h>
#include "settings.h"
#include <QKeyEvent>

namespace Ui {
class InputText;
}

class InputText : public QDialog
{
    Q_OBJECT

public:
    explicit InputText(QWidget *parent = 0);
    ~InputText();
    MorseEncoderCore * MorseEncoderCore_;
    MorseDecoderCore * MorseDecoderCore_;
    void Init();
    Settings * Settings_;

private slots:
    void on_SendB_clicked();
    void KeyPress(QKeyEvent * event);
    void KeyRelease(QKeyEvent * event);




    void on_SendMode_currentIndexChanged(int index);

private:
    Ui::InputText *ui;
    int SendMode = 0;
    void SendText();
    bool InsideSpecial = false;
};

#endif // INPUTTEXT_H
