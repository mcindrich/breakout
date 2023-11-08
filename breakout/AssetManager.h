#pragma once

#include "IAsset.h"

#include <string>
#include <optional>
#include <map>
#include <memory>

class AssetManager
{
public:
    AssetManager()
    {
    }

    template <typename AssetType, typename... Args> void loadAsset(const std::string& fpath, std::optional<std::string> name = std::nullopt, Args&&... args);
    template <typename AssetType> AssetType& getAsset(const std::string& name);

private:
    std::map<std::string, std::unique_ptr<IAsset>> m_assets;
};

template<typename AssetType, typename... Args>
inline void AssetManager::loadAsset(const std::string& fpath, std::optional<std::string> name, Args&&... args)
{
    // also check if an asset exists - many bricks may have the same sound effect - don't load or store twice
    if (name.has_value())
    {
        if (m_assets.find(name.value()) == m_assets.end()) {
            auto asset = std::make_unique<AssetType>(std::forward<Args>(args)...);
            asset->loadFromFile(fpath);

            m_assets[name.value()] = std::move(asset);
        }
    }
    else
    {
        if (m_assets.find(fpath) == m_assets.end()) {
            auto asset = std::make_unique<AssetType>(std::forward<Args>(args)...);
            asset->loadFromFile(fpath);

            m_assets[fpath] = std::move(asset);
        }
    }
}

template<typename AssetType>
inline AssetType& AssetManager::getAsset(const std::string& name)
{
    auto asset_ptr = m_assets[name].get();

    return *dynamic_cast<AssetType*>(m_assets[name].get());
}
