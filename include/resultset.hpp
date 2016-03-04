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

#ifndef __RESULTSET_HPP__
#define __RESULTSET_HPP__
#include <cppsqlxincludes.hpp>
#include <globaldefinitions.hpp>

namespace cppsqlx
{

class ResultsetMetadata;
class Statement;
class DatabaseMetadata;
class ResultsetIterator;
/* Resultset
 *
 * Resultset class holds the resltset result of a query statement
 */
class Resultset : public std::enable_shared_from_this<Resultset>
{
   private:
   friend class Statement;
   friend class DatabaseMetadata;

   /* Constructor
    *
    * @henv SQLENV handle
    * @hdbc SQLHDBC handle
    * @hstmt SQLHSTMT handle
    */
   Resultset(SQLHENV henv,SQLHDBC hdbc,SQLHSTMT hstmt);

   /* Data
    *
    * Data structure that holds a Data information
    * It's type, It's length ...
    */
   struct Data
   {
      SQLSMALLINT   targettype_;
      SQLCHAR*      chartargetvalueptr_;
      SQLDOUBLE     realtargetvalueptr_;
      SQLINTEGER    bufferlength_;
      SQLLEN        strlen_or_ind_;
   };

   struct SQLResult
   {
      std::string   stringresult_;
      int           intresult_;
   };

   public:
   ~Resultset();

   private:
   SQLHENV                        henv_;
   SQLHDBC                        hdbc_;
   SQLHSTMT                       hstmt_;
   mutable std::map<int,std::string> types_;
   int                            columncount_;
   std::map<int,std::string>      columnnames_;
   std::map<int,std::string>      columntypes_;
   std::map<int,int>              columnsqltypes_;
   std::map<int,int>              columnprecisions_;
   std::map<int,int>              columnscales_;
   std::map<int,int>              columnsizes_;
   std::map<int,int>              columnsnullable_;
   mutable std::map<int,Data>     data_;
   ODBC_CURSOR_STATE              cursorstate_;
   int                            rownum_;

   public:

   /* rowNum
    *
    * Retreive the rownum_
    * @return int
    */
   int                            rowNum();

   /* next 
    *
    * Move to Next row in the result set
    * @return bool
    */
   bool                           next();

   /* previous
    *
    * Move to the previous row in the resultset
    * @return bool
    */
   bool                           previous();

   /* last
    *
    * Move to the last row in the resultset
    * @return bool
    */
   bool                           last();

   /* first
    *
    * Move to the first row in the resultset
    * @return bool
    */
   bool                           first();


   bool                           isNull(int columnindex) const;
   bool                           isNull(std::string columnname) const;

   /* getString
    *
    * @columnindex
    * Retrieve a std::string representation of the data at index columnindex
    * 
    * @return std::string representation of the data at index columnindex
    */
   std::string const getString(int columnindex) const;

   /* getString
    *
    * @columnname
    * Retrieve a std::string representation of the data contained in the column columnname
    */
   std::string   getString(std::string columnname);

   /* getMetadata
    * 
    * @return Instance of ResultsetMetadata
    */
   std::shared_ptr<ResultsetMetadata>  getMetadata();

   /* close
    * 
    * Close the resulset
    * After a call of this method the Resultset is no longer usable
    */
   void                           close();
   
   Resultset& get();
   ResultsetIterator              begin();
   ResultsetIterator              end();
   ODBC_CURSOR_STATE              cursorState(){ return cursorstate_;}

   private:

   /* getColumnCount
    *
    * @return int The number of columns contained in the resultset
    */
   int  getColumnCount();

   /* getColumnName
    *
    * @index The index of the column
    * @return std::string that holds the column's name
    */
   std::string  const  getColumnName(int index) const;

   /* getColumnTypeName
    *
    * @index The column's index
    * @return std::string The column's typename
    */
   std::string const  getColumnTypeName(int index) const;
 

   /* getColumnType
    *
    * @index The column's index
    * @return int The column's type
    */
   int const  getColumnType(int index) const;


   /* getPrecision
    * 
    * @index The column's index
    * @return int the precision of a numeric type
    */
   int const getPrecision(int index) const;


   /* getScale
    *
    * @index The column's index
    * @return int
    */
   int const getScale(int index) const;

   /* isNullable
    *
    * @index The column's index
    * @return int 0 if column is nullable 1 if not
    */
   int const isNullable(int index) const;

   /* getColumnDisplaySize
    * 
    * @index int The column's index
    * @return int
    */
   int const getColumnDisplaySize(int index) const;

   /* getColumnAttribute
    * 
    * @index int The column's index
    * @fieldidentifier SQLUSMALLINT The field identifier
    */
   SQLResult const getColumnAttribute(int index,SQLUSMALLINT fieldidentifier) const;

   /* fetch
    *
    * @orientation  SQLSMALLINT
    * @return bool
    */
   bool fetch(SQLSMALLINT orientation);

};/*Resultset*/

};/*namespace cppsqlx*/

#endif //__RESULTSET_HPP__
