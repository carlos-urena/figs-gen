
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


   constexpr float 
      x0 =  2.5, x1 =  x0+1.0,
      y0 =  1.2, y1 =  y0+0.8,
      z0 =  0.0, z1 =  z0+2.0 ;

   const auto cubo_cc  = CuboidMesh { x0, x1, y0, y1, z0, z1 };
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
   
   
   // draw axes, Z axis negated, no subscript
   axes_z_neg_no_sub(  );

// draw vertex coords (with inverted Zs)
   disk( {x0,y0,z1}, "blue", "radius=0.2mm", " node[anchor=north east] {$(x_0,y_0,z_0)$}" );
   disk( {x1,y0,z1}, "blue", "radius=0.2mm", " node[anchor=north west] {$(x_1,y_0,z_0)$}" );
   disk( {x0,y1,z1}, "blue", "radius=0.2mm", " node[anchor=south east] {$(x_0,y_1,z_0)$}" );
   disk( {x1,y1,z1}, "blue", "radius=0.2mm", " node[anchor=north west] {$(x_1,y_1,z_0)$}" );

   disk( {x0,y0,z0}, "blue", "radius=0.2mm", " node[anchor=east]  {$(x_0,y_0,z_1)$}" );
   disk( {x0,y1,z0}, "blue", "radius=0.2mm", " node[anchor=south] {$(x_0,y_1,z_1)$}" );
   disk( {x1,y1,z0}, "blue", "radius=0.2mm", " node[anchor=west]  {$(x_1,y_1,z_1)$}" );
   disk( {x1,y0,z0}, "blue", "radius=0.2mm", " node[anchor=west]  {$(x_1,y_0,z_1)$}" );

   
   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}
