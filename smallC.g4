//
//  smallC.g4
//  ECE467 Lab 3
//
//  Created by Tarek Abdelrahman on 2023-09-13.
//  Based on code written by Ao (Dino) Li for ECE467.
//  Copyright © 2023 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE467 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

grammar smallC;

@header {
#include "ASTNodes.h"
#include <iostream>
#include <string>
}

program
returns [smallc::ProgramNode *prg]
@init {
    $prg = new smallc::ProgramNode();
    $prg->setLocation($ctx->start->getLine(), $ctx->start->getCharPositionInLine());
}
: (preamble {$prg->setIo(true);}
| ) (decls
{
   for(unsigned int i = 0; i < $decls.declarations.size();i++)
   $prg->addChild($decls.declarations[i]);
}
)* EOF ;

preamble:  '#include' '"scio.h"';

decls :
    scalarDeclList
    | arrDeclList
    | fcnProto
    | fcnDecl
;

scalarDeclList
returns [std::vector<smallc::ScalarDeclNode*> scalars]
    :
    scalarDecl
    {
        $scalars.push_back($scalarDecl.decl);
    }
    | scalarDecl
    {
        $scalars.push_back($scalarDecl.decl);
    }
    scalarDeclList
    {
        for(unsigned int i = 0; i < $scalarDeclList.scalars.size(); i++)
            $scalars.push_back($scalarDeclList.scalars[i]);
    }
;

scalarDecl :
    varType varName ';'
;

arrDeclList :
    arrDecl
    | arrDecl arrDeclList
;

arrDecl :
    varType arrName '[' intConst ']' ';'
;

fcnProto :
    retType fcnName '(' params ')' ';'
;

fcnDecl :
    retType fcnName '(' params ')' scope
;

varType :
    'bool'
    | 'int'
;

retType :
    'void'
    | varType
;

constant :
    boolConst
    | intConst
;

boolConst :
    BOOL
;

scope
returns[smallc::ScopeNode* scope_]
@init{
    $scope_ = new smallc::ScopeNode();
    $scope_->setLocation($ctx->start->getLine(), $ctx->start->getCharPositionInLine());
}
:
    '{' (scalarDecl
    {$scope_->addDeclaration($scalarDecl.decl);}
    |arrDecl
    {$scope_->addDeclaration($arrDecl.decl);}
    )* (stmt
    {$scope_->addChild($stmt.statement);}
    )* '}'
;

stmt :
    expr ';'
    | assignStmt
    | ifStmt
    | whileStmt
    | retStmt
    | scope
;

assignStmt :
    var '=' expr ';'
;

ifStmt :
    'if' '(' expr ')' stmt
    | 'if' '(' expr ')' then=stmt 'else' e=stmt
;

whileStmt :
    'while' '(' expr ')' stmt
;

retStmt :
    'return' expr ';'
    |'return' ';'
;

expr :
    intExpr
    | '(' expr ')'
    | fcnName '(' args ')'
    | op=('!' | '-') expr
    | l=expr op=('<' | '<=' | '>' | '>=') r=expr
    | l=expr op=('==' | '!=') r=expr
    | l=expr op='||' r=expr
    | l=expr op='&&' r=expr
;

intExpr :
    var
    | constant
    | l=intExpr op=('*' | '/' ) r=intExpr
    | l=intExpr op=('+' | '-' ) r=intExpr
    | '(' intExpr ')'
;

var :
    varName
    | arrName '[' intExpr ']'
;

params :
    paramList
    | ;

paramEntry :
    varType varName
    | varType arrName '[]'
;

paramList :
    paramEntry
    | paramEntry  ',' paramList
;

args :
    argList
    |
;

argEntry :
    expr
;

argList :
    argEntry
    | argEntry ',' argList;

varName : ID
;

arrName : ID
;

fcnName : ID
;

intConst : INT
| '-' INT
;

BOOL: 'true' | 'false';
ID: [a-zA-Z][a-zA-Z0-9_]* ;
INT:    [0] | ([1-9][0-9]*);
WS:     [ \t\r\n]+ -> skip;
COMMENT: '//' (~[\r\n])* -> skip;
