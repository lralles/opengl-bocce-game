# OpenGL Bocce Game

A 3D bocce game built in C++ with OpenGL 3.3. It features textured OBJ models, lighting, a playable court, ball physics, gravity, drag, wall collisions, and ball-to-ball collisions.

## Graphics pipeline

The project implements the complete real-time rendering pipeline, from loading 3D models and textures to displaying the final image:

1. OBJ models are loaded and converted into vertex data containing positions, normals, and texture coordinates.
2. OpenGL stores this data in vertex buffers and vertex array objects.
3. Model, view, and projection matrices transform each vertex from local model space to screen space.
4. The vertex shader performs these transformations and passes normals, positions, and texture coordinates to the next stage.
5. OpenGL rasterizes the triangles into fragments (potential pixels).
6. The fragment shader applies textures and directional lighting to calculate each fragment's color.
7. Depth testing ensures that objects closer to the camera hide objects behind them before the final image is presented.

The camera uses perspective or orthographic projection, while the game loop updates ball physics and redraws the scene every frame.

## Physics

Physics is updated once per frame using the elapsed time (`delta time`) since the previous frame. This keeps movement approximately independent of the rendering frame rate. The current time step is scaled to make the motion more visible.

Each ball is updated with:

- Gravity while it is above the floor.
- A bounce when it hits the floor, followed by drag while rolling.
- Wall checks that reverse its horizontal velocity at the court boundaries.
- Pairwise collision checks between balls that have already been thrown.

When two balls overlap, `applyCollision` calculates a simplified elastic collision using their positions and velocities, then updates both velocities. The physics loop is variable-timestep: one update is performed for each rendered frame rather than using a fixed tick rate.

The main equations used by the simulation are:

```text
Position integration:  p(t + Δt) = p(t) + v(t) · Δt

Gravity:               v_y(t + Δt) = v_y(t) - g · Δt

Rolling drag:          |v_xz|' = max(0, |v_xz| - d · Δt)

Collision condition:   ||p₁ - p₂|| ≤ r₁ + r₂
```

For a ball collision, the velocity component along the collision normal is exchanged:

```text
n  = p₁ - p₂
v₁' = v₁ - ((v₁ - v₂) · n / ||n||²) · n
v₂' = v₂ - ((v₂ - v₁) · (-n) / ||n||²) · (-n)
```

Here, `g` is the gravity constant, `d` is the rolling-drag constant, `p` is position, `v` is velocity, and `r` is the ball radius. The floor bounce applies a restitution factor to the vertical velocity, approximately `v_y' = -0.3 · v_y`.

## Requirements

- Linux
- C++11 compiler and GNU Make
- OpenGL 3.3
- GLFW, GLAD, GLM, TinyOBJLoader, and `stb_image`
- GLFW library at `lib-linux/libglfw3.a`

## Build and run

```bash
make
make run
```

The executable is created at `bin/Linux/main`. Run it with `make run` so the relative paths to the shaders and assets work correctly.

Clean the build with:

```bash
make clean
```

## How to play

The game uses one white target ball and six player balls. Adjust the throw direction with `A` and `D`, charge the throw with left-click, and release the ball with right-click. Balls are affected by gravity, friction, wall boundaries, and elastic collisions. After all balls are thrown, the winner is printed in the terminal.

## Controls

| Input | Action |
| --- | --- |
| `A` / `D` | Move the throw direction left / right |
| Left mouse button | Increase throw power |
| Right mouse button | Throw the current ball |
| Mouse wheel | Zoom |
| `P` / `O` | Perspective / orthographic projection |
| `H` | Toggle the information overlay |
| `R` | Reload shaders |
| `Esc` | Exit |

## Project structure

```text
data/       Models and textures
include/    Headers and bundled libraries
src/        Game logic, rendering, physics, and shaders
Makefile    Linux build commands
```
