#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

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


class card {
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


void drawSymbol (int number) {
  wchar_t s[2];
  switch (number) {
    case 1:
      s[0] = L'♥';
      break;
    case 2:
      s[0] = L'♦';
      break;
    case 3:
      s[0] = L'♠';
      break;
    case 4:
      s[0] = L'♣';
      break;
  }
  s[1] = '\0';
  int bufferSize = WideCharToMultiByte(CP_UTF8, 0, s, -1, NULL, 0, NULL, NULL);
  char* m = new char[bufferSize];
  WideCharToMultiByte(CP_UTF8, 0, s, -1, m, bufferSize, NULL, NULL);
  wprintf(L"%S", m);
}


int main(int argc, char const *argv[]) {
  SetConsoleOutputCP(CP_UTF8);
  drawSymbol(1);
  drawSymbol(2);
  drawSymbol(3);
  drawSymbol(4);
  return 0;
}
