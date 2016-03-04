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
#include <databasemetadata.hpp>
#include <resultset.hpp>
#include <connection.hpp>
#include <logger.hpp>
#include <odbcerror.hpp>
#include <sqlexception.hpp>

namespace cppsqlx
{

DatabaseMetadata::DatabaseMetadata(SQLHENV henv,SQLHDBC hdbc):henv_(henv),hdbc_(hdbc)
{
   SQLAllocHandle(SQL_HANDLE_STMT, hdbc_, &hstmt_); 
}


DatabaseMetadata::~DatabaseMetadata()
{
   SQLFreeHandle(SQL_HANDLE_STMT, hstmt_);
}



std::shared_ptr<Resultset>  DatabaseMetadata::schemas()
{
    SQLRETURN retcode = SQLTables(hstmt_, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)SQL_ALL_SCHEMAS, SQL_NTS, (SQLCHAR*)"", 0, (SQLCHAR*)"", 0);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLTables", hstmt_, SQL_HANDLE_STMT));
          throw SQLException(err("SQLTables", hstmt_, SQL_HANDLE_STMT));
       }
       std::shared_ptr<Resultset> resultset(new Resultset(henv_,hdbc_,hstmt_));
       return move(resultset);
    }
    else
    {
       ODBCError err;
       LOG_ERROR(err("SQLTables", hstmt_, SQL_HANDLE_STMT));
       throw SQLException(err("SQLTables", hstmt_, SQL_HANDLE_STMT));
    }
}


std::list<std::string> DatabaseMetadata::getSchemas()
{
    std::list<std::string> str_schemas;
    std::shared_ptr<Resultset> p_res = schemas();
    std::string schema;
    while(p_res->next())
    {
       switch(provider_)
       {
         case DBPROVIDER::MONETDB :
           schema = p_res->getString("table_schem");
           str_schemas.push_back(schema);
           break;
         default :
           schema = p_res->getString("TABLE_SCHEM");
           str_schemas.push_back(schema);
           break;
       }
    }
    return str_schemas;
}

std::shared_ptr<Resultset>  DatabaseMetadata::catalogs()
{
    SQLRETURN retcode = SQLTables(hstmt_, (SQLCHAR*)SQL_ALL_CATALOGS, SQL_NTS, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"", 0, (SQLCHAR*)"", 0);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLTables", hstmt_, SQL_HANDLE_STMT));
          throw SQLException(err("SQLTables", hstmt_, SQL_HANDLE_STMT));
       }
       std::shared_ptr<Resultset> resultset(new Resultset(henv_,hdbc_,hstmt_));
       return move(resultset);
    }
    else
    {
       ODBCError err;
       LOG_ERROR(err("SQLTables", hstmt_, SQL_HANDLE_STMT));
       throw err("SQLTables", hstmt_, SQL_HANDLE_STMT);
    }
}


std::shared_ptr<Resultset>  DatabaseMetadata::getTables(std::string catalog,std::string schema,std::string table,std::string tabletype)
{
    SQLRETURN retcode = SQLTables(hstmt_, (SQLCHAR*) catalog.c_str(), SQL_NTS, (SQLCHAR*)schema.c_str(), SQL_NTS, (SQLCHAR*)table.c_str(), SQL_NTS, (SQLCHAR*)tabletype.c_str(), SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLTables", hstmt_, SQL_HANDLE_STMT));
          throw SQLException(err("SQLTables", hstmt_, SQL_HANDLE_STMT));
       }
       std::shared_ptr<Resultset> resultset(new Resultset(henv_,hdbc_,hstmt_));
       return move(resultset);
    }
    else
    {
       ODBCError err;
       LOG_ERROR(err("SQLTables", hstmt_, SQL_HANDLE_STMT));
       throw SQLException(err("SQLTables", hstmt_, SQL_HANDLE_STMT));
    }
}


std::shared_ptr<Resultset> DatabaseMetadata::getColumns(std::string catalog,std::string schema,std::string table)
{
    SQLCHAR* pkcatalog;
    SQLSMALLINT pknamelen;
    SQLCHAR* pkschema;
    SQLSMALLINT pkschemalen;
    if(catalog == "%" || catalog == "")
    {
       pkcatalog = nullptr;
       pknamelen = 0;
    }
    else
    {
       pkcatalog = (SQLCHAR*)catalog.c_str();
       pknamelen = SQL_NTS;
    }

    if(schema  == "%" || schema  == "")
    {
       pkschema = nullptr;
       pkschemalen = 0;
    }
    else
    {
       pkschema = (SQLCHAR*)schema.c_str();
       pkschemalen = SQL_NTS;
    }

    SQLRETURN retcode = SQLColumns(hstmt_, 
                                           pkcatalog,                 pknamelen, 
                                           pkschema,                  pkschemalen,
                                           (SQLCHAR*)table.c_str(), SQL_NTS, 
                                           NULL, 0);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLColumns", hstmt_, SQL_HANDLE_STMT));
          throw SQLException(err("SQLColumns", hstmt_, SQL_HANDLE_STMT));
       }
       std::shared_ptr<Resultset> resultset(new Resultset(henv_,hdbc_,hstmt_));
       return move(resultset);
    }
    else
    {
       ODBCError err;
       LOG_ERROR(err("SQLColumns", hstmt_, SQL_HANDLE_STMT));
       throw SQLException(err("SQLColumns", hstmt_, SQL_HANDLE_STMT));
    }
}


std::shared_ptr<Resultset>   DatabaseMetadata::getPrimaryKeys(std::string catalog,std::string schema,std::string table)
{
    SQLCHAR* pkcatalog;
    SQLSMALLINT pknamelen;
    SQLCHAR* pkschema;
    SQLSMALLINT pkschemalen;
    if(catalog == "%" || catalog == "")
    {
       pkcatalog = nullptr;
       pknamelen = 0;
    }
    else
    {
       pkcatalog = (SQLCHAR*)catalog.c_str();
       pknamelen = SQL_NTS;
    }

    if(schema  == "%" || schema  == "")
    {
       pkschema = nullptr;
       pkschemalen = 0;
    }
    else
    {
       pkschema = (SQLCHAR*)schema.c_str();
       pkschemalen = SQL_NTS;
    }

    SQLRETURN retcode = SQLPrimaryKeys(hstmt_, 
                                               pkcatalog,                 pknamelen,
                                               pkschema,                  pkschemalen, 
                                               (SQLCHAR*)table.c_str(),   SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLPrimaryKeys", hstmt_, SQL_HANDLE_STMT));
          throw SQLException(err("SQLPrimaryKeys", hstmt_, SQL_HANDLE_STMT));
       }
       std::shared_ptr<Resultset> resultset(new Resultset(henv_,hdbc_,hstmt_));
       return move(resultset);
    }
    else
    {
       ODBCError err;
       LOG_ERROR(err("SQLPrimaryKeys", hstmt_, SQL_HANDLE_STMT));
       throw SQLException(err("SQLPrimaryKeys", hstmt_, SQL_HANDLE_STMT));
    }
}


std::shared_ptr<Resultset>   DatabaseMetadata::getImportedKeys(std::string catalog,std::string schema,std::string table)
{
    SQLCHAR* pkcatalog;
    SQLSMALLINT pknamelen;
    SQLCHAR* pkschema;
    SQLSMALLINT pkschemalen;
    if(catalog == "%" || catalog == "")
    {
       pkcatalog = nullptr;
       pknamelen = 0;
    }
    else
    {
       pkcatalog = (SQLCHAR*)catalog.c_str();
       pknamelen = SQL_NTS;
    }

    if(schema  == "%" || schema  == "")
    {
       pkschema = nullptr;
       pkschemalen = 0;
    }
    else
    {
       pkschema = (SQLCHAR*)schema.c_str();
       pkschemalen = SQL_NTS;
    }

    SQLRETURN retcode = SQLForeignKeys(hstmt_, 
                                               pkcatalog,                 pknamelen,
                                               pkschema,                  pkschemalen, 
                                               (SQLCHAR*)table.c_str(),   SQL_NTS,
                                               NULL,                      0,
                                               NULL,                      0,
                                               NULL,                      0);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLForeignKeys", hstmt_, SQL_HANDLE_STMT));
          throw SQLException(err("SQLForeignKeys", hstmt_, SQL_HANDLE_STMT));
       }
       std::shared_ptr<Resultset> resultset(new Resultset(henv_,hdbc_,hstmt_));
       return move(resultset);
    }
    else
    {
       ODBCError err;
       LOG_ERROR(err("SQLForeignKeys", hstmt_, SQL_HANDLE_STMT));
       throw SQLException(err("SQLForeignKeys", hstmt_, SQL_HANDLE_STMT));
    }
}


std::shared_ptr<Resultset>   DatabaseMetadata::getExportedKeys(std::string catalog,std::string schema,std::string table)
{
    SQLCHAR* pkcatalog;
    SQLSMALLINT pknamelen;
    SQLCHAR* pkschema;
    SQLSMALLINT pkschemalen;
    if(catalog == "%" || catalog == "")
    {  
       pkcatalog = nullptr;
       pknamelen = 0;
    }
    else
    {  
       pkcatalog = (SQLCHAR*)catalog.c_str();
       pknamelen = SQL_NTS;
    }
    
    if(schema  == "%" || schema  == "")
    {  
       pkschema = nullptr;
       pkschemalen = 0;
    }
    else
    {  
       pkschema = (SQLCHAR*)schema.c_str();
       pkschemalen = SQL_NTS;
    }

    SQLRETURN retcode = SQLForeignKeys(hstmt_, 
                                               NULL,                      0,
                                               NULL,                      0,
                                               NULL,                      0,
                                               pkcatalog,                 pknamelen,
                                               pkschema,                  pkschemalen,
                                               (SQLCHAR*)table.c_str(),   SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLForeignKeys", hstmt_, SQL_HANDLE_STMT));
          throw SQLException(err("SQLForeignKeys", hstmt_, SQL_HANDLE_STMT));
       }
       std::shared_ptr<Resultset> resultset(new Resultset(henv_,hdbc_,hstmt_));
       return move(resultset);
    }
    else
    {
       ODBCError err;
       LOG_ERROR(err("SQLForeignKeys", hstmt_, SQL_HANDLE_STMT)); 
       throw SQLException(err("SQLForeignKeys", hstmt_, SQL_HANDLE_STMT));
    }
}


std::shared_ptr<Resultset>  DatabaseMetadata::getStatistics(std::string catalog,std::string schema,std::string table)
{
    SQLRETURN retcode = SQLStatistics(hstmt_,
                                      (SQLCHAR*)catalog.c_str(), SQL_NTS,
                                      (SQLCHAR*)schema.c_str(),  SQL_NTS,
                                      (SQLCHAR*)table.c_str(),   SQL_NTS,
                                      SQL_INDEX_ALL,             SQL_QUICK);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLStatistics", hstmt_, SQL_HANDLE_STMT));
          throw SQLException(err("SQLStatistics", hstmt_, SQL_HANDLE_STMT));
       }
       std::shared_ptr<Resultset> resultset(new Resultset(henv_,hdbc_,hstmt_));
       return move(resultset);
    }
    else
    {
       ODBCError err;
       LOG_ERROR(err("SQLStatistics", hstmt_, SQL_HANDLE_STMT));
       throw SQLException(err("SQLStatistics", hstmt_, SQL_HANDLE_STMT));
    }
}

};/*namespace cppsqlx*/
