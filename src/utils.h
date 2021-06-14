
#ifndef UTILS_H
#define UTILS_H

#include <initializer_list>
#include <string>
#include <vector>
#include <iostream>
#include <vec_mat.h>



namespace utils 
{

using namespace std ;
using namespace vec_mat ;

class IndPolMesh ;

// **********************************************************************
// Class VertexIdxSeq
// a sequence of indexed vertices
// ----------------------------------------------------------------------

struct VertexIdxsSeq
{
   public:
   vector<unsigned> idxs ;

    VertexIdxsSeq( std::initializer_list<unsigned> p_idxs ) 
   {
      for( auto it = p_idxs.begin(); it != p_idxs.end(); ++it ) 
         idxs.push_back( *it );
   } ;
   
    unsigned operator[] ( const unsigned i ) const 
   {
      assert( i < idxs.size() );
      return idxs[i] ;
   }
    unsigned size () const 
   {
      return idxs.size() ;
   }

    void write_coords( const vector<Vec3> & vertexes ) const 
   {
      for( unsigned iv= 0 ; iv < idxs.size() ; iv++ )
         cout << " " << vertexes[idxs[iv]]  << (iv < idxs.size()-1 ? " -- " : " ") ; 
   }
      
   
} ;

// **********************************************************************
// Class InPolMesh
// ---------------------------------------------------------------------- 

class IndPolMesh
{
   public:

   vector<Vec3>          vertexes ;
   vector<VertexIdxsSeq> polygons ;
   vector<Vec3>          pol_normals ;
   vector<Vec3>          pol_centers ;
   vector<Vec2u>         edges_verts ;  // for each edge, adyacent vertxes indexes
   vector<Vec2u>         edges_pols  ;  // for each edge, adyacent polygons indexes, or -1

   // ------------------------------------------------------------
   // init tables from 'vertexes' and 'polygons'

    void init_tables()
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

   // ------------------------------------------------------------
   // classify edges according to 'v' (view vector), using polygons normals
   // for each edge: 0 -> backfacing, 1 -> contour, 2--> front facing, 3 --> single adjacent polygon  

   void compute_edges_types( const Vec3 & v, std::vector<unsigned> & edges_types  ) const 
   {
      edges_types.clear();

      const unsigned n_pols = polygons.size() ;
      
      for( unsigned ie = 0 ; ie < edges_verts.size() ; ie++ )
      {

         const Vec2u & ap = edges_pols[ie] ; // adjacent polygons 

         unsigned type = 0 ; // --> back facing, by default
         if ( ap(1) == n_pols )
            type = 3 ;   // --> single adjacent polygon
         else 
         {
            const float 
               d0a = v.dot( pol_normals[ap(0)] ),
               d1a = v.dot( pol_normals[ap(1)] ),
               d0  = std::min( d0a, d1a ),
               d1  = std::max( d0a, d1a );

            if ( 0.0 < d0  )   // 0 < d0 <= d1 --> front facing  
               type = 2 ;
            else if ( 0.0 < d1 )  // d0 <= 0.0 < d1 --> contour
               type = 1 ;
         }
         edges_types.push_back( type );
      }
   }

   // ------------------------------------------------------------
   // draw filled front facing polygons 

   void draw_filled_ff_pols( const Vec3 & view_vec, const std::string &style  ) const 
   {
      cout << endl << "%% front facing polygons, filled" << endl ;
      for( unsigned ip = 0 ; ip < polygons.size() ; ip++ )
      if ( 0.0 < pol_normals[ip].dot( view_vec ) )
      {
         cout << "\\fill[" << style << "] " << endl ;
         polygons[ip].write_coords( vertexes ); 
         cout << " -- cycle ;" << endl << endl ;
      }
   }

   // ------------------------------------------------------------
   // draw filled front facing polygons 

   void draw_filled_shaded_ff_pols( const Vec3 & view_vec, const Vec3 & light_vec  ) const 
   {
      assert( pol_normals.size() == polygons.size() );
      const Vec3 light_n = light_vec.normalized() ;

      cout << endl << "%% front facing polygons, filled & shaded" << endl ;
      for( unsigned ip = 0 ; ip < polygons.size() ; ip++ )
      if ( 0.0 < pol_normals[ip].dot( view_vec ) )
      {
         const float d = std::max( 0.0f, light_n.dot( pol_normals[ip] ) ),
                     perc_f = std::trunc(100.0*(0.4+0.6*d)) ;
         cout << "\\fill[" << "white!" << unsigned(perc_f) << "!black,opacity=0.3" << "] " << endl ;
         polygons[ip].write_coords( vertexes ); 
         cout << " -- cycle ;" << endl << endl ;
      }
   }

   // ------------------------------------------------------------
   // draw edges, but only of a given type

   void draw_edges_type( const unsigned type, const std::string & style, const std::vector<unsigned> edges_types   ) const 
   {
      assert( type < 4 );

      cout << endl << "%% edges with type == " << type << endl ;
      for( unsigned ie = 0 ; ie < edges_verts.size() ; ie++ )
         if ( edges_types[ie] == type )
         {
            const Vec2u & ep = edges_pols[ie] ; // get adjacent polygons 
            const Vec3 &  v1 = vertexes[edges_verts[ie](0)],
                          v2 = vertexes[edges_verts[ie](1)] ;
            cout << "\\draw[" << style << "] " << v1 << " -- " << v2 << " ; " << endl ;
         }
   }
   // ------------------------------------------------------------
   // draw normals, usually for debugging, uses 'pol_centers' and 'pol_normals' 
   void draw_normals( const float len, const std::string & style  ) const 
   {
      assert( pol_centers.size() == polygons.size() );
      assert( pol_normals.size() == polygons.size() );

      cout << endl << "%% normals" << endl ;
      for( unsigned i = 0 ; i < polygons.size() ; i++ )
         cout << "\\draw[" << style << "] "  << " " << pol_centers[i] << " -- " << (pol_centers[i] + len*pol_normals[i]) << " ;" << endl ;
      
   }
   // ------------------------------------------------------------
   // draw the mesh by using a particular style, named as 'style 1'

   void draw_style_1( const Vec3 & view_vec ) const 
   {
      // classify edges according to 'v'
      std::vector<unsigned> edges_types ; // for each edge: 0 -> backfacing, 1 -> contour, 2--> front facing, 3 --> single adjacent polygon  
      compute_edges_types( view_vec, edges_types ) ;

      //fm.draw_normals( 0.4, "->,>=latex,line width=0.3mm,color=blue" );

      // draw frustum back-facing edges (dashed)
      draw_edges_type( 0, "line width=0.07mm,dashed", edges_types );      

      // draw frustum filled front-facing polygons
      //draw_filled_ff_pols( view_vec, "fill=gray,opacity=0.2" );
      draw_filled_shaded_ff_pols( view_vec, { 1.0f, 3.0f, 2.0f} );

      // draw frustum front facing and contour edges
      draw_edges_type( 2, "line width=0.10mm,color=black", edges_types ); // front facing edges
      draw_edges_type( 1, "line width=0.22mm,color=black", edges_types ); // contour edges (thicker)
   }

   // ------------------------------------------------------------
   // draw the mesh by using a particular style, named as 'style 2'

   void draw_style_2( const Vec3 & view_vec ) const 
   {
      // classify edges according to 'v'
      std::vector<unsigned> edges_types ; // for each edge: 0 -> backfacing, 1 -> contour, 2--> front facing, 3 --> single adjacent polygon  
      compute_edges_types( view_vec, edges_types ) ;

      //fm.draw_normals( 0.4, "->,>=latex,line width=0.3mm,color=blue" );

      // draw frustum back-facing edges (dashed)
      draw_edges_type( 0, "line width=0.07mm,dashed", edges_types );      

      // draw frustum filled front-facing polygons
      //draw_filled_ff_pols( view_vec, "fill=gray,opacity=0.2" );
      draw_filled_shaded_ff_pols( view_vec, { 1.0f, 3.0f, 2.0f} );

      // draw frustum front facing and contour edges
      draw_edges_type( 2, "line width=0.08mm,color=black", edges_types ); // front facing edges
      draw_edges_type( 1, "line width=0.08mm,color=black", edges_types ); // contour edges (thicker)
   }

    // ------------------------------------------------------------
   // draw the mesh by using a particular style, named as 'style 3'

   void draw_style_3( const Vec3 & view_vec ) const 
   {
      // classify edges according to 'v'
      std::vector<unsigned> edges_types ; // for each edge: 0 -> backfacing, 1 -> contour, 2--> front facing, 3 --> single adjacent polygon  
      compute_edges_types( view_vec, edges_types ) ;

      //fm.draw_normals( 0.4, "->,>=latex,line width=0.3mm,color=blue" );

      // draw frustum back-facing edges (dashed)
      //draw_edges_type( 0, "line width=0.07mm,dashed", edges_types );      

      // draw frustum filled front-facing polygons
      //draw_filled_ff_pols( view_vec, "fill=gray,opacity=0.2" );
      draw_filled_shaded_ff_pols( view_vec, { 1.0f, 3.0f, 2.0f} );

      // draw frustum front facing and contour edges
      draw_edges_type( 2, "line width=0.08mm,color=black", edges_types ); // front facing edges
      draw_edges_type( 1, "line width=0.08mm,color=black", edges_types ); // contour edges (thicker)
   }
   
} ;

// **********************************************************************
// Class InstancedMesh 
// ----------------------------------------------------------------------

class InstancedMesh : public IndPolMesh 
{
   public:
   InstancedMesh( const IndPolMesh orig, const Mat4 & mat )
   {

      for( unsigned iv = 0 ; iv < orig.vertexes.size() ; iv++ )
      {
         Vec3 vo   = orig.vertexes[iv] ;
         Vec4 vt   = mat * Vec4{ vo(X), vo(Y), vo(Z), 1.0 };
         const float w = vt(3) ;

         vertexes.push_back( (1.0f/w)*Vec3{ vt(X), vt(Y), vt(Z)} ) ;
      }
      for( unsigned ip = 0 ; ip < orig.polygons.size() ; ip++ )
         polygons.push_back( orig.polygons[ip] ) ;

      init_tables();
   }
} ;

// **********************************************************************
// Class frustum mesh
// ----------------------------------------------------------------------

class FrustumMesh : public IndPolMesh 
{
   public:
   FrustumMesh( const float l, const float r, 
                const float b, const float t,
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

      cout << "%%%%% frustum b = " << b << endl ;

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
         {4,5,7,6}, // far (back) polygon 
         {0,4,6,2}, // left side polygon 
         {0,1,5,4},  // bottom polygon 

         {0,2,3,1}, // near (front) plane polygon 
         {1,3,7,5}, // right side polygon 
         {2,6,7,3}, // top polygon 
      } ;

      // inits normals, edges, etc....
      init_tables();

   }

   
} ; // class frustum mesh 


// **********************************************************************
// Class cuboid mesh
// ----------------------------------------------------------------------

class CuboidMesh : public IndPolMesh 
{
   public:
   CuboidMesh(  const float x0, const float x1, 
                const float y0, const float y1,
                const float z0, const float z1   )
   {
      assert( x0 < x1 );
      assert( y0 < y1 );
      assert( z0 < z1 );

      vertexes =
      {  
         // vertexes on the near plane (on z==z1, the max value in Z)
         { x0, y0, z1 }, { x1, y0, z1 },
         { x0, y1, z1 }, { x1, y1, z1 },

         // vertexes on the far plane (on z==z0, the min value in Z)
         { x0, y0, z0 }, { x1, y0, z0 },
         { x0, y1, z0 }, { x1, y1, z0 },   
      };

      polygons = 
      {  
         {4,5,7,6}, // far (back) polygon 
         {0,4,6,2}, // left side polygon 
         {0,1,5,4},  // bottom polygon 

         {0,2,3,1}, // near (front) plane polygon 
         {1,3,7,5}, // right side polygon 
         {2,6,7,3}, // top polygon 
      } ;

      // inits normals, edges, etc....
      init_tables();
   }

   
} ; // class frustum mesh 

// **********************************************************************
// Class MurosCasita
// ----------------------------------------------------------------------

class MurosCasita : public IndPolMesh
{
   public:
   MurosCasita( const float f )
   {
      
      const float sx = 1.0, sy = 1.0, sz = 1.0 ;

      vertexes = 
      {
         { 0.0, 0.0, 0.0 }, { sx, 0.0, 0.0 }, { sx, sy, 0.0 }, { sx/2.0, sy*f, 0.0 }, { 0.0, sy, 0.0 },
         { 0.0, 0.0, sz  }, { sx, 0.0, sz  }, { sx, sy, sz  }, { sx/2.0, sy*f, sz  }, { 0.0, sy, sz  },
      } ;

      polygons = 
      {
         {0,1,2,3,4}, { 9,8,7,6,5},  // delantero, trasero
         {1,6,7,2},  {4,9,5,0},      // derecho, izquierdo
         {2,7,8,3},  {4,3,8,9},       // tejado derecho, tejado izquierdo
         {5,6,1,0} // suelo
      } ;

      init_tables();
   }

} ;

// **********************************************************************
// aux funcs
// ----------------------------------------------------------------------

void line( const Vec3 & org, const Vec3 & dest, const std::string & style, const std::string & end_node  )
{
   using namespace std ;
   cout << "\\draw[" << style << "]" << endl 
      << "         "<< org << " -- " << dest << " " << end_node << " ;" << endl ;
}

void disk( const Vec3 & center, const std::string & color, const std::string & style, const std::string & node )
{
   using namespace std ;
   cout << "\\fill[fill=" << color << "] " << center << " circle[" << style << "] "<< node << ";" << endl ;

}
// ----------------------------------------------------------------------

void axes( const std::string & subscript )
{
   const std::string lw = "line width=0.16mm" ;
   
   line( {0,0,0}, {1,0,0}, "->,>=latex,color=red," +lw, "node[right] {$\\vux_" + subscript + "$}" );
   line( {0,0,0}, {0,1,0}, "->,>=latex,color=green!50!black," +lw , "node[above] {$\\vuy_" + subscript + "$}" );
   line( {0,0,0}, {0,0,1}, "->,>=latex,color=blue," +lw , "node[above] {$\\vuz_" + subscript + "$}" );
   disk( Vec3{0.0,0.0,0.0}, "black", "radius=0.2mm", " node[anchor=north] {$\\pto_" + subscript + "$}" );
   //cout << "\\fill[fill=black] (0,0) circle [radius=0.11mm] node[below] {$\\pto_" + subscript + "$};" << endl ;
   
}

// ----------------------------------------------------------------------

void axes_z_neg( const std::string & subscript )
{
   const std::string lw = "line width=0.16mm" ;
   
   line( {0,0,0}, {1,0,0}, "->,>=latex,color=red," +lw, "node[below] {$\\vux_" + subscript + "$}" );
   line( {0,0,0}, {0,1,0}, "->,>=latex,color=green!50!black," +lw , "node[above] {$\\vuy_" + subscript + "$}" );
   line( {0,0,0}, {0,0,-1}, "->,>=latex,color=blue," +lw , "node[right] {$\\vuz_" + subscript + "$}" );
   disk( Vec3{0.0,0.0,0.0}, "black", "radius=0.2mm", " node[anchor=north] {$\\pto_" + subscript + "$}" );
   //cout << "\\fill[fill=black] (0,0) circle [radius=0.11mm] node[below] {$\\pto_" + subscript + "$};" << endl ;
   
}

// ----------------------------------------------------------------------


void define_isometric_proj( const Vec3 & view_vec_nn )
{
   const float lsq = view_vec_nn.lengthSq()  ;
   assert( lsq >  1e-2 );
    
   const Vec3   // camera coordinates axes, in world coordinates
      z_cam = view_vec_nn/ std::sqrtf( lsq ) ,
      x_cam = Vec3(0.0,1.0,0.0).cross( z_cam ).normalized() ,
      y_cam = z_cam.cross( x_cam ).normalized();
   
   cout 
      << "\\tikzset{isometric_proj/.style={" << endl 
      << "            x={(" << x_cam(0) << "cm," << y_cam(0) << "cm)}," << endl 
      << "            y={(" << x_cam(1) << "cm," << y_cam(1) << "cm)}," << endl
      << "            z={(" << x_cam(2) << "cm," << y_cam(2) << "cm)}"  << endl 
      << "}}" << endl ; 
}

} // end namespace utils 

#endif