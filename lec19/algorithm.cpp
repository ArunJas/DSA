#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){

vector<int> v;

v.push_back(1);
v.push_back(8);
v.push_back(3);
v.push_back(4);

cout<<" finding 8 : "<<binary_search(v.begin(),v.end(),8)<<endl;

cout<<"lower bound : "<<lower_bound(v.begin(),v.end(),8)-v.begin()<<endl;
cout<<"upper bound : "<<upper_bound(v.begin(),v.end(),8)-v.begin()<<endl;

int a = 5; cout<<"a : "<<a<<endl;
int b = 7; cout<<"b : "<<b<<endl;

cout<<"max : "<<max(a,b)<<endl;
cout<<"min : "<<min(a,b)<<endl;

swap(a,b);
cout<<endl<<"a : "<<a<<endl;
cout<<"b : "<<b<<endl;


string abcd = "abcd";
reverse(abcd.begin(),abcd.end());
cout<<"string after reverse : "<<abcd<<endl;

for(int i:v){
    cout<<i<<" ";
}
cout<<endl;

}