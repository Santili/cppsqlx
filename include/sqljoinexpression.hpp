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

#ifndef __SQLJOINEXPRESSION_HPP__
#define __SQLJOINEXPRESSION_HPP__
#include <cppsqlxincludes.hpp>
#include <sqloperators.hpp>
#include <sqlexpression.hpp>

namespace cppsqlx
{

class SQLJoinExpression
{
   public:
   SQLJoinExpression(SQLExpression leftexpression,SQLExpression rightexpression,SQL_OPERATORS compareoperator);
   SQLJoinExpression(SQLJoinExpression leftexpression,SQLJoinExpression rightexpression,SQL_OPERATORS logical_operator);
   SQLJoinExpression();
   ~SQLJoinExpression();

   private:
   SQLExpression         leftexpression_;
   SQLExpression         rightexpression_;
   SQL_OPERATORS operator_;

   public:
   std::string           expression();
   SQL_OPERATORS getOperator();
   std::string           getStringOperator();
   SQLExpression         leftExpression();
   SQLExpression         rightExpression();
   void                  setLeftExpression(SQLExpression ex);
   void                  setRightExpression(SQLExpression ex);
   void                  setOperator(SQL_OPERATORS op);

};/*SQLJoinExpression*/

};/*namespace cppsqlx*/

#endif //__SQLJOINEXPRESSION_HPP__
