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
#include <drivermanager.hpp>
#include <logger.hpp>
#include <unistd.h>
#include <stdlib.h>
#include <boost/filesystem.hpp>


/*namespace cppsqlx*/
namespace cppsqlx
{

DriverManager::DriverManager()
{
   LOG_DEBUG("DriverManager::DriverManager()");

   /* Declare of sopported databases */
   providers_.insert({DBPROVIDER::NETEZZA,   "Netezza"});
   providers_.insert({DBPROVIDER::POSTGRESQL,"PostgreSQL"});
   providers_.insert({DBPROVIDER::GREENPLUM, "Greenplum"});
   providers_.insert({DBPROVIDER::ORACLE,    "Oracle"});
   providers_.insert({DBPROVIDER::MONETDB,   "MonetDB"});
   providers_.insert({DBPROVIDER::VERTICA,   "Vertica"});
   providers_.insert({DBPROVIDER::DRILL,     "Drill"});

   /* Temporary folder where to work to*/
   char* c_diztmp = getenv("CPPSQLX_TMP_DIR");
   if(c_diztmp == nullptr)
     LOG_WARN("CPPSQLX_TMP_DIR environnement variable is not set, /tmp/ will be used as temporary directory");
   tempdir_ = c_diztmp == nullptr ? "/tmp/" :  c_diztmp;
   if( (std::string() + (*(tempdir_.end() -1))) != "/")
   {
       tempdir_ += "/";
   }


   /*
    * Variables required from ODBC library
    **/
   odbcinifilepath_        = tempdir_ + std::to_string(getpid()) + "/odbc.ini";
   std:: string odbcsysdir = tempdir_ + std::to_string(getpid());
   maprdrillini_           = tempdir_ + std::to_string(getpid()) + "/mapr.drillodbc.ini";

   if( setenv("ODBCINI", odbcinifilepath_.c_str(),true) != 0)
     throw std::runtime_error("Unable to set ODBCINI PATH");

   if( setenv("ODBCSYSINI",odbcsysdir.c_str(),true) != 0)
     throw std::runtime_error("Unable to set ODBCSYSINI PATH");

   if( setenv("NZ_ODBC_INI_PATH",odbcsysdir.c_str(),true) != 0)
     throw std::runtime_error("Unable to set ODBCSYSINI PATH");

   if( setenv("MAPRDRILLINI",maprdrillini_.c_str(),true) != 0)
     throw std::runtime_error("Unable to set ODBCSYSINI PATH");


   /*
    * Variables required for ORACLE
    **/
   std::string tnsnamespath = tempdir_ + std::to_string(getpid());
   if( setenv("TNS_ADMIN",tnsnamespath.c_str(),true) != 0)
     throw std::runtime_error("Unable to set TNS_ADMIN PATH");


   /*
    * Declaring supported databases in odbcinst.ini
    **/ 
   boost::filesystem::create_directory(tempdir_ + std::to_string(getpid()));
   odbcinstinifilepath_ = tempdir_ + std::to_string(getpid()) + "/odbcinst.ini";
   std::ofstream ofs (odbcinstinifilepath_, std::ofstream::out);
   std::string odbcdriverentry; 

   /*
    * Pre-declaration of all databases
    **/  
   odbcdriverentry += "[ODBC Drivers]\n";
   odbcdriverentry += providers_[NETEZZA]    + "=Installed\n";
   odbcdriverentry += providers_[POSTGRESQL] + "=Installed\n";
   odbcdriverentry += providers_[ORACLE]     + "=Installed\n";
   odbcdriverentry += providers_[MONETDB]    + "=Installed\n";
   odbcdriverentry += providers_[VERTICA]    + "=Installed\n";
   odbcdriverentry += providers_[DRILL]      + "=Installed\n";
   odbcdriverentry += providers_[GREENPLUM]  + "=Installed\n";
   odbcdriverentry += "\n";

   /*
    * Netezza specific part
    **/
   odbcdriverentry += "[" +  providers_[NETEZZA] +  "]\n";
   odbcdriverentry += "Driver           = " + std::string(NZ_ODBC_LIBRARY) + "\n" ;
   odbcdriverentry += "Setup            = " + std::string(NZ_ODBC_LIBRARY) + "\n";
   odbcdriverentry += "Description      = Netezza ODBC driver\n";
   odbcdriverentry += "Threading        = 0\n";
   odbcdriverentry += "FileUsage        = 1\n"; 
   odbcdriverentry += "\n";

   /*
    * Postgresql specific part
    **/ 
   odbcdriverentry += "[" +  providers_[POSTGRESQL] +  "]\n";
   odbcdriverentry += "Description      = PostgreSQL driver for Linux\n";
   odbcdriverentry += "Driver           = " + std::string(PG_ODBC_LIBRARY) + "\n";
   odbcdriverentry += "Setup            = " + std::string(PG_ODBC_LIBRARY) + "\n";
   odbcdriverentry += "Threading        = 0\n";
   odbcdriverentry += "FileUsage        = 1\n";
   odbcdriverentry += "\n";

   /*
    * Greenplum specific part
    **/   
   odbcdriverentry += "[" +  providers_[GREENPLUM] +  "]\n";
   odbcdriverentry += "Description      = Greenplum driver for Linux\n";
   odbcdriverentry += "Driver           = " + std::string(PG_ODBC_LIBRARY) + "\n";
   odbcdriverentry += "Setup            = " + std::string(PG_ODBC_LIBRARY) + "\n";
   odbcdriverentry += "Threading        = 0\n";
   odbcdriverentry += "FileUsage        = 1\n";
   odbcdriverentry += "\n";

   /*
    * Vertica specific part
    **/  
   odbcdriverentry += "[" +  providers_[VERTICA] +  "]\n";
   odbcdriverentry += "Description      = Vertica driver for Linux\n";
   odbcdriverentry += "Driver           = " + std::string(VERTICA_ODBC_LIBRARY) + "\n";
   odbcdriverentry += "Setup            = " + std::string(VERTICA_ODBC_LIBRARY) + "\n";
   odbcdriverentry += "Threading        = 5\n";
   odbcdriverentry += "FileUsage        = 1\n";
   odbcdriverentry += "\n";

   /*
    * Oracle specific part
    **/ 
   odbcdriverentry += "[" +  providers_[ORACLE] +  "]\n";
   odbcdriverentry += "Description      = Oracle ODBC driver\n";
   odbcdriverentry += "Driver           = " + std::string(ORA_ODBC_LIBRARY) + "\n";
   odbcdriverentry += "Setup            = " + std::string(ORA_ODBC_LIBRARY) + "\n";
//   odbcdriverentry += "Threading        = 0\n";
   odbcdriverentry += "FileUsage        =1\n";
/*
   odbcdriverentry += "CPTimeout        =\n";
   odbcdriverentry += "CPReuse          =\n";
   odbcdriverentry += "Driver Logging   = 7\n";
*/
   odbcdriverentry += "\n";

   /*
    * Monetdb specific part
    **/   
   odbcdriverentry += "[" +  providers_[MONETDB] +  "]\n";
   odbcdriverentry += "Driver           = " + std::string(MONETDB_ODBC_LIBRARY) + "\n" ;
   odbcdriverentry += "Setup            = " + std::string(MONETDB_ODBC_SETUP_LIBRARY) + "\n";
   odbcdriverentry += "Description      = Monetdb ODBC driver\n";
   odbcdriverentry += "Commonlog        = 1\n";
   odbcdriverentry += "Debug            = 1\n";
   odbcdriverentry += "\n";

   /*
    * Drill specific part
    **/ 
   odbcdriverentry += "[" +  providers_[DRILL] +  "]\n";
   odbcdriverentry += "Driver           = " + std::string(DRILL_ODBC_LIBRARY) + "\n" ;
   odbcdriverentry += "Setup            = " + std::string(DRILL_ODBC_LIBRARY) + "\n";
   odbcdriverentry += "Description      = Drill ODBC driver\n";
   odbcdriverentry += "\n";

   ofs << odbcdriverentry;
   ofs.close();


   /*
    * Drill specific ini  configuration file
    **/
   std::ofstream drillinifs (maprdrillini_, std::ofstream::out);
   std::string drillinientry;

   drillinientry +="[Driver]\n";
   drillinientry +="DriverManagerEncoding=UTF-16\n";
   drillinientry +="ErrorMessagesPath=/opt/mapr/drillodbc/ErrorMessages\n";
   drillinientry +="LogLevel=0\n";
   drillinientry +="LogPath=/var/log/mapr\n";
   drillinientry +="SwapFilePath=" + tempdir_ + std::to_string(getpid());
   drillinientry +="\n";
   drillinientry +="ODBCInstLib=/usr/lib/x86_64-linux-gnu/libodbcinst.so.2\n";

   drillinifs << drillinientry;
   drillinifs.close();

 
}


DriverManager::~DriverManager()
{
   LOG_DEBUG("DriverManager::~DriverManager()");
   boost::filesystem::path  temppath(tempdir_.c_str() + std::to_string(getpid()));
   try
   {  
      boost::system::error_code ec;
      if ( boost::filesystem::exists( temppath ) )
      { 
        boost::filesystem::remove_all( temppath);
      }
   }
   catch(boost::filesystem::filesystem_error const & e)
   {  
      std::string message = std::string("Unable to remove temp directory :") + tempdir_;
      LOG_WARN(message);
   }
}


std::shared_ptr<DriverManager>  DriverManager::getInstance()
{  
   if(instance_ == nullptr)
   { 
     LOG_DEBUG("DriverManager::getInstance() - Create instance of DriverManager");
     instance_ = std::shared_ptr<DriverManager>(new DriverManager());
   }
   return  instance_;
}


void DriverManager::addDSN(DBPROVIDER dbprovider,std::string host,int port,std::string database,std::string schema)
{
   LOG_DEBUG("DriverManager::addDSN()");
   dsn d(dbprovider,host,port,database);
   if( find_if(datasources_.begin(),
               datasources_.end(),
               [d](dsn& ds)
               {
                    return (std::get<0>(d)==std::get<0>(ds) && std::get<1>(d)==std::get<1>(ds) && std::get<2>(d)==std::get<2>(ds) && std::get<3>(d)==std::get<3>(ds));
               })==datasources_.end())
   {
       std::ofstream ofs (odbcinifilepath_, std::ofstream::out | std::ofstream::app);
       std::string odbcdsnentry;
       odbcdsnentry += "[" + database + "_" + host + "_" + std::to_string(port)  +  "]\n";

       switch( dbprovider)
       {
          case DBPROVIDER::UNKNOWN:
          {
             break;
          }
          case DBPROVIDER::POSTGRESQL :
          {
             odbcdsnentry += "Driver           = " + providers_[dbprovider] + "\n";
             odbcdsnentry += "Trace            = Yes\n";
             odbcdsnentry += "TraceFile        = sql.log\n";
             odbcdsnentry += "Database         = " + database + "\n";
             odbcdsnentry += "Servername       = " + host + "\n";
             odbcdsnentry += "UserName         = \n";
             odbcdsnentry += "Password         = \n";
             odbcdsnentry += "Port             = " + std::to_string(port) + "\n";
             odbcdsnentry += "Protocol         = 6.4\n";
             odbcdsnentry += "ReadOnly         = No\n";
             odbcdsnentry += "RowVersioning    = No\n";
             odbcdsnentry += "ShowSystemTables = Yes\n";
             odbcdsnentry += "ShowOidColumn    = No\n";
             odbcdsnentry += "FakeOidIndex     = No\n";
             odbcdsnentry += "QueryTimeout     = 0\n";
             break;
          }
          case DBPROVIDER::MONETDB:
          {
             odbcdsnentry += "Description     = ODBC Driver for MonetDB SQL Server\n";
             odbcdsnentry += "Driver          = " + providers_[dbprovider] + "\n";
             odbcdsnentry += "Port            = " + std::to_string(port) + "\n";
             odbcdsnentry += "Host            = " + host + "\n";
             odbcdsnentry += "Database        = " + database + "\n";
             odbcdsnentry += "User            = \n";
             odbcdsnentry += "Password        = \n";
             odbcdsnentry += "Debug           = 1\n";
             odbcdsnentry += "Trace           = 1\n";
             odbcdsnentry += "DebugFile       = /var/log/odbc-debugfile.log\n";
             odbcdsnentry += "TraceFile       = /var/log/odbc-tracefile.log\n";
             break;
          }
          case DBPROVIDER::DRILL:
          {
             odbcdsnentry += "Description     = ODBC Driver for Drill\n";
             odbcdsnentry += "Driver          = " + providers_[dbprovider] + "\n";
             odbcdsnentry += "ConnectionType  = Direct\n";
             odbcdsnentry += "HOST            = " + host + "\n";
             odbcdsnentry += "PORT            = " + std::to_string(port) + "\n";
             odbcdsnentry += "ZKQuorum        =\n";
             odbcdsnentry += "ZKClusterID     =\n";
             odbcdsnentry += "AuthenticationType=No Authentication\n";
             odbcdsnentry += "UID             =\n";
             odbcdsnentry += "PWD             =\n";
             odbcdsnentry += "AdvancedProperties=CastAnyToVarchar=true;HandshakeTimeout=5;QueryTimeout=180;TimestampTZDisplayTimezone=utc;ExcludedSchemas=sys,INFORMATION_SCHEMA;NumberOfPrefetchBuffers=5;\n";
             odbcdsnentry += "Catalog         = " + database + "\n";
             odbcdsnentry += "Schema          = " + schema + "\n";
             break;
          }
          case DBPROVIDER::VERTICA:
          {
             odbcdsnentry += "Description     = ODBC Driver for vertica\n";
             odbcdsnentry += "Driver          = " + providers_[dbprovider] + "\n";
             odbcdsnentry += "Port            = " + std::to_string(port) + "\n";
             odbcdsnentry += "Host            = " + host + "\n";
             odbcdsnentry += "Database        = " + database + "\n";
             odbcdsnentry += "UserName        = \n";
             odbcdsnentry += "Password        = \n";
             odbcdsnentry += "ColumnsAsChar   = \n";
             odbcdsnentry += "ConnSettings    = SET SEARCH_PATH = " + schema + ", public;\n";
             odbcdsnentry += "TxnReadCommitted=1\n";
             odbcdsnentry += "DirectBatchInsert=\n";
             odbcdsnentry += "SSLKeyFile      = /home/dbadmin/client.key\n";
             odbcdsnentry += "SSLCertFile     = /home/dbadmin/client.crt\n";
             break;
          }
          case DBPROVIDER::GREENPLUM:
          {
             odbcdsnentry += "Driver           = " + providers_[dbprovider] + "\n";
             odbcdsnentry += "Trace            = Yes\n";
             odbcdsnentry += "TraceFile        = sql.log\n";
             odbcdsnentry += "Database         = " + database + "\n";
             odbcdsnentry += "Servername       = " + host + "\n";
             odbcdsnentry += "UserName         = \n";
             odbcdsnentry += "Password         = \n";
             odbcdsnentry += "Port             = " + std::to_string(port) + "\n";
             odbcdsnentry += "Protocol         = 6.4\n";
             odbcdsnentry += "ReadOnly         = No\n";
             odbcdsnentry += "RowVersioning    = No\n";
             odbcdsnentry += "ShowSystemTables = Yes\n";
             odbcdsnentry += "ShowOidColumn    = No\n";
             odbcdsnentry += "FakeOidIndex     = No\n";
             odbcdsnentry += "QueryTimeout     = 0\n";
             break;
          }
          case DBPROVIDER::NETEZZA:
          {
             odbcdsnentry += "Driver           = " + providers_[dbprovider] + "\n";
             odbcdsnentry += "Description      = " + providers_[dbprovider] + " ODBC\n";
             odbcdsnentry += "Servername       = " + host + "\n";
             odbcdsnentry += "Port             = " + std::to_string(port) + "\n";
             odbcdsnentry += "Database         = " + database + "\n";
             odbcdsnentry += "SchemaName       = " + schema + "\n";
             odbcdsnentry += "Username         = \n";
             odbcdsnentry += "Password         = \n";
             odbcdsnentry += "ReadOnly         = false\n";
             odbcdsnentry += "FastSelect       = false\n";
             odbcdsnentry += "ShowSystemTables = false\n";
             odbcdsnentry += "LegacySQLTables  = false\n";
             odbcdsnentry += "LoginTimeout     = 0\n";
             odbcdsnentry += "QueryTimeout     = 0\n";
             odbcdsnentry += "DateFormat       = 1\n";
             odbcdsnentry += "NumericAsChar    = false\n";
             odbcdsnentry += "SQLBitOneZero    = false\n";
             odbcdsnentry += "StripCRLF        = false\n";
             odbcdsnentry += "securityLevel    = preferredUnSecured\n";
             break;
          }
          case DBPROVIDER::ORACLE:
          {
             LOG_DEBUG(std::string("DriverManager::addDSN ") + std::to_string(__LINE__));
             /*
              * TNSNAMES
              ******/
             std::string tnsnamespath = tempdir_ + std::to_string(getpid());
             std::string tnsnamesfilepath = tnsnamespath + "/tnsnames.ora";
             std::ofstream tnsofs (tnsnamesfilepath, std::ofstream::out);
             std::string tnsentry;
             tnsentry += database + "=( DESCRIPTION =(ADDRESS_LIST =(ADDRESS =(PROTOCOL = TCP)(Host = ";
             tnsentry += host + " )(Port = 1521)))(CONNECT_DATA = (SID = " ;
             tnsentry += database + ")))\n";
             tnsofs << tnsentry;
             tnsofs.close();
             /*
              * ODBC
              ******/
             odbcdsnentry += "DSN              = " + database + "\n";
             //odbcdsnentry += "DSN              = " + providers_[dbprovider] + "\n";
             odbcdsnentry += "Driver= " + providers_[dbprovider] + "\n";
             odbcdsnentry += "UserID           = \n";
             odbcdsnentry += "Password         = \n";
             odbcdsnentry += "ServerName       = " + database + "\n";
             odbcdsnentry += "HostName         = " + host + "\n";
             odbcdsnentry += "Port             = " + std::to_string(port) + "\n";
             odbcdsnentry += "QueryTimeout     = T\n";
             odbcdsnentry += "Application Attributes = T\n";
             odbcdsnentry += "Attributes       = W\n";
             odbcdsnentry += "BatchAutocommitMode = IfAllSuccessful\n";
             odbcdsnentry += "BindAsFLOAT      = F\n";
             odbcdsnentry += "CloseCursor      = F\n";
             odbcdsnentry += "DisableDPM       = F\n";
             odbcdsnentry += "DisableMTS       = T\n";
             odbcdsnentry += "EXECSchemaOpt    =\n";
             odbcdsnentry += "EXECSyntax       = T\n";
             odbcdsnentry += "Failover         = T\n";
             odbcdsnentry += "FailoverDelay    = 10\n";
             odbcdsnentry += "FailoverRetryCount = 10\n";
             odbcdsnentry += "FetchBufferSize  = 64000\n";
             odbcdsnentry += "ForceWCHAR       = F\n";
             odbcdsnentry += "Lobs             = T\n";
             odbcdsnentry += "Longs            = T\n";
             odbcdsnentry += "MaxLargeData     = 0\n";
             odbcdsnentry += "MetadataIdDefault = F\n";
             odbcdsnentry += "ResultSets       = T\n";
             odbcdsnentry += "SQLGetData extensions = F\n";
             odbcdsnentry += "Translation DLL  =\n";
             odbcdsnentry += "Translation Option = 0\n";
             odbcdsnentry += "DisableRULEHint  = T\n";
             odbcdsnentry += "StatementCache   =F\n";
             odbcdsnentry += "CacheBufferSize  =20\n";
             odbcdsnentry += "UseOCIDescribeAny=F\n";
             odbcdsnentry += "MaxTokenSize     =8192\n";
             break;
          }
          default :
          {
          };
             break;
       }
       LOG_DEBUG(std::string("DriverManager::addDSN ") + std::to_string(__LINE__));
       LOG_DEBUG(odbcdsnentry);
       ofs << odbcdsnentry;
       ofs.close();
       datasources_.push_back(d);
   };

}

} /*namespace cppsqlx*/
