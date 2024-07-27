llv1 a;
llv1 mTree[Mx];
void makeTree(ll idx, ll ss, ll se) {
  if (ss == se) {
    mTree[idx].push_back(a[ss]);
    return;
  }
  ll mid = (ss + se) / 2;
  makeTree(2 * idx + 1, ss, mid);
  makeTree(2 * idx + 2, mid + 1, se);
  merge(mTree[2 * idx + 1].begin(), mTree[2 * idx + 1].end(), mTree[2 * idx + 2].begin(), mTree[2 * idx + 2].end(), back_inserter(mTree[idx]));
}
ll query(ll node, ll start, ll end, ll q_s, ll q_e, ll k) {
  // i j k: Ai, Ai+1, ..., Aj로 이루어진 부분 수열 중에서 k보다 큰 원소의 개수를 출력
  한다.if (q_s > end || start > q_e) return 0;
  if (q_s <= start && q_e >= end) {
    return mTree[node].size() - (upper_bound(mTree[node].begin(), mTree[node].end(), k) - mTree[node].begin());
  }
  ll mid = (start + end) / 2;
  ll p1 = query(2 * node + 1, start, mid, q_s, q_e, k);
  ll p2 = query(2 * node + 2, mid + 1, end, q_s, q_e, k);
  return p1 + p2;
}