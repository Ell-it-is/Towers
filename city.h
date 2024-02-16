using namespace std;

void City::construct_towers() {
  // Initialize with random permutation for the first column
  vector<int> p(n_);
  std::iota(p.begin(), p.end(), 1);
  std::random_shuffle(p.begin(), p.end());

  // Assigning the first column values to temp_towers
  vector<vector<int>> temp_towers(n_, vector<int>(n_, 0));
  for (int i = 0; i < n_; i++) {
    temp_towers[i][0] = p[i];
  }

  // Keep track of available values for each row
  vector<set<int>> a(n_);
  for (int i = 0; i < n_; i++) {
    for (int j = 1; j <= n_; j++) {
      if (p[i] == j) continue;
      a[i].insert(j);
    }
  }

  /*
   * Go from the second column and build each column by:
   * Choosing a random element from available elements.
   * Available element is an element such that:
   * - It is unique across a row it should be placed in
   * - It is unique with respect to already placed elements in current column
   */
  for (int k = 1; k < n_; k++) {
    vector<int> column;
    set<int> used; // already placed elements in current column
    for (int i = 0; i < n_; i++) {
      vector<int> v;
      std::set_difference(a[i].begin(), a[i].end(), used.begin(), used.end(), std::inserter(v, v.begin()));
      if (v.size() == 0) {
        // In case where randomly chosen elements aren't unique across rows, search for a different permutation
        column.clear();
        for (int j = 1; j <= n_; j++) column.push_back(j);
        std::random_shuffle(column.begin(), column.end());
        bool can = false;
        while (!can) {
          can = true;
          std::next_permutation(column.begin(), column.end());
          for (int j = 0; j < n_; j++) {
            if (a[j].count(column[j]) == 0) {
              can = false;
              break;
            }
          }
        }
        break;
      }
      int rand_pos = rand() % v.size();
      int rand_element = v[rand_pos];
      column.push_back(rand_element);
      used.insert(rand_element);
    }
    for (int i = 0; i < n_; i++) {
      temp_towers[i][k] = column[i];
    }
    for (int i = 0; i < n_; i++) {
      a[i].erase(column[i]);
    }
  }

  // Place the elements from temp_towers into 'towers'
  for (int i = 0; i < n_; i++) {
    towers.push_back(vector<Cell>(n_));
    for (int j = 0; j < n_; j++) {
      Cell cell({i, j}, temp_towers[i][j], 0, false);
      towers[i][j] = cell;
    }
  }
}

City::City(int n) {
  n_ = n;
  m_ = n + 2;
  for (int i = 0; i < m_; i++) city.push_back(vector<Cell>(m_));
  construct_towers();
  build_city_with_towers();
  populate();
}

void City::build_city_with_towers() {
  for (int i = 1; i < m_ - 1; i++) {
    for (int j = 1; j < m_ - 1; j++) {
      city[i][j] = towers[i - 1][j - 1];
    }
  }
}

void City::populate() {
  invalidate_corners();
  
  Cell cell;
  cell.type = PERSON;
  cell.person.is_looking = true;
  
  // Top row
  for (int col = 0; col < n_; col++) {
    vector<int> t(n_);
    for (int row = 0; row < n_; row++) {
      t[row] = towers[row][col].tower.height;
    }
    cell.person.towers_counted = cell.person.count_towers(t);
    city[0][col + 1] = cell;
  }

  // Bottom row
  for (int col = 0; col < n_; col++) {
    vector<int> t(n_);
    for (int row = n_ - 1; row >= 0; row--) {
      t[n_ - row - 1] = towers[row][col].tower.height;
    }
    cell.person.towers_counted = cell.person.count_towers(t);
    city[m_ - 1][col + 1] = cell; 
  }

  // Left column
  for (int row = 0; row < n_; row++) {
    vector<int> t(n_);
    for (int col = 0; col < n_; col++) {
      t[col] = towers[row][col].tower.height;
    }
    cell.person.towers_counted = cell.person.count_towers(t);
    city[row + 1][0] = cell;
  }

  // Right column
  for (int row = 0; row < n_; row++) {
    vector<int> t(n_);
    for (int col = n_ - 1; col >= 0; col--) {
      t[n_ - col - 1] = towers[row][col].tower.height;
    }
    cell.person.towers_counted = cell.person.count_towers(t);
    city[row + 1][m_ - 1] = cell;
  }
}

void City::invalidate_corners() {
  city[0][0].type = NONE;
  city[0][m_ - 1].type = NONE;
  city[m_ - 1][0].type = NONE;
  city[m_ - 1][m_ - 1].type = NONE;
}

bool City::is_solution_correct() {
  for (int i = 0; i < n_; i++) {
    for (int j = 0; j < n_; j++) {
      Cell c = towers[i][j];
      Tower t = c.tower;
      if (!t.is_guess_correct() || !c.is_valid(towers)) return false;
    }
  }
  return true;
}

void City::print_solution() {
  for (int i = 0; i < m_; i++) {
    for (int j = 0; j < m_; j++) {
      if (city[i][j].type == PERSON) {
        cout << city[i][j].person.towers_counted << " ";
      } else if (city[i][j].type == TOWER){
        cout << city[i][j].tower.height << " ";
      } else {
        cout << " " << " ";
      }
    }
    cout << "\n";
  }
}

void City::print_puzzle() {
  for (int i = 0; i < m_; i++) {
    for (int j = 0; j < m_; j++) {
      if (city[i][j].type == PERSON) {
        Person p = city[i][j].person;
        if (p.is_looking) {
          cout << city[i][j].person.towers_counted << " ";
        } else {
          cout << "-" << " ";
        }
      } else if (city[i][j].type == TOWER) {
        Tower t = city[i][j].tower;
        if (t.visible) {
          cout << t.height << " ";
        } else {
          cout << t.guess << " ";
        }
      } else {
        cout << " " << " ";
      }
    }
    cout << "\n";
  }
}

void City::make_towers_visible(int percentage) {
  int cells_count = n_ * n_;
  int limit = 1.0 * cells_count / 100 * percentage;
  for (int i = 0; i < n_; i++) {
    for (int j = 0; j < n_; j++) {
      int chance = rand() % cells_count;
      if (chance <= limit) {
        city[i + 1][j + 1].tower.visible = true;
        city[i + 1][j + 1].tower.guess = city[i + 1][j + 1].tower.height;
      }
    }
  }
}

void City::make_people_not_look(int percentage) {
  int people_count = 4 * n_;
  int limit = 1.0 * people_count / 100 * percentage;

  // Top row
  for (int col = 1; col < m_; col++) {
    int chance = rand() % people_count;
    if (chance <= limit) {
      city[0][col].person.is_looking = false;
    }
  }

  // Bottom row
  for (int col = 1; col < m_; col++) {
    int chance = rand() % people_count;
    if (chance <= limit) {
      city[m_ - 1][col].person.is_looking = false;
    }
  }

  // Left column
  for (int row = 1; row < m_; row++) {
    int chance = rand() % people_count;
    if (chance <= limit) {
      city[row][0].person.is_looking = false;
    }
  }

  // Right column
  for (int row = 1; row < m_; row++) {
    int chance = rand() % people_count;
    if (chance <= limit) {
      city[row][m_ - 1].person.is_looking = false;
    }
  }
}

void City::print_easy_puzzle() {
  // ~10% chance that tower will be visible from the start
  make_towers_visible(10);
  print_puzzle();
}

void City::print_hard_puzzle() {
  // ~5% chance that tower will be visible from the start
  make_towers_visible(5);
  // ~20% chance that person won't be looking, therefore there will be no edge clue
  make_people_not_look(20);
  print_puzzle();
}

