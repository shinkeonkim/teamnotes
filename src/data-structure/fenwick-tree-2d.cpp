struct FenwickTree2D {
    ll size;
    llv2 data;

    FenwickTree2D(ll N) {
        size = N;
        data = llv2(size+1, llv1(size+1));
    }

    void update(int x, int y, ll val) {
        ll dv = val - sum(x, y, x, y);
        while(x <= size) {
            int y2 = y;
            while(y2 <= size) {
                data[x][y2] += dv;
                y2 += y2 & -y2;
            }
            x += x & -x;
        }
    }

    ll sum(int x, int y) {
        ll ret = 0;
        while(x) {
            int y2 = y;
            while(y2) {
                ret += data[x][y2];
                y2 -= y2 & -y2;
            }
            x -= x & -x;
        }
        return ret;
    }

    ll sum(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) + sum(x1 - 1, y1 -1) - sum(x1-1, y2) - sum(x2, y1-1);
    }
};
