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
#include <statement.hpp>
#include <resultset.hpp>
#include <logger.hpp>
#include <odbcerror.hpp>
#include <sqlexception.hpp>


namespace cppsqlx
{

Statement::Statement(SQLHENV henv,SQLHDBC hdbc):_henv(henv),_hdbc(hdbc)
{
    SQLAllocHandle(SQL_HANDLE_STMT, _hdbc, &_hstmt);
    LOG_DEBUG("Statement::Statement");
}


Statement::~Statement()
{
   LOG_DEBUG("Statement::~Statement");
}


std::shared_ptr<Resultset>   Statement::executeQuery(std::string query)
{
    SQLRETURN retcode = SQLExecDirect(_hstmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLExecDirect", _hstmt, SQL_HANDLE_STMT));
       }
       std::shared_ptr<Resultset> resultset(new Resultset(_henv,_hdbc,_hstmt));
       return move(resultset);
    }
    else
    {
       if(retcode == SQL_INVALID_HANDLE)
       {
          throw SQLException("Statement object is invalid, see associated connection object");
       }
       ODBCError err;
       throw SQLException(err("SQLExecDirect", _hstmt, SQL_HANDLE_STMT));
    }
}


int  Statement::executeUpdate(std::string query)
{
    SQLINTEGER value;
    SQLRETURN retcode = SQLExecDirect(_hstmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLExecDirect", _hstmt, SQL_HANDLE_STMT));
       }

       SQLRETURN retcode = SQLRowCount(_hstmt,(SQLLEN*)&value);
       return (int)value;
    }
    else
    {
       ODBCError err;
       LOG_ERROR(err("SQLExecDirect", _hstmt, SQL_HANDLE_STMT));
       throw SQLException(err("SQLExecDirect", _hstmt, SQL_HANDLE_STMT));
       return 0;
    }
}


void Statement::execute(std::string query)
{
    SQLINTEGER value;
    SQLRETURN retcode = SQLExecDirect(_hstmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLExecDirect", _hstmt, SQL_HANDLE_STMT));
       }
    }
    else
    {
       ODBCError err;
       LOG_ERROR(err("SQLExecDirect", _hstmt, SQL_HANDLE_STMT));
       throw SQLException(err("SQLExecDirect", _hstmt, SQL_HANDLE_STMT));
    }
}





};/*namespace cppsqlx*/
