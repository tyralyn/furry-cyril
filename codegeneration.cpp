#include "codegeneration.hpp"
int DEBUG2 = 0;
// CodeGenerator Visitor Functions: These are the functions
// you will complete to generate the x86 assembly code. Not
// all functions must have code, many may be left empty.
//d
// NOTE: You only need to complete code for expressions,
// assignments, returns, and local variable space allocation.
// Refer to project description for exact details.

void CodeGenerator::visitProgramNode(ProgramNode* node) {
    // WRITEME: Replace with code if necessary
  std::cout << "  # Program " << std::endl;
  std::cout << "  .globl Main_main "<< std::endl;
  std::cout << "  Main_main: " << std::endl;
  node->visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    // WRITEME: Replace with code if necessary
  //std::cout << "IN CLSSNDE\n";
  currentClassName = node->identifier_1->name;
  //std::cout << "before checking stuff\n";
  currentClassInfo = (*classTable)[currentClassName];
  if (DEBUG2 == 1) std::cout << "CHECKING MAP FOR PRESENCE OF CLASS: "<< classTable->count(currentMethodName)  << std::endl;
  if (DEBUG2 == 1) std::cout << "CURRENT CLASS NAME: " << currentClassInfo.membersSize << std::endl;
  node->visit_children(this);
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    // WRITEME: Replace with code if necessary
  currentMethodName = node->identifier->name;
  if (DEBUG2 == 1) std::cout << "CURRENT METHOD NAME: " << currentMethodName << std::endl;
  if (DEBUG2 == 1) std::cout << "CHECKING MAP FOR PRESENCE OF METHOD NAME: "<< currentClassInfo.methods.count(currentMethodName)  << std::endl;
  currentMethodInfo = currentClassInfo.methods[currentMethodName];
  if (DEBUG2 == 1) std::cout << "CURRENT METHOD TABLE SIZE: "<<(int) (currentClassInfo.methods.size()) << std::endl;
  if (DEBUG2 == 1) std::cout << "CHECKING SIZE METHOD: "<<classTable->size()<<std::endl;
  //currentMethodInfo = 
  int variableSize = currentMethodInfo.localsSize;
  std::cout << "  #Method" << std::endl;
  std::cout << "  push %ebp" << std::endl; //save the current frame pointer value
  std::cout << "  mov %esp, %ebp" << std::endl; //replace it with the current stack pointer value
  std::cout << "  sub $" << currentMethodInfo.localsSize << ", %esp" << std::endl; //allocate space for 1 local variable

  node->visit_children(this); 
  
  std::cout << "  pop %eax" << std::endl; // put return value in appropriate register
  std::cout << "  mov %ebp, %esp" << std::endl; //deallocate local variable space
  std::cout << "  pop %ebp" << std::endl; //restore previous frame pointer value
  std::cout << "  ret" << std::endl;

}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    // WRITEME: Replace with code if necessary
  int variableSize = currentMethodInfo.localsSize;
  if (DEBUG2 == 1) std::cout<<"CURRENT METHOD INFO SIZE: "<<variableSize<<std::endl;
  node->visit_children(this);
  //std::cout << "  pop %eax" << std::endl; // put return value in appropriate register
  //std::cout << "  mov %ebp, %esp" << std::endl; //deallocate local variable space
  //std::cout << "  pop %ebp" << std::endl; //restore previous frame pointer value
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
  std::cout << "  #Return" << std::endl;
  //std::cout << "  ret" << std::endl;
  //  node->visit_children(this);
}

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this); 
  int offset = currentMethodInfo.variables[node->identifier->name].offset;
  std::cout << "  # Assignment" << std::endl;
  // you have base pointer, put something in, move base pointer down by -4
  std::cout << "  pop %eax" << std::endl;
  std::cout << "  mov %eax, "<<offset<<"(%ebp)" << std::endl;
  
}

void CodeGenerator::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
  std::cout << "  # Plus" << std::endl;
  std::cout << "  pop %edx" << std::endl;
  std::cout << "  pop %eax" << std::endl;
  std::cout << "  add %edx, %eax" << std::endl;
  std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    // WRITEME: Replace with code if necessary

    node->visit_children(this);
    std::cout << "  # Minus" << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  sub %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;

}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    // WRITEME: Replace with code if necessary

    node->visit_children(this);
    std::cout << "  # Times" << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  imul %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    // WRITEME: Replace with code if necessary

    node->visit_children(this);
    std::cout << "  # Divide" << std::endl;
    std::cout << "  pop %ebx" << std::endl; //divisor
    std::cout << "  pop %eax" << std::endl; //dividend
    //std::cout << "  cdq" << std::endl;
    std::cout << "  cdq" << std::endl;
    std::cout << "  idiv %ebx" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitLessNode(LessNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
  // std::cout << "  # Less" << std::endl;
   //std::cout << "  pop %edx" << std::endl;
  //std::cout << "  pop %eax" << std::endl;
  // std::cout << "  add %edx, %eax" << std::endl;
  //std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitLessEqualNode(LessEqualNode* node) {
    // WRITEME: Replace with code if necessary

    /*node->visit_children(this);
    std::cout << "  # Plus" << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  add %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;*/
  node->visit_children(this);

}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary

    /*node->visit_children(this);
    std::cout << "  # Plus" << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  add %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;*/
  node->visit_children(this);

}

void CodeGenerator::visitAndNode(AndNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
  std::cout << "  # and" << std::endl;
  std::cout << "  pop %edx" << std::endl;
  std::cout << "  pop %eax" << std::endl;
  std::cout << "  and %edx, %eax" << std::endl;
  std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitOrNode(OrNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
  std::cout << "  # Or" << std::endl;
  std::cout << "  pop %edx" << std::endl;
  std::cout << "  pop %eax" << std::endl;
  std::cout << "  or %edx, %eax" << std::endl;
  std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitNotNode(NotNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
  std::cout << "  #Not" << std::endl;
  std::cout << "  pop %eax" << std::endl;
  std::cout << "  not %eax" << std::endl;
  std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
  std::cout << "  #Negation" << std::endl;
  std::cout << "  pop %eax" << std::endl; 
  std::cout << "  neg %eax" << std::endl;
  std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    // WRITEME: Replace with code if necessary
  //search for node->identifier in current method table's variables
  int offset = currentMethodInfo.variables[node->identifier->name].offset;
   node->visit_children(this);
  std::cout << "  # Variable " << std::endl;
  std::cout << "  push " << offset << "(%ebp)"<< std::endl;
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    // WRITEME: Replace with code if necessary
  std::cout<< "  #IntegerLiteral" <<std::endl;
  //std::cout<< node->integer->value << std::endl;
  std::cout<< "  push $" << node->integer->value << std::endl; 
  node->visit_children(this);
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitNewNode(NewNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}

void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
  node->visit_children(this);
}
