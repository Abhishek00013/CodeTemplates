class SGT {
public:
    vector<int> seg;
    SGT(int n) {
        seg.resize(4 * n);
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
    void update(int idx, int low, int high, int i, int val, vector<int> &nums) {
        if (low == high) {
            seg[idx] = val;
            nums[i] = val;
            return;
        }
        int mid = (low + high) >> 1;

        if (i <= mid)
            update(2 * idx + 1, low, mid, i, val, nums);
        else
            update(2 * idx + 2, mid + 1, high, i, val, nums);
        
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
    int query(int idx, int low, int high, int l, int r, vector<int> &nums) {
        if (r < low || high < l){ 
            // no overlap
            return 0;
        }

        if (l <= low && r >= high){ 
            // complete overlap
            return seg[idx];
        }

        // partial overlap

        int mid = (low + high) >> 1;

        int left = query(2 * idx + 1, low, mid, l, r, nums);
        int right = query(2 * idx + 2, mid + 1, high, l, r, nums);

        return left + right;
    }
};
