def calc (n, m) :
  ans = 1
  for i in range (0, m) :
    ans = ans * (n - i)
  return ans

n, m = map (int, input ().split ())
lim1 = 10000000000
lim2 = lim1 ** 10
if n < m :
  n, m = m, n

ans = calc (n + m, m) // calc (m, m) % lim2
arr = []

for i in range (0, 10) :
  arr.append (ans % lim1)
  ans = ans // lim1
for i in range (0, 10) :
  print ("%010d" % arr[9 - i])