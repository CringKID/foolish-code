#include <iostream>
#include <algorithm>
#include <windows.h>
#include <ctime>

using namespace std;
int main () {
  while (!GetAsyncKeyState (VK_RSHIFT)) {
    srand (time (0));
    bool flag = false;
    while (true) {
      if (GetAsyncKeyState (VK_LBUTTON)) {
        flag = true;
        clock_t start = clock ();
        for (clock_t now = clock (); double (now - start) / CLOCKS_PER_SEC < 0.5; now = clock ()) {
        // while (1) {
          mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
          Sleep (rand () % 34 + 67);// cps 10 ~ 15    time 67 ~ 100
          cout << (double (now - start) / CLOCKS_PER_SEC) << '\n';
        }
      }
    }
  }
  return 0;
}