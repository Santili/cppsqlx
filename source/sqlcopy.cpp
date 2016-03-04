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
#include <sqlcopy.hpp>

namespace cppsqlx
{

SQLCopy::SQLCopy(std::string tablename):tablename_(tablename)
{
  delim_ = R"(|)";
  esc_   = R"(\\)";
  reject_limit_ = 0;
}

std::string   SQLCopy::toString()
{
   std::string query = std::string("COPY ") + tablename_ + "\n";
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
   std::string sdirection = direction_ == COPY_DIRECTION::TO ? "TO" : "FROM";
   query += sdirection + " '" + filename_ + "'\n";
   query += "WITH DELIMITER '" + delim_ + "'\n";
   query += "ESCAPE E'" + esc_ + "'\n";
   query += "NULL '" + null_string_ + "'\n";

   if(header_)
     query += "HEADER\n";

   if(error_table_ != "")
     query += "LOG ERRORS INTO " + error_table_ + "\n";

   if(csv_)
     query += "CSV \n";
 
   if(fill_)
     query += "FILL MISSING FIELDS \n";

   if(reject_limit_ > 0)
     query += "SEGMENT REJECT LIMIT " + std::to_string(reject_limit_) + "\n";

   return query;
}


SQLCopy& SQLCopy::from(std::string filename)
{
   filename_ = filename;
   return *this;
}



SQLCopy& SQLCopy::to(std::string filename)
{
   filename_ = filename;
   return *this;
}



SQLCopy& SQLCopy::delimiter(std::string delim)
{
   delim_ = delim;
   return *this;
}



SQLCopy& SQLCopy::escape(std::string esc)
{
   esc_ = esc;
   return *this;  
}



SQLCopy& SQLCopy::errorTo(std::string log_table)
{
   error_table_ = log_table;
   return *this;
}



SQLCopy& SQLCopy::null(std::string null_string)
{
    null_string_ = null_string;
    return *this;
}


SQLCopy& SQLCopy::columns(std::vector<std::string> columnnames)
{
   columns_ = columnnames;
   return *this;
}

SQLCopy& SQLCopy::header()
{
   header_ = true;
   return *this;
}


SQLCopy& SQLCopy::csv()
{
   csv_ = true;
   return *this;
}


SQLCopy& SQLCopy::fillMissingFields()
{
   fill_ = true;
   return *this;
}


SQLCopy& SQLCopy::rejectLimit(int limit)
{
   reject_limit_ = limit;
   return *this;
}

};/*namespace cppsqlx*/
