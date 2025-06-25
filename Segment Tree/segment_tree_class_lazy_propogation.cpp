class SGT {
public:
    vector<int> seg, lazy;

    SGT(int n) {
        seg.resize(4 * n);
        lazy.resize(4 * n);
    }

    void build(int idx, int low, int high, vector<int> &nums) {
        if (low == high) {
            seg[idx] = nums[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * idx + 1, low, mid, nums);
        build(2 * idx + 2, mid + 1, high, nums);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    // range update: add val to range [l, r]
    void update(int idx, int low, int high, int l, int r, int val) {
        // update previous remaining update 
        if (lazy[idx] != 0) {
            seg[idx] += (high - low + 1) * lazy[idx]; // apply pending updates
            if (low != high) { // propagate to children
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }

        if (r < low || high < l) {  // no overlap
            return;
        }

        if (l <= low && high <= r) { // complete overlap
            seg[idx] += (high - low + 1) * val;
            
            if (low != high) { // propagate to children
                lazy[2 * idx + 1] += val;
                lazy[2 * idx + 2] += val;
            }
          
            return;
        }

        // Partial overlap
        int mid = (low + high) >> 1;
        update(2 * idx + 1, low, mid, l, r, val);
        update(2 * idx + 2, mid + 1, high, l, r, val);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    // Range query: sum in [l, r]
    int query(int idx, int low, int high, int l, int r) {
        // update previous remaining update
        if (lazy[idx] != 0) {
            seg[idx] += (high - low + 1) * lazy[idx]; // apply pending updates
            if (low != high) { // propagate to children
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }

        if (r < low || high < l) {
            // No overlap
            return 0;
        }

        if (l <= low && high <= r) {
            // Complete overlap
            return seg[idx];
        }

        // Partial overlap
        int mid = (low + high) >> 1;
        int left = query(2 * idx + 1, low, mid, l, r);
        int right = query(2 * idx + 2, mid + 1, high, l, r);

        return left + right;
    }
};
