#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>

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
    void on_score();

    void on_pushButton_enter_clicked();

    void on_pushButton_cancel_clicked();

    void on_lineEdit_name_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QDoubleValidator numValidator;
};
#endif // MAINWINDOW_H
