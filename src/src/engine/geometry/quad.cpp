#include "engine/geometry/quad.hpp"

Quad::Quad(float size, bool calcTangents) : _size(size) 
{
    _calcTangents = calcTangents;
    /*
     * Caras = 1
     * Triángulos = 2
     * Vértices = 3
    */
    _nVertices = 1 * 2 * 3;
    _nElements = _nVertices;

    const float half = size / 2.0f;

    float positions[] = 
    {
        // Arriba derecha
        half, half, 0.0f,
        half, -half, 0.0f,
        -half, half, 0.0f,
        // Abajo izquierda
        half, -half, 0.0f,
        -half, half, 0.0f,
        -half, -half, 0.0f
    };

    float uvs[] = 
    {
        // Arriba derecha
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        // Abajo izquierda
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f
    };

    float normals[] = 
    {
        // Arriba derecha
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        // Abajo izquierda
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    uint32_t index[] = 
    { 
        0, 2, 1,
        3 , 4, 5 
    };

    uploadData(positions, uvs, normals, index);
}