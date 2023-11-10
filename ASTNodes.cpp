//
//  ASTNodes.cpp
//  ECE467 Lab 3
//
//  Created by Tarek Abdelrahman on 2023-09-13.
//  Based on code written by Ao (Dino) Li for ECE467.
//  Copyright © 2023 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE467 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#include "ASTNodes.h"

#include <iostream>

using namespace smallc;

/**********************************************************************************/
/* The ASTNode Class                                                              */
/**********************************************************************************/
ASTNode::ASTNode()
{
    parent = nullptr;
    location.first = 0;
    location.second = 0;
    root = nullptr;
}

ASTNode::~ASTNode()
{
    cout << "DESTRUCTOR INVOKED\n";
    for (size_t i = 0; i < children.size(); i++)
        delete children[i];
}

ASTNode *ASTNode::getParent() { return parent; }

ASTNode *ASTNode::getChild(unsigned int i) { return children[i]; }

unsigned int ASTNode::getNumChildren() { return (unsigned int)children.size(); }

unsigned int ASTNode::getLine() { return location.first; }

unsigned int ASTNode::getCol() { return location.second; }

std::pair<unsigned int, unsigned int>ASTNode::getLocation() { return location; }

ProgramNode *ASTNode::getRoot() { return root; }

// Mutators
void ASTNode::addChild(ASTNode *child)
{
    children.push_back(child);
    if (child != nullptr)
        child->setParent(this);
}

void ASTNode::setParent(ASTNode *p) { parent = p; }

void ASTNode::setRoot(ProgramNode *r) { root = r; }

void ASTNode::setLine(unsigned int line) { location.first = line; }

void ASTNode::setColumn(unsigned int column) { location.second = column; }

void ASTNode::setLocation(unsigned int line, unsigned int column)
{
    location.first = line;
    location.second = column;
}

void ASTNode::setLocation(std::pair<unsigned int, unsigned int> loc) { location = loc; }

bool ASTNode::hasVarTable()
{
    return false;
}

FunctionDeclNode *ASTNode::getFunction()
{
    ASTNode *now = this;
    while (now)
    {
        if (typeid(*now) == typeid(FunctionDeclNode))
        {
            return (FunctionDeclNode *)now;
        }
        now = now->getParent();
    }
    return nullptr;
}

void ASTNode::visit(ASTVisitorBase *visitor) {
    visitor->visitASTNode(this);
}

/**********************************************************************************/
/* The ProgramNode Class                                                          */
/**********************************************************************************/
ProgramNode::ProgramNode() : ASTNode(), iolib(false)
{
    this->fenv = new SymTable<FunctionEntry>();
    this->venv = new SymTable<VariableEntry>();
}

void ProgramNode::setIo(bool flag)
{
    iolib = flag;
}

bool ProgramNode::useIo()
{
    return iolib;
}

SymTable<FunctionEntry> *ProgramNode::getFuncTable()
{
    return fenv;
}

SymTable<VariableEntry> *ProgramNode::getVarTable()
{
    return venv;
}

bool ProgramNode::hasVarTable()
{
    return true;
}

void ProgramNode::visit(ASTVisitorBase *visitor)
{
    visitor->visitProgramNode(this);
}

/**********************************************************************************/
/* The TypeNode Class                                                             */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

void TypeNode::visit(ASTVisitorBase *visitor){
    visitor->visitTypeNode(this);
}
/**********************************************************************************/
/* The PrimitiveTypeNode Class                                                    */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

void PrimitiveTypeNode::visit(ASTVisitorBase *visitor){
    visitor->visitPrimitiveTypeNode(this);
}

/**********************************************************************************/
/* The ArrayTypeNode Class                                                        */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

void ArrayTypeNode::visit(ASTVisitorBase *visitor){
    visitor->visitArrayTypeNode(this);
}

/**********************************************************************************/
/* The IdentifierNode Class                                                       */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

void IdentifierNode::visit(ASTVisitorBase *visitor){
    visitor->visitIdentifierNode(this);
}
/**********************************************************************************/
/* The ParameterNode Class                                                        */
/**********************************************************************************/

ParameterNode::ParameterNode() {
    this->type = nullptr;
    this->name = nullptr;
}
ParameterNode::ParameterNode(TypeNode *type_, IdentifierNode *name_) {
    type = type_;
    name = name_;
}

TypeNode *&ParameterNode::getType() {
    return type;
}

void ParameterNode::setIdent(IdentifierNode *&name_) {
    name = name_;
}

IdentifierNode *&ParameterNode::getIdent() {
    return name;
}

void ParameterNode::visit(ASTVisitorBase *visitor) {
    visitor->visitParameterNode(this);
}

/**********************************************************************************/
/* The Expression Class                                                           */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void ExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitExprNode(this);
}

/**********************************************************************************/
/* The Unary Expression Class                                                     */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void UnaryExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitUnaryExprNode(this);
}

/**********************************************************************************/
/* The Binary Expression Class                                                    */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void BinaryExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitBinaryExprNode(this);
}

/**********************************************************************************/
/* The Boolean Expression Class                                                   */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void BoolExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitBoolExprNode(this);
}

/**********************************************************************************/
/* The Integer Expression Class                                                   */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void IntExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitIntExprNode(this);
}

/**********************************************************************************/
/* The Constant Class                                                             */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void ConstantExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitConstantExprNode(this);
}
/**********************************************************************************/
/* The Boolean Constant Class                                                     */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void BoolConstantNode::visit(ASTVisitorBase *visitor){
    visitor->visitBoolConstantNode(this);
}

/**********************************************************************************/
/* The Integer Constant Class                                                     */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void IntConstantNode::visit(ASTVisitorBase *visitor){
    visitor->visitIntConstantNode(this);
}

/**********************************************************************************/
/* The Function Argument Class                                                    */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void ArgumentNode::visit(ASTVisitorBase *visitor){
    visitor->visitArgumentNode(this);
}

/**********************************************************************************/
/* The Call Expression Class                                                      */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void CallExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitCallExprNode(this);
}

/**********************************************************************************/
/* The Reference Expression Class                                                 */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void ReferenceExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitReferenceExprNode(this);
}

/**********************************************************************************/
/* The Declaration Class                                                          */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void DeclNode::visit(ASTVisitorBase *visitor){
    visitor->visitDeclNode(this);
}

/**********************************************************************************/
/* The Scalar Declaration Class                                                   */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void ScalarDeclNode::visit(ASTVisitorBase *visitor){
    visitor->visitScalarDeclNode(this);
}

/**********************************************************************************/
/* The Array Declaration Class                                                    */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void ArrayDeclNode::visit(ASTVisitorBase *visitor){
    visitor->visitArrayDeclNode(this);
}

/**********************************************************************************/
/* The Stmt Class                                                                 */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void StmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitStmtNode(this);
}

/**********************************************************************************/
/* The Scope Class                                                                */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void ScopeNode::visit(ASTVisitorBase *visitor){
    visitor->visitScopeNode(this);
}

/**********************************************************************************/
/* The Function Declaration Class                                                 */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void FunctionDeclNode::visit(ASTVisitorBase *visitor){
    visitor->visitFunctionDeclNode(this);
}

/**********************************************************************************/
/* The Expression Statement Class                                                 */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void ExprStmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitExprStmtNode(this);
}

/**********************************************************************************/
/* The Assignment Statement Class                                                 */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void AssignStmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitAssignStmtNode(this);
}

/**********************************************************************************/
/* The If Statement Class                                                         */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void IfStmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitIfStmtNode(this);
}

/**********************************************************************************/
/* The While Statement Class                                                      */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void WhileStmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitWhileStmtNode(this);
}

/**********************************************************************************/
/* The Return Statement Class                                                     */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
void ReturnStmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitReturnStmtNode(this);
}
