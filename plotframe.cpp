#include <QtGlobal>
#include <QPainter>
#include <QTime>

#include "plotframe.h"

QPointF LinearInterpolation(QPointF &p1, QPointF &p2, double &t)
{
    return p1*(1-t)+p2*t;
}

QPointF CubicInterpolation(QPointF &p1, QPointF &p2, QPointF &p3, QPointF &p4, double &t)
{
    QPointF P0Div2   =  0.5* p1;
    QPointF P1mul1_5 =  1.5* p2;
    QPointF P2Div2   =  0.5* p3;
    QPointF P3Div2   =  0.5* p4;
    QPointF P1PlusP3 =  P1mul1_5 + P3Div2;

    QPointF m0 = p2;
    QPointF m1 = P2Div2 - P0Div2;
    QPointF m2 = p1 - m0 + p3 + p3 - P1PlusP3;
    QPointF m3 = P1PlusP3 - P2Div2  - P0Div2 - p3;

    return  m0 + m1*t + m2*t*t + m3*t*t*t;
}

QPointF SquareInterpolation(QPointF &p1, QPointF &p2, QPointF &p3, double &t)
{
    QPointF a = p3-2*p2+p1;
    QPointF b = 2*(p2-p1);
    QPointF c = p1;

    return a*t*t+b*t+c;
}

PlotFrame::PlotFrame(QWidget *parent) :
    QFrame(parent),
    m_interpolationStepCount(5),
    m_interpolationType(linear)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    generatePoints();
}

PlotFrame::~PlotFrame()
{
}

void PlotFrame::generatePoints()
{
    m_points.clear();

    int xdelta = width()/7;

    for (int i=1;i<7;++i){
        m_points.append(QPointF(i*xdelta,qrand()%height()));
    }

    update();
}

void PlotFrame::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing,true);


    if (m_points.size()<6)
        return;

    drawPoints(&painter);

    switch (m_interpolationType)    {
        case linear:
            drawInterLinear(&painter);
        break;
        case square:
            drawInterSquare(&painter);
        break;
        case cubic:
            drawInterCatmul(&painter);
        break;
    }
}


void PlotFrame::drawPoints(QPainter* _painter)
{
    if (!_painter)
        return;

    _painter->setPen(QPen(QBrush(Qt::red),5));

    for (int i=0;i<m_points.size();++i){
          _painter->drawPoint(m_points.at(i));
    }
}

void PlotFrame::drawInterLinear(QPainter *_painter)
{
    QPointF p1 = m_points.at(0);
    QPointF p2 = m_points.at(1);
    QPointF p3 = m_points.at(2);
    QPointF p4 = m_points.at(3);
    QPointF p5 = m_points.at(4);
    QPointF p6 = m_points.at(5);

    _painter->setPen(Qt::green);

    double tStart=0, tFinish=0;
    _painter->setPen(Qt::green);

    for(int i=0; i<m_interpolationStepCount; ++i)
    {
        tStart = tFinish;
        tFinish += 1.0/m_interpolationStepCount;

        _painter->drawLine(LinearInterpolation(p1,p2,tStart), LinearInterpolation(p1,p2,tFinish));
        _painter->drawLine(LinearInterpolation(p2,p3,tStart), LinearInterpolation(p2,p3,tFinish));
        _painter->drawLine(LinearInterpolation(p3,p4,tStart), LinearInterpolation(p3,p4,tFinish));
        _painter->drawLine(LinearInterpolation(p4,p5,tStart), LinearInterpolation(p4,p5,tFinish));
        _painter->drawLine(LinearInterpolation(p5,p6,tStart), LinearInterpolation(p5,p6,tFinish));
    }
}

void PlotFrame::drawInterSquare(QPainter *_painter)
{
    QPointF p1 = m_points.at(0);
    QPointF p2 = m_points.at(1);
    QPointF p3 = m_points.at(2);
    QPointF p4 = m_points.at(3);
    QPointF p5 = m_points.at(4);
    QPointF p6 = m_points.at(5);

    double tStart=0, tFinish=0;
    _painter->setPen(Qt::green);

    for(int i=0; i<m_interpolationStepCount; ++i)
    {
        tStart = tFinish;
        tFinish += 1.0/m_interpolationStepCount;

        _painter->drawLine(SquareInterpolation(p1,p2,p3,tStart), SquareInterpolation(p1,p2,p3,tFinish));
        _painter->drawLine(SquareInterpolation(p2,p3,p4,tStart), SquareInterpolation(p2,p3,p4,tFinish));
        _painter->drawLine(SquareInterpolation(p3,p4,p5,tStart), SquareInterpolation(p3,p4,p5,tFinish));
        _painter->drawLine(SquareInterpolation(p4,p5,p6,tStart), SquareInterpolation(p4,p5,p6,tFinish));
    }
}


void PlotFrame::drawInterCatmul(QPainter *_painter)
{
    QPointF p1 = m_points.at(0);
    QPointF p2 = m_points.at(1);
    QPointF p3 = m_points.at(2);
    QPointF p4 = m_points.at(3);
    QPointF p5 = m_points.at(4);
    QPointF p6 = m_points.at(5);

    double tStart=0, tFinish=0;
    _painter->setPen(Qt::green);

    for(int i=0; i<m_interpolationStepCount; ++i)
    {
        tStart = tFinish;
        tFinish += 1.0/m_interpolationStepCount;

        _painter->drawLine(CubicInterpolation(p1,p1,p2,p3,tStart), CubicInterpolation(p1,p1,p2,p3,tFinish));
        _painter->drawLine(CubicInterpolation(p1,p2,p3,p4,tStart), CubicInterpolation(p1,p2,p3,p4,tFinish));
        _painter->drawLine(CubicInterpolation(p2,p3,p4,p5,tStart), CubicInterpolation(p2,p3,p4,p5,tFinish));
        _painter->drawLine(CubicInterpolation(p3,p4,p5,p6,tStart), CubicInterpolation(p3,p4,p5,p6,tFinish));
        _painter->drawLine(CubicInterpolation(p4,p5,p6,p6,tStart), CubicInterpolation(p4,p5,p6,p6,tFinish));

    }
}

PlotFrame::interpolation_type_enum PlotFrame::interpolationType() const
{
    return m_interpolationType;
}

void PlotFrame::setInterpolationType(const interpolation_type_enum &interpolationType)
{
    m_interpolationType = interpolationType;

    update();
}

int PlotFrame::interpolationStepCount() const
{
    return m_interpolationStepCount;
}

void PlotFrame::setInterpolationStepCount(int interpolationStepCount)
{
    m_interpolationStepCount = interpolationStepCount;

    update();
}
