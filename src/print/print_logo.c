#include "print.h"

static char* logo[] = {
  " .-----------. .--------------. .-----------. .--------------. .--------------.",
  "|  ______    | |  _______     | |   _____   | |     ______   | |  ___  ____   |",
  "| |_   _ \\   | | |_   __ \\    | |  |_   _|  | |   .' ___  |  | | |_  ||_  _|  |",
  "|   | |_) |  | |   | |__) |   | |    | |    | |  / .'   \\_|  | |   | |_/ /    |",
  "|   |  __ \\  | |   |  __ /    | |    | |    | |  | |         | |   |  __'.    |",
  "|  _| |__) | | |  _| |  \\ \\_  | |   _| |_   | |  \\ `.___.'\\  | |  _| |  \\ \\_  |",
  "| |_______/  | | |____| |___| | |  |_____|  | |   `._____.'  | | |____||____| |",
  "|            | |              | |           | |              | |              |",
  "\\-----------/ \\--------------/ \\-----------/ \\--------------/ \\--------------/",
  "\\.---------------.                                .-----------------------./",
  "                  \\.-------------. .------------./",
  "                   |     ___     | |    _____   |",
  "                   |   .'   '.   | |  /  __  |  |",
  "                   |  /  / \\  \\  | |  | (_ \\_|  |",
  "                   |  | |   | |  | |  '.__`-.   |",
  "                   |  \\  \\_/  /  | |   ____) |  |",
  "                   |   `.___.'   | |  \\_____.'  |",
  "                   |             | |            |",
  "                    \\-----------/   \\----------/",
};

void print_logo() {
  for (int i = 0; i < sizeof(logo) / sizeof(logo[0]); i++) {
    println(logo[i]);
  }
  println("BrickOS");
  println("Version 1.0");
  println("Copyright (C) 2023");
  println(__DATE__);
}
