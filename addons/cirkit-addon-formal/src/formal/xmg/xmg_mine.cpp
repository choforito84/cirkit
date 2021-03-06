/* CirKit: A circuit toolkit
 * Copyright (C) 2009-2015  University of Bremen
 * Copyright (C) 2015-2017  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "xmg_mine.hpp"

#include <fstream>
#include <iostream>

#include <boost/algorithm/string/trim.hpp>
#include <boost/optional.hpp>

#include <core/utils/string_utils.hpp>
#include <classical/utils/truth_table_utils.hpp>
#include <formal/xmg/xmg_minlib.hpp>

namespace cirkit
{

/******************************************************************************
 * Types                                                                      *
 ******************************************************************************/

/******************************************************************************
 * Private functions                                                          *
 ******************************************************************************/

/******************************************************************************
 * Public functions                                                           *
 ******************************************************************************/

void xmg_mine( const std::string& lut_file, const std::string& opt_file, const properties::ptr& settings, const properties::ptr& statistics )
{
  xmg_minlib_manager minlib( settings );
  minlib.load_library_string( xmg_minlib_manager::npn2_s );
  minlib.load_library_string( xmg_minlib_manager::npn3_s );
  minlib.load_library_string( xmg_minlib_manager::npn4_s );

  minlib.load_library_file( opt_file, true );

  std::ifstream in( lut_file.c_str(), std::ifstream::in );
  std::string line;

  while ( getline( in, line ) )
  {
    boost::trim( line );

    tt t( line );

    minlib.find_xmg_no_npn( t );
  }
}

}

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
