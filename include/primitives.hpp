#pragma once

#include "serializable.hpp"
#include <string>
#include <stdexcept>
#include <type_traits>
#include <vector>

inline std::string trim_json_token(const std::string& token) {
    size_t first = token.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return {};
    size_t last = token.find_last_not_of(" \t\n\r");
    return token.substr(first, last - first + 1);
}

template<>
struct Serializer<int> {
    static std::string serialize(const int& value) {
        return std::to_string(value);
    }
    static void deserialize(const std::string& json, int& value) {
        value = std::stoi(trim_json_token(json));
    }
};

template<>
struct Serializer<long> {
    static std::string serialize(const long& value) {
        return std::to_string(value);
    }
    static void deserialize(const std::string& json, long& value) {
        value = std::stol(trim_json_token(json));
    }
};

template<>
struct Serializer<long long> {
    static std::string serialize(const long long& value) {
        return std::to_string(value);
    }
    static void deserialize(const std::string& json, long long& value) {
        value = std::stoll(trim_json_token(json));
    }
};

template<>
struct Serializer<unsigned> {
    static std::string serialize(const unsigned& value) {
        return std::to_string(value);
    }
    static void deserialize(const std::string& json, unsigned& value) {
        value = static_cast<unsigned>(std::stoul(trim_json_token(json)));
    }
};

template<>
struct Serializer<unsigned long> {
    static std::string serialize(const unsigned long& value) {
        return std::to_string(value);
    }
    static void deserialize(const std::string& json, unsigned long& value) {
        value = std::stoul(trim_json_token(json));
    }
};

template<>
struct Serializer<unsigned long long> {
    static std::string serialize(const unsigned long long& value) {
        return std::to_string(value);
    }
    static void deserialize(const std::string& json, unsigned long long& value) {
        value = std::stoull(trim_json_token(json));
    }
};

template<>
struct Serializer<short> {
    static std::string serialize(const short& value) {
        return std::to_string(value);
    }
    static void deserialize(const std::string& json, short& value) {
        value = static_cast<short>(std::stoi(trim_json_token(json)));
    }
};

template<>
struct Serializer<unsigned short> {
    static std::string serialize(const unsigned short& value) {
        return std::to_string(value);
    }
    static void deserialize(const std::string& json, unsigned short& value) {
        value = static_cast<unsigned short>(std::stoul(trim_json_token(json)));
    }
};

template<>
struct Serializer<float> {
    static std::string serialize(const float& value) {
        return std::to_string(value);
    }
    static void deserialize(const std::string& json, float& value) {
        value = std::stof(trim_json_token(json));
    }
};

template<>
struct Serializer<double> {
    static std::string serialize(const double& value) {
        return std::to_string(value);
    }
    static void deserialize(const std::string& json, double& value) {
        value = std::stod(trim_json_token(json));
    }
};

template<>
struct Serializer<long double> {
    static std::string serialize(const long double& value) {
        return std::to_string(value);
    }
    static void deserialize(const std::string& json, long double& value) {
        value = std::stold(trim_json_token(json));
    }
};

template<>
struct Serializer<unsigned char> {
    static std::string serialize(const unsigned char& value) {
        return std::to_string(static_cast<unsigned int>(value));
    }
    static void deserialize(const std::string& json, unsigned char& value) {
        value = static_cast<unsigned char>(std::stoul(trim_json_token(json)));
    }
};

template<>
struct Serializer<bool> {
    static std::string serialize(const bool& value) {
        return value ? "true" : "false";
    }
    static void deserialize(const std::string& json, bool& value) {
        std::string token = trim_json_token(json);
        value = (token == "true");
    }
};

template<>
struct Serializer<char> {
    static std::string serialize(const char& value) {
        return std::string("\"") + value + "\"";
    }
    static void deserialize(const std::string& json, char& value) {
        std::string token = trim_json_token(json);
        if (token.size() < 3 || token.front() != '"' || token.back() != '"') {
            throw std::invalid_argument("Invalid JSON char");
        }
        value = token[1];
    }
};

template<>
struct Serializer<std::string> {
    static std::string serialize(const std::string& value) {
        return std::string("\"") + value + "\"";
    }
    static void deserialize(const std::string& json, std::string& value) {
        std::string token = trim_json_token(json);
        if (token.size() < 2 || token.front() != '"' || token.back() != '"') {
            throw std::invalid_argument("Invalid JSON string");
        }
        value = token.substr(1, token.size() - 2);
    }
};

template<typename T>
struct Serializer<std::vector<T>> {
    static std::string serialize(const std::vector<T>& value) {
        std::string result = "[";
        bool first = true;
        for (const auto& item : value) {
            if (!first) result += ",";
            first = false;
            result += Serializer<T>::serialize(item);
        }
        result += "]";
        return result;
    }

    static void deserialize(const std::string& json, std::vector<T>& value) {
        value.clear();

        std::string token = trim_json_token(json);
        if (token.size() < 2 || token.front() != '[' || token.back() != ']') {
            throw std::invalid_argument("Invalid JSON array");
        }

        std::string content = token.substr(1, token.size() - 2);
        if (content.empty()) return;

        size_t start = 0;
        bool in_quotes = false;
        for (size_t i = 0; i <= content.size(); ++i) {
            if (i == content.size() || (!in_quotes && content[i] == ',')) {
                std::string element = trim_json_token(content.substr(start, i - start));
                if (!element.empty()) {
                    T item{};
                    Serializer<T>::deserialize(element, item);
                    value.push_back(std::move(item));
                }
                start = i + 1;
            } else if (content[i] == '"') {
                in_quotes = !in_quotes;
            }
        }
    }
};