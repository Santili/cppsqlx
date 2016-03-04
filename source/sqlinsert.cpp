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
#include <sqlinsert.hpp>
#include <logger.hpp>

namespace cppsqlx
{

SQLInsert::~SQLInsert()
{
   LOG_DEBUG("SQLInsert::~SQLInsert");
}

SQLInsert::SQLInsert(std::string tablename)
{
   LOG_DEBUG("SQLInsert::SQLInsert");
   tablename_ = tablename;
}


std::string  SQLInsert::toString()
{
   std::string query = "INSERT INTO ";
   query += tablename_;
   if(columns_.size() > 0)
   {
      int index = 0;
      query += "(";
      for(auto v : columns_)
      {
          query += v;
          if( index < columns_.size() - 1)
            query += ",";
          else
            query += ")\n";
          index++;
      }
   }
   query += "\n" + query_->toString();
   return query;
}


SQLInsert&  SQLInsert::columns(std::vector<std::string> columnnames)
{
   columns_ = columnnames;
   return *this;
}

SQLInsert&  SQLInsert::select(SQLSelect sqlselect)
{
   std::shared_ptr<SQLSelect> s(new SQLSelect(sqlselect));
   query_ = s;
   return *this;
}


SQLInsert&  SQLInsert::select(std::shared_ptr<SQLSelect> sqlselect)
{
   query_ = sqlselect;
   return *this;
}


};/*namespace cppsqlx*/
