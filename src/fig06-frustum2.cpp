
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
      b =  0.7*l,
      t = -b ,
      n = 1.0,
      f = 2.0;
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
      << "\\begin{tikzpicture}[scale=4,isometrico]" << endl ;

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
   fm.draw_edges_type( 1, "line width=0.22mm,color=black", edges_types ); // contour edges (thicker)

   // draw line along Z- axis from origin to center of front face on the near plane
   line( {0,0,0}, {0,0,-n}, "line width=0.15mm,color=blue!50!red", "" );

   // draw axes
   axes( "{\\mbox{c}}" );
   
   // draw projectors from origin towards frustum edges
   const std::string & st = "line width=0.07mm,dashed,color=gray" ;
   line( {0,0,0}, {l,t,-n}, st, "" );
   line( {0,0,0}, {r,t,-n}, st, "" );
   line( {0,0,0}, {l,b,-n}, st, "" );
   line( {0,0,0}, {r,b,-n}, st, "" );

   
   
   for( auto &iv : {0,1,2,3} )
      cout << "\\fill[fill=blue] " << fm.vertexes[iv] << " circle [radius=0.15mm];" << endl ;

   for( auto &iv : {4,5,6,7} )
      cout << "\\fill[fill=red] " << fm.vertexes[iv] << " circle [radius=0.15mm];" << endl ;
  
   cout << endl << "%% labels" << endl ;

   cout << "\\path " << fm.vertexes[0] << " node[blue,anchor=east] {$(l,b,-n)$} ;" << endl ;
   cout << "\\path " << fm.vertexes[1] << " node[blue,anchor=north west] {$(r,b,-n)$} ;" << endl ;
   cout << "\\path " << fm.vertexes[2] << " node[blue,anchor=east] {$(l,t,-n)$} ;" << endl ;
   cout << "\\path " << fm.vertexes[3] << " node[blue,anchor=north west] {$(r,t,-n)$} ;" << endl ;

   cout << "\\path " << fm.vertexes[4] << " node[red,anchor=south west] {$(sl,sb,-f)$} ;" << endl ;
   cout << "\\path " << fm.vertexes[5] << " node[red,anchor=west] {$(sr,sb,-f)$} ;" << endl ;
   cout << "\\path " << fm.vertexes[6] << " node[red,anchor=west] {$(sl,st,-f)$} ;" << endl ;
   cout << "\\path " << fm.vertexes[7] << " node[red,anchor=west] {$(sr,st,-f)$} ;" << endl ;

   cout << "\\path " << (fm.vertexes[5]+Vec3(0.0,-0.5,0.0)) << " node[anchor=east] {$s\\,=\\,f/n$} ;" << endl ;

   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}
