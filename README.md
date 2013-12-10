# Black Hole Simulation

view this file formatted nicely at: https://github.com/ridler/glBlackHole/blob/master/README.md

## How to run the program:

The project can be compiled and run using the "Run" button on Qt Creator.  qmake hasn't worked for me from the command line, but "make" does.

The interaction is intuitive: you can move the viewing angles by clicking and dragging in the display area, and you can switch modes by clicking the buttons on the right side of the main window.  Zooming is accomplished by scrolling.  I do not recommend trying to change the viewing angles or zooming while in the object riding mode.

When in merging mode, the action may take a few seconds to start, so be patient.

The most fun mode is the mode called "ride an object."  You can ride the red star or the lower-mass merging black hole in each respective mode.

## Notes

### What I'm Proud Of

- Math:  Getting the math right was challenging, but the orbits look right.  Getting the stars to not fly away to +/- infinity was a bit of a struggle.
- Multiple Light Sources: The stars' light seems to blend nicely when the cubes are enabled.
- Billboarding: This technique wasn't my first choice, but I think it is very clever and I'm glad I was able to implement it correctly.
- Riding Objects:  Even though this is a simple trick with gluLookAt(), I think it is really entertaining.

### Failed Attempts

I spent a lot of time trying to implement a particle system, but I got to the point where I couldn't spend any more time on it, so there are just point arrays.  My program would be a lot neater if the particles were objects that could store velocities, but I could not figure it out.  They would have been especially neat in the merging mode.  Another part of the particle system that I tried to implement, but could not was lighting.  The center of the gas disk around the black hole and each of the stars are light sources, and since I couldn't get the particles to behave correctly for lighting, I added the cubes for the purpose of showing the stars' light.  One thing that almost worked for particle lighting was billboarding each of the particles, but the program would crash after displaying a few very slowly renderd frames.

I attempted to make the stars "shine" by applying a texture in a frame buffer object, but it proved to be too complicated, so I just made them appear as billboarded quads.
