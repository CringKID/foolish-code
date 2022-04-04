#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <windows.h>
#include <ctime>

void solve () {
  bool restag = false;
  int cur = 0;
repeat: 
  cur++;
  int rec = MessageBox (NULL, TEXT ("Time to get a rest!!!"), TEXT ("choose"), MB_YESNO | MB_ICONQUESTION);
  if (rec == IDYES) {
    restag = true;
    MessageBox (NULL, TEXT ("You got a good choice, have a rest is important"), TEXT ("=w="), MB_YESNO | MB_ICONQUESTION);
  }
  for ( ; cur <= 5 && rec != IDYES && !restag; ) {
    goto repeat;
  }
  cur = 0;
  if (!restag) {
    MessageBox (NULL, TEXT ("OK, maybe you are doing a thing that important, have a rest after 5 minute"), TEXT ("= ="), MB_YESNO | MB_ICONQUESTION);
    clock_t from = clock (), to;
    while (true) {
      to = clock ();
      if (to - from >= 300000) {
        goto repeat;
      }
    }
  }
}
#define week() (time -> tm_wday + 6) % 7 + 1
int main () {
  time_t tt; time (&tt);
  tm *time = localtime (&tt);
  for ( ; true; ) {
    if (time -> tm_hour == 20 && time -> tm_min == 45 || time -> tm_hour == 10 && time -> tm_min == 30 || time -> tm_hour == 15 && time -> tm_min == 30) {
      solve ();
    }
    if (time -> tm_hour == 11 && time -> tm_min == 15 || time -> tm_hour == 21 && time -> tm_min == 30) {
      for ( ; MessageBox (NULL, TEXT ("You need to do something other~"), TEXT (">_<"), MB_YESNO | MB_ICONQUESTION) != IDYES; ) {
      }
    }
    if (time -> tm_hour == 12 && time -> tm_min == 0) {
      for ( ; MessageBox (NULL, TEXT ("You can watch news from now"), TEXT ("=w="), MB_YESNO | MB_ICONQUESTION) != IDYES; ) {
      }
    }
    if (time -> tm_hour == 12 && time -> tm_min == 40) {
      for ( ; MessageBox (NULL, TEXT ("News time over~"), TEXT (">_<"), MB_YESNO | MB_ICONQUESTION) != IDYES; ) {
      }
    }
    if ((week () == 2 || week () == 5) && time -> tm_hour == 14 && time -> tm_min == 0 || week () == 7 && time -> tm_hour == 8 && time -> tm_min == 40 || week () == 6 && time -> tm_hour == 13 && time -> tm_min == 30) {
      for ( ; MessageBox (NULL, TEXT ("It's time to have a class"), TEXT (">_<"), MB_YESNO | MB_ICONQUESTION) != IDYES; ) {
      }
    }
  }
	return 0;
}