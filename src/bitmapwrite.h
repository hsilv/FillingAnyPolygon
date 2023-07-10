#include <iostream>
#include <fstream>
#include "framebuffer.cpp"

const std::string filename = "output.bmp";

void renderBuffer() {
    const size_t width = framebufferWidth;
    const size_t height = framebufferHeight;

    constexpr int BMP_HEADER_SIZE = 14;
    constexpr int DIB_HEADER_SIZE = 40;
    const int paddingSize = (4 - (width * 3) % 4) % 4;
    const int fileSize = BMP_HEADER_SIZE + DIB_HEADER_SIZE + (3 * width + paddingSize) * height;

    char bmpHeader[BMP_HEADER_SIZE] = {
        'B', 'M',
        static_cast<char>(fileSize), static_cast<char>(fileSize >> 8), static_cast<char>(fileSize >> 16), static_cast<char>(fileSize >> 24),
        0, 0, 0, 0,
        static_cast<char>(BMP_HEADER_SIZE + DIB_HEADER_SIZE), static_cast<char>((BMP_HEADER_SIZE + DIB_HEADER_SIZE) >> 8), static_cast<char>((BMP_HEADER_SIZE + DIB_HEADER_SIZE) >> 16), static_cast<char>((BMP_HEADER_SIZE + DIB_HEADER_SIZE) >> 24)
    };

    char dibHeader[DIB_HEADER_SIZE] = {
        static_cast<char>(DIB_HEADER_SIZE), static_cast<char>(DIB_HEADER_SIZE >> 8), static_cast<char>(DIB_HEADER_SIZE >> 16), static_cast<char>(DIB_HEADER_SIZE >> 24),
        static_cast<char>(width), static_cast<char>(width >> 8), static_cast<char>(width >> 16), static_cast<char>(width >> 24),
        static_cast<char>(height), static_cast<char>(height >> 8), static_cast<char>(height >> 16), static_cast<char>(height >> 24),
        1, 0,
        24, 0,
        0, 0, 0, 0,
        static_cast<char>((3 * width + paddingSize) * height), static_cast<char>(((3 * width + paddingSize) * height) >> 8), static_cast<char>(((3 * width + paddingSize) * height) >> 16), static_cast<char>(((3 * width + paddingSize) * height) >> 24),
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    file.write(bmpHeader, BMP_HEADER_SIZE);
    file.write(dibHeader, DIB_HEADER_SIZE);

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            size_t index = y * width + x;
            Color color = framebuffer[index];
            file.write(reinterpret_cast<const char*>(&color.getBlue()), 1);
            file.write(reinterpret_cast<const char*>(&color.getGreen()), 1);
            file.write(reinterpret_cast<const char*>(&color.getRed()), 1);
        }

        for (int i = 0; i < paddingSize; i++) {
            file.put(0);
        }
    }

    file.close();

    std::cout << "Archivo " << filename << " generado correctamente." << std::endl;
};