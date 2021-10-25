
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
      u  = { 0.0, 1.0, 0.0 } ;

   const Vec3 
      zec = n.normalized(),
      xec = u.cross( n ).normalized(),
      yec = zec.cross( xec ),
      oec = at + n ;


   // view matrix inverse
   const Mat4 
      view_mat_inv = Mat4_Columns(  xec, yec, zec, oec ),
      view_mat     = Mat4_Inverse( view_mat_inv );

   // world coordinates frame and eye coordinates frame
   const Vec4 
      x_wc = view_mat*Vec4( 1.0, 0.0, 0.0, 0.0 ),
      y_wc = view_mat*Vec4( 0.0, 1.0, 0.0, 0.0 ),
      z_wc = view_mat*Vec4( 0.0, 0.0, 1.0, 0.0 ),
      o_wc = view_mat*Vec4( 0.0, 0.0, 0.0, 1.0 ),

      o_ec = view_mat*Vec4( oec[0], oec[1], oec[2], 1.0 ),
      x_ec = view_mat*Vec4( xec[0], xec[1], xec[2], 0.0 ),
      y_ec = view_mat*Vec4( yec[0], yec[1], yec[2], 0.0 ),
      z_ec = view_mat*Vec4( zec[0], zec[1], zec[2], 0.0 ),

      at_ec4 = view_mat*Vec4( at[0], at[1], at[2], 1.0 ),
      n_ec4  = view_mat*Vec4( n[0], n[1], n[2], 0.0 ) ;

   const Vec3 
      at_ec = { at_ec4[0], at_ec4[1], at_ec4[2] },
      n_ec  = { n_ec4[0],  n_ec4[1],  n_ec4[2]  } ;

   

   const auto 
      casita = InstancedMesh { MurosCasita {1.4},  view_mat*Mat4_Translation( {0.2, 0.0, 0.2} )*Mat4_Scale( { 0.3, 0.5, 0.6} ) } ;

   // draw n vector 
   line( at_ec, at_ec + n_ec, "->,>=latex,color=magenta,line width=0.35mm", " ");
   // draw at point 
   disk( at_ec, "black", "radius=0.2mm", " node[below] {$\\pta$}" ); 

   // draw label for n vector 
   const Vec3 pos_ec = at_ec + 0.5f*n_ec ;
   cout << "\\path " << pos_ec << " node[below] {\\color{magenta}$\\fln$};" << endl ;
   

   // settings for the axes
   std::string subscript = "{\\small\\mbox{wc}}" ;
   std::string lw = "line width=0.35mm" ;

   // draw WCC frame

   line( o_wc, o_wc+x_wc, "->,>=latex,color=red," +lw, "node[right] {$\\vux_" + subscript + "$}" );
   line( o_wc, o_wc+y_wc, "->,>=latex,color=green!50!black," +lw , "node[above] {$\\vuy_" + subscript + "$}" );
   line( o_wc, o_wc+z_wc, "->,>=latex,color=blue," +lw , "node[left] {$\\vuz_" + subscript + "$}" );
   disk( o_wc, "black", "radius=0.2mm", " node[above left] {$\\pto_" + subscript + "$}" );

   // draw house ...
   casita.draw_style_1( view_vec );


   // draw a line through ECC frame's negative Z axe
   line( o_ec, o_ec-2.5f*z_ec, "dotted,color=magenta,line width=0.15mm",""); 

   // draw ECC frame
   subscript = "{\\small\\mbox{ec}}" ;
   line( o_ec, o_ec+x_ec, "->,>=latex,color=red," +lw, "node[right] {$\\vux_" + subscript + "$}" );
   line( o_ec, o_ec+y_ec, "->,>=latex,color=green!50!black," +lw , "node[left] {$\\vuy_" + subscript + "$}" );
   line( o_ec, o_ec+z_ec, "->,>=latex,color=blue," +lw , "node[left] {$\\vuz_" + subscript + "$}" );
   disk( o_ec, "black", "radius=0.2mm", " node[above left] {$\\pto_" + subscript + "$}" );

   
   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}