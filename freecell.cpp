#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <string>
#include <list>
#include <vector>

using namespace std;


enum CARDS {
  KIER = 1,
  KARO,
  PIK,
  TREFL
};

enum COLORS {
  BLACK = false,
  RED = true
};


class card_t {
private:
  CARDS type;
  unsigned short int value;
public:
  bool getColor () {return type <= 2;}
  CARDS getType () {return type;}
  unsigned short int getValue () {return value;}
  void setType (CARDS _type) {type = _type;}
  void setValue (unsigned short int _value) {value = _value;}
  card () {}
  card (CARDS _type, unsigned short int _value) {
    type = _type;
    value = _value;
  }
};

void drawSymbol (CARDS card) {
  SetConsoleOutputCP(CP_UTF8);
  wchar_t s[2];
  switch (card) {
    case KIER:
      s[0] = L'♥';
      break;
    case KARO:
      s[0] = L'♦';
      break;
    case PIK:
      s[0] = L'♠';
      break;
    case TREFL:
      s[0] = L'♣';
      break;
  }
  s[1] = '\0';
  int bufferSize = WideCharToMultiByte(CP_UTF8, 0, s, -1, NULL, 0, NULL, NULL);
  char* m = new char[bufferSize];
  WideCharToMultiByte(CP_UTF8, 0, s, -1, m, bufferSize, NULL, NULL);
  wprintf(L"%S", m);
  SetConsoleOutputCP(869);
}


char getValueChar (unsigned short int value) {
  switch (value) {
    case 1:
      return 'A';
    case 11:
      return 'J';
    case 12:
      return 'Q';
    case 13:
      return 'K';
    default:
      return static_cast<char>(value) + '0';
  }
}

class game_t {
public:
  vector<card_t> board[8];
  card_t target[4];
  card_t aux[4];    // auxiliary
  void draw () {

    bool endDrawing = false;
    for (size_t i = 0; !endDrawing; i++) {
      endDrawing = true;

      for (size_t j = 0; j < 8; j++) {
        if (board[j].size() > i) {
          endDrawing = false;
          cout << static_cast<char>(201);
          for (size_t k = 0; k < 9; k++) {
            cout << static_cast<char>(205);
          }
          cout << static_cast<char>(187);
        } else {
          cout << "           ";
        }

      }

      cout << endl;

      for (size_t j = 0; j < 8; j++) {
        if (board[j].size() > i) {
          endDrawing = false;
          cout << static_cast<char>(186) << "   ";
          if (board[j][i].getValue() == 10)
            cout << setw(2) << 10;
          else
            cout << setw(2) << getValueChar(board[j][i].getValue());
          drawSymbol(board[j][i].getType());
          cout << "   " << static_cast<char>(186);
        } else {
          cout << "           ";
        }
      }
      cout << endl;
    }
  }
};


int main(int argc, char const *argv[]) {
  game_t game;


  // **testing set**
  card_t exampleCard;
  for (size_t i = 0; i < 4; i++) {
    exampleCard.setType(static_cast<CARDS>(i+1));
    for (size_t j = 7; j > 0; j--) {
      exampleCard.setValue(j);
      game.board[i].push_back(exampleCard);
    }
  }
  for (size_t i = 4; i < 8; i++) {
    exampleCard.setType(static_cast<CARDS>(i-3));
    for (size_t j = 13; j > 7; j--) {
      exampleCard.setValue(j);
      game.board[i].push_back(exampleCard);
    }
  }

  exampleCard.setType(PIK);
  exampleCard.setValue(10);
  game.board[2].push_back(exampleCard);
  // *****************
  game.draw();




  return 0;
}
