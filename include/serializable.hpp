#pragma once

#include <string>
#include <utility>

template<typename T>
struct Serializer;

template<typename T>
class Serializable {

protected:
    T value;

public:

    Serializable() = default;

    Serializable(const T& v)
        : value(v)
    {}

    Serializable(T&& v)
        : value(std::move(v))
    {}

    operator T&() {
        return value;
    }

    operator const T&() const {
        return value;
    }

    Serializable& operator=(const T& v) {
        value = v;
        return *this;
    }

    Serializable& operator=(T&& v) {
        value = std::move(v);
        return *this;
    }

    T& get() {
        return value;
    }

    const T& get() const {
        return value;
    }

    std::string serialize() const {
        return Serializer<T>::serialize(value);
    }

    void deserialize(const std::string& json) {
        Serializer<T>::deserialize(json, value);
    }
};