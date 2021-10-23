
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

   //const auto cubo_cc  = CuboidMesh { -1.0, +1.0, -1.0, +1.0, -1.0, +1.0 };
   const auto view_vec = Vec3 { 0.72, 0.81, 1.3 };

   define_isometric_proj( view_vec );
   cout << "\\begin{tikzpicture}[scale=3.5,isometric_proj]" << endl ;

   // view matrix
   // .....

   // draw EC axes 
   
   const std::string subscript = "{\\small\\mbox{ec}}" ;
   const std::string lw = "line width=0.35mm" ;

   
   line( {0.0,0.0,0.0}, {1.0,0.0,0.0}, "->,>=latex,color=red," +lw, "node[right] {$\\vux_" + subscript + "$}" );
   line( {0.0,0.0,0.0}, {0.0,1.0,0.0}, "->,>=latex,color=green!50!black," +lw , "node[above] {$\\vuy_" + subscript + "$}" );
   line( {0.0,0.0,0.0}, {0.0,0.0,1.0}, "->,>=latex,color=blue," +lw , "node[left] {$\\vuz_" + subscript + "$}" );
   disk( {0.0,0.0,0.0}, "black", "radius=0.2mm", " node[above left] {$\\pto_" + subscript + "$}" );

   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}