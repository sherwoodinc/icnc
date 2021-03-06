/* *******************************************************************************
 *  Copyright (c) 2007-2014, Intel Corporation
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of Intel Corporation nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ********************************************************************************/

/*
  see cnc_stddef.h
*/

#include <cnc/internal/cnc_stddef.h>
#include <cnc/internal/dist/distributor.h>
#include <cnc/internal/traceable.h>

namespace CnC {
    namespace Internal {

        void cnc_assert_failed( const char* filename, int line, const char* expression, const char* message ) {
            if ( message == NULL ) {
                Speaker oss( std::cerr );
                oss << filename << ":" << line << " assertion '" << expression << "' failed.";
            } else {
                Speaker oss( std::cerr );
                oss << filename << ":" << line << " assertion '" << expression << "' failed: " << message;
            }
            abort();
        }
        
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        Speaker::Speaker( std::ostream & os )
            : m_os( os )
        {
            static_cast< std::ostringstream & >( *this ) << "[CnC";
            if( distributor::active() ) static_cast< std::ostringstream & >( *this ) << " " << distributor::myPid();
            static_cast< std::ostringstream & >( *this ) << "] ";
        }
        
        Speaker::~Speaker()
        {
            static_cast< std::ostringstream & >( *this ) << std::endl;
            tbb::queuing_mutex::scoped_lock _lock( ::CnC::Internal::s_tracingMutex );
            m_os << str() << std::flush;
        }
        
    } // namespace Internal
} // namespace CnC


