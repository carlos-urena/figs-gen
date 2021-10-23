
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

   const auto fm       = FrustumMesh { l, r, b, t, n, f };
   const auto view_vec = Vec3 { 1, 1, 1 };

   define_isometric_proj( view_vec );
   
   cout << "\\begin{tikzpicture}[scale=4,isometric_proj]" << endl ;

   fm.draw_style_1( view_vec );

   // draw line along Z- axis from origin to center of front face on the near plane
   line( {0,0,0}, {0,0,-n}, "line width=0.15mm,color=blue!50!red", "" );

   // draw axes
   //axes( "{\\mbox{c}}" );
   const std::string 
      lw        = "line width=0.3mm", 
      size      = "\\Large",
      subscript = "{\\small\\mbox{ec}}" ;
   
   line( {0,0,0}, {1,0,0}, "->,>=latex,color=red," +lw, "node[right] {" + size + "$\\vux_" + subscript + "$}" );
   line( {0,0,0}, {0,1,0}, "->,>=latex,color=green!50!black," +lw , "node[above] {" + size + "$\\vuy_" + subscript + "$}" );
   line( {0,0,0}, {0,0,1}, "->,>=latex,color=blue," +lw , "node[above left] {" + size + "$\\vuz_" + subscript + "$}" );
   disk( Vec3{0.0,0.0,0.0}, "black", "radius=0.2mm", " node[anchor=north] {" + size + "$\\pto_" + subscript + "$}" );

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

   cout << "\\path " << fm.vertexes[4] << " node[red,anchor=south west] {$(s\\cdot l,s\\cdot b,-f)$} ;" << endl ;
   cout << "\\path " << fm.vertexes[5] << " node[red,anchor=west]       {$(s\\cdot r,s\\cdot b,-f)$} ;" << endl ;
   cout << "\\path " << fm.vertexes[6] << " node[red,anchor=west]       {$(s\\cdot l,s\\cdot t,-f)$} ;" << endl ;
   cout << "\\path " << fm.vertexes[7] << " node[red,anchor=west]       {$(s\\cdot r,s\\cdot t,-f)$} ;" << endl ;

   cout << "\\path " << (fm.vertexes[5]+Vec3(0.0,-0.5,0.0)) << " node[anchor=east] {$s\\,=\\,f/n$} ;" << endl ;

   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}
