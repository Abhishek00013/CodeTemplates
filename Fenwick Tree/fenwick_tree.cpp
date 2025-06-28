#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define int long long
#define spc " "

class fenwick {
private:
    vector<int> bit; // binary indexed tree
    int n;

public:
    fenwick(int sz) {
        n = sz;
        bit.resize(n + 1); // 1-based indexing
    }

    void update(int idx, int val) {
        idx++; // convert to 1-based index
        while (idx <= n) {
            bit[idx] += val;
            idx += (idx & -idx);
        }
    }

    int query(int idx) {
        idx++; // convert to 1-based index
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    // sum from range [l, r] (0-based index)
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    fenwick ft(n);

    // build the fenwick tree
    for (int i = 0; i < n; ++i)
        ft.update(i, arr[i]);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int idx, val;
            cin >> idx >> val;
            ft.update(idx, val); // add val to index idx
        } 
        else if (type == 2) {
            int l, r;
            cin >> l >> r;
            cout << ft.rangeQuery(l, r) << endl;
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
