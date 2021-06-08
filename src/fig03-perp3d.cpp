
#include <iostream>
#include <vec_mat.h>
#include <utils.h>

using namespace std ;
using namespace vec_mat ;
using namespace utils ;


int main( int argc, char *argv[] )
{
   using namespace std ;
   using namespace vec_mat ;

   cout 
      << "\\documentclass[border=1mm]{standalone}" << endl 
      << "\\input{header.tex}" << endl ;


   const Vec3 
      e = Vec3{ 0, 0.0, 1.0 }.normalized() ,
      s = 1.3f*Vec3( 0.6, 0.0, 1.3 ) ,
      v = e.cross( s ) ,
      u = -e.cross( v ) ,
      t = s-u ;

   cout
      << "\\definecolor{verde}{rgb}{0,0.3,0}" << endl 
      << "\\tikzset{isometrico/.style={x={(0.7cm,-0.45cm)},   " << endl
      << "                             y={(0.0cm,0.95cm)},     " << endl
      << "                             z={(-0.7cm,-0.45cm)}}} " << endl
      << "\\begin{tikzpicture}[scale=2.5,isometrico]" << endl ;

   cout 
      << "   \\draw[color=gray,line width=0.1mm]" << endl 
      << "         " << -e << " -- " << 2.0f*e << "  ;"
      << "   \\draw[->,>=latex,color=blue,line width=0.2mm]" << endl 
      << "         (0,0,0) -- " << t << " node[above,anchor=south east] {$\\flw$} ;" << endl
      << "   \\draw[->,>=latex,color=black,line width=0.2mm]" << endl 
      << "         (0,0,0) -- " << s << " node[near end,above,anchor=south east] {$\\fls$} ;" << endl
      << "   \\draw[->,>=latex,color=blue,line width=0.25mm]" << endl 
      << "         (0,0,0) -- " << v << endl 
      << "         node[right,anchor=west] {$\\flv\\,=\\,\\vue\\times\\fls\\,=\\,P_{\\vue}(\\fls)$} ;" << endl 
      << "   \\draw[->,>=latex,color=blue,line width=0.25mm]" << endl 
      << "         (0,0,0) -- " << u << " ;" << endl
      << "   \\path[color=blue] " << 0.95f*u << endl 
      << "         node[anchor=north west] {$\\begin{aligned} " << endl 
      << "               \\flu\\,&=\\,-\\vue\\times\\flv\\\\" << endl 
      << "                       &=\\,-P_{\\vue}^2(\\fls)\\\\" << endl 
      << "                       & \\color{verde}=\\,\\fls-(\\fls\\cdot\\vue)\\vue" << endl
      << "         \\end{aligned}$} ;" << endl 
      << "   \\draw[->,>=latex,color=black,line width=0.2mm]" << endl 
      << "         (0,0,0) -- " << e << " node[above,anchor=south] {$\\vue$} ;" << endl
      << "   \\draw[color=black!70,line width=0.1mm]" << endl 
      << "         " << t << " -- " << s << " ;" << endl
      << "   \\draw[color=black!70,line width=0.1mm]" << endl 
      << "         " << u << " -- " << s << " ;" << endl
      << "   \\path ( 0," << 1.5*v(Y) << ","<< t(Z) << ") " << endl 
      << "         node[anchor=center,color=blue] {$\\begin{aligned} " << endl 
      << "             \\flw\\,&=\\,\\fls-\\flu\\\\" << endl
      << "                     &=\\,\\fls+P_{\\vue}^2(\\fls)\\\\" << endl 
      << "                    & \\color{verde}=\\,(\\fls\\cdot\\vue)\\vue" << endl
      << "         \\end{aligned}$};" << endl ;
      
   disk( Vec3{0.0,0.0,0.0}, "black", "radius=0.2mm", " node[anchor=north] {$\\pto$}" );
   cout 
      << "\\end{tikzpicture}" << endl
      << endl ;

   cout 
      << "\\end{document}" << endl ;
}
