#include<iostream>
#include <queue>
using namespace std;

int main() {
  
  queue<string> q;

     q.push("I");
     q.push("LOVE");
     q.push("YOU");

     cout << "Front Element : "<<q.front()<<endl;
     cout << "Back Element : "<<q.back()<<endl;

     q.pop();

     cout << "Front Element after pop : "<<q.front()<<endl;
     cout << "Size of queue : "<<q.size()<<endl;
     cout << "Empty or not : "<<q.empty()<<endl;

}