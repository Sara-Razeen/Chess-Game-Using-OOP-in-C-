# Chess Game | C++

A console-based two-player Chess Game developed in C++ using Object-Oriented Programming (OOP) principles. The project implements an interactive chessboard, individual piece movement logic, move validation, turn management, piece capturing, and basic checkmate and stalemate detection.

## Features

- **Interactive Chessboard:** An 8×8 chessboard displayed directly in the console.
- **Two-Player Mode:** Alternating gameplay between White and Black players.
- **Piece Movement:** Individual movement logic for all six chess pieces: King, Queen, Rook, Bishop, Knight, and Pawn.
- **Move Validation:** Validates piece movements, destination squares, and captures.
- **Path Validation:** Prevents pieces with sliding movement from passing through occupied squares.
- **Turn Management:** Automatically switches between players after valid moves.
- **Check Detection:** Identifies when a king is under attack.
- **Checkmate and Stalemate Detection:** Checks whether a player has any legal moves remaining.
- **Console Menu:** Includes options to view instructions, start a game, and exit.

## Technical Implementation

The project applies core Object-Oriented Programming concepts to structure the chess game:

- **Abstraction:** An abstract `Game` base class defines common functionality for chess pieces.
- **Inheritance:** Individual piece classes inherit from the `Game` class.
- **Polymorphism:** Virtual functions implement piece-specific movement validation and identification.
- **Encapsulation:** Class members and methods organize game state and functionality.
- **Dynamic Memory Allocation:** Chess pieces are created and managed dynamically using pointers.
- **Exception Handling:** Handles invalid move attempts.

## Technologies

- C++
- Object-Oriented Programming (OOP)
- Standard C++ Libraries
- Console-based Application

## Getting Started

### Prerequisites

- C++ compiler (GCC or MinGW)
- Terminal or C++ IDE

### Compilation

Compile the source code using:

```bash
g++ main.cpp -o ChessGame
```

### Run

**Windows:**
```bash
ChessGame.exe
```

**Linux:**
```bash
./ChessGame
```

## How to Play

1. Launch the application.
2. Select an option from the main menu:
   - `1` – View game instructions.
   - `2` – Start a new game.
   - `3` – Exit.
3. White makes the first move, followed by Black.
4. Enter the source and destination coordinates when prompted.

### Move Input Format

The game uses a two-digit coordinate system:

- First digit represents the row (1–8).
- Second digit represents the column (1–8).

**Example:**

```text
FROM: 21
TO: 41
```

This represents a move from row 2, column 1 to row 4, column 1.

## Project Structure

```text
Chess-Game/
├── main.cpp
└── README.md
```

## Project Scope

This project focuses on implementing chess gameplay fundamentals and demonstrating OOP concepts in C++. It is an educational implementation and does not cover all official chess rules, including castling, en passant, and pawn promotion.
