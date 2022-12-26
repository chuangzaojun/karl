#include "parser.hpp"
#include "../../error/error.hpp"
#include <map>

namespace karl {
    Parser::Parser(karl::Lexer *lexer) {
        this->lexer = lexer;
        this->curToken = nullptr;
        this->nextToken = nullptr;
        advance();
        advance();
    }

    void Parser::advance() {
        if (curToken != nullptr) {
            delete curToken;
        }
        curToken = nextToken;
        nextToken = lexer->nextToken();
    }

    Program *Parser::parseProgram() {
        Program *program = new Program();
        while (curToken->type != TokenType::EndOfFile) {
            program->stmts.push_back(parseStmt());
        }
        return program;
    }

    void Parser::skip(TokenType type) {
        while (curToken->type == type) {
            advance();
        }
    }

    void Parser::expect(TokenType type) {
        if (curToken->type == type) {
            advance();
        } else {
            grammarError(type,curToken);
        }
    }

    Stmt *Parser::parseStmt() {
        switch (curToken->type) {
            case TokenType::Var:
                return parseVarDefStmt();
        }
    }

    ObjectType *Parser::parseType() {
        ObjectType *type = parseSingleType();
        while (curToken->type == TokenType::LBracket && nextToken->type == TokenType::IntLiteral) {
            type = new ArrayObject(type, std::stoi(nextToken->literal));
            advance();
            advance();
            expect(TokenType::RBracket);
        }
        return type;
    }

    ObjectType *Parser::parseSingleType() {
        switch (curToken->type) {
            case TokenType::Int:
                advance();
                return new IntObject();
            case TokenType::True:
            case TokenType::False:
                advance();
                return new BoolObject();
            case TokenType::Char:
                advance();
                return new CharObject();
            case TokenType::String:
                advance();
                return new StringObject();
        }
        grammarError(curToken);
        return nullptr;
    }

    Expr *Parser::parseIdentifier() {
        IdentifierExpr *expr = new IdentifierExpr(curToken->literal, curToken->line, curToken->column);
        expect(TokenType::Identifier);
        return expr;
    }

    Stmt *Parser::parseVarDefStmt() {
        VarDefStmt *stmt = new VarDefStmt(curToken->line, curToken->column);
        expect(TokenType::Func);
        while (true) {
            stmt->vars.push_back(parseExpr());
            expect(TokenType::Colon);
            stmt->types.push_back(parseType());
            if (curToken->type == TokenType::Assign) {
                advance();
                stmt->initValues.push_back(parseExpr());
            } else {
                stmt->initValues.push_back(nullptr);
            }
            if (curToken->type == TokenType::Comma) {
                advance();
            } else {
                expect(TokenType::Semicolon);
                break;
            }
        }
        return stmt;
    }

    Stmt *Parser::parseFuncDefStmt() {
        expect(TokenType::Func);
        FuncDefStmt *stmt = new FuncDefStmt(parseIdentifier(), nullptr, curToken->line, curToken->column);
        expect(TokenType::LParen);
        if (curToken->type != TokenType::RParen) {
            while (true) {
                stmt->parameters.push_back(parseExpr());
                expect(TokenType::Colon);
                stmt->parameterTypes.push_back(parseType());
                if (curToken->type == TokenType::Comma) {
                    advance();
                } else {
                    expect(TokenType::RParen);
                    break;
                }
            }
        }
        stmt->block = parseBlock();
        return stmt;
    }

    Stmt *Parser::parseWhileStmt() {
        expect(TokenType::While);
        expect(TokenType::LParen);
        WhileStmt *stmt = new WhileStmt(parseExpr(), nullptr, curToken->line, curToken->column);
        expect(TokenType::RParen);
        stmt->block = parseBlock();
        return stmt;
    }

    Stmt *Parser::parseIfStmt() {
        IfStmt *stmt = new IfStmt(curToken->line, curToken->column);
        expect(TokenType::If);
        expect(TokenType::LParen);
        stmt->conditions.push_back(parseExpr());
        expect(TokenType::RParen);
        stmt->blocks.push_back(parseBlock());
        while (curToken->type == TokenType::Elif) {
            advance();
            expect(TokenType::LParen);
            stmt->conditions.push_back(parseExpr());
            expect(TokenType::RParen);
            stmt->blocks.push_back(parseBlock());
        }
        if (curToken->type == TokenType::Else) {
            advance();
            stmt->blocks.push_back(parseBlock());
        }
        return stmt;
    }


} // karl