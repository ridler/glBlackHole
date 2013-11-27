# Black Hole Simulation

view this file formatted nicely at: https://github.com/ridler/glBlackHole/blob/master/README.md

## Status as of 11/27/2013

### How to run the program:

The project can be compiled and run using the "Run" button on Qt Creator.  qmake hasn't worked for me from the command line, but "make" does.

The interaction at this point is simple: you can move the viewing angles by clicking and dragging in the display area, and you can switch modes by clicking the buttons on the right side of the main window.

### What else needs to be done:

#### Particle Systems
I'm having a lot of trouble implementing a particle system.  My program currently creates the correct number of distinct particle objects, but only displays one of them.  Particle systems will be displayed in both modes, and will be key to making the scenes look good.  In the singular/main viewing mode, I want the particles to be produced on a click from the user, so I can model how they swirl into the black hole from different starting positions.  In the merger viewing mode, I want them to start as disks around the black holes, then scatter and be attracted to the new larger black hole.

#### Textures
I need to apply textures to the stars and possibly to the particles to produce a glowing effect.  I've tried doing this the Qt way, but haven't had any success yet.

#### Bug fixes
The math for the merging is a little bit off, but I'm making quick progress with fixing it.

#### Maybe:
Add a UI element that allows the user to update some parameters, such as the simulation speed.
