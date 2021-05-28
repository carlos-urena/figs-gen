
#include <iostream>
#include <vec_mat.h>


int main( int argc, char *argv[] )
{
   using namespace std ;
   using namespace vec_mat ;

   cout 
      << "\\documentclass[border=1mm]{standalone}" << endl 
      << "\\input{header.tex}" << endl ;
   
   const Vec2 
      u           = { 3.2, 1.4 } ,
      v           = { -u(Y), u(X) } ;
   const float 
      u_radius     = sqrt(u.lengthSq()) ,
      u_angle_deg  = atan2( u(Y), u(X) )*180.0/M_PI ;

   const Vec2  
      grid_pmin    = { -u(Y), 0.0 },
      grid_pmax    = { u(X), u(X) } ;
   
   cout
      << "\\begin{tikzpicture}" << endl
      << "\\draw[very thin,color=gray!30,step=0.2]"  << endl
      << "     " << grid_pmin << " grid " << grid_pmax << " ;" << endl
      << "\\draw[->,>=latex,color=red,line width=0.2mm] " << endl 
      << "      (0,0) -- (2,0)" << endl 
      << "      node[below,anchor=north] {$\\vux$} ;" << endl
      << "\\draw[->,>=latex,color=red,line width=0.2mm] " << endl 
      << "      (0,0) -- (0,2) " << endl
      << "      node[right, anchor=west] {$\\vuy$} ;" << endl
      << "\\draw[line width=0.2mm,color=blue]" << endl 
      << "      " << 0.2f*u << " -- " << 0.2f*(u+v) << " -- " << 0.2f*v << " ;" << endl 
      << "\\fill[fill=blue,opacity=0.1] " << endl 
      << "      (0,0) -- ("<< u(X) << ",0) -- " << u << " -- cycle ;" << endl 
      << "\\fill[fill=blue,opacity=0.1] " << endl 
      << "      (0,0) -- ( 0, "<< u(X) << ") -- " << v << " -- cycle ;" << endl 
      << "\\draw[color=gray!20,line width=0.2mm] " << endl 
      << "       +(" << u_angle_deg << ":"<< u_radius << ") " << endl 
      << "       arc[start angle=" << u_angle_deg << ", end angle=" << u_angle_deg+90.0 << ", radius=" << u_radius << "] ;" << endl 
      << "\\draw[->,>=latex,color=blue,line width=0.4mm] " << endl 
      << "      (0,0) " << endl 
      << "      -- ("<< u(X) << "," << u(Y) << ") " << endl 
      << "      node[right] {$\\flu\\,=\\,a\\vux\\,+\\,b\\vuy$} ;" << endl
      << "\\draw[->,>=latex,color=blue,line width=0.4mm] " << endl 
      << "      (0,0) " << endl 
      << "      -- ("<< -u(Y) << "," << u(X) << ") " << endl 
      << "      node[above, anchor=south west] {$\\,P(\\flu)\\,=\\,-b\\vux\\,+\\,a\\vuy$} ;" << endl
      
      << "\\end{tikzpicture}" << endl
      << endl ;

   cout 
      << "\\end{document}" << endl ;
}
