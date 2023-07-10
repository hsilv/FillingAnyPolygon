#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>
#include <iostream>
#include "vertex2.h"
#include "color.h"

extern Color currentColor;
extern std::vector<Color> framebuffer;

void clear();
void point(const Vertex2& vertex, size_t width, size_t height);

#endif  // FRAMEBUFFER_H
