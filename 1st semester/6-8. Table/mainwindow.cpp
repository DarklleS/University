#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <time.h>
#include <algorithm>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->lineEdit_col->setAlignment(Qt::AlignCenter);
    ui->lineEdit_search->setAlignment(Qt::AlignCenter);
    ui->label_messege->setAlignment(Qt::AlignCenter);
    ui->label_searchDup->setAlignment(Qt::AlignCenter);
    ui->label_searchMessege->setAlignment(Qt::AlignCenter);
    ui->label_searchIndex->setAlignment(Qt::AlignCenter);
    ui->label_correctSearch->setAlignment(Qt::AlignCenter);
    ui->label_error->setAlignment(Qt::AlignCenter);
    ui->label_correctSearch->setVisible(false);
    ui->label_messege->setVisible(false);
    ui->label_searchMessege->setVisible(false);
    ui->label_searchDup->setVisible(false);
    ui->label_searchIndex->setVisible(false);
    ui->label_error->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//-------------------------------------------------------------------------------//
//--------------------------- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ---------------------------//
//-------------------------------------------------------------------------------//

void MainWindow::hideMessege() // Функция скрытия сообщений
{
    ui->label_messege->setVisible(false);
    ui->label_searchMessege->setVisible(false);
    ui->label_searchDup->setVisible(false);
    ui->label_searchIndex->setVisible(false);
    ui->label_correctSearch->setVisible(false);
    ui->label_error->setVisible(false);
}

void MainWindow::showMessege() // Функция демонстрации результата
{
    ui->label_messege->setStyleSheet("background-color: red; font-size: 24px; color: white");
    ui->label_messege->setVisible(true);
}

void MainWindow::intError(int idCol, int size) // Функция демонстрации ошибки при неверно введеном значении в ячейку таблицы
{
    int j = idCol; // Переменная индификатора столбца таблицы

    ui->tableWidget->item(0,j)->setSelected(false);
    ui->label_error->setText("Введите верные данные в ячейки!");
    ui->label_error->setStyleSheet("color: white; background-color: red; font-size: 24px");
    ui->label_error->setVisible(true);

    for (j = idCol; j < size; j++)
    {
        if (ui->tableWidget->item(0, j) != NULL)
        {
            bool flag;
            ui->tableWidget->item(0, j)->text().toInt(&flag);

            if (flag)
                ui->tableWidget->item(0,j)->setBackgroundColor(Qt::darkGray);
            else
                ui->tableWidget->item(0,j)->setBackgroundColor(Qt::red);
        }
        else if (ui->tableWidget->item(0, j) == NULL)
        {
            QTableWidgetItem * newItem;
            newItem = new QTableWidgetItem;
            ui->tableWidget->setItem(0,j,newItem);
            ui->tableWidget->item(0,j)->setBackgroundColor(Qt::red);
        }
    }
    ui->tableWidget->scrollToItem(ui->tableWidget->item(0, idCol));
}

void MainWindow::nullError(int idCol, int size) // Функция демонстрации ошибки при существовании пустой ячейки
{
    int j = idCol; // Переменная индификатора столбца таблицы

    ui->label_error->setText("Введите верные данные в ячейки!");
    ui->label_error->setStyleSheet("color: white; background-color: red; font-size: 24px");
    ui->label_error->setVisible(true);

    for (j = idCol; j < size; j++)
    {
        if (ui->tableWidget->item(0, j) == NULL)
        {
            QTableWidgetItem * newItem;
            newItem = new QTableWidgetItem;
            ui->tableWidget->setItem(0,j,newItem);
            ui->tableWidget->item(0,j)->setBackgroundColor(Qt::red);
        }
    }
    ui->tableWidget->scrollToItem(ui->tableWidget->item(0, idCol));
}


int MainWindow::mainArray(int arr[], int size) // Функция главного массива берущего значения из ячеек таблицы
{
    int num; // Переменная значения ячейки таблицы
    int numCol = size; // Переменная кол-ва столбцов таблицы
    bool flag = false; // Переменная проверки

    for (int j=0; j < numCol; j++)
    {
        if (ui->tableWidget->item(0,j) != NULL) // Проверка ячейки на не пустоту
        {
            num = ui->tableWidget->item(0,j)->text().toInt(&flag); // Присваивание переменной значения из ячейки таблицы
            if (flag) // Проверка верности введенных значений
            {
                arr[j] = num;
                ui->tableWidget->item(0,j)->setBackgroundColor(Qt::darkGray);
            }
            else
            {
                intError(j, numCol); // Вывод ошибки при неверно введеном значении в ячейку таблицы
                break;
            }
        }
        else if ((ui->tableWidget->item(0,j)== NULL) && j < numCol) // Проверка ячейки на пустоту
        {
            nullError(j, numCol); // Вывод ошибки при существовании пустой ячейки
            flag = 0;
            break;
        }
    }
    return flag; // Возращение значения переменной
}

void MainWindow::deleteDub (int *arr, int &size) // Функция удаления дублированных ячеек таблицы
{
    int i = 0; // Переменная значения длины

    for (int j = i + 1; j < size; j++)
    {
        if (arr[i] != arr[j]) // Проверка неравества значений эллемента с последующим значением
        {
            i++;
            arr[i]=arr[j];
        }
    }

    size = i+1;
}

void MainWindow::outputArray(int arr[], int size) // Функция вывода значений ячеек таблицы
{
    int num; // Переменная значения ячейки таблицы
    int numCol = ui->tableWidget->columnCount(); // Переменная кол-ва столбцов таблицы
    QString str; // Переменная конвертации значения ячейки таблицы

    for (int j = 0; j < size; j++)
    {
        num = arr[j]; // Присваивание переменной значения ячейки массива
        str.setNum(num); // Конвертация значения ячейки массива в строку
        ui->tableWidget->item(0,j)->setText(str); // Вывод значения ячейки массива на ячейку таблицы
    }

    int newCol = numCol - size; // Переменная нового размера таблицы
    ui->tableWidget->setColumnCount(numCol - newCol); // Ввод новой длины столбцов таблицы
}

int MainWindow::quickSort(int *arr, int size)
{
    int l = 0; // Переменная левого края массива
    int r = size; // Переменная правого края массива
    int m = arr[size/2]; // Переменная центральной ячейки массива

    do
    {
        while (arr[l] < m)
            l++;
        while (arr[r] > m)
            r--;
        if (l <= r)
        {
            swap(arr[l], arr[r]);
            l++;
            r--;
        }
    }
    while (l <= r);

    if (r > 0) quickSort(arr, r);
    if (size > 0) quickSort(arr + l, size - l);

    return 0;
}

//------------------------------------------------------

bool MainWindow::bogoSortSorted(int *arr, int size) // Функция проверки отсортированного массива
{
    while (--size > 0)
        if (arr[size - 1] > arr[size])
            return 0;
    return 1;
}

void MainWindow::bogoSortShuffle(int *arr, int size, int &k) // Функция перестановки ячеек массива
{
    for (int i = 0; i < size; i++)
    {
        swap(arr[i], arr[rand() % size]);
        k++;
    }
}

int MainWindow::bogoSort(int arr[], int size, int &k) // Функция основного метода обезьяньей сортировки
{
    int sorted = bogoSortSorted(arr, size);
    while (!sorted && k < 1000)
        bogoSortShuffle(arr, size, k);
    return sorted;
}

//------------------------------------------------------------------------------------------------------------------------------//
//--------------------------- #6 | ВВОД ДАННЫХ | ГЕНЕРАЦИЯ ЗНАЧЕНИЙ | НАХОЖДЕНИЕ ПРЕДЕЛОВ ДИАПОЗОНОВ ---------------------------//
//------------------------------------------------------------------------------------------------------------------------------//

void MainWindow::on_pushButton_enter_clicked() // Функция ввода кол-ва столбцов
{
    hideMessege(); // Скрытие сообщений

    ui->tableWidget->setColumnCount(ui->tableWidget->columnCount()*0);
    int col = ui->lineEdit_col->text().toInt(); // Переменная считывания значения кол-ва столбцов

    if (col<=200 && col >=1) // Проверка на диапозон введенных значений
    {
        ui->tableWidget->setColumnCount(ui->tableWidget->columnCount()+col);
        showMessege();
        ui->label_messege->setText("Ввод " + QString::number(col) + " столбцов прошел успешно!");
        ui->label_messege->setStyleSheet("background-color: green; font-size: 24px; color: white");
    }
    else
    {
        showMessege();
        ui->label_messege->setText("Введите кол-во от 1 до 200 столбцов!");
    }
}

void MainWindow::on_pushButton_random_clicked() // Фукция генерациии рандомых чисел в ячейках таблицы
{
    int num; // Переменная значения ячейки таблицы
    int numCol = ui->tableWidget->columnCount(); // Переменная кол-ва столбцов таблицы

    hideMessege(); // Скрытие сообщений
    srand(clock()); // Генерация рандомных значений

    if (ui->tableWidget->columnCount()==0) // Проверка на пустоту таблицы
    {
        showMessege();
        ui->label_messege->setText("Введите кол-во столбцов!");
    }
    else
    {
        for (int j = 0; j < numCol; j++)
        {
            if (ui->tableWidget->item(0, j) == NULL) // Проверка на несуществующие ячейки
            {
                QTableWidgetItem * newItem;
                newItem = new QTableWidgetItem;
                ui->tableWidget->setItem(0, j, newItem);
            }
            ui->tableWidget->item(0, j)->setBackgroundColor(Qt::darkGray);
            num = rand()%201-100;
            ui->tableWidget->item(0, j)->setText(QString::number(num));
        }
        showMessege();
        ui->label_messege->setText("Генерация случайных чисел прошла успешно!");
        ui->label_messege->setStyleSheet("background-color: green; font-size: 24px; color: white");
    }
}

void MainWindow::on_pushButton_max_clicked() // Функция нахождения максимального эллемента среди ячеек таблицы
{
    int num; // Переменная значения ячейки таблицы
    int numCol = ui->tableWidget->columnCount(); // Переменная кол-ва столбцов таблицы
    int max = INT_MIN; // Переменная максимального значения ячейки таблицы
    bool flag = 0; // Переменная проверки условий функции

    hideMessege(); // Скрытие сообщений

    if (ui->tableWidget->columnCount()==0)
        showMessege(); // Вывод ошибки в значении кол-ва столбцов таблицы

    for (int j = 0; j < numCol; j++)
    {
        if (ui->tableWidget->item(0, j) != NULL) // Проверка на несуществующие ячейки
        {
            num = ui->tableWidget->item(0, j)->text().toInt(&flag);
            if (flag)
                ui->tableWidget->item(0, j)->setBackgroundColor(Qt::darkGray);
            if (flag && (num > max))
            {
                max = num;
            }
            if (!flag)
            {
                intError(j, numCol);
                break;
            }
        }
        else if ((ui->tableWidget->item(0, j) == NULL) && (j < numCol))
        {
            nullError(j, numCol);
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        showMessege();
        ui->label_messege->setText("Максимальное значение: " + QString::number(max));
        ui->label_messege->setStyleSheet("background-color: purple; font-size: 24px; color: white");
    }
}

void MainWindow::on_pushButton_min_clicked() // Функция нахождения минимального эллемента среди ячеек таблицы
{
    int num; // Переменная значения ячейки таблицы
    int numCol = ui->tableWidget->columnCount(); // Переменная кол-ва столбцов
    int min = INT_MAX; // Переменная минимального значения ячейки таблицы
    bool flag = 0; // Переменная проверки условий функции

    hideMessege(); // Скрытие сообщений

    if (ui->tableWidget->columnCount()==0)
        showMessege(); // Вывод ошибки в значении кол-ва столбцов таблицы

    for (int j = 0; j < numCol; j++)
    {
        if (ui->tableWidget->item(0, j) != NULL) // Проверка на несуществующие ячейки
        {
            num = ui->tableWidget->item(0, j)->text().toInt(&flag);

            if (flag)
                ui->tableWidget->item(0, j)->setBackgroundColor(Qt::darkGray);
            if (flag && (num < min))
            {
                min = num;
                ui->tableWidget->item(0, j)->setBackgroundColor(Qt::darkGray);
            }
            if (!flag)
            {
                intError(j, numCol);
                break;
            }
        }
        else if ((ui->tableWidget->item(0, j) == NULL) && (j < numCol))
        {
            nullError(j, numCol);
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        showMessege();
        ui->label_messege->setText("Минимальное значение: " + QString::number(min));
        ui->label_messege->setStyleSheet("background-color: rgb(0, 160, 160); font-size: 24px; color: white");
    }
}

void MainWindow::on_pushButton_avg_clicked() // Функция нахождения среднего значения среди всех эллементов таблицы
{
    int num; // Переменная значения ячейки таблицы
    int numCol = ui->tableWidget->columnCount(); // Переменная кол-ва столбцов
    int sum = 0; // Переменная суммы всех значений ячеек таблицы
    bool flag = 0; // Переменная проверки условий функции

    hideMessege(); // Скрытие сообщений

    if (ui->tableWidget->columnCount()==0)
        showMessege(); // Вывод ошибки в значении кол-ва столбцов таблицы

    for (int j = 0; j < numCol; j++)
    {
        if (ui->tableWidget->item(0, j) != NULL) // Проверка на несуществующие ячейки
        {
            num = ui->tableWidget->item(0, j)->text().toInt(&flag);
            if (flag)
            {
                sum += num;
                ui->tableWidget->item(0, j)->setBackgroundColor(Qt::darkGray);
            }
            if (!flag)
            {
                intError(j, numCol);
                break;
            }
        }
        else if ((ui->tableWidget->item(0, j) == NULL) && (j < numCol))
        {
            nullError(j, numCol);
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        ui->label_messege->setText("Среднее значение: " + QString::number(sum / numCol));
        showMessege();
        ui->label_messege->setStyleSheet("background-color: orange; font-size: 24px; color: white");
    }
}

//-------------------------------------------------------------------------------------------------//
//--------------------------- #7 | СОРТИРОВКА ЯЧЕЕК ТАБЛИЦЫ АЛГОРИТМАМИ ---------------------------//
//-------------------------------------------------------------------------------------------------//

void MainWindow::on_pushButton_bubbleSort_clicked() // Функция сортировки эллементов таблицы алгоритмом - сортировка пузярьком
{
    hideMessege(); // Скрытие сообщений

    if (ui->tableWidget->columnCount()==0) // Проверка на пустоту таблицы
    {
        showMessege();
        ui->label_messege->setText("Введите кол-во столбцов!");
    }

    int numCol=ui->tableWidget->columnCount(); // Переменная значения ячейки таблицы
    int arr[200]; // Переменная ячейки массива
    int flag = mainArray(arr, numCol); // Переменная ввода значений ячеек таблицы в массив

    if (flag) // Проверка на верность введенных данных в массиве
    {
        for (int i = 0; i < numCol; i++)
        {
            for (int j = 0; j < numCol - 1; j++)
            {
                if (arr[i] < arr[j])
                {
                    swap(arr[i], arr[j]);
                }
            }
        }
        outputArray(arr, numCol); // Вывод значений полученных после сортировки
        showMessege();
        ui->label_messege->setText("Сортировка прошла успешно!");
        ui->label_messege->setStyleSheet("background-color: green; font-size: 24px; color: white");
    }
}

void MainWindow::on_pushButton_quickSort_clicked() // Функция сортировки эллементов таблицы алгоритмом - быстрая сортировка
{
    hideMessege(); // Скрытие сообщений

    if (ui->tableWidget->columnCount()==0) // Проверка на пустоту таблицы
    {
        showMessege();
        ui->label_messege->setText("Введите кол-во столбцов!");
    }

    int numCol = ui->tableWidget->columnCount(); // Переменная значения ячейки таблицы
    int arr[200];
    int flag = mainArray(arr, numCol); // Переменная ввода значений ячеек таблицы в массив

    if (flag) // Проверка на верность введенных данных в массиве
    {
        quickSort(arr, numCol-1); // Запуск функции быстрой сортировки
        outputArray(arr, numCol); // Вывод значений полученных после сортировки
        showMessege();
        ui->label_messege->setText("Сортировка прошла успешно!");
        ui->label_messege->setStyleSheet("background-color: green; font-size: 24px; color: white");
    }
}

void MainWindow::on_pushButton_combSort_clicked() // Функция сортировки эллементов таблицы алгоритмом - сортировка расческой
{
    hideMessege(); // Скрытие сообщений

    if (ui->tableWidget->columnCount()==0) // Проверка на пустоту таблицы
    {
        showMessege();
        ui->label_messege->setText("Введите кол-во столбцов!");
    }

    int numCol = ui->tableWidget->columnCount(); // Переменная значения ячейки таблицы
    int arr[200]; // Переменная ячейки массива
    int flag = mainArray(arr, numCol); // Переменная ввода значений ячеек таблицы в массив
    int step = numCol; // Переменная шага
    int trans = true; // Пременная признака перестановки
    int i; // Переменная индекса ячейки массива

    if (flag) // Проверка на верность введенных данных в массиве
    {
        while (step > 1 || trans)
        {
            if (step>1)
            {
                step /= 1.247;
            }

            trans = false;
            i = 0;

            while ((i + step) < numCol)
            {
                if (arr[i] > arr[i+step])
                {
                    swap(arr[i], arr[i+step]);
                    trans = true;
                }
                i++;
            }
        }
        outputArray(arr, numCol); // Вывод значений полученных после сортировки
        showMessege();
        ui->label_messege->setText("Сортировка прошла успешно!");
        ui->label_messege->setStyleSheet("background-color: green; font-size: 24px; color: white");
    }
}

void MainWindow::on_pushButton_gnomeSort_clicked() // Функция сортировки эллементов таблицы алгоритмом - гномья мортировка
{
    hideMessege(); // Скрытие сообщений

    int i = 0; // Переменная индекса ячейки массива
    int numCol = ui->tableWidget->columnCount(); // Переменная значения ячейки таблицы
    int arr[200]; // Переменная ячейки массива
    int flag = mainArray(arr, numCol); // Переменная ввода значений ячеек таблицы в массив

    if (ui->tableWidget->columnCount()==0) // Проверка на пустоту таблицы
    {
        showMessege();
        ui->label_messege->setText("Введите кол-во столбцов!");
    }

    if (flag) // Проверка на верность введенных данных в массиве
    {
        while (i < numCol)
        {
            if (i == 0 || (arr[i-1] <= arr[i]))
                i++;
            else
            {
                swap(arr[i], arr[i-1]);
                i--;
            }
            outputArray(arr, numCol);
        }
        showMessege();
        ui->label_messege->setText("Сортировка прошла успешно!");
        ui->label_messege->setStyleSheet("background-color: green; font-size: 24px; color: white");
    }
}

void MainWindow::on_pushButton_bogoSort_clicked() // Функция сортировки эллементов таблицы алгоритмом - обезьянья сортировка
{
    hideMessege(); // Скрытие сообщений

    int numCol = ui->tableWidget->columnCount(); // Переменная значения ячейки таблицы
    int arr[200];
    int flag = mainArray(arr, numCol); // Переменная ввода значений ячеек таблицы в массив
    int k = 0;

    if (ui->tableWidget->columnCount()==0) // Проверка на пустоту таблицы
    {
        showMessege();
        ui->label_messege->setText("Введите кол-во столбцов!");
    }

    if (flag) // Проверка на верность введенных данных в массиве
    {
        bool correct = bogoSort(arr, numCol, k); // Переменная проверки корректно выполненой работы алгоритма

        if (correct)
        {
            outputArray(arr, numCol); // Вывод значений полученных после сортировки
            showMessege();
            ui->label_messege->setText("Сортировка прошла успешно!");
            ui->label_messege->setStyleSheet("background-color: green; font-size: 24px; color: white");
        }
        else
        {
            showMessege();
            ui->label_messege->setText("Сортировка была не выполнена т.к. предел времени был превышен!");
            ui->label_messege->setStyleSheet("background-color: orange; font-size: 22px; color: white");
        }
    }
}

void MainWindow::on_pushButton_delete_clicked() // Функция удаления дублированных значений из ячеек таблицы
{
    hideMessege(); // Скрытие сообщений

    int numCol = ui->tableWidget->columnCount(); // Переменная значения ячейки таблицs
    const int count = numCol;
    int arr[200];
    int flag = mainArray(arr, numCol); // Переменная ввода значений ячеек таблицы в массив
    int correct = 0;

    if (ui->tableWidget->columnCount()==0) // Проверка на пустоту таблицы
    {
        showMessege();
        ui->label_messege->setText("Введите кол-во столбцов!");
    }

    if (flag) // Проверка на верность введенных данных в массиве
    {
        for (int i = 0; i < numCol; i++)
            for  (int j = 0; j < numCol-1; j++)
            {
                if (arr[j] > arr[j+1])
                {
                    correct = 0;
                    break;
                }
                else
                {
                    correct = 1;
                }
            }

        if (correct == 1)
        {
            deleteDub(arr, numCol);
            outputArray(arr, numCol);
            showMessege();
            if (numCol != count)
            {
                ui->label_messege->setText("Удаление дубликатов прошло успешно!");
                ui->label_messege->setStyleSheet("background-color: green; font-size: 24px; color: white");
            }
            else
            {
                ui->label_messege->setText("Удаление дубликатов было не выполнено т.к. в таблице отсуствуют дубликаты!");
                ui->label_messege->setStyleSheet("background-color: orange; font-size: 24px; color: white");
            }


        }
        else
        {
            showMessege();
            ui->label_messege->setText("Массив не отсортирован!");
        }
    }
}

//------------------------------------------------------------------------------------------//
//--------------------------- #8 | ПОИСК ЗНАЧЕНИЯ ЯЧЕЙКИ МАССИВА ---------------------------//
//------------------------------------------------------------------------------------------//

void MainWindow::linearSearch(int *arr, int size, int k, int &n, QString &arrStr) // Функция линейного поиска
{
    int arrItems[200];
    for (int j = 0; j < size; j++)
        if (k == arr[j])
        {
            arrStr += QString::number(j+1) + " ";
            arrItems[n++] = j;
        }
}

int MainWindow::binarySearch(int *arr, int size, int k) // Функция бинарного поиска
{
    int l = 0;
    int r = size;

    while (l <= r)
    {
        int m = (l+r)/2;

        if (k < arr[m])
            r = m - 1;
        else if (k > arr[m])
            l = m + 1;
        else
        {
            return m;
        }
    }
    return -1;
}

void MainWindow::on_pushButton_search_clicked()
{
    hideMessege(); // Скрытие сообщений

    ui->label_correctSearch->setVisible(true);

    int numCol = ui->tableWidget->columnCount(); // Переменная значения ячейки таблицs
    int arr[200];
    int flag = mainArray(arr, numCol); // Переменная ввода значений ячеек таблицы в массив
    int correct = 0;
    bool flagNum = 1;
    int k = ui->lineEdit_search->text().toInt(&flagNum);
    int n = 0;
    int count = 0;
    QString arrStr;

    if (flag) // Проверка на верность введенных данных в массиве
    {
        for (int i = 0; i < numCol; i++) // Проверка на сортировку
            for  (int j = 0; j < numCol-1; j++)
            {
                if (arr[j] > arr[j+1])
                {
                    correct = 0;
                    count = 0;
                    break;
                }
                else if (arr[j] == arr[j+1])
                {
                    count = 1;
                    correct = 1;
                }
                else
                    correct = 1;
            }

        if (correct == 1) // Сортировка выполнена
        {
            if (flagNum) // Проверка на верность введенных данных
            {
                if (count != 1) // Проверка на отсутсвие дубликатов
                {
                    int bin = binarySearch(arr, numCol, k);

                    if (bin != -1) // Выполнение бинарного поиска
                    {

                        ui->label_correctSearch->setVisible(true);
                        ui->label_searchMessege->setVisible(true);
                        ui->label_searchDup->setVisible(true);
                        ui->label_searchIndex->setVisible(true);
                        ui->label_correctSearch->setText("Бинарный поиск прошел успешно!");
                        ui->label_correctSearch->setStyleSheet("background-color: green; font-size: 24px; color: white");
                        ui->label_searchMessege->setText("Результат бинарного поиска числа: " + QString::number(k));
                        ui->label_searchIndex->setText("Номер ячейки: " + QString::number(bin+1));
                        ui->label_searchDup->setText("Кол-во совпадений: 1");
                        ui->label_searchMessege->setStyleSheet("background-color: purple; color: white");
                        ui->label_searchIndex->setStyleSheet("background-color: #333; border-radius: 15px; color: white");
                        ui->label_searchDup->setStyleSheet("background-color: #333; color: white");
                    }
                    else // Не найдено совпадений
                    {
                        ui->label_correctSearch->setVisible(true);
                        ui->label_searchMessege->setVisible(false);
                        ui->label_searchDup->setVisible(false);
                        ui->label_searchIndex->setVisible(false);
                        ui->label_correctSearch->setText("Число " + QString::number(k) + " было нe найдено!");
                        ui->label_correctSearch->setStyleSheet("background-color: red; font-size: 24px; color: white");
                    }
                }
                else if (count == 1) // Проверка на существование дубликатов
                {
                    linearSearch(arr, numCol, k, n, arrStr);

                    if (n > 0) // Выполнение линейного поиска
                    {

                        ui->label_correctSearch->setVisible(true);
                        ui->label_searchMessege->setVisible(true);
                        ui->label_searchDup->setVisible(true);
                        ui->label_searchIndex->setVisible(true);
                        ui->label_correctSearch->setText("Линейный поиск прошел успешно!");
                        ui->label_correctSearch->setStyleSheet("background-color: green; font-size: 24px; color: white");
                        ui->label_searchMessege->setText("Результат линейного поиска числа: " + QString::number(k));
                        ui->label_searchIndex->setText("Номера ячеек: " + arrStr);
                        ui->label_searchDup->setText("Кол-во совпадений: " + QString::number(n));
                        ui->label_searchMessege->setStyleSheet("background-color: orange; color: white");
                        ui->label_searchIndex->setStyleSheet("background-color: #333; border-radius: 15px; color: white");
                        ui->label_searchDup->setStyleSheet("background-color: #333; color: white");
                    }
                    else // Не найдено совпадений
                    {
                        ui->label_correctSearch->setVisible(true);
                        ui->label_searchMessege->setVisible(false);
                        ui->label_searchDup->setVisible(false);
                        ui->label_searchIndex->setVisible(false);
                        ui->label_correctSearch->setText("Число " + QString::number(k) + " было нe найдено!");
                        ui->label_correctSearch->setStyleSheet("background-color: red; font-size: 24px; color: white");
                    }
                }

            }
            else // Введено не верное значение
            {
                ui->label_correctSearch->setVisible(true);
                ui->label_searchMessege->setVisible(false);
                ui->label_searchDup->setVisible(false);
                ui->label_searchIndex->setVisible(false);
                ui->label_correctSearch->setText("Введите верное число в поле поиска!");
                ui->label_correctSearch->setStyleSheet("background-color: red; font-size: 24px; color: white");
            }
        }
        else // Сортировка не выполнена
        {
            if (flagNum) // Проверка на верность введенного значения
            {
                linearSearch(arr, numCol, k, n, arrStr);

                if (n > 0) // Выполнение линейного поиска
                {
                    ui->label_correctSearch->setVisible(true);
                    ui->label_searchMessege->setVisible(true);
                    ui->label_searchDup->setVisible(true);
                    ui->label_searchIndex->setVisible(true);
                    ui->label_correctSearch->setText("Линейный поиск прошел успешно!");
                    ui->label_correctSearch->setStyleSheet("background-color: green; font-size: 24px; color: white");
                    ui->label_searchMessege->setText("Результат линейного поиска числа: " + QString::number(k));
                    ui->label_searchIndex->setText("Номера ячеек: " + arrStr);
                    ui->label_searchDup->setText("Кол-во совпадений: " + QString::number(n));
                    ui->label_searchMessege->setStyleSheet("background-color: orange; color: white");
                    ui->label_searchIndex->setStyleSheet("background-color: #333; border-radius: 15px; color: white");
                    ui->label_searchDup->setStyleSheet("background-color: #333; color: white");
                }
                else // Не найдено совпадений
                {
                    ui->label_correctSearch->setVisible(true);
                    ui->label_searchMessege->setVisible(false);
                    ui->label_searchDup->setVisible(false);
                    ui->label_searchIndex->setVisible(false);
                    ui->label_correctSearch->setText("Число " + QString::number(k) + " было нe найдено!");
                    ui->label_correctSearch->setStyleSheet("background-color: red; font-size: 24px; color: white");
                }
            }
            else // Не верно введенное число
            {
                ui->label_correctSearch->setVisible(true);
                ui->label_searchMessege->setVisible(false);
                ui->label_searchDup->setVisible(false);
                ui->label_searchIndex->setVisible(false);
                ui->label_correctSearch->setText("Введите верное число в поле поиска!");
                ui->label_correctSearch->setStyleSheet("background-color: red; font-size: 24px; color: white");
            }
        }
    }
}


void MainWindow::on_tableWidget_itemChanged()
{
    hideMessege();
    ui->label_error->setVisible(true);
}
