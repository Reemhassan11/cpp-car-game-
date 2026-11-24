# 🏎️ C++ Car Racing Game

A 2D car racing game developed using **C++ and SFML 3**.

This project is a simple racing game where the player controls a car, avoids incoming traffic, and tries to achieve the highest possible score. The game gradually increases in speed as time passes, making it more challenging.

## 🎮 Game Features

- Player-controlled car movement.
- Multiple traffic cars with different colors.
- Detailed road and background scenery.
- Moving road markings and roadside trees.
- Increasing game speed over time.
- Collision detection.
- Score tracking.
- Game over screen and restart functionality.

## 🕹️ Controls

| Key | Action |
|---|---|
| ← / A | Move left |
| → / D | Move right |
| R | Restart the game |

## 🖼️ Screenshots

### Gameplay

![Game Screenshot 1](Screenshot%202026-11-24%20230907.png)

![Game Screenshot 2](Screenshot%202026-11-24%20230922.png)

![Game Screenshot 3](Screenshot%202026-11-24%20230944.png)

![Game Screenshot 4](Screenshot%202026-11-24%20230951.png)

![Game Screenshot 5](Screenshot%202026-11-24%20231003.png)

![Game Screenshot 6](Screenshot%202026-11-24%20231014.png)

## 🛠️ Technologies Used

- **C++** — Main programming language.
- **SFML 3** — Graphics, window management, and game interaction.
- **Visual Studio Code** — Development environment.
- **MSYS2 UCRT64 / GCC** — C++ compiler.

## ⚙️ How to Run

### Requirements

- Windows
- GCC compiler
- SFML 3
- MSYS2 UCRT64

### Installation

Install SFML using MSYS2 UCRT64:

```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

### Compile

Navigate to the project directory and run:

```bash
g++ -std=c++17 game.cpp -o game.exe -lsfml-graphics -lsfml-window -lsfml-system
```

### Run

```bash
./game.exe
```

## 📚 What I Learned

Through this project, I practiced:

- C++ programming and object-oriented concepts.
- Working with the SFML graphics library.
- Creating and managing game objects.
- Handling keyboard input and events.
- Implementing collision detection.
- Using game loops and time-based movement.
- Managing speed, scoring, and game states.

## 👩‍💻 Author

**Reem Hassan**

GitHub: [@Reemhassan11](https://github.com/Reemhassan11)

---

*This project was created as part of my journey in learning C++ programming and game development.*
