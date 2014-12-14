#include "symbol.hpp"
using namespace std;
int DEBUG = 0;
int inMethodBody = 0;
// Symbol Visitor Functions: These are the functions you will
// complete to build the symbol table. Not all functions must
// have code, many may be left empty.

void Symbol::visitProgramNode(ProgramNode* node) {
  if (DEBUG==1) cout<<"visitingProgramNode\n";
  ClassTable c;
  classTable = new ClassTable;//&c;
  node->visit_children(this);
}

void Symbol::visitClassNode(ClassNode* node) {
if (DEBUG==1) cout<<"visitingClassNode\n";
 ClassInfo c;
 MethodTable m;
 VariableTable v;
 
 c.superClassName = (node->identifier_2) ? node->identifier_2->name : "" ;
 std::string className = (node->identifier_1) ? node->identifier_1->name: "";
 // classTable->insert(std::pair<std::string,ClassInfo>(className,c));
 //c.methods = m;
 //c.members = v;
 
 currentMethodTable = &(c.methods);
 currentMemberOffset = 0;
 //currentLocalOffset = -4;
  //currentParameterOffset = 8;
  currentVariableTable = &(c.members);
  node->visit_children(this);  
  if (classTable->count(className)<1)classTable->insert(std::pair<std::string,ClassInfo>(className,c));
  //node->visit_children(this);  
  //c.membersSize = v.size()*4;
}

void Symbol::visitMethodNode(MethodNode* node) {
  // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingMethodNode\n";
  MethodInfo m;
  m.returnType.baseType = node->type->basetype;
  m.returnType.objectClassName=(node->type->basetype == bt_object) ? ((ObjectTypeNode*)(node->type))->identifier->name : "";
  //VariableTable v;
  //m.variables = (v);

  currentLocalOffset = -4;
  currentParameterOffset = 8;
  currentVariableTable = &(m.variables);
  node->visit_children(this);
  m.localsSize = m.variables.size()*4;
  if (currentMethodTable->count(node->identifier->name)<1)currentMethodTable->insert(std::pair<std::string,MethodInfo>(node->identifier->name, m));
  //node->visit_children(this);
}

void Symbol::visitMethodBodyNode(MethodBodyNode* node) {
    // WRITEME: Replace with code if necessary
    if (DEBUG==1) cout<<"visitingMethodBodyNode\n";
      inMethodBody = 1;
  node->visit_children(this);
  //inMethodBody = 0;
}

void Symbol::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingParameterNode\n";
  VariableInfo v;
  CompoundType c;
  c.baseType = node->type->basetype;
  //c.objectClassName = node->identifier->name;
  v.offset = currentParameterOffset;
  currentParameterOffset+=4;
  v.size = 4;
  v.type = c;
    node->visit_children(this);
  if (currentVariableTable->count(node->identifier->name)<1)currentVariableTable->insert(std::pair<std::string, VariableInfo>(node->identifier->name, v));
  //  node->visit_children(this);
}

void Symbol::visitDeclarationNode(DeclarationNode* node) {
    // WRITEME: Replace with code if necessary
  //node->visit_children(this);

  //VariableInfo v;
  CompoundType c;
  c.objectClassName=(node->type->basetype == bt_object) ? ((ObjectTypeNode*)(node->type))->identifier->name : "";
  c.baseType = node->type->basetype;
for (std::list<IdentifierNode*>::iterator it = node->identifier_list->begin();it!=node->identifier_list->end();it++) {
    VariableInfo v;
    if (inMethodBody == 1) {
      v.offset = currentLocalOffset;
      currentLocalOffset -=4;
      //cout<<"OFFSET: "<<v.offset<<endl;
    }
    else {
      v.offset = currentMemberOffset;
      currentMemberOffset +=4;
    }
    v.size = 4;
    v.type = c;
    //cout<<(*it)->name<<endl;
    if (currentVariableTable->count((*it)->name)<1)currentVariableTable->insert(std::pair<std::string, VariableInfo>((*it)->name, v));
  }
  node->visit_children(this); 
}

void Symbol::visitReturnStatementNode(ReturnStatementNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingReturnStatementNode\n";
  node->visit_children(this);
}

void Symbol::visitAssignmentNode(AssignmentNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingAssignmentNode\n";
  //CompoundType c;
  //VariableInfo v;
  //.baseType =node->basetype;
    //c.objectClassName = (node->basetype == bt_object) ? node->type->identifier->name : "";
  //v.offset = currentLocalOffset;
  //currentLocalOffset -= 4;
  //v.size = 4;
  //v.type = c;
  //currentVariableTable ->insert (std::pair<std::string, VariableInfo>(node->identifier->name, v));
  node->visit_children(this);
}

void Symbol::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingCallNode\n";
  node->visit_children(this);
}

void Symbol::visitIfElseNode(IfElseNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingIfElseNode\n";
  node->visit_children(this);
}

void Symbol::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingForNode\n";
  node->visit_children(this);
}

void Symbol::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingPrintNode\n";
  node->visit_children(this);
}

void Symbol::visitPlusNode(PlusNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingPlusNode\n";
  node->visit_children(this);
}

void Symbol::visitMinusNode(MinusNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingMinusNode\n";
  node->visit_children(this);
}

void Symbol::visitTimesNode(TimesNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingTimesNode\n";
  node->visit_children(this);
}

void Symbol::visitDivideNode(DivideNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingDivideNode\n";
  node->visit_children(this);
}

void Symbol::visitLessNode(LessNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingLessNode\n";
  node->visit_children(this);
}

void Symbol::visitLessEqualNode(LessEqualNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingLessEqualNode\n";
  node->visit_children(this);
}

void Symbol::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingEqualNode\n";
  node->visit_children(this);
}

void Symbol::visitAndNode(AndNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingAndNode\n";
  node->visit_children(this);
}

void Symbol::visitOrNode(OrNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingOrNode\n";
  node->visit_children(this);
}

void Symbol::visitNotNode(NotNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingNotNode\n";
  node->visit_children(this);
}

void Symbol::visitNegationNode(NegationNode* node) {
  // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingNegationNode\n";  
  node->visit_children(this);
}

void Symbol::visitMethodCallNode(MethodCallNode* node) {
  // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingMethodCallNode\n";
  node->visit_children(this);
}

void Symbol::visitMemberAccessNode(MemberAccessNode* node) {
  // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingMemberAccessNode\n";
  node->visit_children(this);
}

void Symbol::visitVariableNode(VariableNode* node) {
  // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingVariableNode\n";
  VariableInfo v;
  CompoundType c;
  //c->basetype = node->basetype;
  v.type = c;
  v.offset = currentLocalOffset;
  currentLocalOffset -=4;
  v.size = 4;
  currentVariableTable->insert(std::pair<std::string, VariableInfo>(node->identifier->name, v));
  
  //node->visit_children(this);
}


void Symbol::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingIntegerLiteralNode\n";
  node->visit_children(this);
}

void Symbol::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingBooleanNode\n";
  node->visit_children(this);
}

void Symbol::visitNewNode(NewNode* node) {
  // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingNewNode\n";
  node->visit_children(this);
}

void Symbol::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingIntegerTypeNode\n";
  node->visit_children(this);
}

void Symbol::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingBooleanTypeNode\n";
  node->visit_children(this);
}

void Symbol::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingObjectTypeNode\n";
  node->visit_children(this);
}

void Symbol::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingNoneNode\n";
  node->visit_children(this);
}

void Symbol::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
  if (DEBUG==1) cout<<"visitingIdentifierNode\n";
  node->visit_children(this);
}

void Symbol::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
 if (DEBUG==1) cout<<"visitingIntegerNode\n";
  node->visit_children(this);
}
