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
#include <table.hpp>
#include <dataset.hpp>

namespace cppsqlx
{

Table::Table(std::shared_ptr<Dataset> ds):Dataset(ds->name())
{
   name_    = ds->name();
   for(int i = 1;i < ds->rowSize();i++)
   {
       columns_.insert( {i,ds->at(i)});
   }
}

PrimaryKey  Table::primaryKey()
{
   return pk_;
}

std::vector<ForeignKey>  Table::foreignKeys()
{
   return fks_;
}


std::vector<UniqueKey> Table::uniqueKeys()
{
   return uks_;
}

void  Table::setPrimaryKey(PrimaryKey pk)
{
   pk_ = pk;
}


void  Table::addForeignKey(ForeignKey fk)
{
   fks_.push_back(fk);
}


void  Table::addUniquekey(UniqueKey uk)
{
   uks_.push_back(uk);
}

};/*namespace cppsqlx*/
