#include "printtext.h"
#include "ui_printtext.h"

PrintText::PrintText(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintText)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMaximizeButtonHint;
    //flags |= Qt::WindowContextHelpButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
    ui->setupUi(this);
}

PrintText::~PrintText()
{
    delete ui;
}

void PrintText::on_ClearB_clicked()
{
    ui->PrintTextX->clear();
}

void PrintText::Print(QString S)
{
    if (S.length() > 0)
    {
        ui->PrintTextX->moveCursor(QTextCursor::End);
        ui->PrintTextX->insertPlainText(S);
        ui->PrintTextX->moveCursor(QTextCursor::End);
    }
}

void PrintText::on_NewLineB_clicked()
{
    ui->PrintTextX->moveCursor(QTextCursor::End);
    ui->PrintTextX->insertPlainText("\r\n");
    ui->PrintTextX->moveCursor(QTextCursor::End);
}
