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

/**
 * @file compute_levels.hpp
 *
 * @brief Compute levels of the AIG
 *
 * @author Mathias Soeken
 * @since  2.3
 */

#ifndef COMPUTE_LEVELS_HPP
#define COMPUTE_LEVELS_HPP

#include <map>
#include <vector>

#include <core/properties.hpp>
#include <classical/aig.hpp>

namespace cirkit
{

/**
 * @brief Maps each aig_node to a level
 */
std::map<aig_node, unsigned> compute_levels( const aig_graph& aig,
                                             const properties::ptr& settings = properties::ptr(),
                                             const properties::ptr& statistics = properties::ptr() );

/**
 * @brief Maps each level to a vector of aig_nodes
 *
 * Internally calls compute_levels
 */
std::vector<std::vector<aig_node>> levelize_nodes( const aig_graph& aig,
                                                   const properties::ptr& settings = properties::ptr(),
                                                   const properties::ptr& statistics = properties::ptr() );

}

#endif

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
