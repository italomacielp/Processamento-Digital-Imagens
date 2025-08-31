#include <exception>
#include <string>

class ImageException : public std::exception {
private:
    std::string message;
public:
    explicit ImageException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};
