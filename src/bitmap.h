#include <iostream>
#include <fstream>
#include "bitmapwrite.h"

void draw_centered_rectangle(size_t width, size_t height);

void render() {

    // Inicializar el framebuffer con el tamaño definido
    stretch(framebufferWidth, framebufferHeight);

    setClearColor(Color(46, 52, 64));
    clear();

    setCurrentColor(Color(66, 135, 245));
    draw_centered_rectangle(750, 550);

    setCurrentColor(Color(255, 0, 0));
    draw_centered_rectangle(150, 150);

    setCurrentColor(Color(0, 255, 0));
    draw_centered_rectangle(100, 100);

    setCurrentColor(Color(0, 0, 255));
    draw_centered_rectangle(50, 50);

    setCurrentColor(Color(255, 0, 0));
    renderBuffer();
}

void draw_centered_rectangle(size_t width, size_t height) {
    float startVPoint = (framebufferHeight/2) - (height/2);
    float startHPoint = (framebufferWidth/2) - (width/2);

    for (float i = startVPoint; i <= startVPoint+height; i++)
    {
        for (float j = startHPoint; j <= startHPoint+width; j++)
        {
            point(Vertex2(j, i), framebufferWidth, framebufferHeight);
        }
    }
}