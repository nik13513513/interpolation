#ifndef PLOTFRAME_H
#define PLOTFRAME_H

#include <QFrame>

class PlotFrame : public QFrame
{
    Q_OBJECT
public:
    enum interpolation_type_enum{
        linear,
        square,
        cubic
    };

    explicit PlotFrame(QWidget *parent = 0);
    ~PlotFrame();

    void generatePoints();

    int interpolationStepCount() const;
    void setInterpolationStepCount(int interpolationStepCount);

    PlotFrame::interpolation_type_enum interpolationType() const;
    void setInterpolationType(const interpolation_type_enum &interpolationType);

protected:
    void paintEvent(QPaintEvent *e);

private:
    void drawPoints(QPainter* _painter);

    void drawInterLinear(QPainter* _painter);
    void drawInterCatmul(QPainter* _painter);
    void drawInterSquare(QPainter *_painter);

private:
    QList<QPointF> m_points;

    int m_interpolationStepCount;

    interpolation_type_enum m_interpolationType;
};

#endif
