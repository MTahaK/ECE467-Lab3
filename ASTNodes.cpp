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

bool TypeNode::isArray(){
    return false;
}

void TypeNode::visit(ASTVisitorBase *visitor){
    visitor->visitTypeNode(this);
}
/**********************************************************************************/
/* The PrimitiveTypeNode Class                                                    */
/**********************************************************************************/

PrimitiveTypeNode::PrimitiveTypeNode() : type(TypeNode::Void) {}
PrimitiveTypeNode::PrimitiveTypeNode(TypeEnum type_) : type(type_) {}

void PrimitiveTypeNode::setType(TypeEnum type_) {
    type = type_;
}
TypeNode::TypeEnum PrimitiveTypeNode::getTypeEnum() const {
    return type;
}
bool PrimitiveTypeNode::operator == (const PrimitiveTypeNode& other) {
    return type == other.type;
}
bool PrimitiveTypeNode::operator != (const PrimitiveTypeNode& other) {
    return type != other.type;
}
void PrimitiveTypeNode::visit(ASTVisitorBase *visitor){
    visitor->visitPrimitiveTypeNode(this);
}

/**********************************************************************************/
/* The ArrayTypeNode Class                                                        */
/**********************************************************************************/
ArrayTypeNode::ArrayTypeNode() {
    type = nullptr;
    size = 0;
}
ArrayTypeNode::ArrayTypeNode(PrimitiveTypeNode *type_) {
    type = type_;
    size = 0;
}
ArrayTypeNode::ArrayTypeNode(PrimitiveTypeNode *type_, int size_) {
    type = type_;
    size = size_;
}
void ArrayTypeNode::setType(TypeEnum type_) {
    type->setType(type_);
}
TypeNode::TypeEnum ArrayTypeNode::getTypeEnum() const {
    return type->getTypeEnum();
}
void ArrayTypeNode::setSize(int size_) {
    size = size_;
}
int ArrayTypeNode::getSize() {
    return size;
}
bool ArrayTypeNode::operator == (const ArrayTypeNode& other) {
    return type == other.type && size == other.size;
}
bool ArrayTypeNode::operator != (const ArrayTypeNode& other) {
    return type != other.type || size != other.size;
}
bool ArrayTypeNode::isArray(){
    return true;
}
void ArrayTypeNode::visit(ASTVisitorBase *visitor){
    visitor->visitArrayTypeNode(this);
}
/**********************************************************************************/
/* The IdentifierNode Class                                                       */
/**********************************************************************************/

IdentifierNode::IdentifierNode() {
    name = "";
}
IdentifierNode::IdentifierNode(const std::string &text){
    name = text;
}
const std::string& IdentifierNode::getName() {
    return name;
}
void IdentifierNode::visit(ASTVisitorBase *visitor){
    visitor->visitIdentifierNode(this);
}
/**********************************************************************************/
/* The ParameterNode Class                                                        */
/**********************************************************************************/

ParameterNode::ParameterNode() {
    type = nullptr;
    name = nullptr;
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

ExprNode::ExprNode() : ASTNode() {}
void ExprNode::setType(PrimitiveTypeNode* type_) {
    type = type_;
}
void ExprNode::setTypeInt(){
    type->setType(TypeNode::Int);
}
void ExprNode::setTypeBool(){
    type->setType(TypeNode::Bool);
}
void ExprNode::setTypeVoid(){
    type->setType(TypeNode::Void);
}
PrimitiveTypeNode* ExprNode::getType() {
    return type;
}
void ExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitExprNode(this);
}

/**********************************************************************************/
/* The Unary Expression Class                                                     */
/**********************************************************************************/

UnaryExprNode::UnaryExprNode() : ExprNode() {}
UnaryExprNode::UnaryExprNode(ExprNode *expr_){
    operand = expr_;
}
UnaryExprNode::UnaryExprNode(ExprNode *expr_, Opcode code){
    operand = expr_;
    opcode = code;
}
ExprNode* UnaryExprNode::getOperand() {
    return operand;
}
void UnaryExprNode::setOperand(ExprNode *operand_) {
    operand = operand_;
}
ExprNode::Opcode UnaryExprNode::getOpcode() {
    return opcode;
}
void UnaryExprNode::setOpcode(Opcode code) {
    opcode = code;
}
void UnaryExprNode::setOpcode(std::string code){
    if(code == "Not")
        opcode = ExprNode::Not;
    else if(code == "Minus") // Unary minus
        opcode = ExprNode::Minus;
}
void UnaryExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitUnaryExprNode(this);
}

/**********************************************************************************/
/* The Binary Expression Class                                                    */
/**********************************************************************************/

BinaryExprNode::BinaryExprNode() : ExprNode() {}
BinaryExprNode::BinaryExprNode(ExprNode *l, ExprNode *r){
    left = l;
    right = r;
}
BinaryExprNode::BinaryExprNode(ExprNode *l, ExprNode *r, Opcode code){
    left = l;
    right = r;
    opcode = code;
}
ExprNode* BinaryExprNode::getLeft() {
    return left;
}
void BinaryExprNode::setLeft(ExprNode *l) {
    left = l;
}
ExprNode* BinaryExprNode::getRight() {
    return right;
}
void BinaryExprNode::setRight(ExprNode *r) {
    right = r;
}
ExprNode::Opcode BinaryExprNode::getOpcode() {
    return opcode;
}
void BinaryExprNode::setOpcode(Opcode code) {
    opcode = code;
}
void BinaryExprNode::setOpcode(std::string code){
    if(code == "Addition")
        opcode = ExprNode::Addition;
    else if(code == "Subtraction")
        opcode = ExprNode::Subtraction;
    else if(code == "Multiplication")
        opcode = ExprNode::Multiplication;
    else if(code == "Division")
        opcode = ExprNode::Division;
    else if(code == "And")
        opcode = ExprNode::And;
    else if(code == "Or")
        opcode = ExprNode::Or;
    else if(code == "Equal")
        opcode = ExprNode::Equal;
    else if(code == "NotEqual")
        opcode = ExprNode::NotEqual;
    else if(code == "LessThan")
        opcode = ExprNode::LessThan;
    else if(code == "LessorEqual")
        opcode = ExprNode::LessorEqual;
    else if(code == "Greater")
        opcode = ExprNode::Greater;
    else if(code == "GreaterorEqual")
        opcode = ExprNode::GreaterorEqual;
}
void BinaryExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitBinaryExprNode(this);
}

/**********************************************************************************/
/* The Boolean Expression Class                                                   */
/**********************************************************************************/

BoolExprNode::BoolExprNode() : ExprNode() {}
BoolExprNode::BoolExprNode(ExprNode *val){
    value = val;
}
ExprNode* BoolExprNode::getValue() {
    return value;
}
void BoolExprNode::setValue(ExprNode *val) {
    value = val;
}
void BoolExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitBoolExprNode(this);
}
/**********************************************************************************/
/* The Integer Expression Class                                                   */
/**********************************************************************************/

IntExprNode::IntExprNode() : ExprNode() {}
IntExprNode::IntExprNode(ExprNode *val){
    value = val;
}
ExprNode* IntExprNode::getValue() {
    return value;
}
void IntExprNode::setValue(ExprNode *val) {
    value = val;
}
void IntExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitIntExprNode(this);
}

/**********************************************************************************/
/* The Constant Class                                                             */
/**********************************************************************************/

ConstantExprNode::ConstantExprNode(const std::string &source_){
    source = source_;
}
void ConstantExprNode::setSource(const std::string &source_) {
    source = source_;
}
int ConstantExprNode::getVal(){
    return val;
}
void ConstantExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitConstantExprNode(this);
}
/**********************************************************************************/
/* The Boolean Constant Class                                                     */
/**********************************************************************************/

BoolConstantNode::BoolConstantNode(const std::string &source) : ConstantExprNode(source) {}
void BoolConstantNode::visit(ASTVisitorBase *visitor){
    visitor->visitBoolConstantNode(this);
}

/**********************************************************************************/
/* The Integer Constant Class                                                     */
/**********************************************************************************/

IntConstantNode::IntConstantNode(const std::string &source) : ConstantExprNode(source) {}
void IntConstantNode::visit(ASTVisitorBase *visitor){
    visitor->visitIntConstantNode(this);
}

/**********************************************************************************/
/* The Function Argument Class                                                    */
/**********************************************************************************/

ArgumentNode::ArgumentNode() : ASTNode() {}
ArgumentNode::ArgumentNode(ExprNode *expr){
    expr = expr;
}
ExprNode* ArgumentNode::getExpr() {
    return expr;
}
void ArgumentNode::setExpr(ExprNode *expr_) {
    expr = expr_;
}
void ArgumentNode::visit(ASTVisitorBase *visitor){
    visitor->visitArgumentNode(this);
}

/**********************************************************************************/
/* The Call Expression Class                                                      */
/**********************************************************************************/

CallExprNode::CallExprNode() : ExprNode() {}
CallExprNode::CallExprNode(IdentifierNode *callee){
    name = callee;
}
CallExprNode::CallExprNode(IdentifierNode *callee, std::vector<ArgumentNode*> arglist){
    name = callee;
    args = arglist;
}
ArgumentNode* CallExprNode::getArgument(unsigned int i) {
    return args[i];
}
std::vector<ArgumentNode *> CallExprNode::getArguments() {
    return args;
}
void CallExprNode::addArgument(ArgumentNode *arg) {
    args.push_back(arg);
}
void CallExprNode::setArguments(std::vector<ArgumentNode *> args_) {
    args = args_;
}
void CallExprNode::setIdent(IdentifierNode *callee){
    name = callee;
}
IdentifierNode* CallExprNode::getIdent() {
    return name;
}
void CallExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitCallExprNode(this);
}

/**********************************************************************************/
/* The Reference Expression Class                                                 */
/**********************************************************************************/

ReferenceExprNode::ReferenceExprNode() : ExprNode() {}
ReferenceExprNode::ReferenceExprNode(IdentifierNode *name_){
    name = name_;
}
ReferenceExprNode::ReferenceExprNode(IdentifierNode *name_, IntExprNode *exp){
    name = name_;
    index = exp;
}
IdentifierNode* ReferenceExprNode::getIdent() {
    return name;
}
void ReferenceExprNode::setIdent(IdentifierNode *name_) {
    name = name_;
}
IntExprNode* ReferenceExprNode::getIndex() {
    return index;
}
void ReferenceExprNode::setIndex(IntExprNode *index_) {
    index = index_;
}
void ReferenceExprNode::visit(ASTVisitorBase *visitor){
    visitor->visitReferenceExprNode(this);
}

/**********************************************************************************/
/* The Declaration Class                                                          */
/**********************************************************************************/

DeclNode::DeclNode() : ASTNode() {}
DeclNode::DeclNode(TypeNode* type_, IdentifierNode* name_) {
    type = type_;
    name = name_;
}
void DeclNode::setName(IdentifierNode* name_) {
    name = name_;
}
void DeclNode::setType(TypeNode* type_) {
    type = type_;
}
IdentifierNode* DeclNode::getIdent() {
    return name;
}
TypeNode* DeclNode::getType() {
    return type;
}
bool DeclNode::isGlobal(){
    return false;
}
void DeclNode::visit(ASTVisitorBase *visitor){
    visitor->visitDeclNode(this);
}

/**********************************************************************************/
/* The Scalar Declaration Class                                                   */
/**********************************************************************************/

ScalarDeclNode::ScalarDeclNode() : DeclNode() {}
ScalarDeclNode::ScalarDeclNode(PrimitiveTypeNode*& type_, IdentifierNode*& name_) : DeclNode(type_, name_) {}
PrimitiveTypeNode* ScalarDeclNode::getType() {
    return static_cast<PrimitiveTypeNode*>(DeclNode::getType());
}
void ScalarDeclNode::visit(ASTVisitorBase *visitor){
    visitor->visitScalarDeclNode(this);
}

/**********************************************************************************/
/* The Array Declaration Class                                                    */
/**********************************************************************************/

ArrayDeclNode::ArrayDeclNode() : DeclNode() {}
ArrayDeclNode::ArrayDeclNode(ArrayTypeNode* type_, IdentifierNode* name_) : DeclNode(type_, name_) {} 
ArrayTypeNode* ArrayDeclNode::getType() {
    return static_cast<ArrayTypeNode*>(DeclNode::getType());
}
void ArrayDeclNode::visit(ASTVisitorBase *visitor){
    visitor->visitArrayDeclNode(this);
}

/**********************************************************************************/
/* The Stmt Class                                                                 */
/**********************************************************************************/

void StmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitStmtNode(this);
}

/**********************************************************************************/
/* The Scope Class                                                                */
/**********************************************************************************/

ScopeNode::ScopeNode() : StmtNode() {}
void ScopeNode::addDeclaration(DeclNode *decl) {
    decls.push_back(decl);
}
std::vector<DeclNode *> ScopeNode::getDeclarations() {
    return decls;
}
SymTable<VariableEntry> *ScopeNode::getVarTable() {
    return env;
}
bool ScopeNode::hasVarTable(){
    return (env != nullptr);
}
void ScopeNode::visit(ASTVisitorBase *visitor){
    visitor->visitScopeNode(this);
}

/**********************************************************************************/
/* The Function Declaration Class                                                 */
/**********************************************************************************/

FunctionDeclNode::FunctionDeclNode() : DeclNode() {}
void FunctionDeclNode::setProto(bool val){
    isProto = val;
}
void FunctionDeclNode::setBody(ScopeNode* val){
    body = val;
}
void FunctionDeclNode::setRetType(PrimitiveTypeNode* type){
    DeclNode::setType(type);
}
void FunctionDeclNode::setParameter(std::vector<ParameterNode*> parameters){
    params = parameters;
}
void FunctionDeclNode::addParameter(ParameterNode* param){
    params.push_back(param);
}
bool FunctionDeclNode::getProto(){
    return isProto;
}
ScopeNode* FunctionDeclNode::getBody(){
    return body;
}
PrimitiveTypeNode* FunctionDeclNode::getRetType(){
    return static_cast<PrimitiveTypeNode*>(DeclNode::getType());
}
std::vector<ParameterNode*> FunctionDeclNode::getParams(){
    return params;
}
unsigned int FunctionDeclNode::getNumParameters(){
    return params.size();
}
PrimitiveTypeNode* FunctionDeclNode::getType(){
    return static_cast<PrimitiveTypeNode*>(DeclNode::getType());
}
void FunctionDeclNode::visit(ASTVisitorBase *visitor){
    visitor->visitFunctionDeclNode(this);
}

/**********************************************************************************/
/* The Expression Statement Class                                                 */
/**********************************************************************************/

ExprStmtNode::ExprStmtNode() : StmtNode() {}
ExprStmtNode::ExprStmtNode(ExprNode* exp){
    expr = exp;
}
void ExprStmtNode::setExpr(ExprNode* expr_) {
    expr = expr_;
}
ExprNode* ExprStmtNode::getExpr() {
    return expr;
}
void ExprStmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitExprStmtNode(this);
}

/**********************************************************************************/
/* The Assignment Statement Class                                                 */
/**********************************************************************************/

AssignStmtNode::AssignStmtNode() : StmtNode() {}
AssignStmtNode::AssignStmtNode(ReferenceExprNode* target_, ExprNode* val_) {
    target = target_;
    val = val_;
}
ReferenceExprNode* AssignStmtNode::getTarget() {
    return target;
}
void AssignStmtNode::setTarget(ReferenceExprNode* name){
    target = name;
}
ExprNode* AssignStmtNode::getValue() {
    return val;
}
void AssignStmtNode::setValue(ExprNode* value){
    val = value;
}
void AssignStmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitAssignStmtNode(this);
}

/**********************************************************************************/
/* The If Statement Class                                                         */
/**********************************************************************************/

IfStmtNode::IfStmtNode() : StmtNode() {}
IfStmtNode::IfStmtNode(ExprNode* cond, StmtNode* then_){
    condition = cond;
    Then = then_;
}
IfStmtNode::IfStmtNode(ExprNode* cond, StmtNode* then_, StmtNode* else_){
    condition = cond;
    Then = then_;
    Else = else_;
}
ExprNode* IfStmtNode::getCondition() {
    return condition;
}
void IfStmtNode::setCondition(ExprNode* condition_){
    condition = condition_;
}
bool IfStmtNode::getHasElse(){
    return hasElse;
}
void IfStmtNode::setHasElse(bool hasElse_){
    hasElse = hasElse_;
}
StmtNode* IfStmtNode::getThen(){
    return Then;
}
void IfStmtNode::setThen(StmtNode* then_){
    Then = then_;
}
StmtNode* IfStmtNode::getElse(){
    return Else;
}
void IfStmtNode::setElse(StmtNode* else_){
    Else = else_;
}
void IfStmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitIfStmtNode(this);
}

/**********************************************************************************/
/* The While Statement Class                                                      */
/**********************************************************************************/

WhileStmtNode::WhileStmtNode() : StmtNode() {}
WhileStmtNode::WhileStmtNode(ExprNode* cond, StmtNode* body_){
    condition = cond;
    body = body_;
}
ExprNode* WhileStmtNode::getCondition() {
    return condition;
}
void WhileStmtNode::setCondition(ExprNode* cond){
    condition = cond;
}
StmtNode* WhileStmtNode::getBody(){
    return body;
}
void WhileStmtNode::setBody(StmtNode* body_){
    body = body_;
}
void WhileStmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitWhileStmtNode(this);
}

/**********************************************************************************/
/* The Return Statement Class                                                     */
/**********************************************************************************/

ReturnStmtNode::ReturnStmtNode() : StmtNode() {}
ReturnStmtNode::ReturnStmtNode(ExprNode* exp){
    ret = exp;
}
ExprNode* ReturnStmtNode::getReturn(){
    return ret;
}
void ReturnStmtNode::setReturn(ExprNode* value){
    ret = value;
}
bool ReturnStmtNode::returnVoid(){
    return (ret == nullptr);
}
void ReturnStmtNode::visit(ASTVisitorBase *visitor){
    visitor->visitReturnStmtNode(this);
}
