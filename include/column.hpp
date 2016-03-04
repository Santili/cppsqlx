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

#ifndef __COLUMN_HPP__
#define __COLUMN_HPP__
#include <cppsqlxincludes.hpp>

namespace cppsqlx
{

class Dataset;
class DatasetFactory;
class Column
{
   private:
   friend class DatasetFactory;
   friend class Dataset;
   Column(std::string name,int position,std::string type,int size,int precision,int scale, int sqltype,bool isnullable = false);


   private:
   std::string                    name_;
   std::string                    type_;
   int                            sqltype_;
   int                            size_;
   int                            precision_;
   int                            scale_;
   bool                           isnullable_;
   int                            position_;

   public:
   std::string                    name();
   std::string                    type();
   int                            sqlType();
   int                            size();
   int                            precision();
   int                            scale();
   int                            isNullable();
   int                            position();

};/*Column*/

};/*namespace cppsqlx*/

#endif //__COLUMN_HPP__
