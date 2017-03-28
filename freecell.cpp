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


char mark (unsigned short int x, unsigned short int y, unsigned short int pos_x, unsigned short int pos_y, unsigned short int pos_x_marked, unsigned short int pos_y_marked, bool marked) {
  if (x == pos_x && y == pos_y) {
    if (marked) {
      if (pos_x == pos_x_marked && pos_y == pos_y_marked) {
        return static_cast<char>(178);
      } else {
        return static_cast<char>(176);
      }
    } else {
      return static_cast<char>(176);
    }
  } else {
    if (marked && x == pos_x_marked && y == pos_y_marked) {
      return static_cast<char>(177);
    } else {
      return ' ';
    }
  }
}


class graphics_t {
public:
  void init () {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    //MoveWindow(window_handle, x, y, width, height, redraw_window);
    MoveWindow(console, r.left, r.top, 800, 600, TRUE);
  }
};

class game_t {
public:
  vector<card_t> board[8];
  card_t target[4];
  card_t aux[4];    // auxiliary

  void init () {
    // **testing set**
    card_t exampleCard;
    for (size_t i = 0; i < 4; i++) {
      exampleCard.setType(static_cast<CARDS>(i+1));
      for (size_t j = 7; j > 0; j--) {
        exampleCard.setValue(j);
        board[i].push_back(exampleCard);
      }
    }
    for (size_t i = 4; i < 8; i++) {
      exampleCard.setType(static_cast<CARDS>(i-3));
      for (size_t j = 13; j > 7; j--) {
        exampleCard.setValue(j);
        board[i].push_back(exampleCard);
      }
    }

    exampleCard.setType(PIK);
    exampleCard.setValue(10);
    board[2].push_back(exampleCard);
  }
  void draw (unsigned short int x, unsigned short int y, unsigned short int x_marked, unsigned short int y_marked, bool marked) {
    for (size_t i = 0; i < 8; i++) {
      cout << static_cast<char>(201);
      for (size_t k = 0; k < 9; k++) {
        cout << static_cast<char>(205);
      }
      cout << static_cast<char>(187);
    }
    cout << endl;

    for (size_t j = 0; j < 8; j++) {
      cout << static_cast<char>(186);
      for (size_t k = 0; k < 3; k++) {
        cout << static_cast<char>(mark(j, 0, x, y, x_marked, y_marked, marked));
      }
      cout << "XXX";
      for (size_t k = 0; k < 3; k++) {
        cout << static_cast<char>(mark(j, 0, x, y, x_marked, y_marked, marked));
      }
      cout << static_cast<char>(186);
    }
    cout << endl;

    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 8; j++) {
        cout << static_cast<char>(186);
        for (size_t k = 0; k < 9; k++) {
          cout << static_cast<char>(mark(j, 0, x, y, x_marked, y_marked, marked));
        }
        cout << static_cast<char>(186);
      }
      cout << endl;
    }

    for (size_t i = 0; i < 8; i++) {
        cout << static_cast<char>(200);
        for (size_t k = 0; k < 9; k++) {
          cout << static_cast<char>(205);
        }
        cout << static_cast<char>(188);
      }
    cout << endl;

    bool endDrawing = false;

    size_t i = 0;

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
          if (i - 2 <= board[j].size()) {
            endDrawing = false;
            if (i - 2 < board[j].size()) {
              cout << static_cast<char>(186);
              for (size_t k = 0; k < 9; k++) {
                cout << static_cast<char>(mark(j, i, x, y, x_marked, y_marked, marked));
              }
              cout << static_cast<char>(186);
            }else{
              cout << static_cast<char>(200);
              for (size_t k = 0; k < 9; k++) {
                cout << static_cast<char>(205);
              }
              cout << static_cast<char>(188);
            }
          }else{
            cout << "           ";
          }
        }
      }

      cout << endl;

      for (size_t j = 0; j < 8; j++) {
        if (board[j].size() > i) {
          endDrawing = false;
          cout << static_cast<char>(186);
          for (size_t k = 0; k < 3; k++) {
            cout << static_cast<char>(mark(j, i + 1, x, y, x_marked, y_marked, marked));
          }
          if (board[j][i].getValue() == 10)
            cout << setw(2) << 10;
          else
            cout << setw(2) << getValueChar(board[j][i].getValue());
          drawSymbol(board[j][i].getType());
          for (size_t k = 0; k < 3; k++) {
            cout << static_cast<char>(mark(j, i + 1, x, y, x_marked, y_marked, marked));
          }
          cout << static_cast<char>(186);
        } else {
          if (i - 2 < board[j].size()) {
            endDrawing = false;
            cout << static_cast<char>(186) << "         " << static_cast<char>(186);
          }else{
            cout << "           ";
          }
        }
      }
      cout << endl;
    }
  }
  void loop () {

  }
};


int main(int argc, char const *argv[]) {
  game_t game;
  graphics_t graphics;

  game.init();
  graphics.init();

  unsigned short int x = 0;
  unsigned short int y = 0;
  unsigned short int x_marked = 0;
  unsigned short int y_marked = 0;
  bool marked = false;
  char c;
  game.draw(x, y, x_marked, y_marked, marked);
  while (1) {
    c = getch();
    switch (c) {
      case 'w':
        y--;
        break;
      case 's':
        y++;
        break;
      case 'a':
        x--;
        break;
      case 'd':
        x++;
        break;
      case ' ':
      if (marked && x == x_marked && y == y_marked) {
        marked = false;
      } else {
        marked = true;
        x_marked = x;
        y_marked = y;
      }
        break;
    }
    system("cls");
    game.draw(x, y, x_marked, y_marked, marked);
  }



  return 0;
}
