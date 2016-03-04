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

#ifndef __SQLUPDATE_HPP__
#define __SQLUPDATE_HPP__
#include <cppsqlxincludes.hpp>
#include <sqlquery.hpp>

namespace cppsqlx
{

class SQLUpdate : public DTLQuery<SQLUpdate>, public filterable<SQLUpdate>
{
   public:
   SQLUpdate(std::string tablename);

   private:
   SQLSelectionSet   sets_;

   public:
   virtual std::string  toString();

   SQLUpdate& set()
   {  
      return *this;
   }

   SQLUpdate& set(const SQLSelectionSet& selectionset)
   {  
      sets_ = selectionset;
      return *this;
   }

   template<typename ... Types>
   SQLUpdate& set(SQLExpression first, Types ... rest)
   {   
       int nb = sizeof...(rest);
       sets_.push_back(first);
       set(rest...);
       return *this;
   }


};/*SQLUpdate*/

};/*namespace cppsqlx*/

#endif //__SQLUPDATE_HPP__
