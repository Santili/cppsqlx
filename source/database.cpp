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
#include <database.hpp>
#include <logger.hpp>
#include <odbcerror.hpp>
#include <sqlexception.hpp>


namespace cppsqlx
{
std::mutex                    g_i_mutex;

Database::Database(DBPROVIDER provider,std::string host,int port,std::string name,std::string schema):
provider_(provider),
host_(host),
port_(port),
name_(name),
schema_(schema)
{  
   std::shared_ptr<DriverManager>  drivermanager = DriverManager::getInstance();
   std::lock_guard<std::mutex> guard(odbcinimutex);
   dsnentry_ = name + "_" + host_ + "_" + std::to_string(port_);
   DriverManager::getInstance()->addDSN(provider_,host_,port_,name_,schema_);
   std::string message = std::string("Database::Database() provider_(") + std::to_string(provider_) 
                                                           + ") host_(" + host_ 
                                                           + ") port_(" + std::to_string(port_) 
                                                           + ") name_(" + name_ 
                                                           + ") schema_(" + schema_ + ")";
   LOG_DEBUG(message);
}


Database::~Database()
{
   std::string message = std::string("Database::Database() provider_(") + std::to_string(provider_) 
                                                           + ") host_(" + host_ 
                                                           + ") port_(" + std::to_string(port_) 
                                                           + ") name_(" + name_ 
                                                           + ") schema_(" + schema_ + ")";
   LOG_DEBUG(message);
}


Database&  Database::dbms(std::string name)
{
   provider_ =  getProvider(name);
   LOG_DEBUG(std::string("Database provider:") + std::to_string(provider_) + "[" + name + "]" );
   return *this;
}

Database&  Database::host(std::string addr)
{
   host_ = addr;
   LOG_DEBUG(std::string("Database host:") + host_);
   return *this;
}


Database&  Database::port(int port)
{
   port_ = port;
   LOG_DEBUG(std::string("Database port:") + std::to_string(port_));
   return *this;
}

Database& Database::name(std::string database)
{
  name_ = database;
  LOG_DEBUG(std::string("Database name:") + name_);
  return *this;
}

Database&  Database::schema(std::string schema)
{
   schema_ = schema;
   LOG_DEBUG(std::string("Database schema:") + schema_);
   return *this;
}

Database& Database::database(std::string db)
{
   name_ = db;
   LOG_DEBUG(std::string("Database name:") + name_);
   return *this;
}

std::shared_ptr<Connection>  Database::getConnection(std::string user,std::string password)
{
   LOG_DEBUG(std::string(__FILE__) + " " + std::to_string(__LINE__));
   std::lock_guard<std::mutex> lock(g_i_mutex);
   SQLHENV   henv;
   SQLHDBC   hdbc;
   SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
   SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
   SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
   SQLRETURN ret; 
   SQLCHAR outstr[1024];
   SQLSMALLINT outstrlen;
   std::string dsnname;
   dsnname += "DSN=" + dsnentry_ + ";UID=" + user + ";PWD=" + password;
   LOG_DEBUG(std::string("ODBCSYSINI :") + std::string(getenv("ODBCSYSINI")));
   LOG_DEBUG(std::string("ODBCINI:") + std::string(getenv("ODBCINI")));
   LOG_DEBUG(std::string("TNS_ADMIN:") + std::string(getenv("TNS_ADMIN")));
   LOG_DEBUG(dsnname);
   ret = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)dsnname.c_str(), SQL_NTS,outstr, sizeof(outstr), &outstrlen,SQL_DRIVER_COMPLETE);
   LOG_DEBUG(std::string(__FILE__) + " " + std::to_string(__LINE__));
   if (SQL_SUCCEEDED(ret)) 
   {
      if (ret == SQL_SUCCESS_WITH_INFO) 
      {
         LOG_DEBUG("SQLDriverConnect");
         ODBCError err;
         LOG_DEBUG(err("SQLDriverConnect", hdbc, SQL_HANDLE_DBC));
      }
      std::shared_ptr<Connection> cnx(new Connection(user,password,henv,hdbc));
      cnx->setProvider(provider_);
      cnx->setSchema(schema_);
      LOG_DEBUG(std::string("Provider set for connection : ") + DBPROVIDERS[provider_]);
      return move(cnx);
   } 
   else  
   {
      ODBCError err;
      std::string message = err("SQLDriverConnect", hdbc, SQL_HANDLE_DBC) + "\nDSN : " + dsnentry_ + "\nDatabase user : " + user;
      throw SQLException(message);
   }
}

std::shared_ptr<Connection>   Database::connect(std::string user,std::string password)
{
   std::lock_guard<std::mutex> guard(odbcinimutex);
   dsnentry_ = name_ + "_" + host_ + "_" + std::to_string(port_);
   DriverManager::getInstance()->addDSN(provider_,host_,port_,name_,schema_);
   LOG_DEBUG(std::string(__FILE__) + " " + std::to_string(__LINE__));
   return getConnection(user,password);
}


}/*namespace cppsqlx*/
