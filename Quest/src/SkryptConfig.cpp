#include "SkryptConfig.hpp"
#include "main.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

void createConfig() {
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();

    if (!getConfig().config.HasMember("isBold")) {
        getConfig().config.AddMember("isBold", rapidjson::Value(0).SetBool(false), allocator);
    }
    if (!getConfig().config.HasMember("isStrikethrough")) {
        getConfig().config.AddMember("isStrikethrough", rapidjson::Value(0).SetBool(false), allocator);
    }
    if (!getConfig().config.HasMember("isUnderline")) {
        getConfig().config.AddMember("isUnderline", rapidjson::Value(0).SetBool(false), allocator);
    }
    if (!getConfig().config.HasMember("case")) {
        getConfig().config.AddMember("case", rapidjson::Value(0).SetInt(0), allocator);
    }
    if (!getConfig().config.HasMember("fontFile")) {
        getConfig().config.AddMember("fontFile", rapidjson::Value(0).SetString(""), allocator);
    }

    getConfig().Write();
}