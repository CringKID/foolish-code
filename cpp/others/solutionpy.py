lst=dict() 
n,k=int(),int() 
access=[] 
def research(x): 
    i=2
    while i<=x :
        if x%i==0 :
            access.append(i)
            lst[i]=0
        while x%i==0 :
            x/=i
            lst[i]+=k
        i+=1
    if x>1 :
        lst[x]+=1

n,k=map(int,input().split())

research(n)

ans=1

for i in access:
    t=0
    tmp=1
    for j in range(lst[i]+1):
        t+=tmp
        tmp*=i
    ans*=t

print(ans)