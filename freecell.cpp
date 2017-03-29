#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
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


class game_t {
public:
  unsigned short int cursor_x = 0;
  unsigned short int cursor_y = 0;
  unsigned short int cursor_marked_x = 0;
  unsigned short int cursor_marked_y = 0;
  bool cursor_marked = false;

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

  void loop () {
    char c = getch();
    switch (c) {
      case 'w':
        cursor_y--;
        break;
      case 's':
        cursor_y++;
        break;
      case 'a':
        cursor_x--;
        break;
      case 'd':
        cursor_x++;
        break;
      case ' ':
      if (cursor_marked && cursor_x == cursor_marked_x && cursor_y == cursor_marked_y) {
        cursor_marked = false;
      } else {
        cursor_marked = true;
        cursor_marked_x = cursor_x;
        cursor_marked_y = cursor_y;
      }
        break;
    }
    // system("cls");

  }
};


class graphics_t {
private:
  game_t* game;
  char mark (unsigned short int x, unsigned short int y) {
    unsigned short int pos_x = game->cursor_x;
    unsigned short int pos_y = game->cursor_y;
    unsigned short int pos_x_marked = game->cursor_marked_x;
    unsigned short int pos_y_marked = game->cursor_marked_y;
    bool marked = game->cursor_marked;


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
public:
  void init (game_t* _game) {
    game = _game;
    HWND console = GetConsoleWindow();
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    RECT r;

    GetWindowRect(console, &r); //stores the console's current dimensions
    //MoveWindow(window_handle, x, y, width, height, redraw_window);
    MoveWindow(console, r.left, r.top, 800, 600, TRUE);
    // cout << "graphics Init " << _game->board[1][1].getType() << endl;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
  }
  void goToStart() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD CursorPosition;
    CursorPosition.X = 0;
    CursorPosition.Y = 0;
    SetConsoleCursorPosition(console,CursorPosition);
  }
  void draw () {
    unsigned short int x = game->cursor_x;
    unsigned short int y = game->cursor_y;
    unsigned short int x_marked = game->cursor_marked_x;
    unsigned short int y_marked = game->cursor_marked_y;
    bool marked = game->cursor_marked;

    goToStart();

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
        cout << static_cast<char>(mark(j, 0));
      }
      cout << "XXX";
      for (size_t k = 0; k < 3; k++) {
        cout << static_cast<char>(mark(j, 0));
      }
      cout << static_cast<char>(186);
    }
    cout << endl;

    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 8; j++) {
        cout << static_cast<char>(186);
        for (size_t k = 0; k < 9; k++) {
          cout << static_cast<char>(mark(j, 0));
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
        if (game->board[j].size() > i) {
          endDrawing = false;
          cout << static_cast<char>(201);
          for (size_t k = 0; k < 9; k++) {
            cout << static_cast<char>(205);
          }
          cout << static_cast<char>(187);
        } else {
          if (i - 2 <= game->board[j].size()) {
            endDrawing = false;
            if (i - 2 < game->board[j].size()) {
              cout << static_cast<char>(186);
              for (size_t k = 0; k < 9; k++) {
                cout << static_cast<char>(mark(j, i));
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
        if (game->board[j].size() > i) {
          endDrawing = false;
          cout << static_cast<char>(186);
          for (size_t k = 0; k < 3; k++) {
            cout << static_cast<char>(mark(j, i + 1));
          }
          if (game->board[j][i].getValue() == 10)
            cout << setw(2) << 10;
          else
            cout << setw(2) << getValueChar(game->board[j][i].getValue());
          drawSymbol(game->board[j][i].getType());
          for (size_t k = 0; k < 3; k++) {
            cout << static_cast<char>(mark(j, i + 1));
          }
          cout << static_cast<char>(186);
        } else {
          if (i - 2 < game->board[j].size()) {
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
};


int main(int argc, char const *argv[]) {
  game_t game;
  graphics_t graphics;

  game.init();
  graphics.init(&game);

  graphics.draw();
  while (1) {
    game.loop();
    graphics.draw();
  }

  return 0;
}
