#ifndef QLABELKEY_H
#define QLABELKEY_H

#include <QObject>
#include <QKeyEvent>
#include <QLabel>
#include <QDebug>
#include <QPainter>

class QLabelKey : public QLabel
{
    Q_OBJECT
public:
    explicit QLabelKey(QWidget *parent = 0);
    //~QLabelKey();
    QImage * ImgX = NULL;

signals:
    void KeyPress(QKeyEvent *event);
    void KeyRelease(QKeyEvent *event);

public slots:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // QLABELKEY_H
