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
ASTNode::ASTNode () {
    parent = nullptr;
    location.first = 0;
    location.second = 0;
    root = nullptr;
}

ASTNode::~ASTNode () {
    cout << "DESTRUCTOR INVOKED\n";
    for (size_t i = 0; i < children.size(); i++)
        delete children[i];
}

ASTNode*
ASTNode::getParent () { return parent;}

ASTNode*
ASTNode::getChild (unsigned int i) { return children[i]; }

unsigned int
ASTNode::getNumChildren () { return (unsigned int) children.size(); }

unsigned int
ASTNode::getLine () { return location.first; }

unsigned int
ASTNode::getCol () { return location.second;}

std::pair<unsigned int, unsigned int>
ASTNode::getLocation () { return location; }

ProgramNode*
ASTNode::getRoot () { return root; }

// Mutators
void
ASTNode::addChild (ASTNode* child) {
    children.push_back(child);
    if (child != nullptr) child->setParent(this);
}

void
ASTNode::setParent (ASTNode *p) { parent = p; }

void
ASTNode::setRoot (ProgramNode *r) { root = r; }

void
ASTNode::setLine (unsigned int line) { location.first = line; }

void
ASTNode::setColumn (unsigned int column) { location.second = column; }

void
ASTNode::setLocation (unsigned int line, unsigned int column) {
    location.first = line;
    location.second = column;
}

void
ASTNode::setLocation (std::pair<unsigned int, unsigned int> loc) { location = loc; }

bool
ASTNode::hasVarTable () {
    return false;
}

FunctionDeclNode*
ASTNode::getFunction () {
    ASTNode* now = this;
    while (now) {
        if(typeid(*now) == typeid(FunctionDeclNode)) {
            return (FunctionDeclNode*)now;
        }
        now = now->getParent();
    }
    return nullptr;
}

void
ASTNode::visit(ASTVisitorBase* visitor) { }

/**********************************************************************************/
/* The ProgramNode Class                                                          */
/**********************************************************************************/
ProgramNode::ProgramNode () : ASTNode(), iolib(false) {
    this->fenv = new SymTable<FunctionEntry>();
    this->venv = new SymTable<VariableEntry>();
}

void
ProgramNode::setIo (bool flag) {
    iolib = flag;
}

bool
ProgramNode::useIo () {
    return iolib;
}


SymTable<FunctionEntry>*
ProgramNode::getFuncTable () {
    return fenv;
}

SymTable<VariableEntry>*
ProgramNode::getVarTable () {
    return venv;
}

bool
ProgramNode::hasVarTable () {
    return true;
}

void
ProgramNode::visit (ASTVisitorBase* visitor) {
    visitor->visitProgramNode(this);
}

/**********************************************************************************/
/* The TypeNode Class                                                             */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The PrimitiveTypeNode Class                                                    */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The ArrayTypeNode Class                                                        */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

    
/**********************************************************************************/
/* The IdentifierNode Class                                                       */
/**********************************************************************************/

// ECE467 STUDENT: implement the class


/**********************************************************************************/
/* The ParameterNode Class                                                        */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Expression Class                                                           */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Unary Expression Class                                                     */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Binary Expression Class                                                    */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Boolean Expression Class                                                   */
/**********************************************************************************/


// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Integer Expression Class                                                   */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Constant Class                                                             */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Boolean Constant Class                                                     */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Integer Constant Class                                                     */
/**********************************************************************************/

// ECE467 STUDENT: implement the class


/**********************************************************************************/
/* The Function Argument Class                                                    */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Call Expression Class                                                      */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Reference Expression Class                                                 */
/**********************************************************************************/

// ECE467 STUDENT: implement the class


/**********************************************************************************/
/* The Declaration Class                                                          */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Scalar Declaration Class                                                   */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
    
/**********************************************************************************/
/* The Array Declaration Class                                                    */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Stmt Class                                                                 */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Scope Class                                                                */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Function Declaration Class                                                 */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Expression Statement Class                                                 */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Assignment Statement Class                                                 */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The If Statement Class                                                         */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The While Statement Class                                                      */
/**********************************************************************************/

// ECE467 STUDENT: implement the class

/**********************************************************************************/
/* The Return Statement Class                                                     */
/**********************************************************************************/

// ECE467 STUDENT: implement the class
