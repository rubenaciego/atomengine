#include "ObjLoader.hpp"
#include <Debug/Log.hpp>
#include <fstream>
#include <algorithm>
#include <unordered_map>

namespace atom
{
    static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token);
    static inline unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end);
    static inline float ParseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end);
    static inline std::vector<std::string> SplitString(const std::string &s, char delim);

    bool OBJIndex::operator==(const OBJIndex& r) const
    {
        return vertexIndex == r.vertexIndex;
    }

    OBJModel::OBJModel(const std::string& fileName)
    {
        hasUVs = false;
        hasNormals = false;
        std::ifstream file;
        file.open(fileName.c_str());

        std::string line;
        if (file.is_open())
        {
            while (file.good())
            {
                getline(file, line);
            
                unsigned int lineLength = line.length();
                
                if (lineLength < 2)
                    continue;
                
                const char* lineCStr = line.c_str();
                
                switch (lineCStr[0])
                {
                    case 'v':
                        if (lineCStr[1] == 't')
                            this->uvs.push_back(ParseOBJVec2(line));
                        else if (lineCStr[1] == 'n')
                            this->normals.push_back(ParseOBJVec3(line));
                        else if (lineCStr[1] == ' ' || lineCStr[1] == '\t')
                            this->vertices.push_back(ParseOBJVec3(line));
                    break;
                    case 'f':
                        CreateOBJFace(line);
                    break;
                    default:
                    break;
                };
            }
        }
        else
        {
            ATOM_CORE_ERROR("[Atom]: Error, unable to load mesh %s\n", fileName.c_str());
        }
    }

    IndexedModel OBJModel::ToIndexedModel()
    {
        IndexedModel result;
        IndexedModel normalModel;
        
        std::unordered_map<OBJIndex, unsigned int> normalModelIndexMap;
        std::unordered_map<OBJIndex, unsigned int> resultModelIndexMap;
        std::unordered_map<unsigned int, unsigned int> indexMap;
        
        for (unsigned int i = 0; i < OBJIndices.size(); i++)
        {
            OBJIndex* currentIndex = &OBJIndices[i];
            
            Vector3 currentPosition = vertices[currentIndex->vertexIndex];
            Vector2 currentTexCoord;
            Vector3 currentNormal;
            Vector3 currentTangent;
            
            if (hasUVs)
                currentTexCoord = uvs[currentIndex->uvIndex];
            else
                currentTexCoord = Vector2(0, 0);
                
            if (hasNormals)
                currentNormal = normals[currentIndex->normalIndex];
            else
                currentNormal = Vector3(0, 0, 0);
            
            unsigned int normalModelIndex;
            unsigned int resultModelIndex;
            
            //Create model to properly generate normals on
            try
            {
                normalModelIndex = normalModelIndexMap.at(*currentIndex);
            }
            catch (const std::out_of_range& e)
            {
                normalModelIndex = normalModel.positions.size();
            
                normalModelIndexMap.insert(std::pair<OBJIndex, unsigned int>(*currentIndex, normalModelIndex));
                normalModel.positions.push_back(currentPosition);
                normalModel.texCoords.push_back(currentTexCoord);
                normalModel.normals.push_back(currentNormal);
                normalModel.tangents.push_back(currentTangent);
            }
            
            //Create model which properly separates texture coordinates
            try
            {
                resultModelIndex = resultModelIndexMap.at(*currentIndex);
            }
            catch (const std::out_of_range& e)
            {
                resultModelIndex = result.positions.size();
            
                resultModelIndexMap.insert(std::pair<OBJIndex, unsigned int>(*currentIndex, resultModelIndex));
                result.positions.push_back(currentPosition);
                result.texCoords.push_back(currentTexCoord);
                result.normals.push_back(currentNormal);
                result.tangents.push_back(currentTangent);
            }
            
            normalModel.indices.push_back(normalModelIndex);
            result.indices.push_back(resultModelIndex);
            indexMap.insert(std::pair<unsigned int, unsigned int>(resultModelIndex, normalModelIndex));
        }
        
        if (!hasNormals)
        {
            normalModel.CalcNormals();
            
            for (unsigned int i = 0; i < result.positions.size(); i++)
                result.normals[i] = normalModel.normals[indexMap[i]];
        }

        normalModel.CalcTangentSpace();

        for (unsigned int i = 0; i < result.positions.size(); i++)
            result.tangents[i] = normalModel.tangents[indexMap[i]];   
        
        return result;
    };

    void OBJModel::CreateOBJFace(const std::string& line)
    {
        std::vector<std::string> tokens = SplitString(line, ' ');

        this->OBJIndices.push_back(ParseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
        this->OBJIndices.push_back(ParseOBJIndex(tokens[2], &this->hasUVs, &this->hasNormals));
        this->OBJIndices.push_back(ParseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));

        if ((int)tokens.size() > 4)
        {
            this->OBJIndices.push_back(ParseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
            this->OBJIndices.push_back(ParseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));
            this->OBJIndices.push_back(ParseOBJIndex(tokens[4], &this->hasUVs, &this->hasNormals));
        }
    }

    OBJIndex OBJModel::ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals)
    {
        unsigned int tokenLength = token.length();
        const char* tokenString = token.c_str();
        
        unsigned int vertIndexStart = 0;
        unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');
        
        OBJIndex result;
        result.vertexIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
        result.uvIndex = 0;
        result.normalIndex = 0;
        
        if (vertIndexEnd >= tokenLength)
            return result;
        
        vertIndexStart = vertIndexEnd + 1;
        vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');
        
        result.uvIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
        *hasUVs = true;
        
        if (vertIndexEnd >= tokenLength)
            return result;
        
        vertIndexStart = vertIndexEnd + 1;
        vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');
        
        result.normalIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
        *hasNormals = true;
        
        return result;
    }

    Vector3 OBJModel::ParseOBJVec3(const std::string& line) 
    {
        unsigned int tokenLength = line.length();
        const char* tokenString = line.c_str();
        
        unsigned int vertIndexStart = 2;
        
        while (vertIndexStart < tokenLength)
        {
            if (tokenString[vertIndexStart] != ' ')
                break;
            vertIndexStart++;
        }
        
        unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');
        
        float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);
        
        vertIndexStart = vertIndexEnd + 1;
        vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');
        
        float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);
        
        vertIndexStart = vertIndexEnd + 1;
        vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');
        
        float z = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);
        
        return Vector3(x,y,z);
    }

    Vector2 OBJModel::ParseOBJVec2(const std::string& line)
    {
        unsigned int tokenLength = line.length();
        const char* tokenString = line.c_str();
        
        unsigned int vertIndexStart = 3;
        
        while (vertIndexStart < tokenLength)
        {
            if (tokenString[vertIndexStart] != ' ')
                break;
            vertIndexStart++;
        }
        
        unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');
        
        float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);
        
        vertIndexStart = vertIndexEnd + 1;
        vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');
        
        float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);
        
        return Vector2(x,y);
    }

    static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token)
    {
        unsigned int result = start;
        while (result < length)
        {
            result++;
            if (str[result] == token)
                break;
        }
        
        return result;
    }

    static inline unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end)
    {
        return atoi(token.substr(start, end - start).c_str()) - 1;
    }

    static inline float ParseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end)
    {
        return atof(token.substr(start, end - start).c_str());
    }

    static inline std::vector<std::string> SplitString(const std::string &s, char delim)
    {
        std::vector<std::string> elems;
            
        const char* cstr = s.c_str();
        unsigned int strLength = s.length();
        unsigned int start = 0;
        unsigned int end = 0;
            
        while (end <= strLength)
        {
            while (end <= strLength)
            {
                if (cstr[end] == delim)
                    break;
                end++;
            }
                
            elems.push_back(s.substr(start, end - start));
            start = end + 1;
            end = start;
        }
            
        return elems;
    }
}
