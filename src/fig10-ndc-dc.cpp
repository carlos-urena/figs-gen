
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
   
   // draw DC grid 
   const unsigned nx = 6, ny = 6 ;

   for( unsigned ix = 0 ; ix <= nx ; ix++ )
   {
      const float cx = -1.0+2.0*(float(ix)/float(nx)) ;
      line( {cx,-1.0,+1.0}, {cx,+1.0,+1.0}, "line width=0.12mm,color=black", "" );
   }
   for( unsigned iy = 0 ; iy <= ny ; iy++ )
   {
      const float cy = -1.0+2.0*(float(iy)/float(ny)) ;
      line( {-1.0,cy,+1.0}, {+1.0,cy,+1.0}, "line width=0.12mm,color=black", "" );
   }

   for( unsigned ix = 0 ; ix < nx ; ix++ )
   for( unsigned iy = 0 ; iy < ny ; iy++ )
   {
      const float cx = -1.0+2.0*((float(ix)+0.5)/float(nx)) ;
      const float cy = -1.0+2.0*((float(iy)+0.5)/float(ny)) ;
      disk( {cx,cy,1.0}, "gray", "radius=0.06mm", "" );
   }
   
   
   // draw ndc axes
   //axes_z_neg( "{\\mbox{\\tiny\\!ndc}}" );

   // draw dc axes 
   const float lx = 2.0/nx, ly = 2.0/ny ;
   const std::string subscript = "{\\small\\mbox{\\!dc}}" ;
   const std::string lw = "line width=0.35mm" ;

   
   line( {-1.0,-1.0,1.0}, {-1.0+lx,-1.0,1.0}, "->,>=latex,color=red," +lw, "node[below] {\\huge$\\vux_" + subscript + "$}" );
   line( {-1.0,-1.0,1.0}, {-1.0,-1.0+ly,1.0}, "->,>=latex,color=green!50!black," +lw , "node[left] {\\huge$\\vuy_" + subscript + "$}" );
   line( {-1.0,-1.0,1.0}, {-1.0,-1.0,-1.0}, "->,>=latex,color=blue," +lw , "node[above right] {\\huge$\\vuz_" + subscript + "$}" );
   //disk( {-1.0,-1.0,1.0}, "black", "radius=0.2mm", " node[anchor=north east] {$\\pto_" + subscript + "$}" );


   disk( {-1.0,-1.0,1.0}, "blue", "radius=0.2mm", " node[anchor=north east] {\\large$(0,0,0)$}" );
   disk( {+1.0,-1.0,1.0}, "blue", "radius=0.2mm", " node[anchor=north west] {\\large$(n_x,0,0)$}" );
   disk( {-1.0,+1.0,1.0}, "blue", "radius=0.2mm", " node[anchor=south east] {\\large$(0,n_y,0)$}" );
   disk( {+1.0,+1.0,1.0}, "blue", "radius=0.2mm", " node[anchor=north west] {\\large$(n_x,n_y,0)$}" );

   disk( {-1.0,-1.0,-1.0}, "blue", "radius=0.2mm", "node[anchor=north west] {\\large$(0,0,1)$}" );
   disk( {-1.0,+1.0,-1.0}, "blue", "radius=0.2mm", "node[anchor=south] {\\large$(0,n_y,1)$}" );
   disk( {+1.0,+1.0,-1.0}, "blue", "radius=0.2mm", "node[anchor=west] {\\large$(n_x,n_y,1)$}" );
   disk( {+1.0,-1.0,-1.0}, "blue", "radius=0.2mm", "node[anchor=west] {\\large$(n_x,0,1)$}" );

   
   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}
