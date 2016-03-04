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

#ifndef __DATABASEMETADATA_HPP__
#define __DATABASEMETADATA_HPP__
#include <cppsqlxincludes.hpp>
#include <dbprovider.hpp>

namespace cppsqlx
{

class Connection;
class Resultset;
/* Database Metadata
 *
 * DatabaseMetadata is for manipulating database metadata
 */
class DatabaseMetadata
{
   private:
   friend class Connection;
   /* Constructor
    * 
    * @henv SQLENV handler see ODBC API handlers
    * @hdbc SQLHDBC handler see ODBC API handlers
    */
   DatabaseMetadata(SQLHENV henv,SQLHDBC hdbc);
     
   public:
   /* Destructor */
   ~DatabaseMetadata();

   private:
   SQLHENV         henv_;
   SQLHDBC         hdbc_;
   SQLHSTMT        hstmt_;
   DBPROVIDER      provider_;

   public:

   /* catalogs
    * 
    * @catalog Database catalog
    * @return std::shared_ptr<Resultset> Shared pointer to Resultset
    **/
   std::shared_ptr<Resultset> catalogs();


   /* schemas
    * 
    * @catalog Database catalog
    * @return std::shared_ptr<Resultset> Shared pointer to Resultset
    **/
   std::shared_ptr<Resultset>   schemas();


   /* getSchemas
    *
    * @return std::list<std::string> list of schemas
    **/
   std::list<std::string>       getSchemas();


   /* getTables
    *
    * @catalog Database catalog
    * @schema Database schema
    * @table Database table
    * @tabletype Database table type
    * @return std::shared_ptr<Resultset> Shared pointer to Resultset
    */
   std::shared_ptr<Resultset>           getTables(std::string catalog,std::string schema,std::string table,std::string tabletype);  


   /* getColumns
    *
    * @catalog Database catalog
    * @schema Database schema
    * @table Database table
    * @return std::shared_ptr<Resultset> Shared pointer to Resultset
    */
   std::shared_ptr<Resultset>           getColumns(std::string catalog,std::string schema,std::string table);

   /* getPrimaryKeys
    *
    * @catalog Database catalog
    * @schema Database schema
    * @table Database table
    * @return std::shared_ptr<Resultset> Shared pointer to Resultset
    */
   std::shared_ptr<Resultset>           getPrimaryKeys(std::string catalog,std::string schema,std::string table);

   /* getImportedKeys
    *
    * @catalog Database catalog
    * @schema Database schema
    * @table Database table
    * @return std::shared_ptr<Resultset> Shared pointer to Resultset
    */
   std::shared_ptr<Resultset>           getImportedKeys(std::string catalog,std::string schema,std::string table);

   /* getExportedKeys
    * 
    * @catalog Database catalog
    * @schema Database schema
    * @table Database table
    * @return std::shared_ptr<Resultset> Shared pointer to Resultset
    */
   std::shared_ptr<Resultset>           getExportedKeys(std::string catalog,std::string schema,std::string table);


   /* getStatistics
    *
    * @catalog Database catalog
    * @schema Database schema
    * @table Database table
    * @return std::shared_ptr<Resultset> Shared pointer to Resultset
    */
   std::shared_ptr<Resultset>           getStatistics(std::string catalog,std::string schema,std::string table);



};/*DatabaseMetadata*/

};/*namespace cppsqlx*/

#endif //__DATABASEMETADATA_HPP__
