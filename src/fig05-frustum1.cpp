
#include <initializer_list>
#include <string>
#include <vector>
#include <iostream>
#include <vec_mat.h>

#include <utils.h>


using namespace std ;
using namespace vec_mat ;
using namespace utils ;


// **********************************************************************
// main
// ----------------------------------------------------------------------

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
      n = 1.0,
      f = 3.0;
   auto  
      fm = FrustumMesh { l, r, b, t, n, f };
   const Vec3 
      view_vec = { 1, 1, 1 };

   cout
      << "\\definecolor{verde}{rgb}{0,0.3,0}" << endl 
      << "\\tikzset{isometrico/.style={x={(0.7cm,-0.45cm)},   " << endl
      << "                             y={(0.0cm,0.95cm)},     " << endl
      << "                             z={(-0.7cm,-0.45cm)}}} " << endl
      // << "\\tikzset{isometrico/.style={x={(0.0cm,-0.0cm)},   " << endl
      // << "                             y={(0.0cm,0.95cm)},     " << endl
      // << "                             z={(-1.0cm,0.0cm)}}} " << endl
      << "\\begin{tikzpicture}[scale=2.5,isometrico]" << endl ;

   // classify edges according to 'v'
   std::vector<unsigned> edges_types ; // for each edge: 0 -> backfacing, 1 -> contour, 2--> front facing, 3 --> single adjacent polygon  
   fm.compute_edges_types( view_vec, edges_types ) ;

   //fm.draw_normals( 0.4, "->,>=latex,line width=0.3mm,color=blue" );

   // draw frustum back-facing edges (dashed)
   fm.draw_edges_type( 0, "line width=0.07mm,dashed", edges_types );      

   // draw frustum filled front-facing polygons
   fm.draw_filled_ff_pols( view_vec, "fill=gray,opacity=0.2" );

   // draw frustum front facing and contour edges
   fm.draw_edges_type( 2, "line width=0.10mm,color=black", edges_types ); // front facing edges
   fm.draw_edges_type( 1, "line width=0.16mm,color=black", edges_types ); // contour edges (thicker)

   // draw line along Z- axis from origin to center of front face on the near plane
   line( {0,0,0}, {0,0,-n}, "line width=0.15mm,color=blue!50!red", "" );

   // draw axes
   axes();
   
   // draw projectors from origin towards frustum edges
   const std::string & st = "line width=0.05mm,color=gray" ;
   line( {0,0,0}, {l,t,-n}, st, "" );
   line( {0,0,0}, {r,t,-n}, st, "" );
   line( {0,0,0}, {l,b,-n}, st, "" );
   line( {0,0,0}, {r,b,-n}, st, "" );

   

   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}
