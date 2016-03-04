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

#include <connection.hpp>
#include <logger.hpp>
#include <sqlexception.hpp>
#include <odbcerror.hpp>
#include <statement.hpp>
#include <databasemetadata.hpp>

namespace cppsqlx
{

Connection::Connection(std::string user,std::string password,SQLHENV henv,SQLHDBC hdbc):
user_(user),
password_(password),
henv_(henv),
hdbc_(hdbc),
autocommit_(true)
{
   LOG_DEBUG(std::string("Connection::Connection user_(") + user_ + ") password_(" + password_ + ")");
}


Connection::~Connection()
{
   SQLDisconnect(hdbc_);
   SQLFreeHandle(SQL_HANDLE_DBC, hdbc_);
   SQLFreeHandle(SQL_HANDLE_ENV, henv_);
   LOG_DEBUG(std::string("Connection::~Connection user_(") + user_ + ") password_(" + password_ + ")");
}

DBPROVIDER Connection::provider()
{
   return provider_;
}

void Connection::setProvider(DBPROVIDER provider)
{
   provider_ = provider;
}

void Connection::setSchema(std::string schema)
{
   schema_ = schema;
   if(schema == "")
   {
     LOG_DEBUG("Schema not set because received empty string");
     return;
   }

   std::shared_ptr<Statement> p_stmt = createStatement();
   
   switch(provider_)
   {
      case DBPROVIDER::GREENPLUM :
         p_stmt->execute(std::string("SET SEARCH_PATH=") + schema + ";");
         break;
      case DBPROVIDER::POSTGRESQL :
         p_stmt->execute(std::string("SET SEARCH_PATH=") + schema);
         break;
      case DBPROVIDER::MONETDB :
         p_stmt->execute(std::string("SET SCHEMA ") + schema);
         break;
      case DBPROVIDER::ORACLE :
         p_stmt->execute(std::string("ALTER SESSION SET CURRENT_SCHEMA = ") + schema);
         break;
      case DBPROVIDER::VERTICA :
         p_stmt->execute(std::string("SET SEARCH_PATH=") + schema);
         break;
      default :
         break;
   }
   
}

std::string Connection::schema()
{
   return schema_;
}



void Connection::setAutoCommit(bool autocommit)
{
     SQLRETURN retcode;
     long unsigned int  committype;
     if(autocommit)
     {
        retcode = SQLSetConnectAttr(hdbc_,SQL_ATTR_AUTOCOMMIT, (SQLPOINTER*)SQL_AUTOCOMMIT_ON, 0);
     }
     else
     { 
        retcode = SQLSetConnectAttr(hdbc_,SQL_ATTR_AUTOCOMMIT, (SQLPOINTER*)SQL_AUTOCOMMIT_OFF, 0);
     }
     if (SQL_SUCCEEDED(retcode))
     {
        if (retcode == SQL_SUCCESS_WITH_INFO)
        {  
            ODBCError err;
            LOG_WARN(err("SQLSetConnectAttr", hdbc_, SQL_HANDLE_DBC));
        }
     } 
     else
     {
          ODBCError err;
          LOG_ERROR(err("SQLSetConnectAttr", hdbc_, SQL_HANDLE_DBC)); 
          throw SQLException(err("SQLSetConnectAttr", hdbc_, SQL_HANDLE_DBC));
     }

}


void Connection::commit()
{
     if(autocommit_)
       return;
     SQLRETURN retcode = SQLEndTran(SQL_HANDLE_DBC,hdbc_,SQL_COMMIT);
     if (SQL_SUCCEEDED(retcode))
     {  
        if (retcode == SQL_SUCCESS_WITH_INFO)
        {   
            ODBCError err;
            LOG_WARN(err("SQLEndTran", hdbc_, SQL_HANDLE_DBC));
            //throw SQLException(err("SQLEndTran", hdbc_, SQL_HANDLE_DBC));
        }
     } 
     else
     {    
          ODBCError err;
          LOG_ERROR(err("SQLEndTran",hdbc_, SQL_HANDLE_DBC));
          throw SQLException(err("SQLEndTran", hdbc_, SQL_HANDLE_DBC));
     }
}


void Connection::roolback()
{
     if(autocommit_)
        return;
     SQLRETURN retcode = SQLEndTran(SQL_HANDLE_DBC,hdbc_,SQL_ROLLBACK);
     if (SQL_SUCCEEDED(retcode))
     {
        if (retcode == SQL_SUCCESS_WITH_INFO)
        {
            ODBCError err;
            LOG_WARN(err("SQLEndTran", hdbc_, SQL_HANDLE_DBC));
            //throw SQLException(err("SQLEndTran", hdbc_, SQL_HANDLE_DBC));
        }
     } 
     else
     {    
          ODBCError err;
          LOG_ERROR(err("SQLEndTran", hdbc_, SQL_HANDLE_DBC));
          throw SQLException(err("SQLEndTran", hdbc_, SQL_HANDLE_DBC));
     }
}

std::shared_ptr<Statement>  Connection::createStatement()
{
   LOG_DEBUG(std::string("Connection::createStatement() line :") + std::to_string(__LINE__));
   std::shared_ptr<Statement> statement(new Statement(henv_,hdbc_));
   return move(statement);
}

std::shared_ptr<DatabaseMetadata>   Connection::getMetadata()
{
   std::shared_ptr<DatabaseMetadata> metadata(new DatabaseMetadata(henv_,hdbc_));
   metadata->provider_ = provider_;
   return move(metadata);
}

};/*namespace cppsqlx*/
