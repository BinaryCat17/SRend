#include "stringUtils.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace utils
{
  std::string readIsToString(std::istream &is)
  {
    std::ostringstream oss;
    oss << is.rdbuf();
    return oss.str();
  }

  std::string readFileToString(std::filesystem::path const &path)
  {
    std::ifstream fin(path);
    return readIsToString(fin);
  }

  std::vector<std::string> readIsToStringVec(std::istream &is)
  {
    std::vector<std::string> result;
    for (std::string line; getline(is, line); result.push_back(line))
      ;
    return result;
  }

  std::vector<std::string> readFileToStringVec(std::filesystem::path const &path)
  {
    std::ifstream fin(path);
    return readIsToStringVec(fin);
  }

  std::string stringVecToString(std::vector<std::string> const &src)
  {
    std::string result;
    for (auto const &str : src)
    {
      result += str;
    }
    return result;
  }

  std::string strVecToStr(std::vector<std::string> const &vec)
  {
    std::string result;
    for (auto const &str : vec)
    {
      result += str;
    }
    return result;
  }

}  // namespace utils