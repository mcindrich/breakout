#pragma once

#include <string>

class IAsset
{
public:
    IAsset() = default;

    virtual void loadFromFile(const std::string& fpath) = 0;

    virtual ~IAsset() = default;
};