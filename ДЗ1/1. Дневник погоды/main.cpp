#include <iostream>
#include <iomanip>
#include <cmath>


double Mean(const double* arr, int n){
    double sum = 0;
    for(int i = 0; i < n; ++i){
        sum += arr[i];
    }
    return sum / n;
}


double Min(const double* arr, int n){
    double min = arr[0];
    for(int i = 0; i < n; ++i){
        min = std::min(min, arr[i]);
    }
    return min;
}


double Max(const double* arr, int n){
    double max = arr[0];
    for(int i = 0; i < n; ++i){
        max = std::max(max, arr[i]);
    }
    return max;
}


int CountCold(const double* arr, int n){
    int cnt = 0;
    for(int i = 0; i < n; ++i){
        if(arr[i] < 0){
            cnt += 1;
        }
    }
    return cnt;
}


int main(){
    int n;
    std::cin >> n;
    double* arr = new double[n];
    for(int i = 0; i < n; ++i){
        std::cin >> arr[i];
    }

    double mean = Mean(arr, n);
    double min = Min(arr, n);
    double max = Max(arr, n);
    int cold = CountCold(arr, n);

    std::cout << std::fixed << std::setprecision(1);
    std::cout << mean << '\n';
    std::cout << std::defaultfloat;
    std::cout << min << ' ' << max << '\n';
    std::cout << cold << '\n';

    delete[] arr;
    return 0;
}