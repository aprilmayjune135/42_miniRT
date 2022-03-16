![alt text](https://user-images.githubusercontent.com/73280726/158613827-8c536687-71fe-4b8f-a59c-0b9eaf3ec5aa.png)
# miniRT
This school project is a `ray tracing` rendering program (using school library `42 MLX`.)

## Features
* This project is written in `C` (based on school requirement).
* Based on scene input _(image size, object/camera position and etc., see [here](#scene-input-file))_, this program will open a window and render the image.
* Keyboard and mouse interactivity are implemented:
* Following basic shapes are implemented:<br />
    `Plane` | `Sphere` | `Cylinder` | `Square` | `Triangle` | `Cube` | `Pyramid` | `Cone`
* Following effects are implemented:<br />
  * Light:
    * Colord and multiple spotlight
    * Ambient lightning
    * Parrele light following a precise direction
  * Color effect:
    * Normal disruption (wave effect)
    * Checkerboard pattern
    * Rainbow effect
    * Sphere texture: uv mapping
    * Bump map texture
  * Color filter

## Usage
This program will render image in a window from a valid scene input file. The rendered window is interactive with keyboard/mouse.

### Run the program
`./run.sh [SCENE_INPUT_FILE]`<br />
`SCENE_INPUT_FILE = "*.rt"`<br />

* File extension has to be `.rt`.
* Input data has to meet the [requirements](#scene-input-file).
* Pre-existing scene files can be found under directory `scene` _(no need to add `./scene/` for these files when passing as an argument)_.

### Window Interactivity
It is possible to interactive with the scene through keyboard and mouse:
* Move viewer perspective from keyboard:
  * up: ⬆️ or `w`
  * down: ⬇️ or `s`
  * left: ⬅️ or `a`
  * right: ➡️ or `d`
  * forward: `e`
  * backward: `q`
* Move viewer perspective from mouse click:
  * `one left click` on any position inside the window
* Switch camera _(if multiple camera positions are provided in the input file)_:
  * keyboard `c` 
* Close window:
  * Mouse click on ❌ at the window corner
  * Keyboard `esc`

### Scene Input File
* It will contain the window/rendered image size, which implies your miniRT
must be able to render in any positive size.
* Each type of element can be separated by one or more line break(s).
* Each type of information from an element can be separated by one or more
space(s).
* Each type of element can be set in any order in the file.
* Elements which are defined by a capital letter can only be declared once in
the scene.
* Each element first’s information is the type identifier (composed by one or two
character(s)), followed by all specific information for each object in a strict
order such as:
  * **Resolution**: `R 1920 1080`
    * identifier: R
    * x render size
    * y render size
  * **Ambient** lightning: `A 0.2 255,255,255`
    * identifier: A
    * ambient lighting ratio in range [0.0,1.0]: 0.2
    * R,G,B colors in range [0-255]: 255, 255, 255
  * **Camera**: `c -50.0,0,20 0,0,1 70`
    * identifier: c
    * x,y,z coordinates of the view point: 0.0,0.0,20.6
    * 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
    * FOV : Horizontal field of view in degrees in range [0,180]
  * **Light**: `l -40.0,50.0,0.0 0.6 10,0,255`
    * identifier: l
    * x,y,z coordinates of the light point: 0.0,0.0,20.6
    * the light brightness ratio in range [0.0,1.0]: 0.6
    * R,G,B colors in range [0-255]: 10, 0, 255
  * **Sphere**: `sp 0.0,0.0,20.6 12.6 10,0,255`
    * identifier: sp
    * x,y,z coordinates of the sphere center: 0.0,0.0,20.6
    * the sphere diameter: 12.6
    * R,G,B colors in range [0-255]: 10, 0, 255
  * **Plane**: `pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225`
    * identifier: pl
    * x,y,z coordinates: 0.0,0.0,-10.0
    * 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0
    * R,G,B colors in range [0-255]: 0, 0, 255
  * **Square**: `sq 0.0,0.0,20.6 1.0,0.0,0.0 12.6 255,0,255`
    * identifier: sq
    * x,y,z coordinates of the square center: 0.0,0.0,20.6
    * 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
1.0,0.0,0.0
    * side size: 12.6
    * R,G,B colors in range [0-255]: 255, 0, 255
  * **Cylinder**: `cy 50.0,0.0,20.6 0.0,0.0,1.0 10,0,255 14.2 21.42`
    * identifier: cy
    * x,y,z coordinates: 50.0,0.0,20.6
    * 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
    * the cylinder diameter: 14.2
    * the cylinder height: 21.42
    * R,G,B colors in range [0,255]: 10, 0, 255
  * **Triangle**: `tr 10.0,20.0,10.0 10.0,10.0,20.0 20.0,10.0,10.0 0,0,255`
    * identifier: tr
    * x,y,z coordinates of the first point: 10.0,20.0,10.0
    * x,y,z coordinates of the second point: 10.0,10.0,20.0
    * x,y,z coordinates of the third point: 20.0,10.0,10.0
    * R,G,B colors in range [0,255]: 0, 255, 255
