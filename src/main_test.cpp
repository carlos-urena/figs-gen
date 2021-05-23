#include <stdio.h>
#include <vec_mat.h>

namespace ttt 
{
   // tests for: https://clang.llvm.org/docs/LanguageExtensions.html#vectors-and-extended-vectors
   
   typedef float float4 __attribute__((ext_vector_type(4)));
   typedef float float2 __attribute__((ext_vector_type(2)));

   float4 foo(float2 a, float2 b) 
   {
      float4 c;
      c.xz = a;
      c.yw = b;
      return c;
   }
   void print_v4( const float v[4] )
   {
      using namespace std ;
      cout << " v == (" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")" << endl ;
   }
   void test()
   {
      float2 v12 = { 1.0, 2.0 } ;
      float2 v34 = { 3.0, 4.0 } ;
      float4 v   = foo( v12+v34, 4.0*v34 );

      using namespace std ;
      cout << " v == (" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << endl ;
   }
}

int main( int argc, char * argv[] )
{
   using namespace vec_mat ; 
   tests() ;

   ttt::test();
}