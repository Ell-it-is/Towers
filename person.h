using namespace std;

int Person::count_towers(const vector<int>& t) {
  std::set<int, greater<int>> towers_seen;
  int n = (int) t.size();
  int max = n;
  int cnt = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (t[i] != max) towers_seen.insert(t[i]);
    else {
      cnt++;
      do {
        --max;
      } while (towers_seen.count(max));
    }
  }
  return cnt;
}
