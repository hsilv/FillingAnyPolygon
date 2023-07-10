#include <iostream>
#include <fstream>
#include <algorithm>
#include "bitmapwrite.h"

void draw_centered_rectangle(size_t width, size_t height);
void drawLine(float startX, float startY, float endX, float endY, size_t width, size_t height);
void drawPolygon(const std::vector<Vertex2> &points, size_t width, size_t height);
void fillPolygon(const std::vector<Vertex2> &vertices, size_t width, size_t height);

void render()
{

    // Inicializar el framebuffer con el tamaño definido
    stretch(framebufferWidth, framebufferHeight);

    setClearColor(Color(46, 52, 64));
    clear();

    std::vector<Vertex2> polygon = {
        {377.0f, 249.0f},
        {411.0f, 197.0f},
        {436.0f, 249.0f}};

    setCurrentColor(Color(255, 255, 255));
    drawPolygon(polygon, framebufferWidth, framebufferHeight);
    setCurrentColor(Color(255, 0, 0));
    fillPolygon(polygon, framebufferWidth, framebufferHeight);

    renderBuffer();
}

void draw_centered_rectangle(size_t width, size_t height)
{
    float startVPoint = (framebufferHeight / 2) - (height / 2);
    float startHPoint = (framebufferWidth / 2) - (width / 2);

    for (float i = startVPoint; i <= startVPoint + height; i++)
    {
        for (float j = startHPoint; j <= startHPoint + width; j++)
        {
            point(Vertex2(j, i), framebufferWidth, framebufferHeight);
        }
    }
}

void drawLine(float startX, float startY, float endX, float endY, size_t width, size_t height)
{
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

    while (true)
    {
        // Verificar si las coordenadas están dentro del rango del framebuffer
        if (x0 >= 0 && x0 < static_cast<int>(width) && y0 >= 0 && y0 < static_cast<int>(height))
        {
            // Dibujar el punto en el framebuffer
            point(Vertex2{static_cast<float>(x0), static_cast<float>(y0)}, width, height);
        }

        // Verificar si se alcanzó el punto final
        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        // Calcular el siguiente punto en la línea
        int error2 = 2 * error;

        if (error2 > -dy)
        {
            error -= dy;
            x0 += sx;
        }

        if (error2 < dx)
        {
            error += dx;
            y0 += sy;
        }
    }
}

void drawPolygon(const std::vector<Vertex2> &points, size_t width, size_t height)
{
    size_t numPoints = points.size();

    // Dibujar las líneas que conectan los puntos
    for (size_t i = 0; i < numPoints; i++)
    {
        const Vertex2 &startPoint = points[i];
        const Vertex2 &endPoint = points[(i + 1) % numPoints]; // Punto siguiente (o primer punto si es el último)

        drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, width, height);
    }
}

void fillPolygon(const std::vector<Vertex2> &vertices, size_t width, size_t height)
{
    std::vector<int> yValues;
    for (const Vertex2 &vertex : vertices)
    {
        yValues.push_back(static_cast<int>(vertex.y));
    }

    std::sort(yValues.begin(), yValues.end());

    for (int y = yValues.front(); y <= yValues.back(); y++)
    {
        std::vector<float> xIntercepts;
        for (size_t i = 0; i < vertices.size(); i++)
        {
            const Vertex2 &currentVertex = vertices[i];
            const Vertex2 &nextVertex = vertices[(i + 1) % vertices.size()];

            if ((currentVertex.y <= static_cast<float>(y) && nextVertex.y > static_cast<float>(y)) || (nextVertex.y <= static_cast<float>(y) && currentVertex.y > static_cast<float>(y)))
            {
                float xIntercept = currentVertex.x + (static_cast<float>(y) - currentVertex.y) *
                                                         (nextVertex.x - currentVertex.x) / (nextVertex.y - currentVertex.y);
                xIntercepts.push_back(xIntercept);
            }
        }

        std::sort(xIntercepts.begin(), xIntercepts.end());

        for (size_t i = 0; i < xIntercepts.size(); i += 2)
        {
            int startX = static_cast<int>(xIntercepts[i]);
            int endX = static_cast<int>(xIntercepts[i + 1]);

            for (int x = startX; x <= endX; x++)
            {
                point(Vertex2{static_cast<float>(x), static_cast<float>(y)}, width, height);
            }
        }
    }
}
