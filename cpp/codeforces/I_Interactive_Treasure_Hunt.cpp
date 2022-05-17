#include <iostream>
#include <algorithm>
#define y1 fk1
#define y2 fk2

using namespace std;
const char *scan = "SCAN ", *dig = "DIG ";

int T, n, m, cur, x1, y1, x2, y2;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  for (cin >> T; T; T--) {
    cin >> n >> m;
    int num, diff, dx, dy, tmp;
    cout << scan << 1 << ' ' << 1 << endl;
    cin >> num, num += 4;
    cout << scan << n << ' ' << 1 << endl;
    cin >> diff, diff += 2 - 2 * n;
    dy = num + diff >> 1, dx = num - dy;

    cout << scan << dx / 2 << ' ' << 1 << endl;
    cin >> x1, x1 += 2 - dy;
    x1 = (x1 + dx) / 2, x2 = dx - x1;

    cout << scan << 1 << ' ' << dy / 2 << endl;
    cin >> y1, y1 += 2 - dx;
    y1 = (y1 + dy) / 2, y2 = dy - y1;
    
    cout << dig << x1 << ' ' << y1 << endl;
    cin >> tmp;
    !tmp ? swap (y1, y2) : void ();
    cout << dig << x1 << ' ' << y1 << endl;
    cin >> tmp;
    cout << dig << x2 << ' ' << y2 << endl;
  }
   
  return 0;
}