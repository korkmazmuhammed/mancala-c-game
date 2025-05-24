# Mancala C Game

This project is a terminal-based Mancala (sowing stones) game implemented in C, where a user plays against the computer. The game board and logic are designed according to traditional rules.

## Features

- 2-player mode: User vs. Computer
- 12 cups and 2 big stores (1 for each player), initial stones as per classic rules
- Visual board with current stone counts
- Intelligent computer opponent (basic AI move selection)
- Game ends when one side's cups are empty, winner is declared based on points in stores

## How to Play

1. Compile the code:
    ```bash
    gcc 220104004043.c -o mancala
    ```
2. Run the program:
    ```bash
    ./mancala
    ```
3. Follow on-screen instructions:
    - User always starts
    - Enter a cup number (1-6) on your side to make a move
    - Computer will play automatically on its turn
    - The board updates after each move

## Rules

- On your turn, pick one of your cups (1-6) to move all stones, dropping one into each subsequent cup (and your big store).
- If your last stone lands in your big store, you get another turn.
- The game ends when one side has no stones left in their cups.
- The player with the most stones in their store wins.

## Example Output

