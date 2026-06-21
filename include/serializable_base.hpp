#pragma once
template<typename T>
class SerializableBase {

protected:
    T value;

public:

    SerializableBase() = default;
    SerializableBase(const T& v): value(v){}
    SerializableBase(T&& v): value(std::move(v)){}
    
    operator T&() {
        return value;
    }

    operator const T&() const {
        return value;
    }

    SerializableBase& operator=(const T& v) {
        value = v;
        return *this;
    }

    SerializableBase& operator=(T&& v) {
        value = std::move(v);
        return *this;
    }

    T& get() {
        return value;
    }

    const T& get() const {
        return value;
    }
};