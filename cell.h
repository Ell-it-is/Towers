using namespace std;

Cell::Cell() {}

Cell::Cell(pair<int, int> coord, int height, int guess, bool visible) {
  type = TOWER;
  tower.height = height;
  tower.guess = guess;
  tower.visible = visible;
  set_coord(coord.first, coord.second);
}

Cell::Cell(pair<int, int> coord, int towers_counted, bool is_looking) {
  type = PERSON;
  person.towers_counted = towers_counted;
  person.is_looking = is_looking;
  set_coord(coord.first, coord.second);
}

void Cell::set_coord(int x, int y) {
  x_ = x;
  y_ = y;
}

// Checks whether the guessed value is unique accross rows / columns
bool Cell::is_valid(const vector<vector<Cell>>& towers) {
  // if visible -> check against height
  // if invisible -> check against non-zero guess
  int n = towers.size();
  int cell_height = 0;
  if (towers[x_][y_].tower.visible) cell_height = towers[x_][y_].tower.height;
  else cell_height = towers[x_][y_].tower.guess;
    
  for (int i = 0; i < n; i++) {
    Tower t = towers[x_][i].tower;
    if (i == y_) continue;

    int h = 0;
    if (t.visible) h = t.height;
    else h = t.guess;

    if (h == cell_height) return false;
  }
  for (int i = 0; i < n; i++) {
    Tower t = towers[i][y_].tower;
    if (i == x_) continue;

    int h = 0;
    if (t.visible) h = t.height;
    else h = t.guess;

    if (h == cell_height) return false;
  }
  return true;
}


















