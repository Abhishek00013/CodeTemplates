#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define int long long
#define spc " "

class Fenwick {
private:
    vector<int> bit;
    int n;

public:
    Fenwick(int sz) {
        n = sz;
        bit.resize(n + 2); // 1-based indexing, n+2 to handle r+1 update
    }

    // point add at index idx (0-based)
    void add(int idx, int val) {
        idx++; // convert to 1-based index
        while (idx <= n) {
            bit[idx] += val;
            idx += (idx & -idx);
        }
    }

    // add val to range [l, r] (0-based)
    void rangeAdd(int l, int r, int val) {
        add(l, val);
        add(r + 1, -val);
    }

    int pointQuery(int idx) {
        idx++; // convert to 1-based index
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    Fenwick ft(n);

    for (int i = 0; i < n; ++i)
        ft.rangeAdd(i, i, arr[i]);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r, val;
            cin >> l >> r >> val;
            ft.rangeAdd(l, r, val); // range add [l, r] += val
        } 
        else if (type == 2) {
            int idx;
            cin >> idx;
            cout << ft.pointQuery(idx) << endl;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
