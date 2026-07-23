#include<iostream>
#include <queue>
using namespace std;

int main() {
  
    priority_queue<int> maxi;

    priority_queue<int, vector<int>, greater<int>> mini;
      
      maxi.push(10);
      maxi.push(20);
      maxi.push(10);
      maxi.push(20);
      
      cout<< "size : " << maxi.size() << endl;
      int n = maxi.size();
      for(int i = 0;i<n;i++){
      for(int i = 0;i<maxi.size();i++){
        cout<<maxi.top()<<" ";
        maxi.pop();
      }
      cout << endl;

     mini.push(10);
     mini.push(20);
      mini.push(10);
      mini.push(20);
      
      cout<< "size : " << mini.size() << endl;
      int m = mini.size();
      for(int i = 0;i<m;i++){
        cout<<mini.top()<<" ";
        mini.pop();
      }
   



    }
}
