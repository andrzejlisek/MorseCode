#ifndef PRINTTEXT_H
#define PRINTTEXT_H

#include <QDialog>
#include <string>

using namespace std;

namespace Ui {
class PrintText;
}

class PrintText : public QDialog
{
    Q_OBJECT

public:
    explicit PrintText(QWidget *parent = 0);
    ~PrintText();
    void Print(QString S);

private slots:
    void on_ClearB_clicked();

    void on_NewLineB_clicked();

private:
    Ui::PrintText *ui;
};

#endif // PRINTTEXT_H
