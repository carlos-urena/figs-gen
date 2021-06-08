
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
      << "\\input{header.tex}" << endl ;

   const float 
      l = -0.3,    r = -l,
      b =  0.7*l,  t = -b ,
      n =  1.0,    f =  1.5;
   
   const auto fm       = FrustumMesh { l, r, b, t, n, f };
   const auto view_vec = Vec3 { 1, 1, 1 };

   cout
      << "\\definecolor{verde}{rgb}{0,0.3,0}" << endl 
      << "\\tikzset{isometrico/.style={x={(0.7cm,-0.45cm)},   " << endl
      << "                             y={(0.0cm,0.95cm)},     " << endl
      << "                             z={(-0.7cm,-0.45cm)}}} " << endl
      // << "\\tikzset{isometrico/.style={x={(0.0cm,-0.0cm)},   " << endl
      // << "                             y={(0.0cm,0.95cm)},     " << endl
      // << "                             z={(-1.0cm,0.0cm)}}} " << endl
      << "\\begin{tikzpicture}[scale=4,isometrico]" << endl ;

   fm.draw_style_2( view_vec );

   // draw line along Z- axis from origin to center of front face on the near plane
   //line( {0,0,0}, {0,0,-n}, "line width=0.15mm,color=blue!50!red", "" );

   // lines marking the width and heigth of frustum front face

   // filled triangle with 'beta' arc and bisectriz

   cout << "\\draw[color=black!70!white,line width=0.1mm] (" << l << ",0," << -n << ") -- (" << r << ",0," << -n << ") ;" << endl ;

   cout 
      << "\\fill[fill=white,opacity=0.7] "<< endl 
      << "       (0,0,0) " << endl 
      << "      -- " << Vec3 {0.0,b,-n} << endl 
      << "      -- " << Vec3 {0.0,t,-n} << endl 
      << "      -- cycle ;" << endl 
      << "\\draw[color=black!30!white,line width=0.1mm] (0,0,0) -- (0,0," << -n << ") -- (" << r << ",0," << -n << ") ;" << endl ;

   
   // width:
   line( {l,b,-n}, {l,b-0.4,-n}, "line width=0.07mm,dashed,color=blue", "" );
   line( {r,b,-n}, {r,b-0.4,-n}, "line width=0.07mm,dashed,color=blue", "" );
   line( {l,b-0.3,-n}, {r,b-0.3,-n}, "<->,>=latex,line width=0.15mm,color=blue", " node[fill=white,pos=0.5,anchor=center] {$2w$}" );
  
   // height
   line( {l-0.4,b,-n}, {l,b,-n}, "line width=0.07mm,dashed,color=blue", "" );
   line( {l-0.4,t,-n}, {l,t,-n}, "line width=0.07mm,dashed,color=blue", "" );
   line( {l-0.25,b,-n},{l-0.25,t,-n}, "<->,>=latex,line width=0.15mm,color=blue", " node[fill=white,pos=0.5,anchor=center] {$2h$}" );

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
        << "           w\\,&=\\,hr \\\\" << endl 
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
