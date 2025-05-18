#include "engine/geometry/cube.hpp"

Cube::Cube(float size, bool calcTangents) : _size(size) 
{
    _calcTangents = calcTangents;
    /*
     * Caras = 6
     * Triángulos = 2
     * Vértices = 3
     */
    _nVertices = 6 * 2 * 3;
    _nElements = _nVertices;

    const float half = size / 2.0f;

    float positions[] = 
    {
        // Frontal
        -half, -half, half,
        half, -half, half,
        half, half, half,
        -half, -half, half,
        half, half, half,
        -half, half, half,
        // Derecha
        half, -half, half,
        half, -half, -half,
        half, half, -half,
        half, -half, half,
        half, half, -half,
        half, half, half,
        // Trasera
        half, -half, -half,
        -half, -half, -half,
        -half, half, -half,
        half, -half, -half,
        -half, half, -half,
        half, half, -half,
        // Izquierda
        -half, -half, -half,
        -half, -half, half,
        -half, half, half,
        -half, -half, -half,
        -half, half, half,
        -half, half, -half,
        // Abajo
        -half, -half, -half,
        half, -half, -half,
        half, -half, half,
        -half, -half, -half,
        half, -half, half,
        -half, -half, half,
        // Arriba
        -half, half, half,
        half, half, half,
        half, half,-half,
        -half, half, half,
        half, half, -half,
        -half, half, -half
    };

    float uvs[] = 
    {
        // Frontal
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Derecha
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Trasera
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Izquierda      
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Abajo
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Arriba
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    float normals[] = 
    { 
        // Frontal
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        // Derecha
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        // Trasera
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        // Izquierda
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        // Abajo
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        // Arriba
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    uint32_t index[] = 
    {
        0, 1, 2,        3, 4, 5,    // Frontal
        6, 7, 8,        9, 10, 11,  // Derecha
        12, 13, 14,     15, 16, 17, // Trasera
        18, 19, 20,     21, 22, 23, // Izquierda
        24, 25, 26,     27, 28, 29, // Abajo
        30, 31, 32,     33, 34, 35  // Arriba
    };

    uploadData(positions, uvs, normals, index);
}