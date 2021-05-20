// *********************************************************************
// **
// ** Template classes for small vectors and matrices
// ** Copyright (C) 2014 Carlos Ureña
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
//


#ifndef FIGS_GEN_VECMAT_H
#define FIGS_GEN_VECMAT_H

#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751
#endif

namespace figs_gen 
{
    
// constantes para acceder a las componentes de las tuplas
const unsigned
   X = 0,
   Y = 1,
   Z = 2,

   R = 0,
   G = 1,
   B = 2 ;

// definir alias de 'unsigned int' cuyo descriptor tiene un solo token
typedef unsigned int uint ;


// *********************************************************************
//
// plantilla de clase: TuplaG
// clase para tuplas de valores numéricos (genéricas)
// 
// parámetros: 
//    T - tipo de los valores numéricos (float, double, int, unsigned, etc...)
//    n - número de valores
//
// *********************************************************************

template< class T, unsigned n >
class TuplaG
{
   private:
   T coo[n] ;  // vector de valores escalares

   public:
   // constructor por defecto: no hace nada
   inline TuplaG();

   // constructor usando un array C++
   inline TuplaG( const T * org ) ;

   // acceso de lectura/escritura a un elemento (v[i]=x, x=v[i])
   //T & operator [] (const unsigned i) ;

   // acceso de solo lectura a un elemento ( x=v(i) )
   const T & operator () (const unsigned i) const ;

   // acceso de lectura-escritura a un elemento ( v(i)=x )
   T & operator () (const unsigned i) ;

   // conversion a un puntero de lectura/escritura de tipo T* ( T* p = tupla )
   operator  T * ()  ;

   // conversion a un puntero de solo lectura de tipo: const  T* ( const T* p = tupla )
   operator  const T * ()  const ;

   // suma componente a componente ( v1=v2+v3 )
   TuplaG<T,n> operator + ( const TuplaG & der ) const ;

   // resta componente a componente ( v1=v2-v3 )
   TuplaG<T,n> operator - ( const TuplaG & der ) const ;

   // devuelve tupla negada ( v1 = -v2 )
   TuplaG<T,n> operator - (  ) const ;

   // mult. por escalar por la derecha ( v1=v2*a )
   TuplaG<T,n> operator * ( const T & a ) const ;

   // division por escalar ( v1=v2/a )
   TuplaG<T,n> operator / ( const T & a ) const ;

   // producto escalar (dot)  a = v1.dot(v2)
   T dot( const TuplaG<T,n> & v2 ) const ;

   // operador binario para producto escalar a = v1|v2 ;
   T operator | ( const TuplaG & der ) const ;

   // obtener longitud al cuadrado
   T lengthSq( ) const ;

   // obtener una copia normalizada
   TuplaG<T,n> normalized() const ;
} ;

//----------------------------------------------------------------------
// non-member functions and operators

// mult. por escalar por la izquierda ( v1=a*v2 )
template< class T, unsigned n >
inline TuplaG<T,n> operator *  ( const T & a, const  TuplaG<T,n> & der ) ;

// escritura de un vector en un ostream
template< class T, unsigned n >
inline std::ostream & operator <<  ( std::ostream & os, const TuplaG<T,n> & der ) ;

// *********************************************************************
//
// Plantilla de clase: TuplaG2
// especialización parcial para tuplas de 2 elementos
// (define constructores específicos)
//
// *********************************************************************

template< class T >
class TuplaG2 : public TuplaG<T,2>
{
   public:

   // constructores: por defecto
   TuplaG2() ;
   TuplaG2( const T & c0, const T & c1 ) ;
   TuplaG2( const TuplaG<T,2> & ini );
   void operator = ( const TuplaG<T,2> & der ) ;
} ;



// *********************************************************************
//
// Plantilla de clase: TuplaG3
// especialización parcial para tuplas de 3 elementos
// (define constructores específicos)
//
// *********************************************************************

template< class T >
class TuplaG3 : public TuplaG<T,3>
{
   public:

   // constructores: por defecto
   TuplaG3() ;
   TuplaG3( const T & c0, const T & c1, const T & c2 ) ;
   TuplaG3( const TuplaG<T,3> & ini );
   void operator = ( const TuplaG<T,3> & der ) ;
   void operator = ( const TuplaG<T,4> & der ) ; // asignar ignorando ultimo

   // producto vectorial (cross)  a = v1.cross(v2)
   TuplaG3<T> cross( const TuplaG3<T> & v2 ) const ;
} ;


// *********************************************************************
//
// Plantilla de clase: TuplaG4
// especialización parcial para tuplas de 4 elementos
// (define constructores específicos)
//
// *********************************************************************

template< class T >
class TuplaG4 : public TuplaG<T,4>
{
   public:

   // constructores: por defecto
   TuplaG4() ;
   TuplaG4( const T & c0, const T & c1, const T & c2, const T & c3 ) ;
   TuplaG4( const TuplaG<T,4> & ini );
   void operator = ( const TuplaG<T,4> & der ) ;
} ;

// *********************************************************************
//
// plantilla de clase: MatrizCG
// clase para matrices cuadradas genéricas
//
// *********************************************************************

template< class T, unsigned n >
class MatrizCG
{
   public:
   TuplaG< TuplaG<T,n>, n > mat ;

   MatrizCG<T,n> ()  {}  // constructor por defecto inline (no inicializa)

   // conversion a un puntero de lectura/escritura de tipo: T*
   // ( T* p = matriz )
   inline operator  T * ()  ;

   // conversion a un puntero de solo lectura de tipo: const T*
   // ( const T* p = matriz )
   inline operator  const T * ()  const ;

   // acceso de lectura a una fila
   // (devuelve puntero al primer elemento de una columna)
   //inline const TuplaG<T,n> & operator() ( const unsigned i ) const ;

   // acceso de lectura/escritura a una fila:
   //inline TuplaG<T,n> & operator[] ( int i )  ;

   // componer esta matriz con otra por la derecha
   inline MatrizCG<T,n> operator * ( const MatrizCG<T,n> & der ) const ;

   // acceso de solo lectura usando fila,columna: T x = m(fil,col)
   inline const T & operator()( const unsigned fil, const unsigned col ) const ;

   // acceso de lectura/escritura usando fila,columna: T x = m(fil,col)
   inline T & operator()( const unsigned fil, const unsigned col )  ;

   // multiplicar esta matriz por una tupla por la derecha
   inline TuplaG<T,n> operator * ( const TuplaG<T,n>  & t ) const ;

   // multiplicar esta matriz por una tupla por la derecha (con una dimesnión menos)
   // (se añade un 1, se multiplica, y luego se le quita la ultima componente)
   inline TuplaG<T,n-1> operator * ( const TuplaG<T,n-1>  & t ) const ;
} ;

// escritura de una matriz en un ostream
template< class T, unsigned n > inline
std::ostream & operator <<  ( std::ostream & os, const MatrizCG<T,n> & m ) ;





// *********************************************************************
// tipos concretos:

typedef TuplaG2<float>  Tupla2f ;
typedef TuplaG2<double> Tupla2d ;
typedef TuplaG2<uint>   Tupla2u ;
typedef TuplaG2<int>    Tupla2i ;

typedef TuplaG3<float>  Tupla3f ;
typedef TuplaG3<double> Tupla3d ;
typedef TuplaG3<uint>   Tupla3u ;
typedef TuplaG3<int>    Tupla3i ;

typedef TuplaG4<float>  Tupla4f ;
typedef TuplaG4<double> Tupla4d ;
typedef TuplaG4<int>    Tupla4i ;
typedef TuplaG4<uint>   Tupla4u ;

typedef MatrizCG<float,4>  Matriz4f ;
typedef MatrizCG<double,4> Matriz4d ;

// *********************************************************************
// inline implementations

// *********************************************************************
// plantilla de clase:
// TuplaG<T,n>
// *********************************************************************

template< class T, unsigned n> inline
TuplaG<T,n>::TuplaG()
{
   
} 

// constructor usando un array C++
template< class T, unsigned n> inline 
TuplaG<T,n>::TuplaG( const T * org ) 
{
   for( unsigned i = 0 ; i < n ; i++ )
      (*this)[i] = org[i] ;
}

//----------------------------------------------------------------------

//template< class T, unsigned n >
//T & TuplaG<T,n>::operator [] (const unsigned i)
//{
   //assert( i < n ) ;
   //return coo[i] ;
//}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
const T & TuplaG<T,n>::operator () (const unsigned i) const
{
   assert( i < n ) ;
   return coo[i] ;
}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
T & TuplaG<T,n>::operator () (const unsigned i) 
{
   assert( i < n ) ;
   return coo[i] ;
}

//----------------------------------------------------------------------
// conversion a un puntero de lectura/escritura de tipo: T* ( T* p = tupla )

template< class T, unsigned n > inline 
TuplaG<T,n>::operator  T * () 
{
   return coo ;
}

//----------------------------------------------------------------------
// conversion a un puntero de solo lectura de tipo T* ( const T* p = tupla )

template< class T, unsigned n > inline 
TuplaG<T,n>::operator  const T * () const 
{
   return coo ;
}

//----------------------------------------------------------------------

template< class T, unsigned n > inline 
TuplaG<T,n> TuplaG<T,n>::operator + ( const TuplaG<T,n> & der ) const
{
   TuplaG<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = (*this)(i)+der(i) ;
   return res ;
}

//----------------------------------------------------------------------

template< class T, unsigned n > inline 
TuplaG<T,n> TuplaG<T,n>::operator - ( const TuplaG<T,n> & der ) const
{
   TuplaG<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = (*this)(i)-der(i) ;
   return res ;
}

//----------------------------------------------------------------------

// devuelve tupla negada ( v1 = -v2 )
template< class T, unsigned n > inline
TuplaG<T,n> TuplaG<T,n>::operator - (  ) const 
{
   TuplaG<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = -(*this)(i) ;
   return res ;
   
}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
TuplaG<T,n> TuplaG<T,n>::operator * ( const T & a ) const 
{
   TuplaG<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = (*this)(i)*a ;
   return res ;
}

//----------------------------------------------------------------------

template< class T, unsigned n >  inline
TuplaG<T,n> TuplaG<T,n>::operator / ( const T & a ) const 
{
   TuplaG<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = (*this)(i)/a ;
   return res ;
}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
TuplaG<T,n> operator * ( const T & a, const TuplaG<T,n> & der )  
{
   TuplaG<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = a*der(i) ;
   return res ;
}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
std::ostream & operator <<  ( std::ostream & os, const TuplaG<T,n> & der ) 
{
   os << "(" ;
   for( unsigned i = 0 ; i < n ; i++ )
   {  os << der(i) ;
      if ( i+1 < n ) 
         os << "," ;
   }
   os << ")" ;
   return os ;   
}

//----------------------------------------------------------------------

// producto escalar (dot)  a = v1.dot(v2)
template< class T, unsigned n > inline
T TuplaG<T,n>::dot( const TuplaG<T,n> & v2 ) const 
{
   double res = 0.0 ;
   for( unsigned int i = 0 ; i < n ; i++ )
      res += double((*this)(i)) * double(v2(i)) ;
   return T(res) ;
}

//----------------------------------------------------------------------

// obtener longitud al cuadrado
template< class T, unsigned n > inline
T TuplaG<T,n>::lengthSq( ) const 
{
   return T( this->dot( *this ) ) ;
}

//----------------------------------------------------------------------
// operador binario para producto escalar

template< class T, unsigned n > inline
T TuplaG<T,n>::operator | ( const TuplaG & der ) const 
{
   return this->dot( der ) ;
}

// ---------------------------------------------------------------------

template< class T, unsigned n > inline
TuplaG<T,n> TuplaG<T,n>::normalized() const 
{
   T lenSq = T(0.0) ;
   for( unsigned i = 0 ; i < n ; i++ )
      lenSq += (*this)(i) * (*this)(i) ;
   
   if ( ! ( lenSq > 0.0 ) )
   {  using namespace std ;
      cout << "lenSq == " << lenSq << endl << flush ;
   }
   
   assert( lenSq > 0.0 ) ;
   
   return (*this)*(T(1.0/sqrt(double(lenSq)))) ;
   
}

// *********************************************************************
// plantilla de clase:
//
//   TuplaG2<T>
// *********************************************************************

template< class T > inline
TuplaG2<T>::TuplaG2(  ) 
{

}

// ---------------------------------------------------------------------

template< class T > inline
TuplaG2<T>::TuplaG2( const TuplaG<T,2> & ini )
{
   (*this)[0] = ini(0) ;
   (*this)[1] = ini(1) ;
}

// ---------------------------------------------------------------------

template< class T > inline
void TuplaG2<T>::operator = ( const TuplaG<T,2> & der ) 
{
   (*this)[0] = der(0) ;
   (*this)[1] = der(1) ;
}

// ---------------------------------------------------------------------

template< class T > inline
TuplaG2<T>::TuplaG2( const T & c0, const T & c1 ) 
{
   (*this)[0] = c0 ;
   (*this)[1] = c1 ;
}

// *********************************************************************
//
// plantilla de clase:
// TuplaG3<T>
//
// *********************************************************************

template< class T > inline
TuplaG3<T>::TuplaG3(  ) 
{

}

// ---------------------------------------------------------------------

template< class T > inline
TuplaG3<T>::TuplaG3( const TuplaG<T,3> & ini )
{
   (*this)[0] = ini(0) ;
   (*this)[1] = ini(1) ;
   (*this)[2] = ini(2) ;
}

// ---------------------------------------------------------------------

template< class T > inline
void TuplaG3<T>::operator = ( const TuplaG<T,3> & der ) 
{
   (*this)[0] = der(0) ;
   (*this)[1] = der(1) ;
   (*this)[2] = der(2) ;
}

// ---------------------------------------------------------------------

template< class T > inline
void TuplaG3<T>::operator = ( const TuplaG<T,4> & der ) 
{
   (*this)[0] = der(0) ;
   (*this)[1] = der(1) ;
   (*this)[2] = der(2) ;
}

// ---------------------------------------------------------------------

template< class T > inline
TuplaG3<T>::TuplaG3( const T & c0, const T & c1, const T & c2 ) 
{
   (*this)[0] = c0 ;
   (*this)[1] = c1 ;
   (*this)[2] = c2 ;
}

// ---------------------------------------------------------------------


template< class T > inline
TuplaG3<T> TuplaG3<T>::cross( const TuplaG3<T> & v2 ) const 
{
   // cuidado: no hay acceso a 'coo' tal cual, mirar:
   // http://stackoverflow.com/questions/7281072/accessing-public-members-of-base-class-fails
   
   return TuplaG3<T>(  (*this)(1)*v2(2) -  (*this)(2)*v2(1),
                       (*this)(2)*v2(0) -  (*this)(0)*v2(2), 
                       (*this)(0)*v2(1) -  (*this)(1)*v2(0)
                     );
}

// *********************************************************************
// plantilla de clase:
//
//   TuplaG4<T>
//
// *********************************************************************

template< class T > inline
TuplaG4<T>::TuplaG4(  ) 
{

}

// ---------------------------------------------------------------------

template< class T > inline
TuplaG4<T>::TuplaG4( const TuplaG<T,4> & ini )
{
   (*this)[0] = ini(0) ;
   (*this)[1] = ini(1) ;
   (*this)[2] = ini(2) ;
   (*this)[3] = ini(3) ;
}

// ---------------------------------------------------------------------

template< class T > inline
void TuplaG4<T>::operator = ( const TuplaG<T,4> & der ) 
{
   (*this)[0] = der(0) ;
   (*this)[1] = der(1) ;
   (*this)[2] = der(2) ;
   (*this)[3] = der(3) ;
}

// ---------------------------------------------------------------------

template< class T > inline
TuplaG4<T>::TuplaG4( const T& c0, const T& c1, const T& c2, const T& c3 ) 
{
   (*this)[0] = c0 ;
   (*this)[1] = c1 ;
   (*this)[2] = c2 ;
   (*this)[3] = c3 ;
}


// *******
//#include "matrizg_impl.h"


// ---------------------------------------------------------------------
// conversion a un puntero de lectura/escritura de tipo T* ( T* p = m )
// (devuelve puntero al primer elemento de la primera columna)
template< class T, unsigned n > inline
MatrizCG<T,n>::operator  T * ()
{
   return mat[0] ;
}

// ---------------------------------------------------------------------
// conversion a un puntero de solo lectura de tipo: const T* ( T* p = m )
// (devuelve puntero al primer elemento de la primera columna)
template< class T, unsigned n > inline
MatrizCG<T,n>::operator  const T * ()  const
{
   return & (mat(0)(0)) ;
}

//// ---------------------------------------------------------------------
//// acceso de lectura a una fila:
//template< class T, unsigned n > inline
//const TuplaG<T,n> & MatrizCG<T,n>::operator() ( const unsigned i ) const
//{
   //return mat(i) ;
//}

////----------------------------------------------------------------------

//template< class T, unsigned n > inline
//TuplaG<T,n> & MatrizCG<T,n>::operator[] ( int i )
//{
   //return mat[i] ;
//}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
std::ostream & operator <<  ( std::ostream & os, const MatrizCG<T,n> & m )
{
   using namespace std ;

   ios estado_anterior( nullptr );
   estado_anterior.copyfmt( cout );
   cout << fixed << setprecision(9) ;

   const char * izq = "/||\\", * der = "\\||/" ;
   using namespace std ;
   for( unsigned fil = 0 ; fil < n ; fil++ )
   {  os << izq[fil] << " " ;
      for( unsigned col = 0 ; col < n ; col++ )
      {   os << setw(15) << m(fil,col) ;
          if ( col < n-1 ) os << " , " ;
      }
      os << " " << der[fil] << endl ;
   }

   cout.copyfmt( estado_anterior );
   return os ;
}

//----------------------------------------------------------------------
// componer una matriz con otra por la derecha

template< class T, unsigned n > inline
MatrizCG<T,n> MatrizCG<T,n>::operator * ( const MatrizCG<T,n> & der ) const
{
   MatrizCG<T,n> res ;

   for( unsigned fil = 0 ; fil < n ; fil++ )
   for( unsigned col = 0 ; col < n ; col++ )
   {  res(fil,col) = 0.0f ;
      for( unsigned k = 0 ; k < n ; k++ )
         res(fil,col) += (*this)(fil,k)*der(k,col) ;
   }
   return res ;
}

// ---------------------------------------------------------------------
// acceso de solo lectura usando fila,columna: T x = m(fil,col)

template< class T, unsigned n > inline
const T & MatrizCG<T,n>::operator()( const unsigned fil, const unsigned col ) const
{
   assert( fil < n );
   assert( col < n ) ;
   return mat(col)(fil) ;
}


// ---------------------------------------------------------------------
// acceso de lectura/escritura usando fila,columna: m(fil,col) = v

template< class T, unsigned n > inline
T & MatrizCG<T,n>::operator()( const unsigned fil, const unsigned col )
{
   assert( fil < n );
   assert( col < n ) ;
   return mat(col)(fil) ;
}

// ---------------------------------------------------------------------
// multiplicar esta matriz por una tupla por la derecha
template< class T, unsigned n > inline
TuplaG<T,n> MatrizCG<T,n>::operator * ( const TuplaG<T,n>  & t ) const
{
   TuplaG<T,n>  res ;
   for( unsigned fil = 0 ; fil < n ; fil++ )
   {  res[fil] = 0.0 ;
      for( unsigned col = 0 ; col < n ; col++ )
         res(fil) += (*this)(fil,col) * t(col) ;
   }
   return res ;
}

// ---------------------------------------------------------------------
// multiplicar esta matriz por una tupla por la derecha (con una dimesnión menos)
// (se añade un 1, se multiplica, y luego se le quita la ultima componente)

template< class T, unsigned n > inline
TuplaG<T,n-1> MatrizCG<T,n>::operator * ( const TuplaG<T,n-1>  & t ) const
{
   TuplaG<T,n> t1 ;

   // añadir un 1 a t, crear 't1'
   for( unsigned i = 0 ; i < n-1 ; i++ )
      t1(i) = t(i) ;
   t1(n-1) = T(1); // añadir un uno al final

   //// multiplicar por 't1', obtener 'resn'
   //for( unsigned fil = 0 ; fil < n ; fil++ )
   //{  resn(fil) = 0.0 ;
      //for( unsigned col = 0 ; col < n ; col++ )
         //resn(fil) += (*this)(fil,col) * t1(col) ;
   //}

   TuplaG<T,n> res1 = (*this)*t1 ;

   // copiar 'resn' en 'res'
   TuplaG<T,n-1>  res ;
   for( unsigned i = 0 ; i < n-1 ; i++ )
      res(i) = res1(i) ;

   return res ;
}

// *********************************************************************
// test function

inline void test_vec_mat()
{
   using namespace std ;
   cout << "test_vec_mat" << endl ;
}

// *********************************************************************

} // end namespace figs_gen 

#endif // end of FIGS_GEN_VEC_MAT_H
