#include "engine/geometry/teapot.hpp"
#include "engine/geometry/data/teapot.hpp"

#pragma warning(push, 0)
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

Teapot::Teapot(uint32_t grid, glm::mat4 lidTransform, bool calcTangents) 
{
    _calcTangents = calcTangents;
    _nVertices = 32 * (grid + 1) * (grid + 1);
    const uint32_t faces = grid * grid * 32;
    _nElements = faces * 6;

    const auto positions = new float[static_cast<size_t>(_nVertices) * 3];
    const auto uvs = new float[static_cast<size_t>(_nVertices) * 2];
    const auto normals = new float[static_cast<size_t>(_nVertices) * 3];
    const auto index = new uint32_t[_nElements];

    generateVertexData(positions, uvs, normals, index, grid);
    moveLid(grid, positions, lidTransform);
    uploadData(positions, uvs, normals, index);

    delete[] positions;
    delete[] uvs;
    delete[] normals;
    delete[] index;
}

void Teapot::generateVertexData(float* positions, float* uvs, float* normals, uint32_t* index, uint32_t grid) const 
{
    // Computar las funciones base (polinomios de Bernstein) y sus derivadas
    const auto B = new float[4 * (grid + 1)];
    const auto dB = new float[4 * (grid + 1)];
    computeBasisFunctions(B, dB, grid);

    uint32_t idx = 0; 
    uint32_t uvIdx = 0;
    uint32_t indexIdx = 0;

    // Borde de la tetera
    buildPatchReflect(0, B, dB, positions, uvs, normals, index, idx, uvIdx, indexIdx, grid, true, true);

    // Cuerpo de la tetera
    buildPatchReflect(1, B, dB, positions, uvs, normals, index, idx, uvIdx, indexIdx, grid, true, true);
    buildPatchReflect(2, B, dB, positions, uvs, normals, index, idx, uvIdx, indexIdx, grid, true, true);

    // Tapa de la tetera
    buildPatchReflect(3, B, dB, positions, uvs, normals, index, idx, uvIdx, indexIdx, grid, true, true);
    buildPatchReflect(4, B, dB, positions, uvs, normals, index, idx, uvIdx, indexIdx, grid, true, true);

    // Fondo de la tetera
    buildPatchReflect(5, B, dB, positions, uvs, normals, index, idx, uvIdx, indexIdx, grid, true, true);

    // Asa de la tetera
    buildPatchReflect(6, B, dB, positions, uvs, normals, index, idx, uvIdx, indexIdx, grid, false, true);
    buildPatchReflect(7, B, dB, positions, uvs, normals, index, idx, uvIdx, indexIdx, grid, false, true);

    // Pitorro de la tetera
    buildPatchReflect(8, B, dB, positions, uvs, normals, index, idx, uvIdx, indexIdx, grid, false, true);
    buildPatchReflect(9, B, dB, positions, uvs, normals, index, idx, uvIdx, indexIdx, grid, false, true);

    delete[] B;
    delete[] dB;
}



void Teapot::buildPatchReflect(uint32_t patchNum, float* B, float* dB, float* positions, float* uvs, float* normals, uint32_t* indices, uint32_t& idx, uint32_t& uvIdx, uint32_t& indicesIdx, int grid, bool reflectX, bool reflectY) 
{
    glm::vec3 patch[4][4];
    glm::vec3 patchRevV[4][4];
    getPatch(patchNum, patch, false);
    getPatch(patchNum, patchRevV, true);

    // Construir parche en ningún eje
    buildPatch(patch, B, dB, positions, uvs, normals, indices, idx, uvIdx, indicesIdx, grid, glm::mat3(1.0f), true);

    // Construir parche sobre el eje X
    if(reflectX) 
    {
        buildPatch(patchRevV, B, dB, positions, uvs, normals, indices, idx, uvIdx, indicesIdx, grid, glm::mat3(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)), false);
    }

    // Construir parche sobre el eje Y
    if(reflectY) 
    {
        buildPatch(patchRevV, B, dB, positions, uvs, normals, indices, idx, uvIdx, indicesIdx, grid, glm::mat3(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)), false);
    }

    // Construir parche sobre ambos ejes
    if(reflectX && reflectY) 
    {
        buildPatch(patch, B, dB, positions, uvs, normals, indices, idx, uvIdx, indicesIdx, grid, glm::mat3(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)), true);
    }
}

void Teapot::buildPatch(glm::vec3 patch[][4], float* B, float* dB, float* positions, float* uvs, float* normals, uint32_t* index, uint32_t& idx, uint32_t& uvIdx, uint32_t& indexIdx, uint32_t grid, glm::mat3 reflect, bool invertNormal) 
{
    const uint32_t startIndex = idx / 3;
    const float tcFactor = 1.0f / static_cast<float>(grid);

    for(uint32_t i = 0; i <= grid; ++i) 
    {
        for(uint32_t j = 0; j <= grid; ++j) 
        {
            const glm::vec3 pt = reflect * evaluate(i, j, B, patch);

            glm::vec3 norm = reflect * evaluateNormal(i, j, B, dB, patch);
            if (invertNormal) 
            {
                norm = -norm;
            }

            positions[idx] = pt.x;
            positions[idx + 1] = pt.y;
            positions[idx + 2] = pt.z;

            normals[idx] = norm.x;
            normals[idx + 1] = norm.y;
            normals[idx + 2] = norm.z;

            uvs[uvIdx] = i * tcFactor;
            uvs[uvIdx + 1] = j * tcFactor;

            idx += 3;
            uvIdx += 2;
        }
    }

    for(uint32_t i = 0; i < grid; ++i) 
    {
        const uint32_t iStart = i * (grid + 1) + startIndex;
        const uint32_t nextiStart = (i + 1) * (grid + 1) + startIndex;

        for(uint32_t j = 0; j < grid; ++j) 
        {
            index[indexIdx] = iStart + j;
            index[indexIdx + 1] = nextiStart + j + 1;
            index[indexIdx + 2] = nextiStart + j;

            index[indexIdx + 3] = iStart + j;
            index[indexIdx + 4] = iStart + j + 1;
            index[indexIdx + 5] = nextiStart + j + 1;

            indexIdx += 6;
        }
    }
}

void Teapot::getPatch(int patchNum, glm::vec3 patch[][4], bool reverseV) 
{
    // Recorrer en la dirección U
    for(uint32_t u = 0; u < 4; ++u)
    {
        // Recorrer en la dirección V
        for(uint32_t v = 0; v < 4; ++v)
        {
            if(reverseV) 
            {
                patch[u][v] = glm::vec3(
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + (3 - v)]][0],
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + (3 - v)]][1],
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + (3 - v)]][2]
                );
            } else 
            {
                patch[u][v] = glm::vec3(
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + v]][0],
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + v]][1],
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + v]][2]
                );
            }
        }
    }
}

void Teapot::computeBasisFunctions(float* B, float* dB, uint32_t grid) 
{
    const float inc = 1.0f / static_cast<float>(grid);
    for(uint32_t i = 0; i <= grid; ++i) 
    {
        const float t = static_cast<float>(i) * inc;
        const float tSqr = t * t;
        const float oneMinusT = (1.0f - t);
        const float oneMinusT2 = oneMinusT * oneMinusT;

        B[i * 4 + 0] = oneMinusT * oneMinusT2;
        B[i * 4 + 1] = 3.0f * oneMinusT2 * t;
        B[i * 4 + 2] = 3.0f * oneMinusT * tSqr;
        B[i * 4 + 3] = t * tSqr;

        dB[i * 4 + 0] = -3.0f * oneMinusT2;
        dB[i * 4 + 1] = -6.0f * t * oneMinusT + 3.0f * oneMinusT2;
        dB[i * 4 + 2] = -3.0f * tSqr + 6.0f * t * oneMinusT;
        dB[i * 4 + 3] = 3.0f * tSqr;
    }
}

glm::vec3 Teapot::evaluate(int gridU, int gridV, float* B, glm::vec3 patch[][4]) 
{
    glm::vec3 p(0.0f, 0.0f, 0.0f);
    for(uint32_t i = 0; i < 4; ++i) 
    {
        for(uint32_t j = 0; j < 4; ++j) 
        {
            p += patch[i][j] * B[gridU * 4 + i] * B[gridV * 4 + j];
        }
    }
    return p;
}

glm::vec3 Teapot::evaluateNormal(int gridU, int gridV, float* B, float* dB, glm::vec3 patch[][4]) 
{
    glm::vec3 du(0.0f, 0.0f, 0.0f);
    glm::vec3 dv(0.0f, 0.0f, 0.0f);
    for(uint32_t i = 0; i < 4; ++i) 
    {
        for(uint32_t j = 0; j < 4; ++j)
        {
            du += patch[i][j] * dB[gridU * 4 + i] * B[gridV * 4 + j];
            dv += patch[i][j] * B[gridU * 4 + i] * dB[gridV * 4 + j];
        }
    }

    glm::vec3 norm = glm::cross(du, dv);
    if(glm::length(norm) != 0.0f) 
    {
        norm = glm::normalize(norm);
    }

    return norm;
}

void Teapot::moveLid(int grid, float* v, glm::mat4 lidTransform) 
{
    const uint32_t start = 3 * 12 * (grid + 1) * (grid + 1);
    const uint32_t end = 3 * 20 * (grid + 1) * (grid + 1);

    for(uint32_t i = start; i < end; i += 3) 
    {
        glm::vec4 vertex = glm::vec4(v[i], v[i + 1], v[i + 2], 1.0f);
        vertex = lidTransform * vertex;
        v[i] = vertex.x;
        v[i + 1] = vertex.y;
        v[i + 2] = vertex.z;
    }
}