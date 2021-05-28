
#include <iostream>
#include <vec_mat.h>

using namespace std ;
using namespace vec_mat ;


int main( int argc, char *argv[] )
{
   using namespace std ;
   using namespace vec_mat ;

   cout 
      << "\\documentclass[border=1mm]{standalone}" << endl 
      << "\\input{header.tex}" << endl ;

   const float 
      theta_deg = 30.0 ,
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
      << "   \\begin{scope}[color=gray!50, line width=0.08mm]"  << endl 
      << "        \\gridtresdxyii{1.1}" << endl 
      << "   \\end{scope}"
      << "   \\draw[color=gray,line width=0.1mm]" << endl 
      << "         " << -e << " -- " << 2.0f*e << "  ;"
      << "   \\draw[->,>=latex,color=blue,line width=0.2mm]" << endl 
      << "         (0,0,0) -- " << t << " node[above,anchor=south east] {$\\fls-\\flu\\,=\\,\\flt$} ;" << endl
      << "   \\draw[->,>=latex,color=black,line width=0.2mm]" << endl 
      << "         (0,0,0) -- " << s << " node[below,anchor=north] {$\\fls$} ;" << endl
      << "   \\draw[->,>=latex,color=blue,line width=0.25mm]" << endl 
      << "         (0,0,0) -- " << v << " node[above,anchor=south west] {$\\flv\\,=\\,\\vue\\times\\fls$} ;" << endl 
      << "   \\draw[->,>=latex,color=blue,line width=0.25mm]" << endl 
      << "         (0,0,0) -- " << u << " node[above,anchor=west] {$\\flu\\,=\\,-\\vue\\times\\flv$} ;" << endl 
      << "   \\draw[->,>=latex,color=blue,line width=0.25mm]" << endl 
      << "         (0,0,0) -- " << w << " node[right,anchor=west] {$\\flw\\,=\\,(\\cos\\theta)\\flu+(\\sin\\theta)\\flv$} ;" << endl
      //<< "   \\draw[->,>=latex,color=red,line width=0.1mm]" << endl 
      //<< "         (0,0,0) -- " << v*sin_theta << " node[midway,left,anchor=east] {$(\\sin\\theta)\\flv$} ;" << endl
      << "   \\draw[->,>=latex,color=black,line width=0.2mm]" << endl 
      << "         (0,0,0) -- " << e << " node[above,anchor=south] {$\\vue$} ;" << endl
      << "   \\draw[color=black!70,line width=0.1mm]" << endl 
      << "         " << t << " -- " << s << " ;" << endl
      << "   \\draw[color=black!70,line width=0.1mm]" << endl 
      << "         " << u << " -- " << s << " ;" << endl
      << "   \\path ( 0," << 1.5*v(Y) << ","<< t(Z) << ") " << endl 
      << "         node[anchor=center] {$\\begin{aligned} " << endl 
      << "             R_{\\theta}(\\fls)\\,&=\\,R_{\\theta}(\\flt+\\flu)\\\\" << endl
      << "                                  &=\\,\\flt+R_{\\theta}(\\flu)\\\\" << endl 
      << "                                  &=\\,\\flt+\\flw " << endl 
      << "         \\end{aligned}$};" << endl
      << "   \\path "<< endl
      << "         (" << 1.3*s(X) << "," << s(Y) << "," << 0.8*s(Z) << ")" << endl 
      << "         node[right,anchor=west] " << endl
      << "         {$R_{\\theta}(\\fls)\\,=\\,\\fls+(\\cos\\theta-1)\\flu+(\\sin\\theta)\\flv$} ;" << endl 
      << "\\end{tikzpicture}" << endl
      << endl ;

   cout 
      << "\\end{document}" << endl ;
}
