#include "html.hpp"
#include <string>
#include <variant>

namespace {
std::string render_header(const md::parser::Node &node)
{
    const auto &h = std::get<md::parser::Heading>(node);
    return "<h" + std::to_string(h.level) + ">" + h.text + "</h" +
           std::to_string(h.level) + ">";
}
std::string render_list(const md::parser::Node &node)
{
    const auto &l = std::get<md::parser::List>(node);
    std::string output = "<ul>";
    for (const auto &i : l.items) {
        output += "<li>" + i + "</li>";
    }
    output += "</ul>";
    return output;
}
std::string render_paragraph(const md::parser::Node &node)
{
    const auto &p = std::get<md::parser::Paragraph>(node);
    return "<p>" + p.text + "</p>";
}
} // namespace

namespace md {
std::string html::render(const std::vector<parser::Node> &nodes)
{
    std::string output;

    for (const auto &node : nodes) {
        // TODO: std::visit and static_assert to not miss new node types
        if (std::holds_alternative<md::parser::Heading>(node)) {
            output += render_header(node);
        } else if (std::holds_alternative<md::parser::List>(node)) {
            output += render_list(node);
        } else if (std::holds_alternative<md::parser::Paragraph>(node)) {
            output += render_paragraph(node);
        }
    }

    return output;
}
} // namespace md
