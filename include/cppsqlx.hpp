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
#ifndef __CPPSQLX_HPP__
#define __CPPSQLX_HPP__
#include <sqljoinable.hpp>
#include <column.hpp>
#include <connection.hpp>
#include <cppsqlx.hpp>
#include <cppsqlxincludes.hpp>
#include <cppsqlxroot.hpp>
#include <database.hpp>
#include <databasemetadata.hpp>
#include <dataset.hpp>
#include <dbprovider.hpp>
#include <drivermanager.hpp>
#include <foreignkey.hpp>
#include <globaldefinitions.hpp>
#include <logger.hpp>
#include <odbcerror.hpp>
#include <primarykey.hpp>
#include <resultset.hpp>
#include <resultsetiterator.hpp>
#include <resultsetmetadata.hpp>
#include <sqlexception.hpp>
#include <statement.hpp>
#include <uniquekey.hpp>
#include <table.hpp>
#include <datasetfactory.hpp>
#include <sqlexpression.hpp>
#include <helperfunctions.hpp>
#include <sqljoinexpression.hpp>
#include <sqlselectionset.hpp>
#include <sqlquery.hpp>
#include <sqlselect.hpp>
#include <sqldml.hpp>
#include <sqlinsert.hpp>
#include <sqlupdate.hpp>
#include <sqldelete.hpp>
#include <sqlcopy.hpp>
#include <sqlcreatetable.hpp>
#include <sqlcreateview.hpp>
#include <sqlcreateexternaltable.hpp>
#include <loadprotocols.hpp>
#include <sqldrop.hpp>
#include <sqltruncate.hpp>
#include <sqlddl.hpp>

namespace cppsqlx
{

#define DIZ_DISPLAY_SIZE  30

std::wostream& operator<<(std::wostream& os, const std::shared_ptr<Resultset> res)
{
   std::shared_ptr<ResultsetMetadata> resmeta         = res->getMetadata();

   auto counter = 0;
   auto j =0;
   auto sum = 0;
   os.setf(std::ios_base::uppercase);

   for(auto i = 0; i < resmeta->getColumnCount() ; i++)
   {
      
      os.setf(std::ios_base::uppercase);
      if(resmeta->getColumnDisplaySize(i) > DIZ_DISPLAY_SIZE || resmeta->getColumnName(i).size() > DIZ_DISPLAY_SIZE)
        os.width(DIZ_DISPLAY_SIZE);
      else
        os.width(resmeta->getColumnDisplaySize(i) > resmeta->getColumnName(i).size() ? resmeta->getColumnDisplaySize(i) : resmeta->getColumnName(i).size());
      std::wstringstream cls;
      std::string disp = truncate(resmeta->getColumnName(i),DIZ_DISPLAY_SIZE);
      cls << disp.c_str() ;
      std::wstring var = cls.str();
      os << var;  
      if(i != resmeta->getColumnCount() - 1)
          os << " " ;
   }
   os << "\n";

   while(res->next())
   {
     std::string  output = "";
     for(auto i = 0;i < resmeta->getColumnCount() ; i++)
     {
        os.setf(std::ios_base::uppercase);
        if(resmeta->getColumnDisplaySize(i) > DIZ_DISPLAY_SIZE || resmeta->getColumnName(i).size() > DIZ_DISPLAY_SIZE)
           os.width(DIZ_DISPLAY_SIZE);
         else
           os.width(resmeta->getColumnDisplaySize(i) > resmeta->getColumnName(i).size() ? resmeta->getColumnDisplaySize(i) : resmeta->getColumnName(i).size());
        std::wstringstream cls;
        std::string disp = truncate(res->getString(i),DIZ_DISPLAY_SIZE).c_str();
        cls << disp.c_str();
       // cls << res->getString(i).substr(0,DIZ_DISPLAY_SIZE).c_str() ;
        std::wstring var = cls.str();
        os << var;
        if(i != resmeta->getColumnCount() - 1)
          os << "|" ;
     }
     os << "\n";
     counter ++;
     j++;
     sum++;
     if( counter > 1000)
     {
       os.flush();
       counter = 0;
     }
     if( j > 1000000)
     {
        std::cout << sum << " lines read" << std::endl;
        j = 0;
     }
  }
  os << "(" << sum << " rows)\n";
  os.flush();
  return os;
}

SQLExpression& SQLSum(SQLExpression& exp){ return exp.sum();};
SQLExpression& SQLSum(std::string s){ return SQLExpression(s).sum();};
SQLExpression& SQLCount(SQLExpression exp){ return exp.count();};
SQLExpression  SQLCount(const std::string exp){ SQLExpression e(exp); return e.count();};
SQLExpression& SQLRound(SQLExpression& exp){ return exp.round();};
SQLExpression& SQLNvl(SQLExpression& exp,int val){ return exp.nvl(val);};

typedef SQLExpression sql;
typedef SQLExpression sqx;
SQLExpression operator "" _sql(const char * c, std::size_t)
{
   return SQLExpression(c);
}

typedef SQLJoinExpression sqjnx;
#define SELECT(...) SQLDML().sqlSelect().select(__VA_ARGS__)
#define FROM(X) .from(X)
#define LIMIT(X) .limit(X)
#define EXEC(X) .run(X)
#define WHERE(X) .where(X)
#define DIALECT(X) .dialect(X)
#define GROUPBY(...) .groupBy(__VA_ARGS__)
#define ORDERBY(...) .orderBy(__VA_ARGS__)

#define INNER_JOIN(U,V,X,Y,Z) .join(U,V,X,Y,Z)
#define LEFT_OUTER_JOIN(U,V,X,Y,Z) .leftJoin(U,V,X,Y,Z)
#define RIGHT_OUTER_JOIN(U,V,X,Y,Z) .rightJoin(U,V,X,Y,Z)
#define FULL_OUTER_JOIN(U,V,X,Y,Z) .fullJoin(U,V,X,Y,Z)

#define SUM(X) SQLSum(X)
#define COUNT(X) SQLCount(X)
#define NVL(X,Y) SQLNvl(X,Y)
#define ROUND(X) SQLRound(X)
#define AS(X) .as(X)
#define AND(X) .opAND(X)
#define LIKE(X) .like(X)
#define DESC .descending()
#define ASC  .ascending()

};

#endif //__CPPSQLX_HPP__
