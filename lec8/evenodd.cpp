#include<iostream>
using namespace std;
// 1 is even
// 0 is odd

bool iseven(int a){
    // odd
    if(a&1){
        return 0;
    }
    else{
        return 1;
    }
}

int main (){
    cout << "Enter the number :";

int num ;
cin >> num;

if (iseven(num)){
    cout << "Number is even"<<endl;
}
else{
    cout << "Number is odd"<<endl;

}







}