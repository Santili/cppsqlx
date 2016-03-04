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

#ifndef __SQLTYPES_HPP__
#define __SQLTYPES_HPP__
#include <cppsqlxincludes.hpp>

namespace cppsqlx
{

static std::map<int,std::string> ORACLE_SQL_TYPES = {
{SQL_CHAR                     ,"CHAR"},
{SQL_VARCHAR                  ,"VARCHAR2"},
{SQL_LONGVARCHAR              ,"LONG"},
{SQL_DECIMAL                  ,"NUMBER"},
{SQL_NUMERIC                  ,"NUMBER"},
{SQL_SMALLINT                 ,"NUMBER"},
{SQL_INTEGER                  ,"INTEGER"},
{SQL_REAL                     ,"FLOAT"},
{SQL_FLOAT                    ,"FLOAT"},
{SQL_DOUBLE                   ,"FLOAT"},
{SQL_BIT                      ,"CHAR"},
{SQL_TINYINT                  ,"NUMBER"},
{SQL_BIGINT                   ,"NUMBER"},
{SQL_BINARY                   ,"RAW"},
{SQL_VARBINARY                ,"RAW"},
{SQL_LONGVARBINARY            ,"LONG RAW"},
{SQL_TYPE_DATE                ,"DATE"},
{SQL_TYPE_TIME                ,"TIME"},
{SQL_TYPE_TIMESTAMP           ,"TIMESTAMP"},
{SQL_INTERVAL_MONTH           ,"INTERVAL MONTH"},
{SQL_INTERVAL_YEAR            ,"INTERVAL YEAR"},
{SQL_INTERVAL_YEAR_TO_MONTH   ,"INTERVAL YEAR TO MONTH"},
{SQL_INTERVAL_DAY             ,"INTERVAL DAY"},
{SQL_INTERVAL_HOUR            ,"INTERVAL HOUR"},
{SQL_INTERVAL_MINUTE          ,"INTERVAL MINUTE"},
{SQL_INTERVAL_SECOND          ,"INTERVAL SECOND"},
{SQL_INTERVAL_DAY_TO_HOUR     ,"INTERVAL DAY TO HOUR"},
{SQL_INTERVAL_DAY_TO_MINUTE   ,"INTERVAL DAY TO MINUTE"},
{SQL_INTERVAL_DAY_TO_SECOND   ,"INTERVAL DAY TO SECOND"},
{SQL_INTERVAL_HOUR_TO_MINUTE  ,"INTERVAL HOUR TO MINUTE"},
{SQL_INTERVAL_HOUR_TO_SECOND  ,"INTERVAL HOUR TO SECOND"},
{SQL_INTERVAL_MINUTE_TO_SECOND,"INTERVAL MINUTE TO SECOND"},
{SQL_GUID                     ,"UNSUPPORTED"}
};


static std::map<int,std::string> NETEZZA_SQL_TYPES = {
{SQL_CHAR                     ,"CHAR"},
{SQL_VARCHAR                  ,"VARCHAR"},
{SQL_LONGVARCHAR              ,"VARCHAR"},
{SQL_DECIMAL                  ,"DECIMAL"},
{SQL_NUMERIC                  ,"NUMERIC"},
{SQL_SMALLINT                 ,"SMALLINT"},
{SQL_INTEGER                  ,"INTEGER"},
{SQL_REAL                     ,"REAL"},
{SQL_FLOAT                    ,"FLOAT"},
{SQL_DOUBLE                   ,"DOUBLE"},
{SQL_BIT                      ,"BIT"},
{SQL_TINYINT                  ,"SMALLINT"},
{SQL_BIGINT                   ,"BIGINT"},
{SQL_BINARY                   ,"BINARY"},
{SQL_VARBINARY                ,"VARBINARY"},
{SQL_LONGVARBINARY            ,"UNSUPPORTED"},
{SQL_TYPE_DATE                ,"DATE"},
{SQL_TYPE_TIME                ,"TIME"},
{SQL_TYPE_TIMESTAMP           ,"TIMESTAMP"},
{SQL_INTERVAL_MONTH           ,"INTERVAL MONTH"},
{SQL_INTERVAL_YEAR            ,"INTERVAL YEAR"},
{SQL_INTERVAL_YEAR_TO_MONTH   ,"INTERVAL YEAR TO MONTH"},
{SQL_INTERVAL_DAY             ,"INTERVAL DAY"},
{SQL_INTERVAL_HOUR            ,"INTERVAL HOUR"},
{SQL_INTERVAL_MINUTE          ,"INTERVAL MINUTE"},
{SQL_INTERVAL_SECOND          ,"INTERVAL SECOND"},
{SQL_INTERVAL_DAY_TO_HOUR     ,"INTERVAL DAY TO HOUR"},
{SQL_INTERVAL_DAY_TO_MINUTE   ,"INTERVAL DAY TO MINUTE"},
{SQL_INTERVAL_DAY_TO_SECOND   ,"INTERVAL DAY TO SECOND"},
{SQL_INTERVAL_HOUR_TO_MINUTE  ,"INTERVAL HOUR TO MINUTE"},
{SQL_INTERVAL_HOUR_TO_SECOND  ,"INTERVAL HOUR TO SECOND"},
{SQL_INTERVAL_MINUTE_TO_SECOND,"INTERVAL MINUTE TO SECOND"},
{SQL_GUID                     ,"UNSUPPORTED"}
};


namespace SQL
{
  enum TYPE {VARCHAR,INTEGER,TINYINT,SMALLINT,BIGINT,LONG,DOUBLE,FLOAT,DATE,HOUR,DATETIME,TIMESTAMP};
  std::string SQLTYPE(SQL::TYPE sqltype);
}


};/*namespace cppsqlx*/

#endif //__SQLTYPES_HPP__
