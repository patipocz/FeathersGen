# Patrycja Poczkai ASE Assignment
Repository for the ASE assignment and code.
## Project Idea

### Feather Generator

The idea of the project is to generate a simple feather structure using Bezier curves. The method for feather generation is inspired by the 2002 papers by Franco and Walter and Streit and Heidrich.

## Initial Design & future development

Create bezier curves for the main feather parts: the rachis cubic bezier, boundary of the vanes (should be quadratic but initially cubic) and a cubic bezier curve for the barbs. Make this draw in NGL.

Here is an [example of creating the initial feather shape in Desmos](https://www.desmos.com/calculator/pzt44gh9e7) 


Next step was to interpolate a big number of barbs in a way that their 1st control points lay on the rachis and last control points lay on the vane. The two other control points on each barb can be controlled by vector parameters. 

I initially interpolated the barbs with 'straight lines' so with the 2nd control point being the same as the first one and the 3rd control point being the same as the 4th. 
Then following Franko and Walter's method the second and 3rd point get moved using v parameters that add a random value in x and y ( first as a constant input then changed to be random)to simulatethe plumulaceous (fuzzy)effect.

Next step was to add a ratio parameter that gives control over how much of the feather is supposed to be smooth and how much fuzzy.

Then randomisation of length of the barbs.

Then generating a few different feathers to demonstrate the tool in action (I wanted to  maybe assign them to keys the user can press and see different basic feather structures but this wasn'timplemented).

## Important Instructions

!!!!!!!!

**For now to generate different feathers you need to change what you pass into your constructor and change the values in the generate all barbs function in feather.cpp as things break when I pass the values in the constructor**

!!!!!!!!

![Parameters](/docs/params.jpg "Variables you can change")


## Current stage of development & Future Development Possibilities

Currently the program generates a feather and draws it using GL_POINTS, it would be good to change it so it can use the lines. 

Adding more functionality to the generator would be possible for instance an option to turn the symmetry of vanes on and off so having the curve control point mirror the other curve control points or be independent.

Make nice sliders based UI to enable easy manipulation of the parameters like the distance between the barbs, ratio of plumulaceous (fuzzy) to pennaceous(smooth) structures and where they start. Maybe have nice base feathers built in as examples.

Then maybe find a way to port it into Houdini and use for groom. 

From the code point of view it would be good to get the parameters to be private variables and make it so they can only be manipulated from NGLScene.cpp if not from UI as a lot of manipulation still happens in Feather.cpp which we don't want the user to touch but due to various issues and time constraints for now it is in both places (see graphic above for more details). It would be great to make the vane curves into quadratic beziers too as it would increase control over feaather shape and make it easier to manipulate

## Example Results

![result1](/docs/feather1.png "Feather1") ![result2](/docs/feather2.png "Feather1") ![result3](/docs/feather3.png "Feather1") ![result4](/docs/feather4.png "Feather1")



## Building

[build instructions can be found here](docs/BUILDING.md)
