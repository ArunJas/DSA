#include<iostream>
#include<map>
using namespace std;

int main(){

    map<int, string> m;

    m[1] = "one";
    m[2] = "piexe";
    m[3] = "luffy";
    m[4] = "zoro";

    for(auto i:m){
        cout<<i.first<<" "<<i.second<<endl;
    }

    cout<<"Size of map : "<<m.size()<<endl;

    auto it = m.find(3);
    if(it != m.end()){
        cout<<"Element found : "<<it->first<<" "<<it->second<<endl;
    }else{
        cout<<"Element not found"<<endl;
    }



}