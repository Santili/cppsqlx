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

#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__
#include <cppsqlxincludes.hpp>
#include <dbprovider.hpp>

namespace cppsqlx
{

class Statement;
class Database;
class DatabaseMetadata;
/* Connection Class
 *
 * Connection Holds a connection to a Database object 
 * It is a pre-requisite to retreive any information from a database
 * Via Statements or DatabaseMetadata 
 */                                                                  
class Connection
{
  private:
  friend class Database;
  /* Connection
   * @user The user account to the database
   * @password The user password
   * @henv SQLHENV handler
   * @hdbc SQLHDBC handler
   *
   * It can't be instantiated directly
   * but an instance is get via getConnection method of Database class
   * which is friend of Connection class
   */
  Connection(std::string user,std::string password,SQLHENV henv,SQLHDBC hdbc);

  public:
 ~Connection();


  private:
  std::string   user_;
  std::string   password_;
  std::string   schema_;
  SQLHENV       henv_;
  SQLHDBC       hdbc_; 
  bool          autocommit_;
  DBPROVIDER    provider_;

  public:

  DBPROVIDER provider();
  void   setProvider(DBPROVIDER provider);
  /* Get schema
   *
   * @return schema
   */
  std::string schema();

  /* Set schema
   *
   * @schema the schema name
   */
  void setSchema(std::string schema);

  /* Create a statement
   *
   * @return Statement instance
   */
  std::shared_ptr<Statement> createStatement();

  /* Get Metadata
   * 
   * @return Instance of DatabaseMetadata
   */
  std::shared_ptr<DatabaseMetadata>   getMetadata(); 

  /* Set Auto commit mode
   *
   * @autocommit The auto commit mode
   */
  void setAutoCommit(bool autocommit);

  /* Commit transaction
   *
   * Makes sense only in auto commit mode false
   */
  void commit();

  /* Rollback the current transaction
   *
   * Makes sense only in auto commit mode false
   */
  void roolback();
};/*Connection*/

};/*namespace cppsqlx*/

#endif //__CONNECTION_HPP__
