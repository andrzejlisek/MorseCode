#include "inputtext.h"
#include "ui_inputtext.h"

InputText::InputText(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputText)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMaximizeButtonHint;
    //flags |= Qt::WindowContextHelpButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
    ui->setupUi(this);
    connect(ui->InputTextX, SIGNAL(KeyPress(QKeyEvent*)), this, SLOT(KeyPress(QKeyEvent*)));
    connect(ui->InputTextX, SIGNAL(KeyRelease(QKeyEvent*)), this, SLOT(KeyRelease(QKeyEvent*)));
}

InputText::~InputText()
{
    delete ui;
}

void InputText::on_SendB_clicked()
{
    if (ui->InputTextX->toPlainText() != "")
    {
        SendText();
    }
    else
    {
        int WPM = Eden::ToInt(ui->WPM->text());
        MorseEncoderCore_->CalcFromWPM(WPM);
        if ((MorseEncoderCore_->CalcSignalDITlen > 0) && (MorseEncoderCore_->CalcSignalDAHlen))
        {
            MorseDecoderCore_->CalcFromLength(MorseEncoderCore_->CalcSignalDITlen, MorseEncoderCore_->CalcSignalDAHlen);
        }
        ui->InputTextX->setFocus();
    }
}

void InputText::SendText()
{
    MorseEncoderCore_->CalcPeriod(-1, -1);
    Settings_->MorseWPM = Eden::ToInt(ui->WPM->text());
    MorseEncoderCore_->Send(ui->InputTextX->toPlainText());
    ui->WPM->setText(Eden::ToQStr(Settings_->MorseWPM));
    ui->InputTextX->clear();
    ui->InputTextX->setFocus();
}

void InputText::Init()
{
    ui->WPM->setText(Eden::ToQStr(Settings_->MorseWPM));
}

void InputText::KeyPress(QKeyEvent * event)
{
    if (SendMode == 1)
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        {
            SendText();
        }
    }

    if (SendMode == 2)
    {
        if (event->key() < 16777215)
        {
            if ((event->key() == 91) || (event->key() == 123))
            {
                InsideSpecial = true;
            }
            if ((event->key() == 93) || (event->key() == 125))
            {
                InsideSpecial = false;
            }
            if (!InsideSpecial)
            {
                SendText();
            }
        }
    }
}

void InputText::KeyRelease(QKeyEvent * event)
{
    event++;
    event--;
}

void InputText::on_SendMode_currentIndexChanged(int index)
{
    SendMode = index;
}
