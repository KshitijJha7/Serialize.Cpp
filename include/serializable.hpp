#pragma once

#include <string>
#include <utility>
#include "serializable_base.hpp"

template<typename T>
class Serializable : public SerializableBase<T> {
    public:
        using SerializableBase<T>::SerializableBase;
        std::string serialize() const;
        void deserialize(const std::string& json);
};