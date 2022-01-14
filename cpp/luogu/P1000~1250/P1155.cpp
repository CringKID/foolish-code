#include<bits/stdc++.h>

using namespace std;

const int maxn=2e3+5;

int n,Element,Sta1[maxn],Top1,Sta2[maxn],Top2,Base=1;
string Ans;

int main(){
    scanf("%d",&n);
    for(int k=1;k<=n;k++){
        scanf("%d",&Element);
        if(Element==Base){Base++,Ans+="a b ";continue;}

        while(Sta1[Top1]==Base||Sta2[Top2]==Base){if(Sta1[Top1]==Base) Ans+="b ",Top1--;if(Sta2[Top2]==Base) Ans+="d ",Top2--;Base++;}
        if(Top1&&Sta1[Top1]==Element+1) Sta1[++Top1]=Element,Ans+="a ";
        else if(Top2&&Sta2[Top2]==Element+1) Sta2[++Top2]=Element,Ans+="c ";
        else if(Element<Sta1[Top1]||Top1==0) Sta1[++Top1]=Element,Ans+="a ";
        else if(Element>Sta1[Top1]){if(Element>Sta2[Top2]&&!(Sta2[Top2]==0)) return puts("0"),0;Sta2[++Top2]=Element,Ans+="c ";}
    }

    while(Sta1[Top1]==Base||Sta2[Top2]==Base){if(Sta1[Top1]==Base) Ans+='b ',Top1--;if(Sta2[Top2]==Base) Ans+='d ',Top2--;Base++;}

    return printf("%s\n",Ans.c_str())&0;
}