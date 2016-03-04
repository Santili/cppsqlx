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

#ifndef __RESULTSETITERATOR_HPP__
#define __RESULTSETITERATOR_HPP__
#include <cppsqlxincludes.hpp>
#include <globaldefinitions.hpp>
#include <resultset.hpp>

namespace cppsqlx
{

ResultsetIterator begin(std::shared_ptr<Resultset> p);
ResultsetIterator end(std::shared_ptr<Resultset> p);
class ResultsetIterator
{
   public:
   typedef std::shared_ptr<const Resultset> value_type;

   bool operator != (const ResultsetIterator& other) const
   {
      return cursorstate_ != other.cursorstate_ && rownum_ != other.rownum_;
   }

   value_type operator* () 
   {
      return resultset_;
   }

   const ResultsetIterator& operator++ ()
   {
       resultset_->next();
       cursorstate_ = resultset_->cursorState();
       rownum_ = resultset_->rowNum();
       return *this;
   }

   public:
   ResultsetIterator(std::shared_ptr<Resultset> resultset,ODBC_CURSOR_STATE cursorstate,int rownum):cursorstate_(cursorstate), rownum_(rownum)
   {
      resultset_ = resultset;
   };
   ~ResultsetIterator(){};

   private:
   std::shared_ptr<Resultset>  resultset_;
   ODBC_CURSOR_STATE cursorstate_;
   int rownum_;

};/*ResultsetIterator*/

};/*namespace cppsqlx*/

#endif //__RESULTSETITERATOR_HPP__
