#pragma once

#include <cstdint>
#include <ostream>
#include <string>
#include <variant>
#include <vector>

#include "lexer.hpp"

namespace md::parser {
constexpr std::uint8_t MAX_HEADERS = 6;
constexpr std::uint8_t MAX_STARS = 2;
constexpr std::uint8_t MAX_MINUS = 3;

struct Heading
{
    std::uint8_t level;
    std::string text;

    bool operator==(const Heading &) const = default;
};

inline std::ostream &operator<<(std::ostream &os, const Heading &h)
{
    return os << "Heading{level=" << static_cast<int>(h.level) << ", text=\""
              << h.text << "\"}";
};

struct Paragraph
{
    std::string text;

    bool operator==(const Paragraph &) const = default;
};

inline std::ostream &operator<<(std::ostream &os, const Paragraph &p)
{
    return os << "Paragraph{text=\"" << p.text << "\"}";
}

struct List
{
    std::vector<std::string> items;

    bool operator==(const List &) const = default;
};

inline std::ostream &operator<<(std::ostream &os, const List &l)
{
    os << "List{items=[";
    for (const auto &item : l.items) {
        os << "\"" << item << "\", ";
    }

    return os << "]\"}";
}

using Node = std::variant<Heading, Paragraph, List>;

inline std::ostream &operator<<(std::ostream &os, const Node &n)
{
    std::visit([&os](const auto &value) { os << value; }, n);
    return os;
}

std::vector<Node> parse(const std::vector<lexer::Token> &tokens);

} // namespace md::parser
