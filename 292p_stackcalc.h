#ifndef _STACK_CALC_
#define _STACK_CALC_

void calcExpr(ExprToken* pExprTokens, int tokenCount);
int pushLinkedStackExprToken(LinkedStack* pStack, ExprToken data);
void convertInfixToPostfix(ExprToken* pExprTokens, int tokenCount);
int inStackprecedence(Precedence oper);
int outStackPrecedence(Precedence oper);
void printToken(ExprToken element);

#endif
