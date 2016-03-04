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
#include <resultset.hpp>
#include <statement.hpp>
#include <databasemetadata.hpp>
#include <resultsetmetadata.hpp>
#include <resultsetiterator.hpp>
#include <logger.hpp>
#include <sqlexception.hpp>
#include <odbcerror.hpp>

namespace cppsqlx
{

Resultset::Resultset(SQLHENV henv,SQLHDBC hdbc,SQLHSTMT hstmt):henv_(henv),hdbc_(hdbc),hstmt_(hstmt)
{
    types_.insert({SQL_CHAR , "CHAR"});
    types_.insert({SQL_VARCHAR,"VARCHAR"});
    types_.insert({SQL_LONGVARCHAR,"LONG VARCHAR"});
    types_.insert({SQL_DECIMAL,"DECIMAL"});
    types_.insert({SQL_NUMERIC,"NUMERIC"});
    types_.insert({SQL_SMALLINT,"SMALLINT"});
    types_.insert({SQL_INTEGER,"INTEGER"});
    types_.insert({SQL_REAL,"REAL"});
    types_.insert({SQL_FLOAT,"FLOAT"});
    types_.insert({SQL_DOUBLE,"DOUBLE"});
    types_.insert({SQL_BIT,"BIT"});
    types_.insert({SQL_TINYINT,"TINYINT"});
    types_.insert({SQL_BIGINT,"BIGINT"});
    types_.insert({SQL_BINARY,"BINARY"});
    types_.insert({SQL_VARBINARY,"VARBINARY"});
    types_.insert({SQL_LONGVARBINARY,"LONG VARBINARY"});
    types_.insert({SQL_TYPE_DATE,"DATE"});
    types_.insert({SQL_TYPE_TIME,"TIME"});
    types_.insert({SQL_TYPE_TIMESTAMP,"TIMESTAMP"});
    types_.insert({SQL_INTERVAL_MONTH,"INTERVAL MONTH"});
    types_.insert({SQL_INTERVAL_YEAR,"INTERVAL YEAR"});
    types_.insert({SQL_INTERVAL_YEAR_TO_MONTH,"INTERVAL YEAR TO MONTH"});
    types_.insert({SQL_INTERVAL_DAY,"INTERVAL DAY"});
    types_.insert({SQL_INTERVAL_HOUR,"INTERVAL HOUR"});
    types_.insert({SQL_INTERVAL_MINUTE,"INTERVAL MINUTE"});
    types_.insert({SQL_INTERVAL_SECOND,"INTERVAL SECOND"});
    types_.insert({SQL_INTERVAL_DAY_TO_HOUR,"INTERVAL DAY TO HOUR"});
    types_.insert({SQL_INTERVAL_DAY_TO_MINUTE,"INTERVAL DAY TO MINUTE"});
    types_.insert({SQL_INTERVAL_DAY_TO_SECOND,"INTERVAL DAY TO SECOND"});
    types_.insert({SQL_INTERVAL_HOUR_TO_MINUTE,"INTERVAL HOUR TO MINUTE"});
    types_.insert({SQL_INTERVAL_HOUR_TO_SECOND,"INTERVAL HOUR TO SECOND"});
    types_.insert({SQL_INTERVAL_MINUTE_TO_SECOND,"INTERVAL MINUTE TO SECOND"});
    types_.insert({SQL_GUID,"GUID"});

    columncount_ = getColumnCount();
    for( auto i = 0;i < columncount_;i++)
    {
        columnsqltypes_.insert({i,getColumnType(i)});
        columnprecisions_.insert({i,getPrecision(i)});
        std::string col_type_name;

        switch(getColumnType(i))
        {
           case SQL_DECIMAL:
              col_type_name = getColumnTypeName(i) + "(" + std::to_string(getPrecision(i)) + "," + std::to_string(getScale(i)) + ")";
              break;
           case SQL_NUMERIC:
              col_type_name = getColumnTypeName(i) + "(" + std::to_string(getPrecision(i)) + "," + std::to_string(getScale(i)) + ")";
              break;
           case SQL_VARCHAR:
              col_type_name = getColumnTypeName(i) + "(" + std::to_string(getPrecision(i)) + ")";
              break;
           case SQL_CHAR:
              col_type_name = getColumnTypeName(i) + "(" + std::to_string(getPrecision(i)) + ")";
              break;
           case SQL_TYPE_DATE:
              col_type_name = getColumnTypeName(i);
              break;
           case SQL_TYPE_TIME:
              col_type_name = getColumnTypeName(i);
              break;
           case SQL_TYPE_TIMESTAMP:
              col_type_name = getColumnTypeName(i);
              break;
           case SQL_VARBINARY:
              col_type_name = getColumnTypeName(i) + "(" + std::to_string(getPrecision(i)) +  ")";
              break;
           default:
              col_type_name = getColumnTypeName(i) ;
              break;              
        };

        columntypes_.insert({i,col_type_name});
        columnnames_.insert({i,getColumnName(i)});
        columnscales_.insert({i,getScale(i)});
        columnsizes_.insert({i,getColumnDisplaySize(i)});
        columnsnullable_.insert({i,isNullable(i)});

        Data data;
        if( (getColumnType(i) == SQL_NUMERIC && getScale(i) != 0) || 
            (getColumnType(i) == SQL_DECIMAL && getScale(i) != 0) || 
             getColumnType(i) == SQL_REAL                         || 
             getColumnType(i) == SQL_FLOAT                        || 
             getColumnType(i) == SQL_DOUBLE)
           data.targettype_ = SQL_C_DOUBLE;
        else
           data.targettype_ = SQL_C_CHAR;
        data.chartargetvalueptr_ = new SQLCHAR[sizeof(unsigned char)*(columnsizes_[i]+4)];
        data.bufferlength_ = columnsizes_[i]+4;
        data_.insert({i,data});
    }

    SQLRETURN retcode;
    for ( int i = 0 ; i < columncount_ ; i++ )
    {
      if( (getColumnType(i) == SQL_NUMERIC && getScale(i) != 0) || 
          (getColumnType(i) == SQL_DECIMAL && getScale(i) != 0) || 
           getColumnType(i) == SQL_REAL                         || 
           getColumnType(i) == SQL_FLOAT                        || 
           getColumnType(i) == SQL_DOUBLE)
         retcode = SQLBindCol(hstmt_, (SQLUSMALLINT)i + 1,data_[i].targettype_, &(data_[i].realtargetvalueptr_),0, &(data_[i].strlen_or_ind_));
      else
         retcode = SQLBindCol(hstmt_, (SQLUSMALLINT)i + 1,data_[i].targettype_, data_[i].chartargetvalueptr_, data_[i].bufferlength_, &(data_[i].strlen_or_ind_));

    }
    rownum_ = 0;
    cursorstate_ = ODBC_CURSOR_STATE::CURSOR_BEFORE_FIRST;

    LOG_DEBUG("Resultset::Resultset()"); 
}

Resultset::~Resultset()
{
   for(auto i = 0;i < columncount_;i++)
   {
      if(data_[i].chartargetvalueptr_ != nullptr)
      delete data_[i].chartargetvalueptr_;
   }

   LOG_DEBUG("Resultset::~Resultset()");
}

int Resultset::rowNum()
{
   return rownum_;
}


void Resultset::close()
{
   SQLCloseCursor(hstmt_);
}


int  Resultset::getColumnCount()
{
   int count;
   try
   {
      count = getColumnAttribute(0,SQL_DESC_COUNT).intresult_;
   }
   catch(const SQLException& ex)
   {
       throw ex;
   }
   return count;
}

Resultset::SQLResult const Resultset::getColumnAttribute(int index,SQLUSMALLINT fieldidentifier) const
{
   SQLResult   res;
   SQLUSMALLINT sqlindex = index;
   SQLSMALLINT  retsize;
   char outstr[256];
   SQLLEN  retid;
   SQLRETURN  retcode = SQLColAttribute ( hstmt_, (SQLUSMALLINT)sqlindex + 1,fieldidentifier,&outstr,256*sizeof(char),&retsize,&retid);
   while(retcode == SQL_STILL_EXECUTING)
   {
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
   };

   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
   {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLColAttribute", hstmt_, SQL_HANDLE_STMT));
       }
       res.intresult_    = (int)retid;
       res.stringresult_ = outstr;
       return res;
   }
   else
   {
       ODBCError err;
       throw SQLException(err("SQLColAttribute", hstmt_, SQL_HANDLE_STMT));
   }
}


std::string  const Resultset::getColumnName(int index) const
{
   std::string name;
   try
   {
      name = getColumnAttribute(index,SQL_DESC_NAME).stringresult_;
   }
   catch(const SQLException& ex)
   {
      throw ex;
   }
   return name;
}


std::string  const Resultset::getColumnTypeName(int index) const
{
   std::string type_name;
   try
   {
      type_name = getColumnAttribute(index,SQL_DESC_TYPE_NAME).stringresult_;
   }
   catch(const SQLException& ex)
   {
      throw ex;
   }
   return type_name;
}


int const  Resultset::getColumnType(int index) const
{
   int  res;
   try
   {
      res = getColumnAttribute(index,SQL_DESC_CONCISE_TYPE).intresult_;
   }
   catch(const SQLException& ex)
   {
      throw ex;
   }
   return res;
}


int const Resultset::isNullable(int index) const
{
   int res;
   try
   {
       res = getColumnAttribute(index,SQL_DESC_NULLABLE).intresult_;
   }
   catch(const SQLException& ex)
   {
       throw ex;
   }
   return res;
}


int const Resultset::getPrecision(int index) const
{
   int res;
   try
   {
      res = getColumnAttribute(index,SQL_DESC_PRECISION).intresult_;
   }
   catch(const SQLException& ex)
   {
      throw ex;
   }
   return res;
}



int const Resultset::getScale(int index) const
{
   int res;
   try
   {
      res = getColumnAttribute(index,SQL_DESC_SCALE).intresult_;
   }
   catch(const SQLException& ex)
   {
      throw ex;
   }
   return res;
}

int const Resultset::getColumnDisplaySize(int index) const
{
   int res;
   try
   {
     res = getColumnAttribute(index,SQL_DESC_DISPLAY_SIZE).intresult_;
   }
   catch(const SQLException& ex)
   {
      throw ex;
   }
   return res;
}


bool  Resultset::fetch(SQLSMALLINT orientation)
{
    bool res;
    SQLRETURN retcode = SQLFetchScroll(hstmt_, orientation, 0);
    while(retcode == SQL_STILL_EXECUTING)
    {
       std::this_thread::sleep_for(std::chrono::milliseconds(20));
    };

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
       if(retcode == SQL_SUCCESS_WITH_INFO)
       {
          ODBCError err;
          LOG_WARN(err("SQLFetchScroll", hstmt_, SQL_HANDLE_STMT)) ;
       }
       res = true;
    }
    else
    {
       std::string errortype;
       if(retcode ==  SQL_NO_DATA)
       {
          return false;
       }
       if(retcode == SQL_INVALID_HANDLE)
       {
          errortype =  "INVALID HANDLE ";
       }

       if(retcode == SQL_ERROR)
       {
          errortype = "SQL_ERROR " ;
       }
       ODBCError err;
       LOG_ERROR(errortype + ": " + err("SQLFetchScroll", hstmt_, SQL_HANDLE_STMT)) ;
       res = false;
    }
    return res;
}


bool  Resultset::first()
{
    return fetch(SQL_FETCH_FIRST);
}


bool  Resultset::last()
{
    return fetch(SQL_FETCH_LAST);
}


bool  Resultset::next()
{
    bool hasnext = fetch(SQL_FETCH_NEXT);
    hasnext ? rownum_++ : rownum_ = -1;
    hasnext ? cursorstate_ = CURSOR_VALID : cursorstate_ = CURSOR_AFTER_LAST;
    return hasnext;
}


bool Resultset::previous()
{
    return fetch(SQL_FETCH_PRIOR);
}

bool Resultset::isNull(int columnindex) const
{
   return data_[columnindex].strlen_or_ind_ == SQL_NULL_DATA ? true : false;
}


bool Resultset::isNull(std::string columnname) const
{
   for(auto i : columnnames_)
   {
      if( columnname == i.second)
      {
          return data_[i.first].strlen_or_ind_ == SQL_NULL_DATA ? true : false;
      }
   }
   return false;
}


std::string  const Resultset::getString(int columnindex) const
{
   std::string res;
  
   if( (getColumnType(columnindex) == SQL_NUMERIC && getScale(columnindex) != 0) || 
       (getColumnType(columnindex) == SQL_DECIMAL && getScale(columnindex) != 0) || 
        getColumnType(columnindex) == SQL_REAL                                   || 
        getColumnType(columnindex) == SQL_FLOAT                                  || 
        getColumnType(columnindex) == SQL_DOUBLE) 
   {
      if(data_[columnindex].strlen_or_ind_ == SQL_NULL_DATA)
      {
        res = "NULL";
      }
      else
      {
         res = std::to_string((double)data_[columnindex].realtargetvalueptr_);
         res.erase(res.find_last_not_of('0') + 1, std::string::npos);
      }
   }
   else
   {
      if(data_[columnindex].strlen_or_ind_ == SQL_NULL_DATA)
      {
         res = "NULL";
      }
      else
      {
        res = (char*) data_[columnindex].chartargetvalueptr_;
      }
      
   }
   return res;
}


std::string  Resultset::getString(std::string columnname)
{
   std::string res;
   for(auto i : columnnames_)
   {
      if( columnname == i.second)
      {
         if( getColumnType(i.first) == SQL_NUMERIC || 
             getColumnType(i.first) == SQL_DECIMAL || 
             getColumnType(i.first) == SQL_REAL    || 
             getColumnType(i.first) == SQL_FLOAT   || 
             getColumnType(i.first) == SQL_DOUBLE)
         {
            if(data_[i.first].strlen_or_ind_ == SQL_NULL_DATA)
            {
              res = "NULL";
            }
            else
            {
              res = std::to_string((double)data_[i.first].realtargetvalueptr_);
              res.erase(res.find_last_not_of('0') + 1, std::string::npos);
            }
         }
         else
         {
            if(data_[i.first].strlen_or_ind_ == SQL_NULL_DATA)
            {
              res = "NULL";
            }
            else
            {
              res = (char*) data_[i.first].chartargetvalueptr_;
            }
         }
      }
   }
   return res;
}


std::shared_ptr<ResultsetMetadata>  Resultset::getMetadata()
{
   std::shared_ptr<ResultsetMetadata> metadata(new ResultsetMetadata());
   metadata->columncount_      = columncount_;
   metadata->columnnames_      = columnnames_;
   metadata->columntypes_      = columntypes_;
   metadata->columnsqltypes_   = columnsqltypes_;
   metadata->columnprecisions_ = columnprecisions_;
   metadata->columnscales_     = columnscales_;
   metadata->columnsizes_      = columnsizes_;
   metadata->columnsnullable_  = columnsnullable_;
   return metadata;
}


Resultset& Resultset::get()
{
   return *this;
}

ResultsetIterator  Resultset::Resultset::begin()
{
    next();
    return ResultsetIterator(shared_from_this(),CURSOR_VALID,1);   
}

ResultsetIterator  Resultset::Resultset::end()
{
    return ResultsetIterator(shared_from_this(),CURSOR_AFTER_LAST,-1);
}


};/*namespace cppsqlx*/
