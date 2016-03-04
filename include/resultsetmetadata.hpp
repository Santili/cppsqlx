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

#ifndef __RESULTSETMETADATA_HPP__
#define __RESULTSETMETADATA_HPP__
#include <cppsqlxincludes.hpp>

namespace cppsqlx
{

class Resultset;
class ResultsetMetadata
{
   private:
   friend class Resultset;
   ResultsetMetadata();

   public:
   ~ResultsetMetadata();

   private:
   int                            columncount_;
   std::map<int,std::string>      columnnames_;
   std::map<int,std::string>      columntypes_;
   std::map<int,int>              columnsqltypes_;
   std::map<int,int>              columnprecisions_;
   std::map<int,int>              columnscales_;
   std::map<int,int>              columnsizes_;
   std::map<int,int>              columnsnullable_;

   public:
   int                            getColumnCount();
   std::string                    getColumnName(int index);
   std::string                    getColumnTypeName(int index);
   int                            getColumnType(int index);
   int                            getPrecision(int index);
   int                            getScale(int index);
   int                            getColumnDisplaySize(int index);
   int                            isNullable(int index);

};/*ResultsetMetadata*/

};/*namespace cppsqlx*/

#endif //__RESULTSETMETADATA_HPP__
