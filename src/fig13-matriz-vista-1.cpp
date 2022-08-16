
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
      



   const auto casita = InstancedMesh 
   {  
      MurosCasita {1.4}, 
      Mat4_Translation( {0.2, 0.0, 0.2} )*Mat4_Scale( { 0.3, 0.5, 0.6} ) 
   } ;

   
   constexpr float ccwx = 0.4, ccwy = 0.3, ccwz = 0.04 ;

   const auto camara_caja = InstancedMesh 
   {  
      CuboidMesh( -ccwx/2.0, +ccwx/2.0, -ccwy/2.0, +ccwy/2.0, 0.0, ccwz ), 
      view_mat_inv 
   } ;

   const float cfn = 0.3, s = 0.15 ;
   const auto  camara_frustum = InstancedMesh 
   {
      FrustumMesh( -s*cfn, +s*cfn, -s*cfn, +s*cfn, cfn, 0.5 ),
      view_mat_inv*Mat4_Translation( Vec3( 0.0, 0.0, cfn )) 
   } ;

    // draw grid in plane Y=0 for the WCC frame
   const unsigned nx = 20,  nz = 20 ;
   const float    wx = 1.0, wz = 1.0 ;

   for( unsigned ix = 0 ; ix < nx ; ix++ )
   {
      Vec4 p0 = o_wc + (wx*float(ix)/float(nx-1))*x_wc,
           p1 = p0   + wz*z_wc ;
      line( p0, p1, "color=white!80!black,line width=0.15mm","");
   }

   for( unsigned iz = 0 ; iz < nz ; iz++ )
   {
      Vec4 p0 = o_wc + (wz*float(iz)/float(nz-1))*z_wc,
           p1 = p0   + wx*x_wc ;
      line( p0, p1, "color=white!80!black,line width=0.15mm","");
   }

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

   // draw small camera at origin of eye coordinate frame
   camara_caja.draw_style_4( view_vec );
   camara_frustum.draw_style_4( view_vec );

   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}