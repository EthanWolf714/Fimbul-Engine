#include "engine/resources/TextureManager.h"

void TextureManager::Init()
{

}

Texture2D TextureManager::Load(const std::string& path)
{
    //check if already loaded
    auto it = m_textures.find(path);
    if(it != m_textures.end())
    {
        TraceLog(LOG_INFO, "Texture already loaded returning cached: %s", path.c_str());
        return it->second;
    }

    //Load and cache
    Texture2D texture = LoadTexture(path.c_str());
    m_textures[path] = texture;
    return texture;
}

Texture2D TextureManager::Get(const std::string& name) {
    auto it = m_textures.find(name);
    if(it != m_textures.end()) return it->second;
    
    TraceLog(LOG_ERROR, "Texture not found: %s", name.c_str());
    return { 0 }; // return empty texture if not found
}

void TextureManager::Unload(const std::string& name)
{
    auto it = m_textures.find(name);
    if(it != m_textures.end()) {
        UnloadTexture(it->second);
        m_textures.erase(it);
    }
}

void TextureManager::UnloadAll()
{
    for(auto& pair : m_textures)
    {
        UnloadTexture(pair.second);
    }
    m_textures.clear();
}

void TextureManager::ShutDown()
{
    UnloadAll();
}