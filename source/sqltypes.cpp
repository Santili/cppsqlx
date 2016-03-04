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
#include <sqltypes.hpp>

namespace cppsqlx
{

std::string SQL::SQLTYPE(SQL::TYPE sqltype)
{
   std::string type;
   switch(sqltype)
   {
      case SQL::TYPE::VARCHAR :
         type = "VARCHAR";
         break;
      case SQL::TYPE::INTEGER :
         type = "INTEGER";
         break;
      case SQL::TYPE::TINYINT :
         type = "TINYINT";
         break;
      case SQL::TYPE::SMALLINT :
         type = "SMALLINT";
         break;
      case SQL::TYPE::BIGINT :
         type = "BIGINT";
         break;
      case SQL::TYPE::LONG :
         type = "LONG";
         break;
      case SQL::TYPE::DOUBLE :
         type = "DOUBLE";
         break;
      case SQL::TYPE::FLOAT :
         type = "FLOAT";
         break;
      case SQL::TYPE::DATE :
         type = "DATE";
         break;
      case SQL::TYPE::HOUR :
         type = "HOUR";
         break;
      case SQL::TYPE::DATETIME :
         type = "DATETIME";
         break;
      case SQL::TYPE::TIMESTAMP :
         type = "TIMESTAMP";
         break;
   }

   return type;
};


};/*namespace cppsqlx*/
