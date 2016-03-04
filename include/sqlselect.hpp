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

#ifndef __SQLSELECT_HPP__
#define __SQLSELECT_HPP__
#include <cppsqlxincludes.hpp>
#include <sqlquery.hpp>

namespace cppsqlx
{

class SQLSelect : public SQLQuery<SQLSelect,std::shared_ptr<Resultset>>,public filterable<SQLSelect>, public SQLJoinable
{
   public:
   SQLSelect(bool doublequoted = true);
   SQLSelect(SQLSelect& q);
   SQLSelect(SQLExpression ex,bool doublequoted = true);
   SQLSelect(SQLSelectionSet sqset ,bool doublequoted = true);
   ~SQLSelect();

   private:
   std::vector<std::tuple<std::shared_ptr<SQLJoinable>,std::string,std::shared_ptr<SQLJoinable>,std::string,SQLJoinExpression,std::string>> joins_;
   std::vector<std::tuple<std::string,std::shared_ptr<SQLJoinable>>> from_;
   std::vector<std::tuple<std::string,std::shared_ptr<SQLJoinable>>> joinables_;
   SQLSelectionSet orderby_;
   SQLSelectionSet groupby_;
   SQLSelectionSet selection_;
   bool            doublequoted_;
   bool            limit_;
   int             limitvalue_;

   public:
   bool                doubleQuoted();
   SQLSelectionSet     getOrderBy();
   SQLSelectionSet     getGroupBy();
   SQLSelectionSet     getSelection();
   SQLSelect&          from(std::shared_ptr<SQLJoinable> ds,std::string alias);
   SQLSelect&          from(Dataset ds);
   SQLSelect&          limit(int limitvalue);
   SQLSelect&            join(std::shared_ptr<SQLJoinable> lds,std::string las,std::shared_ptr<SQLJoinable> rds,std::string ras,SQLJoinExpression expression);
   SQLSelect&            join(Dataset lds,std::string las,Dataset  rds,std::string ras,SQLJoinExpression expression);
   SQLSelect&              leftJoin(std::shared_ptr<SQLJoinable> lds,std::string las,std::shared_ptr<SQLJoinable> rds,std::string ras,SQLJoinExpression expression);
   SQLSelect&                rightJoin(std::shared_ptr<SQLJoinable> lds,std::string las,std::shared_ptr<SQLJoinable> rds,std::string ras,SQLJoinExpression expression);
   SQLSelect&                    fullJoin(std::shared_ptr<SQLJoinable> lds,std::string las,std::shared_ptr<SQLJoinable> rds,std::string ras,SQLJoinExpression expression);
   virtual     std::string             toString();
   virtual     std::string                  joinidentifier();
   std::vector<std::tuple<std::string,std::shared_ptr<SQLJoinable>>> getDatasets();
   std::vector<std::tuple<std::string,std::shared_ptr<SQLJoinable>>> getFromDatasets();
   std::vector<std::tuple<std::shared_ptr<SQLJoinable>,std::string,std::shared_ptr<SQLJoinable>,std::string,SQLJoinExpression,std::string>> getJoins();
   
   
   SQLSelect& select()
   {
      return *this;
   }

   SQLSelect& select(const SQLSelectionSet& selectionset)
   {
      selection_ = selectionset;
      return *this;
   }


   template<typename ... Types>
   SQLSelect& select(SQLExpression first, Types ... rest)
   {
       int nb = sizeof...(rest);
       selection_.push_back(first);
       select(rest...);
       return *this;
   }

   template<typename ... Types>
   SQLSelect& select(std::string first, Types ... rest)
   {
       int nb = sizeof...(rest);
       selection_.push_back(SQLExpression(first));
       select(rest...);
       return *this;
   }


   template<typename ... Types>
   SQLSelect& select(int first, Types ... rest)
   {
       int nb = sizeof...(rest);
       selection_.push_back(SQLExpression(first));
       select(rest...);
       return *this;
   }


   SQLSelect& groupBy(const SQLSelectionSet& selectionset)
   {
      groupby_ = selectionset;  
      return *this;
   }

   SQLSelect& groupBy()
   {
       return *this;
   }

   template<typename ... Types>
   SQLSelect& groupBy(SQLExpression first, Types ... rest)
   {                  
       int nb = sizeof...(rest);
       groupby_.push_back(first);
       groupBy(rest...);
       return *this;  
   }


   template<typename ... Types>
   SQLSelect& groupBy(std::string first, Types ... rest)
   {
       int nb = sizeof...(rest);
       groupby_.push_back(SQLExpression(first));
       groupBy(rest...);
       return *this;
   }


   SQLSelect& orderBy(const SQLSelectionSet& selectionset)
   {
      orderby_ = selectionset;  
      return *this;
   }
   

   SQLSelect& orderBy()
   {
      return *this;
   }

   template<typename ... Types>
   SQLSelect& orderBy(SQLExpression first, Types ... rest)
   {
       int nb = sizeof...(rest);
       orderby_.push_back(first);
       orderBy(rest...);
       return *this;
   }

   template<typename ... Types>
   SQLSelect& orderBy(std::string first, Types ... rest)
   {
       int nb = sizeof...(rest);
       orderby_.push_back(SQLExpression(first));
       orderBy(rest...);
       return *this;
   }


};/*SQLSelect*/

};/*namespace cppsqlx*/

#endif //__SQLSELECT_HPP__
