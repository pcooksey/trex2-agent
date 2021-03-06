/*********************************************************************
 * Software License Agreement (BSD License)
 * 
 *  Copyright (c) 2011, MBARI.
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 * 
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the TREX Project nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */
#ifdef TREX_PP_SYSTEM_FILE

# if defined(_MSC_VER)  // MSVC
#  pragma warning (push, 0)

# elif defined(__GNUC__) // gcc

#  undef TREX_PP_PUSHED
#  if (__GNUC__>4) || ((__GNUC__==4) && (__GNUC_MINOR__>=6))
// push and pop only exists since 4.6 in gcc
#   pragma GCC diagnostic push
#   define TREX_PP_PUSHED
#  endif

// indicate that this header is system to gcc and clang
#  pragma GCC system_header

// This below is a hacky way to make gcc shut up about deprecated headers
# undef TREX_PP_DEPRECATED
# if defined(__GNUC__) && defined(__DEPRECATED)
# undef __DEPRECATED
# define TREX_PP_DEPRECATED
# endif // __GNUC__ && _DEPRECATED

# elif defined(__clang__)

# pragma clang diagnostic push
# pragma clang system_header

# endif // end of compiler specific macros


// include the file
# include TREX_PP_SYSTEM_FILE
// undef the macro
# undef TREX_PP_SYSTEM_FILE



# if defined(_MSC_VER)

// for msvc restore warning level
#  pragma warning (pop)

# elif defined(__GNUC__)

#  if defined(TREX_PP_DEPRECATED)
#   define __DEPRECATED
#   undef TREX_PP_DEPRECATED
#  endif

# if defined(TREX_PP_PUSHED)
// restore warning level
#  pragma GCC diagnostic pop
#  undef TREX_PP_PUSHED
# endif

# elif defined(__clang__)

#  pragma clang diagnostic pop

# endif // _MSC_VER

#endif // TREX_PP_SYTEM_FILE
