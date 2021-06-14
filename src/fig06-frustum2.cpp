
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
      l = -0.3,    r = -l,
      b =  0.7*l,  t = -b ,
      n =  1.0,    f =  1.5;
   
   const auto fm       = FrustumMesh { l, r, b, t, n, f };
   const auto view_vec = Vec3 { 1, 1, 1 };

   define_isometric_proj( view_vec );

   // tikzpicture environment begins
   cout << "\\begin{tikzpicture}[scale=5,isometric_proj]" << endl ;

    // lines marking the half width and half height of frustum front face
   
   line( {0.0,t,-n}, {0.0,t+0.3,-n}, "line width=0.07mm,dashed,color=blue", "" );
   line( {r,t,-n},   {r,t+0.3,-n}, "line width=0.07mm,dashed,color=blue", "" );
   line( {0.0,t+0.2,-n}, {r,t+0.2,-n}, "<->,>=latex,line width=0.15mm,color=blue", " node[fill=white,pos=0.5,anchor=center] {$w$}" );
  
   line( {r,0.0,-n}, {r+0.3,0.0,-n}, "line width=0.07mm,dashed,color=blue", "" );
   line( {r,t,-n},   {r+0.3,t,-n}, "line width=0.07mm,dashed,color=blue", "" );
   line( {r+0.2,0.0,-n},{r+0.2,t,-n}, "<->,>=latex,line width=0.15mm,color=blue", " node[fill=white,pos=0.5,anchor=center] {$h$}" );
   
   fm.draw_style_3( view_vec );

   // filled triangle with 'beta' arc and bisectriz

   cout << "\\draw[color=black!70!white,line width=0.1mm] (" << l << ",0," << -n << ") -- (" << r << ",0," << -n << ") ;" << endl ;

   cout 
      << "\\fill[fill=white,opacity=0.7] "<< endl 
      << "       (0,0,0) " << endl 
      << "      -- " << Vec3 {0.0,b,-n} << endl 
      << "      -- " << Vec3 {0.0,t,-n} << endl 
      << "      -- cycle ;" << endl 
      << "\\draw[color=black!30!white,line width=0.1mm] (0,0,0) -- (0,0," << -n << ") -- (" << r << ",0," << -n << ") ;" << endl ;

  
   // angulo relleno correspondiente a hfovy
   const unsigned ns = 16 ;
   const float    hfovy_ang_rad = 2.0*std::atan2(0.5*(t-b),n) , 
                  hfovy_radius  = 0.5 ;

   cout << "   \\fill[fill=red,opacity=0.5]" << endl 
        << "         (0,0) -- " << endl ;
   for( unsigned i = 0 ; i <= ns ; i++ )
   {  const float ang  = hfovy_ang_rad*(-0.5+float(i)/float(ns)) ;
      const Vec3  vert = hfovy_radius*Vec3{ 0.0, std::sin(ang), -std::cos(ang)} ;
      cout << "      " << vert << " -- " << endl ;
   }
   cout << "         cycle   ;" << endl;

   //line( {0.0,0.0,0.0}, {0.0,0.0,-n}, "line width=0.15mm,color=red!50!blue", "" );

   // 'beta' (hfovy) label
   cout << "    \\path " << Vec3{0.0,0.0,-hfovy_radius*1.15} << " node[anchor=center] {$\\beta$};" << endl ; 

   // lines on sides (and in front) of hfovy arc 
   line( {0.0,0.0,0.0}, {0.0,b,-n}, "line width=0.15mm,color=black", "" );
   line( {0.0,0.0,0.0}, {0.0,t,-n}, "line width=0.15mm,color=black", "" );
   line( {0.0,b,-n}, {0.0,t,-n}, "line width=0.15mm,color=black", "" );

   // expresions for w,h,r,l,b,t .... ??

   cout << "     \\path " << Vec3{0.0,1.0,1.0} << endl 
        << "         node[anchor=center] {$\\begin{aligned}" << endl 
        << "           h\\,&=\\,n\\tan(\\beta/2) \\\\" << endl 
        << "           w\\,&=\\,h\\cdot a \\\\" << endl 
        << "           l\\,&=-w \\\\" << endl 
        << "           r\\,&=+w \\\\" << endl
        << "           b\\,&=-h \\\\" << endl
        << "           t\\,&=+h " << endl
        << "      \\end{aligned}$};" << endl ;



  

   // draw axes
   axes( "{\\mbox{c}}" );
   
   cout 
      << "\\end{tikzpicture}"
      << "\\end{document}" << endl ;
}
