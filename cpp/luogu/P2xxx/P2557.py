pre = dict ()
n, k = int (), int ()
arr = []
def solve (x) :
  i = 2
  while i <= x : 
    if x % i == 0 :
      arr.append (i)
      pre[i] = 0;
    while x % i == 0 : 
      x /= i
      pre[i] += k
    i += 1
  if x > 1 : 
    pre[x] += 1
n, k = map (int, input ().split ())
solve (n)
ans = 1
for i in arr : 
  t = 0
  tmp = 1
  for j in range (pre[i] + 1) : 
    t += tmp
    tmp *= i
  ans *= t
print (ans)