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

#ifndef __DATASETFACTORY_HPP__
#define __DATASETFACTORY_HPP__
#include <cppsqlxincludes.hpp>
#include <connection.hpp>
#include <table.hpp>
#include <dataset.hpp>
#include <dbprovider.hpp>

namespace cppsqlx
{

class DatasetFactory
{
   public:
   DatasetFactory();
   ~DatasetFactory();
   Dataset  dsFrom(std::string name,std::shared_ptr<Connection> connection,std::string schema = "");
   Dataset  dsFrom(std::string name,Dataset ds,DBPROVIDER provider = DBPROVIDER::UNKNOWN);
   //std::shared_ptr<Dataset>                 dsFrom(std::string name,SQLSelect query,std::shared_ptr<Connection> connection);
   std::shared_ptr<Table>                   tableFrom(std::string name,std::shared_ptr<Connection> connection);
   std::vector<Dataset>    datasetsFrom(std::shared_ptr<Connection> connection);
};/*DatasetFactory*/

#define GET_DATASET(X,Y) DatasetFactory().dsFrom(X,Y)


};/*namespace cppsqlx*/

#endif //__DATASETFACTORY_HPP__
