
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


   // attention point and viewplane normal
   const Vec3
      at = { 0.35, 0.0, 0.8 } ,
      n  = { -1.0, 0.15, 1.0 }, //{ -0.5, 0.3, 0.9 } ,
      u  = { 0.0, 0.7, 0.0 } ,
      uo = {-0.7,-0.1,0.0} ;  // point where 'u' is placed (u's origin )

   const Vec3 
      zec = n.normalized(),
      xec = u.cross( n ).normalized(),
      yec = zec.cross( xec ),
      oec = at + n ;


   // view matrix inverse
   const Mat4 
      view_mat_inv = Mat4_Columns(  xec, yec, zec, oec );

   // world coordinates frame and eye coordinates frame
   const Vec4 
      o_wc = { 0.0, 0.0, 0.0, 1.0 },
      x_wc = { 1.0, 0.0, 0.0, 0.0 },
      y_wc = { 0.0, 1.0, 0.0, 0.0 },
      z_wc = { 0.0, 0.0, 1.0, 0.0 },
      o_ec = view_mat_inv * o_wc,
      x_ec = view_mat_inv * x_wc,
      y_ec = view_mat_inv * y_wc,
      z_ec = view_mat_inv * z_wc;
      



   const auto 
      casita = InstancedMesh { MurosCasita {1.4},  Mat4_Translation( {0.2, 0.0, 0.2} )*Mat4_Scale( { 0.3, 0.5, 0.6} ) } ;

   // draw n vector and label 
   line( at, oec, "->,>=latex,color=magenta,line width=0.35mm", " ");
   const Vec3 pos = at+ 0.5f*n ;
   cout << "\\path " << pos << " node[below] {\\color{magenta}$\\fln$};" << endl ;

   // draw at point 
   disk( at, "magenta", "radius=0.2mm", " node[below] {\\color{magenta}$\\pta$}" ); 

   // draw u vector and label
   
   line( uo, uo+u, "->,>=latex,color=magenta,line width=0.35mm", " ");
   const Vec3 posu = uo + 0.5f*u ;
   cout << "\\path " << posu << " node[right] {\\color{magenta}$\\flu$};" << endl ;
   


   

   // settings for the axes
   std::string subscript = "{\\small\\mbox{wc}}" ;
   std::string lw = "line width=0.35mm" ;

   // draw WCC frame

   line( o_wc, x_wc, "->,>=latex,color=red," +lw, "node[right] {$\\vux_" + subscript + "$}" );
   line( o_wc, y_wc, "->,>=latex,color=green!50!black," +lw , "node[left] {$\\vuy_" + subscript + "$}" );
   line( o_wc, z_wc, "->,>=latex,color=blue," +lw , "node[above left] {$\\vuz_" + subscript + "$}" );
   disk( o_wc, "black", "radius=0.2mm", " node[below] {$\\pto_" + subscript + "$}" );

   // draw house ...
   casita.draw_style_1( view_vec );


   // draw a line through ECC frame's negative Z axe
   line( o_ec, o_ec-2.5f*z_ec, "dotted,color=magenta,line width=0.15mm",""); 

   // draw ECC frame
   subscript = "{\\small\\mbox{ec}}" ;
   line( o_ec, o_ec+x_ec, "->,>=latex,color=red," +lw, "node[right] {$\\vux_" + subscript + "$}" );
   line( o_ec, o_ec+y_ec, "->,>=latex,color=green!50!black," +lw , "node[above] {$\\vuy_" + subscript + "$}" );
   line( o_ec, o_ec+z_ec, "->,>=latex,color=blue," +lw , "node[left] {$\\vuz_" + subscript + "$}" );
   disk( o_ec, "black", "radius=0.2mm", " node[above left] {$\\pto_" + subscript + "$}" );

   
   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}