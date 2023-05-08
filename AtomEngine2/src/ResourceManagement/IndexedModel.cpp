#include "IndexedModel.hpp"

namespace atom
{
    void IndexedModel::CalcNormals()
    {
        for (unsigned int i = 0; i < indices.size(); i += 3)
        {
            int i0 = indices[i];
            int i1 = indices[i + 1];
            int i2 = indices[i + 2];

            Vector3 v1 = positions[i1] - positions[i0];
            Vector3 v2 = positions[i2] - positions[i0];
            
            Vector3 normal = v1.Cross(v2).Normalize();
                
            normals[i0] += normal;
            normals[i1] += normal;
            normals[i2] += normal;
        }
        
        for (unsigned int i = 0; i < normals.size(); i++)
            normals[i].Normalize();
    }

    void IndexedModel::CalcTangentSpace()
    {
        for (unsigned int i = 0; i < indices.size(); i += 3)
        {
            int i0 = indices[i];
            int i1 = indices[i + 1];
            int i2 = indices[i + 2];

            Vector3 v1 = positions[i1] - positions[i0];
            Vector3 v2 = positions[i2] - positions[i0];
            float du1 = texCoords[i1].x - texCoords[i0].x;
            float du2 = texCoords[i2].x - texCoords[i0].x;
            float dv1 = texCoords[i1].y - texCoords[i0].y;
            float dv2 = texCoords[i2].y - texCoords[i0].y;
            
            float invDet = 1.0f / (du1 * dv2 - du2 * dv1);
            Vector3 tan(invDet * (dv2 * v1.x - dv1 * v2.x),
                invDet * (dv2 * v1.y - dv1 * v2.y),
                invDet * (dv2 * v1.z - dv1 * v2.z));

            tangents[i0] += tan;
            tangents[i1] += tan;
            tangents[i2] += tan;
        }
        
        for (unsigned int i = 0; i < tangents.size(); i++)
            tangents[i].Normalize();
    }
}
