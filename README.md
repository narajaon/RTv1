## Description

Rtv1 is RayTracer written in C. It uses a custom library called minilibx wich, you can guess by it’s name, is a minimalist version of the Xlib. Basic shapes are supported, including the sphere, the cone, the cylinder and the plane

## Getting Started

Start by compiling the project using the command `Make`

Then you need to launch the program (replace `scene_file.rt` with an appropriate file)<br>
`./rtv1 scene_file.rt`

Some template scenes are included in ‘scenes’ directory

## Usage

After launching the program, you will see a window showcasing the scene you selected

![alt text](https://github.com/narajaon/RTv1/blob/master/readme_pics/simple_scene.png)

You can then move in the scene in real time

X axis :		`A` or `D` <br>
Y axis :		`W` or `S` <br>
Z axis :		`page up` or `page down` <br>
Reset scene :	`R`
Close window :	`esc`

![alt text](https://github.com/narajaon/RTv1/blob/master/readme_pics/rotation.gif)
![alt text](https://github.com/narajaon/RTv1/blob/master/readme_pics/z_axis.gif)
![alt text](https://github.com/narajaon/RTv1/blob/master/readme_pics/y_axis.gif)

And of course, you can also rotate your POV to look around with the `arrow keys`
