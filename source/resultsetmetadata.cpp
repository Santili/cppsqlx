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
#include <resultsetmetadata.hpp>
#include <resultset.hpp>
#include <logger.hpp>

namespace cppsqlx
{

ResultsetMetadata::ResultsetMetadata()
{
   LOG_DEBUG( "ResultsetMetadata::ResultsetMetadata");
}


ResultsetMetadata::~ResultsetMetadata()
{
   LOG_DEBUG("ResultsetMetadata::~ResultsetMetadata");
}



int  ResultsetMetadata::getColumnCount()
{
   return columncount_;
}


std::string  ResultsetMetadata::getColumnName(int index)
{
   return columnnames_[index];
}


std::string  ResultsetMetadata::getColumnTypeName(int index)
{
   return columntypes_[index];
}


int ResultsetMetadata::getPrecision(int index)
{
   return columnprecisions_[index];
}


int ResultsetMetadata::getScale(int index)
{
   return columnscales_[index];
}

int ResultsetMetadata::getColumnDisplaySize(int index)
{
   return  columnsizes_[index];
}

int ResultsetMetadata::isNullable(int index)
{
   return  columnsnullable_[index];
}

int ResultsetMetadata::getColumnType(int index)
{
   return columnsqltypes_[index];
}


};/*namespace cppsqlx*/
