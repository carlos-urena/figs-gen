
#include <iostream>
#include <vec_mat.h>


int main( int argc, char *argv[] )
{

   const char * tex = R"tex(
   \tikzisometrico
   \begin{tikzpicture}[scale=1.4,isometricXYZ]
      \ejesvi{0.8}{1.5}
      \casita
%%    \circulox{0.4}{1.2}  \path (1.2,0.0,0.0) node [above=.7cm,right=.3cm]{$\trota{\alpha,\vx}$};
      \circulox{0.4}{1.2}  \path (1.2,0.0,0.0) node  [above right=.3cm and .5cm]{$\trotax{\theta}$};
      \circuloy{0.4}{1.2}  \path (0.0,1.2,0.0) node [left=.6cm] {$\trotay{\theta}$} ;
      \circuloz{0.4}{1.2}  \path (0.0,0.0,1.2) node [above left=.3cm and .5cm] {$\trotaz{\theta}$} ;
   \end{tikzpicture}
   )tex";

   using namespace std ;
   cout << tex ;
}
