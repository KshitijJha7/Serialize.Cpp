#pragma once

#include "serializable.hpp"
#include <vector>
#include <string>
#include <stdexcept>

template<typename T>
class Serializable<std::vector<T>> : public SerializableBase<std::vector<T>>
{
public:
    using SerializableBase<std::vector<T>>::SerializableBase;
    std::string serialize() const {
        std::string result = "[";
        bool first = true;
        for (const auto& item : this->value) {
            if (!first) {
                result += ",";
            }
            first = false;
            Serializable<T> wrapper(item);
            result += wrapper.serialize();
        }
        result += "]";
        return result;
    }

    void deserialize(const std::string& json) {
        this->value.clear();
        std::string token = trim_json_token(json);
        if (token.size() < 2 ||
            token.front() != '[' ||
            token.back() != ']') {
            throw std::invalid_argument(
                "Invalid JSON array"
            );
        }
        std::string content = token.substr(1, token.size() - 2);
        if (content.empty()) {
            return;
        }
        std::size_t start = 0;
        bool inQuotes = false;
        for (std::size_t i = 0;i <= content.size();++i) {
            if (i == content.size() ||(!inQuotes && content[i] == ',')) {
                std::string element =trim_json_token(content.substr(start,i - start));
                if (!element.empty()) {
                    Serializable<T> item;
                    item.deserialize(element);
                    this->value.push_back(item.get());
                }
                start = i + 1;
            }
            else if (content[i] == '"') {
                inQuotes = !inQuotes;
            }
        }
    }
};