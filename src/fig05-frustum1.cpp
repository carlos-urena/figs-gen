
#include <initializer_list>
#include <string>
#include <vector>
#include <iostream>
#include <vec_mat.h>

using namespace std ;
using namespace vec_mat ;

class IndPolMesh ;

// ----------------------------------------------------------------------
// a sequence of vertexes indexes

struct VertexIdxsSeq
{
   public:
   vector<unsigned> idxs ;

   inline VertexIdxsSeq( std::initializer_list<unsigned> p_idxs ) 
   {
      for( auto it = p_idxs.begin(); it != p_idxs.end(); ++it ) 
         idxs.push_back( *it );
   } ;
   
   inline unsigned operator[] ( const unsigned i ) const 
   {
      assert( i < idxs.size() );
      return idxs[i] ;
   }
   inline unsigned size () const 
   {
      return idxs.size() ;
   }

   inline void write_coords( const vector<Vec3> & vertexes ) const 
   {
      for( unsigned iv= 0 ; iv < idxs.size() ; iv++ )
         cout << " " << vertexes[idxs[iv]]  << (iv < idxs.size()-1 ? " -- " : " ") ; 
   }
      
   
} ;

// ----------------------------------------------------------------------
// indexed polygonal meshes 

class IndPolMesh
{
   public:

   vector<Vec3>          vertexes ;
   vector<VertexIdxsSeq> polygons ;
   vector<Vec3>          pol_normals ;
   vector<Vec3>          pol_centers ;
   vector<Vec2u>         edges_verts ;  // for each edge, adyacent vertxes indexes
   vector<Vec2u>         edges_pols  ;  // for each edge, adyacent polygons indexes, or -1

   // init tables from 'vertexes' and 'polygons'
   inline void init_tables()
   {
      // empty current tables, if not void
      pol_normals.clear();
      pol_centers.clear();
      edges_verts.clear() ;
      edges_pols.clear() ;

      // compute 'pol_centers'
      
      for( unsigned i = 0 ; i < polygons.size() ; i++ )
      {
         const VertexIdxsSeq & p = polygons[i] ;
         Vec3 sum = { 0.0, 0.0, 0.0 } ;

         for( unsigned j = 0 ; j < p.size() ; j++ )
            sum = sum + vertexes[p[j]] ;

         pol_centers.push_back( (1.0f/float(p.size())) * sum );
      }

      // compute 'pol_normals'
     
      for( unsigned i = 0 ; i < polygons.size() ; i++ )
      {
         const VertexIdxsSeq & p = polygons[i] ;
         const Vec3           
            edge1 = vertexes[p[1]] - vertexes[p[0]],
            edge2 = vertexes[p[p.size()-1]] - vertexes[p[0]],
            nn    = edge2.cross( edge1 ) ;

         if ( nn.lengthSq() > 0.0  )
            pol_normals.push_back( nn.normalized() );
         else 
            pol_normals.push_back( Vec3 { 0.0,0.0,0.0} );
      }

      
     
     

      // populate adj_vert and adj_edge

       vector<vector<unsigned> > 
         adj_vert , // for each vertex, the list of (greater) adjacent vertexes indexes
         adj_edge ; // similar to the other one, but with  

      for( unsigned iv = 0 ; iv < vertexes.size() ; iv++ )
      {
         adj_vert.push_back( vector<unsigned>{ } );
         adj_edge.push_back( vector<unsigned>{ } );
      }

      // compute 'edges_verts' and 'edges_pols'

      const unsigned n_pols = polygons.size() ;
      
      for( unsigned ip = 0 ; ip < n_pols ; ip++ )
      {
         const VertexIdxsSeq & p = polygons[ip] ;
         const unsigned        n = p.size() ;
         assert( 2 < n );

         for( unsigned j = 0 ; j < n ; j++ )
         {
            unsigned iv0 = p[j], iv1 = p[(j+1)% n] ;
            
            if ( iv0 < iv1 )
               std::swap( iv0, iv1 );
            
            // search i1 in adjacent list of i0
            bool      found = false ;
            unsigned  k_found = 0 ;
            for( unsigned k = 0 ; k < adj_vert[iv0].size() ; k++ )
               if ( adj_vert[iv0][k] == iv1 )
               {  found   = true ;
                  k_found = k ;
                  break ;
               }
            
            if ( found )   // the edge 'i0--i1' is already in the tables: update second polygon in the edge polygons pair
            {
               const unsigned ei        = adj_edge[iv0][k_found] ; // get the edge index
               Vec2u &        edge_pols = edges_pols[ei] ;         // get reference to edge polygons

               edge_pols(1) = ip ;  // update second polygon of the edge
            }
            else // the edge 'i0--i1' is not in the tables
            {  
               const unsigned ei = edges_verts.size();      // new edge index
               edges_verts.push_back( Vec2u{ iv0, iv1 } );  // add edge's vertexes (at 'ei')
               edges_pols.push_back( Vec2u{ ip, n_pols } ); // add edge's adjacent polygons (also at 'ei') ('n_pols' means there is still no second adjacent polygon)
               adj_vert[iv0].push_back( iv1 ) ;             // register index of adjacent vertex 
               adj_edge[iv0].push_back( ei  );              // register index of adjacent edge
            } 
         }
      }

   }
} ;

// ----------------------------------------------------------------------
// frustum mesh

class FrustumMesh : public IndPolMesh 
{
   public:
   FrustumMesh( const float l, const float r, 
                const float t, const float b,
                const float n, const float f   );  
   void draw( const Vec3 & v );  
} ;

// ----------------------------------------------------------------------

FrustumMesh::FrustumMesh( const float l, const float r, 
                          const float t, const float b,
                          const float n, const float f   )

{
   assert( 0 < n );
   assert( n < f );

   const float
      s = f/n,
      lf = l*s, 
      rf = r*s, 
      bf = b*s,
      tf = t*s ;

   vertexes =
   {  
      // vertexes on the near plane
      { l, b, -n }, { r, b, -n },
      { l, t, -n }, { r, t, -n },

      // vertexes on the far plane
      { lf, bf, -f }, { rf, bf, -f },
      { lf, tf, -f }, { rf, tf, -f },   
   };

   polygons = 
   {  
      {6,7,5,4}, // far (back) polygon 
      {6,4,0,2}, // left side polygon 
      {4,5,1,0},  // bottom polygon 

      {0,1,3,2}, // near (front) plane polygon 
      {1,5,7,3}, // right side polygon 
      {2,3,7,6}, // top polygon 
   } ;

   // inits normals, edges, etc....
   init_tables();

}

// draw using a view vector 'v'
void FrustumMesh::draw( const Vec3 & v )
{
   const unsigned n_pols = polygons.size() ;

   // draw normals, only for debugging 
   // for( unsigned i = 0 ; i < polygons.n_pols ; i++ )
   // {
   //    cout << "\\draw[->,>=latex,line width=0.3mm,color=blue] " ;
   //    cout << " " << pol_centers[i] << " -- " << (pol_centers[i] + 0.5f*pol_normals[i]) << " ;" << endl ;
   // }

   // classify edges according to 'v'

   std::vector<bool> draw_edge ; // for each edge, true iif the edge is front-facing or contour according to 'v'

   for( unsigned ie = 0 ; ie < edges_verts.size() ; ie++ )
   {
      
   }

   // draw all edges (dashed)
   
   for( unsigned ie = 0 ; ie < edges_verts.size() ; ie++ )
   {
      const Vec2u & ep = edges_pols[ie] ; // get adjacent polygons 
      const Vec3 & v1 = vertexes[edges_verts[ie](0)],
                   v2 = vertexes[edges_verts[ie](1)] ;
      cout << "\\draw[line width=0.1mm,dashed] " << v1 << " -- " << v2 << " ; " << endl ;
   }

   // draw filled polygons (only front-facing polygons)
   for( unsigned ip = 0 ; ip < polygons.size() ; ip++ )
      if ( 0.0 < pol_normals[ip].dot( v ) )
      {
         cout << "\\fill[fill=gray,opacity=0.1] " << endl ;
         polygons[ip].write_coords( vertexes ); 
         cout << " -- cycle ;" << endl << endl ;
      }
   

   // draw again, but only front facing or contour edges 

   
}

void arrow3( const Vec3 & org, const Vec3 & dest, const std::string & style, const std::string & end_node  )
{
   using namespace std ;
   cout << "\\draw[->,>=latex," << style << "]" << endl 
      << "         "<< org << " -- " << dest << " " << end_node << " ;" << endl ;
}
void segment( const Vec3 & org, const Vec3 & dest, const std::string & style, const std::string & end_node  )
{
   using namespace std ;
   cout << "\\draw[" << style << "]" << endl 
      << "         "<< org << " -- " << dest << " " << end_node << " ;" << endl ;
}

void axes()
{
   
   arrow3( {0,0,0}, {1,0,0}, "color=red,line width=0.1mm", "node[right] {$\\vux_c$}" );
   arrow3( {0,0,0}, {0,1,0}, "color=green!50!black,line width=0.1mm", "node[above] {$\\vuy_c$}" );
   arrow3( {0,0,0}, {0,0,1}, "color=blue,line width=0.1mm", "node[above] {$\\vuz_c$}" );
}


int main( int argc, char *argv[] )
{
   using namespace std ;
   using namespace vec_mat ;

   cout 
      << "\\documentclass[border=1mm]{standalone}" << endl 
      << "\\input{header.tex}" << endl ;

   const float 
      l = -0.3,
      r = -l,
      b = 0.7*l,
      t = -b ,
      n = 1.5,
      f = 3.0;

   auto fm = FrustumMesh { l, r, b, t, n, f };

   //cout << "// " << fm.polygons[0][0] << " ?? " << endl ;

   cout
      << "\\definecolor{verde}{rgb}{0,0.3,0}" << endl 
      << "\\tikzset{isometrico/.style={x={(0.7cm,-0.45cm)},   " << endl
      << "                             y={(0.0cm,0.95cm)},     " << endl
      << "                             z={(-0.7cm,-0.45cm)}}} " << endl
      // << "\\tikzset{isometrico/.style={x={(0.0cm,-0.0cm)},   " << endl
      // << "                             y={(0.0cm,0.95cm)},     " << endl
      // << "                             z={(-1.0cm,0.0cm)}}} " << endl
      << "\\begin{tikzpicture}[scale=2.5,isometrico]" << endl ;

   axes();
   segment( {0,0,2}, {0,0,-n}, "line width=0.1mm,color=blue", "" );
   //segment( {0,0,-n}, {0,0,-f}, "dashed,line width=0.07mm,color=blue", "" );
   fm.draw( Vec3 {1.0,1.0,1.0} );
   
   segment( {0,0,0}, {l,t,-n}, "line width=0.05mm,color=gray", "" );
   segment( {0,0,0}, {r,t,-n}, "line width=0.05mm,color=gray", "" );
   segment( {0,0,0}, {l,b,-n}, "line width=0.05mm,color=gray", "" );
   segment( {0,0,0}, {r,b,-n}, "line width=0.05mm,color=gray", "" );

   

   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}
