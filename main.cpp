//
// Created by ivan on 12/5/23.
//

#include "render/pixmap.h"

int main() {
  Pixmap pixmap(500, 500, Color(255, 0, 0));
  pixmap.write_to_stdout();
  return 0;
}
