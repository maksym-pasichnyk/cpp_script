//
// Created by Maksym Pasichnyk on 25.04.2023.
//

module;

#include <map>
#include <list>
#include <array>
#include <string>
#include <vector>
#include <charconv>
#include <string_view>

export module cpp_script:ast;
import :ir;
import :gc;
import :token;
import :variant;

export class Expression : public ManagedObject {};

export class Statement : public ManagedObject {};

export class ConstExpression : public Expression {
public:
    explicit ConstExpression(int value) : value_(value) {}

    [[nodiscard]] auto getValue() const -> int {
        return value_;
    }

private:
    int value_;
};

export class VariableExpression : public Expression {
public:
    explicit VariableExpression(std::string name) : name_(std::move(name)) {}

    [[nodiscard]] auto getName() const -> std::string {
        return name_;
    }

private:
    std::string name_;
};

export class AddExpression : public Expression {
public:
    explicit AddExpression(ManagedShared<Expression> lhs, ManagedShared<Expression> rhs)
        : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    [[nodiscard]] auto getLhs() const -> const ManagedShared<Expression>& {
        return lhs_;
    }

    [[nodiscard]] auto getRhs() const -> const ManagedShared<Expression>& {
        return rhs_;
    }

private:
    ManagedShared<Expression> lhs_;
    ManagedShared<Expression> rhs_;
};

export class SubExpression : public Expression {
public:
    explicit SubExpression(ManagedShared<Expression> lhs, ManagedShared<Expression> rhs)
        : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    [[nodiscard]] auto getLhs() const -> const ManagedShared<Expression>& {
        return lhs_;
    }

    [[nodiscard]] auto getRhs() const -> const ManagedShared<Expression>& {
        return rhs_;
    }

private:
    ManagedShared<Expression> lhs_;
    ManagedShared<Expression> rhs_;
};

export class MulExpression : public Expression {
public:
    explicit MulExpression(ManagedShared<Expression> lhs, ManagedShared<Expression> rhs)
        : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    [[nodiscard]] auto getLhs() const -> const ManagedShared<Expression>& {
        return lhs_;
    }

    [[nodiscard]] auto getRhs() const -> const ManagedShared<Expression>& {
        return rhs_;
    }

private:
    ManagedShared<Expression> lhs_;
    ManagedShared<Expression> rhs_;
};

export class DivExpression : public Expression {
public:
    explicit DivExpression(ManagedShared<Expression> lhs, ManagedShared<Expression> rhs)
        : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    [[nodiscard]] auto getLhs() const -> const ManagedShared<Expression>& {
        return lhs_;
    }

    [[nodiscard]] auto getRhs() const -> const ManagedShared<Expression>& {
        return rhs_;
    }

private:
    ManagedShared<Expression> lhs_;
    ManagedShared<Expression> rhs_;
};

export class ModExpression : public Expression {
public:
    explicit ModExpression(ManagedShared<Expression> lhs, ManagedShared<Expression> rhs)
        : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    [[nodiscard]] auto getLhs() const -> const ManagedShared<Expression>& {
        return lhs_;
    }

    [[nodiscard]] auto getRhs() const -> const ManagedShared<Expression>& {
        return rhs_;
    }

private:
    ManagedShared<Expression> lhs_;
    ManagedShared<Expression> rhs_;
};

export class AssignExpression : public Expression {
public:
    explicit AssignExpression(ManagedShared<Expression> lhs, ManagedShared<Expression> rhs)
        : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    [[nodiscard]] auto getLhs() const -> const ManagedShared<Expression>& {
        return lhs_;
    }

    [[nodiscard]] auto getRhs() const -> const ManagedShared<Expression>& {
        return rhs_;
    }

private:
    ManagedShared<Expression> lhs_;
    ManagedShared<Expression> rhs_;
};

export class NegExpression : public Expression {
public:
    explicit NegExpression(ManagedShared<Expression> expr)
        : expr_(std::move(expr)) {}

    [[nodiscard]] auto getExpr() const -> const ManagedShared<Expression>& {
        return expr_;
    }

private:
    ManagedShared<Expression> expr_;
};

export class CallExpression : public Expression {
public:
    explicit CallExpression(ManagedShared<Expression> callee, std::vector<ManagedShared<Expression>> args)
        : callee_(std::move(callee)), args_(std::move(args)) {}

    [[nodiscard]] auto getCallee() const -> const ManagedShared<Expression>& {
        return callee_;
    }

    [[nodiscard]] auto getArgs() const -> const std::vector<ManagedShared<Expression>>& {
        return args_;
    }

private:
    ManagedShared<Expression> callee_;
    std::vector<ManagedShared<Expression>> args_;
};

export class ExpressionStatement : public Statement {
public:
    explicit ExpressionStatement(ManagedShared<Expression> expr) : expr_(std::move(expr)) {}

    [[nodiscard]] auto getExpr() const -> const ManagedShared<Expression>& {
        return expr_;
    }

private:
    ManagedShared<Expression> expr_;
};

export class ReturnStatement : public Statement {
public:
    explicit ReturnStatement(ManagedShared<Expression> expr) : expr_(expr) {}

    [[nodiscard]] auto getExpr() const -> const ManagedShared<Expression>& {
        return expr_;
    }

private:
    ManagedShared<Expression> expr_;
};

export class VariableDeclarationStatement : public Statement {
public:
    explicit VariableDeclarationStatement(std::string name, ManagedShared<Expression> initializer)
        : name_(std::move(name)), initializer_(std::move(initializer)) {}

    [[nodiscard]] auto getName() const -> std::string {
        return name_;
    }

    [[nodiscard]] auto getInitializer() const -> const ManagedShared<Expression>& {
        return initializer_;
    }

private:
    std::string name_;
    ManagedShared<Expression> initializer_;
};

export class FunctionDeclarationStatement : public Statement {
public:
    explicit FunctionDeclarationStatement(std::string name, std::vector<std::string> args, std::vector<ManagedShared<Statement>> body)
        : name_(std::move(name)), args_(std::move(args)), body_(std::move(body)) {}

    [[nodiscard]] auto getName() const -> std::string {
        return name_;
    }

    [[nodiscard]] auto getArgs() const -> const std::vector<std::string>& {
        return args_;
    }

    [[nodiscard]] auto getBody() const -> const std::vector<ManagedShared<Statement>>& {
        return body_;
    }

private:
    std::string name_;
    std::vector<std::string> args_;
    std::vector<ManagedShared<Statement>> body_;
};

static auto parseInteger(std::string_view str) -> int {
    int result = 0;
    std::from_chars(str.data(), str.data() + str.size(), result);
    return result;
}

auto parseStatement(TokenStream& stream) -> ManagedShared<Statement>;
auto parseStatements(TokenStream& stream) -> std::vector<ManagedShared<Statement>>;
auto parsePrimaryExpression(TokenStream& stream) -> ManagedShared<Expression>;
auto parseExpression(TokenStream& stream) -> ManagedShared<Expression>;
auto parseAssignment(TokenStream& stream) -> ManagedShared<Expression>;
auto parseArithmetic(TokenStream& stream) -> ManagedShared<Expression>;
auto parseMultiplication(TokenStream& stream) -> ManagedShared<Expression>;
auto parsePrefixExpression(TokenStream& stream) -> ManagedShared<Expression>;
auto parsePostfixExpression(TokenStream& stream) -> ManagedShared<Expression>;

auto parseExpression(TokenStream& stream) -> ManagedShared<Expression> {
    return parseAssignment(stream);
}

auto parseAssignment(TokenStream& stream) -> ManagedShared<Expression> {
    auto lhs = parseArithmetic(stream);
    if (stream.peekToken().type == TOKEN_EQUAL) {
        stream.readToken();
        auto rhs = parseArithmetic(stream);
        return ManagedShared(new AssignExpression(lhs, rhs));
    }
    return lhs;
}

auto parseArithmetic(TokenStream& stream) -> ManagedShared<Expression> {
    auto lhs = parseMultiplication(stream);
    while (stream.peekToken().type != TOKEN_EOF) {
        switch (stream.peekToken().type) {
            case TOKEN_PLUS: {
                stream.readToken();
                auto rhs = parseMultiplication(stream);
                lhs = ManagedShared(new AddExpression(lhs, rhs));
                break;
            }
            case TOKEN_MINUS: {
                stream.readToken();
                auto rhs = parseMultiplication(stream);
                lhs = ManagedShared(new SubExpression(lhs, rhs));
                break;
            }
            default: {
                return lhs;
            }
        }
    }
    return lhs;
}

auto parseMultiplication(TokenStream& stream) -> ManagedShared<Expression> {
    auto lhs = parsePrefixExpression(stream);
    while (stream.peekToken().type != TOKEN_EOF) {
        switch (stream.peekToken().type) {
            case TOKEN_STAR: {
                stream.readToken();
                auto rhs = parsePrefixExpression(stream);
                lhs = ManagedShared(new MulExpression(lhs, rhs));
                break;
            }
            case TOKEN_SLASH: {
                stream.readToken();
                auto rhs = parsePrefixExpression(stream);
                lhs = ManagedShared(new DivExpression(lhs, rhs));
                break;
            }
            default: {
                return lhs;
            }
        }
    }
    return lhs;
}

auto parsePrefixExpression(TokenStream& stream) -> ManagedShared<Expression> {
    if (stream.peekToken().type == TOKEN_MINUS) {
        stream.readToken();
        auto e = parsePostfixExpression(stream);
        return ManagedShared(new NegExpression(e));
    }
    if (stream.peekToken().type == TOKEN_PLUS) {
        stream.readToken();
        return parsePostfixExpression(stream);
    }
    return parsePostfixExpression(stream);
}

auto parsePostfixExpression(TokenStream& stream) -> ManagedShared<Expression> {
    auto lhs = parsePrimaryExpression(stream);
    while (stream.peekToken().type != TOKEN_EOF) {
        if (stream.peekToken().type == TOKEN_LEFT_PAREN) {
            stream.readToken();

            std::vector<ManagedShared<Expression>> args;
            if (stream.peekToken().type != TOKEN_RIGHT_PAREN) {
                args.push_back(parseExpression(stream));
                while (stream.peekToken().type == TOKEN_COMMA) {
                    stream.readToken();
                    args.push_back(parseExpression(stream));
                }
                if (stream.peekToken().type != TOKEN_RIGHT_PAREN) {
                    std::fprintf(stderr, "Expected ')'\n");
                    abort();
                }
            }
            stream.readToken();
            lhs = ManagedShared(new CallExpression(lhs, args));
            continue;
        }
        break;
    }
    return lhs;
}

auto parsePrimaryExpression(TokenStream& stream) -> ManagedShared<Expression> {
    if (stream.peekToken().type == TOKEN_LEFT_PAREN) {
        stream.readToken();
        auto e = parseExpression(stream);
        if (stream.peekToken().type != TOKEN_RIGHT_PAREN) {
            std::fprintf(stderr, "Expected ')'\n");
            abort();
        }
        stream.readToken();
        return e;
    }
    if (stream.peekToken().type == TOKEN_INTEGER_LITERAL) {
        auto number = parseInteger(stream.peekToken().str);
        stream.readToken();
        return ManagedShared(new ConstExpression(number));
    }
    if (stream.peekToken().type == TOKEN_IDENTIFIER) {
        auto variable = stream.peekToken().str;
        stream.readToken();
        return ManagedShared(new VariableExpression(std::string(variable)));
    }
    std::fprintf(stderr, "Unexpected token: %.*s\n", (int) stream.peekToken().str.size(), stream.peekToken().str.data());
    abort();
}

auto parseTypename(TokenStream& stream) -> std::string {
    if (stream.peekToken().type == TOKEN_KEYWORD_AUTO) {
        stream.readToken();
        return "auto";
    }
    if (stream.peekToken().type == TOKEN_IDENTIFIER) {
        auto name = std::string(stream.peekToken().str);
        stream.readToken();
        return name;
    }
    std::fprintf(stderr, "Expected typename\n");
    abort();
}

auto parseIdentifier(TokenStream& stream) -> std::string {
    if (stream.peekToken().type == TOKEN_IDENTIFIER) {
        auto name = std::string(stream.peekToken().str);
        stream.readToken();
        return name;
    }
    std::fprintf(stderr, "Expected identifier\n");
    abort();
}

auto parseStatement(TokenStream& stream) -> ManagedShared<Statement> {
    if (stream.peekToken().type == TOKEN_KEYWORD_AUTO) {
        stream.readToken();

        if (stream.peekToken().type != TOKEN_IDENTIFIER) {
            std::fprintf(stderr, "Expected identifier\n");
            abort();
        }

        auto name = stream.peekToken().str;
        stream.readToken();

        if (stream.peekToken().type == TOKEN_EQUAL) {
            stream.readToken();

            auto initializer = parseExpression(stream);

            if (stream.peekToken().type != TOKEN_SEMICOLON) {
                std::fprintf(stderr, "Expected ';'\n");
                abort();
            }

            stream.readToken();

            return ManagedShared(new VariableDeclarationStatement(std::string(name), initializer));
        }

        if (stream.peekToken().type == TOKEN_LEFT_PAREN) {
            stream.readToken();

            std::vector<std::string> args;
            if (stream.peekToken().type != TOKEN_RIGHT_PAREN) {
                while (true) {
                    auto arg_type = parseTypename(stream);
                    auto arg_name = parseIdentifier(stream);
                    args.emplace_back(arg_name);

                    if (stream.peekToken().type != TOKEN_COMMA) {
                        break;
                    }

                    stream.readToken();
                }

                if (stream.peekToken().type != TOKEN_RIGHT_PAREN) {
                    std::fprintf(stderr, "Expected ')'\n");
                    abort();
                }
            }
            stream.readToken();

            if (stream.peekToken().type == TOKEN_ARROW) {
                stream.readToken();

                auto return_type = parseTypename(stream);
            }

            if (stream.peekToken().type != TOKEN_LEFT_CURLY) {
                std::fprintf(stderr, "Expected '{'\n");
                abort();
            }
            stream.readToken();

            std::vector<ManagedShared<Statement>> statements;
            while (stream.peekToken().type != TOKEN_RIGHT_CURLY) {
                statements.emplace_back(parseStatement(stream));
            }
            stream.readToken();

            return ManagedShared(new FunctionDeclarationStatement(std::string(name), args, statements));
        }

        fprintf(stderr, "declaration of variable '%.*s' with deduced type 'auto' requires an initializer", (int) name.size(), name.data());
        abort();
    }

    if (stream.peekToken().type == TOKEN_KEYWORD_RETURN) {
        stream.readToken();

        auto e = parseExpression(stream);

        if (stream.peekToken().type != TOKEN_SEMICOLON) {
            std::fprintf(stderr, "Expected ';'\n");
            abort();
        }

        stream.readToken();

        return ManagedShared(new ReturnStatement(e));
    }

    auto e = parseExpression(stream);

    if (stream.peekToken().type != TOKEN_SEMICOLON) {
        std::fprintf(stderr, "Expected ';'\n");
        abort();
    }

    stream.readToken();

    return ManagedShared(new ExpressionStatement(e));
}

auto parseStatements(TokenStream& stream) -> std::vector<ManagedShared<Statement>> {
    std::vector<ManagedShared<Statement>> statements;
    while (stream.peekToken().type != TOKEN_EOF) {
        statements.emplace_back(parseStatement(stream));
    }
    return statements;
}

class Chunk : public ManagedObject {
public:
    ManagedShared<Chunk> parent;
    std::vector<int> opcodes;
    std::map<std::string, int> variables;
    std::map<std::string, ManagedShared<Chunk>> functions;

    auto getVariable(const std::string& name) -> int {
        if (auto it = variables.find(name); it != variables.end()) {
            return it->second;
        }
        if (parent.get() != nullptr) {
            return parent->getVariable(name);
        }
        fprintf(stderr, "Unknown variable '%s'\n", name.c_str());
        abort();
    }
};

class ASTVisitor {
public:
    ManagedShared<Chunk> chunk;

    ASTVisitor() {
        chunk = ManagedShared(new Chunk());
    }

    void accept(Statement* statement) {
        if (auto stmt = dynamic_cast<ExpressionStatement*>(statement)) {
            visitExpressionStatement(stmt);
            return;
        }
        if (auto stmt = dynamic_cast<VariableDeclarationStatement*>(statement)) {
            visitVariableDeclarationStatement(stmt);
            return;
        }
        if (auto stmt = dynamic_cast<ReturnStatement*>(statement)) {
            visitReturnStatement(stmt);
            return;
        }
        if (auto stmt = dynamic_cast<FunctionDeclarationStatement*>(statement)) {
            visitFunctionDeclarationStatement(stmt);
            return;
        }
        std::fprintf(stderr, "Unknown statement type\n");
        abort();
    }

    void accept(Expression* expression) {
        if (auto expr = dynamic_cast<ConstExpression*>(expression)) {
            return visitConstExpression(expr);
        }
        if (auto expr = dynamic_cast<VariableExpression*>(expression)) {
            return visitVariableExpression(expr);
        }
        if (auto expr = dynamic_cast<CallExpression*>(expression)) {
            return visitCallExpression(expr);
        }
        if (auto expr = dynamic_cast<AddExpression*>(expression)) {
            return visitAddExpression(expr);
        }
        if (auto expr = dynamic_cast<SubExpression*>(expression)) {
            return visitSubExpression(expr);
        }
        if (auto expr = dynamic_cast<MulExpression*>(expression)) {
            return visitMulExpression(expr);
        }
        if (auto expr = dynamic_cast<DivExpression*>(expression)) {
            return visitDivExpression(expr);
        }
        if (auto expr = dynamic_cast<ModExpression*>(expression)) {
            return visitModExpression(expr);
        }
        if (auto expr = dynamic_cast<NegExpression*>(expression)) {
            return visitNegExpression(expr);
        }
        if (auto expr = dynamic_cast<AssignExpression*>(expression)) {
            return visitAssignExpression(expr);
        }
        fprintf(stderr, "Unknown expression type\n");
        abort();
    }

    void visitConstExpression(ConstExpression* expr) {
        chunk->opcodes.emplace_back(OP_PUSH);
        chunk->opcodes.emplace_back(expr->getValue());
    }

    void visitVariableExpression(VariableExpression* expr) {
        chunk->opcodes.emplace_back(OP_GET_LOCAL);
        chunk->opcodes.emplace_back(chunk->variables.at(expr->getName()));
    }

    void visitCallExpression(CallExpression* expr) {
        auto variable = dynamic_cast<VariableExpression*>(expr->getCallee().get());
        if (variable->getName() == "print") {
            for (auto& arg : expr->getArgs()) {
                accept(arg.get());
            }
            chunk->opcodes.emplace_back(OP_PRINT);
            chunk->opcodes.emplace_back(expr->getArgs().size());
            return;
        }
        abort();
    }

    void visitAddExpression(AddExpression* expr) {
        accept(expr->getLhs().get());
        accept(expr->getRhs().get());
        chunk->opcodes.emplace_back(OP_ADD);
    }

    void visitSubExpression(SubExpression* expr) {
        accept(expr->getLhs().get());
        accept(expr->getRhs().get());
        chunk->opcodes.emplace_back(OP_SUB);
    }

    void visitMulExpression(MulExpression* expr) {
        accept(expr->getLhs().get());
        accept(expr->getRhs().get());
        chunk->opcodes.emplace_back(OP_MUL);
    }

    void visitDivExpression(DivExpression* expr) {
        accept(expr->getLhs().get());
        accept(expr->getRhs().get());
        chunk->opcodes.emplace_back(OP_DIV);
    }

    void visitModExpression(ModExpression* expr) {
        abort();
    }

    void visitNegExpression(NegExpression* expr) {
        accept(expr->getExpr().get());
        chunk->opcodes.emplace_back(OP_NEG);
    }

    void visitAssignExpression(AssignExpression* expr) {
        auto variable = dynamic_cast<VariableExpression*>(expr->getLhs().get());
        accept(expr->getRhs().get());
        chunk->opcodes.emplace_back(OP_SET_LOCAL);
        chunk->opcodes.emplace_back(chunk->variables.at(variable->getName()));
    }

    void visitExpressionStatement(ExpressionStatement* stmt) {
        accept(stmt->getExpr().get());
    }

    void visitVariableDeclarationStatement(VariableDeclarationStatement* stmt) {
        accept(stmt->getInitializer().get());
        auto variable = chunk->variables.size();
        chunk->opcodes.emplace_back(OP_SET_LOCAL);
        chunk->opcodes.emplace_back(variable);
        chunk->variables.insert_or_assign(stmt->getName(), variable);
    }

    void visitReturnStatement(ReturnStatement* stmt) {
        abort();
    }

    void visitFunctionDeclarationStatement(FunctionDeclarationStatement* stmt) {
        abort();
    }
};

export void evaluate(TokenStream& stream) {
    ASTVisitor visitor;
    auto statements = parseStatements(stream);
    for (auto& statement : statements) {
        visitor.accept(statement.get());
    }
    statements.clear();
    visitor.chunk->opcodes.emplace_back(OP_HALT);
//    disassemble(visitor.chunk->opcodes.data(), visitor.chunk->opcodes.size());
    execute(visitor.chunk->opcodes.data(), 0);
}
