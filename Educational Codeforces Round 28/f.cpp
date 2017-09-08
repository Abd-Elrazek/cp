#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int a[N];
int last[N];

int main() {
  memset(last, -1, sizeof(last));
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
  }
  long long ans = n;
  long long now = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (last[a[i]] == -1) {
      now += n - 1 - i;
    } else {
      now += last[a[i]] - i - 1;
    }
    ans += 2 * now;
    now++;
    last[a[i]] = i;
  }
  printf("%.15f\n", (double) ans / (1LL * n * n));
  return 0;
}
