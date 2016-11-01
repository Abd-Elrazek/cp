#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int n, m;
int s[N], can[N][N], mid[N][N];
int a[N], b[N];

int sum(int l, int r) {
  return s[r] - s[l - 1];
}

void dfs(int l, int r, int carry) {
  if (l == r) return;
  dfs(l, mid[l][r], carry);
  dfs(mid[l][r] + 1, r, carry + 1);
  int lef = sum(l, mid[l][r]);
  int rig = sum(mid[l][r] + 1, r);
  if (lef > rig) {
    printf("%d R\n", carry);
  } else if (lef < rig) {
    printf("%d L\n", carry + 1);
  } else {
    assert(0);
  }
}

int main() {
  scanf("%d", &n);
  long long suma = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    suma += a[i];
    s[i] = s[i - 1] + a[i];
  }
  scanf("%d", &m);
  long long sumb = 0;
  for (int i = 1; i <= m; i++) {
    scanf("%d", b + i);
    sumb += b[i];
  }
  if (suma != sumb) {
    puts("NO");
    return 0;
  }
  int i = 0;
  for (int j = 1; j <= m; j++) {
    long long now = 0;
    int st = i + 1;
    while (now < b[j]) {
      now += a[++i];
    }
    int fn = i;
    if (now != b[j]) {
      puts("NO");
      return 0;
    }
    for (int p = st; p <= fn; p++) {
      can[p][p] = 1;
    }
    for (int len = 2; len <= fn - st + 1; len++) {
      for (int p = st; p <= fn; p++) {
        int q = p + len - 1;
        for (int r = p; r < q; r++) {
          if (can[p][r] && can[r + 1][q] && sum(p, r) != sum(r + 1, q)) {
            can[p][q] = 1;
            mid[p][q] = r;
          }
        }
      }
    }
    if (!can[st][fn]) {
      puts("NO");
      return 0;
    }
  }
  
  puts("YES");
  i = 0;
  for (int j = 1; j <= m; j++) {
    long long now = 0;
    int st = i + 1;
    while (now < b[j]) {
      now += a[++i];
    }
    int fn = i;
    dfs(st, fn, j);
  }
  
  return 0;
}
