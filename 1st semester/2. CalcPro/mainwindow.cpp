#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelError->setVisible(false);
    ui->labelRes->setVisible(false);
    ui->radioButtonSum->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_radioButtonSum_clicked()
{
    ui->labelOp1->setText("Слагаемое 1");
    ui->labelOp2->setText("Слагаемое 2");
    ui->pushButton->setText("Сумма");
}

void MainWindow::on_radioButtonDiv_clicked()
{
    ui->labelOp1->setText("Числитель");
    ui->labelOp2->setText("Знаменатель");
    ui->pushButton->setText("Частное");
}

void MainWindow::on_radioButtonMul_clicked()
{
    ui->labelOp1->setText("Множитель 1");
    ui->labelOp2->setText("Множитель 2");
    ui->pushButton->setText("Произведение");
}

void MainWindow::on_radioButtonSub_clicked()
{
    ui->labelOp1->setText("Уменьшаемое");
    ui->labelOp2->setText("Вычитаемое");
    ui->pushButton->setText("Разность");
}



void MainWindow::on_pushButton_clicked()
{
    bool flag; //Признак успешной конвертации
    int op1, op2; //Операнты 1 и 2
    int res; //Результат
    QString tmpstring; //Строка для конвертации

    if (ui->radioButtonSum->isChecked()) //Сложение
    {
        tmpstring.clear();
        tmpstring.append(ui->lineEditOp1->text());
        op1=tmpstring.toInt(&flag);

        if (flag) //Операнд 1 корректен
        {
            tmpstring.clear();
            tmpstring.append(ui->lineEditOp2->text());
            op2=tmpstring.toInt(&flag);

            if (flag) //Операнд 2 корректен
            {
                ui->labelError->setVisible(false);
                res=op1+op2;
                ui->labelRes->setNum(res);
                ui->labelRes->setVisible(true);
            }
            else //Операнд 2 не корректен
            {
                ui->labelError->setText("Ошибка в слагаемом 2");
                ui->labelError->setVisible(true);
                ui->labelRes->setVisible(false);
            }
        }
        else //Операнд 1 не корректен
        {
            ui->labelError->setText("Ошибка в слагаемом 1");
            ui->labelError->setVisible(true);
            ui->labelRes->setVisible(false);
        }
    }

    if (ui->radioButtonSub->isChecked()) //Деление
    {
        tmpstring.clear();
        tmpstring.append(ui->lineEditOp1->text());
        op1=tmpstring.toInt(&flag);

        if (flag) //Операнд 1 корректен
        {
            tmpstring.clear();
            tmpstring.append(ui->lineEditOp2->text());
            op2=tmpstring.toInt(&flag);

            if (flag) //Операнд 2 корректен
            {                
                ui->labelError->setVisible(false);
                res=op1-op2;
                ui->labelRes->setNum(res);
                ui->labelRes->setVisible(true);
            }
            else //Операнд 2 не корректен
            {
                ui->labelError->setText("Ошибка в вычитаемом");
                ui->labelError->setVisible(true);
                ui->labelRes->setVisible(false);
            }
        }
        else //Операнд 1 не корректен
        {
            ui->labelError->setText("Ошибка в уменьшаемом");
            ui->labelError->setVisible(true);
            ui->labelRes->setVisible(false);
        }
    }

    if (ui->radioButtonMul->isChecked()) //Умножение
    {
        tmpstring.clear();
        tmpstring.append(ui->lineEditOp1->text());
        op1=tmpstring.toInt(&flag);

        if (flag) //Операнд 1 корректен
        {
            tmpstring.clear();
            tmpstring.append(ui->lineEditOp2->text());
            op2=tmpstring.toInt(&flag);

            if (flag) //Операнд 2 корректен
            {
                ui->labelError->setVisible(false);
                res=op1*op2;
                ui->labelRes->setNum(res);
                ui->labelRes->setVisible(true);
            }
            else //Операнд 2 не корректен
            {
                ui->labelError->setText("Ошибка в множителе 2");
                ui->labelError->setVisible(true);
                ui->labelRes->setVisible(false);
            }
        }
        else //Операнд 1 не корректен
        {
            ui->labelError->setText("Ошибка в множителе 1");
            ui->labelError->setVisible(true);
            ui->labelRes->setVisible(false);
        }
    }

    if (ui->radioButtonDiv->isChecked()) //Деление
    {
        tmpstring.clear();
        tmpstring.append(ui->lineEditOp1->text());
        op1=tmpstring.toInt(&flag);

        if (flag) //Операнд 1 корректен
        {
            tmpstring.clear();
            tmpstring.append(ui->lineEditOp2->text());
            op2=tmpstring.toInt(&flag);

            if (flag and op2!=0) //Операнд 2 корректен
            {
                ui->labelError->setVisible(false);
                res=op1/op2;
                ui->labelRes->setNum(res);
                ui->labelRes->setVisible(true);
            }
            else //Операнд 2 не корректен
            {
                ui->labelError->setText("Ошибка в знаменателе");
                ui->labelError->setVisible(true);
                ui->labelRes->setVisible(false);
            }
        }
        else //Операнд 1 не корректен
        {
            ui->labelError->setText("Ошибка в числителе");
            ui->labelError->setVisible(true);
            ui->labelRes->setVisible(false);
        }
    }
}
