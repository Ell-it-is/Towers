using namespace std;
typedef enum { TOWER, PERSON, NONE } CellType;

class Tower {
private:
public:
  int height;
  int guess; // non-zero value means the player guessed a height
  bool visible; // visible towers cannot be guessed and have assigned height from the start
  bool is_guess_correct();
};

class Person {
private:
public:
  int towers_counted;
  bool is_looking; // when 'Person' is looking -> player see how many towers 'Person' counted
  int count_towers(const vector<int>& t);
};

class Cell {
private:
  int x_;
  int y_;
  void set_coord(int x, int y);
public:
  CellType type;
  Tower tower;
  Person person;
  Cell();
  Cell(pair<int, int> coord, int height, int guess, bool visible);
  Cell(pair<int, int> coord, int towers_counted, bool is_looking);
  bool is_valid(const vector<vector<Cell>>& towers);
};

class City {
private:
  int n_; // towers dimensions
  int m_; // city dimensions
  vector<vector<Cell>> towers;
  vector<vector<Cell>> city;
  void construct_towers();
  void build_city_with_towers();
  void populate();
  void invalidate_corners();
  void print_puzzle();
  void make_towers_visible(int percentage);
  void make_people_not_look(int percentage);
public:
  City(int n);
  void print_solution();
  void print_easy_puzzle();
  void print_hard_puzzle();
  bool is_solution_correct();
};