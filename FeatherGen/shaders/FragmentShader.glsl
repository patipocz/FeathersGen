#version 330 core
uniform vec4 Colour;
/// @brief our output fragment colour
layout (location = 0) out vec4 fragColour;
in vec3 norm;
void main ()
{
  fragColour = Colour;
}