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

#ifndef __SQLCREATEEXTERNALTABLE_HPP__
#define __SQLCREATEEXTERNALTABLE_HPP__
#include <cppsqlxincludes.hpp>
#include <sqlquery.hpp>
#include <loadprotocols.hpp>

namespace cppsqlx
{

class SQLCreateExternalTable : public DDLQuery<SQLCreateExternalTable>
{
   private:
   std::string       _sameas;
   std::string       _dataobject;
   int               _delimiter;
   int               _maxerror;
   bool              _ctrlchars;
   bool              _crinstring;
   bool              _fillrecord;
   bool              _writable;
   std::string       _nullvalue;
   std::string       _remotesource;
   std::string       _encoding;
   std::string       _timedelimiter;
   std::string       _escapechar;
   LOADPROTOCOL      _loadprotocol;
   int               _port;
   std::string       _location;
   bool              _header;
   std::string       _filetype;
   std::string       _errortable;
   int               _rejectlimit;
     
   public:
   SQLCreateExternalTable(std::string tablename);
   std::string toString();
   
   SQLCreateExternalTable& sameAs(std::string sameas){ _sameas = sameas;       return *this;}
   SQLCreateExternalTable& file(std::string filename){ _dataobject = filename; return *this;}
   SQLCreateExternalTable& delimiter(int delim)      { _delimiter = delim;     return *this;}
   SQLCreateExternalTable& maxError(int max)         { _maxerror = max;        return *this;}
   SQLCreateExternalTable& ctrlChars(bool ctrl)      { _ctrlchars = ctrl;      return *this;}
   SQLCreateExternalTable& crInstring(bool cr)  { _crinstring = cr;       return *this;}
   SQLCreateExternalTable& fillRecord(bool fill)     { _fillrecord = fill;     return *this;}
   SQLCreateExternalTable& nullValue(std::string val){ _nullvalue = val;       return *this;}
   SQLCreateExternalTable& writable(bool write)      { _writable = write;      return *this;}
   SQLCreateExternalTable& port(int p)               { _port = p ;             return *this;}
   SQLCreateExternalTable& location(std::string loc) { _location = loc;        return *this;}
   SQLCreateExternalTable& header(bool h)            { _header = h;            return *this;}
   SQLCreateExternalTable& escapeChar(std::string c) { _escapechar = c;        return *this;}
   SQLCreateExternalTable& csv()                     { _filetype = "csv";      return *this;}
   SQLCreateExternalTable& errorTo(std::string table){ _errortable = table;    return *this;}
   SQLCreateExternalTable& rejectLimit(int rl)       { _maxerror = rl;         return *this;}

};/*SQLCreateExternalTable*/

};/*namespace cppsqlx*/

#endif //__SQLCREATEEXTERNALTABLE_HPP__
