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

#ifndef __DRIVERMANAGER_HPP__
#define __DRIVERMANAGER_HPP__
#include <cppsqlxincludes.hpp>
#include <dbprovider.hpp>

namespace cppsqlx
{

/* Locations of supported drivers */
#ifndef NZ_ODBC_LIBRARY
#define NZ_ODBC_LIBRARY            "/produit/netezza/current/lib64/libnzodbc.so"
#endif

#ifndef PG_ODBC_LIBRARY
#define PG_ODBC_LIBRARY            "/usr/lib64/psqlodbcw.so"
#endif

#ifndef ORA_ODBC_LIBRARY
#define ORA_ODBC_LIBRARY           "/usr/lib/oracle/11.2/client64/lib/libsqora.so.11.1"
#endif

#ifndef VERTICA_ODBC_LIBRARY
#define VERTICA_ODBC_LIBRARY       "/opt/vertica/lib64/libverticaodbc.so"
#endif

#ifndef MONETDB_ODBC_LIBRARY
#define MONETDB_ODBC_LIBRARY       "/usr/lib/libMonetODBC.so"
#endif

#ifndef MONETDB_ODBC_SETUP_LIBRARY
#define MONETDB_ODBC_SETUP_LIBRARY "/usr/lib/libMonetODBC.so"
#endif

#ifndef DRILL_ODBC_LIBRARY
#define DRILL_ODBC_LIBRARY         "/opt/mapr/drillodbc/lib/64/libmaprdrillodbc64.so"
#endif

/*
 *
 *
 *
 **/
class DriverManager
{
   public:
   DriverManager();
   ~DriverManager();

   private:
   std::string                       tempdir_;
   std::string                       odbcinifilepath_;
   std::string                       odbcinstinifilepath_;
   std::vector<dsn>                  datasources_;
   std::map<DBPROVIDER,std::string>  providers_;
   std::string                       maprdrillini_;


   public:
   /* The single instance of this class */
   static std::shared_ptr<DriverManager>    instance_;

   /* getInstance
    * @return The sinfle instance of this class
    **/
   static std::shared_ptr<DriverManager>    getInstance();

   /* Add Datasource to managed datasources
    * @dbprovider Database provider
    * @host The database host
    * @port The database port
    * @database The database name
    **/
   void addDSN(DBPROVIDER dbprovider,std::string host,int port,std::string database,std::string schema = "");

};

};
#endif //__DRIVERMANAGER_HPP__
