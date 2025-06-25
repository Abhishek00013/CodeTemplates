#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define int long long
#define spc " "

void build(int idx, int low, int high, vector<int> &nums, vector<int> &seg) {
    if (low == high) {
        seg[idx] = nums[low];
        return;
    }
    int mid = (low + high) >> 1;
    build(2 * idx + 1, low, mid, nums, seg);
    build(2 * idx + 2, mid + 1, high, nums, seg);

    seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
}

void update(int idx, int low, int high, int i, int val, vector<int> &nums, vector<int> &seg) {
    if (low == high) {
        nums[i] = val;
        seg[idx] = val;
        return;
    }

    int mid = (low + high) >> 1;
    if (i <= mid)
        update(2 * idx + 1, low, mid, i, val, nums, seg);
    else
        update(2 * idx + 2, mid + 1, high, i, val, nums, seg);

    seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
}

int query(int idx, int low, int high, int l, int r, vector<int> &nums, vector<int> &seg) {
    if (r < low || high < l)
        return LLONG_MAX; // No overlap

    if (l <= low && high <= r)
        return seg[idx]; // Total overlap

    int mid = (low + high) >> 1;

    int left = query(2 * idx + 1, low, mid, l, r, nums, seg);
    int right = query(2 * idx + 2, mid + 1, high, l, r, nums, seg);

    return min(left, right);
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];

    vector<int> seg(4 * n);
    build(0, 0, n - 1, nums, seg);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            // Update: type 1 idx val
            int idx, val;
            cin >> idx >> val;
            update(0, 0, n - 1, idx, val, nums, seg);
        } else if (type == 2) {
            // Query: type 2 l r
            int l, r;
            cin >> l >> r;
            cout << query(0, 0, n - 1, l, r, nums, seg) << endl;
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
