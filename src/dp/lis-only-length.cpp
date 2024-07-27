ll lis(llv1& ar) {
  llv1 v, buffer;
  llv1::iterator vv;
  v.pb(2000000000ll);

  ll n = sz(ar);

  for1(0, n){
    if(ar[i] > *v.rbegin()) {
      v.pb(ar[i]);
    }
    else{
      vv = lower_bound(v.begin(), v.end(), ar[i]);
      *vv = ar[i];
    }
  }
  return sz(v);
}
