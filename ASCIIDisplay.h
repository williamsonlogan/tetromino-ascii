/* Copyright (C) 2017 Logan Williamson - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license, and this disclaimer must
 * remain in this source file while code is being used.
 */

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// Size of the display buffer
#define ScreenWidth 80
#define ScreenHeight 23

class ASCIIDisplay {
public:
  // Constructor, essentially just sets the resolution variables
  ASCIIDisplay() {
    xres = ScreenWidth;
    yres = ScreenHeight;
    Clear();
  }

  // Clears the display buffer, but not the screen
  void Clear() {
    memset(charBuffer, ' ', sizeof(charBuffer[0][0]) * xres * yres);
  }

  // Sets a character with spaces at a given point in the buffer
  void charSet(char c, int xpoint, int ypoint, bool spaces = false) {
    if (!withinBounds(xpoint, ypoint))
      return;

    if (c != ' ' || spaces)
      charBuffer[ypoint][xpoint] = c;
  }

  // Sets an entire string at a given point in the buffer
  void Print(string s, int xpoint, int ypoint, bool spaces = false) {
    // Don't knoe the complexity of string::length so storing it in case it's O(N)
    int sLen = s.length();

    // Make sure that the point is within the character buffer bounds
    if (!withinBounds(xpoint, ypoint) || !withinBounds(xpoint + sLen, ypoint))
      return;

    for (int i = 0; i < sLen; i++)
      if (s[i] != ' ' || spaces)
	charBuffer[ypoint][xpoint + i] = s[i];
  }

  // Creates a box, for use with dialogues
  void CreateDialogue(int xdim, int ydim, int xpoint, int ypoint) {
    for (int y = 0; y < ydim; y++) {
      if (y == 0) {
        charSet('/', xpoint, ypoint + y);
        for (int i = 1; i < (xdim); i++) {
          charSet('=', xpoint + i, ypoint + y);
        }
        charSet('\\', xpoint + xdim - 1, ypoint + y);
      } else if (y == ydim - 1) {
        charSet('\\', xpoint, ypoint + y);
        for (int i = 1; i < (xdim); i++) {
          charSet('-', xpoint + i, ypoint + y);
        }
        charSet('/', xpoint + xdim - 1, ypoint + y);
      } else {
        charSet('|', xpoint, ypoint + y);
        for (int i = 1; i < (xdim); i++) {
          charSet(' ', xpoint + i, ypoint + y, true);
        }
        charSet('|', xpoint + xdim - 1, ypoint + y);
      }
    }
  }

  // Redraws the buffer to the screen
  void draw() {
    clrscrn();
    for (int y = 0; y < yres; y++) {
      for (int x = 0; x < xres; x++) {
        cout << charBuffer[y][x];
      }
      cout << endl;
    }
  }

private:
  // Clears the screen
  void clrscrn() {
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif
  }

  // Returns whether or not the point is within the bounds of charBuffer
  bool withinBounds(int x, int y)
  {
	return (x >= 0) && (x < xres) &&
	       (y >= 0) && (y < yres);
  }

  int xres, yres;
  char charBuffer[ScreenHeight][ScreenWidth];
};
