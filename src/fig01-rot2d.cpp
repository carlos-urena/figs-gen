
#include <iostream>
#include <vec_mat.h>

using namespace std ;
using namespace vec_mat ;


int main( int argc, char *argv[] )
{
   Vec2 pmin = { -0.37, -0.37 },
        pmax = {  2.67,  2.67 } ;


   cout
      << "\\begin{tikzpicture}" << endl
      << "\\draw[very thin,color=gray!20,step=0.25]"  << endl
      << "          " << pmin << " grid " << pmax << " ;" << endl
      << "\\end{tikzpicture}" << endl
      << endl ;
}
