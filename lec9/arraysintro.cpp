#include <iostream>
using namespace std;

void printArray(int arr[], int n){
    cout << " printing the array " << endl;
    // print the array
    for (int i = 0; i<n;i++){
        cout << arr[i] << " ";
    }
    cout << " printing  done" << endl;

}

 int main(){

 // declaration of array

 int number[15];

 // accessing the array

 cout <<" value of 14 index is " << number[14] << endl;

 // initialization of array

 int second[3]= {5 , 7 , 11};

 // accessing the array

 cout << " value at 2 index is " << second[2] << endl;

int third[15] = {2 , 7};
int n = 15 ;
printArray(third , 15);

int fourth [10] = {0}; 
n = 10;
printArray(fourth , 10);

// intialization all locations with 1 [not possible with below line]

int fifth[10] = {0};
n = 10;
printArray(fifth , 10);

int fifthSize = sizeof(fifth) / sizeof(int);
cout << " size of fifth array is " << fifthSize << endl;

char ch[5] = {'a', 'b', 'c', 'r', 'p'};
cout << ch[3] << endl;
cout <<"printing the array" << endl;
// print the array
for (int i = 0; i<5;i++){
    cout << ch[i] << " ";
}
cout << "printing done"<< endl;
double firstDouble[5];
float firstFloat[6];
bool firstBool[9];


cout << endl << " everything is fine " << endl << endl;
return 0;

}