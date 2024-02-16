#include <bits/stdc++.h>
#include "towers.h"
#include "tower.h"
#include "cell.h"
#include "city.h"
#include "person.h"
using namespace std;
typedef long long ll;
#ifdef DEBUG
#include "../template/debug.h"
#else
#define db(x...)
#endif
/*
 * Code that generates games of puzzle called "Towers" (also called "Skyscrapers" on some websites)
 *
 * This is a program mainly made for learning purposes and atm producess correct but non-deterministic puzzle solutions.
 */

int main() {
  // Seed random generator with current time
  srand((unsigned) time(0));

  // Generate and print a new game
  City city(5);
  
  cout << "Easy puzzle: " << "\n";;
  city.print_easy_puzzle();
  cout << "\n";
  
  cout << "Hard puzzle: " << "\n";
  city.print_hard_puzzle();
  cout << "\n";
    
  cout << "Solution: " << "\n";
  city.print_solution();
}