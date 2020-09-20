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

    ui->lineEdit_power->setValidator(&numValidator); // Приcваивание защиты полю силы
    ui->lineEdit_agility->setValidator(&numValidator); // Приcваивание защиты полю ловкости
    ui->lineEdit_mind->setValidator(&numValidator); // Приcваивание защиты полю интеллекта
    ui->lineEdit_luck->setValidator(&numValidator); // Приcваивание защиты полю удачи

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
    ui->lineEdit_hp->setAlignment(Qt::AlignCenter);
    ui->lineEdit_mp->setAlignment(Qt::AlignCenter);
    ui->lineEdit_attack->setAlignment(Qt::AlignCenter);
    ui->lineEdit_defence->setAlignment(Qt::AlignCenter);
    ui->lineEdit_power->setAlignment(Qt::AlignCenter);
    ui->lineEdit_agility->setAlignment(Qt::AlignCenter);
    ui->lineEdit_luck->setAlignment(Qt::AlignCenter);
    ui->lineEdit_mind->setAlignment(Qt::AlignCenter);
    ui->label_message->setAlignment(Qt::AlignCenter);
    ui->label_lim->setAlignment(Qt::AlignCenter);

    ui->radioButton_cancel->setVisible(false);
    ui->label_congr->setVisible(false);
    ui->label_hero->setVisible(false);
    ui->label_lim->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_score() // Функция работы очков характеристик
{
    int score = 20; // Переменная очков характеристик
    score = score - (ui->lineEdit_power->text().toInt() + ui->lineEdit_agility->text().toInt() + ui->lineEdit_mind->text().toInt() + ui->lineEdit_luck->text().toInt());
    ui->lineEdit_score->setText(QString::number(score));

    if (score<0) // Проверка на количество очков
    {
        int unscore = abs(score);
        ui->lineEdit_score->setText("!");
        ui->lineEdit_score->setStyleSheet("border-radius: 40px; border: 1px solid red; color: white; background-color: #333;");
        ui->label_score->setStyleSheet("color: red;");
        ui->label_lim->setText("Перебор на " + QString::number(unscore));
        ui->label_lim->setStyleSheet("background-color: red; border-radius: 10px; color: white;");
        ui->label_lim->setVisible(true);

        if (ui->lineEdit_power->text()=="")
        {
            ui->label_power->setStyleSheet("color: white");
            ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }
        if (ui->lineEdit_agility->text()=="")
        {
            ui->label_agility->setStyleSheet("color: white");
            ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }
        if (ui->lineEdit_mind->text()=="")
        {
            ui->label_mind->setStyleSheet("color: white");
            ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }
        if (ui->lineEdit_luck->text()=="")
        {
            ui->label_luck->setStyleSheet("color: white");
            ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }
    }
    else if ((ui->lineEdit_power->text()!="" && ui->lineEdit_agility->text()!="" && ui->lineEdit_mind->text()!="" && ui->lineEdit_luck->text()!="") && score > 0) // Проверка на неиспользованные очки
    {
        ui->lineEdit_score->setStyleSheet("border-radius: 40px; border: 1px solid orange; color: white; background-color: #333;");
        ui->label_score->setStyleSheet("color: orange;");
        ui->label_lim->setVisible(false);
    }
    else if ((ui->lineEdit_power->text()=="" || ui->lineEdit_agility->text()=="" || ui->lineEdit_mind->text()=="" || ui->lineEdit_luck->text()=="") && score == 0) // Проверка на нехватку очков
    {
        ui->lineEdit_score->setStyleSheet("border-radius: 40px; border: 1px solid orange; color: white; background-color: #333;");
        ui->label_score->setStyleSheet("color: orange;");
        ui->label_lim->setVisible(false);

        if (ui->lineEdit_power->text()=="")
        {
            ui->label_power->setStyleSheet("color: orange");
            ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid orange; background-color: #333;");
        }
        if (ui->lineEdit_agility->text()=="")
        {
            ui->label_agility->setStyleSheet("color: orange");
            ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid orange; background-color: #333;");
        }
        if (ui->lineEdit_mind->text()=="")
        {
            ui->label_mind->setStyleSheet("color: orange");
            ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid orange; background-color: #333;");
        }
        if (ui->lineEdit_luck->text()=="")
        {
            ui->label_luck->setStyleSheet("color: orange");
            ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid orange; background-color: #333;");
        }
    }
    else if (score==0) // Проверка на все использованные очки
    {
        ui->lineEdit_score->setText("✔");
        ui->lineEdit_score->setStyleSheet("border-radius: 40px; border: 1px solid green; background-color: #333;");
        ui->label_score->setStyleSheet("color: green;");
        ui->label_lim->setVisible(false);

        if (ui->lineEdit_power->text()=="")
        {
            ui->label_power->setStyleSheet("color: white");
            ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }
        if (ui->lineEdit_agility->text()=="")
        {
            ui->label_agility->setStyleSheet("color: white");
            ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }
        if (ui->lineEdit_mind->text()=="")
        {
            ui->label_mind->setStyleSheet("color: white");
            ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }
        if (ui->lineEdit_luck->text()=="")
        {
            ui->label_luck->setStyleSheet("color: white");
            ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }
    }
    else
    {
        ui->lineEdit_score->setStyleSheet("border-radius: 40px; border: 1px solid #444; color: white; background-color: #333;");
        ui->label_score->setStyleSheet("color: white;");
        ui->label_lim->setVisible(false);
        if (ui->lineEdit_power->text()=="")
        {
            ui->label_power->setStyleSheet("color: white");
            ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }
        if (ui->lineEdit_agility->text()=="")
        {
            ui->label_agility->setStyleSheet("color: white");
            ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }

        if (ui->lineEdit_mind->text()=="")
        {
            ui->label_mind->setStyleSheet("color: white");
            ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }
        if (ui->lineEdit_luck->text()=="")
        {
            ui->label_luck->setStyleSheet("color: white");
            ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
        }
    }
}

void MainWindow::on_pushButton_enter_clicked()
{
    int p=0, a=0, m=0, l=0; // Переменные значений
    int score = 20; // Переменная очков характеристик
    bool flagP, flagA, flagM, flagL, flagS; // Переменные проверки
    QString value, name, hero; // Поле ввода

    score = score - (ui->lineEdit_power->text().toInt() + ui->lineEdit_agility->text().toInt() + ui->lineEdit_mind->text().toInt() + ui->lineEdit_luck->text().toInt());
    ui->lineEdit_score->setText(QString::number(score));

    name=ui->lineEdit_name->text(); // Обработка значения имени

    int size = name.length(); // Переменная длины имени

    value=ui->lineEdit_power->text(); // Обработка значения силы
    p=value.toInt(&flagP);

    value=ui->lineEdit_agility->text(); // Обработка значения ловкости
    a=value.toInt(&flagA);

    value=ui->lineEdit_mind->text(); // Обработка значения интеллекта
    m=value.toInt(&flagM);

    value=ui->lineEdit_luck->text(); // Обработка значения удачи
    l=value.toInt(&flagL);

    value=ui->lineEdit_score->text(); // Обработка значения очков характеристик
    score=value.toInt(&flagS);

    if (score<0)
    {
        ui->lineEdit_score->setText("!");
    }

    if (ui->lineEdit_name->text()=="")
    {
        ui->label_name->setStyleSheet("background-color: red; color: white; border-radius: 10px");
        ui->lineEdit_name->setStyleSheet("padding-left: 5px; border-radius: 10px; border: 1px solid red; background-color: #333;");
    }

    if (ui->radioButton_male->isChecked() == ui->radioButton_female->isChecked())
    {
        ui->label_gender->setStyleSheet("background-color: red; color: white; border-radius: 10px");
    }

    if (ui->lineEdit_power->text()=="")
    {
        ui->label_power->setStyleSheet("background-color: red; color: white; border-radius: 10px");
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid red; background-color: #333;");
    }
    if (ui->lineEdit_agility->text()=="")
    {
        ui->label_agility->setStyleSheet("background-color: red; color: white; border-radius: 10px");
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid red; background-color: #333;");
    }
    if (ui->lineEdit_mind->text()=="")
    {
        ui->label_mind->setStyleSheet("background-color: red; color: white; border-radius: 10px");
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid red; background-color: #333;");
    }
    if (ui->lineEdit_luck->text()=="")
    {
        ui->label_luck->setStyleSheet("background-color: red; color: white; border-radius: 10px");
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid red; background-color: #333;");
    }

    if  (ui->radioButton_male->isChecked()) // Определение класса героя
    {
        if (p == 5 && a == 5 && m == 5 && l == 5)
            hero = "Охотник";
        else if ((p > a) && (p > m) && (p > l))
            hero = "Воином";
        else if ((a > p) && (a > m) && (a > l))
            hero = "Друидом";
        else if ((m > a) && (m > p) && (m > l))
            hero = "Магом";
        else if ((l > a) && (l > m) && (l > p))
            hero = "Иллюзианистом";
        else if ((p == a && p > l) || (p == a == m))
            hero = "Паладином";
        else if ((p == m && p > a) || (p == l == m))
            hero = "Лучником";
        else if ((p == l && p > m) || (p == l == a))
            hero = "Монахом";
        else if ((a == m && a > l) || (a == m == l))
            hero = "Целителем";
        else if (a == l && a > m)
            hero = "Вором";
        else if (m == l && m > p)
            hero = "Провидцем";
    }

    if  (ui->radioButton_female->isChecked()) // Определения класса героини
    {
        if (p == 5 && a == 5 && m == 5 && l == 5)
            hero = "Охотница";
        else if ((p > a) && (p > m) && (p > l))
            hero = "Воительницей";
        else if ((a > p) && (a > m) && (a > l))
            hero = "Охотницей";
        else if ((m > a) && (m > p) && (m > l))
            hero = "Чародейкой";
        else if ((l > a) && (l > m) && (l > p))
            hero = "Иллюзианисткой";
        else if ((p == a && p > l) || (p == a == m))
            hero = "Валькирией";
        else if ((p == m && p > a) || (p == l == m))
            hero = "Лучницей";
        else if ((p == l && p > m) || (p == l == a))
            hero = "Монахиней";
        else if ((a == m && a > p) || (a == m == l))
            hero = "Целительницей";
        else if (a == l && a > p)
            hero = "Воровка";
        else if (m == l && m > p)
            hero = "Ясновидящей";
    }

    if (ui->lineEdit_name->text()=="") // Проверка на пустое имя
    {
        ui->label_message->setText("Проверьте верность введенных данных!");
        QMessageBox::warning(this, "ВНИМАНИЕ", "Введите имя героя!");
    }
    else if (size<=3) // Проверка на длину имени
    {
        ui->label_message->setText("Проверьте верность введенных данных!");
        QMessageBox::warning(this, "ВНИМАНИЕ", "Имя должно иметь больше 3 символов!");

    }
    else
    {
        if ((ui->radioButton_male->isChecked()) || (ui->radioButton_female->isChecked()))
        {
            if (score>0)
            {
                ui->label_message->setText("Проверьте верность введенных данных!");
                QMessageBox::warning(this, "ВНИМАНИЕ", "Используйте все очки!");
            }
            else if (score<0)
            {
                ui->lineEdit_score->setText("!");
                ui->lineEdit_score->setStyleSheet("border-radius: 40px; border: 1px solid red; background-color: #333;");
                ui->label_message->setText("Проверьте верность введенных данных!");
                QMessageBox::warning(this, "ВНИМАНИЕ", "У вас не хватает очков!");
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
                    else if (p == 4 || p == 5 || p == 6)
                    {
                        ui->label_power->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
                        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid orange; background-color: #333;");
                    }
                    else if (p <= 3)
                    {
                        ui->label_power->setStyleSheet("background-color: red; color: white; border-radius: 10px");
                        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid red; background-color: #333;");
                    }
                    else if (p >= 7)
                    {
                        ui->label_power->setStyleSheet("background-color: green; color: white; border-radius: 10px");
                        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
                    }

                    if (flagA) // Проверка значения ловкости
                    {
                        value.clear();
                        value.append(ui->lineEdit_agility->text());
                        a=value.toInt(&flagA);

                        if (a == 0 || a > 10) // Проверка количества ловкости
                            ui->label_agility->setStyleSheet("color: white;");
                        else if (a == 4 || a == 5 || a == 6)
                        {
                            ui->label_agility->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
                            ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid orange; background-color: #333;");
                        }
                        else if (a <= 3)
                        {
                            ui->label_agility->setStyleSheet("background-color: red; color: white; border-radius: 10px");
                            ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid red; background-color: #333;");

                        }
                        else if (a >= 7)
                        {
                            ui->label_agility->setStyleSheet("background-color: green; color: white; border-radius: 10px");
                            ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
                        }


                        if (flagM) // Проверка значения интеллекта
                        {
                            value.clear();
                            value.append(ui->lineEdit_mind->text());
                            m=value.toInt(&flagM);

                            if (m == 0 || m > 10) // Проверка количества интеллекта
                                ui->label_mind->setStyleSheet("color: white;");
                            else if (m == 4 || m == 5 || m == 6)
                            {
                                ui->label_mind->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
                                ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid orange; background-color: #333;");
                            }
                            else if (m <= 3)
                            {
                                ui->label_mind->setStyleSheet("background-color: red; color: white; border-radius: 10px");
                                ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid red; background-color: #333;");
                            }
                            else if (m >= 7)
                            {
                                ui->label_mind->setStyleSheet("background-color: green; color: white; border-radius: 10px");
                                ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
                            }
                            if (flagL) // Проверка значения удачи
                            {
                                value.clear();
                                value.append(ui->lineEdit_luck->text());
                                l=value.toInt(&flagL);

                                if (l == 0 || l > 10) // Проверка количества удачи
                                    ui->label_luck->setStyleSheet("color: white;");
                                else if (l == 4 || l == 5 || l == 6)
                                {
                                    ui->label_luck->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
                                    ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid orange; background-color: #333;");
                                }
                                else if (l < 4)
                                {
                                    ui->label_luck->setStyleSheet("background-color: red; color: white; border-radius: 10px");
                                    ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid red; background-color: #333;");
                                }
                                else if (l > 6)
                                {
                                    ui->label_luck->setStyleSheet("background-color: green; color: white; border-radius: 10px");
                                    ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
                                }

                                if ((ui->lineEdit_power->text()!="" && ui->lineEdit_agility->text()!="" && ui->lineEdit_mind->text()!="" && ui->lineEdit_luck->text()!="") && score == 0)
                                {
                                    ui->lineEdit_score->setText("✔");
                                    ui->lineEdit_score->setStyleSheet("border-radius: 40px; border: 1px solid green; background-color: #333;");
                                }

                                double hp = .7 * l + .2 * p + .1 * a; // Формула значения переменной жизни
                                double mp = .7 * m + .2 * l + .1 * p; // Формула значения переменной маны
                                double at = .7 * p + .2 * a + .1 * m; // Формула значения переменной атаки
                                double def = .7 * a + .2 * m + .1 * l; // Формула значения переменной защиты

                                if ((hp >= 4) && (hp <= 7))
                                {
                                    ui->label_hp->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
                                    ui->lineEdit_hp->setStyleSheet("border-radius: 15px; border: 1px solid orange; background-color: #333;");
                                }
                                else if (hp < 4)
                                {
                                    ui->label_hp->setStyleSheet("background-color: red; color: white; border-radius: 10px");
                                    ui->lineEdit_hp->setStyleSheet("border-radius: 15px; border: 1px solid red; background-color: #333;");
                                }
                                else if (hp > 7)
                                {
                                    ui->label_hp->setStyleSheet("background-color: green; color: white; border-radius: 10px");
                                    ui->lineEdit_hp->setStyleSheet("border-radius: 15px; border: 1px solid green; background-color: #333;");
                                }

                                if ((mp >= 4) && (mp <= 7))
                                {
                                    ui->label_mp->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
                                    ui->lineEdit_mp->setStyleSheet("border-radius: 15px; border: 1px solid orange; background-color: #333;");
                                }
                                else if (mp < 4)
                                {
                                    ui->label_mp->setStyleSheet("background-color: red; color: white; border-radius: 10px");
                                    ui->lineEdit_mp->setStyleSheet("border-radius: 15px; border: 1px solid red; background-color: #333;");
                                }
                                else if (mp > 7)
                                {
                                    ui->label_mp->setStyleSheet("background-color: green; color: white; border-radius: 10px");
                                    ui->lineEdit_mp->setStyleSheet("border-radius: 15px; border: 1px solid green; background-color: #333;");
                                }

                                if ((def >= 4) && (def <= 7))
                                {
                                    ui->label_defence->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
                                    ui->lineEdit_defence->setStyleSheet("border-radius: 15px; border: 1px solid orange; background-color: #333;");
                                }
                                else if (def < 4)
                                {
                                    ui->label_defence->setStyleSheet("background-color: red; color: white; border-radius: 10px");
                                    ui->lineEdit_defence->setStyleSheet("border-radius: 15px; border: 1px solid red; background-color: #333;");
                                }
                                else if (def > 7)
                                {
                                    ui->label_defence->setStyleSheet("background-color: green; color: white; border-radius: 10px");
                                    ui->lineEdit_defence->setStyleSheet("border-radius: 15px; border: 1px solid green; background-color: #333;");
                                }

                                if ((at >= 4) && (at <= 7))
                                {
                                    ui->label_attack->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
                                    ui->lineEdit_attack->setStyleSheet("border-radius: 15px; border: 1px solid orange; background-color: #333;");
                                }
                                else if (at < 4)
                                {
                                    ui->label_attack->setStyleSheet("background-color: red; color: white; border-radius: 10px");
                                    ui->lineEdit_attack->setStyleSheet("border-radius: 15px; border: 1px solid red; background-color: #333;");
                                }
                                else if (at > 7)
                                {
                                    ui->label_attack->setStyleSheet("background-color: green; color: white; border-radius: 10px");
                                    ui->lineEdit_attack->setStyleSheet("border-radius: 15px; border: 1px solid green; background-color: #333;");
                                }

                                ui->lineEdit_hp->setText(QString::number(hp)); // Вывод значения жизни
                                ui->lineEdit_mp->setText(QString::number(mp)); // Вывод значения маны
                                ui->lineEdit_attack->setText(QString::number(at)); // Вывод значения атаки
                                ui->lineEdit_defence->setText(QString::number(def)); // Вывод значения защиты

                                ui->label_message->setText("Добро пожаловать, странник!");
                                ui->label_congr->setText("Поздравляю вас " + name); // Вывод поздравления
                                ui->label_hero->setText("Вы избраны стать - " + hero); // Вывод класса героя
                                ui->label_congr->setVisible(true);
                                ui->label_hero->setVisible(true);
                            }
                            else
                            {
                                ui->label_message->setText("Проверьте верность введенных данных!");
                                QMessageBox::warning(this, "ВНИМАНИЕ", "Введите значение удачи!");
                            }
                        }
                        else
                        {
                            ui->label_message->setText("Проверьте верность введенных данных!");
                            QMessageBox::warning(this, "ВНИМАНИЕ", "Введите значение интеллекта!");
                        }
                    }
                    else
                    {
                        ui->label_message->setText("Проверьте верность введенных данных!");
                        QMessageBox::warning(this, "ВНИМАНИЕ", "Введите значение ловкости!");
                    }
                }
                else
                {
                    ui->label_message->setText("Проверьте верность введенных данных!");
                    QMessageBox::warning(this, "ВНИМАНИЕ", "Введите значение силы!");
                }
            }
        }
        else
        {
            ui->label_message->setText("Проверьте верность введенных данных!");
            QMessageBox::warning(this, "ВНИМАНИЕ", "Выберите пол!");
        }
    }
}

void MainWindow::on_pushButton_cancel_clicked() // Функция отмены
{
    ui->radioButton_cancel->setChecked(true);
    ui->label_lim->setVisible(false);
    ui->label_power->setStyleSheet("color: white;");
    ui->label_agility->setStyleSheet("color: white;");
    ui->label_mind->setStyleSheet("color: white;");
    ui->label_luck->setStyleSheet("color: white;");
    ui->label_hp->setStyleSheet("color: white;");
    ui->label_mp->setStyleSheet("color: white;");
    ui->label_defence->setStyleSheet("color: white;");
    ui->label_attack->setStyleSheet("color: white;");
    ui->label_score->setStyleSheet("color: white;");
    ui->label_gender->setStyleSheet("color: white;");
    ui->label_name->setStyleSheet("color: white;");
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
    ui->lineEdit_name->setStyleSheet("padding-left: 5px; border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    ui->lineEdit_hp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_mp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_attack->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_defence->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_score->setStyleSheet("border-radius: 40px; border: 1px solid #444; background-color: #333;");
    ui->label_message->setText("Введите данные о своем герое!");
}

void MainWindow::on_lineEdit_name_textChanged(const QString &arg1) // Функция смены значения поля ввода имени
{
    QString name=arg1.trimmed();
    ui->lineEdit_name->setText(name);

    int size = name.length();

    ui->label_message->setText("Введите данные о своем герое!");

    if (size == 0)
    {
        ui->label_name->setStyleSheet("color: white");
        ui->lineEdit_name->setStyleSheet("padding-left: 5px; border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }
    else if (size <=3)
    {
        ui->label_name->setStyleSheet("background-color: red; color: white; border-radius: 10px");
        ui->lineEdit_name->setStyleSheet("padding-left: 5px; border-radius: 10px; border: 1px solid red; background-color: #333; color: red;");
    }
    else
    {
        ui->label_name->setStyleSheet("background-color: green; color: white; border-radius: 10px");
        ui->lineEdit_name->setStyleSheet("padding-left: 5px; border-radius: 10px; border: 1px solid green; background-color: #333; color: white");
    }

    if (ui->lineEdit_power->text()!="")
    {
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_power->setStyleSheet("color: white;");
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_luck->text()!="")
    {
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_luck->setStyleSheet("color: white;");
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_mind->text()!="")
    {
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_mind->setStyleSheet("color: white;");
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_agility->text()!="")
    {
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_agility->setStyleSheet("color: white;");
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->radioButton_male->isChecked() == ui->radioButton_female->isChecked())
    {
        ui->label_gender->setStyleSheet("color: white;");
        ui->radioButton_male->setStyleSheet("color: white;");
        ui->radioButton_female->setStyleSheet("color: white;");
    }
    else
    {
        ui->label_gender->setStyleSheet("background-color: green; color: white; border-radius: 10px");
    }

    ui->lineEdit_attack->setText("");
    ui->label_attack->setStyleSheet("color: white;");
    ui->lineEdit_defence->setText("");
    ui->label_defence->setStyleSheet("color: white;");
    ui->lineEdit_hp->setText("");
    ui->label_hp->setStyleSheet("color: white;");
    ui->lineEdit_mp->setText("");
    ui->label_mp->setStyleSheet("color: white;");
    ui->label_congr->setVisible(false);
    ui->label_hero->setVisible(false);
    ui->lineEdit_hp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_mp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_attack->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_defence->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
}

void MainWindow::on_lineEdit_power_textChanged(const QString &arg1) // Функция смены значения поля ввода силы
{
    int p=0; // Переменные значений
    QString value=arg1; // Поле ввода

    value=ui->lineEdit_power->text(); // Обработка значения силы
    p=value.toInt();

    ui->label_message->setText("Введите данные о своем герое!");

    if (p>10)
        ui->lineEdit_power->setText("");

    if (ui->lineEdit_power->text() == "0")
        ui->lineEdit_power->setText("");

    if (ui->lineEdit_name->text() == "")
    {
        ui->label_name->setStyleSheet("color: white;");
        ui->lineEdit_name->setStyleSheet("padding-left: 5px; border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_power->text() == "") // Проверка количества силы
    {
        ui->label_power->setStyleSheet("color: white;");
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }
    else
    {
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }

    if (ui->lineEdit_luck->text()!="")
    {
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_luck->setStyleSheet("color: white;");
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_mind->text()!="")
    {
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_mind->setStyleSheet("color: white;");
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_agility->text()!="")
    {
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_agility->setStyleSheet("color: white;");
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->radioButton_male->isChecked() == ui->radioButton_female->isChecked())
    {
        ui->label_gender->setStyleSheet("color: white;");
        ui->radioButton_male->setStyleSheet("color: white;");
        ui->radioButton_female->setStyleSheet("color: white;");
    }
    else
    {
        ui->label_gender->setStyleSheet("background-color: green; color: white; border-radius: 10px");
    }

    if (p == 4 || p == 5 || p == 6)
        ui->label_power->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
    else if (p <= 3)
        ui->label_power->setStyleSheet("background-color: red; color: white; border-radius: 10px");
    else if (p >= 7)
        ui->label_power->setStyleSheet("background-color: green; color: white; border-radius: 10px");

    ui->lineEdit_attack->setText("");
    ui->label_attack->setStyleSheet("color: white;");
    ui->lineEdit_defence->setText("");
    ui->label_defence->setStyleSheet("color: white;");
    ui->lineEdit_hp->setText("");
    ui->label_hp->setStyleSheet("color: white;");
    ui->lineEdit_mp->setText("");
    ui->label_mp->setStyleSheet("color: white;");
    ui->label_congr->setVisible(false);
    ui->label_hero->setVisible(false);
    ui->lineEdit_hp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_mp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_attack->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_defence->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
}

void MainWindow::on_lineEdit_agility_textChanged(const QString &arg1) // Функция смены значения поля ввода ловкости
{
    int a=0; // Переменные значений
    QString value=arg1; // Поле ввода

    value=ui->lineEdit_agility->text(); // Обработка значения силы
    a=value.toInt();

    ui->label_message->setText("Введите данные о своем герое!");

    if (a>10)
        ui->lineEdit_agility->setText("");

    if (ui->lineEdit_agility->text() == "0")
        ui->lineEdit_agility->setText("");

    if (ui->lineEdit_name->text() == "")
    {
        ui->label_name->setStyleSheet("color: white;");
        ui->lineEdit_name->setStyleSheet("padding-left: 5px; border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_agility->text() == "")
    {
        ui->label_agility->setStyleSheet("color: white;");
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }
    else
    {
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }

    if (ui->lineEdit_luck->text()!="")
    {
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_luck->setStyleSheet("color: white;");
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_mind->text()!="")
    {
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_mind->setStyleSheet("color: white;");
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_power->text()!="")
    {
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_power->setStyleSheet("color: white;");
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->radioButton_male->isChecked() == ui->radioButton_female->isChecked())
    {
        ui->label_gender->setStyleSheet("color: white;");
        ui->radioButton_male->setStyleSheet("color: white;");
        ui->radioButton_female->setStyleSheet("color: white;");
    }
    else
    {
        ui->label_gender->setStyleSheet("background-color: green; color: white; border-radius: 10px");
    }

    if (a == 4 || a == 5 || a == 6)
        ui->label_agility->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
    else if (a <= 3)
        ui->label_agility->setStyleSheet("background-color: red; color: white; border-radius: 10px");
    else if (a >= 7)
        ui->label_agility->setStyleSheet("background-color: green; color: white; border-radius: 10px");

    ui->lineEdit_attack->setText("");
    ui->label_attack->setStyleSheet("color: white;");
    ui->lineEdit_defence->setText("");
    ui->label_defence->setStyleSheet("color: white;");
    ui->lineEdit_hp->setText("");
    ui->label_hp->setStyleSheet("color: white;");
    ui->lineEdit_mp->setText("");
    ui->label_mp->setStyleSheet("color: white;");
    ui->label_congr->setVisible(false);
    ui->label_hero->setVisible(false);
    ui->lineEdit_hp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_mp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_attack->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_defence->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
}

void MainWindow::on_lineEdit_mind_textChanged(const QString &arg1) // Функция смены значения поля ввода интеллекта
{
    int m=0; // Переменные значений
    QString value=arg1; // Поле ввода

    value=ui->lineEdit_mind->text(); // Обработка значения силы
    m=value.toInt();

    ui->label_message->setText("Введите данные о своем герое!");

    if (m>10)
        ui->lineEdit_mind->setText("");

    if (ui->lineEdit_mind->text() == "0")
        ui->lineEdit_mind->setText("");

    if (ui->lineEdit_name->text() == "")
    {
        ui->label_name->setStyleSheet("color: white;");
        ui->lineEdit_name->setStyleSheet("padding-left: 5px; border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_mind->text() == "")
    {
        ui->label_mind->setStyleSheet("color: white;");
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }
    else
    {
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }

    if (ui->lineEdit_luck->text()!="")
    {
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_luck->setStyleSheet("color: white;");
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_agility->text()!="")
    {
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_agility->setStyleSheet("color: white;");
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_power->text()!="")
    {
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_power->setStyleSheet("color: white;");
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->radioButton_male->isChecked() == ui->radioButton_female->isChecked())
    {
        ui->label_gender->setStyleSheet("color: white;");
        ui->radioButton_male->setStyleSheet("color: white;");
        ui->radioButton_female->setStyleSheet("color: white;");
    }
    else
    {
        ui->label_gender->setStyleSheet("background-color: green; color: white; border-radius: 10px");
    }

    if (m == 4 || m == 5 || m == 6)
        ui->label_mind->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
    else if (m <= 3)
        ui->label_mind->setStyleSheet("background-color: red; color: white; border-radius: 10px");
    else if (m >= 7)
        ui->label_mind->setStyleSheet("background-color: green; color: white; border-radius: 10px");

    ui->lineEdit_attack->setText("");
    ui->label_attack->setStyleSheet("color: white;");
    ui->lineEdit_defence->setText("");
    ui->label_defence->setStyleSheet("color: white;");
    ui->lineEdit_hp->setText("");
    ui->label_hp->setStyleSheet("color: white;");
    ui->lineEdit_mp->setText("");
    ui->label_mp->setStyleSheet("color: white;");
    ui->label_congr->setVisible(false);
    ui->label_hero->setVisible(false);
    ui->lineEdit_hp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_mp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_attack->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_defence->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
}


void MainWindow::on_lineEdit_luck_textChanged(const QString &arg1) // Функция смены значения поля ввода удачи
{
    int l=0; // Переменные значений
    QString value=arg1; // Поле ввода

    value=ui->lineEdit_luck->text(); // Обработка значения силы
    l=value.toInt();

    ui->label_message->setText("Введите данные о своем герое!");

    if (l>10)
        ui->lineEdit_luck->setText("");

    if (ui->lineEdit_luck->text() == "0")
        ui->lineEdit_luck->setText("");

    if (ui->lineEdit_name->text() == "")
    {
        ui->label_name->setStyleSheet("color: white;");
        ui->lineEdit_name->setStyleSheet("padding-left: 5px; border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_luck->text() == "")
    {
        ui->label_luck->setStyleSheet("color: white;");
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }
    else
    {
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }

    if (ui->lineEdit_agility->text()!="")
    {
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_agility->setStyleSheet("color: white;");
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_mind->text()!="")
    {
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_mind->setStyleSheet("color: white;");
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_power->text()!="")
    {
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_power->setStyleSheet("color: white;");
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->radioButton_male->isChecked() == ui->radioButton_female->isChecked())
    {
        ui->label_gender->setStyleSheet("color: white;");
        ui->radioButton_male->setStyleSheet("color: white;");
        ui->radioButton_female->setStyleSheet("color: white;");
    }
    else
    {
        ui->label_gender->setStyleSheet("background-color: green; color: white; border-radius: 10px");
    }

    if (l == 4 || l == 5 || l == 6)
        ui->label_luck->setStyleSheet("background-color: orange; color: white; border-radius: 10px");
    else if (l <= 3)
        ui->label_luck->setStyleSheet("background-color: red; color: white; border-radius: 10px");
    else if (l >= 7)
        ui->label_luck->setStyleSheet("background-color: green; color: white; border-radius: 10px");

    ui->lineEdit_attack->setText("");
    ui->label_attack->setStyleSheet("color: white;");
    ui->lineEdit_defence->setText("");
    ui->label_defence->setStyleSheet("color: white;");
    ui->lineEdit_hp->setText("");
    ui->label_hp->setStyleSheet("color: white;");
    ui->lineEdit_mp->setText("");
    ui->label_mp->setStyleSheet("color: white;");
    ui->label_congr->setVisible(false);
    ui->label_hero->setVisible(false);
    ui->lineEdit_hp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_mp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_attack->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_defence->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
}

void MainWindow::on_radioButton_male_clicked() // Функция нажатия на радио м
{
    ui->label_gender->setStyleSheet("background-color: green; color: white; border-radius: 10px");

    ui->label_message->setText("Введите данные о своем герое!");

    if (ui->lineEdit_name->text() == "")
    {
        ui->label_name->setStyleSheet("color: white;");
        ui->lineEdit_name->setStyleSheet("padding-left: 5px; border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_power->text()!="")
    {
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_power->setStyleSheet("color: white;");
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_luck->text()!="")
    {
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_luck->setStyleSheet("color: white;");
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_mind->text()!="")
    {
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_mind->setStyleSheet("color: white;");
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_agility->text()!="")
    {
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_agility->setStyleSheet("color: white;");
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    ui->lineEdit_attack->setText("");
    ui->label_attack->setStyleSheet("color: white;");
    ui->lineEdit_defence->setText("");
    ui->label_defence->setStyleSheet("color: white;");
    ui->lineEdit_hp->setText("");
    ui->label_hp->setStyleSheet("color: white;");
    ui->lineEdit_mp->setText("");
    ui->label_mp->setStyleSheet("color: white;");
    ui->label_congr->setVisible(false);
    ui->label_hero->setVisible(false);
    ui->lineEdit_hp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_mp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_attack->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_defence->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
}

void MainWindow::on_radioButton_female_clicked() // Функция нажатия на радио ж
{
    ui->label_gender->setStyleSheet("background-color: green; color: white; border-radius: 10px");

    ui->label_message->setText("Введите данные о своем герое!");

    if (ui->lineEdit_name->text() == "")
    {
        ui->label_name->setStyleSheet("color: white;");
        ui->lineEdit_name->setStyleSheet("padding-left: 5px; border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_power->text()!="")
    {
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_power->setStyleSheet("color: white;");
        ui->lineEdit_power->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_luck->text()!="")
    {
        ui->lineEdit_luck->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_luck->setStyleSheet("color: white;");
        ui->lineEdit_luck->setStyleSheet("border-radius: 15px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_mind->text()!="")
    {
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_mind->setStyleSheet("color: white;");
        ui->lineEdit_mind->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    if (ui->lineEdit_agility->text()!="")
    {
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid green; background-color: #333;");
    }
    else
    {
        ui->label_agility->setStyleSheet("color: white;");
        ui->lineEdit_agility->setStyleSheet("border-radius: 10px; border: 1px solid #252525; background-color: #333;");
    }

    ui->lineEdit_attack->setText("");
    ui->label_attack->setStyleSheet("color: white;");
    ui->lineEdit_defence->setText("");
    ui->label_defence->setStyleSheet("color: white;");
    ui->lineEdit_hp->setText("");
    ui->label_hp->setStyleSheet("color: white;");
    ui->lineEdit_mp->setText("");
    ui->label_mp->setStyleSheet("color: white;");
    ui->label_congr->setVisible(false);
    ui->label_hero->setVisible(false);
    ui->lineEdit_hp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_mp->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_attack->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
    ui->lineEdit_defence->setStyleSheet("border-radius: 15px; border: 1px solid #444; background-color: #333;");
}
