#pragma once
#include <cstdint> 
#include <utility> 

using namespace std;

class response {
private:
    uint32_t _status;

public:
    explicit response(uint32_t status) : _status(status) {}

    virtual ~response() = default;  

    uint32_t status() const noexcept { return _status; }
};

template<typename T>
class typed_response : public response {
private:
    T _value;

public:
    typed_response(uint32_t status, T value)
        : response(status), _value(std::move(value)) {
    }

    const T& value() const noexcept { return _value; }
};




