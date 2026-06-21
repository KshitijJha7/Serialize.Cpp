#pragma once

#include "serializable.hpp"

#include <string>
#include <stdexcept>
#include <utility>
#include <cstddef>

inline std::string trim_json_token(const std::string& token) {
    const std::size_t first = token.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return {};
    }

    const std::size_t last = token.find_last_not_of(" \t\n\r");
    return token.substr(first, last - first + 1);
}

template<>
inline std::string Serializable<int>::serialize() const {
    return std::to_string(value);
}

template<>
inline void Serializable<int>::deserialize(const std::string& json) {
    value = std::stoi(trim_json_token(json));
}

template<>
inline std::string Serializable<long>::serialize() const {
    return std::to_string(value);
}

template<>
inline void Serializable<long>::deserialize(const std::string& json) {
    value = std::stol(trim_json_token(json));
}

template<>
inline std::string Serializable<long long>::serialize() const {
    return std::to_string(value);
}

template<>
inline void Serializable<long long>::deserialize(const std::string& json) {
    value = std::stoll(trim_json_token(json));
}

template<>
inline std::string Serializable<short>::serialize() const {
    return std::to_string(value);
}

template<>
inline void Serializable<short>::deserialize(const std::string& json) {
    value = static_cast<short>(std::stoi(trim_json_token(json)));
}

template<>
inline std::string Serializable<signed char>::serialize() const {
    return std::to_string(static_cast<int>(value));
}

template<>
inline void Serializable<signed char>::deserialize(const std::string& json) {
    value = static_cast<signed char>(std::stoi(trim_json_token(json)));
}

template<>
inline std::string Serializable<unsigned>::serialize() const {
    return std::to_string(value);
}

template<>
inline void Serializable<unsigned>::deserialize(const std::string& json) {
    value = static_cast<unsigned>(std::stoul(trim_json_token(json)));
}

template<>
inline std::string Serializable<unsigned long>::serialize() const {
    return std::to_string(value);
}

template<>
inline void Serializable<unsigned long>::deserialize(const std::string& json) {
    value = std::stoul(trim_json_token(json));
}

template<>
inline std::string Serializable<unsigned long long>::serialize() const {
    return std::to_string(value);
}

template<>
inline void Serializable<unsigned long long>::deserialize(const std::string& json) {
    value = std::stoull(trim_json_token(json));
}

template<>
inline std::string Serializable<unsigned short>::serialize() const {
    return std::to_string(value);
}

template<>
inline void Serializable<unsigned short>::deserialize(const std::string& json) {
    value = static_cast<unsigned short>(std::stoul(trim_json_token(json)));
}

template<>
inline std::string Serializable<unsigned char>::serialize() const {
    return std::to_string(static_cast<unsigned int>(value));
}

template<>
inline void Serializable<unsigned char>::deserialize(const std::string& json) {
    value = static_cast<unsigned char>(std::stoul(trim_json_token(json)));
}

// -------------------- floating point types --------------------

template<>
inline std::string Serializable<float>::serialize() const {
    return std::to_string(value);
}

template<>
inline void Serializable<float>::deserialize(const std::string& json) {
    value = std::stof(trim_json_token(json));
}

template<>
inline std::string Serializable<double>::serialize() const {
    return std::to_string(value);
}

template<>
inline void Serializable<double>::deserialize(const std::string& json) {
    value = std::stod(trim_json_token(json));
}

template<>
inline std::string Serializable<long double>::serialize() const {
    return std::to_string(value);
}

template<>
inline void Serializable<long double>::deserialize(const std::string& json) {
    value = std::stold(trim_json_token(json));
}

// -------------------- bool --------------------

template<>
inline std::string Serializable<bool>::serialize() const {
    return value ? "true" : "false";
}

template<>
inline void Serializable<bool>::deserialize(const std::string& json) {
    const std::string token = trim_json_token(json);

    if (token == "true") {
        value = true;
    } else if (token == "false") {
        value = false;
    } else {
        throw std::invalid_argument("Invalid JSON bool");
    }
}

// -------------------- char / string --------------------

template<>
inline std::string Serializable<char>::serialize() const {
    return std::string("\"") + value + "\"";
}

template<>
inline void Serializable<char>::deserialize(const std::string& json) {
    const std::string token = trim_json_token(json);

    if (token.size() != 3 || token.front() != '"' || token.back() != '"') {
        throw std::invalid_argument("Invalid JSON char");
    }

    value = token[1];
}

template<>
inline std::string Serializable<std::string>::serialize() const {
    return std::string("\"") + value + "\"";
}

template<>
inline void Serializable<std::string>::deserialize(const std::string& json) {
    const std::string token = trim_json_token(json);

    if (token.size() < 2 || token.front() != '"' || token.back() != '"') {
        throw std::invalid_argument("Invalid JSON string");
    }

    value = token.substr(1, token.size() - 2);
}