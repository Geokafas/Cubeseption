# Cubeseption
a simple 3d opengl game

This game was created in Opengl, using the glut toolkit. It is a simple 3d game where the player tries to reach the top of the map by climbing from cube to cube. Be aware, fall damage is enabled!
![alt tag](https://cloud.githubusercontent.com/assets/10997512/20861655/f71c95b2-b99d-11e6-8157-00091d2afe80.PNG)
W,S,D,A to move around, right click to add a new cube and left click to kick one around. 'E' deletes all the cubes in font of you (all cubes in the Y axis), 'Q' does the same thing only this time is for the cube right in front of you (in the same Y axis as the player).
![alt tag](https://cloud.githubusercontent.com/assets/10997512/20861656/f9b36c9c-b99d-11e6-9415-55821c9a5fb1.PNG)
'R' lowers by one level all the unsupported cubes, in other words every cube that doesn't have another cube beneath it drops 1 unit each time you press 'R'. Finally 'space', well space increases your cube stock so you can spawn more by clicking around.


GETING STARTED:

1) Download the source files

2) Complile your program using the following terminal command inside the game directory : make

3) Make sure you you have instaled the freeglut library on your machine, if you are using a linux distribution. Else i suggest you make a project in visual studio, include the necessary libraries and this source code, and then run it
