using namespace std;

// Checks whether guessed height is the same as correct height
bool Tower::is_guess_correct() {
  if (visible) return true;
  if (!visible && guess != 0) {
    if (guess == height) return true;
  }
  return false;
}