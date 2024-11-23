#include <iostream>
using namespace std;

char* CopyString(const char* str){
    auto cp = str;
    int len = 0;
    while(*(cp++)){
        len++;
    }
    auto res = new char[len+1];
    res[len] = 0;
    for(auto i = 0; i < len; i++){
        res[i] = str[i];
    }
    return res;
}

char* ConcatinateStrings(const char* a, const char* b){
    auto cpa = a;
    int lena = 0;
    while(*(cpa++)){
        lena++;
    }
    auto cpb = b;
    int lenb = 0;
    while(*(cpb++)){
        lenb++;
    }
    auto res = new char[lena+lenb+1];
    res[lena+lenb] = 0;
    for(auto i = 0; i < lena; i++){
        res[i] = a[i];
    }
    for(auto i = lena; i < (lena +lenb); i++){
        res[i] = b[i-lena];
    }
    return res;
}
int main(){
    char *st =  "Hello world";
    char *st2 = CopyString(st);
    cout << st2 << endl;

    char *a = "Privet ", *b = "Mir";
    char *c = ConcatinateStrings(a, b);
    cout << c << endl;
    return 0;
}
