#include <iostream>
#include <random>

bool equal(const char* a, const char* b){
    while (*a && *b){
        if (*a != *b){
            return false;
        }
        ++a;
        ++b;
    }
    return *a == *b;
}

void deposit(int& b, int k){
    if (k <= 0){
        std::cout << "error" << '\n';
        return;
    }
    b += k;
}

void withdraw(int& b, int k){
    if (k <= 0 || k > b){
        std::cout << "error" << '\n';
        return;
    }
    b -= k;
}

void balance(int& b, int){
    std::cout << b << '\n';
}

void reset(int& b, int){
    b = 0;
}

void dep(int& sum, int){
    static std::random_device rd;
    if (rd() & 1){
        sum *= 2;
    }
    else{
        sum = 0;
    }
}

int main(){
    const int n = 5;
    const char* comands[n] = {"deposit", "withdraw", "balance", "reset", "dep"};
    void (*ops[n])(int&, int) = {deposit, withdraw, balance, reset, dep};

    int balance = 0;
    char comand[64];
    int k = 0;

    while (std::cin >> comand){
        if (equal(comand, "stop")){
            break;
        }

        bool found = false;
        for (int j = 0; j < n; ++j){
            if (equal(comand, comands[j])){
                if (j < 2){
                    std::cin >> k;
                }
                ops[j](balance, k);
                found = true;
                break;
            }
        }

        if (!found){
            std::cout << "error\n";
        }
    }

    return 0;
}