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

#ifndef __STATEMENT_HPP__
#define __STATEMENT_HPP__
#include <cppsqlxincludes.hpp>

namespace cppsqlx
{

class Resultset;
/* Statement class
 *
 * Statement class is holding a SQL statement
 * Used to issue a SQL query
 */
class Statement
{
   private:
   friend class Connection;
   /* Constructor
    * @henv SQLENV handle
    * @hdbc SQLHDBC handle
    *
    * An instance is get only via Connection class
    * which is frien of Statement class
    */
   Statement(SQLHENV henv,SQLHDBC hdbc);

   public:
   /* Destructor */
   ~Statement();

   private:
   SQLHENV         _henv;
   SQLHDBC         _hdbc;
   SQLHSTMT        _hstmt; 

   public:
   /* Execute a selection query
    *
    * @query The selection query
    * @return An instance of Resultset
    */
   std::shared_ptr<Resultset> executeQuery(std::string query);

   /* Execute update, insert, delete statement
    *
    * @query The sql query
    * @return the number of rows affected by the query statement
    */
   int executeUpdate(std::string query);

   /* Execute a DDL query
    *
    * @query The sql query
    */
   void  execute(std::string query);

};/*Statement*/

};/*namespace cppsqlx*/

#endif //__STATEMENT_HPP__
