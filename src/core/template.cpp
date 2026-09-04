#include "template.hpp"

#include <cstddef>
#include <string>

std::string content::tmpl::render(
    std::string_view tmpl,
    const std::unordered_map<std::string, std::string> &context)
{
    std::string result;
    std::size_t pos = 0;

    while (true) {
        auto open_pos = tmpl.find("{{", pos);
        if (open_pos == std::string::npos) {
            result += tmpl.substr(pos);
            break;
        }
        result += tmpl.substr(pos, open_pos - pos);

        auto close_pos = tmpl.find("}}", open_pos);
        if (close_pos == std::string::npos) {
            result += tmpl.substr(open_pos);
            break;
        }

        auto key = tmpl.substr(open_pos + 2, close_pos - open_pos - 2);
        if (auto it = context.find(std::string(key)); it != context.end()) {
            result += it->second;
        }

        pos = close_pos + 2;
    }

    return result;
}
