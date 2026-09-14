#pragma once

#include <functional>
#include <string>
#include <map>

namespace athena {

class UCIOption {
public:
    using Callback = std::function<void(const UCIOption&)>;

    UCIOption(Callback cb = nullptr);
    UCIOption(bool value, Callback cb = nullptr);
    UCIOption(int value, int min, int max, Callback cb = nullptr);
    UCIOption(const char* value, Callback cb = nullptr);
    UCIOption(const char* values, const char* current, Callback cb = nullptr);

    operator int() const;
    operator bool() const;
    operator std::string() const;
    bool operator==(const char* s) const;
    bool operator!=(const char* s) const;

    UCIOption& operator=(const std::string& value);

private:
    friend std::ostream& operator<<(std::ostream&, const UCIOption&);

    std::string type;
    std::string default_value;
    std::string current_value;
    int min = 0;
    int max = 0;
    Callback callback;
};

class Options {
public:
    void addoption(std::string name, UCIOption option);
    void setoption(std::istream& is);

    const UCIOption& operator[](const std::string& name) const;
    
private:
    friend std::ostream& operator<<(std::ostream&, const Options&);

    std::map<std::string, UCIOption> map;
};

} // namespace athena