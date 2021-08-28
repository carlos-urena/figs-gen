
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
      << "\\input{../src/header.tex}" << endl ;

   const auto cubo_cc  = CuboidMesh { -1.0, +1.0, -1.0, +1.0, -1.0, +1.0 };
   const auto view_vec = Vec3 { 0.72, 0.81, 1.3 };

   define_isometric_proj( view_vec );
   cout << "\\begin{tikzpicture}[scale=3,isometric_proj]" << endl ;

   cubo_cc.draw_style_2( view_vec );
   
   // // draw DC grid 
   // const unsigned nx = 8, ny = 8 ;

   // for( unsigned ix = 0 ; ix <= nx ; ix++ )
   // {
   //    const float cx = -1.0+2.0*(float(ix)/float(nx)) ;
   //    line( {cx,-1.0,+1.0}, {cx,+1.0,+1.0}, "line width=0.1mm,color=black", "" );
   // }
   // for( unsigned iy = 0 ; iy <= ny ; iy++ )
   // {
   //    const float cy = -1.0+2.0*(float(iy)/float(ny)) ;
   //    line( {-1.0,cy,+1.0}, {+1.0,cy,+1.0}, "line width=0.1mm,color=black", "" );
   // }

   // for( unsigned ix = 0 ; ix < nx ; ix++ )
   // for( unsigned iy = 0 ; iy < ny ; iy++ )
   // {
   //    const float cx = -1.0+2.0*((float(ix)+0.5)/float(nx)) ;
   //    const float cy = -1.0+2.0*((float(iy)+0.5)/float(ny)) ;
   //    disk( {cx,cy,1.0}, "gray", "radius=0.06mm", "" );
   // }
   
   
   // draw axes, no subscript
   axes_no_sub(  );

   disk( {-1.0,-1.0,1.0}, "blue", "radius=0.2mm", " node[anchor=north east] {$(-1,-1,+1)$}" );
   disk( {+1.0,-1.0,1.0}, "blue", "radius=0.2mm", " node[anchor=north west] {$(+1,-1,+1)$}" );
   disk( {-1.0,+1.0,1.0}, "blue", "radius=0.2mm", " node[anchor=south east] {$(-1,+1,+1)$}" );
   disk( {+1.0,+1.0,1.0}, "blue", "radius=0.2mm", " node[anchor=north west] {$(+1,+1,+1)$}" );

   disk( {-1.0,-1.0,-1.0}, "blue", "radius=0.2mm", " node[anchor=east]  {$(-1,-1,-1)$}" );
   disk( {-1.0,+1.0,-1.0}, "blue", "radius=0.2mm", " node[anchor=south] {$(-1,+1,-1)$}" );
   disk( {+1.0,+1.0,-1.0}, "blue", "radius=0.2mm", " node[anchor=west]  {$(+1,+1,-1)$}" );
   disk( {+1.0,-1.0,-1.0}, "blue", "radius=0.2mm", " node[anchor=west]  {$(+1,-1,-1)$}" );

   
   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}
