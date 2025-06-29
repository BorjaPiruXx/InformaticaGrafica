#define _USE_MATH_DEFINES

#include "engine/geometry/sphere.hpp"

#include <cmath>
#include <fstream>
#include <glm/glm.hpp>

//http://www.songho.ca/opengl/gl_sphere.html

Sphere::Sphere(float radius, uint32_t stacks, uint32_t slices, bool calcTangents) : _radius(radius), _stacks(stacks), _slices(slices) 
{
    _calcTangents = calcTangents;
    _nVertices = (slices + 1) * (stacks + 1);
    _nElements = (slices * 2 * (stacks - 1)) * 3;

    const auto positions = new float[static_cast<size_t>(_nVertices) * 3];
    const auto uvs = new float[static_cast<size_t>(_nVertices) * 2];
    const auto normals = new float[static_cast<size_t>(_nVertices) * 3];
    const auto index = new uint32_t[_nElements];

    generateVertexData(positions, uvs, normals, index);
    uploadData(positions, uvs, normals, index);

    delete[] positions;
    delete[] uvs;
    delete[] normals;
    delete[] index;
}

void Sphere::generateVertexData(float* positions, float* uvs, float* normals, uint32_t* index) const 
{
    // Generar posiciones y normales
    const auto thetaFac = static_cast<float>((2.0 * M_PI) / _slices);
    const auto phiFac = static_cast<float>(M_PI / _stacks);

    uint32_t idx = 0, tIdx = 0;
    for(size_t i = 0; i <= _slices; i++) 
    {
        const float theta = i * thetaFac;
        const float s = static_cast<float>(i) / _slices;

        for(size_t  j = 0; j <= _stacks; j++) 
        {
            const float phi = j * phiFac;
            const float t = static_cast<float>(j) / _stacks;
            const float nx = sinf(phi) * cosf(theta);
            const float ny = sinf(phi) * sinf(theta);
            const float nz = cosf(phi);

            positions[idx] = _radius * nx; positions[idx + 1] = _radius * ny; positions[idx + 2] = _radius * nz;
            normals[idx] = nx; normals[idx + 1] = ny; normals[idx + 2] = nz;
            idx += 3;

            uvs[tIdx] = s;
            uvs[tIdx + 1] = t;
            tIdx += 2;
        }
    }

    // Generar lista de elementos
    idx = 0;
    for(size_t i = 0; i < _slices; i++) 
    {
        const uint32_t stackStart = i * (static_cast<size_t>(_stacks) + 1);
        const uint32_t nextStackStart = (i + 1) * (static_cast<size_t>(_stacks) + 1);

        for(size_t  j = 0; j < _stacks; j++) 
        {
            if(j == 0) 
            {
                index[idx] = stackStart;
                index[idx + 1] = stackStart + 1;
                index[idx + 2] = nextStackStart + 1;
                idx += 3;
            } else if(j == _stacks - 1) 
            {
                index[idx] = stackStart + j;
                index[idx + 1] = stackStart + j + 1;
                index[idx + 2] = nextStackStart + j;
                idx += 3;
            } else 
            {
                index[idx] = stackStart + j;
                index[idx + 1] = stackStart + j + 1;
                index[idx + 2] = nextStackStart + j + 1;
                index[idx + 3] = nextStackStart + j;
                index[idx + 4] = stackStart + j;
                index[idx + 5] = nextStackStart + j + 1;
                idx += 6;
            }
        }
    }
}