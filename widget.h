#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_generateButton_clicked();
    void on_stepSpinBox_valueChanged(int i);

    void on_linearRadioButton_toggled(bool checked);
    void on_squareRadioButton_toggled(bool checked);
    void on_cubicRadioButton_toggled(bool checked);


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
