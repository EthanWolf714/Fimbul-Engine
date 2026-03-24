#pragma once
#include "raylib.h"
#include <string>
#include <unordered_map>

class TextureManager
{
public:
    void Init();
    void ShutDown();
    Texture2D Load(const std::string& path);
    Texture2D Get(const std::string& name);
    void Unload(const std::string& name);
    void UnloadAll();
private:
    std::unordered_map<std::string, Texture2D> m_textures;


};