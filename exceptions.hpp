#include <stdexcept>
class accuracy_error : public std::runtime_error {
public:
    accuracy_error(const std::string& what) : std::runtime_error(what) {};
};
