<h2>Nibbler</h2>

This project is a simple snake game written in C++, but with three different GUIs loaded as dynamic libraries which are used to render the game. The goal is to make each GUI behave like an independent plugin and keep all renderering/graphics logic out of the main executable.

<h3>Features</h3>

* A wireframe 2D GUI
* A textured 2D GUI
* A 3D (all primitives) GUI
* Seamless switching between GUIs with 1-3 keys
* Scoring system
* Pause menu
* Gameover screen with Restart
* Obstacles
* Music and Sounds
* Resizable window

<h3>Controls</h3>

Move with arrow keys

Pause with esc key

Switch to respective renderer with 1, 2, 3 keys

<h3>Running and Compiling</h3>

Run "make" and an executable will be created. Type "export DYLD_LIBRARY_PATH=lib" to set up the env. Run "./Nibbler" and enjoy the game!

<h3>Gameplay Demo</h3>

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/3PxN0nGZwIg/0.jpg)](https://youtu.be/3PxN0nGZwIg)

<h3>Screenshots</h3>

![alt-text](https://github.com/dylanmpeck/Nibbler/blob/master/screenshots/renderer2.png "Renderer 2")
![alt-text](https://github.com/dylanmpeck/Nibbler/blob/master/screenshots/renderer3.png "Renderer 3")
![alt-text](https://github.com/dylanmpeck/Nibbler/blob/master/screenshots/renderer1.png "Renderer 1")
