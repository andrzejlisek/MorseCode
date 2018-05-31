#include "qlabelkey.h"

QLabelKey::QLabelKey(QWidget *parent) : QLabel(parent)
{
    this->setFocusPolicy(Qt::StrongFocus);
}

//QLabelKey::~QLabelKey()
//{
//
//}

void QLabelKey::keyPressEvent(QKeyEvent * event)
{
    QLabel::keyPressEvent(event);
    emit KeyPress(event);
}

void QLabelKey::keyReleaseEvent(QKeyEvent * event)
{
    QLabel::keyReleaseEvent(event);
    emit KeyRelease(event);
}

void QLabelKey::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    /*QRect geo = this->geometry();
    int x, y, width, height;

    x = geo.x()-10;
    y = geo.y()-10;
    width = geo.width()-3;
    height = geo.height()-5;*/
    if (ImgX != NULL)
    {
        painter.drawImage(0, 0, *ImgX);
    }
    else
    {
        QLabel::paintEvent(event);
    }
}
