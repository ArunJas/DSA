#include<iostream>
using namespace std;

int main(){
    int a;
    cout << "enter the value of a:";
    cin >> a;
    for(int i=0;i<a;i++){
          for(int k=0;k<i;k++){
            cout << "  ";

          }
        

        for(int j = 0;j<a;j++){
            cout <<" *";
            
            
        }
        
        cout << endl;
    }

}