#include <iostream>

// массив weights хранит веса нейросети.
// массив params хранит ее параметры.
// нужен void* т.к. параметры имеют разный тип данных

int main() {
    const int n = 5;
    void* params[n];
    int type[n] = {0, 0, 0, 1, 2};

    params[0] = new int(2);        // A
    params[1] = new int(3);        // B
    params[2] = new int(4);        // C
    params[3] = new float(0.01f);  // lr
    params[4] = new bool(true);    // early stop

    int A = *static_cast<int*>(params[0]);
    int B = *static_cast<int*>(params[1]);
    int C = *static_cast<int*>(params[2]);

    int*** weights = new int**[A];
    for (int a = 0; a < A; a++) {
        weights[a] = new int*[B];
        for (int b = 0; b < B; b++) {
            weights[a][b] = new int[C];
            for (int c = 0; c < C; c++) {
                weights[a][b][c] = rand() % 9 - 4;   
            }
        }
    }

    std::cout << "params:\n";
    for (int i = 0; i < n; i++) {
        if (type[i] == 0) {
            std::cout << *static_cast<int*>(params[i]);
        }
        else if (type[i] == 1) {
            std::cout << *static_cast<float*>(params[i]);
        }
        else {
            std::cout << (*static_cast<bool*>(params[i]) ? "true" : "false");
        }
        std::cout << "\n";
    }

    for (int a = 0; a < A; a++) {
        std::cout << "layer " << a + 1 << ":\n";
        for (int b = 0; b < B; b++) {
            for (int c = 0; c < C; c++) {
                std::cout << weights[a][b][c] << " ";
            }
            std::cout << "\n";
        }
    }

    for (int i = 0; i < n; i++) {
        if (type[i] == 0) {
            delete static_cast<int*>(params[i]);
        }
        else if (type[i] == 1) {
            delete static_cast<float*>(params[i]);
        }
        else {
            delete static_cast<bool*>(params[i]);
        }
    }
    for (int a = 0; a < A; a++) {
        for (int b = 0; b < B; b++) {
            delete[] weights[a][b];
        }
        delete[] weights[a];
    }
    delete[] weights;
}