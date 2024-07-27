// shortest path faster algorithm
// average for random graph : O(E) , worst : O(VE)

const int MAXN = 20001;
const int INF = 100000000;
int n, m;
vector<pii> graph[MAXN];

bool inqueue[MAXN];
int dist[MAXN];

void spfa(int start) {
    for (int i = 0; i < n; ++i) dist[i] = INF;
    dist[start] = 0;

    queue<int> q;
    q.push(start);
    inqueue[start] = true;

    while (!q.empty()) {
        int here = q.front();
        q.pop();

        inqueue[here] = false;
        for (auto& nxt : graph[here]) {
            if (dist[here] + nxt.second < dist[nxt.first]) {
                dist[nxt.first] = dist[here] + nxt.second;
                if (!inqueue[nxt.first]) {
                    q.push(nxt.first);
                    inqueue[nxt.first] = true;
                }
            }
        }
    }
}
