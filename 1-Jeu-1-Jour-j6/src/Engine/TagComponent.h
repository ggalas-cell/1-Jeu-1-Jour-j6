#pragma once
#include "Component.h"
#include <string>
#include <vector>

class TagComponent : public Component
{
    std::vector<std::string> m_tags;

public:
    TagComponent(const std::string& _tag);

    void AddTag(const std::string& _tag);
    void RemoveTag(const std::string& _tag);

    bool Is(const std::string& _tag) const;
};