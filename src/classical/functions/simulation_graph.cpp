/* CirKit: A circuit toolkit
 * Copyright (C) 2009-2015  University of Bremen
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

#include "simulation_graph.hpp"

#include <fstream>

#include <boost/assign/std/vector.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/combine.hpp>

#include <core/io/write_graph_file.hpp>
#include <core/utils/bitset_utils.hpp>
#include <core/utils/range_utils.hpp>
#include <classical/functions/aig_support.hpp>
#include <classical/utils/aig_utils.hpp>
#include <classical/utils/simulate_aig.hpp>

using namespace boost::assign;

namespace cirkit
{

simulation_graph create_simulation_graph( const aig_graph& aig, const std::vector<boost::dynamic_bitset<>>& sim_vectors,
                                          const properties::ptr& settings, const properties::ptr& statistics )
{
  simulation_graph g;
  auto& edge_lookup       = boost::get_property( g, boost::graph_edge_lookup );
  const auto& vertex_in_degree  = boost::get( boost::vertex_in_degree, g );
  const auto& vertex_out_degree = boost::get( boost::vertex_out_degree, g );

  /* Settings */
  const auto dotname     = get( settings, "dotname",     std::string() );
  const auto graphname   = get( settings, "graphname",   std::string() );
  const auto labeledname = get( settings, "labeledname", std::string() );
  const bool support     = get( settings, "support",     false );

  /* Timing */
  properties_timer t( statistics );

  /* AIG */
  const auto& info = aig_info( aig );
  const auto n = info.inputs.size();
  const auto m = info.outputs.size();

  /* add vertices */
  const auto vertices_count = n + sim_vectors.size() + m;
  add_vertices( g, vertices_count );
  edge_lookup.reserve( vertices_count << 5u );

  /* edge inserting */
  const auto add_edge_func = [&]( unsigned from, unsigned to ) {
    add_edge( from, to, g );
    edge_lookup.insert( {from, to} );
    vertex_in_degree[to]++;
    vertex_out_degree[from]++;
  };

  /* edges from inputs to simulation vectors */
  for ( auto it : index( sim_vectors ) )
  {
    foreach_bit( it.second, [&]( unsigned pos ) {
        add_edge_func( pos, n + it.first );
      } );
  }

  /* simulate */
  word_assignment_simulator::aig_name_value_map map( info.inputs.size() );
  const auto sim_vectors_t = transpose( sim_vectors );
  for ( const auto& p : boost::combine( info.inputs, sim_vectors_t ) )
  {
    map.insert( {info.node_names.at( boost::get<0>( p ) ), boost::get<1>( p )} );
  }

  const auto results = simulate_aig( aig, word_assignment_simulator( map ) );

  /* create edges */
  for ( auto j = 0u; j < m; ++j )
  {
    const auto& ovalue = results.at( info.outputs[j].first );
    for ( auto i = 0u; i < sim_vectors.size(); ++i )
    {
      if ( ovalue[i] )
      {
        add_edge_func( n + i, n + sim_vectors.size() + j );
      }
    }
  }

  /* annotate support size */
  if ( support )
  {
    const auto& vertex_support = boost::get( boost::vertex_support, g );

    const auto s = aig_structural_support( aig );
    for ( const auto& o : index( info.outputs ) )
    {
      vertex_support[n + sim_vectors.size() + o.first] = s.at( o.second.first );
    }
  }

  /* Dump files */
  if ( !dotname.empty() )
  {
    std::ofstream os( dotname.c_str(), std::ofstream::out );
    boost::write_graphviz( os, g );
    os.close();
  }

  if ( !graphname.empty() )
  {
    write_graph_file( g, graphname );
  }

  if ( !labeledname.empty() )
  {
    // TODO be more flexible
    write_labeled_graph_file( g, [&]( const simulation_node& v ) {
        if ( v < n ) return 1u;
        if ( v < n + sim_vectors.size() ) return 2u + (unsigned)std::min( (unsigned)sim_vectors[v - n].count(), 3u );
        return 0u;
      }, [&]( const simulation_edge& e ) {
        if ( boost::source( e, g ) < n ) return 0u;
        else return 1u + (unsigned)std::min( (unsigned)sim_vectors[boost::source( e, g ) - n].count(), 3u );
      }, labeledname );
  }

  return g;
}

std::vector<boost::dynamic_bitset<>> create_simulation_vectors( unsigned width, unsigned selector,
                                                                std::vector<unsigned>* partition )
{
  std::vector<boost::dynamic_bitset<>> sim_vectors;

  if ( selector & static_cast<unsigned>( simulation_pattern::all_hot ) )
  {
    sim_vectors += ~boost::dynamic_bitset<>( width );
    if ( partition ) *partition += 1;
  }
  if ( selector & static_cast<unsigned>( simulation_pattern::one_hot ) )
  {
    for ( unsigned i = 0u; i < width; ++i )
    {
      boost::dynamic_bitset<> b( width );
      b.set( i );
      sim_vectors += b;
    }
    if ( partition ) *partition += width;
  }
  if ( selector & static_cast<unsigned>( simulation_pattern::two_hot ) )
  {
    for ( unsigned i = 0u; i < width - 1u; ++i )
    {
      for ( unsigned j = i + 1u; j < width; ++j )
      {
        boost::dynamic_bitset<> b( width );
        b.set( i );
        b.set( j );
        sim_vectors += b;
      }
    }
    if ( partition ) *partition += ( width * (width -  1) ) / 2;
  }

  if ( selector & static_cast<unsigned>( simulation_pattern::all_cold ) )
  {
    sim_vectors += boost::dynamic_bitset<>( width );
    if ( partition ) *partition += 1;
  }
  if ( selector & static_cast<unsigned>( simulation_pattern::one_cold ) )
  {
    for ( unsigned i = 0u; i < width; ++i )
    {
      auto b = ~boost::dynamic_bitset<>( width );
      b.reset( i );
      sim_vectors += b;
    }
    if ( partition ) *partition += width;
  }
  if ( selector & static_cast<unsigned>( simulation_pattern::two_cold ) )
  {
    for ( unsigned i = 0u; i < width - 1u; ++i )
    {
      for ( unsigned j = i + 1u; j < width; ++j )
      {
        auto b = ~boost::dynamic_bitset<>( width );
        b.reset( i );
        b.reset( j );
        sim_vectors += b;
      }
    }
    if ( partition ) *partition += ( width * (width -  1) ) / 2;
  }

  return sim_vectors;
}

igraph_t simulation_graph_to_igraph( const simulation_graph& g )
{
  igraph_t ig;
  igraph_vector_t edges;

  igraph_vector_init( &edges, boost::num_edges( g ) << 1u );
  unsigned index = 0u;
  for ( const auto& e : boost::make_iterator_range( boost::edges( g ) ) )
  {
    VECTOR(edges)[index++] = boost::source( e, g );
    VECTOR(edges)[index++] = boost::target( e, g );
  }
  igraph_create( &ig, &edges, boost::num_vertices( g ), 1 );
  igraph_simplify( &ig, 1, 1, 0 );
  return ig;
}

}

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End: