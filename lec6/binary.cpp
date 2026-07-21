#include<iostream>
#include<math.h>
using namespace std;

int main(){
int n;
cout << "enter the value of n:";
cin >>n;
int ans = 0;
int i = 0;
while(n!=0){
    int bit  = n & 1;
  ans = (bit * pow(10,i)) + ans;  //   using power function 10 to the power i
  n = n >> 1;
  i++;
  
}
cout << "answer is :" << ans << endl;
return 0;
}