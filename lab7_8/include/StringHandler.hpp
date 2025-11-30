#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

class StringHandler {
  public:
    static std::vector<std::string>* divideLineIntoTokensAndCommand(const std::string &line, std::string &command);
    static bool isNumber(const std::string& str);
    static float stringToFloat(const std::string& str);
};
