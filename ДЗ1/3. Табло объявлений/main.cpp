#include <iostream>

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

int length(const char* s){
    int len = 0;
    while (s[len]){
        ++len;
    }
    return len;
}

void clear(char table[][10]){
    for (int y = 0; y < 5; ++y){
        for (int x = 0; x < 10; ++x){
            table[y][x] = ' ';
        }
    }
}

bool put(char table[][10], int x, int y, char c){
    if (x < 0 || x >= 10){
        return false;
    }
    if (y < 0 || y >= 5){
        return false;
    }
    table[y][x] = c;
    return true;
}

bool text(char table[][10], int x, int y, const char* word){
    int len = length(word);
    if (x < 0 || x >= 10 || y < 0 || y >= 5 || len > 10 - x){
        return false;
    }
    for (int i = 0; i < len; ++i){
        table[y][x + i] = word[i];
    }
    return true;
}

void print(char table[][10]){
    for (int y = 0; y < 5; ++y){
        for (int x = 0; x < 10; ++x){
            std::cout << table[y][x];
        }
        std::cout << '\n';
    }
}

int main(){
    char table[5][10];
    clear(table);

    char cmd[64];

    while (std::cin >> cmd){
        if (equal(cmd, "quit")){
            break;
        }

        if (equal(cmd, "clear")){
            clear(table);
        }
        else if (equal(cmd, "put")){
            int x, y;
            char c;
            std::cin >> x >> y >> c;
            if (!put(table, x, y, c)){
                std::cout << "error\n";
            }
        }
        else if (equal(cmd, "text")){
            int x, y;
            char word[64];
            std::cin >> x >> y >> word;
            if (!text(table, x, y, word)){
                std::cout << "error\n";
            }
        }
        else if (equal(cmd, "print")){
            print(table);
        }
        else{
            std::cout << "error\n";
        }
    }

    return 0;
}