#include "mainwindow.h"
#include "ui_mainwindow.h"

bool op1=false, op2=false; // Логические переменные операндов 1 и 2 и результат
int res, comp=0; // Результат и индефикатор логических операций

int comparison(bool op1, bool op2, int comp) // Функция обозначения логических операций
{
    switch (comp)
    {
    case 0:
        res=(op1&&op2);
        break;
    case 1:
        res=(op1||op2);
        break;
    case 2:
        res=(op1^op2);
        break;
    case 3:
        res=(!op1);
        break;
    case 4:
        res=(op1==op2);
        break;
    case 5:
        res=(op1!=op2);
        break;
    case 6:
        res=!(op1||!op1)&&op2;
    }
    return res;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    changecolor(res);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changecolor(int res) // Функция изменения цвета
{
    res=comparison(op1, op2, comp);
    if (res)
    {
        this->setStyleSheet("background-color: green;");
    }
    else
    {
        this->setStyleSheet("background-color: red;");
    }
}

void MainWindow::on_comboBox_op1_currentIndexChanged(int index) // Функция обработки операнда 1
{
    op1=index;
    if (comp==3)
    {
        ui->comboBox_op2->setVisible(false);
    }
    changecolor(res);

}

void MainWindow::on_comboBox_op2_currentIndexChanged(int index) // Функция обработки операнда 2
{
    op2=index;
    changecolor(res);
}


void MainWindow::on_comboBox_comp_currentIndexChanged(int index) // Функция обработки операции сравнивания
{
    comp=index;
    ui->comboBox_op2->setVisible(true);
    if (comp==3)
    {
        ui->comboBox_op2->setVisible(false);
    }
    changecolor(res);
}
