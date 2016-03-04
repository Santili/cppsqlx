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
#include <odbcerror.hpp>
#include <logger.hpp>

namespace cppsqlx
{


const std::string ODBCError::operator() (std::string fnc,SQLHANDLE handle,SQLSMALLINT type)
{
    std::string error;
    SQLINTEGER       i = 0;
    SQLINTEGER       native;
    SQLCHAR          state[ 7 ];
    SQLCHAR          text[256];
    SQLSMALLINT      len;
    SQLRETURN        ret;
    char             buffer [524];

    do
    {
        ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,sizeof(text), &len );
        if (SQL_SUCCEEDED(ret))
        {
           sprintf(buffer,"%s:%id:%id:%s\n", state, i, native, text);
           error += buffer;
        }
    }
    while( ret == SQL_SUCCESS );
    error.erase(std::remove(error.begin(), error.end(), '\n'), error.end());
    return error;
}


} /*namespace cppsqlx*/
