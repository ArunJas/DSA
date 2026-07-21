#include <iostream>
using namespace std;

int main(){
    // power of a,b
          int a , b;      
         cout<<"Enter the values of  a and b:"<<endl;


         cin >> a >> b;

          int ans = 1;

          for(int i = 1; i<=b; i++){
            ans = ans * a;

          }
         cout << " The answer is : "<< ans << endl;
      
         return 0;

         }