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

    int mainArray(int arr[], int size);

    bool bogoSortSorted(int *arr, int size);

    void bogoSortShuffle(int *arr, int size, int &k);

    int bogoSort(int arr[], int size, int &k);

    int quickSort(int *arr, int size);

    void deleteDub (int *arr, int &size);

    void outputArray(int arr[], int size);

    void linearSearch(int *arr, int size, int k, int &n, QString &arrStr);

    int binarySearch(int *arr, int size, int k);

    void hideMessege();

    void showMessege();

    void intError(int idCol, int size);

    void nullError(int idCol, int size);

    void on_pushButton_enter_clicked();

    void on_pushButton_random_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_min_clicked();

    void on_pushButton_avg_clicked();

    void on_pushButton_bubbleSort_clicked();

    void on_pushButton_quickSort_clicked();

    void on_pushButton_combSort_clicked();

    void on_pushButton_gnomeSort_clicked();

    void on_pushButton_bogoSort_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_search_clicked();

    void on_tableWidget_itemChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
