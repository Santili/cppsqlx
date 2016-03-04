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

#ifndef __SQLCOPY_HPP__
#define __SQLCOPY_HPP__
#include <cppsqlxincludes.hpp>
#include <sqlquery.hpp>
#include <sqlselect.hpp>

namespace cppsqlx
{

class SQLCopy : public DTLQuery<SQLCopy>
{
   public:
   enum COPY_DIRECTION {TO,FROM};
   SQLCopy(std::string tablename);

   private:
   std::vector<std::string>   columns_;
   std::shared_ptr<SQLSelect> query_;
   COPY_DIRECTION            direction_;
   std::string             null_string_;
   std::string          esc_;
   std::string       delim_;
   std::string    error_table_;
   std::string filename_;
   std::string tablename_;
   int         reject_limit_;
   bool        csv_;
   bool        header_;
   bool        fill_;

   public:
   virtual std::string   toString();
   SQLCopy&              from(std::string filename);
   SQLCopy&           to(std::string filename);
   SQLCopy&         delimiter(std::string delim);
   SQLCopy&       escape(std::string esc);
   SQLCopy&     header();
   SQLCopy&   csv();
   SQLCopy& fillMissingFields();
   SQLCopy& errorTo(std::string log_table);
   SQLCopy& null(std::string null_string);
   SQLCopy& rejectLimit(int limit);
   SQLCopy& columns(std::vector<std::string> columnnames);
   SQLCopy& select(std::shared_ptr<SQLSelect> sqlselect);
   SQLCopy& select(SQLSelect sqlselect);
   SQLCopy& columns()
   {
      return *this;
   }

   template<typename ... Types>
   SQLCopy& columns(std::string first, Types ... rest)
   {
      int nb = sizeof...(rest);
      columns_.push_back(first);
      columns(rest...);
      return *this;
   }

};/*SQLCopy*/

};/*namespace cppsqlx*/

#endif //__SQLCOPY_HPP__
