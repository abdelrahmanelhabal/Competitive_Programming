  vector<int>all;
  for(int i = 0 ; i < n ; i++){
      cin >> a[i];
      all.emplace_back(a[i]);
  }
  sort(all(all));
  all.erase(unique(all(all)) , all.end());
  for(int i = 0 ; i < n ; i++){
      a[i] = lower_bound(all(all) , a[i]) - all.begin();
  }
