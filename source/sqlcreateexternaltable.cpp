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
#include <sqlcreateexternaltable.hpp>

namespace cppsqlx
{

SQLCreateExternalTable::SQLCreateExternalTable(std::string tablename)
{ 
   _objectname   = tablename; 
   _objecttype   = "EXTERNAL TABLE";
   _delimiter    = 124;
   _timedelimiter= ":";
   _maxerror     = 0;
   _ctrlchars    = true;
   _crinstring   = true;
   _fillrecord   = true;
   _nullvalue    = "NULL";
   _remotesource = "ODBC";
   _encoding     = "internal";
}

std::string SQLCreateExternalTable::toString()
{
   std::string query;
   query = "CREATE ";
   query += _objecttype + " \"" + _objectname + "\"";
   switch(sqldialect_)
   {
      case DBPROVIDER::NETEZZA :
        {
          query += "\n" + std::string("SAMEAS ") + _sameas;
          query += "\nUSING\n(\nDATAOBJECT ('" + _dataobject + "')";
          query += "\nDELIMITER " + std::to_string(_delimiter);
          query += "\nTIMEDELIM '" + _timedelimiter + "'";
          query += "\nSOCKETBUFSIZE 8388608";
          query += "\nMaxErrors " + std::to_string(_maxerror);
          query += "\nCTRLCHARS " ;
          query += (_ctrlchars ? "TRUE" : "FALSE");
          query += "\nCRINSTRING ";
          query += (_crinstring ? "TRUE" : "FALSE");
          query += "\nFILLRECORD ";
          query += (_fillrecord ? "TRUE" : "FALSE");
          query += "\nNullValue '" + _nullvalue + "'";
          query += "\nlogdir '/tmp/'";
          query += "\nREMOTESOURCE  'ODBC'";
          query += "\nENCODING      'internal'";
          query += "\n)";         
          break;
        }
      case DBPROVIDER::GREENPLUM :
        {
          query += "\n" + std::string("(LIKE ") + _sameas + ")";
          query += "\nLOCATION ('" + _dataobject + "')";
          query += "\nFORMAT 'CSV' (DELIMITER ';' NULL'" + _nullvalue + "')";
          query += "\nSEGMENT REJECT LIMIT " + std::to_string(_maxerror);
          query += "\n";
          break;
        }
      default :
          break;
   }
   return query;
}

};/*namespace cppsqlx*/
