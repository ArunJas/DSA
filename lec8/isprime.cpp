#include<iostream>
using namespace std;

//1 : prime no .
// 0 : not a prime no.

bool isPrime(int n){

    for (int i =2; i<n; i++){
        // divide hogya h,not a prime no.
        if(n%i == 0){
            return 0;
        }
    }
    return 1;
}

int main(){
    int n;
    cout << "enter the value of n:";
    cin >> n;

    if(isPrime(n)){
        cout << n << " is a prime number." << endl;
    }
    else{
        cout << n << " is not a prime number." << endl;
    }

     return 0;
}