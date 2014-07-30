/* RevKit: A Toolkit for Reversible Circuit Design (www.revkit.org)
 * Copyright (C) 2009-2011  The RevKit Developers <revkit@informatik.uni-bremen.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file exact_synthesis.hpp
 *
 * @brief Exact Synthesis of Reversible Networks
 */

#include "z3_utils.hpp"

namespace cirkit
{

z3::expr operator<<( z3::expr const & a, z3::expr const & b )
{
  check_context( a, b );
  assert( a.is_bv() && b.is_bv() );
  Z3_ast r = Z3_mk_bvshl( a.ctx(), a, b );
  a.check_error();
  return z3::expr( a.ctx(), r );
}

z3::expr ite( z3::expr const & a, z3::expr const & b, z3::expr const & c )
{
  check_context( a, b );
  check_context( b, c );
  assert(a.is_bool());
  Z3_ast r = Z3_mk_ite( a.ctx(), a, b, c );
  a.check_error();
  return z3::expr( a.ctx(), r );
}

boost::dynamic_bitset<> to_bitset( const z3::expr& a )
{
  std::stringstream s;
  s << a;
  return boost::dynamic_bitset<>( s.str().substr( 2u ) );
}

}

// Local Variables:
// c-basic-offset: 2
// End: