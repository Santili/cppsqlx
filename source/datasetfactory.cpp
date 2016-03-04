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
#include <datasetfactory.hpp>
#include <resultset.hpp>
#include <sqlexception.hpp>
#include <odbcerror.hpp>
#include <databasemetadata.hpp>
#include <resultsetmetadata.hpp>
#include <logger.hpp>

namespace cppsqlx
{

DatasetFactory::DatasetFactory()
{
   LOG_DEBUG("DatasetFactory::DatasetFactory");
}


DatasetFactory::~DatasetFactory()
{
   LOG_DEBUG("DatasetFactory::~DatasetFactory");
}



Dataset  DatasetFactory::dsFrom(std::string name,Dataset ds,DBPROVIDER provider)
{
   Dataset   dscopy(name);
   std::map<int,Column> columns;
   if(provider != DBPROVIDER::UNKNOWN || provider != dscopy.provider())
   {
      for(auto i = 1;i <= ds.rowSize();i++)
      {
          std::string  targettype;
          switch(provider)
	{
             case DBPROVIDER::ORACLE:
               {
                  switch(ds.at(i).sqlType())
                  {
                     case SQL_VARCHAR:
                        targettype = std::string("VARCHAR2(") + std::to_string(ds.at(i).precision()) + ")";
                        break;
                     case SQL_NUMERIC:
                        targettype = std::string("NUMBER(") + std::to_string(ds.at(i).precision()) + "," + std::to_string(ds.at(i).scale()) + ")";
                        break;
                     case SQL_DOUBLE:
                        targettype = std::string("FLOAT(53)");
                        break;
                     case SQL_DECIMAL:
                        targettype = std::string("NUMBER(") + std::to_string(ds.at(i).precision()) + "," + std::to_string(ds.at(i).scale()) + ")";
                        break;
                     case SQL_FLOAT:
                        targettype = std::string("FLOAT(53)");
                        break;
                     case SQL_INTEGER:
                        targettype = std::string("NUMBER(10)");
                        break;
                     case SQL_BIGINT:
                        targettype = std::string("NUMBER(19,0)");
                        break;
                     case SQL_REAL:
                        targettype = std::string("FLOAT(25)");
                        break;
                     case SQL_SMALLINT:
                        targettype = std::string("NUMBER(5)");
                        break;
                     case SQL_TYPE_TIME:
                        targettype = std::string("CHAR(15)");
                        break;
                     case SQL_TINYINT:
                        targettype = std::string("NUMBER(3)");
                        break;
                     case SQL_TYPE_TIMESTAMP:
                        targettype = std::string("DATE");
                        break;
                     case SQL_TYPE_DATE:
                        targettype = std::string("DATE");
                        break;
                     case SQL_BINARY:
                        targettype = std::string("RAW");
                        break;
                     case SQL_VARBINARY:
                        targettype = std::string("RAW");
                        break;
                     case SQL_CHAR:
                        targettype = std::string("CHAR(") + std::to_string(ds.at(i).precision()) + ")";
                        break;
                     case SQL_BIT:
                        targettype = std::string("CHAR(1)");
                        break;
                     default:
                        break;
                  }
                  Column col(ds.at(i).name(),ds.at(i).position(),targettype,
                             ds.at(i).size(),ds.at(i).precision(),ds.at(i).sqlType(),
                             ds.at(i).scale(),ds.at(i).isNullable());
                  columns.insert({ds.at(i).position(),col});
               }
               break;
             case DBPROVIDER::NETEZZA:
               {
                  switch(ds.at(i).sqlType())
                  {
                     case SQL_VARCHAR:
                        targettype = std::string("VARCHAR(") + std::to_string(ds.at(i).precision()) + ")";
                        break;
                     case SQL_NUMERIC:
                        if(ds.at(i).scale() == 0 && ds.at(i).precision() <= 2)
                          targettype = std::string("BYTEINT");
                        else if(ds.at(i).scale() == 0 && (2 < ds.at(i).size()) && (ds.at(i).size() <= 4))
                          targettype = std::string("SMALLINT");
                        else if(ds.at(i).scale() == 0 && 4 < ds.at(i).size() && ds.at(i).size() <= 9)
                          targettype = std::string("INTEGER");
                        else if(ds.at(i).scale() == 0 && 9 < ds.at(i).size() && ds.at(i).size() <= 18)
                          targettype = std::string("BIGINT"); 
                        else
                          targettype = std::string("NUMERIC(") + std::to_string(ds.at(i).precision()) + "," + std::to_string(ds.at(i).scale()) + ")";
                        break;
                     case SQL_DOUBLE:
                        targettype = std::string("DOUBLE PRECISION");
                        break;
                     case SQL_DECIMAL:
                        if(ds.at(i).scale() == 0 && ds.at(i).precision() <= 2)
                          targettype = std::string("BYTEINT");
                        else if(ds.at(i).scale() == 0 && 2 < ds.at(i).precision() && ds.at(i).size() <= 4)
                          targettype = std::string("SMALLINT");
                        else if(ds.at(i).scale() == 0 && 4 < ds.at(i).precision() && ds.at(i).size() <= 9)
                          targettype = std::string("INTEGER");
                        else if(ds.at(i).scale() == 0 && 9 < ds.at(i).precision() && ds.at(i).size()<= 18)
                          targettype = std::string("BIGINT");
                        else
                          targettype = std::string("DECIMAL(") + std::to_string(ds.at(i).precision()) + "," + std::to_string(ds.at(i).scale()) + ")";
                        break;
                     case SQL_FLOAT:
                        targettype = std::string("DOUBLE PRECISION");
                        break;
                     case SQL_INTEGER:
                        targettype = std::string("INTEGER");
                        break;
                     case SQL_BIGINT:
                        targettype = std::string("BIGINT");
                        break;
                     case SQL_REAL:
                        targettype = std::string("FLOAT");
                        break;
                     case SQL_SMALLINT:
                        targettype = std::string("SMALLINT");
                        break;
                     case SQL_TYPE_TIME:
                        targettype = std::string("TIME");
                        break;
                     case SQL_TINYINT:
                        targettype = std::string("SMALLINT");
                        break;
                     case SQL_TYPE_TIMESTAMP:
                        targettype = std::string("TIMESTAMP");
                        break;
                     case SQL_TYPE_DATE:
                        targettype = std::string("DATE");
                        break;
                     case SQL_BINARY:
                        targettype = std::string("varbinary(") + std::to_string(ds.at(i).precision()) + ")";
                        break;
                     case SQL_VARBINARY:
                        targettype = std::string("varbinary(") + std::to_string(ds.at(i).precision()) + ")";
                        break;
                     case SQL_CHAR:
                        targettype = std::string("CHAR(") + std::to_string(ds.at(i).precision()) + ")";
                        break;
                     case SQL_BIT:
                        targettype = std::string("CHAR(1)");
                        break;
                     default:
                        break;
                  }
                  Column col(ds.at(i).name(),ds.at(i).position(),targettype,
                             ds.at(i).size(),ds.at(i).precision(),ds.at(i).sqlType(),
                             ds.at(i).scale(),ds.at(i).isNullable());
                  columns.insert({ds.at(i).position(),col});
               }
               break;
             default:
               {
                  Column col(ds.at(i).name(),ds.at(i).position(),ds.at(i).type(),
                             ds.at(i).size(),ds.at(i).precision(),ds.at(i).sqlType(),
                             ds.at(i).scale(),ds.at(i).isNullable());
                  columns.insert({ds.at(i).position(),col});
               }
               break;
          }
      }
   }
   dscopy.columns_ = columns;
   dscopy.provider_ = provider;
   return dscopy;
}


Dataset  DatasetFactory::dsFrom(std::string name,std::shared_ptr<Connection> connection,std::string schema)
{
  std::map<int,Column>  columns;
  std::shared_ptr<DatabaseMetadata>     meta;
  try
  {
     meta  = connection->getMetadata();
  }
  catch(const SQLException& ex)
  {
     throw meta;
  }
  std::shared_ptr<Resultset>           rescols ;
  try
  {
     rescols = meta->getColumns("","",name);
  }
  catch(const SQLException& ex)
  {
     throw ex;
  }

  while(rescols->next())
  {
    int displaysize;
    int i ;
    int sqltype = 0;
    try
    {
       switch(connection->provider())
       {
          case DBPROVIDER::MONETDB :
            i = stoi(rescols->getString("ordinal_position"));     
            break;
          default :
            i = stoi(rescols->getString("ORDINAL_POSITION"));
            break;
       }
    }
    catch(const std::exception& e)
    {
       throw e;
    }


    try
    {
       switch(connection->provider())
       {
          case DBPROVIDER::MONETDB :
            sqltype = stoi(rescols->getString("data_type"));
            break;
          default :
            sqltype = stoi(rescols->getString("DATA_TYPE"));
            break;
       }
    }
    catch(const std::exception& e)
    {
       sqltype = 0;
    }


    try
    {
       switch(connection->provider())
       {
          case DBPROVIDER::MONETDB :
            displaysize = stoi(rescols->getString("column_size")); 
            break;
          default :
            displaysize = stoi(rescols->getString("COLUMN_SIZE"));
            break;
       }
    }
    catch(const std::exception& e)
    {
       displaysize = 0;
    }

  
    int precision;
    try
    {
       switch(connection->provider())
       {
          case DBPROVIDER::MONETDB :
            precision = stoi(rescols->getString("precision")); 
            break;
          default :
            precision = stoi(rescols->getString("PRECISION"));
            break;
       }

    }
    catch(...)
    {
       precision = displaysize;
    }
     

    int scale;
    try
    {

       switch(connection->provider())
       {
          case DBPROVIDER::MONETDB :
            if(rescols->getString("decimal_digits") == "" || rescols->getString("decimal_digits") == "NULL")
               scale = 0;
            else
               scale = stoi(rescols->getString("decimal_digits"));
            break;
          default :
            if(rescols->getString("DECIMAL_DIGITS") == "" || rescols->getString("DECIMAL_DIGITS") == "NULL")
               scale = 0;
            else
               scale = stoi(rescols->getString("DECIMAL_DIGITS"));          
            break;
       }

    }
    catch(const std::exception& e)
    {
       switch(connection->provider())
       {  
          case DBPROVIDER::MONETDB :
            if(rescols->getString("scale") == "" || rescols->getString("scale") == "NULL")
               scale = 0;
            else
               scale = stoi(rescols->getString("scale"));
            break;
          default :
            if(rescols->getString("SCALE") == "" || rescols->getString("SCALE") == "NULL")
               scale = 0;
            else
               scale = stoi(rescols->getString("SCALE"));
            break;
       }

    }
    bool nullable;


    switch(connection->provider())
    {
       case DBPROVIDER::MONETDB :
         nullable = stoi(rescols->getString("nullable"));
         break;
       default :
         nullable = stoi(rescols->getString("NULLABLE"));
         break;
    }

    
    switch(connection->provider())
    {
       case DBPROVIDER::MONETDB :
         {
           Column col(rescols->getString("column_name"),i,rescols->getString("type_name"),displaysize,precision,scale,sqltype,nullable);
           columns.insert({i,col});
         };
         break;
       default :
         {
           Column col(rescols->getString("COLUMN_NAME"),i,rescols->getString("TYPE_NAME"),displaysize,precision,scale,sqltype,nullable);
           columns.insert({i,col});
         };
         break;
    }
  }
  rescols->close();

  //std::shared_ptr<Dataset> ds(new Dataset(name));
  Dataset ds(name);

  if(schema != "")
  {
    ds.setSchema(schema);
  }
  else
  {
    ds.setSchema(connection->schema());
  }

 
 
  ds.setProvider(connection->provider());
  ds.columns_     = columns;
  return ds;
}


std::vector<Dataset>    DatasetFactory::datasetsFrom(std::shared_ptr<Connection> connection)
{
    std::vector<std::string>               tablenames;
    std::vector<Dataset>  datasets;
    std::shared_ptr<DatabaseMetadata> meta;
    try
    {
       meta = connection->getMetadata();
    }
    catch(const SQLException& ex)
    {
       throw ex;
    }

    std::shared_ptr<Resultset> res;
    try
    {
       res = meta->getTables("%",connection->schema(), "%","TABLE");
    }
    catch(const SQLException& ex)
    {
       throw ex;
    }

    while(res->next())
    {
       switch(connection->provider())
       {
           case DBPROVIDER::MONETDB :
               tablenames.push_back(res->getString("table_name"));
               break;
           default:
               tablenames.push_back(res->getString("TABLE_NAME"));
               break;
       }
    }
    res->close();

    for(auto tn : tablenames)
    {
       std::map<int,Column>        columns;
       std::shared_ptr<Resultset>  rescols;
       try
       {
           rescols = meta->getColumns("",connection->schema(),tn);
       }
       catch(const SQLException& ex)
       {
           throw ex;
       }

       std::shared_ptr<ResultsetMetadata> resmeta;
       try
       {
           resmeta  = rescols->getMetadata();
       }
       catch(const SQLException& ex)
       {
           throw ex;
       }

/*
       for(auto i = 0;i < resmeta->getColumnCount() ; i++)
       {
          if(i != resmeta->getColumnCount() - 1)
             cout << "|" ;
       }
*/

       while(rescols->next())
       {
          int displaysize;
          int i ;
          int sqltype = 0;
          try
          {  
             switch(connection->provider())
             {  
                 case DBPROVIDER::MONETDB :
                   i = stoi(rescols->getString("ordinal_position"));
                   break;
                 default :
                   i = stoi(rescols->getString("ORDINAL_POSITION"));
                   break;
             }
          }
          catch(const std::exception& e)
          {  
             throw e;
          }

          try
          {
            switch(connection->provider())
            {
               case DBPROVIDER::MONETDB :
                  sqltype = stoi(rescols->getString("data_type"));
                  break;
               default :
                  sqltype = stoi(rescols->getString("DATA_TYPE"));
                  break;
             }
          }
          catch(const std::exception& e)
          {
             sqltype = 0;
          }


          try
          {  
             switch(connection->provider())
             {  
                case DBPROVIDER::MONETDB :
                   displaysize = stoi(rescols->getString("column_size"));
                   break;
                default :
                   displaysize = stoi(rescols->getString("COLUMN_SIZE"));
                   break;
             }
    
          }
          catch(const std::exception& e)
          {  
              displaysize = 0;
          }

          int precision;
          try
          {
             switch(connection->provider())
             {
                case DBPROVIDER::MONETDB :
                  precision = stoi(rescols->getString("precision"));
                  break;
                default :
                  precision = stoi(rescols->getString("PRECISION"));
                  break;
             }

          }
          catch(...)
          {
             precision = displaysize;
          }

          int scale;
          try
          {
       
             switch(connection->provider())
             {  
                case DBPROVIDER::MONETDB :
                  if(rescols->getString("decimal_digits") == "" || rescols->getString("decimal_digits") == "NULL")
                     scale = 0;
                  else
                     scale = stoi(rescols->getString("decimal_digits"));
                  break;
                default :
                  if(rescols->getString("DECIMAL_DIGITS") == "" || rescols->getString("DECIMAL_DIGITS") == "NULL")
                     scale = 0;
                  else
                     scale = stoi(rescols->getString("DECIMAL_DIGITS"));
                  break;
             }
    
          }
          catch(const std::exception& e)
          {  
             switch(connection->provider())
             {  
                case DBPROVIDER::MONETDB :
                  if(rescols->getString("scale") == "" || rescols->getString("scale") == "NULL")
                     scale = 0;
                  else
                     scale = stoi(rescols->getString("scale"));
                  break;
                default :
                  if(rescols->getString("SCALE") == "" || rescols->getString("SCALE") == "NULL")
                     scale = 0;
                  else
                     scale = stoi(rescols->getString("SCALE"));
                  break;
             }
          }

          bool nullable;
          switch(connection->provider())
          {
             case DBPROVIDER::MONETDB :
               {
                 Column col(rescols->getString("column_name"),i,rescols->getString("type_name"),displaysize,precision,scale,sqltype,nullable);
                 columns.insert({i,col});
               };
               break;
             default :
               {
                 Column col(rescols->getString("COLUMN_NAME"),i,rescols->getString("TYPE_NAME"),displaysize,precision,scale,sqltype,nullable);
                 columns.insert({i,col});
               };
               break;
          }

       }
       rescols->close();
       Dataset ds(tn);
       ds.columns_     = columns;
       ds.setProvider(connection->provider());
       ds.setSchema(connection->schema());
       datasets.push_back(ds);
    }
    return datasets;
}


std::shared_ptr<Table>  DatasetFactory::tableFrom(std::string name,std::shared_ptr<Connection> connection)
{
  std::map<int,Column>  columns;
  std::shared_ptr<DatabaseMetadata>     meta ;
  try
  {
     meta  = connection->getMetadata();
  }
  catch(const SQLException& ex)
  {
     throw ex;
  }

  std::shared_ptr<Resultset>  rescols;
  try
  {
     rescols = meta->getColumns("","",name);
  }
  catch(const SQLException& ex)
  {
     throw ex;
  }

  while(rescols->next())
  {
    int displaysize;
    int i = stoi(rescols->getString("ORDINAL_POSITION"));
    int sqltype = 0;

    try
    {
       switch(connection->provider())
       {
          case DBPROVIDER::MONETDB :
            sqltype = stoi(rescols->getString("data_type"));
            break;
          default :
            sqltype = stoi(rescols->getString("DATA_TYPE"));
            break;
       }
    }
    catch(const std::exception& e)
    {
       sqltype = 0;
    }

    try
    {
       displaysize = stoi(rescols->getString("COLUMN_SIZE"));
    }
    catch(const std::exception& e)
    {
       displaysize = 0;
    }
    int precision;
    try
    {
       precision = stoi(rescols->getString("PRECISION"));
    }
    catch(...)
    {
       precision = stoi(rescols->getString("COLUMN_SIZE"));
    }
    int scale;
    try
    {
       scale = stoi(rescols->getString("DECIMAL_DIGITS"));
    }
    catch(const std::exception& e)
    {
       scale = stoi(rescols->getString("SCALE"));
    }
    bool nullable = stoi(rescols->getString("NULLABLE"));
    Column col(rescols->getString("COLUMN_NAME"),i,rescols->getString("TYPE_NAME"),displaysize,precision,scale,sqltype,nullable);
    columns.insert({i,col});
  }
  rescols->close();

  std::shared_ptr<Dataset> ds(new Dataset(name));
  ds->columns_     = columns;
  std::shared_ptr<Table>  table(new Table(ds));

/* GET FK */

  std::shared_ptr<DatabaseMetadata>     metafk;
  try
  {
     metafk = connection->getMetadata();
  }
  catch(const SQLException& ex)
  {
     throw ex;
  }

  std::shared_ptr<Resultset> resfk;
  try
  {
     resfk  = metafk->getExportedKeys("%","%",name);
  }
  catch(const SQLException& ex)
  {
     throw ex;
  }

  std::shared_ptr<ResultsetMetadata> resmeta;
  try
  {
     resmeta = resfk->getMetadata();
  }
  catch(const SQLException& ex)
  {
     resfk->close();
     throw ex;
  }

  std::string current_pk_table="";
  std::string current_fkname_="";
  std::map<int,std::tuple<std::string,std::string>>     columnsref;
  while(resfk->next())
  {
     std::string pktable   = resfk->getString("pktablename_");
     std::string fkname    = resfk->getString("fkname_");
     std::string fkcolname = resfk->getString("fkcolumnname_");
     std::string pkcolname = resfk->getString("pkcolumnname_");
     int    colindex= stoi(resfk->getString("key_seq"));

     for(auto it = columns.begin();it != columns.end();it++)
     {
        if((it->second).name() == fkcolname)
        {
           if(current_pk_table == "")
           {
              current_pk_table = pktable;
              current_fkname_  = fkname;
              std::tuple<std::string,std::string> t = std::make_tuple(fkcolname,pkcolname);
              columnsref.insert({colindex,t});
           }
           else
           {
              if(current_pk_table != pktable)
              {
                 ForeignKey fk;
                 fk.fktable_    = name;
                 fk.pktable_    = current_pk_table;
                 fk.name_       = current_fkname_;
                 fk.columnsref_ = columnsref;
                 table->addForeignKey(fk);
                 columnsref.clear();
                 current_pk_table = pktable;
                 current_fkname_  = fkname;
              }
              columnsref.insert({colindex,std::make_tuple(fkcolname,pkcolname)});
           }
        }
     }
  }

  if(current_pk_table != "")
  {
     ForeignKey fk;
     fk.fktable_    = name;
     fk.pktable_    = current_pk_table;
     fk.name_       = current_fkname_;
     fk.columnsref_ = columnsref;
     table->addForeignKey(fk);
  }
  resfk->close();

/* GET PK */
  std::shared_ptr<DatabaseMetadata>  metapk;
  try
  {
    metapk = connection->getMetadata();
  }
  catch(const SQLException& ex)
  {
     throw ex;
  }

  std::shared_ptr<Resultset> respk;
  try
  {
     respk = metapk->getPrimaryKeys("%","%",name);
  }
  catch(const SQLException& ex)
  {
     throw ex;
  }

  std::shared_ptr<ResultsetMetadata> resmetapk;
  try
  {
     resmetapk = respk->getMetadata();
  }
  catch(const SQLException& ex)
  {
     respk->close();
     throw ex;
  }

  std::map<int,std::string> pkcols;
  std::string pkname;
  while(respk->next())
  {
     pkname          = respk->getString     ("PK_NAME");
     std::string  colname = respk->getString     ("COLUMN_NAME");
     int index       = stoi(respk->getString("KEY_SEQ"));
     pkcols.insert({index,colname});
  }
  PrimaryKey pk;
  pk.name_      = pkname;
  pk.tablename_ = name;
  pk.columns_   = pkcols;
  table->setPrimaryKey(pk);
  respk->close();
  table->setSchema(connection->schema());
  return table;
}




};/*namespace cppsqlx*/
