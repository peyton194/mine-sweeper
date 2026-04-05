# 🧩 Minesweeper (C++ Console Game)

A fully playable console-based Minesweeper game built in C++ using dynamic memory, recursion, and object-oriented programming.

---

## 🎮 Features

- Interactive text-based Minesweeper gameplay
- Left-click to reveal cells
- Right-click to place/remove flags
- Recursive flood-fill expansion for empty regions
- Win/lose game state detection
- Dynamic 2D board allocation
- File-based board generation

---

## 🧠 How It Works

The game reads a minefield from an input file where:

- `*` represents a mine
- Spaces represent empty cells

The board is dynamically generated and then processed to compute:
- Adjacent mine counts
- Cell states (hidden, revealed, flagged)

---

## 🏗️ Project Structure


board.hpp / board.cpp → Core game board logic
cell.hpp / cell.cpp → Individual cell state handling
text-menu-app.hpp / cpp → Game loop and user interaction
main.cpp → Program entry point