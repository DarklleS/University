#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_comboBox_op1_currentIndexChanged(int index);

    void on_comboBox_comp_currentIndexChanged(int index);

    void on_comboBox_op2_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    void changecolor(int res);
};
#endif // MAINWINDOW_H
