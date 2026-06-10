#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int getMin(int num[],int n){
    int mini = INT_MAX;
    for (int i = 0; i<n;i++){
        mini = min(mini , num[i]);
     //if(nu[i] <mini){
     //    mini = num[i];
     //}
    }
    // returing min value
    return mini;
}
int getMax(int num[],int n){
    int maxi = INT_MIN;
    for (int i = 0; i<n;i++){
        maxi = max(maxi , num[i]);
     //if(num[i] >maxi){
     //    maxi = num[i];
     //}
    }
    // returing max value
    return maxi;
}
 int main(){
    cout << "enter the size of array: " ;
 int size;
 cin >> size;
    int num[100];
  // taking input in array
 for (int i = 0; i<size;i++){
    cin >> num[i];
}
 cout << "Minimum value is: " << getMin(num, size) << endl;
 cout << "Maximum value is: " << getMax(num, size) << endl;

 return 0;

}