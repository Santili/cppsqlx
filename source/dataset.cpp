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
#include <dataset.hpp>
#include <table.hpp>
#include <logger.hpp>

namespace cppsqlx
{

Dataset::Dataset(std::string name):name_(name),alias_(name)
{
   LOG_DEBUG("Dataset::Dataset"); 
}

Dataset::~Dataset()
{
   LOG_DEBUG("Dataset::~Dataset");
}

std::string  Dataset::name()
{
   return name_;
}

std::string Dataset::alias()
{
   return alias_;
}



std::string Dataset::schema()
{
   return schema_;
}

std::string Dataset::catalog()
{
   return catalog_;
}

DBPROVIDER Dataset::provider()
{
   return provider_;
}

void Dataset::setSchema(std::string schema)
{
   schema_ = schema;
}

void Dataset::setProvider(DBPROVIDER provider)
{
   provider_ = provider;
}


void Dataset::setCatalog(std::string catalog)
{
   catalog_ = catalog;
}


Dataset& Dataset::as(std::string alias)
{
   alias_ = alias;
   return *this;
}


Column  Dataset::at(int index)
{
   return columns_.at(index);
}


int Dataset::rowSize()
{
   return columns_.size();
}

std::string Dataset::joinidentifier()
{
   return name_;
}


};/*namespace cppsqlx*/
