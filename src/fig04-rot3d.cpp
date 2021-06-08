
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

   const float 
      theta_deg = 35.0 ,
      theta_rad = theta_deg *M_PI/180.0 ,
      cos_theta = std::cos( theta_rad ),
      sin_theta = std::sin( theta_rad ) ;

   const Vec3 
      e = Vec3{ 0, 0.0, 1.0 }.normalized() ,
      s = 1.3f*Vec3( 0.6, 0.0, 1.3 ) ,
      v = e.cross( s ) ,
      u = -e.cross( v ) ,
      t = s-u,
      w = u*cos_theta + v*sin_theta ,
      theta_p = 0.6f*(u*cos(theta_rad/2.0) + v*sin(theta_rad/2.0)) ;

   cout
      << "\\tikzset{isometrico/.style={x={(0.7cm,-0.45cm)},   " << endl
      << "                             y={(0.0cm,0.95cm)},     " << endl
      << "                             z={(-0.7cm,-0.45cm)}}} " << endl
      << "\\begin{tikzpicture}[scale=2.5,isometrico]" << endl ;

   // rejilla en el plano XY
   // cout 
   //    << "   \\begin{scope}[color=gray!50, line width=0.08mm]"  << endl 
   //    << "        \\gridtresdxyii{1.1}" << endl 
   //    << "   \\end{scope}" << endl ;

   unsigned ns = 64 ;
   
   // arco desde u hasta v en rojo 
   cout << "   \\draw[color=red,line width=0.15mm]" << endl ;
   for( unsigned i = 0 ; i <= ns ; i++ )
   {  const float ang  = 0.5f*M_PI*float(i)/float(ns) ;
      const Vec3  vert = cos(ang)*u + sin( ang )*v ;
      cout << "      " << vert ;
      if ( i < ns ) cout << " -- " ;
      cout << endl ;
   }
   cout << "    ;" << endl;

   // angulo relleno correspondiente a theta
   ns = 16 ;
   const float theta_arc_rad = 0.4 ;
   cout << "   \\fill[fill=red,opacity=0.3]" << endl 
        << "         (0,0) -- " << endl ;
   for( unsigned i = 0 ; i <= ns ; i++ )
   {  const float ang  = theta_rad*float(i)/float(ns) ;
      const Vec3  vert = theta_arc_rad*(cos(ang)*u + sin( ang )*v) ;
      cout << "      " << vert << " -- " << endl ;
   }
   cout << "         cycle   ;" << endl;

   // arco correspondiente a theta
   ns= 16 ;
   cout << "   \\draw[->,>=latex,color=red,line width=0.2mm]" << endl ;
   for( unsigned i = 0 ; i <= ns ; i++ )
   {  const float ang  = theta_rad*float(i)/float(ns) ;
      const Vec3  vert = theta_arc_rad*(cos(ang)*u + sin( ang )*v) ;
      cout << "      " << vert ;
      if ( i < ns ) cout << " -- " ;
      cout << endl ;
   }
   cout << "         ;" << endl;

   // etiqueta 'theta'
   cout << "    \\path " << theta_p << " node[anchor=center] {$\\theta$} ;" << endl ; 

   cout

      // axis line
      << "   \\draw[color=gray,line width=0.1mm]" << endl 
      << "         " << -e << " -- " << 2.0f*e << "  ;" << endl 
      
      // vector 't'
      << "   \\draw[->,>=latex,color=blue,line width=0.2mm]" << endl 
      << "         (0,0,0) -- " << t << " node[above,anchor=south east] {$\\flw$} ;" << endl
      
      // vector 's'
      << "   \\draw[->,>=latex,color=black,line width=0.2mm]" << endl 
      << "         (0,0,0) -- " << s << " node[below,anchor=north] {$\\fls$} ;" << endl

      // vector 'v'
      << "   \\draw[->,>=latex,color=blue,line width=0.25mm]" << endl 
      << "         (0,0,0) -- " << v << " node[above,anchor=south west] {$\\flv$} ;" << endl 

      // vector 'u'
      << "   \\draw[->,>=latex,color=blue,line width=0.25mm]" << endl    
      << "         (0,0,0) -- " << u << " node[above,anchor=west] {$\\flu$} ;" << endl 

      // components of 'w'
      << "   \\draw[color=red,line width=0.12mm]" << endl 
      << "         (" << w(X) << ",0,0) -- " << w << ";" << endl
      << "   \\draw[color=red,line width=0.12mm]" << endl 
      << "         (0," << w(Y) << ",0) -- " << w << ";" << endl
      << "   \\draw[->,>=latex,color=red,line width=0.15mm]" << endl 
      << "         (0,0,0) -- (" << w(X) << ",0,0)  ;" << endl
      << "   \\draw[->,>=latex,color=red,line width=0.15mm]" << endl 
      << "         (0,0,0) -- (0," << w(Y) << ",0) ;" << endl

      // vector 'w'
      << "   \\draw[->,>=latex,color=blue,line width=0.25mm]" << endl 
      << "         (0,0,0) -- " << w << " node[right,anchor=west] {$\\flt\\,=\\,(\\cos\\theta)\\flu+(\\sin\\theta)\\flv$} ;" << endl
      
      // vector 'e'
      << "   \\draw[->,>=latex,color=black,line width=0.2mm]" << endl 
      << "         (0,0,0) -- " << e << " node[above,anchor=south] {$\\vue$} ;" << endl

      // components of 's'
      << "   \\draw[color=black!70,line width=0.1mm]" << endl 
      << "         " << t << " -- " << s << " ;" << endl
      << "   \\draw[color=black!70,line width=0.1mm]" << endl 
      << "         " << u << " -- " << s << " ;" << endl

      // expresion for the rotated vector (upper left)
      << "   \\path ( 0," << 1.5*v(Y) << ","<< t(Z) << ") " << endl 
      << "         node[anchor=center] {$\\begin{aligned} " << endl 
      << "             R_{\\theta}(\\fls)\\,&=\\,R_{\\theta}(\\flu+\\flw)\\\\" << endl
      << "                                  &=\\,R_{\\theta}(\\flu)+\\flw\\\\" << endl 
      << "                                  &=\\,\\flt+\\flw " << endl 
      << "         \\end{aligned}$};" << endl 
      // expresion for rotated vector (bottom right)
      << "   \\path "<< endl
      << "         (" << 1.3*s(X) << "," << s(Y) << "," << 0.8*s(Z) << ")" << endl 
      << "         node[right,anchor=west] " << endl
      << "         {$R_{\\theta}(\\fls)\\,=\\,(\\cos\\theta)\\flu+(\\sin\\theta)\\flv+\\flw$} ;" << endl ;

   disk( Vec3{0.0,0.0,0.0}, "black", "radius=0.2mm", " node[anchor=north] {$\\pto$}" );

   cout 
      << "\\end{tikzpicture}" << endl
      << endl ;

   cout 
      << "\\end{document}" << endl ;
}
