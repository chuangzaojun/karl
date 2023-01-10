#include "parser.hpp"
#include "../error/error.hpp"
#include <map>
#include <iostream>

namespace karl::compiler {

    Parser::Parser(Lexer *lexer) {
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
            grammarError(type, curToken);
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
                return parseBlock(false);
            case TokenType::Semicolon:
                advance();
                return parseStmt();
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
            case TokenType::Void:
                advance();
                return new VoidObject();
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
        expect(TokenType::Var);
        while (true) {
            stmt->vars.push_back(parseIdentifier());
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
                    break;
                }
            }
        }
        expect(TokenType::RParen);
        expect(TokenType::Colon);
        stmt->objectType = parseType();
        stmt->block = parseBlock(false);
        return stmt;
    }

    Stmt *Parser::parseWhileStmt() {
        expect(TokenType::While);
        expect(TokenType::LParen);
        WhileStmt *stmt = new WhileStmt(parseExpr(), nullptr, curToken->line, curToken->column);
        expect(TokenType::RParen);
        stmt->block = parseBlock(true);
        return stmt;
    }

    Stmt *Parser::parseIfStmt() {
        IfStmt *stmt = new IfStmt(curToken->line, curToken->column);
        expect(TokenType::If);
        expect(TokenType::LParen);
        stmt->conditions.push_back(parseExpr());
        expect(TokenType::RParen);
        stmt->blocks.push_back(parseBlock(false));
        while (curToken->type == TokenType::Elif) {
            advance();
            expect(TokenType::LParen);
            stmt->conditions.push_back(parseExpr());
            expect(TokenType::RParen);
            stmt->blocks.push_back(parseBlock(false));
        }
        if (curToken->type == TokenType::Else) {
            advance();
            stmt->blocks.push_back(parseBlock(false));
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
        expect(TokenType::Return);
        if (curToken->type != TokenType::Semicolon) {
            stmt->expr = parseExpr();
        }
        expect(TokenType::Semicolon);
        return stmt;
    }

    Stmt *Parser::parseExprStmt() {
        ExprStmt *stmt = new ExprStmt(parseExpr(), 0, 0);
        stmt->line = stmt->expr->line;
        stmt->column = stmt->expr->column;
        expect(TokenType::Semicolon);
        return stmt;
    }

    Block *Parser::parseBlock(bool isLoopBlock) {
        Block *block = new Block(isLoopBlock, curToken->line, curToken->column);
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
            case TokenType::Int:
            case TokenType::Char:
            case TokenType::String:
                return parseTypeConversionExpr();
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
                expr->arguments.push_back(parseExpr());
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

    Expr *Parser::parseTypeConversionExpr() {
        TypeConversionExpr *expr = new TypeConversionExpr(SingleObjectType::_, nullptr, curToken->line,
                                                          curToken->column);
        if (curToken->type == TokenType::Int) {
            expr->targetType = SingleObjectType::Int;
        } else if (curToken->type == TokenType::Char) {
            expr->targetType = SingleObjectType::Char;
        } else {
            expect(TokenType::String);
            expr->targetType = SingleObjectType::String;
        }
        expect(TokenType::LParen);
        expr->expr = parseExpr();
        expect(TokenType::RParen);
        return expr;
    }

    std::map<TokenType, OpType> tokenToOpType = {
            {TokenType::Assign, OpType::Assign},
            {TokenType::Minus, OpType::Minus},
            {TokenType::Add, OpType::Add},
            {TokenType::Mul, OpType::Mul},
            {TokenType::Div, OpType::Div},
            {TokenType::Mod, OpType::Mod},
            {TokenType::LessThan, OpType::LessThan},
            {TokenType::LessEqual, OpType::LessEqual},
            {TokenType::GreaterThan, OpType::GreaterThan},
            {TokenType::GreaterEqual, OpType::GreaterEqual},
            {TokenType::Equal, OpType::Equal},
            {TokenType::NotEqual, OpType::NotEqual},
            {TokenType::And, OpType::And},
            {TokenType::Or, OpType::Or},
            {TokenType::Not, OpType::Not},
            {TokenType::BAnd, OpType::BAnd},
            {TokenType::BOr, OpType::BOr},
            {TokenType::BNot, OpType::BNot},
            {TokenType::BXor, OpType::BXor},
            {TokenType::LMove, OpType::LMove},
            {TokenType::RMove, OpType::RMove}
    };

    Expr *Parser::parseExpr1() {
        switch (curToken->type) {
            case TokenType::Minus:
            case TokenType::Not:
            case TokenType::BNot:
            case TokenType::Add:
                PrefixExpr *expr = new PrefixExpr(tokenToOpType[curToken->type], nullptr, curToken->line,
                                                  curToken->column);
                advance();
                expr->right = parseExpr0();
                return expr;
        }
        return parseExpr0();
    }

    Expr *Parser::parseExpr2() {
        Expr *expr = parseExpr1();
        while (curToken->type == TokenType::Mul || curToken->type == TokenType::Div ||
               curToken->type == TokenType::Mod) {
            expr = new BinaryExpr(expr, tokenToOpType[curToken->type], nullptr, curToken->line, curToken->column);
            advance();
            ((BinaryExpr *) expr)->right = parseExpr1();
        }
        return expr;
    }

    Expr *Parser::parseExpr3() {
        Expr *expr = parseExpr2();
        while (curToken->type == TokenType::Add || curToken->type == TokenType::Minus) {
            expr = new BinaryExpr(expr, tokenToOpType[curToken->type], nullptr, curToken->line, curToken->column);
            advance();
            ((BinaryExpr *) expr)->right = parseExpr2();
        }
        return expr;
    }

    Expr *Parser::parseExpr4() {
        Expr *expr = parseExpr3();
        while (curToken->type == TokenType::LMove || curToken->type == TokenType::RMove) {
            expr = new BinaryExpr(expr, tokenToOpType[curToken->type], nullptr, curToken->line, curToken->column);
            advance();
            ((BinaryExpr *) expr)->right = parseExpr3();
        }
        return expr;
    }

    Expr *Parser::parseExpr5() {
        Expr *expr = parseExpr4();
        while (curToken->type == TokenType::LessThan || curToken->type == TokenType::LessEqual ||
               curToken->type == TokenType::GreaterThan || curToken->type == TokenType::GreaterEqual) {
            expr = new BinaryExpr(expr, tokenToOpType[curToken->type], nullptr, curToken->line, curToken->column);
            advance();
            ((BinaryExpr *) expr)->right = parseExpr4();
        }
        return expr;
    }

    Expr *Parser::parseExpr6() {
        Expr *expr = parseExpr5();
        while (curToken->type == TokenType::Equal || curToken->type == TokenType::NotEqual) {
            expr = new BinaryExpr(expr, tokenToOpType[curToken->type], nullptr, curToken->line, curToken->column);
            advance();
            ((BinaryExpr *) expr)->right = parseExpr5();
        }
        return expr;
    }

    Expr *Parser::parseExpr7() {
        Expr *expr = parseExpr6();
        while (curToken->type == TokenType::BAnd) {
            expr = new BinaryExpr(expr, tokenToOpType[curToken->type], nullptr, curToken->line, curToken->column);
            advance();
            ((BinaryExpr *) expr)->right = parseExpr6();
        }
        return expr;
    }

    Expr *Parser::parseExpr8() {
        Expr *expr = parseExpr7();
        while (curToken->type == TokenType::BXor) {
            expr = new BinaryExpr(expr, tokenToOpType[curToken->type], nullptr, curToken->line, curToken->column);
            advance();
            ((BinaryExpr *) expr)->right = parseExpr7();
        }
        return expr;
    }

    Expr *Parser::parseExpr9() {
        Expr *expr = parseExpr8();
        while (curToken->type == TokenType::BOr) {
            expr = new BinaryExpr(expr, tokenToOpType[curToken->type], nullptr, curToken->line, curToken->column);
            advance();
            ((BinaryExpr *) expr)->right = parseExpr8();
        }
        return expr;
    }

    Expr *Parser::parseExpr10() {
        Expr *expr = parseExpr9();
        while (curToken->type == TokenType::And) {
            expr = new BinaryExpr(expr, tokenToOpType[curToken->type], nullptr, curToken->line, curToken->column);
            advance();
            ((BinaryExpr *) expr)->right = parseExpr9();
        }
        return expr;
    }

    Expr *Parser::parseExpr11() {
        Expr *expr = parseExpr10();
        while (curToken->type == TokenType::Or) {
            expr = new BinaryExpr(expr, tokenToOpType[curToken->type], nullptr, curToken->line, curToken->column);
            advance();
            ((BinaryExpr *) expr)->right = parseExpr10();
        }
        return expr;
    }

    Expr *Parser::parseExpr12() {
        Expr *expr = parseExpr11();
        if (curToken->type != TokenType::Assign) {
            return expr;
        }
        int line = curToken->line;
        int column = curToken->column;
        advance();
        return new AssignExpr(expr, parseExpr11(), line, column);
    }

    Expr *Parser::parseArrayLiteralExpr() {
        ArrayLiteralExpr *expr = new ArrayLiteralExpr(curToken->line, curToken->column);
        expect(TokenType::LBracket);
        if (curToken->type != TokenType::RBracket) {
            while (curToken->type != TokenType::RBracket) {
                expr->exprs.push_back(parseExpr());
                if (curToken->type == TokenType::Comma) {
                    advance();
                } else {
                    advance();
                    break;
                }
            }
        }
        expect(TokenType::RBracket);
        return expr;
    }

    Expr *Parser::parseExpr() {
        if (curToken->type == TokenType::LBracket) {
            return parseArrayLiteralExpr();
        }
        return parseExpr12();
    }

} // karl