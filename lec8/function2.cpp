#include<iostream>
using namespace std;

int power ( ){
    cout << "taking the value of a and b: " << endl;
    int a ,b;
    cin >> a >> b;
    int ans = 1;
    for(int i = 1; i<=b; i++){
        ans = ans * a;
     }
    
     return ans;
     }
     int main(){
        int answer = power();
            cout << "the answer is :" << answer << endl;

        
         return 0;
         }

