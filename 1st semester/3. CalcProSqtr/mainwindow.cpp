#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <math.h>

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
    ui->labelOp2->setVisible(true);
    ui->lineEditOp2->setVisible(true);
}

void MainWindow::on_radioButtonDiv_clicked()
{
    ui->labelOp1->setText("Числитель");
    ui->labelOp2->setText("Знаменатель");
    ui->pushButton->setText("Частное");
    ui->labelOp2->setVisible(true);
    ui->lineEditOp2->setVisible(true);
}

void MainWindow::on_radioButtonMul_clicked()
{
    ui->labelOp1->setText("Множитель 1");
    ui->labelOp2->setText("Множитель 2");
    ui->pushButton->setText("Произведение");
    ui->labelOp2->setVisible(true);
    ui->lineEditOp2->setVisible(true);
}

void MainWindow::on_radioButtonSub_clicked()
{
    ui->labelOp1->setText("Уменьшаемое");
    ui->labelOp2->setText("Вычитаемое");
    ui->pushButton->setText("Разность");
    ui->labelOp2->setVisible(true);
    ui->lineEditOp2->setVisible(true);
}

void MainWindow::on_radioButtonSqrt_clicked()
{
    ui->labelOp1->setText("Извлекаемое");
    ui->pushButton->setText("Извлечь");
    ui->labelOp2->setVisible(false);
    ui->lineEditOp2->setVisible(false);
}

void MainWindow::on_pushButton_clicked()
{
    bool flag; //Признак успешной конвертации
    double op1, op2; //Операнты 1 и 2
    double res; //Результат
    QString tmpstring; //Строка для конвертации

    if (ui->radioButtonSum->isChecked()) //Сложение
    {
        tmpstring.clear();
        tmpstring.append(ui->lineEditOp1->text());
        op1=tmpstring.toDouble(&flag);

        if (flag) //Операнд 1 корректен
        {
            tmpstring.clear();
            tmpstring.append(ui->lineEditOp2->text());
            op2=tmpstring.toDouble(&flag);

            if (flag) //Операнд 2 корректен
            {
                ui->labelError->setVisible(false);  
                res=op1+op2;

                if (!isinf(res)) //Результат не бесконечен
                {
                    tmpstring.setNum(res);
                    ui->labelRes->setText(tmpstring);
                    ui->labelRes->setVisible(true);
                }
                else //Результат бесконечен
                {
                    ui->labelError->setVisible(true);
                    ui->labelError->setText("Результат вышел за диапозон");
                    ui->labelRes->setVisible(false);
                }
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

    if (ui->radioButtonSub->isChecked()) //Вычитание
    {
        tmpstring.clear();
        tmpstring.append(ui->lineEditOp1->text());
        op1=tmpstring.toDouble(&flag);

        if (flag) //Операнд 1 корректен
        {
            tmpstring.clear();
            tmpstring.append(ui->lineEditOp2->text());
            op2=tmpstring.toDouble(&flag);

            if (flag) //Операнд 2 корректен
            {                
                ui->labelError->setVisible(false);
                res=op1-op2;

                if (!isinf(res)) //Результат не бесконечен
                {
                    tmpstring.setNum(res);
                    ui->labelRes->setText(tmpstring);
                    ui->labelRes->setVisible(true);
                }
                else //Результат бесконечен
                {
                    ui->labelError->setVisible(true);
                    ui->labelError->setText("Результат вышел за диапозон");
                    ui->labelRes->setVisible(false);
                }

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
        op1=tmpstring.toDouble(&flag);

        if (flag) //Операнд 1 корректен
        {
            tmpstring.clear();
            tmpstring.append(ui->lineEditOp2->text());
            op2=tmpstring.toDouble(&flag);

            if (flag) //Операнд 2 корректен
            {
                ui->labelError->setVisible(false);
                res=op1*op2;
                if (!isinf(res)) //Результат не бесконечен
                {
                    tmpstring.setNum(res);
                    ui->labelRes->setText(tmpstring);
                    ui->labelRes->setVisible(true);
                }
                else //Результат бесконечен
                {
                    ui->labelError->setVisible(true);
                    ui->labelError->setText("Результат вышел за диапозон");
                    ui->labelRes->setVisible(false);
                }
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
        op1=tmpstring.toDouble(&flag);

        if (flag) //Операнд 1 корректен
        {
            tmpstring.clear();
            tmpstring.append(ui->lineEditOp2->text());
            op2=tmpstring.toDouble(&flag);

            if (flag and op2!=0) //Операнд 2 корректен
            {
                ui->labelError->setVisible(false);
                res=op1/op2;

                if (!isinf(res)) //Результат не бесконечен
                {
                    tmpstring.setNum(res);
                    ui->labelRes->setText(tmpstring);
                    ui->labelRes->setVisible(true);
                }
                else //Результат бесконечен
                {
                    ui->labelError->setVisible(true);
                    ui->labelError->setText("Результат вышел за диапозон");
                    ui->labelRes->setVisible(false);
                }

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

    if (ui->radioButtonSqrt->isChecked()) //Корень
    {
         tmpstring.clear();
         tmpstring.append(ui->lineEditOp1->text());
         op1=tmpstring.toDouble(&flag);

         if (flag and op1>=0) //Операнд корректен
         {
             ui->labelError->setVisible(false);
             res=sqrt(op1);

             if (!isinf(res)) //Результат не бесконечен
             {
                 tmpstring.setNum(res);
                 ui->labelRes->setText(tmpstring);
                 ui->labelRes->setVisible(true);
             }
             else //Результат бесконечен
             {
                 ui->labelError->setVisible(true);
                 ui->labelError->setText("Результат вышел за диапозон");
                 ui->labelRes->setVisible(false);
             }
         }

         else //Оперранд не корректен
         {
             ui->labelError->setText("Ошибка извлечения");
             ui->labelError->setVisible(true);
             ui->labelRes->setVisible(false);
        }
    }
}
