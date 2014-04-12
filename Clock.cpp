#include "Clock.h"
#include <QTimer>

Clock::Clock(QWidget *parent)
    : QWidget(parent)
{
    size = 350;
    halfsize = size/2;
    scale = 1;
    resize(size,size);

    QTimer* timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(disp()));
    timer->start(1000);
}

Clock::Clock (int i_size, QWidget *parent)
    : QWidget(parent)
{
    size = i_size;
    halfsize = size/2;
    scale = (double)size/350; //NB: n'oblie pas de le caster en double
    resize(size,size);

    QTimer* timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(disp()));
    timer->start(1000);
}

void Clock::paintEvent(QPaintEvent* event)
{


    QPainter paint_B(this);//paint background
    paint_B.scale(scale, scale);
    paint_B.drawPixmap(0,0,QPixmap("clock_B.png"));// on peut préciser aussi le largeur et hauteur
                                                  //paint.drawPixmap(0,0,400,400,QPixmap("clock_B.png"))


    QTime time = QTime::currentTime();

    QPainter paint_h(this);
    paint_h.translate(halfsize, halfsize);
    paint_h.rotate(180 + 30*time.hour() + 0.5*time.minute()); // +30*time.minute()/60
    paint_h.scale(scale,scale);
    paint_h.drawPixmap(-3,-20,QPixmap("h_hand.png"));

    QPainter paint_m(this);
    paint_m.translate(halfsize, halfsize);
    paint_m.rotate(180 + 6*time.minute());
    paint_m.scale(scale,scale);
    paint_m.drawPixmap(-3,-20,QPixmap("m_hand.png"));

    QPainter paint_s(this);
    paint_s.translate(halfsize, halfsize);
    paint_s.rotate(180+6*time.second());
    paint_s.scale(scale,scale);
    paint_s.drawPixmap(-3,-30,QPixmap("s_hand.png"));


}

void Clock::disp()
{

    update();
}
