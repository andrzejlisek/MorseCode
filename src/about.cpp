#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::on_AboutBtn_clicked()
{
    close();
}
