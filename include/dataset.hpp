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

#ifndef __DATASET_HPP__
#define __DATASET_HPP__
#include <cppsqlxincludes.hpp>
#include <dbprovider.hpp>
#include <column.hpp>
#include <sqljoinable.hpp>

namespace cppsqlx
{

class DatasetFactory;
class Table;
class Dataset: public SQLJoinable
{
   private:
   friend class DatasetFactory;
   friend class Table;
   Dataset(std::string name);

   private:
   std::string          xml_;
   std::string          name_;
   std::string          schema_;
   std::string          catalog_;
   std::string          alias_;
   std::map<int,Column> columns_;
   DBPROVIDER           provider_;

   public:
   virtual ~Dataset();
   std::string          name();
   std::string          schema();
   std::string          catalog();
   std::string          alias();
   DBPROVIDER           provider();
   void                 setSchema(std::string schema);
   void                 setCatalog(std::string catalog);
   Dataset&             as(std::string alias);
   void                 setProvider(DBPROVIDER);
   Column               at(int index);
   int                  rowSize();
   virtual std::string  joinidentifier();

};/*Dataset*/

};/*namespace cppsqlx*/

#endif //__DATASET_HPP__
