/*
 * Copyright (c) 2014-2016, Santili Y-HRAH KRONG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <sqljoinexpression.hpp>
#include <logger.hpp>

namespace cppsqlx
{

SQLJoinExpression::SQLJoinExpression(SQLExpression leftexpression,SQLExpression rightexpression,SQL_OPERATORS compareoperator):leftexpression_(leftexpression),rightexpression_(rightexpression),operator_(compareoperator)
{
}

SQLJoinExpression::SQLJoinExpression(SQLJoinExpression leftexpression,SQLJoinExpression rightexpression,SQL_OPERATORS logical_operator)
{
   leftexpression_ = leftexpression.expression();
   rightexpression_= rightexpression.expression();
   operator_ = logical_operator;
}

SQLJoinExpression::SQLJoinExpression()
{
}

SQLJoinExpression::~SQLJoinExpression()
{
}


std::string SQLJoinExpression::expression()
{
  return leftExpression().expression() + " " + getStringOperator() + " " + rightExpression().expression();
}


SQLExpression SQLJoinExpression::leftExpression()
{
  return leftexpression_;
}


SQLExpression SQLJoinExpression::rightExpression()
{
  return rightexpression_;
}

std::string SQLJoinExpression::getStringOperator()
{
  return sqlCompareOperators[operator_];
}

SQL_OPERATORS SQLJoinExpression::getOperator()
{
  return operator_;
}

void SQLJoinExpression::setLeftExpression(SQLExpression ex)
{
   leftexpression_ = ex;
}

void SQLJoinExpression::setRightExpression(SQLExpression ex)
{
   rightexpression_ = ex;
}

void SQLJoinExpression::setOperator(SQL_OPERATORS op)
{
   operator_ = op;
}



};/*namespace cppsqlx*/
