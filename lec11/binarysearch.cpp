#include<iostream>
using namespace std;

int binarySearch(int arr[], int size, int key){
    int start = 0;
    int end = size - 1;

    while(start <= end){
        int mid = (start + end) / 2;

        if(arr[mid] == key){
            return mid;
        }
        else if(arr[mid] < key){
            start = mid + 1;
        }
        else{
            end = mid - 1;
        }
    }
    return -1; // Key not found
}


int main(){
    cout << "Binary Search Implementation" << endl;

    int even[6] = {2,4,6,8,12,18};
    int odd[5] = {3,8,11,14,16};
    
    int evenindex = binarySearch(even, 6, 6);
    cout << "Index of 6 in even array : " << evenindex << endl;
    
    int oddindex = binarySearch(odd, 5, 14);
    cout << "Index of 14 in odd array : " << oddindex << endl;

    return 0;
}






 
