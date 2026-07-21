#include <iostream>
using namespace std;

int main(){
     cout << "Welcome to the Arun calculator program"<<endl;
    int a,b;
      cout << "enter the value of a:" << endl;
     cin >> a;

      cout << "enter the value of b :" << endl;
      cin >> b;
 
     char op;
      cout << "enter the operation you want to perform" << endl;
      cin >> op;
        switch(op){
            case '+': cout << "the sum is :" << a+b << endl;
            break;
            case '-': cout << "the difference is :" << a-b << endl;
            break;
            case '*': cout << "the product is :" << a*b << endl;
            break;
            case '/': cout << "the quotient is :" << a/b << endl;
            break;
            default: cout << "please enter a valid operation" << endl;
          
        }
        
         return 0;
        }