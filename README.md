Breakout Game - OpenGL
A classic Breakout arcade game implementation using OpenGL and GLUT with modern C++.

🎮 Features
Classic Gameplay: Break bricks with a ball and paddle

Smooth Controls: Keyboard-controlled paddle movement

Physics System: Realistic ball bouncing and collision detection

Score Tracking: Live score display

Game States: Win/lose conditions with menu system

Pause Functionality: Start/stop game with 'P' key

🛠️ Controls
A / D or ← / →: Move paddle left/right

P: Pause/Resume game

ENTER: Select menu options

↑ / ↓: Navigate menu (in game over state)

ESC: Exit game

🏗️ Technical Details
Language: C++

Graphics: OpenGL with GLUT

Libraries: GLEW, FreeGLUT

Physics: Collision detection with clamping

Architecture: Object-oriented with struct-based brick system

🚀 How to Build
Prerequisites
Visual Studio with C++ support

OpenGL development libraries

GLEW and FreeGLUT

Compilation
bash
# Compile with OpenGL and GLUT linked
g++ -o breakout main.cpp -lglew32 -lfreeglut -lopengl32 -lglu32
🎯 Game Rules
Break all bricks to win

Don't let the ball fall below the paddle

Score increases with each brick destroyed

Ball angle changes based on paddle hit position

📁 Project Structure
main.cpp - Main game logic and rendering

Brick management system with vector container

State machine for game flow control

Menu system for restart/quit options

💡 Features Implementation
Clamp function for boundary management

Collision detection with bricks and paddle

Velocity-based ball movement

Responsive paddle controls with boundary checking

Perfect for learning game development with OpenGL and understanding 2D game physics!
