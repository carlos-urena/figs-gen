// *********************************************************************
// **
// ** Template classes for small vectors and matrices
// ** Copyright (C) 2014-2021 Carlos Ureña
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


#ifndef VECMAT_H
#define VECMAT_H

#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751
#endif

namespace vec_mat
{

// constants used to access vectors' components
const unsigned
   X = 0,
   Y = 1,
   Z = 2,

   R = 0,
   G = 1,
   B = 2 ;

// an alias for 'unsigned int' but with a single token
typedef unsigned int uint ;


// *********************************************************************
// class template: VecTmpl
// a template for classes for small fixed-length vectors with numeric values
//
// parameters:
//    T - values type (float, double, int, unsigned, etc...)
//    n - number of values in the vector
// --------------------------------------------------------------------

template< class T, unsigned n >
class VecTmpl
{
   private:
   T coo[n] ;  // values

   public:
   // does nothing
   inline VecTmpl();

   // build from an array
   inline VecTmpl( const T * org ) ;

   // read-only access (usage: x=v(i) )
   const T & operator () (const unsigned i) const ;

   // arbitrary read/write access (usage: v(i)=x )
   T & operator () (const unsigned i) ;

   // conversion to a read-write pointer (whose type is T*) (usage: T* p = v)
   operator  T * ()  ;

   // conversion to a read-only pointer (whose type is T*) (usage: const T* p = v )
   operator  const T * ()  const ;

   // componentwise addition (usage: v1=v2+v3 )
   VecTmpl<T,n> operator + ( const VecTmpl & der ) const ;

   // componentwise substraction (usage: v1=v2-v3 )
   VecTmpl<T,n> operator - ( const VecTmpl & der ) const ;

   // componentwise negation (usage: v1 = -v2 )
   VecTmpl<T,n> operator - (  ) const ;

   // multiplication by a scalar (usage: v1=v2*a )
   VecTmpl<T,n> operator * ( const T & a ) const ;

   // division por escalar ( v1=v2/a )
   VecTmpl<T,n> operator / ( const T & a ) const ;

   // producto escalar (dot)  a = v1.dot(v2)
   T dot( const VecTmpl<T,n> & v2 ) const ;

   // operador binario para producto escalar a = v1|v2 ;
   T operator | ( const VecTmpl & der ) const ;

   // obtener longitud al cuadrado
   T lengthSq( ) const ;

   // obtener una copia normalizada
   VecTmpl<T,n> normalized() const ;
} ;

//----------------------------------------------------------------------
// non-member functions and operators

// mult. por escalar por la izquierda ( v1=a*v2 )
template< class T, unsigned n >
inline VecTmpl<T,n> operator *  ( const T & a, const  VecTmpl<T,n> & der ) ;

// escritura de un vector en un ostream
template< class T, unsigned n >
inline std::ostream & operator <<  ( std::ostream & os, const VecTmpl<T,n> & der ) ;

// ********************************************************************
// Plantilla de clase: VecTmpl2
// especialización parcial para tuplas de 2 elementos
// (define constructores específicos)
// --------------------------------------------------------------------

template< class T >
class VecTmpl2 : public VecTmpl<T,2>
{
   public:

   // constructores: por defecto
   VecTmpl2() ;
   VecTmpl2( const T & c0, const T & c1 ) ;
   VecTmpl2( const VecTmpl<T,2> & ini );
   void operator = ( const VecTmpl<T,2> & der ) ;
} ;


// *********************************************************************
// Plantilla de clase: VecTmpl3
// especialización parcial para tuplas de 3 elementos
// (define constructores específicos)
// --------------------------------------------------------------------

template< class T >
class VecTmpl3 : public VecTmpl<T,3>
{
   public:

   // constructores: por defecto
   VecTmpl3() ;
   VecTmpl3( const T & c0, const T & c1, const T & c2 ) ;
   VecTmpl3( const VecTmpl<T,3> & ini );
   void operator = ( const VecTmpl<T,3> & der ) ;
   void operator = ( const VecTmpl<T,4> & der ) ; // asignar ignorando ultimo

   // producto vectorial (cross)  a = v1.cross(v2)
   VecTmpl3<T> cross( const VecTmpl3<T> & v2 ) const ;
} ;


// *********************************************************************
// Plantilla de clase: VecTmpl4
// especialización parcial para tuplas de 4 elementos
// (define constructores específicos)
// --------------------------------------------------------------------

template< class T >
class VecTmpl4 : public VecTmpl<T,4>
{
   public:

   // constructores: por defecto
   VecTmpl4() ;
   VecTmpl4( const T & c0, const T & c1, const T & c2, const T & c3 ) ;
   VecTmpl4( const VecTmpl<T,4> & ini );
   void operator = ( const VecTmpl<T,4> & der ) ;
} ;

// *********************************************************************
// plantilla de clase: MatrixTemplate
// clase para matrices cuadradas genéricas
// --------------------------------------------------------------------

template< class T, unsigned n >
class MatrixTemplate
{
   public:
   VecTmpl< VecTmpl<T,n>, n > mat ;

   MatrixTemplate<T,n> ()  {}  // constructor por defecto inline (no inicializa)

   // conversion a un puntero de lectura/escritura de tipo: T*
   // ( T* p = matriz )
   inline operator  T * ()  ;

   // conversion a un puntero de solo lectura de tipo: const T*
   // ( const T* p = matriz )
   inline operator  const T * ()  const ;

   // acceso de lectura a una fila
   // (devuelve puntero al primer elemento de una columna)
   //inline const VecTmpl<T,n> & operator() ( const unsigned i ) const ;

   // acceso de lectura/escritura a una fila:
   //inline VecTmpl<T,n> & operator[] ( int i )  ;

   // componer esta matriz con otra por la derecha
   inline MatrixTemplate<T,n> operator * ( const MatrixTemplate<T,n> & der ) const ;

   // acceso de solo lectura usando fila,columna: T x = m(fil,col)
   inline const T & operator()( const unsigned fil, const unsigned col ) const ;

   // acceso de lectura/escritura usando fila,columna: T x = m(fil,col)
   inline T & operator()( const unsigned fil, const unsigned col )  ;

   // multiplicar esta matriz por una tupla por la derecha
   inline VecTmpl<T,n> operator * ( const VecTmpl<T,n>  & t ) const ;

   // multiplicar esta matriz por una tupla por la derecha (con una dimesnión menos)
   // (se añade un 1, se multiplica, y luego se le quita la ultima componente)
   inline VecTmpl<T,n-1> operator * ( const VecTmpl<T,n-1>  & t ) const ;
} ;

// escritura de una matriz en un ostream
template< class T, unsigned n > inline
std::ostream & operator <<  ( std::ostream & os, const MatrixTemplate<T,n> & m ) ;


// *********************************************************************
// tipos concretos:

typedef VecTmpl2<float>  Vec2 ;
typedef VecTmpl2<double> Vec2d ;
typedef VecTmpl2<uint>   Vec2u ;
typedef VecTmpl2<int>    Vec2i ;

typedef VecTmpl3<float>  Vec3 ;
typedef VecTmpl3<double> Vec3d ;
typedef VecTmpl3<uint>   Vec3u ;
typedef VecTmpl3<int>    Vec3i ;

typedef VecTmpl4<float>  Vec4 ;
typedef VecTmpl4<double> Vec4d ;
typedef VecTmpl4<int>    Vec4i ;
typedef VecTmpl4<uint>   Vec4u ;

typedef MatrixTemplate<float,4>  Mat4 ;
typedef MatrixTemplate<double,4> Mat4d ;

// *********************************************************************
// MAT_ functions for various types of matrices typically used in
// computer graphics (declarations)
// --------------------------------------------------------------------


// ---------------------------------------------------------------------
// juego de tests de la matrices
void MAT_Tests() ;

// ---------------------------------------------------------------------
// creación y operadores de matrices: transformaciones de modelado

Mat4 MAT_Ident       ( ) ;
Mat4 Mat4_Translation( const Vec3& d ) ;
Mat4 Mat4_Scale      ( const Vec3& s ) ;
Mat4 Mat4_Rotation   ( const float ang_deg, const Vec3& a ) ;
Mat4 Mat4_Rows       ( const Vec3 & row0, const Vec3 & row1, const Vec3 & row2 );

// ---------------------------------------------------------------------
// matrices auxiliares para la transformación de vista

Mat4 MAT_Transpuesta3x3( const Mat4 & org ) ;
Mat4 Mat4_Rows         ( const Vec3 fila[3] );
Mat4 Mat4_Columns      ( const Vec3 colum[3] );

// ---------------------------------------------------------------------
// matrices para la transformacion de vista:

Mat4 Mat4_LookAt( const float origen[3], const float centro[3], const float vup[3] );
Mat4 Mat4_View         ( const Vec3 eje[3], const Vec3& org );
Mat4 Mat4_View_inv     ( const Vec3 eje[3], const Vec3& org );


// ---------------------------------------------------------------------
// matrices de transformación del viewport

Mat4 Mat4_Viewport      ( int org_x, int org_y, int ancho, int alto );
Mat4 Mat4_Viewport_inv  ( int org_x, int org_y, int ancho, int alto );

// ---------------------------------------------------------------------
// matrices para la transf. de proyección

Mat4 Mat4_Frustum    ( const float l, const float r, const float b, const float t, const float n, const float f );
Mat4 Mat4_Ortho( const float l, const float r, const float b, const float t, const float n, const float f );
Mat4 Mat4_Perspective( const float fovy_grad, const float raz_asp, const float n, const float f );

// --------------------------------------------------------------------
// calcula la inversa (la última fila debe ser 0, 0, 0, 1 - es decir,
// no debe haber proyeccion)
Mat4 Mat4_Inverse( const Mat4 & m );

// -------------------------------------------------------------------
// una clase para una pila de matrices

class Mat4Stack
{
   private:
      std::vector<Mat4> anteriores ;

   public:
      Mat4 actual  ;
      // crea una pila, donde la matriz actual es la identidad
      inline Mat4Stack()
      {  actual = MAT_Ident() ;
      }
      // crear una pila, dándole un valor a la matriz actual
      inline Mat4Stack( const Mat4 & actual_ini )
      {  actual = actual_ini ;
      }
      // hacer push de la pila (guarda la actual)
      inline void push(  )
      {  anteriores.push_back( actual );
      }
      // componer una matriz
      inline void comp( const Mat4 & mat )
      {  actual = actual*mat ;
      }
      // hacer pop de la pila (recupera la última guardada con push)
      inline void pop()
      {  const size_t n = anteriores.size() ;
         //assert( 0 < n );
         actual = anteriores[n-1] ;
         anteriores.pop_back() ;
      }
} ;



// *********************************************************************
// inline implementations

// *********************************************************************
// plantilla de clase:
// VecTmpl<T,n>
// *********************************************************************

template< class T, unsigned n> inline
VecTmpl<T,n>::VecTmpl()
{

}

// constructor usando un array C++
template< class T, unsigned n> inline
VecTmpl<T,n>::VecTmpl( const T * org )
{
   for( unsigned i = 0 ; i < n ; i++ )
      (*this)[i] = org[i] ;
}

//----------------------------------------------------------------------

//template< class T, unsigned n >
//T & VecTmpl<T,n>::operator [] (const unsigned i)
//{
   //assert( i < n ) ;
   //return coo[i] ;
//}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
const T & VecTmpl<T,n>::operator () (const unsigned i) const
{
   assert( i < n ) ;
   return coo[i] ;
}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
T & VecTmpl<T,n>::operator () (const unsigned i)
{
   assert( i < n ) ;
   return coo[i] ;
}

//----------------------------------------------------------------------
// conversion a un puntero de lectura/escritura de tipo: T* ( T* p = tupla )

template< class T, unsigned n > inline
VecTmpl<T,n>::operator  T * ()
{
   return coo ;
}

//----------------------------------------------------------------------
// conversion a un puntero de solo lectura de tipo T* ( const T* p = tupla )

template< class T, unsigned n > inline
VecTmpl<T,n>::operator  const T * () const
{
   return coo ;
}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
VecTmpl<T,n> VecTmpl<T,n>::operator + ( const VecTmpl<T,n> & der ) const
{
   VecTmpl<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = (*this)(i)+der(i) ;
   return res ;
}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
VecTmpl<T,n> VecTmpl<T,n>::operator - ( const VecTmpl<T,n> & der ) const
{
   VecTmpl<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = (*this)(i)-der(i) ;
   return res ;
}

//----------------------------------------------------------------------

// devuelve tupla negada ( v1 = -v2 )
template< class T, unsigned n > inline
VecTmpl<T,n> VecTmpl<T,n>::operator - (  ) const
{
   VecTmpl<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = -(*this)(i) ;
   return res ;

}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
VecTmpl<T,n> VecTmpl<T,n>::operator * ( const T & a ) const
{
   VecTmpl<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = (*this)(i)*a ;
   return res ;
}

//----------------------------------------------------------------------

template< class T, unsigned n >  inline
VecTmpl<T,n> VecTmpl<T,n>::operator / ( const T & a ) const
{
   VecTmpl<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = (*this)(i)/a ;
   return res ;
}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
VecTmpl<T,n> operator * ( const T & a, const VecTmpl<T,n> & der )
{
   VecTmpl<T,n> res ;
   for( unsigned i = 0 ; i < n ; i++ )
      res[i] = a*der(i) ;
   return res ;
}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
std::ostream & operator <<  ( std::ostream & os, const VecTmpl<T,n> & der )
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
T VecTmpl<T,n>::dot( const VecTmpl<T,n> & v2 ) const
{
   double res = 0.0 ;
   for( unsigned int i = 0 ; i < n ; i++ )
      res += double((*this)(i)) * double(v2(i)) ;
   return T(res) ;
}

//----------------------------------------------------------------------

// obtener longitud al cuadrado
template< class T, unsigned n > inline
T VecTmpl<T,n>::lengthSq( ) const
{
   return T( this->dot( *this ) ) ;
}

//----------------------------------------------------------------------
// operador binario para producto escalar

template< class T, unsigned n > inline
T VecTmpl<T,n>::operator | ( const VecTmpl & der ) const
{
   return this->dot( der ) ;
}

// ---------------------------------------------------------------------

template< class T, unsigned n > inline
VecTmpl<T,n> VecTmpl<T,n>::normalized() const
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
//   VecTmpl2<T>
// *********************************************************************

template< class T > inline
VecTmpl2<T>::VecTmpl2(  )
{

}

// ---------------------------------------------------------------------

template< class T > inline
VecTmpl2<T>::VecTmpl2( const VecTmpl<T,2> & ini )
{
   (*this)[0] = ini(0) ;
   (*this)[1] = ini(1) ;
}

// ---------------------------------------------------------------------

template< class T > inline
void VecTmpl2<T>::operator = ( const VecTmpl<T,2> & der )
{
   (*this)[0] = der(0) ;
   (*this)[1] = der(1) ;
}

// ---------------------------------------------------------------------

template< class T > inline
VecTmpl2<T>::VecTmpl2( const T & c0, const T & c1 )
{
   (*this)[0] = c0 ;
   (*this)[1] = c1 ;
}

// *********************************************************************
//
// plantilla de clase:
// VecTmpl3<T>
//
// *********************************************************************

template< class T > inline
VecTmpl3<T>::VecTmpl3(  )
{

}

// ---------------------------------------------------------------------

template< class T > inline
VecTmpl3<T>::VecTmpl3( const VecTmpl<T,3> & ini )
{
   (*this)[0] = ini(0) ;
   (*this)[1] = ini(1) ;
   (*this)[2] = ini(2) ;
}

// ---------------------------------------------------------------------

template< class T > inline
void VecTmpl3<T>::operator = ( const VecTmpl<T,3> & der )
{
   (*this)[0] = der(0) ;
   (*this)[1] = der(1) ;
   (*this)[2] = der(2) ;
}

// ---------------------------------------------------------------------

template< class T > inline
void VecTmpl3<T>::operator = ( const VecTmpl<T,4> & der )
{
   (*this)[0] = der(0) ;
   (*this)[1] = der(1) ;
   (*this)[2] = der(2) ;
}

// ---------------------------------------------------------------------

template< class T > inline
VecTmpl3<T>::VecTmpl3( const T & c0, const T & c1, const T & c2 )
{
   (*this)[0] = c0 ;
   (*this)[1] = c1 ;
   (*this)[2] = c2 ;
}

// ---------------------------------------------------------------------


template< class T > inline
VecTmpl3<T> VecTmpl3<T>::cross( const VecTmpl3<T> & v2 ) const
{
   // cuidado: no hay acceso a 'coo' tal cual, mirar:
   // http://stackoverflow.com/questions/7281072/accessing-public-members-of-base-class-fails

   return VecTmpl3<T>(  (*this)(1)*v2(2) -  (*this)(2)*v2(1),
                       (*this)(2)*v2(0) -  (*this)(0)*v2(2),
                       (*this)(0)*v2(1) -  (*this)(1)*v2(0)
                     );
}

// *********************************************************************
// plantilla de clase:
//
//   VecTmpl4<T>
//
// *********************************************************************

template< class T > inline
VecTmpl4<T>::VecTmpl4(  )
{

}

// ---------------------------------------------------------------------

template< class T > inline
VecTmpl4<T>::VecTmpl4( const VecTmpl<T,4> & ini )
{
   (*this)[0] = ini(0) ;
   (*this)[1] = ini(1) ;
   (*this)[2] = ini(2) ;
   (*this)[3] = ini(3) ;
}

// ---------------------------------------------------------------------

template< class T > inline
void VecTmpl4<T>::operator = ( const VecTmpl<T,4> & der )
{
   (*this)[0] = der(0) ;
   (*this)[1] = der(1) ;
   (*this)[2] = der(2) ;
   (*this)[3] = der(3) ;
}

// ---------------------------------------------------------------------

template< class T > inline
VecTmpl4<T>::VecTmpl4( const T& c0, const T& c1, const T& c2, const T& c3 )
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
MatrixTemplate<T,n>::operator  T * ()
{
   return mat[0] ;
}

// ---------------------------------------------------------------------
// conversion a un puntero de solo lectura de tipo: const T* ( T* p = m )
// (devuelve puntero al primer elemento de la primera columna)
template< class T, unsigned n > inline
MatrixTemplate<T,n>::operator  const T * ()  const
{
   return & (mat(0)(0)) ;
}

//// ---------------------------------------------------------------------
//// acceso de lectura a una fila:
//template< class T, unsigned n > inline
//const VecTmpl<T,n> & MatrixTemplate<T,n>::operator() ( const unsigned i ) const
//{
   //return mat(i) ;
//}

////----------------------------------------------------------------------

//template< class T, unsigned n > inline
//VecTmpl<T,n> & MatrixTemplate<T,n>::operator[] ( int i )
//{
   //return mat[i] ;
//}

//----------------------------------------------------------------------

template< class T, unsigned n > inline
std::ostream & operator <<  ( std::ostream & os, const MatrixTemplate<T,n> & m )
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
MatrixTemplate<T,n> MatrixTemplate<T,n>::operator * ( const MatrixTemplate<T,n> & der ) const
{
   MatrixTemplate<T,n> res ;

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
const T & MatrixTemplate<T,n>::operator()( const unsigned fil, const unsigned col ) const
{
   assert( fil < n );
   assert( col < n ) ;
   return mat(col)(fil) ;
}


// ---------------------------------------------------------------------
// acceso de lectura/escritura usando fila,columna: m(fil,col) = v

template< class T, unsigned n > inline
T & MatrixTemplate<T,n>::operator()( const unsigned fil, const unsigned col )
{
   assert( fil < n );
   assert( col < n ) ;
   return mat(col)(fil) ;
}

// ---------------------------------------------------------------------
// multiplicar esta matriz por una tupla por la derecha
template< class T, unsigned n > inline
VecTmpl<T,n> MatrixTemplate<T,n>::operator * ( const VecTmpl<T,n>  & t ) const
{
   VecTmpl<T,n>  res ;
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
VecTmpl<T,n-1> MatrixTemplate<T,n>::operator * ( const VecTmpl<T,n-1>  & t ) const
{
   VecTmpl<T,n> t1 ;

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

   VecTmpl<T,n> res1 = (*this)*t1 ;

   // copiar 'resn' en 'res'
   VecTmpl<T,n-1>  res ;
   for( unsigned i = 0 ; i < n-1 ; i++ )
      res(i) = res1(i) ;

   return res ;
}


// *********************************************************************
// MAT_ functions for generating various types of matrices typically
// used in computer graphics (implementations)
// --------------------------------------------------------------------


inline Mat4 MAT_Ident(  )
{
   Mat4 res ;
   for( unsigned fil = 0 ; fil < 4 ; fil++ )
   for( unsigned col = 0 ; col < 4 ; col++ )
      res(fil,col) = (col == fil) ? 1.0f : 0.0f ;

   return res ;
}

//----------------------------------------------------------------------

inline Mat4 Mat4_Rows( const Vec3 & row0, const Vec3 & row1, const Vec3 & row2 )
{
   Mat4 res = MAT_Ident();

   for( unsigned col = 0 ; col < 3 ; col++ )
   {  res(0,col) = row0(col) ;
      res(1,col) = row1(col) ;
      res(2,col) = row2(col) ;
   }
   return res ;
}
// ---------------------------------------------------------------------

inline Mat4 Mat4_Translation( const Vec3& d )
{
   Mat4 res = MAT_Ident();

   res(0,3) = d(0) ;
   res(1,3) = d(1) ;
   res(2,3) = d(2) ;

   return res ;
}
// ---------------------------------------------------------------------

inline Mat4 Mat4_Scale( const Vec3& s )
{
   Mat4 res = MAT_Ident();

   res(0,0) = s(0) ;
   res(1,1) = s(1) ;
   res(2,2) = s(2) ;

   return res ;
}

// ---------------------------------------------------------------------

inline Mat4 Mat4_Rotation( const float ang_deg, const Vec3 &a )
{
   const Vec3 ejen = a.normalized() ;

   const double
      ang_rad = double(ang_deg)*double(2.0)*double(M_PI)/double(360.0) ,
      c       = cos(ang_rad),
      s       = sin(ang_rad);

   const double
      exn     = ejen[X],
      eyn     = ejen[Y],
      ezn     = ejen[Z],
      hx      = (1.0-c)*exn ,
      hy      = (1.0-c)*eyn ,
      hz      = (1.0-c)*ezn ;

   Mat4 res = MAT_Ident();

   res(0,0) = hx*exn+c     ; res(0,1) = hx*eyn-s*ezn ; res(0,2) = hx*ezn+s*eyn ;
   res(1,0) = hy*exn+s*ezn ; res(1,1) = hy*eyn+c     ; res(1,2) = hy*ezn-s*exn ;
   res(2,0) = hz*exn-s*eyn ; res(2,1) = hz*eyn+s*exn ; res(2,2) = hz*ezn+c     ;

   return res ;
}
// ---------------------------------------------------------------------

inline Mat4 Mat4_LookAt( const Vec3& origin, const Vec3& center, const Vec3& vup )
{
   Vec3
      axis[3] ; // array con los tres vectores de los ejes del S.R. de la cámara

   axis[Z] = ( origin - center ).normalized() ; // eje Z desde el p.a. hacia el obs., normalizado
   axis[X] = vup.cross( axis[Z] ).normalized(),  // eje Z apunta en la dir. contraria a la camara
   axis[Y] = axis[Z].cross( axis[X] );                     // eje Y perpendicular a los otros dos.

   Mat4
      trasl = Mat4_Translation( -origin ),
      rot   = MAT_Ident() ; // matriz de cambio de base mundo --> camara

   // use Mat4_Rows or Mat4_Columns instead ??
   for( unsigned col = X ; col <= Z ; col++ )
   for( unsigned fil = X ; fil <= Z ; fil++ )
      rot(fil,col) = axis[fil](col) ;

   return rot * trasl ;
}
// ---------------------------------------------------------------------

inline Mat4 Mat4_Frustum( const float l, const float r, const float b, const float t, const float n, const float f )
{
   const float eps = 1e-6 ;
   assert( fabs(r-l) > eps && fabs(t-b) > eps  && fabs(n-f) > eps );

   const float
      irl = 1.0f/(r-l) ,
      itb = 1.0f/(t-b) ,
      inf = 1.0f/(n-f) ;
   const float
      a0 = 2.0f*n*irl ,
      a2 = (r+l)*irl,
      b1 = 2.0f*n*itb ,
      b2 = (t+b)*itb ,
      c2 = (n+f)*inf ,
      c3 = 2.0f*f*n*inf ;

   Mat4
      res ;

   res(0,0) = a0  ; res(0,1) = 0.0; res(0,2) = a2  ; res(0,3) = 0.0 ;
   res(1,0) = 0.0 ; res(1,1) = b1 ; res(1,2) = b2  ; res(1,3) = 0.0 ;
   res(2,0) = 0.0 ; res(2,1) = 0.0; res(2,2) = c2  ; res(2,3) = c3  ;
   res(3,0) = 0.0 ; res(3,1) = 0.0; res(3,2) = -1.0; res(3,3) = 0.0 ;

   return res ;
}

// ---------------------------------------------------------------------

inline Mat4 Mat4_Ortho( const float l, const float r, const float b, const float t, const float n, const float f )
{
   const float eps = 1e-6 ;
   assert( fabs(r-l) > eps && fabs(t-b) > eps  && fabs(n-f) > eps );

   const float
      irl = 1.0f/(l-r) ,
      itb = 1.0f/(b-t) ,
      inf = 1.0f/(n-f) ;
   const float
      a0 = -2.0f*irl ,
      a3 = (r+l)*irl,
      b1 = -2.0f*itb ,
      b3 = (t+b)*itb ,
      c2 = 2.0f*inf ,
      c3 = (f+n)*inf ;

   Mat4
      res ;

   res(0,0) = a0  ; res(0,1) = 0.0 ; res(0,2) = 0.0 ; res(0,3) = a3  ;
   res(1,0) = 0.0 ; res(1,1) = b1  ; res(1,2) = 0.0 ; res(1,3) = b3  ;
   res(2,0) = 0.0 ; res(2,1) = 0.0 ; res(2,2) = c2  ; res(2,3) = c3  ;
   res(3,0) = 0.0 ; res(3,1) = 0.0 ; res(3,2) = 0.0 ; res(3,3) = 1.0 ;

   return res ;
}

// ---------------------------------------------------------------------

inline Mat4 Mat4_Perspective( const float fovy_grad, const float raz_asp, const float n, const float f )
{
   const float eps = 1e-6 ;
   assert( raz_asp > eps && fovy_grad > eps  && fabs(n-f) > eps );

   const float
      fovy_rad = fovy_grad*2.0f*M_PI/360.0f,
      t = n*tan(0.5*fovy_rad),
      r = t/raz_asp,
      b = -t ,
      l = -r ;

   return Mat4_Frustum( l,r,b,t,n,f );
}


// ---------------------------------------------------------------------
// traspuesta (IGNORA LAS TRASLACIONES)

inline Mat4 MAT_Transpuesta3x3( const Mat4 & org )
{
   Mat4 res = MAT_Ident() ;

   for( unsigned i = 0 ; i < 3 ; i++ )
   for( unsigned j = 0 ; j < 3 ; j++ )
      res(i,j) = org(j,i);

   return res ;
}
//----------------------------------------------------------------------
// construir la sub-matriz 3x3 dando sus tres filas

inline Mat4 Mat4_Rows( const Vec3 fila[3] )
{
   Mat4 res = MAT_Ident();

   for( unsigned col = 0 ; col < 3 ; col++ )
   {
      res(0,col) = fila[0](col) ;
      res(1,col) = fila[1](col) ;
      res(2,col) = fila[2](col) ;
   }
   return res ;
}
//----------------------------------------------------------------------
// construir la sub-matriz 3x3 dando sus tres columnas

inline Mat4 Mat4_Columns( const Vec3 colum[3] )
{
   Mat4 res = MAT_Ident();

   for( unsigned fil = 0 ; fil < 3 ; fil++ )
   {
      res(fil,0) = colum[0](fil) ;
      res(fil,1) = colum[1](fil) ;
      res(fil,2) = colum[2](fil) ;
   }
   return res ;
}
// ---------------------------------------------------------------------
// matriz del viewport  (deja las Z igual: entre -1 y 1)

inline Mat4 Mat4_Viewport( int org_x, int org_y, int ancho, int alto )
{
   return Mat4_Translation( { float(org_x), float(org_y), 0.0 } )*
          Mat4_Scale( { float(ancho), float(alto), 1.0 } )*
          Mat4_Scale( { 0.5, 0.5, 1.0 })*
          Mat4_Translation( {1.0, 1.0, 1.0 } ) ;
}
// ---------------------------------------------------------------------
// matriz inversa de la matriz del viewport

inline Mat4 Mat4_Viewport_inv( int org_x, int org_y, int ancho, int alto )
{
   return Mat4_Translation( { -1.0, -1.0, -1.0 } ) *
          Mat4_Scale( { 2.0, 2.0, 1.0 } )*
          Mat4_Scale( { 1.0f/float(ancho), 1.0f/float(alto), 1.0 } )*
          Mat4_Translation( {-float(org_x), -float(org_y), 0.0 } ) ;
}

// ---------------------------------------------------------------------
// matriz de vista, a partir del marco de coordenadas de la camara:
inline Mat4 Mat4_View( const Vec3 eje[3], const Vec3& org )
{
   // traslación por -origen, seguida de productos escalares
   return Mat4_Rows( eje )*Mat4_Translation( -org ) ;
}
// ---------------------------------------------------------------------
// matriz inversa de la vista, a partir del marco de coordenadas de la camara:
inline Mat4 Mat4_View_inv( const Vec3 eje[3], const Vec3& org )
{
   // rotaciones seguidas de traslación por origen
   return  Mat4_Translation( org )*Mat4_Columns( eje );
}

// --------------------------------------------------
// métodos auxiliares para calcular la inversa de una matriz

// -----------------------------------------------------------------------
// calculo del determinante de la submatriz 3x3
inline float Mat4_Determinant3x3( const Mat4 & m )
{
   return + m(0,0)*m(1,1)*m(2,2)
          + m(0,1)*m(1,2)*m(2,0)
          + m(0,2)*m(1,0)*m(2,1)

          - m(0,0)*m(1,2)*m(2,1)
          - m(0,1)*m(1,0)*m(2,2)
          - m(0,2)*m(1,1)*m(2,0) ;
}

// --------------------------------------------------------------------
// calcula la inversa de una matriz 4x4 (sin términos de proyección)
// (la última fila debe ser 0, 0, 0, 1)

inline Mat4 Mat4_Inverse( const Mat4 & m )
{
   assert( m(3,0) == 0.0 );
   assert( m(3,1) == 0.0 );
   assert( m(3,2) == 0.0 );
   assert( m(3,3) == 1.0 );

   // 1. calcular matriz de cofactores ('cofac')
   Mat4 cofac = MAT_Ident();

   for( int i = 0 ; i < 3 ; i++ )
   for( int j = 0 ; j < 3 ; j++ )
   {
      const int i1 = (i+1)%3, i2 = (i+2)%3,
                j1 = (j+1)%3, j2 = (j+2)%3;
      cofac(i,j) = m(i1,j1)*m(i2,j2) - m(i1,j2)*m(i2,j1) ;
   }

   // 2. calcular determinante (det) (usando la primera fila de 'm' y de 'cofac')
   const float det = m(0,0)*cofac(0,0) +  m(0,1)*cofac(0,1) + m(0,2)*cofac(0,2) ;
   assert( 1e-6 < fabs(det) );
   const float inv_det = 1.0/det ;

   // 3. calcular la matriz inversa de la sub-matrix 3x3 (inv3x3) como la
   // adjunta (transpuesta de los cofactores), dividida por el determinante:
   Mat4 inv3x3 = MAT_Ident();
   for( int i = 0 ; i < 3 ; i++ )
   for( int j = 0 ; j < 3 ; j++ )
      inv3x3(i,j) = inv_det * cofac(j,i) ;

   // 4. calcular la matriz de traslación inversa
   Mat4 trasl_inv = MAT_Ident() ;
   for( int i = 0 ; i < 3 ; i++ )
      trasl_inv(i,3) = -m(i,3) ;

   // 5. calcular (y devolver) la inversa completa
   // (traslación inversa seguida de la inversa 3x3)
   return inv3x3 * trasl_inv;
}


// ---------------------------------------------------------------------
// juego de tests de la matrices



inline void matrix_tests()
{
   using namespace std ;

   // test de la matriz inversa:
   const Mat4
      mat1 = Mat4_Scale( {0.5, 0.9, -1.1} )*
             Mat4_Rotation( 34.0, {1.0, 2.0, 3.0} )*Mat4_Translation( {1.5, -2.2, -1.1} )*Mat4_Scale( {-1.5, -2.7, 5.0} )*
             Mat4_Rotation( -130.0, {-3.2, 2.0, -1.0} )*Mat4_Translation( {-0.8, 1.0, -1.7} )*Mat4_Scale( {0.5, 2.0, -1.5} ),
      mt   = Mat4_Translation( {1.0, 2.0, 3.0} ),
      mr   = Mat4_Rotation( -130.0, {-3.2, 2.0, -1.0} ),
      me   = Mat4_Scale( {2.0, -1.0, 0.7}  ) ;

   // test for the inverse matrix
   const Mat4 mat2 = me*mat1*mt*mr*me ;

   const float det = Mat4_Determinant3x3( mat2 );
   cout << "det de mat2 == " << det << endl ;

   const Mat4 inv = Mat4_Inverse( mat2 );
   const Mat4 ide = inv*mat2 ;

   cout << "mat2 == " << endl
        << mat2 << endl
        << "inv == " << endl
        << inv << endl
        << "ide == " << endl
        << ide << endl ;

}


// *********************************************************************
// test function

inline void tests()
{
   using namespace std ;
   cout << "vec_mat::Tests()" << endl ;
   matrix_tests();
}

// *********************************************************************

} // end namespace vec_mat

#endif // end of  VECMAT_H
