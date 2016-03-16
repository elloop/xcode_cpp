_Pragma("once")

#include "inc.h"
#include <string>

NS_BEGIN(elloop);
NS_BEGIN(string_algorithm);

class StringAlgoSolution {
public:
    StringAlgoSolution();
    ~StringAlgoSolution();
    void run();
    bool string_contain_stupid(const std::string& sa, const std::string& sb) const;
    bool string_contain_binary_search(std::string& sa, const std::string& sb) const;
    bool string_contain_hash(const std::string& sa, const std::string& sb) const;
    bool string_contain_bit_flag(const std::string& sa, const std::string& sb) const;
};

NS_END(string_algorithm);
NS_END(elloop);



