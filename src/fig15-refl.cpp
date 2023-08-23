
#include <iostream>
#include <vec_mat.h>


int main( int argc, char *argv[] )
{
   using namespace std ;
   using namespace vec_mat ;

   cout 
      << "\\documentclass[border=1mm]{standalone}" << endl 
      << "\\input{../src/header.tex}" << endl ;
   
   const float scale = 1.8f ;
   const Vec2 
      p1   = { +1.1, +0.6 },  // right edge of plane line 
      u    = { -1.0, 0.3 } ,  // vector 'u' (to be transformed)

      p0   = -p1 ,                  // left edge of plane line
      pv   = (p1-p0).normalized() , // vector paralel to plane, normalized
      n    = Vec2( -pv(Y), pv(X) ), // normal to the plane, normalized

      w    = (u.dot(n))*n ,  // component of 'u' parallel to 'n'
      v    = u-w ,           // component of 'u' perpendicular to 'n'
      utr  = v-w ;           // u, transformed
      
   // const float 
   //    u_radius     = sqrt(u.lengthSq()) ,
   //    u_angle_deg  = atan2( u(Y), u(X) )*180.0/M_PI ;

   const float m = 0.5f ; // margin
   const Vec2  
      grid_pmin    = Vec2( -2.2, -1.5 ),
      grid_pmax    = Vec2( +1.4, +1.5 );
   
   cout
      // additional colors 
      << "\\definecolor{cuaverde}{rgb}{0.0,0.6,0.0}" << endl 

      // grid, from grid_pmin, hasta grid_pmax
      << "\\begin{tikzpicture}" << endl
      << "\\draw[very thin,color=gray!30,step=0.2]"  << endl
      << "     " << scale*grid_pmin << " grid " << scale*grid_pmax << " ;" << endl

      // dotted lines 
      << "\\draw[line width=0.2mm,color=gray!60,dotted]" << endl 
      << "      " << scale*u << " -- " << scale*w << " ;" << endl 
      << "\\draw[line width=0.2mm,color=gray!60,dotted]" << endl 
      << "      " << scale*u << " -- " << scale*utr << " ;" << endl 
      << "\\draw[line width=0.2mm,color=gray!60,dotted]" << endl 
      << "      " << scale*utr << " -- " << -1.0f*scale*w << " ;" << endl 

      
      // X and Y axes
      << "\\draw[->,>=latex,color=red,line width=0.2mm] " << endl 
      << "      (0,0) -- (" << scale << ",0)" << endl 
      << "      node[below,anchor=north] {$\\vux$} ;" << endl
      << "\\draw[->,>=latex,color=red,line width=0.2mm] " << endl 
      << "      (0,0) -- (0," << scale << ") " << endl
      << "      node[right, anchor=south] {$\\vuy$} ;" << endl

      // plane line  
      << "\\draw[line width=0.4mm,color=gray!80]" << endl 
      << "      " << (p0*scale) << " -- " << (p1*scale) << " node[anchor=south east] {$\\Pi$};" << endl 

      // extended line parallel to n 
      << "\\draw[line width=0.1mm,color=gray!70]" << endl 
      << "      " << (-0.5f*scale*n) << " -- " << (1.5f*scale*n) << ";" << endl 

      // n = normal vector to the plane 
      << "\\draw[->,>=latex,line width=0.4mm,color=black]" << endl 
      << "      (0,0) -- " << scale*n << " node[anchor=east] {$\\fln$};" << endl 

      // vector u (to be transformed)
      << "\\draw[->,>=latex,line width=0.3mm,color=blue]" << endl 
      << "      (0,0) -- " << scale*u << " node[anchor=east] {{\\color{cuaverde} $\\flv+\\flw$} $\\,=\\,\\flu$};" << endl 

      // vector u' (u transformed)
      << "\\draw[->,>=latex,line width=0.3mm,color=blue]" << endl 
      << "      (0,0) -- " << scale*utr << " node[anchor=north west] {$\\flu'\\,=\\,$ {\\color{cuaverde} $\\flv-\\flw$}};" << endl 

      // vector w  (component of u parallel to n)
      << "\\draw[->,>=latex,line width=0.1mm,color=cuaverde]" << endl 
      << "      (0,0) -- " << scale*w << " node[anchor=west] {$\\flw$};" << endl 

      // vector -w  (component of u parallel to n, negated)
      << "\\draw[->,>=latex,line width=0.1mm,color=cuaverde]" << endl 
      << "      (0,0) -- " << -1.0f*scale*w << " node[anchor=west] {$-\\flw$};" << endl 

      // vector v  (component of u perpend. to n)
      << "\\draw[->,>=latex,line width=0.1mm,color=cuaverde]" << endl 
      << "      (0,0) -- " << scale*v << " node[anchor=south] {$\\flv$};" << endl 

      // normal to the plane vector

      // << "\\draw[line width=0.2mm,color=blue]" << endl 
      // << "      " << 0.2f*u << " -- " << 0.2f*(u+v) << " -- " << 0.2f*v << " ;" << endl 
      // << "\\fill[fill=blue,opacity=0.1] " << endl 
      // << "      (0,0) -- ("<< u(X) << ",0) -- " << u << " -- cycle ;" << endl 
      // << "\\fill[fill=blue,opacity=0.1] " << endl 
      // << "      (0,0) -- ( 0, "<< u(X) << ") -- " << v << " -- cycle ;" << endl 
      // << "\\draw[color=gray!20,line width=0.2mm] " << endl 
      // << "       +(" << u_angle_deg << ":"<< u_radius << ") " << endl 
      // << "       arc[start angle=" << u_angle_deg << ", end angle=" << u_angle_deg+90.0 << ", radius=" << u_radius << "] ;" << endl 
      // << "\\draw[->,>=latex,color=blue,line width=0.4mm] " << endl 
      // << "      (0,0) " << endl 
      // << "      -- ("<< u(X) << "," << u(Y) << ") " << endl 
      // << "      node[right] {$\\flu\\,=\\,a\\vux\\,+\\,b\\vuy$} ;" << endl
      // << "\\draw[->,>=latex,color=blue,line width=0.4mm] " << endl 
      // << "      (0,0) " << endl 
      // << "      -- ("<< -u(Y) << "," << u(X) << ") " << endl 
      // << "      node[above, anchor=south west] {$\\,P(\\flu)\\,=\\,-b\\vux\\,+\\,a\\vuy$} ;" << endl
      
      << "\\end{tikzpicture}" << endl
      << endl ;

   cout 
      << "\\end{document}" << endl ;
}
