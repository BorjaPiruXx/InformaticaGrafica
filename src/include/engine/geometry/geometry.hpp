#pragma once

#include <cstdint>

/*
 * Asociación de atributos:
 *  > Posición = 0
 *  > UV = 1
 *  > Normal = 2
 *  > Tangente = 3
 *  > Bitangente = 4
*/

class Geometry 
{
    public:
        Geometry() = default;

        virtual void render() const;

        virtual ~Geometry();

        Geometry(const Geometry&) = default;
        Geometry& operator=(const Geometry&) = default;

        Geometry(Geometry&&) noexcept = default;
        Geometry& operator=(Geometry&&) noexcept = default;

    protected:
        void uploadData(const float* positions, const float* uvs, const float* normals, const uint32_t* indices);

        uint32_t _VAO = 0;
        uint32_t _VBO[6] 
        {
            0, 0, 0, 
            0, 0, 0 
        };
        uint32_t _nVertices = 0;
        uint32_t _nElements = 0;
        bool _calcTangents = true;

    private:
        void calcTangents(const float* positions, const float* uvs, const float* normals, float* tangents, float* biTangents) const;
};