#include<iostream>
using namespace std;

void Dummy(int n){
    n++;
    cout << " n is :" << n << endl;

}
int main(){
    int n;
    cout << "enter the value of n:";
    cin >> n;
    cout << "before calling dummy function n is :" << n << endl;
    Dummy(n);
    cout << "after calling dummy function n is :" << n << endl;

     return 0;
}
