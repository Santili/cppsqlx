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
#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__
#include <cppsqlxincludes.hpp>
#include <drivermanager.hpp>
#include <connection.hpp>


namespace cppsqlx
{
/* Database
 *
 * Database Holds information to access a database
 * It is factory for Connections to physical databases
 **/

static std::mutex odbcinimutex;

class Database
{  
   public:
   Database(DBPROVIDER provider,std::string host,int port,std::string name,std::string schema="");
   Database(){};
   ~Database();
   
   private:                 
   std::string                   name_;
   std::string                   schema_;
   DBPROVIDER                    provider_;
   std::string                   host_;
   int                           port_;
   std::string                   tempdir_;
   std::string                   odbcinifilepath_;
   std::string                   dsnentry_;
   
   public:
   std::shared_ptr<Connection>   connect(std::string user,std::string password);
   std::shared_ptr<Connection>   getConnection(std::string user,std::string password);     
   Database&                     dbms(std::string name);
   Database&                     host(std::string addr);
   Database&                     port(int port);
   Database&                     name(std::string database);
   Database&                     schema(std::string schema);
   Database&                     database(std::string db);
};

};/*namespace cppsqlx*/
#endif //__DATABASE_HPP__
