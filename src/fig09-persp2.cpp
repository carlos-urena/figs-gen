
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

   const float 
      l = -0.3,   r = -l,
      b =  0.7*l, t = -b ,
      n = 1.0,    f = 2.0;

   const auto cubo_cc = CuboidMesh { -1.0, +1.0, -1.0, +1.0, -1.0, +1.0 };
   const auto mat      =  Mat4_Scale({1,1,-1}) *
                          Mat4_Frustum( l,r,b,t,n,f )*
                          Mat4_Translation( {-0.15, -0.2, -(n+f)/2.0 })*
                          Mat4_Scale({0.3,0.3,0.3}) ; 
   const auto muros_ca = InstancedMesh { MurosCasita {1.3},  mat } ;
   const auto view_vec = Vec3 { 1.0, 1.0, 0.5 };

   define_isometric_proj( view_vec );
   cout << "\\begin{tikzpicture}[scale=2,isometric_proj]" << endl ;

   muros_ca.draw_style_2( view_vec );
   cubo_cc.draw_style_2( view_vec );
   
   // draw line along Z- axis from origin to center of front face on the near plane
   line( {0,0,0}, {0,0,-n}, "line width=0.15mm,color=blue!50!red", "" );

   // draw axes
   axes_z_neg( "{\\mbox{\\tiny\\!cc}}" );
   
   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}
