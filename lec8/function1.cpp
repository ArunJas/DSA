#include<iostream>
using namespace std;

int power ( ){
    cout << "Taking input: " << endl;
    int a , b;
    cin >> a >> b;
     
    int ans = 1;
    for(int i = 1; i<=b; i++){
        ans = ans * a;
     }
     return ans;
     }

     int main(){ 
     /*
        int a, b ;
        cout<<"taking input: "<<endl;
     cin >> a >> b;
     int answer  = power(a,b);
     
        cout << "b to the power of a is :" << answer << endl;

        int c, d ;
        cout<<"taking input: "<<endl;
     cin >> c >> d;
      answer = power(c,d);
        cout << "the answer is :" << answer << endl;
     */
    cout << " answer is :" << power() << endl;

     return 0;

    }