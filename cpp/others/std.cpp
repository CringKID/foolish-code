#include"bits/stdc++.h"
using namespace std;
typedef long long ll;

int main(){
    ll Q;
    cin>>Q;
    priority_queue<ll,vector<ll>, greater<ll>> pq;
    queue<ll>q;

    for(ll i=0;i<Q;i++){
        ll t;
        cin>>t;

        if(t==1){
            ll x;
            cin>>x;
            q.push(x);
        }else if(t==2){
            if(pq.empty()){
                cout<<q.front()<<endl;
                q.pop();
            }else{
                cout<<pq.top()<<endl;
                pq.pop();
            }
        }else{
            while(!q.empty()){
                ll k=q.front();
                pq.push(k);
                q.pop();
            }
        }
    }
}