#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class Image
{
public:
    Image(size_t size) : _size(size)
    {
        _rgbMatrix.resize(3, vector<vector<int>>(_size, vector<int>(_size)));
        _imageMatrix.resize(_size, vector<int>(_size));
        _convolutionMatrix.resize(_size, vector<int>(_size));

        for (size_t i = 0; i < 3; ++i)
        {
            for (size_t j = 0; j < _size; ++j)
            {
                for (size_t k = 0; k < _size; ++k)
                {
                    _rgbMatrix[i][j][k] = rand() % 256;

                    switch (i)
                    {
                    case(0):
                        _imageMatrix[j][k] += _rgbMatrix[i][j][k] * 0.3;
                        break;
                    case(1):
                        _imageMatrix[j][k] += _rgbMatrix[i][j][k] * 0.59;
                        break;
                    case(2):
                        _imageMatrix[j][k] += _rgbMatrix[i][j][k] * 0.11;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }

    void print()
    {
        for (size_t i = 0; i < 3; ++i)
        {
            switch (i)
            {
            case(0):
                cout << "---------------------------------------------------------------------------" << endl;
                cout << "RED:" << endl;
                cout << "---------------------------------------------------------------------------" << endl;
                break;
            case(1):
                cout << "---------------------------------------------------------------------------" << endl;
                cout << "GREEN:" << endl;
                cout << "---------------------------------------------------------------------------" << endl;
                break;
            case(2):
                cout << "---------------------------------------------------------------------------" << endl;
                cout << "BLUE:" << endl;
                cout << "---------------------------------------------------------------------------" << endl;
                break;
            default:
                break;
            }

            for (size_t j = 0; j < _size; ++j)
            {
                for (size_t k = 0; k < _size; ++k)
                {
                    cout << _rgbMatrix[i][j][k] << "\t";
                }
                cout << endl;
            }
        }

        cout << "IMAGE:" << endl;
        cout << "---------------------------------------------------------------------------" << endl;

        for (size_t i = 0; i < _size; ++i)
        {
            for (size_t j = 0; j < _size; ++j)
            {
                cout << _imageMatrix[i][j] << "\t";
            }

            cout << endl;
        }
    }

    vector<vector<int>> filter()
    {
        vector<vector<int>> filter =
        {
            {1, 0, -1},
            {2, 0, -2},
            {1, 0, -1}
        };
        vector<vector<int>> result(_size, vector<int>(_size));
        int count = 0;

        for (size_t shiftI = 0; shiftI < _size - 2; ++shiftI)
        {
            for (size_t shiftJ = 0; shiftJ < _size - 2; ++shiftJ)
            {
                for (size_t i = 0; i < 3; ++i)
                {
                    for (size_t j = 0; j < 3; ++j)
                    {
                        count += _imageMatrix[i + shiftI][j + shiftJ] * filter[i][j];
                    }
                }

                _overflow(result, shiftI + 1, shiftJ + 1, count);

                count = 0;
            }
        }

        cout << "CONVOLUTION:" << endl;
        cout << "---------------------------------------------------------------------------" << endl;

        for (size_t i = 0; i < _size; ++i)
        {
            for (size_t j = 0; j < _size; ++j)
            {
                cout << result[i][j] << "\t";
            }
            cout << endl;
        }

        _convolutionMatrix = result;

        return result;
    }

    vector<vector<int>> activation()
    {
        vector<vector<int>> result(_size, vector<int>(_size));

        cout << "ACTIVATION:" << endl;
        cout << "---------------------------------------------------------------------------" << endl;

        for (size_t i = 0; i < _size; ++i)
        {
            for (size_t j = 0; j < _size; ++j)
            {
                result[i][j] = _sigmoid(_convolutionMatrix[i][j]);
                cout << result[i][j] << "\t";
            }
            cout << endl;
        }

        _activationMatrix = result;

        return result;
    }

    vector<vector<int>> pooling()
    {
        vector<vector<int>> result(_size, vector<int>(_size));
        int count = 0;

        for (size_t shiftI = 0, countI = 0; shiftI < _size - 1; shiftI += 2, ++countI)
        {
            for (size_t shiftJ = 0, countJ = 0; shiftJ < _size - 1; shiftJ += 2, ++countJ)
            {
                for (size_t i = 0; i < 2; ++i)
                {
                    for (size_t j = 0; j < 2; ++j)
                    {
                        count += _activationMatrix[i + shiftI][j + shiftJ];
                    }
                }

                _overflow(result, countI + 2, countJ + 2, count /= 4);

                count = 0;
            }
        }

        cout << "POOLING:" << endl;
        cout << "---------------------------------------------------------------------------" << endl;

        for (size_t i = 0; i < _size; ++i)
        {
            for (size_t j = 0; j < _size; ++j)
            {
                cout << result[i][j] << "\t";
            }

            cout << endl;
        }

        _poolingMatrix = result;

        return result;
    }

private:
    size_t _size;
    vector<vector<vector<int>>> _rgbMatrix;
    vector<vector<int>> _imageMatrix;
    vector<vector<int>> _convolutionMatrix;
    vector<vector<int>> _activationMatrix;
    vector<vector<int>> _poolingMatrix;

    double _sigmoid(int x)
    {
        return 1.0 / (1 + exp(-x));
    }
    
    void _overflow(vector<vector<int>>& matrix, const size_t& i, const size_t& j, const int& count)
    {
        if (count > 255)
            matrix[i][j] = 255;
        else if (count < 0)
            matrix[i][j] = 0;
        else
            matrix[i][j] = count;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    Image img(10);
    
    {
        cout << "|--------------------------------------------------------------------------|" << endl;
        cout << "|============================= ВВОДНЫЕ ДАННЫЕ =============================|" << endl;
        cout << "|--------------------------------------------------------------------------|" << endl;

        img.print();
    }

    {
        cout << "|--------------------------------------------------------------------------|" << endl;
        cout << "|============================== ЗАДАНИЕ 4.1. ==============================|" << endl;
        cout << "|--------------------------------------------------------------------------|" << endl;

        img.filter();
    }

    {
        cout << "|--------------------------------------------------------------------------|" << endl;
        cout << "|============================== ЗАДАНИЕ 4.2. ==============================|" << endl;
        cout << "|--------------------------------------------------------------------------|" << endl;

        img.activation();
    }

    {
        cout << "|--------------------------------------------------------------------------|" << endl;
        cout << "|============================== ЗАДАНИЕ 4.3. ==============================|" << endl;
        cout << "|--------------------------------------------------------------------------|" << endl;

        img.pooling();
    }
}