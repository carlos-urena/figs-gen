
#include <iostream>
#include <vec_mat.h>



int main( int argc, char *argv[] )
{
   using namespace std ;
   using namespace vec_mat ;

   cout 
      << "\\documentclass[border=1mm]{standalone}" << endl 
      << "\\input{../src/header.tex}" << endl ;

   const float 
      radius      = 3.0 ,
      arc_radius  = 1.2 ,
      theta_deg   = 40 ,
      u_angle_deg = 15.0 ,
      theta_rad   = theta_deg*M_PI/180.0,
      radius_u    = radius*std::cos( theta_rad ),
      radius_v    = radius*std::sin( theta_rad ) ;
   
               
   const Vec2  
      pmin    = { -radius/3.0, -radius/3.0 },
      pmax    = {  radius+1.0,  radius+1.0 } ;
   


   cout
      << "\\begin{tikzpicture}" << endl
      << "%%\\draw[very thin,color=gray!20,step=0.25]"  << endl
      << "%%     " << pmin << " grid " << pmax << " ;" << endl
      << "\\draw[color=gray,line width=0.2mm] " << endl 
      << "       +(" << u_angle_deg << ":"<< radius << ") " << endl 
      << "       arc[start angle=" << u_angle_deg << ", end angle=" << u_angle_deg+90.0 << ", radius=" << radius << "] ;" << endl 
      << "\\draw[color=gray,dotted,line width=0.2mm] " << endl 
      << "       ("<< u_angle_deg << ":" << radius_u << ") " << endl 
      << "       -- (" << u_angle_deg+theta_deg << ":" << radius << ") ;" << endl 
      << "\\draw[color=gray,dotted,line width=0.2mm] " << endl 
      << "       ("<< (u_angle_deg+90.0) << ":" << radius_v << ") " << endl 
      << "       -- (" << u_angle_deg+theta_deg << ":" << radius << ") ;" << endl 
      << "\\fill[fill opacity=0.2,fill=blue] " << endl 
      << "       (0,0) " << endl 
      << "       -- +(" << u_angle_deg << ":" << arc_radius << ") arc[start angle=" << u_angle_deg << ", end angle=" << u_angle_deg+theta_deg << ", radius=" << arc_radius <<"]" << endl 
      << "       -- cycle ; " << endl 
      << "\\draw[color=blue,line width=0.1mm] " << endl 
      << "       +(" << u_angle_deg << ":"<< arc_radius << ") " << endl 
      << "       arc[start angle=" << u_angle_deg << ", end angle=" << u_angle_deg+theta_deg << ", radius=" << arc_radius << "] ;" << endl 
      << "\\path " << endl 
      << "       +("<< u_angle_deg + theta_deg/2.0 << ":" << arc_radius*0.7 << ") " << endl 
      << "       node[anchor=center] {$\\theta$} ;" << endl
      << "\\draw[->,>=latex,color=blue,line width=0.4mm] " << endl 
      << "      (0,0) " << endl 
      << "      -- +("<< u_angle_deg << ":" << radius << ") " << endl 
      << "      node[right] {$\\flu$} ;" << endl
      << "\\draw[->,>=latex,color=blue,line width=0.4mm] " << endl 
      << "      (0,0) " << endl 
      << "      --  +("<< (u_angle_deg+90.0) << ":" << radius << ")" << endl 
      << "      node[right, anchor=east] {$\\flv\\,=\\,P(\\flu)$} ;" << endl
      << "\\draw[->,>=latex,color=black,line width=0.4mm] " << endl 
      << "      (0,0) " << endl 
      << "      --  +("<< (u_angle_deg+theta_deg) << ":" << radius << ")" << endl 
      << "      node[anchor=south west] {$\\flt\\,=\\,(\\cos\\theta)\\flu\\,+\\,(\\sin\\theta)\\flv$} ;" << endl
      << "\\draw[->,>=latex,color=red,line width=0.2mm] " << endl 
      << "      (0,0) " << endl 
      << "       --  +("<< u_angle_deg << ":" << radius_u << ") " << endl 
      << "      node[midway, anchor=north] {$(\\cos\\theta)\\flu$} ;" << endl
      << "\\draw[->,>=latex,color=red,line width=0.2mm] " << endl 
      << "      (0,0) " << endl 
      << "       --  +("<< (u_angle_deg+90.0) << ":" << radius_v << ") " << endl 
      << "      node[midway, anchor=east] {$(\\sin\\theta)\\flv$} ;" << endl
     
      << "\\end{tikzpicture}" << endl
      << endl ;

   cout 
      << "\\end{document}" << endl ;
}
