#include <iostream>
#include <fstream>
#include "bitmapwrite.h"

void draw_centered_rectangle(size_t width, size_t height);
void drawLine(float startX, float startY, float endX, float endY, size_t width, size_t height);

void render() {

    // Inicializar el framebuffer con el tamaño definido
    stretch(framebufferWidth, framebufferHeight);

    setClearColor(Color(46, 52, 64));
    clear();

    setCurrentColor(Color(255, 0, 0));
    draw_centered_rectangle(150, 150);

    setCurrentColor(Color(0, 255, 0));
    draw_centered_rectangle(100, 100);

    setCurrentColor(Color(0, 0, 255));
    draw_centered_rectangle(50, 50);

    drawLine(0, 0, 800, 600, framebufferWidth, framebufferHeight);
    drawLine(0, 600, 800, 0, framebufferWidth, framebufferHeight);

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

void drawLine(float startX, float startY, float endX, float endY, size_t width, size_t height) {
    // Convertir las coordenadas iniciales y finales en enteros
    int x0 = static_cast<int>(startX);
    int y0 = static_cast<int>(startY);
    int x1 = static_cast<int>(endX);
    int y1 = static_cast<int>(endY);

    // Calcular las diferencias en las coordenadas x e y
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    // Determinar la dirección de incremento para x e y
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    // Calcular el valor de error inicial
    int error = dx - dy;

    while (true) {
        // Verificar si las coordenadas están dentro del rango del framebuffer
        if (x0 >= 0 && x0 < static_cast<int>(width) && y0 >= 0 && y0 < static_cast<int>(height)) {
            // Dibujar el punto en el framebuffer
            point(Vertex2{ static_cast<float>(x0), static_cast<float>(y0) }, width, height);
        }

        // Verificar si se alcanzó el punto final
        if (x0 == x1 && y0 == y1) {
            break;
        }

        // Calcular el siguiente punto en la línea
        int error2 = 2 * error;

        if (error2 > -dy) {
            error -= dy;
            x0 += sx;
        }

        if (error2 < dx) {
            error += dx;
            y0 += sy;
        }
    }
}
