#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->label_3->clear();
    int x, y, z;
    bool flag1, flag2;

    QString num1 = ui->lineEdit->text();
    x = num1.toInt(&flag1);

    QString num2 = ui->lineEdit_2->text();
    y = num2.toInt(&flag2);

    z = x + y;
    ui->label_3->setText(QString::number(z));

}
