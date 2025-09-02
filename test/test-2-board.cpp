#include "../board.hpp"
#include "../cell.hpp"
#include "board-configurations.hpp"
#include "catch/catch.hpp"

TEST_CASE("Test 4x4 board") {
  Board b;

  CHECK(!b.load("badFile.txt"));  // fail to load a non-existing file
  CHECK(b.load("test/4x4.in"));  // file opened successfully
  CHECK(NOTHING_CLICKED_4x4 == b.str());  // original state of the board
}

TEST_CASE("Test 5x5 board") {
  Board b;

  CHECK(!b.load("badFile.txt"));  // fail to load a non-existing file
  CHECK(b.load("test/5x5.in"));  // file opened successfully
  CHECK(NOTHING_CLICKED_5x5 == b.str());  // original state of the board
}
