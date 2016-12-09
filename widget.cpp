#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->stepSpinBox->setValue(ui->frame->interpolationStepCount());

    setWindowTitle(tr("Интерполяция"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_generateButton_clicked()
{
    ui->frame->generatePoints();
}

void Widget::on_stepSpinBox_valueChanged(int i)
{
    ui->frame->setInterpolationStepCount(i);
}

void Widget::on_linearRadioButton_toggled(bool checked)
{
    if (checked){
        ui->frame->setInterpolationType(PlotFrame::linear);
        ui->lineGroupBox->setEnabled(false);
    }
}

void Widget::on_squareRadioButton_toggled(bool checked)
{
    if (checked){
        ui->frame->setInterpolationType(PlotFrame::square);
        ui->lineGroupBox->setEnabled(true);
    }
}

void Widget::on_cubicRadioButton_toggled(bool checked)
{
    if (checked){
        ui->frame->setInterpolationType(PlotFrame::cubic);
        ui->lineGroupBox->setEnabled(true);
    }
}
