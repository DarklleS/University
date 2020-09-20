#include <iostream>
#include <ctime>

using namespace std;

int* searchZero(int** matrix, int n, int m) // Функция поиска строк с нулевыми элементами
{
    int* res = new int[n];
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            if (matrix[i][j] == 0)
                count++;

        res[i] = count;
        count = 0;
    }
    return res;
}

int** deleteZero(int** matrix, int n, int m, int* search) // Функция удаление строк с нулевыми элементами
{
    int** res = new int* [n];

    for (int i = 0; i < n; i++)
        res[i] = new int[m];

    for (int i = 0; i < n; i++)
    {
        if (search[i] == 0)
        { 
            cout << "| ";
            for (int j = 0; j < m; j++)
            {
                res[i][j] = matrix[i][j]; 
                cout << res[i][j] << " ";
            }
            cout << "|" << endl;
        }
    }
    return res;
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(0));

    int n = 0;
    int m = 0;

    cout << "Введите количество строк матрицы: ";
    cin >> n;

    if (cin.fail() || n < 1) // Проверка на ввод корректных значений строк матрицы
    {
        cout << "Ошибка: Введенно некорректное значение кол-ва строк матрицы!";
        return 0;
    }
    else
    {
        cout << "Введите количество столбцов матрицы: ";
        cin >> m;

        if (cin.fail() || m < 1) // Проверка на ввод корректных значений столбцов матрицы
        {
            cout << "Ошибка: Введенно некорректное значение кол-ва столбцов матрицы!";
            return 0;
        }
    }    

    cout << endl << "---------------------------------------" << endl;

    int** matrix = new int* [n]; // Выделение памяти под массив

    for (int i = 0; i < n; i++)
        matrix[i] = new int[m];

    for (int i = 0; i < n; i++) // Генерация случайных чисел ячеек матрицы
        for (int j = 0; j < m; j++)
            matrix[i][j] = rand() % 6;

    cout << "\nМатрица входа:\n" << endl;

    for (int i = 0; i < n; i++) // Вывод матрицы входа
    {
        cout << "| ";

        for (int j = 0; j < m; j++)
            cout << matrix[i][j] << " ";

        cout << "|" << endl;
    }

    int* search = searchZero(matrix, n, m);

    cout << endl << "---------------------------------------" << endl;

    cout <<  "\nМатрица выхода:\n" << endl;

    int** res = deleteZero(matrix, n, m, search); // Вывод матрицы выхода

    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
        delete[] res[i];
    }

    delete[] matrix;
    delete[] res;
    delete[] search;
}

