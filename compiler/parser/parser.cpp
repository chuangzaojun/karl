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
            case TokenType::While:
                return parseWhileStmt();
            case TokenType::Func:
                return parseFuncDefStmt();
            case TokenType::If:
                return parseIfStmt();
            case TokenType::Break:
                return parseBreakStmt();
            case TokenType::Continue:
                return parseContinueStmt();
            case TokenType::Return:
                return parseReturnStmt();
            case TokenType::LBrace:
                return parseBlock();
        }
        return parseExprStmt();
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
                break;
            }
        }
        expect(TokenType::Semicolon);
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

    Stmt *Parser::parseBreakStmt() {
        BreakStmt *stmt = new BreakStmt(curToken->line, curToken->column);
        expect(TokenType::Break);
        expect(TokenType::Semicolon);
        return stmt;
    }

    Stmt *Parser::parseContinueStmt() {
        ContinueStmt *stmt = new ContinueStmt(curToken->line, curToken->column);
        expect(TokenType::Continue);
        expect(TokenType::Semicolon);
        return stmt;
    }

    Stmt *Parser::parseReturnStmt() {
        ReturnStmt *stmt = new ReturnStmt(nullptr, curToken->line, curToken->column);
        expect(TokenType::Continue);
        if (curToken->type != TokenType::Semicolon) {
            stmt->expr = parseExpr();
        }
        expect(TokenType::Semicolon);
    }

    Stmt *Parser::parseExprStmt() {
        ExprStmt *stmt = new ExprStmt(parseExpr(), 0, 0);
        stmt->line = stmt->expr->line;
        stmt->column = stmt->expr->column;
        return stmt;
    }

    Block *Parser::parseBlock() {
        Block *block = new Block(curToken->line, curToken->column);
        expect(TokenType::LBrace);
        while (curToken->type != TokenType::RBrace) {
            block->stmts.push_back(parseStmt());
        }
        expect(TokenType::RBrace);
        return block;
    }

    Expr *Parser::parseExpr0() {
        switch (curToken->type) {
            case TokenType::Identifier:
                if (nextToken->type == TokenType::LBracket) {
                    return parseArrayIndexExpr();
                }
                if (nextToken->type == TokenType::LParen) {
                    return parseFuncCallExpr();
                }
                return parseIdentifier();
            case TokenType::IntLiteral:
                return parseIntExpr();
            case TokenType::CharLiteral:
                return parseCharExpr();
            case TokenType::StringLiteral:
                return parseStringExpr();
            case TokenType::True:
            case TokenType::False:
                return parseBoolExpr();
        }
        return nullptr;
    }

    Expr *Parser::parseArrayIndexExpr() {
        ArrayIndexExpr *expr = new ArrayIndexExpr(parseIdentifier(), nullptr, curToken->line, curToken->column);
        expect(TokenType::LBracket);
        expr->index = parseExpr();
        expect(TokenType::RBracket);
        while (curToken->type == TokenType::LBracket) {
            expr = new ArrayIndexExpr(expr, nullptr, curToken->line, curToken->column);
            expect(TokenType::LBracket);
            expr->index = parseExpr();
            expect(TokenType::RBracket);
        }
        return expr;
    }

    Expr *Parser::parseFuncCallExpr() {
        FuncCallExpr *expr = new FuncCallExpr(parseIdentifier(), curToken->line, curToken->column);
        expect(TokenType::LParen);
        if (curToken->type != TokenType::RParen) {
            while (curToken->type != TokenType::RParen) {
                expr->argument.push_back(parseExpr());
                if (curToken->type == TokenType::Comma) {
                    advance();
                }
            }
        }
        expect(TokenType::RParen);
        return expr;
    }

    Expr *Parser::parseIntExpr() {
        IntExpr *expr = new IntExpr(std::stoi(curToken->literal), curToken->line, curToken->column);
        expect(TokenType::IntLiteral);
        return expr;
    }

    Expr *Parser::parseBoolExpr() {
        BoolExpr *expr = new BoolExpr(true, curToken->line, curToken->column);
        if (curToken->type == TokenType::False) {
            advance();
            expr->value = false;
        }
        expect(TokenType::True);
        return expr;
    }

    Expr *Parser::parseCharExpr() {
        CharExpr *expr = new CharExpr(curToken->literal[0], curToken->line, curToken->column);
        expect(TokenType::CharLiteral);
        return expr;
    }

    Expr *Parser::parseStringExpr() {
        StringExpr *expr = new StringExpr(curToken->literal, curToken->line, curToken->column);
        expect(TokenType::StringLiteral);
        return expr;
    }


} // karl