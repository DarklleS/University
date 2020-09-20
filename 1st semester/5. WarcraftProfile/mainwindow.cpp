#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QValidator>
#include <QRegExpValidator>
#include <QDoubleValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , numValidator(1, 10, 1, this)
{
    ui->setupUi(this);

    double score = 20;
    ui->lineEdit_score->setText(QString::number(score));

    numValidator.setNotation(QDoubleValidator::StandardNotation); // Защита на ввод прочих символов (кроме цифр)

    ui->lineEdit_power->setValidator(&numValidator); // Призваивание защиты полю силы
    ui->lineEdit_agility->setValidator(&numValidator); // Призваивание защиты полю ловкости
    ui->lineEdit_mind->setValidator(&numValidator); // Призваивание защиты полю интеллекта
    ui->lineEdit_luck->setValidator(&numValidator); // Призваивание защиты полю удачи

    connect(ui->lineEdit_power, SIGNAL(textChanged(QString)), this, SLOT(on_score())); // Связь с функцией очков характеристик (on_score())
    connect(ui->lineEdit_agility, SIGNAL(textChanged(QString)), this, SLOT(on_score())); // Связь с функцией очков характеристик (on_score())
    connect(ui->lineEdit_mind, SIGNAL(textChanged(QString)), this, SLOT(on_score())); // Связь с функцией очков характеристик (on_score())
    connect(ui->lineEdit_luck, SIGNAL(textChanged(QString)), this, SLOT(on_score())); // Связь с функцией очков характеристик (on_score())

    ui->lineEdit_hp->setDisabled(true);
    ui->lineEdit_mp->setDisabled(true);
    ui->lineEdit_score->setDisabled(true);
    ui->lineEdit_attack->setDisabled(true);
    ui->lineEdit_defence->setDisabled(true);

    ui->label_congr->setAlignment(Qt::AlignCenter); // Выравнивание текста по центру
    ui->label_hero->setAlignment(Qt::AlignCenter); // Выравнивание текста по центру
    ui->lineEdit_score->setAlignment(Qt::AlignCenter); // Выравнивание текста по центру

    ui->label_congr->setVisible(false);
    ui->label_hero->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_score() // Функция работы очков характеристик
{
    double score = 20; // Переменная очков характеристик
    score = score - (ui->lineEdit_power->text().toDouble() + ui->lineEdit_agility->text().toDouble() + ui->lineEdit_mind->text().toDouble() + ui->lineEdit_luck->text().toDouble());
    ui->lineEdit_score->setText(QString::number(score));

    if (score<0) // Проверка на нехватку отчков
    {
        ui->lineEdit_score->setText("");

        QMessageBox::warning(this, "ВНИМАНИЕ", "У вас не хватает очков!");

        ui->lineEdit_luck->setText("");
        ui->lineEdit_mind->setText("");
        ui->lineEdit_agility->setText("");
        ui->lineEdit_power->setText("");
    }
}

void MainWindow::on_pushButton_enter_clicked()
{
    int p=0, a=0, m=0, l=0; // Переменные значений
    double score=20;
    bool flagP, flagA, flagM, flagL, flagS; // Переменные проверки
    QString value, name, hero; // Поле ввода

    name=ui->lineEdit_name->text(); // Обработка значения имени

    value=ui->lineEdit_power->text(); // Обработка значения силы
    p=value.toInt(&flagP);

    value=ui->lineEdit_agility->text(); // Обработка значения ловкости
    a=value.toInt(&flagA);

    value=ui->lineEdit_mind->text(); // Обработка значения интеллекта
    m=value.toInt(&flagM);

    value=ui->lineEdit_luck->text(); // Обработка значения удачи
    l=value.toInt(&flagL);

    value=ui->lineEdit_score->text(); // Обработка значения очков характеристик
    score=value.toDouble(&flagS);

    if  (ui->radioButton_male->isChecked()) // Определение класса героя
    {
        if ((p & a & l & m) == 10)
            hero="Богом";
        else if ((p <= 5) && ((p > a) && (p > m) && (p > l)))
            hero="Войном";
        else if ((p > a) && (p > m) && (p > l))
            hero="Орком";
        else if ((a <= 5) && ((a > p) && (a > m) && (a > l)))
            hero="Разбойником";
        else if ((a > p) && (a > m) && (a > l))
            hero="Алхимиком";
        else if ((m <= 5) && ((m > a) && (m > p) && (m > l)))
            hero="Жрецом";
        else if ((m > a) && (m > p) && (m > l))
            hero="Магом";
        else if ((l <= 5) && ((l > a) && (l > m) && (l > p)))
            hero="Вором";
        else if ((l > a) && (l > m) && (l > p))
            hero="Лучником";
        else if ((p == a) || (p == m) || (p == l))
            hero="Паладином";
        else if ((a == p) || (a == m) || (a == l))
            hero="Легионером";
        else if ((m == a) || (m == p) || (m == l))
            hero="Эльфом";
        else if ((l == a) || (l == m) || (l == p))
            hero="Колдуном";
    }

    if  (ui->radioButton_female->isChecked()) // Определения класса героини
    {
        if ((p & a & l & m) == 10)
            hero="Богиней";
        else if ((p <= 5) && ((p > a) && (p > m) && (p > l)))
            hero="Воительницей";
        else if ((p > a) && (p > m) && (p > l))
            hero="Великаншей";
        else if ((a <= 5) && ((a > p) && (a > m) && (a > l)))
            hero="Расхитительницей";
        else if ((a > p) && (a > m) && (a > l))
            hero="Лекарем";
        else if ((m <= 5) && ((m > a) && (m > p) && (m > l)))
            hero="Ведьмой";
        else if ((m > a) && (m > p) && (m > l))
            hero="Чародейкой";
        else if ((l <= 5) && ((l > a) && (l > m) && (l > p)))
            hero="Феей";
        else if ((l > a) && (l > m) && (l > p))
            hero="Лучницей";
        else if ((p == a) || (p == m) || (p == l))
            hero="Валькирией";
        else if ((a == p) || (a == m) || (a == l))
            hero="Лучницей";
        else if ((m == a) || (m == p) || (m == l))
            hero="Эльфийкой";
        else if ((l == a) || (l == m) || (l == p))
            hero="Жрицей";
    }

    if (ui->lineEdit_name->text()=="") // Проверка на пустое имя
    {
        QMessageBox::warning(this, "ВНИМАНИЕ", "Введите имя героя!");
    }
    else
    {
        if ((ui->radioButton_male->isChecked()) || (ui->radioButton_female->isChecked()))
        {
            if (p > 10 || a > 10 || m > 10 || l > 10) // Проверка значений вышедших из диапозона
            {
                QMessageBox::warning(this, "ВНИМАНИЕ", "Введите значение от 1 до 10!");
            }
            else if (p < 1 || a < 1 || m < 1 || l < 1) // Проверка значений не вошедших в диапозон
            {
                QMessageBox::warning(this, "ВНИМАНИЕ", "Введите значение от 1 до 10!");
            }
            else
            {
                if (score>0)
                {
                    QMessageBox::warning(this, "ВНИМАНИЕ", "Используйте все очки!");
                }
                else
                {

                    if (flagP) // Проверка значения силы
                    {
                        value.clear();
                        value.append(ui->lineEdit_power->text());
                        p=value.toInt(&flagP);

                        if (p < 1 || p > 10) // Проверка количества силы
                            ui->label_power->setStyleSheet("color: white;");
                        else if (p == 5 || p == 6)
                            ui->label_power->setStyleSheet("color: orange;");
                        else if (p <= 4)
                            ui->label_power->setStyleSheet("color: red;");
                        else if (p >= 7)
                            ui->label_power->setStyleSheet("color: green;");

                        if (flagA) // Проверка значения ловкости
                        {
                            value.clear();
                            value.append(ui->lineEdit_agility->text());
                            a=value.toInt(&flagA);

                            if (a == 0 || a > 10) // Проверка количества ловкости
                                ui->label_agility->setStyleSheet("color: white;");
                            else if (a == 5 || a == 6)
                                ui->label_agility->setStyleSheet("color: orange;");
                            else if (a <= 4)
                                ui->label_agility->setStyleSheet("color: red;");
                            else if (a >= 7)
                                ui->label_agility->setStyleSheet("color: green;");

                            if (flagM) // Проверка значения интеллекта
                            {
                                value.clear();
                                value.append(ui->lineEdit_mind->text());
                                p=value.toInt(&flagM);

                                if (m == 0 || m > 10) // Проверка количества интеллекта
                                    ui->label_mind->setStyleSheet("color: white;");
                                else if (m == 5 || m == 6)
                                    ui->label_mind->setStyleSheet("color: orange;");
                                else if (m <= 4)
                                    ui->label_mind->setStyleSheet("color: red;");
                                else if (m >= 7)
                                    ui->label_mind->setStyleSheet("color: green;");

                                if (flagL) // Проверка значения удачи
                                {
                                    value.clear();
                                    value.append(ui->lineEdit_luck->text());
                                    p=value.toInt(&flagL);

                                    if (l == 0 || l > 10) // Проверка количества удачи
                                        ui->label_luck->setStyleSheet("color: white;");
                                    else if (l == 5 || l == 6)
                                        ui->label_luck->setStyleSheet("color: orange;");
                                    else if (l <= 4)
                                        ui->label_luck->setStyleSheet("color: red;");
                                    else if (l >= 7)
                                        ui->label_luck->setStyleSheet("color: green;");

                                    double hp = .8 * p + .2 * a; // Формула значения переменной жизни
                                    double mp = .8 * m + .15 * l + .85 * a; // Формула значения переменной маны
                                    double at = .5 * p + .2 * l + .3 * a; // Формула значения переменной атаки
                                    double def = .7 * p + .25 * l + .05 * a; // Формула значения переменной защиты

                                    ui->lineEdit_hp->setText(QString::number(hp)); // Вывод значения жизни
                                    ui->lineEdit_mp->setText(QString::number(mp)); // Вывод значения маны
                                    ui->lineEdit_attack->setText(QString::number(at)); // Вывод значения атаки
                                    ui->lineEdit_defence->setText(QString::number(def)); // Вывод значения защиты

                                    ui->label_congr->setText("Поздравляю вас " + name); // Вывод поздравления
                                    ui->label_hero->setText("Вы избраны стать - " + hero); // Вывод класса героя
                                    ui->label_congr->setVisible(true);
                                    ui->label_hero->setVisible(true);
                                }
                                else
                                {
                                    QMessageBox::warning(this, "ВНИМАНИЕ", "Введите значение удачи!");
                                }
                            }
                            else
                            {
                                QMessageBox::warning(this, "ВНИМАНИЕ", "Введите значение интеллекта!");
                            }
                        }
                        else
                        {
                            QMessageBox::warning(this, "ВНИМАНИЕ", "Введите значение ловкости!");
                        }
                    }
                    else
                    {
                        QMessageBox::warning(this, "ВНИМАНИЕ", "Введите значение силы!");
                    }
                }
            }
        }
        else
        {
            QMessageBox::warning(this, "ВНИМАНИЕ", "Выберите пол!");
        }
    }
}

void MainWindow::on_pushButton_cancel_clicked()
{
    ui->label_power->setStyleSheet("color: white;");
    ui->label_agility->setStyleSheet("color: white;");
    ui->label_mind->setStyleSheet("color: white;");
    ui->label_luck->setStyleSheet("color: white;");
    ui->lineEdit_name->setText("");
    ui->lineEdit_power->setText("");
    ui->lineEdit_agility->setText("");
    ui->lineEdit_mind->setText("");
    ui->lineEdit_luck->setText("");
    ui->lineEdit_hp->setText("");
    ui->lineEdit_mp->setText("");
    ui->lineEdit_attack->setText("");
    ui->lineEdit_defence->setText("");
    ui->label_congr->setText("");
    ui->label_hero->setText("");
    ui->radioButton_male->setChecked(false);
    ui->radioButton_female->setChecked(false);
}

void MainWindow::on_lineEdit_name_textChanged(const QString &arg1)
{
    QString str=arg1.trimmed();
    ui->lineEdit_name->setText(str);
}
