#include <string>
#include <vector>

#include "parser.hpp"

namespace md::html {
std::string render(const std::vector<parser::Node> &nodes);
}
