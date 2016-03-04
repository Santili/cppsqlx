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

#ifndef __SQLQUERY_HPP__
#define __SQLQUERY_HPP__
#include <cppsqlxincludes.hpp>
#include <sqlexpression.hpp>
#include <resultset.hpp>
#include <connection.hpp>
#include <statement.hpp>
#include <sqlexception.hpp>
#include <sqljoinable.hpp>
#include <sqlselectionset.hpp>
#include <sqljoinexpression.hpp>
#include <dataset.hpp>

namespace cppsqlx
{

template <typename T>
class filterable
{  
   protected:                
   SQLExpression wherexpr_;
   public:
   operator T&() { return static_cast<T&>(*this);}
   operator T const&() const { return static_cast<const T&>(*this); }
     
   T& where(const SQLExpression& expr)
   {   
       wherexpr_ = expr;
       return static_cast<T&>(*this);
   }

   T& where(const std::string& expr)
   {
       wherexpr_ = SQLExpression(expr);
       return static_cast<T&>(*this);
   }

};
 
 
template<typename QueryType,typename ReturnType> 
class SQLQuery
{
   protected:
   DBPROVIDER sqldialect_;
   public:
   SQLQuery(){};
   public:
   virtual std::string  toString() = 0;
   virtual ReturnType run(std::shared_ptr<Connection> connection) = 0;
   virtual QueryType& dialect(DBPROVIDER provider);
};

template<typename QueryType>
class SQLQuery<QueryType,void>
{
   protected:
   DBPROVIDER   sqldialect_;
   public:
   SQLQuery(){};
   public:
   virtual std::string  toString() = 0;
   virtual void run(std::shared_ptr<Connection> connection)
   {
      std::shared_ptr<Statement>  stmt  = connection->createStatement();
      try
      {
         stmt->execute(toString());
      }
      catch(const SQLException&  ex)
      {
         throw ex;
      }
   }


   virtual QueryType& dialect(DBPROVIDER provider)
   {  
      sqldialect_ = provider;
      return static_cast<QueryType&>(*this);
   }

}; 

template<typename QueryType>
class SQLQuery<QueryType,int>
{
   protected:
   DBPROVIDER   sqldialect_;

   public:
   SQLQuery(){};
   public:
   virtual std::string  toString() = 0;
   virtual int run(std::shared_ptr<Connection> connection)
   {
      std::shared_ptr<Statement>  stmt  = connection->createStatement();
      return stmt->executeUpdate(toString());
   }

   virtual QueryType& dialect(DBPROVIDER provider)
   {  
      sqldialect_ = provider;
      return static_cast<QueryType&>(*this);
   }
};


template<typename QueryType>
class SQLQuery<QueryType,std::shared_ptr<Resultset>>
{
   protected:
   DBPROVIDER  sqldialect_;

   public:
   SQLQuery(){};
   virtual ~SQLQuery(){};
   public:
   virtual std::string  toString() = 0;
   std::shared_ptr<Statement>  stmt;
   std::shared_ptr<Resultset> res;
   virtual std::shared_ptr<Resultset> run(std::shared_ptr<Connection> connection)
   {
      try
      {
         stmt = connection->createStatement();
         res = stmt->executeQuery(toString());  
      }
      catch(const SQLException& ex)
      {
         throw ex;
      }
      return res;
   }

   virtual QueryType& dialect(DBPROVIDER provider)
   {  
      sqldialect_ = provider;
      return static_cast<QueryType&>(*this);
   }
};


template <typename T>
class DDLQuery : public SQLQuery<T,void>
{
   protected:
   std::string        _sqlcmdtype;
   std::string        _objectname;
   std::string        _objecttype;

   public:
   operator T&() { return static_cast<T&>(*this);}
   operator T const&() const { return static_cast<const T&>(*this); };
   virtual std::string  toString() = 0;
};


template <typename T>
class DTLQuery : public SQLQuery<T,int>
{
   protected:
   std::string tablename_;

   public:
   virtual std::string toString() = 0;
};


};/*namespace cppsqlx*/

#endif //__SQLQUERY_HPP__
