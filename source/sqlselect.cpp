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
#include <sqlselect.hpp>
#include <logger.hpp>

namespace cppsqlx
{

SQLSelect::~SQLSelect()
{
  LOG_DEBUG("SQLSelect::~SQLSelect");
}

SQLSelect::SQLSelect(bool doublequoted):doublequoted_(doublequoted),limit_(false),limitvalue_(0)
{
   LOG_DEBUG("SQLSelect::SQLSelect");
}

SQLSelect::SQLSelect(SQLSelect& q)
{
   LOG_DEBUG("SQLSelect::SQLSelect");
   *this = q;
}
   
SQLSelect::SQLSelect(SQLSelectionSet sqset,bool doublequoted):doublequoted_(doublequoted),limit_(false),limitvalue_(0)
{
   LOG_DEBUG("SQLSelect::SQLSelect");
   selection_ = sqset;
} 


SQLSelect::SQLSelect(SQLExpression ex,bool doublequoted):doublequoted_(doublequoted),limit_(false),limitvalue_(0)
{
    LOG_DEBUG("SQLSelect::SQLSelect");
    selection_.push_back(ex);
}
 
std::string  SQLSelect::toString()
{
   std::string query = "SELECT " + selection_.expression();
   if(from_.size() > 0)
     query  += "\nFROM ";
   int i = 0;
   for( auto ds : from_)
   {
      std::shared_ptr<Dataset> dataset     = std::dynamic_pointer_cast<Dataset>(std::get<1>(ds));
      std::shared_ptr<SQLSelect> sqlselect = std::dynamic_pointer_cast<SQLSelect>(std::get<1>(ds));
      if(dataset)
      {
         if(doublequoted_)
         {
            if(sqldialect_ == DBPROVIDER::DRILL)
              query += dataset->schema() + "." + (std::get<1>(ds))->joinidentifier() + " " + std::get<0>(ds) + " ";
            else
              query += "\"" + dataset->schema() + "\".\"" + (std::get<1>(ds))->joinidentifier() + "\" " + std::get<0>(ds) + " ";
         }
         else
         {
            query += dataset->schema() + "." + (std::get<1>(ds))->joinidentifier() + " " + std::get<0>(ds) + " ";
         }
      }
      else
      {
         query += sqlselect->joinidentifier() ;
      }
      if(i < from_.size() - 1)
      query += " ,\n";
      i++;
   }
   for( auto j : joins_ )
   {
      std::shared_ptr<Dataset> dataset     = std::dynamic_pointer_cast<Dataset>(std::get<2>(j));
      std::shared_ptr<SQLSelect> sqlselect = std::dynamic_pointer_cast<SQLSelect>(std::get<2>(j));
      if(doublequoted_)
      {
          if(sqldialect_ == DBPROVIDER::DRILL)
          {
             query += "\n" + std::get<5>(j) + " " + dataset->schema() + "." + (std::get<2>(j))->joinidentifier() + " " + std::get<3>(j) +  " ON (" + std::get<4>(j).expression() + ") " ;
          }
          else
          {
             query += "\n" + std::get<5>(j) + " \"" + dataset->schema() + "\".\"" + (std::get<2>(j))->joinidentifier() + "\" " + std::get<3>(j) +  " ON (" + std::get<4>(j).expression() + ") " ;
          }
      }
      else
      {
          query += "\n" + std::get<5>(j) + " " + dataset->schema() + "." + (std::get<2>(j))->joinidentifier() + " " + std::get<3>(j) +  " ON (" + std::get<4>(j).expression() + ") " ;
      }
   }

   if( wherexpr_ != SQLExpression() )
   {
      query += "\nWHERE " + wherexpr_.expression();
      if(limit_ && sqldialect_ == DBPROVIDER::ORACLE)
      {
          query += "\nAND ROWNUM <= " + std::to_string(limitvalue_);
      }
   }
   else
   {
      if(limit_ && sqldialect_ == DBPROVIDER::ORACLE)
      {
         query += "\nWHERE ROWNUM <= " + std::to_string(limitvalue_);
      }
   }


   if( groupby_.size() > 0)
   {
      query += "\nGROUP BY " + groupby_.expression();
   }


   if( orderby_.expression() != "")
   {
      query += "\nORDER BY " + orderby_.expression();
   }

   if(limit_ && sqldialect_ != DBPROVIDER::ORACLE)
   {
     query += "\nLIMIT " + std::to_string(limitvalue_);
   }
   return query;
}


std::string  SQLSelect::joinidentifier()
{  
   return std::string("(") + toString() + std::string(")") ;
}


SQLSelect&  SQLSelect::from(std::shared_ptr<SQLJoinable> ds,std::string alias)
{
   from_.push_back( make_tuple(alias,ds ));
   joinables_.push_back( make_tuple(alias,ds ));
   return *this;
}


SQLSelect&  SQLSelect::from(Dataset ds)
{
   std::shared_ptr<Dataset> d(new Dataset(ds));
   from_.push_back( make_tuple(ds.alias(),d ));
   joinables_.push_back( make_tuple(ds.alias(),d ));
   return *this;
}



SQLSelect&  SQLSelect::limit(int limitvalue)
{
   limit_ = true;
   limitvalue_ = limitvalue;
   return *this;
}

SQLSelect&  SQLSelect::join(Dataset lds,std::string las,Dataset  rds,std::string ras,SQLJoinExpression expression)
{
    std::shared_ptr<Dataset> lshds(new Dataset(lds));
    std::shared_ptr<Dataset> rshds(new Dataset(rds));
    return join(lshds,las,rshds,ras,expression);
}

SQLSelect&  SQLSelect::join(std::shared_ptr<SQLJoinable> lds,std::string las,std::shared_ptr<SQLJoinable> rds,std::string ras,SQLJoinExpression expression)
{
   std::string type("JOIN");
   joins_.push_back(make_tuple(lds,las,rds,ras,expression,type));
   joinables_.push_back( make_tuple(ras,rds ));
   return *this;
}


SQLSelect&   SQLSelect::leftJoin(std::shared_ptr<SQLJoinable> lds,std::string las,std::shared_ptr<SQLJoinable> rds,std::string ras,SQLJoinExpression expression)
{
   std::string type("LEFT OUTER JOIN");
   joins_.push_back(make_tuple(lds,las,rds,ras,expression,type));
   joinables_.push_back( make_tuple(ras,rds ));
   return *this;
}


SQLSelect&   SQLSelect::rightJoin(std::shared_ptr<SQLJoinable> lds,std::string las,std::shared_ptr<SQLJoinable> rds,std::string ras,SQLJoinExpression expression)
{
   std::string type("RIGHT OUTER JOIN");
   joins_.push_back(make_tuple(lds,las,rds,ras,expression,type));
   joinables_.push_back( make_tuple(ras,rds ));
   return *this;
}


SQLSelect&   SQLSelect::fullJoin(std::shared_ptr<SQLJoinable> lds,std::string las,std::shared_ptr<SQLJoinable> rds,std::string ras,SQLJoinExpression expression)
{
   std::string type("FULL OUTER JOIN");
   joins_.push_back(make_tuple(lds,las,rds,ras,expression,type));
   joinables_.push_back( make_tuple(ras,rds ));
   return *this;
}


std::vector<std::tuple<std::shared_ptr<SQLJoinable>,std::string,std::shared_ptr<SQLJoinable>,std::string,SQLJoinExpression,std::string>> SQLSelect::getJoins()
{
  return joins_;
}

std::vector<std::tuple<std::string,std::shared_ptr<SQLJoinable>>> SQLSelect::getDatasets()
{
  return from_;
}

SQLSelectionSet SQLSelect::getOrderBy()
{
  return orderby_;
}

SQLSelectionSet SQLSelect::getGroupBy()
{
  return groupby_;
}

SQLSelectionSet SQLSelect::getSelection()
{
  return selection_;
}

bool SQLSelect::doubleQuoted()
{
  return doublequoted_;
}

};/*namespace cppsqlx*/
