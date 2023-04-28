//
// Created by Maksym Pasichnyk on 25.04.2023.
//

module;

#include <map>
#include <string_view>

export module cpp_script:token;

export enum TokenType : uint32_t {
    TOKEN_EOF,
    TOKEN_ERROR,
    TOKEN_IDENTIFIER,

    TOKEN_KEYWORD_AUTO,
    TOKEN_KEYWORD_RETURN,

    TOKEN_STRING_LITERAL,
    TOKEN_INTEGER_LITERAL,
    TOKEN_FLOAT_LITERAL,
    TOKEN_TRUE_LITERAL,
    TOKEN_FALSE_LITERAL,
    TOKEN_NULL_LITERAL,

    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_CURLY,
    TOKEN_RIGHT_CURLY,
    TOKEN_LEFT_SQUARE,
    TOKEN_RIGHT_SQUARE,

    TOKEN_ARROW,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,

    TOKEN_EQUAL,

    TOKEN_COMMA,
    TOKEN_SEMICOLON,
};

export struct Token {
    TokenType           type;
    std::string_view    str;

    explicit Token() : type(TOKEN_EOF), str() {}
    explicit Token(TokenType type, std::string_view str) : type(type), str(str) {}
};

export struct TokenStream {
public:
    explicit TokenStream(std::string_view source) : source_(source), current_(0) {}
    
    [[nodiscard]] auto peekToken() const -> Token {
        return token_;
    }

    void readToken() {
        while (true) {
            if (current_ >= source_.size()) {
                token_ = Token(TOKEN_EOF, "");
                return;
            }

            if (std::isspace(source_[current_])) {
                current_ += 1;
                continue;
            }
            if (std::isdigit(source_[current_])) {
                auto start = current_;
                while (current_ < source_.size() && std::isdigit(source_[current_])) {
                    current_ += 1;
                }
                token_ = Token(TOKEN_INTEGER_LITERAL, source_.substr(start, current_ - start));
                return;
            }
            if (std::isalpha(source_[current_])) {
                auto start = current_;
                while (current_ < source_.size() && std::isalnum(source_[current_])) {
                    current_ += 1;
                }
                auto str = source_.substr(start, current_ - start);
                if (str == "null") {
                    token_ = Token(TOKEN_NULL_LITERAL, str);
                } else if (str == "true") {
                    token_ = Token(TOKEN_TRUE_LITERAL, str);
                } else if (str == "false") {
                    token_ = Token(TOKEN_FALSE_LITERAL, str);
                } else if (str == "auto") {
                    token_ = Token(TOKEN_KEYWORD_AUTO, str);
                } else if (str == "return") {
                    token_ = Token(TOKEN_KEYWORD_RETURN, str);
                } else {
                    token_ = Token(TOKEN_IDENTIFIER, str);
                }
                return;
            }

            switch (source_[current_]) {
                case '"' : {
                    current_ += 1;
                    auto start = current_;
                    while (current_ < source_.size() && source_[current_] != '"') {
                        current_ += 1;
                    }
                    if (current_ >= source_.size()) {
                        token_ = Token(TOKEN_ERROR, "");
                    }
                    auto end = current_;
                    current_ += 1;
                    token_ = Token(TOKEN_STRING_LITERAL, source_.substr(start, end - start));
                    return;
                }
                case '(': {
                    current_ += 1;
                    token_ = Token(TOKEN_LEFT_PAREN, "(");
                    return;
                }
                case ')': {
                    current_ += 1;
                    token_ = Token(TOKEN_RIGHT_PAREN, ")");
                    return;
                }
                case '{': {
                    current_ += 1;
                    token_ = Token(TOKEN_LEFT_CURLY, "{");
                    return;
                }
                case '}': {
                    current_ += 1;
                    token_ = Token(TOKEN_RIGHT_CURLY, "}");
                    return;
                }
                case '[': {
                    current_ += 1;
                    token_ = Token(TOKEN_LEFT_SQUARE, "[");
                    return;
                }
                case ']': {
                    current_ += 1;
                    token_ = Token(TOKEN_RIGHT_SQUARE, "]");
                    return;
                }
                case '+': {
                    current_ += 1;
                    token_ = Token(TOKEN_PLUS, "");
                    return;
                }
                case '-': {
                    current_ += 1;
                    if (source_[current_] == '>') {
                        current_ += 1;
                        token_ = Token(TOKEN_ARROW, "");
                    } else {
                        token_ = Token(TOKEN_MINUS, "");
                    }
                    return;
                }
                case '*': {
                    current_ += 1;
                    token_ = Token(TOKEN_STAR, "");
                    return;
                }
                case '/': {
                    current_ += 1;
                    token_ = Token(TOKEN_SLASH, "");
                    return;
                }
                case '=': {
                    current_ += 1;
                    token_ = Token(TOKEN_EQUAL, "");
                    return;
                }
                case ',': {
                    current_ += 1;
                    token_ = Token(TOKEN_COMMA, "");
                    return;
                }
                case ';': {
                    current_ += 1;
                    token_ = Token(TOKEN_SEMICOLON, "");
                    return;
                }
                default: {
                    current_ += 1;
                    token_ = Token(TOKEN_ERROR, "");
                    return;
                }
            }
        }
    }
    
private:
    std::string_view source_;
    size_t current_;
    Token token_;
};