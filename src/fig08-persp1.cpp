
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
      n =  0.4,   f = 2.3;

   const auto frustum           = FrustumMesh { l, r, b, t, n, f };
   const auto instance_mat_1    = Mat4_Translation( {-0.15, -0.2, -n-0.3-0.1 })*
                                  Mat4_Scale({0.3,0.3,0.3}) ; 
   const auto instance_mat_2    = Mat4_Translation({0.0,0.0,-0.4})*instance_mat_1 ;
   const auto instance_mat_3    = Mat4_Translation({0.0,0.0,-0.4})*instance_mat_2 ;
   const auto instance_mat_4    = Mat4_Translation({0.0,0.0,-0.4})*instance_mat_3 ;
   const auto muros_ca_1        = InstancedMesh { MurosCasita {1.4},  instance_mat_1 } ;
   const auto muros_ca_2        = InstancedMesh { MurosCasita {1.4},  instance_mat_2 } ;
   const auto muros_ca_3        = InstancedMesh { MurosCasita {1.4},  instance_mat_3 } ;
   const auto muros_ca_4        = InstancedMesh { MurosCasita {1.4},  instance_mat_4 } ;

   // const auto view_vec          = Vec3 { 1.0, 0.6, 0.5 };
   const auto view_vec          = Vec3 { 1.0, 0.3, 0.2 };

   define_isometric_proj( view_vec );
   cout << "\\begin{tikzpicture}[scale=3,isometric_proj]" << endl ;

   muros_ca_1.draw_style_1( view_vec );
   muros_ca_2.draw_style_1( view_vec );
   muros_ca_3.draw_style_1( view_vec );
   muros_ca_4.draw_style_1( view_vec );

   frustum.draw_style_2( view_vec );
   
   //mc.draw_normals( 0.5, "->,>=latex,color=blue");

   // draw line along Z- axis from origin to center of front face on the near plane
   line( {0,0,0}, {0,0,-n}, "line width=0.15mm,color=blue!50!red", "" );

   // draw axes
   //axes( "{\\mbox{e}}" );

   const std::string lw = "line width=0.3mm", 
                     size      = "\\Large",
                     subscript =  "{\\small\\mbox{ec}}" ;
   
   line( {0,0,0}, {1,0,0}, "->,>=latex,color=red," +lw, "node[right] {" + size + "$\\vux_" + subscript + "$}" );
   line( {0,0,0}, {0,1,0}, "->,>=latex,color=green!50!black," +lw , "node[above] {" + size + "$\\vuy_" + subscript + "$}" );
   line( {0,0,0}, {0,0,1}, "->,>=latex,color=blue," +lw , "node[above] {" + size + "$\\vuz_" + subscript + "$}" );
   disk( Vec3{0.0,0.0,0.0}, "black", "radius=0.2mm", " node[anchor=south west] {" + size + "$\\pto_" + subscript + "$}" );
   //cout << "\\fill[fill=black] (0,0) circle [radius=0.11mm] node[below] {$\\pto_" + subscript + "$};" << endl ;
   
   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}
