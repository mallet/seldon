// Copyright (C) 2001-2005 Vivien Mallet
// File authors: Marc Durufl� (main part), Vivien Mallet.
//
// This file is part of Seldon library.
// Seldon library provides matrices and vectors structures for
// linear algebra.
// 
// Seldon is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// Seldon is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License (file "license") for more details.
//
// For more information, please see the Seldon home page:
//     http://spacetown.free.fr/lib/seldon/

#ifndef SELDON_FILE_LAPACK_LINEAREQUATIONS_CXX

namespace Seldon
{
  
  
  ////////////////
  // LapackInfo //
  
    
  class LapackInfo
  {
  private:
    int info_;
  public:
    LapackInfo(int info);
    
    operator int ();

    int GetInfo();
    int& GetInfoRef();
    
  };
  
  
  LapackInfo::LapackInfo(int info): info_(info)
  {  
  }
  
  
  LapackInfo::operator int ()
  {
    return info_;
  }
  
  
  int LapackInfo::GetInfo()
  {
    return info_;
  }
  
  
  int& LapackInfo::GetInfoRef()
  {
    return info_;
  }
  
  
  LapackInfo lapack_info(0);
  
  
  // LapackInfo //
  ////////////////
  
  
  
  ///////////
  // GetLU //
  
  
  /*** ColMajor ***/


  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<float, Prop0, ColMajor, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    int n = A.GetN();
    P.Reallocate(min(m, n));
    sgetrf_(&m, &n, A.GetData(), &m,
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<double, Prop0, ColMajor, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    int n = A.GetN();
    P.Reallocate(min(m, n));
    dgetrf_(&m, &n, A.GetData(), &m,
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<float>, Prop0, ColMajor, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    int n = A.GetN();
    P.Reallocate(min(m, n));
    cgetrf_(&m, &n, A.GetDataVoid(), &m,
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<double>, Prop0, ColMajor, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    int n = A.GetN();
    P.Reallocate(min(m, n));
    zgetrf_(&m, &n, A.GetDataVoid(), &m,
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /*** RowMajor ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<float, Prop0, RowMajor, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    int n = A.GetN();
    P.Reallocate(min(m, n));
    sgetrf_(&m, &n, A.GetData(), &m,
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<double, Prop0, RowMajor, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    int n = A.GetN();
    P.Reallocate(min(m, n));
    dgetrf_(&m, &n, A.GetData(), &m,
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<float>, Prop0, RowMajor, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    int n = A.GetN();
    P.Reallocate(min(m, n));
    cgetrf_(&m, &n, A.GetDataVoid(), &m,
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<double>, Prop0, RowMajor, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    int n = A.GetN();
    P.Reallocate(min(m, n));
    zgetrf_(&m, &n, A.GetDataVoid(), &m,
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /*** ColSym and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<float, Prop0, ColSym, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); 
    int lwork = m;
    char uplo('U');
    Vector<float,Vect_Full,Allocator0> work(lwork);
    P.Reallocate(m);
    ssytrf_(&uplo, &m, A.GetData(), &m,
	    P.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<double, Prop0, ColSym, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); 
    int lwork = m;
    char uplo('U');
    Vector<double,Vect_Full,Allocator0> work(lwork);
    P.Reallocate(m);
    dsytrf_(&uplo, &m, A.GetData(), &m,
	    P.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<float>, Prop0, ColSym, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); 
    int lwork = m;
    char uplo('U');
    Vector<complex<float>,Vect_Full,Allocator0> work(lwork);
    P.Reallocate(m);
    csytrf_(&uplo, &m, A.GetDataVoid(), &m,
	    P.GetData(),  work.GetDataVoid(), 
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<double>, Prop0, ColSym, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();  
    int lwork = m;
    char uplo('U');
    Vector<complex<double>,Vect_Full,Allocator0> work(lwork);
    P.Reallocate(m);
    zsytrf_(&uplo, &m, A.GetDataVoid(), &m,
	    P.GetData(), work.GetDataVoid(), 
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  /*** ColSymPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<float, Prop0, ColSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    P.Reallocate(m);
    ssptrf_(&uplo, &m, A.GetData(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<double, Prop0, ColSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    P.Reallocate(m);
    dsptrf_(&uplo, &m, A.GetData(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<float>, Prop0, ColSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    P.Reallocate(m);
    csptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<double>, Prop0, ColSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    P.Reallocate(m);
    zsptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /*** ColSymPacked and Uplo ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(SeldonUplo Uplo,
	     Matrix<float, Prop0, ColSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo(Uplo);
    P.Reallocate(m);
    ssptrf_(&uplo, &m, A.GetData(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(SeldonUplo Uplo,
	     Matrix<double, Prop0, ColSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo(Uplo);
    P.Reallocate(m);
    dsptrf_(&uplo, &m, A.GetData(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(SeldonUplo Uplo,
	     Matrix<complex<float>, Prop0, ColSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo(Uplo);
    P.Reallocate(m);
    csptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(SeldonUplo Uplo,
	     Matrix<complex<double>, Prop0, ColSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo(Uplo);
    P.Reallocate(m);
    zsptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /*** RowSym and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<float, Prop0, RowSym, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); 
    int lwork = m;
    char uplo('L');
    Vector<float, Vect_Full, Allocator0> work(lwork);
    P.Reallocate(m);
    ssytrf_(&uplo, &m, A.GetData(), &m,
	    P.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<double, Prop0, RowSym, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); 
    int lwork = m;
    char uplo('L');
    Vector<double, Vect_Full, Allocator0> work(lwork);
    P.Reallocate(m);
    dsytrf_(&uplo, &m, A.GetData(), &m,
	    P.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<float>, Prop0, RowSym, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); 
    int lwork = m;
    char uplo('L');
    Vector<complex<float>, Vect_Full, Allocator0> work(lwork);
    P.Reallocate(m);
    csytrf_(&uplo, &m, A.GetDataVoid(), &m,
	    P.GetData(),  work.GetDataVoid(), 
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<double>, Prop0, RowSym, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();  
    int lwork = m;
    char uplo('L');
    Vector<complex<double>, Vect_Full, Allocator0> work(lwork);
    P.Reallocate(m);
    zsytrf_(&uplo, &m, A.GetDataVoid(), &m,
	    P.GetData(), work.GetDataVoid(), 
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  /*** RowSymPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<float, Prop0, RowSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    P.Reallocate(m);
    ssptrf_(&uplo, &m, A.GetData(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<double, Prop0, RowSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    P.Reallocate(m);
    dsptrf_(&uplo, &m, A.GetData(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<float>, Prop0, RowSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    P.Reallocate(m);
    csptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<double>, Prop0, RowSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    P.Reallocate(m);
    zsptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /*** RowSymPacked and Uplo ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(SeldonUplo Uplo,
	     Matrix<float, Prop0, RowSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo(Uplo.RevChar());
    P.Reallocate(m);
    ssptrf_(&uplo, &m, A.GetData(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(SeldonUplo Uplo,
	     Matrix<double, Prop0, RowSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo(Uplo.RevChar());
    P.Reallocate(m);
    dsptrf_(&uplo, &m, A.GetData(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(SeldonUplo Uplo,
	     Matrix<complex<float>, Prop0, RowSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo(Uplo.RevChar());
    P.Reallocate(m);
    csptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(SeldonUplo Uplo,
	     Matrix<complex<double>, Prop0, RowSymPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo(Uplo.RevChar());
    P.Reallocate(m);
    zsptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /*** ColHerm and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<float>, Prop0, ColHerm, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); 
    int lwork = m;
    char uplo('U');
    Vector<complex<float>, Vect_Full, Allocator0> work(lwork);
    P.Reallocate(m);
    chetrf_(&uplo, &m, A.GetDataVoid(), &m,
	    P.GetData(),  work.GetDataVoid(), 
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<double>, Prop0, ColHerm, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();  
    int lwork = m;
    char uplo('U');
    Vector<complex<double>, Vect_Full, Allocator0> work(lwork);
    P.Reallocate(m);
    zhetrf_(&uplo, &m, A.GetDataVoid(), &m,
	    P.GetData(), work.GetDataVoid(), 
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  /*** ColHermPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<float>, Prop0, ColHermPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    P.Reallocate(m);
    chptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<double>, Prop0, ColHermPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    P.Reallocate(m);
    zhptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /*** RowHerm and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<float>, Prop0, RowHerm, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); 
    int lwork = m;
    char uplo('L');
    Vector<complex<float>, Vect_Full, Allocator0> work(lwork);
    P.Reallocate(m);
    chetrf_(&uplo, &m, A.GetDataVoid(), &m,
	    P.GetData(),  work.GetDataVoid(), 
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<double>, Prop0, RowHerm, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();  
    int lwork = m;
    char uplo('L');
    Vector<complex<double>, Vect_Full, Allocator0> work(lwork);
    P.Reallocate(m);
    zhetrf_(&uplo, &m, A.GetDataVoid(), &m,
	    P.GetData(), work.GetDataVoid(), 
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  /*** RowSymPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<float>, Prop0, RowHermPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    P.Reallocate(m);
    chptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1>
  void GetLU(Matrix<complex<double>, Prop0, RowHermPacked, Allocator0>& A,
	     Vector<int, Vect_Full, Allocator1>& P,
	     LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    P.Reallocate(m);
    zhptrf_(&uplo, &m, A.GetDataVoid(),
	    P.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  // GetLU //
  ///////////



  /////////////
  // SolveLU //

  
  /*** ColMajor and NoTrans ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const Matrix<float, Prop0, ColMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('N');
    sgetrs_(&trans, &m, &nrhs, A.GetData(), &m, P.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, ColMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P, 
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('N');
    dgetrs_(&trans, &m, &nrhs, A.GetData(), &m,P.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, ColMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('N');
    cgetrs_(&trans, &m, &nrhs, A.GetDataVoid(), &m,
	    P.GetData(), b.GetDataVoid(),
	    &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, ColMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('N');
    zgetrs_(&trans, &m, &nrhs, A.GetData(), &m,
	    P.GetData(), b.GetDataVoid(),
	    &m, &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColMajor ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const SeldonTranspose& TransA,
	       const Matrix<float, Prop0, ColMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.Char();
    sgetrs_(&trans, &m, &nrhs, A.GetData(), &m, P.GetData(), 
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const SeldonTranspose& TransA,
	       const Matrix<double, Prop0, ColMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.Char();
    dgetrs_(&trans, &m, &nrhs, A.GetData(), &m, P.GetData(), 
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const SeldonTranspose& TransA,
	       const Matrix<complex<float>, Prop0, ColMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.Char();
    cgetrs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, P.GetData(), 
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const SeldonTranspose& TransA,
	       const Matrix<complex<double>, Prop0, ColMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.Char();
    zgetrs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, P.GetData(), 
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  /*** RowMajor and NoTrans***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const Matrix<float, Prop0, RowMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('T');
    sgetrs_(&trans, &m, &nrhs, A.GetData(), &m,
	    P.GetData(), b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const Matrix<double, Prop0, RowMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('T');
    dgetrs_(&trans, &m, &nrhs, A.GetData(), &m,
	    P.GetData(), b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, RowMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('T');
    cgetrs_(&trans, &m, &nrhs, A.GetDataVoid(), &m,
	    P.GetData(), b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, RowMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('T');
    zgetrs_(&trans, &m, &nrhs, A.GetDataVoid(), &m,
	    P.GetData(), b.GetData(), &m, &lapack_info.GetInfoRef() );
  }

  
  /*** RowMajor ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const SeldonTranspose& TransA,
	       const Matrix<float, Prop0, RowMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.RevChar();
    sgetrs_(&trans, &m, &nrhs, A.GetData(), &m, P.GetData(), 
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const SeldonTranspose& TransA,
	       const Matrix<double, Prop0, RowMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.RevChar();
    dgetrs_(&trans, &m, &nrhs, A.GetData(), &m, P.GetData(), 
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const SeldonTranspose& TransA,
	       const Matrix<complex<float>, Prop0, RowMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.RevChar();
    if (TransA.ConjTrans())
      Conjugate(b);
    
    cgetrs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, P.GetData(), 
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
    if (TransA.ConjTrans())
      Conjugate(b);
  }
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const SeldonTranspose& TransA,
	       const Matrix<complex<double>, Prop0, RowMajor, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.RevChar();
    if (TransA.ConjTrans())
      Conjugate(b);
    
    zgetrs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, P.GetData(), 
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
    if (TransA.ConjTrans())
      Conjugate(b);
  }
  
  
  /*** ColSym and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, ColSym, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    ssytrs_(&uplo, &m, &nrhs, A.GetData(), &m,
	    P.GetData(), b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, ColSym, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    dsytrs_(&uplo, &m, &nrhs, A.GetData(), &m,
	    P.GetData(), b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, ColSym, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    csytrs_(&uplo, &m, & nrhs, A.GetDataVoid(), &m,
	    P.GetData(),  b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }


  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, ColSym, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    zsytrs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m,
	    P.GetData(), b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  /*** ColSymPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, ColSymPacked, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    ssptrs_(&uplo, &m, &nrhs, A.GetData(), P.GetData(), 
	    b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, ColSymPacked, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    dsptrs_(&uplo, &m, &nrhs, A.GetData(), P.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1,class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, ColSymPacked,
	       Allocator0>& A, const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    csptrs_(&uplo, &m, &nrhs, A.GetDataVoid(), P.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, ColSymPacked,
	       Allocator0>& A, const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    zsptrs_(&uplo, &m, &nrhs, A.GetDataVoid(), P.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  /*** RowSym and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, RowSym, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    ssytrs_(&uplo, &m, &nrhs, A.GetData(), &m,
	    P.GetData(), b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, RowSym, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    dsytrs_(&uplo, &m, &nrhs, A.GetData(), &m,
	    P.GetData(), b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, RowSym, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    csytrs_(&uplo, &m, & nrhs, A.GetDataVoid(), &m,
	    P.GetData(),  b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, RowSym, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    zsytrs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m,
	    P.GetData(), b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  /*** RowSymPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, RowSymPacked, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    ssptrs_(&uplo, &m, &nrhs, A.GetData(), P.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, RowSymPacked, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    dsptrs_(&uplo, &m, &nrhs, A.GetData(), P.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, RowSymPacked,
	       Allocator0>& A, const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    csptrs_(&uplo, &m, &nrhs, A.GetDataVoid(), P.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, RowSymPacked,
	       Allocator0>& A, const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    zsptrs_(&uplo, &m, &nrhs, A.GetDataVoid(), P.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColHerm and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, ColHerm, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    chetrs_(&uplo, &m, & nrhs, A.GetDataVoid(), &m,
	    P.GetData(),  b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, ColHerm, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    zhetrs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m,
	    P.GetData(), b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  /*** ColHermPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, ColHermPacked,
	       Allocator0>& A, const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    chptrs_(&uplo, &m, & nrhs, A.GetDataVoid(),
	    P.GetData(),  b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, ColHermPacked,
	       Allocator0>& A, const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    zhptrs_(&uplo, &m, &nrhs, A.GetDataVoid(),
	    P.GetData(), b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  /*** RowHerm and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, RowHerm, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    Conjugate(b);
    chetrs_(&uplo, &m, & nrhs, A.GetDataVoid(), &m,
	    P.GetData(),  b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    Conjugate(b);
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, RowHerm, Allocator0>& A,
	       const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    Conjugate(b);
    zhetrs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m,
	    P.GetData(), b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    Conjugate(b);
  }
  
  
  /*** RowHermPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, RowHermPacked,
	       Allocator0>& A, const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    Conjugate(b);
    chptrs_(&uplo, &m, & nrhs, A.GetDataVoid(),
	    P.GetData(),  b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    Conjugate(b);
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, RowHermPacked,
	       Allocator0>& A, const Vector<int, Vect_Full, Allocator1>& P,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, pivot, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    Conjugate(b);
    zhptrs_(&uplo, &m, &nrhs, A.GetDataVoid(),
	    P.GetData(), b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    Conjugate(b);
  }
  
  
  /*** ColUpTriang, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, ColUpTriang, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('N'); char diag('N');
    strtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, ColUpTriang, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('N'); char diag('N');
    dtrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, ColUpTriang, 
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('N'); char diag('N');
    ctrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, ColUpTriang,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('N'); char diag('N');
    ztrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** ColUpTriang ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<float, Prop0, ColUpTriang, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    strtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<double, Prop0, ColUpTriang, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    dtrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<float>, Prop0, ColUpTriang, 
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    ctrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<double>, Prop0, ColUpTriang,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    ztrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** ColLoTriang, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, ColLoTriang, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('N'); char diag('N');
    strtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, ColLoTriang, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('N'); char diag('N');
    dtrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, ColLoTriang,
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('N'); char diag('N');
    ctrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, ColLoTriang,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('N'); char diag('N');
    ztrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** ColLoTriang ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<float, Prop0, ColLoTriang, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    strtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<double, Prop0, ColLoTriang, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    dtrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<float>, Prop0, ColLoTriang,
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    ctrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<double>, Prop0, ColLoTriang,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    ztrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** ColUpTriangPacked, NoTrans, and NonUnit ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, ColUpTriangPacked, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('N'); char diag('N');
    stptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, ColUpTriangPacked, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('N'); char diag('N');
    dtptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, ColUpTriangPacked,
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('N'); char diag('N');
    ctptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, ColUpTriangPacked,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('N'); char diag('N');
    ztptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** ColUpTriangPacked ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<float, Prop0, ColUpTriangPacked, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    stptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<double, Prop0, ColUpTriangPacked, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    dtptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<float>, Prop0, ColUpTriangPacked,
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    ctptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<double>, Prop0, ColUpTriangPacked,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    ztptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** ColLoTriangPacked, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, ColLoTriangPacked, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('N'); char diag('N');
    stptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, ColLoTriangPacked, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('N'); char diag('N');
    dtptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, ColLoTriangPacked,
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('N'); char diag('N');
    ctptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, ColLoTriangPacked,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('N'); char diag('N');
    ztptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** ColLoTriangPacked ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<float, Prop0, ColLoTriangPacked, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.Char(); char diag = DiagA.Char();
    stptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<double, Prop0, ColLoTriangPacked, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.Char(); char diag = DiagA.Char();
    dtptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<float>, Prop0, ColLoTriangPacked,
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.Char(); char diag = DiagA.Char();
    ctptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<double>, Prop0, ColLoTriangPacked,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.Char(); char diag = DiagA.Char();
    ztptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** RowUpTriang, NoTrans and NonUnit  ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, RowUpTriang, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('T'); char diag('N');
    strtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, RowUpTriang, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('T'); char diag('N');
    dtrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void
  SolveLU(const Matrix<complex<float>, Prop0, RowUpTriang, Allocator0>& A,
	  Vector<complex<float>, Vect_Full, Allocator2>& b,
	  LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('T'); char diag('N');
    ctrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void
  SolveLU(const Matrix<complex<double>, Prop0, RowUpTriang, Allocator0>& A,
	  Vector<complex<double>, Vect_Full, Allocator2>& b,
	  LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('T'); char diag('N');
    ztrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** RowUpTriang ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<float, Prop0, RowUpTriang, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    strtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<double, Prop0, RowUpTriang, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    dtrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void
  SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	  const Matrix<complex<float>, Prop0, RowUpTriang, Allocator0>& A,
	  Vector<complex<float>, Vect_Full, Allocator2>& b,
	  LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    if (TransA.ConjTrans())
      Conjugate(b);
    ctrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    if (TransA.ConjTrans())
      Conjugate(b);
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void
  SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	  const Matrix<complex<double>, Prop0, RowUpTriang, Allocator0>& A,
	  Vector<complex<double>, Vect_Full, Allocator2>& b,
	  LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    if (TransA.ConjTrans())
      Conjugate(b);
    ztrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    if (TransA.ConjTrans())
      Conjugate(b);
    
  }
  
  
  /*** RowLoTriang, NoTrans and NonUnit  ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, RowLoTriang, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('T'); char diag('N');
    strtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, RowLoTriang, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('T'); char diag('N');
    dtrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void
  SolveLU(const Matrix<complex<float>, Prop0, RowLoTriang, Allocator0>& A,
	  Vector<complex<float>, Vect_Full, Allocator2>& b,
	  LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('T'); char diag('N');
    ctrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void
  SolveLU(const Matrix<complex<double>, Prop0, RowLoTriang, Allocator0>& A,
	  Vector<complex<double>, Vect_Full, Allocator2>& b,
	  LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('T'); char diag('N');
    ztrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** RowLoTriang ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<float, Prop0, RowLoTriang, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    strtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<double, Prop0, RowLoTriang, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    dtrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(), &m,
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void
  SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	  const Matrix<complex<float>, Prop0, RowLoTriang, Allocator0>& A,
	  Vector<complex<float>, Vect_Full, Allocator2>& b,
	  LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    if (TransA.ConjTrans())
      Conjugate(b);
    ctrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    if (TransA.ConjTrans())
      Conjugate(b);
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void
  SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	  const Matrix<complex<double>, Prop0, RowLoTriang, Allocator0>& A,
	  Vector<complex<double>, Vect_Full, Allocator2>& b,
	  LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    if (TransA.ConjTrans())
      Conjugate(b);
    ztrtrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    if (TransA.ConjTrans())
      Conjugate(b);
  }
  
  
  /*** RowUpTriangPacked, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, RowUpTriangPacked, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('T'); char diag('N');
    stptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, RowUpTriangPacked, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('T'); char diag('N');
    dtptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, RowUpTriangPacked,
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('T'); char diag('N');
    ctptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, RowUpTriangPacked,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L'); char trans('T'); char diag('N');
    ztptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** RowUpTriangPacked ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<float, Prop0, RowUpTriangPacked, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    stptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<double, Prop0, RowUpTriangPacked, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    dtptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<float>, Prop0, RowUpTriangPacked,
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    if (TransA.ConjTrans())
      Conjugate(b);
    ctptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    if (TransA.ConjTrans())
      Conjugate(b);
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<double>, Prop0, RowUpTriangPacked,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('L');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    if (TransA.ConjTrans())
      Conjugate(b);
    ztptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    if (TransA.ConjTrans())
      Conjugate(b);
  }
  
  
  /*** RowLoTriangPacked, NoTrans and NonUnit  ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<float, Prop0, RowLoTriangPacked, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('T'); char diag('N');
    stptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<double, Prop0, RowLoTriangPacked, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('T'); char diag('N');
    dtptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<float>, Prop0, RowLoTriangPacked,
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('T'); char diag('N');  
    

    ctptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const Matrix<complex<double>, Prop0, RowLoTriangPacked,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U'); char trans('T'); char diag('N');
    ztptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  /*** RowLoTriangPacked ***/
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<float, Prop0, RowLoTriangPacked, Allocator0>& A,
	       Vector<float, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    stptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<double, Prop0, RowLoTriangPacked, Allocator0>& A,
	       Vector<double, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    dtptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetData(),
	    b.GetData(), &m, &lapack_info.GetInfoRef());
    
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<float>, Prop0, RowLoTriangPacked,
	       Allocator0>& A,
	       Vector<complex<float>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    if (TransA.ConjTrans())
      Conjugate(b);
    ctptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    if (TransA.ConjTrans())
      Conjugate(b);
  }
  
  
  template <class Prop0, class Allocator0, class Allocator2>
  void SolveLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
	       const Matrix<complex<double>, Prop0, RowLoTriangPacked,
	       Allocator0>& A,
	       Vector<complex<double>, Vect_Full, Allocator2>& b,
	       LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, b, "SolveLU(A, X)");
#endif
    
    int m = A.GetM(); int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    if (TransA.ConjTrans())
      Conjugate(b);
    ztptrs_(&uplo, &trans, &diag, &m, & nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, &lapack_info.GetInfoRef());
    if (TransA.ConjTrans())
      Conjugate(b);
  }
  
  
  // SolveLU //
  /////////////
  
  
  
  ///////////////////////////////
  // ReciprocalConditionNumber //
  
  
  /*** ColMajor ***/
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<float, Prop0, ColMajor,
				  Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char norm_type = norm.Char();
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(4*n);
    sgecon_(&norm_type, &n, A.GetData(), &n, &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<double, Prop0, ColMajor,
				   Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char norm_type = norm.Char();
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(4*n);
    dgecon_(&norm_type, &n, A.GetData(), &n, &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  ColMajor, Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char norm_type = norm.Char();
    
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(2*n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    cgecon_(&norm_type, &n, A.GetDataVoid(), &n, &anorm, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   ColMajor, Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char norm_type = norm.Char();
    
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(2*n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    zgecon_(&norm_type, &n, A.GetDataVoid(), &n, &anorm, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowMajor ***/
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<float, Prop0, RowMajor,
				  Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char norm_type = norm.RevChar();
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(4*n);
    sgecon_(&norm_type, &n, A.GetData(), &n, &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<double, Prop0, RowMajor,
				   Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char norm_type = norm.RevChar();
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(4*n);
    dgecon_(&norm_type, &n, A.GetData(), &n, &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  RowMajor, Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char norm_type = norm.RevChar();
    
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(2*n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    cgecon_(&norm_type, &n, A.GetDataVoid(), &n, &anorm, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   RowMajor, Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char norm_type = norm.RevChar();
    
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(2*n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    zgecon_(&norm_type, &n, A.GetDataVoid(), &n, &anorm, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColSym and Upper ***/
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<float, Prop0, ColSym,
				  Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(2*n);
    ssycon_(&uplo, &n, A.GetData(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<double, Prop0, ColSym,
				   Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(2*n);
    dsycon_(&uplo, &n, A.GetData(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  ColSym, Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); float rcond(0);
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    csycon_(&uplo, &n, A.GetDataVoid(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   ColSym, Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); double rcond(0);
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    zsycon_(&uplo, &n, A.GetDataVoid(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColSymPacked and Upper ***/
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<float, Prop0,
				  ColSymPacked, Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(2*n);
    sspcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<double, Prop0, ColSymPacked,
				   Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(2*n);
    dspcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  ColSymPacked, Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); float rcond(0);
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    cspcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   ColSymPacked, Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); double rcond(0);
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    zspcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowSym and Upper ***/
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<float, Prop0, RowSym,
				  Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(2*n);
    ssycon_(&uplo, &n, A.GetData(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<double, Prop0, RowSym,
				   Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(2*n);
    dsycon_(&uplo, &n, A.GetData(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0, RowSym,
				  Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); float rcond(0);
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    csycon_(&uplo, &n, A.GetDataVoid(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   RowSym, Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); double rcond(0);
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    zsycon_(&uplo, &n, A.GetDataVoid(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowSymPacked and Upper ***/
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<float, Prop0, RowSymPacked,
				  Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(2*n);
    sspcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<double, Prop0, RowSymPacked,
				   Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(2*n);
    dspcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  RowSymPacked, Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); float rcond(0);
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    cspcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   RowSymPacked, Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); double rcond(0);
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    zspcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColHerm and Upper ***/
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  ColHerm, Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); float rcond(0);
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    checon_(&uplo, &n, A.GetData(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   ColHerm, Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm,  double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); double rcond(0);
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    zhecon_(&uplo, &n, A.GetData(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColHermPacked and Upper ***/
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  ColHermPacked, Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); float rcond(0);
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    chpcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   ColHermPacked, Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U');
    
    int n = A.GetM(); double rcond(0);
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    zhpcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowHerm and Upper ***/
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  RowHerm, Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); float rcond(0);
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    checon_(&uplo, &n, A.GetData(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   RowHerm, Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); double rcond(0);
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    zhecon_(&uplo, &n, A.GetData(), &n, P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowHermPacked and Upper ***/
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  RowHermPacked, Allocator0>& A,
				  Vector<int, Vect_Full, Allocator1>& P,
				  SeldonNorm norm, float anorm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); float rcond(0);
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    chpcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0, class Allocator1>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   RowHermPacked, Allocator0>& A,
				   Vector<int, Vect_Full, Allocator1>& P,
				   SeldonNorm norm, double anorm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L');
    
    int n = A.GetM(); double rcond(0);
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    zhpcon_(&uplo, &n, A.GetData(), P.GetData(), &anorm, &rcond, 
	    work.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColUpTriang and NonUnit ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<float, Prop0, ColUpTriang,
				  Allocator0>& A, SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    strcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<double, Prop0, ColUpTriang,
				   Allocator0>& A, SeldonNorm norm, 
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtrcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  ColUpTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   ColUpTriang, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColUpTriang ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<float, Prop0, ColUpTriang,
				  Allocator0>& A, SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    strcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<double, Prop0, ColUpTriang,
				   Allocator0>& A, SeldonNorm norm, 
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char();
    
    int n = A.GetM(); double rcond(0);
    char diag = DiagA.Char();
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtrcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<complex<float>, Prop0,
				  ColUpTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<complex<double>, Prop0,
				   ColUpTriang, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColLoTriang and NonUnit ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<float, Prop0,
				  ColLoTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    strcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<double, Prop0, ColLoTriang,
				   Allocator0>& A, SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtrcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  ColLoTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   ColLoTriang, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColLoTriang ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<float, Prop0,
				  ColLoTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    strcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<double, Prop0, ColLoTriang,
				   Allocator0>& A, SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtrcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<complex<float>, Prop0,
				  ColLoTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<complex<double>, Prop0,
				   ColLoTriang, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColUpTriangPacked and NonUnit ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<float, Prop0,
				  ColUpTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    stpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<double, Prop0,
				   ColUpTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  ColUpTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   ColUpTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColUpTriangPacked ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<float, Prop0,
				  ColUpTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    stpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<double, Prop0,
				   ColUpTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<complex<float>, Prop0,
				  ColUpTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<complex<double>, Prop0,
				   ColUpTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColLoTriangPacked and NonUnit ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<float, Prop0,
				  ColLoTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    stpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<double, Prop0,
				   ColLoTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  ColLoTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   ColLoTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** ColLoTriangPacked ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<float, Prop0,
				  ColLoTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    stpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<double, Prop0,
				   ColLoTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<complex<float>, Prop0,
				  ColLoTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<complex<double>, Prop0,
				   ColLoTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.Char();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowUpTriang and NonUnit ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<float, Prop0, RowUpTriang,
				  Allocator0>& A, SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    strcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<double, Prop0, RowUpTriang,
				   Allocator0>& A, SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtrcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  RowUpTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   RowUpTriang, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowUpTriang ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<float, Prop0, RowUpTriang,
				  Allocator0>& A, SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    strcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<double, Prop0, RowUpTriang,
				   Allocator0>& A, SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtrcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<complex<float>, Prop0,
				  RowUpTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<complex<double>, Prop0,
				   RowUpTriang, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowLoTriang and NonUnit ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<float, Prop0,
				  RowLoTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    strcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<double, Prop0,
				   RowLoTriang, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtrcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  RowLoTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   RowLoTriang, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowLoTriang ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<float, Prop0,
				  RowLoTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    strcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<double, Prop0,
				   RowLoTriang, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtrcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &n, &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<complex<float>, Prop0,
				  RowLoTriang, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<complex<double>, Prop0,
				   RowLoTriang, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztrcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &n, &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }  
  
  
  /*** RowUpTriangPacked and NonUnit ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<float, Prop0,
				  RowUpTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    stpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<double, Prop0,
				   RowUpTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  RowUpTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   RowUpTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowUpTriangPacked ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<float, Prop0,
				  RowUpTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); Vector<float, Vect_Full, Allocator0> work(3*n);
    stpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<double, Prop0,
				   RowUpTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<complex<float>, Prop0,
				  RowUpTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<complex<double>, Prop0,
				   RowUpTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('L'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowLoTriangPacked and NonUnit ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<float, Prop0,
				  RowLoTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); 
    Vector<float, Vect_Full, Allocator0> work(3*n);
    stpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<double, Prop0,
				   RowLoTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const Matrix<complex<float>, Prop0,
				  RowLoTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const Matrix<complex<double>, Prop0,
				   RowLoTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar(); char diag('N');
    
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  /*** RowLoTriangPacked ***/
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<float, Prop0,
				  RowLoTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<int> iwork(n); 
    Vector<float, Vect_Full, Allocator0> work(3*n);
    stpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<double, Prop0,
				   RowLoTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<int> iwork(n); Vector<double, Vect_Full, Allocator0> work(3*n);
    dtpcon_(&norm_type, &uplo, &diag, &n, A.GetData(), &rcond, 
	    work.GetData(), iwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  float ReciprocalConditionNumber(const SeldonDiag& DiagA,
				  const Matrix<complex<float>, Prop0,
				  RowLoTriangPacked, Allocator0>& A,
				  SeldonNorm norm,
				  LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); float rcond(0);
    Vector<float> rwork(n); 
    Vector<complex<float>, Vect_Full, Allocator0> work(2*n);
    ctpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  template<class Prop0, class Allocator0>
  double ReciprocalConditionNumber(const SeldonDiag& DiagA,
				   const Matrix<complex<double>, Prop0,
				   RowLoTriangPacked, Allocator0>& A,
				   SeldonNorm norm,
				   LapackInfo& info = lapack_info)
  {
    char uplo('U'); char norm_type = norm.RevChar();
    char diag = DiagA.Char();
    int n = A.GetM(); double rcond(0);
    Vector<double> rwork(n); 
    Vector<complex<double>, Vect_Full, Allocator0> work(2*n);
    ztpcon_(&norm_type, &uplo, &diag, &n, A.GetDataVoid(), &rcond, 
	    work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    return rcond;
  }
  
  
  // ReciprocalConditionNumber //
  ///////////////////////////////
  
  
  
  //////////////////////
  // RefineSolutionLU //
  
  
  /*** ColMajor and NoTrans ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<float, Prop0, ColMajor, Allocator0>& A,
			const Matrix<float, Prop0, ColMajor,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<float, Vect_Full, Allocator3>& x,
			const Vector<float, Vect_Full, Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('N');
    Vector<float, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    sgerfs_(&trans, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m,
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<double, Prop0, ColMajor, Allocator0>& A,
			const Matrix<double, Prop0, ColMajor,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<double, Vect_Full, Allocator3>& x,
			const Vector<double, Vect_Full, Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('N');
    Vector<double, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    dgerfs_(&trans, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m,
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<float>, Prop0,
			ColMajor, Allocator0>& A,
			const Matrix<complex<float>, Prop0,
			ColMajor, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<float>, Vect_Full, Allocator3>& x,
			const Vector<complex<float>, Vect_Full,
			Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('N');
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    cgerfs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m,
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<double>, Prop0,
			ColMajor, Allocator0>& A,
			const Matrix<complex<double>, Prop0,
			ColMajor, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			const Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('N');
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    zgerfs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m,
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColMajor ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const SeldonTranspose& TransA,
			const Matrix<float, Prop0, ColMajor, Allocator0>& A,
			const Matrix<float, Prop0, ColMajor,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<float, Vect_Full, Allocator3>& x,
			const Vector<float, Vect_Full, Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.Char();
    Vector<float, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    sgerfs_(&trans, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m,
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const SeldonTranspose& TransA,
			const Matrix<double, Prop0, ColMajor, Allocator0>& A,
			const Matrix<double, Prop0, ColMajor,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<double, Vect_Full, Allocator3>& x,
			const Vector<double, Vect_Full, Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.Char();
    Vector<double, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    dgerfs_(&trans, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m,
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, 
		   const Matrix<complex<float>, Prop0, ColMajor,
		   Allocator0>& A,
		   const Matrix<complex<float>, Prop0, ColMajor,
		   Allocator1>& Alu,
		   const Vector<int, Vect_Full, Allocator2>& P,
		   Vector<complex<float>, Vect_Full, Allocator3>& x,
		   const Vector<complex<float>, Vect_Full, Allocator4>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.Char();
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    cgerfs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m,
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const SeldonTranspose& TransA, 
			const Matrix<complex<double>, Prop0, ColMajor,
			Allocator0>& A,
			const Matrix<complex<double>, Prop0, ColMajor,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			const Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.Char();
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    zgerfs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m, 
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, 
	    &ferr, &berr, work.GetDataVoid(), 
	    rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /*** RowMajor and NoTrans ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<float, Prop0, RowMajor, Allocator0>& A,
			const Matrix<float, Prop0, RowMajor,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<float, Vect_Full, Allocator3>& x,
			const Vector<float, Vect_Full, Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('T');
    Vector<float, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    sgerfs_(&trans, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m, 
	    P.GetData(), b.GetData(), &m, x.GetData(), &m, 
	    &ferr, &berr, work.GetData(), 
	    iwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<double, Prop0, RowMajor, Allocator0>& A,
			const Matrix<double, Prop0, RowMajor,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<double, Vect_Full, Allocator3>& x,
			const Vector<double, Vect_Full, Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('T');
    Vector<double, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    dgerfs_(&trans, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m, 
	    P.GetData(), b.GetData(), &m, x.GetData(), &m, 
	    &ferr, &berr, work.GetData(), 
	    iwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<float>, Prop0,
			RowMajor, Allocator0>& A,
			const Matrix<complex<float>, Prop0,
			RowMajor, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<float>, Vect_Full, Allocator3>& x,
			const Vector<complex<float>, Vect_Full,
			Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('T');
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    cgerfs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m, 
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr, 
	    &berr, work.GetData(), rwork.GetData(), 
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<double>, Prop0,
			RowMajor, Allocator0>& A,
			const Matrix<complex<double>, Prop0,
			RowMajor, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			const Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans('T');
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    zgerfs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m, 
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr, 
	    &berr, work.GetData(), rwork.GetData(), 
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** RowMajor ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const SeldonTranspose& TransA, 
			const Matrix<float, Prop0, RowMajor, Allocator0>& A,
			const Matrix<float, Prop0, RowMajor,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<float, Vect_Full, Allocator3>& x,
			const Vector<float, Vect_Full, Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.RevChar();
    Vector<float, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    sgerfs_(&trans, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m, 
	    P.GetData(), b.GetData(), &m, x.GetData(), &m, 
	    &ferr, &berr, work.GetData(), 
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const SeldonTranspose& TransA,
			const Matrix<double, Prop0, RowMajor, Allocator0>& A,
			const Matrix<double, Prop0, RowMajor,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<double, Vect_Full, Allocator3>& x,
			const Vector<double, Vect_Full, Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.RevChar();
    Vector<double, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    dgerfs_(&trans, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m, 
	    P.GetData(), b.GetData(), &m, x.GetData(), &m, 
	    &ferr, &berr, work.GetData(), 
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const SeldonTranspose& TransA,
			const Matrix<complex<float>, Prop0, RowMajor,
			Allocator0>& A,
			const Matrix<complex<float>, Prop0, RowMajor,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<float>, Vect_Full, Allocator3>& x,
			Vector<complex<float>, Vect_Full, Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.RevChar();
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
    cgerfs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m, 
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, 
	    &ferr, &berr, work.GetDataVoid(), 
	    rwork.GetData(), &lapack_info.GetInfoRef() );
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const SeldonTranspose& TransA,
			const Matrix<complex<double>, Prop0, RowMajor,
			Allocator0>& A,
			const Matrix<complex<double>, Prop0, RowMajor,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char trans = TransA.RevChar();
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
    zgerfs_(&trans, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m, 
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, 
	    &ferr, &berr, work.GetDataVoid(), 
	    rwork.GetData(), &lapack_info.GetInfoRef());
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
  }
  
  
  /*** ColSym and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<float, Prop0, ColSym, Allocator0>& A,
			const Matrix<float, Prop0, ColSym,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<float, Vect_Full, Allocator3>& x,
			const Vector<float, Vect_Full, Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<float, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    ssyrfs_(&uplo, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m,
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<double, Prop0, ColSym, Allocator0>& A,
			const Matrix<double, Prop0, ColSym,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<double, Vect_Full, Allocator3>& x,
			const Vector<double, Vect_Full, Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<double, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    dsyrfs_(&uplo, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m,
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<float>, Prop0,
			ColSym, Allocator0>& A,
			const Matrix<complex<float>, Prop0,
			ColSym, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<float>, Vect_Full, Allocator3>& x,
			const Vector<complex<float>, Vect_Full,
			Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    csyrfs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m,
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<double>, Prop0,
			ColSym, Allocator0>& A,
			const Matrix<complex<double>, Prop0,
			ColSym, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			const Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    zsyrfs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m,
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColSymPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<float, Prop0, ColSymPacked,
			Allocator0>& A,
			const Matrix<float, Prop0, ColSymPacked,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<float, Vect_Full, Allocator3>& x,
			const Vector<float, Vect_Full, Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<float, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    ssprfs_(&uplo, &m, &nrhs, A.GetData(), Alu.GetData(),
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<double, Prop0, ColSymPacked,
			Allocator0>& A,
			const Matrix<double, Prop0, ColSymPacked,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<double, Vect_Full, Allocator3>& x,
			const Vector<double, Vect_Full, Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<double, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    dsprfs_(&uplo, &m, &nrhs, A.GetData(), Alu.GetData(),
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<float>, Prop0,
			ColSymPacked, Allocator0>& A,
			const Matrix<complex<float>, Prop0,
			ColSymPacked, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<float>, Vect_Full, Allocator3>& x,
			const Vector<complex<float>, Vect_Full,
			Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    csprfs_(&uplo, &m, &nrhs, A.GetDataVoid(), Alu.GetDataVoid(),
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<double>, Prop0,
			ColSymPacked, Allocator0>& A,
			const Matrix<complex<double>, Prop0,
			ColSymPacked, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			const Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    zsprfs_(&uplo, &m, &nrhs, A.GetDataVoid(), Alu.GetDataVoid(),
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  /*** RowSym and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<float, Prop0, RowSym, Allocator0>& A,
			const Matrix<float, Prop0, RowSym,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<float, Vect_Full, Allocator3>& x,
			const Vector<float, Vect_Full, Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<float, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    ssyrfs_(&uplo, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m,
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<double, Prop0, RowSym, Allocator0>& A,
			const Matrix<double, Prop0, RowSym,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<double, Vect_Full, Allocator3>& x,
			const Vector<double, Vect_Full, Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<double, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    dsyrfs_(&uplo, &m, &nrhs, A.GetData(), &m, Alu.GetData(), &m,
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<float>, Prop0,
			RowSym, Allocator0>& A,
			const Matrix<complex<float>, Prop0,
			RowSym, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<float>, Vect_Full, Allocator3>& x,
			const Vector<complex<float>, Vect_Full,
			Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    csyrfs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m, 
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<double>, Prop0,
			RowSym, Allocator0>& A,
			const Matrix<complex<double>, Prop0,
			RowSym, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			const Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    zsyrfs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m, 
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
    
  
  /*** RowSymPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<float, Prop0, RowSymPacked,
			Allocator0>& A,
			const Matrix<float, Prop0, RowSymPacked,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<float, Vect_Full, Allocator3>& x,
			const Vector<float, Vect_Full, Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<float, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    ssprfs_(&uplo, &m, &nrhs, A.GetData(), Alu.GetData(),
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<double, Prop0, RowSymPacked,
			Allocator0>& A,
			const Matrix<double, Prop0, RowSymPacked,
			Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<double, Vect_Full, Allocator3>& x,
			const Vector<double, Vect_Full, Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<double, Vect_Full, Allocator3> work(3*m);
    Vector<int> iwork(m);
    dsprfs_(&uplo, &m, &nrhs, A.GetData(), Alu.GetData(),
	    P.GetData(), b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<float>, Prop0,
			RowSymPacked, Allocator0>& A,
			const Matrix<complex<float>, Prop0,
			RowSymPacked, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<float>, Vect_Full, Allocator3>& x,
			const Vector<complex<float>, Vect_Full,
			Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    csprfs_(&uplo, &m, &nrhs, A.GetDataVoid(), Alu.GetDataVoid(),
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<double>, Prop0,
			RowSymPacked, Allocator0>& A,
			const Matrix<complex<double>, Prop0,
			RowSymPacked, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			const Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    zsprfs_(&uplo, &m, &nrhs, A.GetDataVoid(), Alu.GetDataVoid(),
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColHerm and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<float>, Prop0,
			ColHerm, Allocator0>& A,
			const Matrix<complex<float>, Prop0,
			ColHerm, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<float>, Vect_Full, Allocator3>& x,
			const Vector<complex<float>, Vect_Full,
			Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    cherfs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m,
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<double>, Prop0,
			ColHerm, Allocator0>& A,
			const Matrix<complex<double>, Prop0,
			ColHerm, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			const Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    zherfs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m, 
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColHermPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<float>, Prop0,
			ColHermPacked, Allocator0>& A,
			const Matrix<complex<float>, Prop0,
			ColHermPacked, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<float>, Vect_Full, Allocator3>& x,
			const Vector<complex<float>, Vect_Full,
			Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    chprfs_(&uplo, &m, &nrhs, A.GetDataVoid(), Alu.GetDataVoid(),
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<double>, Prop0,
			ColHermPacked, Allocator0>& A,
			const Matrix<complex<double>, Prop0,
			ColHermPacked, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			const Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    zhprfs_(&uplo, &m, &nrhs, A.GetDataVoid(), Alu.GetDataVoid(),
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
  }
  
  
  /*** RowHerm and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<float>, Prop0,
			RowHerm, Allocator0>& A,
			const Matrix<complex<float>, Prop0,
			RowHerm, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<float>, Vect_Full, Allocator3>& x,
			Vector<complex<float>, Vect_Full,
			Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    Conjugate(b); Conjugate(x);
    cherfs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m, 
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
    Conjugate(b); Conjugate(x);
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<double>, Prop0,
			RowHerm, Allocator0>& A,
			const Matrix<complex<double>, Prop0,
			RowHerm, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    Conjugate(b); Conjugate(x);
    zherfs_(&uplo, &m, &nrhs, A.GetDataVoid(), &m, Alu.GetDataVoid(), &m, 
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
    Conjugate(b); Conjugate(x);
  }
  

  /*** RowHermPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<float>, Prop0,
			RowHermPacked, Allocator0>& A,
			const Matrix<complex<float>, Prop0,
			RowHermPacked, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<float>, Vect_Full, Allocator3>& x,
			Vector<complex<float>, Vect_Full,
			Allocator4>& b,
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<complex<float>, Vect_Full, Allocator3> work(2*m);
    Vector<float> rwork(m);
    Conjugate(b); Conjugate(x);
    chprfs_(&uplo, &m, &nrhs, A.GetDataVoid(), Alu.GetDataVoid(),
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
    Conjugate(b); Conjugate(x);
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2,
	    class Allocator3, class Allocator4>
  void RefineSolutionLU(const Matrix<complex<double>, Prop0,
			RowHermPacked, Allocator0>& A,
			const Matrix<complex<double>, Prop0,
			RowHermPacked, Allocator1>& Alu,
			const Vector<int, Vect_Full, Allocator2>& P,
			Vector<complex<double>, Vect_Full, Allocator3>& x,
			Vector<complex<double>, Vect_Full,
			Allocator4>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
    CheckDim(Alu, x, b, "RefineSolutionLU(A, Alu, pivot, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    Vector<complex<double>, Vect_Full, Allocator3> work(2*m);
    Vector<double> rwork(m);
    Conjugate(b); Conjugate(x);
    zhprfs_(&uplo, &m, &nrhs, A.GetDataVoid(), Alu.GetDataVoid(),
	    P.GetData(), b.GetDataVoid(), &m, x.GetDataVoid(), &m, &ferr,
	    &berr, work.GetData(), rwork.GetData(),
	    &lapack_info.GetInfoRef() );
    Conjugate(b); Conjugate(x);
  }
  
  
  /*** ColUpTriang, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<float, Prop0, ColUpTriang,
			Allocator0>& A,
			Vector<float, Vect_Full, Allocator1>& x, 
			const Vector<float, Vect_Full, Allocator2>& b, 
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('N'); char diag('N');
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    strrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<double, Prop0, ColUpTriang,
			Allocator0>& A,
			Vector<double, Vect_Full, Allocator1>& x,
			const Vector<double, Vect_Full, Allocator2>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('N'); char diag('N');
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<float>, Prop0, ColUpTriang,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('N'); char diag('N');
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<double>, Prop0, ColUpTriang,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U'); 
    char trans('N'); char diag('N');
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }

  
  /*** ColUpTriang ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<float, Prop0, ColUpTriang,
		   Allocator0>& A,
		   Vector<float, Vect_Full, Allocator1>& x, 
		   const Vector<float, Vect_Full, Allocator2>& b, 
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    strrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<double, Prop0, ColUpTriang,
		   Allocator0>& A,
		   Vector<double, Vect_Full, Allocator1>& x,
		   const Vector<double, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<float>, Prop0, ColUpTriang,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<double>, Prop0, ColUpTriang,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColLoTriang, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<float, Prop0, ColLoTriang,
			Allocator0>& A,
			Vector<float, Vect_Full, Allocator1>& x, 
			const Vector<float, Vect_Full, Allocator2>& b, 
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('N'); char diag('N');
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    strrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<double, Prop0, ColLoTriang,
			Allocator0>& A,
			Vector<double, Vect_Full, Allocator1>& x,
			const Vector<double, Vect_Full, Allocator2>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('N'); char diag('N');
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<float>, Prop0, ColLoTriang,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('N'); char diag('N');
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<double>, Prop0, ColLoTriang,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L'); 
    char trans('N'); char diag('N');
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColLoTriang ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<float, Prop0, ColLoTriang,
		   Allocator0>& A,
		   Vector<float, Vect_Full, Allocator1>& x, 
		   const Vector<float, Vect_Full, Allocator2>& b, 
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    strrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<double, Prop0, ColLoTriang,
		   Allocator0>& A,
		   Vector<double, Vect_Full, Allocator1>& x,
		   const Vector<double, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<float>, Prop0, ColLoTriang,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<double>, Prop0, ColLoTriang,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColUpTriangPacked, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<float, Prop0, ColUpTriangPacked,
			Allocator0>& A,
			Vector<float, Vect_Full, Allocator1>& x, 
			const Vector<float, Vect_Full, Allocator2>& b, 
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('N'); char diag('N');
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    stprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<double, Prop0, ColUpTriangPacked,
			Allocator0>& A,
			Vector<double, Vect_Full, Allocator1>& x,
			const Vector<double, Vect_Full, Allocator2>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('N'); char diag('N');
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<float>, Prop0, ColUpTriangPacked,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('N'); char diag('N');
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<double>, Prop0, ColUpTriangPacked,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U'); 
    char trans('N'); char diag('N');
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColUpTriangPacked ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<float, Prop0, ColUpTriangPacked,
		   Allocator0>& A,
		   Vector<float, Vect_Full, Allocator1>& x, 
		   const Vector<float, Vect_Full, Allocator2>& b, 
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    stprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<double, Prop0, ColUpTriangPacked,
		   Allocator0>& A,
		   Vector<double, Vect_Full, Allocator1>& x,
		   const Vector<double, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<float>, Prop0, ColUpTriangPacked,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<double>, Prop0, ColUpTriangPacked,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColLoTriangPacked, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<float, Prop0, ColLoTriangPacked,
			Allocator0>& A,
			Vector<float, Vect_Full, Allocator1>& x, 
			const Vector<float, Vect_Full, Allocator2>& b, 
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('N'); char diag('N');
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    stprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<double, Prop0, ColLoTriangPacked,
			Allocator0>& A,
			Vector<double, Vect_Full, Allocator1>& x,
			const Vector<double, Vect_Full, Allocator2>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('N'); char diag('N');
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<float>, Prop0, ColLoTriangPacked,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('N'); char diag('N');
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<double>, Prop0, ColLoTriangPacked,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L'); 
    char trans('N'); char diag('N');
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  /*** ColLoTriangPacked ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<float, Prop0, ColLoTriangPacked,
		   Allocator0>& A,
		   Vector<float, Vect_Full, Allocator1>& x, 
		   const Vector<float, Vect_Full, Allocator2>& b, 
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    stprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<double, Prop0, ColLoTriangPacked,
		   Allocator0>& A,
		   Vector<double, Vect_Full, Allocator1>& x,
		   const Vector<double, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<float>, Prop0, ColLoTriangPacked,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<double>, Prop0, ColLoTriangPacked,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans = TransA.Char(); char diag = DiagA.Char();
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  /*** RowUpTriang, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<float, Prop0, RowUpTriang,
			Allocator0>& A,
			Vector<float, Vect_Full, Allocator1>& x, 
			const Vector<float, Vect_Full, Allocator2>& b, 
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('T'); char diag('N');
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    strrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<double, Prop0, RowUpTriang,
			Allocator0>& A,
			Vector<double, Vect_Full, Allocator1>& x,
			const Vector<double, Vect_Full, Allocator2>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('T'); char diag('N');
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<float>, Prop0, RowUpTriang,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('T'); char diag('N');
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<double>, Prop0, RowUpTriang,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L'); 
    char trans('T'); char diag('N');
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }

  
  /*** RowUpTriang ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<float, Prop0, RowUpTriang,
		   Allocator0>& A,
		   Vector<float, Vect_Full, Allocator1>& x, 
		   const Vector<float, Vect_Full, Allocator2>& b, 
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L'); 
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    strrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<double, Prop0, RowUpTriang,
		   Allocator0>& A,
		   Vector<double, Vect_Full, Allocator1>& x,
		   const Vector<double, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L'); 
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<float>, Prop0, RowUpTriang,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L'); 
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
    ctrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<double>, Prop0, RowUpTriang,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L'); 
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
    ztrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
  }
  
  
  /*** RowLoTriang, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<float, Prop0, RowLoTriang,
			Allocator0>& A,
			Vector<float, Vect_Full, Allocator1>& x, 
			const Vector<float, Vect_Full, Allocator2>& b, 
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('T'); char diag('N');
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    strrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<double, Prop0, RowLoTriang,
			Allocator0>& A,
			Vector<double, Vect_Full, Allocator1>& x,
			const Vector<double, Vect_Full, Allocator2>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('T'); char diag('N');
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<float>, Prop0, RowLoTriang,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('T'); char diag('N');
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<double>, Prop0, RowLoTriang,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U'); 
    char trans('T'); char diag('N');
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  /*** RowLoTriang ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<float, Prop0, RowLoTriang,
		   Allocator0>& A,
		   Vector<float, Vect_Full, Allocator1>& x, 
		   const Vector<float, Vect_Full, Allocator2>& b, 
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    strrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<double, Prop0, RowLoTriang,
		   Allocator0>& A,
		   Vector<double, Vect_Full, Allocator1>& x,
		   const Vector<double, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(), &m,
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<float>, Prop0, RowLoTriang,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
    ctrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<double>, Prop0, RowLoTriang,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U'); 
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
    ztrrfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(), &m,
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
  }
  
  
  /*** RowUpTriangPacked, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<float, Prop0, RowUpTriangPacked,
			Allocator0>& A,
			Vector<float, Vect_Full, Allocator1>& x, 
			const Vector<float, Vect_Full, Allocator2>& b, 
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('T'); char diag('N');
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    stprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<double, Prop0, RowUpTriangPacked,
			Allocator0>& A,
			Vector<double, Vect_Full, Allocator1>& x,
			const Vector<double, Vect_Full, Allocator2>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('T'); char diag('N');
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<float>, Prop0, RowUpTriangPacked,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans('T'); char diag('N');
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<double>, Prop0, RowUpTriangPacked,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L'); 
    char trans('T'); char diag('N');
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  /*** RowUpTriangPacked ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<float, Prop0, RowUpTriangPacked,
		   Allocator0>& A,
		   Vector<float, Vect_Full, Allocator1>& x, 
		   const Vector<float, Vect_Full, Allocator2>& b, 
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    stprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<double, Prop0, RowUpTriangPacked,
		   Allocator0>& A,
		   Vector<double, Vect_Full, Allocator1>& x,
		   const Vector<double, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<float>, Prop0, RowUpTriangPacked,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
    ctprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<double>, Prop0, RowUpTriangPacked,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('L'); 
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
    ztprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
  }
  
  
  /*** RowLoTriangPacked, NoTrans and NonUnit ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<float, Prop0, RowLoTriangPacked,
			Allocator0>& A,
			Vector<float, Vect_Full, Allocator1>& x, 
			const Vector<float, Vect_Full, Allocator2>& b, 
			float& ferr, float& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('T'); char diag('N');
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    stprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void RefineSolutionLU(const Matrix<double, Prop0, RowLoTriangPacked,
			Allocator0>& A,
			Vector<double, Vect_Full, Allocator1>& x,
			const Vector<double, Vect_Full, Allocator2>& b,
			double& ferr, double& berr,
			LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('T'); char diag('N');
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<float>, Prop0, RowLoTriangPacked,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   const Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans('T'); char diag('N');
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    ctprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const Matrix<complex<double>, Prop0, RowLoTriangPacked,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   const Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U'); 
    char trans('T'); char diag('N');
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    ztprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  /*** RowLoTriangPacked ***/
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<float, Prop0, RowLoTriangPacked,
		   Allocator0>& A,
		   Vector<float, Vect_Full, Allocator1>& x, 
		   const Vector<float, Vect_Full, Allocator2>& b, 
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<float, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    stprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }

  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<double, Prop0, RowLoTriangPacked,
		   Allocator0>& A,
		   Vector<double, Vect_Full, Allocator1>& x,
		   const Vector<double, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<double, Vect_Full, Allocator1> work(3*m);
    Vector<int> iwork(m);
    dtprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetData(),
	    b.GetData(), &m, x.GetData(), &m,
	    &ferr, &berr, work.GetData(),
	    iwork.GetData(), &lapack_info.GetInfoRef() );
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<float>, Prop0, RowLoTriangPacked,
		   Allocator0>& A,
		   Vector<complex<float>, Vect_Full, Allocator1>& x,
		   Vector<complex<float>, Vect_Full, Allocator2>& b,
		   float& ferr, float& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<complex<float>, Vect_Full, Allocator1> work(2*m);
    Vector<float> rwork(m);
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
    ctprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
  }
  
  
  template <class Prop0, class Allocator0,
	    class Allocator1, class Allocator2>
  void
  RefineSolutionLU(const SeldonTranspose& TransA, const SeldonDiag& DiagA,
		   const Matrix<complex<double>, Prop0, RowLoTriangPacked,
		   Allocator0>& A,
		   Vector<complex<double>, Vect_Full, Allocator1>& x,
		   Vector<complex<double>, Vect_Full, Allocator2>& b,
		   double& ferr, double& berr,
		   LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, x, b, "RefineSolutionLU(A, Alu, X, Y)");
#endif
    
    int m = A.GetM();
    int nrhs = 1;
    char uplo('U');
    char trans = TransA.RevChar(); char diag = DiagA.Char();
    Vector<complex<double>, Vect_Full, Allocator1> work(2*m);
    Vector<double> rwork(m);
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
    ztprfs_(&uplo, &trans, &diag, &m, &nrhs, A.GetDataVoid(),
	    b.GetDataVoid(), &m, x.GetDataVoid(), &m,
	    &ferr, &berr, work.GetDataVoid(),
	    rwork.GetData(), &lapack_info.GetInfoRef() );
    if (TransA.ConjTrans())
      { 
	Conjugate(b);
	Conjugate(x);
      }
  }
  
  
  // RefineSolutionLU //
  //////////////////////
  
  
  
  ////////////////
  // GetInverse //
  
  
  /*** ColMajor ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, ColMajor, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<float, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    sgetri_(&m, A.GetData(), &m, pivot.GetData(), work.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, ColMajor, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<double, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    dgetri_(&m, A.GetData(), &m, pivot.GetData(), work.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, ColMajor, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<float>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    cgetri_(&m, A.GetDataVoid(), &m, pivot.GetData(), 
	    work.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, ColMajor, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<double>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    zgetri_(&m, A.GetDataVoid(), &m, pivot.GetData(), 
	    work.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  /*** RowMajor ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, RowMajor, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<float, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    sgetri_(&m, A.GetData(), &m, pivot.GetData(), work.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, RowMajor, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<double, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    dgetri_(&m, A.GetData(), &m, pivot.GetData(), work.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, RowMajor, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<float>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    cgetri_(&m, A.GetDataVoid(), &m, pivot.GetData(),
	    work.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, RowMajor, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<double>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    zgetri_(&m, A.GetDataVoid(), &m, pivot.GetData(),
	    work.GetDataVoid(), &m, &lapack_info.GetInfoRef());
  }
  
  
  /*** ColSym and Upper ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, ColSym, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<float, Vect_Full, Allocator0> work(2*m);
    GetLU(A, pivot, info);
    ssytri_(&uplo, &m, A.GetData(), &m, pivot.GetData(), work.GetData(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, ColSym, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<double, Vect_Full, Allocator0> work(2*m);
    GetLU(A, pivot, info);
    dsytri_(&uplo, &m, A.GetData(), &m, pivot.GetData(), work.GetData(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, ColSym, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<float>, Vect_Full, Allocator0> work(2*m);
    GetLU(A, pivot, info);
    csytri_(&uplo, &m, A.GetDataVoid(), &m, pivot.GetData(),
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, ColSym, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<double>, Vect_Full, Allocator0> work(2*m);
    GetLU(A, pivot, info);
    zsytri_(&uplo, &m, A.GetDataVoid(), &m, pivot.GetData(), 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  /*** ColSymPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, ColSymPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<float, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    ssptri_(&uplo, &m, A.GetData(), pivot.GetData(), work.GetData(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, ColSymPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<double, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    dsptri_(&uplo, &m, A.GetData(), pivot.GetData(), work.GetData(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, ColSymPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<float>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    csptri_(&uplo, &m, A.GetDataVoid(), pivot.GetData(),
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, ColSymPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<double>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    zsptri_(&uplo, &m, A.GetDataVoid(), pivot.GetData(), 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  /*** RowSym and Upper ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, RowSym, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<float, Vect_Full, Allocator0> work(2*m);
    GetLU(A, pivot, info);
    ssytri_(&uplo, &m, A.GetData(), &m, pivot.GetData(), work.GetData(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, RowSym, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<double, Vect_Full, Allocator0> work(2*m);
    GetLU(A, pivot, info);
    dsytri_(&uplo, &m, A.GetData(), &m, pivot.GetData(), work.GetData(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, RowSym, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<float>, Vect_Full, Allocator0> work(2*m);
    GetLU(A, pivot, info);
    csytri_(&uplo, &m, A.GetDataVoid(), &m, pivot.GetData(),
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, RowSym, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<double>, Vect_Full, Allocator0> work(2*m);
    GetLU(A, pivot, info);
    zsytri_(&uplo, &m, A.GetDataVoid(), &m, pivot.GetData(), 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  /*** RowSymPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, RowSymPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<float, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    ssptri_(&uplo, &m, A.GetData(), pivot.GetData(), work.GetData(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, RowSymPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<double, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    dsptri_(&uplo, &m, A.GetData(), pivot.GetData(), work.GetData(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, RowSymPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<float>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    csptri_(&uplo, &m, A.GetDataVoid(), pivot.GetData(),
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, RowSymPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<double>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    zsptri_(&uplo, &m, A.GetDataVoid(), pivot.GetData(), 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  /*** ColHerm and Upper ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, ColHerm, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<float>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    chetri_(&uplo, &m, A.GetDataVoid(), &m, pivot.GetData(),
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, ColHerm, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<double>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    zhetri_(&uplo, &m, A.GetDataVoid(), &m, pivot.GetData(), 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  /*** ColHermPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, ColHermPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<float>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    chptri_(&uplo, &m, A.GetDataVoid(), pivot.GetData(),
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, ColHermPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<double>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    zhptri_(&uplo, &m, A.GetDataVoid(), pivot.GetData(), 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  /*** RowHerm and Upper ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, RowHerm, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<float>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    chetri_(&uplo, &m, A.GetDataVoid(), &m, pivot.GetData(),
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, RowHerm, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<double>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    zhetri_(&uplo, &m, A.GetDataVoid(), &m, pivot.GetData(), 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  /*** RowHermPacked and Upper ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, RowHermPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<float>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    chptri_(&uplo, &m, A.GetDataVoid(), pivot.GetData(),
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, RowHermPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L');
    Vector<int, Vect_Full, CallocAlloc<int> > pivot;
    Vector<complex<double>, Vect_Full, Allocator0> work(m);
    GetLU(A, pivot, info);
    zhptri_(&uplo, &m, A.GetDataVoid(), pivot.GetData(), 
	    work.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  /*** ColUpTriang and NonUnit ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, ColUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    strtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, ColUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    dtrtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, ColUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    ctrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, ColUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    ztrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** ColUpTriang ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<float, Prop0, ColUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    strtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<double, Prop0, ColUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    dtrtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<float>, Prop0, ColUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    ctrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<double>, Prop0, ColUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    ztrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** ColLoTriang and NonUnit ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, ColLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    strtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, ColLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    dtrtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, ColLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    ctrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, ColLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    ztrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** ColLoTriang ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<float, Prop0, ColLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    strtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<double, Prop0, ColLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    dtrtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<float>, Prop0, ColLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    ctrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<double>, Prop0, ColLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    ztrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** ColUpTriangPacked and NonUnit ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, ColUpTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    stptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, ColUpTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    dtptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, ColUpTriangPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    ctptri_(&uplo, &diag, &m, A.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, ColUpTriangPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    ztptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** ColUpTriangPacked ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<float, Prop0, ColUpTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    stptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<double, Prop0, ColUpTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    dtptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<float>, Prop0, ColUpTriangPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    ctptri_(&uplo, &diag, &m, A.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<double>, Prop0, ColUpTriangPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    ztptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** ColLoTriangPacked and NonUnit ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, ColLoTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    stptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, ColLoTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    dtptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, ColLoTriangPacked,
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    ctptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, ColLoTriangPacked,
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    ztptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** ColLoTriangPacked ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<float, Prop0, ColLoTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    stptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<double, Prop0, ColLoTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    dtptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<float>, Prop0, ColLoTriangPacked,
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    ctptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<double>, Prop0, ColLoTriangPacked,
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    ztptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** RowUpTriang and NonUnit ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, RowUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    strtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, RowUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    dtrtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, RowUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    ctrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, RowUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    ztrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** RowUpTriang ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<float, Prop0, RowUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    strtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<double, Prop0, RowUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    dtrtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<float>, Prop0, RowUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    ctrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<double>, Prop0, RowUpTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    ztrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** RowLoTriang and NonUnit ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, RowLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    strtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, RowLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    dtrtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, RowLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    ctrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, RowLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    ztrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** RowLoTriang ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<float, Prop0, RowLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    strtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<double, Prop0, RowLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    dtrtri_(&uplo, &diag, &m, A.GetData(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<float>, Prop0, RowLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    ctrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<double>, Prop0, RowLoTriang, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    ztrtri_(&uplo, &diag, &m, A.GetDataVoid(), &m,
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** RowUpTriangPacked and NonUnit ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, RowUpTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    stptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, RowUpTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    dtptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, RowUpTriangPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    ctptri_(&uplo, &diag, &m, A.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, RowUpTriangPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag('N');
    ztptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** RowUpTriangPacked ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<float, Prop0, RowUpTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    stptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<double, Prop0, RowUpTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    dtptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<float>, Prop0, RowUpTriangPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    ctptri_(&uplo, &diag, &m, A.GetDataVoid(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<double>, Prop0, RowUpTriangPacked, 
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('L'); char diag = DiagA.Char();
    ztptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** RowLoTriangPacked and NonUnit ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<float, Prop0, RowLoTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    stptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<double, Prop0, RowLoTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    dtptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<float>, Prop0, RowLoTriangPacked,
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    ctptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(Matrix<complex<double>, Prop0, RowLoTriangPacked,
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag('N');
    ztptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  /*** RowLoTriangPacked ***/
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<float, Prop0, RowLoTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    stptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<double, Prop0, RowLoTriangPacked, Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    dtptri_(&uplo, &diag, &m, A.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<float>, Prop0, RowLoTriangPacked,
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    ctptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  template <class Prop0, class Allocator0>
  void GetInverse(const SeldonDiag& DiagA,
		  Matrix<complex<double>, Prop0, RowLoTriangPacked,
		  Allocator0>& A,
		  LapackInfo& info = lapack_info)
  {
    int m = A.GetM();
    char uplo('U'); char diag = DiagA.Char();
    ztptri_(&uplo, &diag, &m, A.GetDataVoid(),
	    &lapack_info.GetInfoRef());
  }
  
  
  // GetInverse //
  ////////////////
  
  
  
  ///////////////////////
  // GetScalingFactors //
  
  
  /*** ColMajor ***/
  
  
  template<class Prop0, class Allocator0,
	   class Allocator1, class Allocator2>
  void GetScalingFactors(const Matrix<float, Prop0, ColMajor, Allocator0>& A,
			 Vector<float, Vect_Full, Allocator1>& row_scale, 
			 Vector<float, Vect_Full, Allocator2>& col_scale, 
			 float& row_condition_number, 
			 float& col_condition_number, float& amax, 
			 LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, col_scale, row_scale, string("GetScalingFactors(A, X, Y, ")
             + string(" rowcnd, colcnd, amax)"));
#endif
    
    int m = A.GetM(), n = A.GetN();
    int lda = A.GetLD();
    sgeequ_(&m, &n, A.GetData(), &lda, row_scale.GetData(), 
	    col_scale.GetData(), &row_condition_number, &col_condition_number,
	    &amax,  &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop0, class Allocator0,
	   class Allocator1, class Allocator2>
  void GetScalingFactors(const Matrix<double, Prop0, ColMajor, Allocator0>& A,
			 Vector<double, Vect_Full, Allocator1>& row_scale, 
			 Vector<double, Vect_Full, Allocator2>& col_scale, 
			 double& row_condition_number, 
			 double& col_condition_number, double& amax, 
			 LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, col_scale, row_scale, string("GetScalingFactors(A, X, Y, ")
             + string(" rowcnd, colcnd, amax)"));
#endif
    
    int m = A.GetM(), n = A.GetN();
    int lda = A.GetLD();
    dgeequ_(&m, &n, A.GetData(), &lda, row_scale.GetData(), 
	    col_scale.GetData(), &row_condition_number, &col_condition_number,
	    &amax,  &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop0, class Allocator0,
	   class Allocator1, class Allocator2>
  void GetScalingFactors(const Matrix<complex<float>, Prop0, ColMajor, 
			 Allocator0>& A,
			 Vector<float, Vect_Full, Allocator1>& row_scale, 
			 Vector<float, Vect_Full, Allocator2>& col_scale, 
			 float& row_condition_number, 
			 float& col_condition_number, float& amax, 
			 LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, col_scale, row_scale, string("GetScalingFactors(A, X, Y, ")
	     +string("rowcnd, colcnd, amax)"));
#endif
    
    int m = A.GetM(), n = A.GetN();
    int lda = A.GetLD();
    cgeequ_(&m, &n, A.GetDataVoid(), &lda, row_scale.GetData(), 
	    col_scale.GetData(),  &row_condition_number, 
	    &col_condition_number, &amax,  &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop0, class Allocator0,
	   class Allocator1, class Allocator2>
  void GetScalingFactors(const Matrix<complex<double>, Prop0, ColMajor, 
			 Allocator0>& A,
			 Vector<double, Vect_Full, Allocator1>& row_scale, 
			 Vector<double, Vect_Full, Allocator2>& col_scale, 
			 double& row_condition_number, 
			 double& col_condition_number, double& amax, 
			 LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, col_scale, row_scale, string("GetScalingFactors(A, X, Y, ")
	     + string("rowcnd, colcnd, amax)"));
#endif
    
    int m = A.GetM(), n = A.GetN();
    int lda = A.GetLD();
    zgeequ_(&m, &n, A.GetDataVoid(), &lda, row_scale.GetData(), 
	    col_scale.GetData(),  &row_condition_number, 
	    &col_condition_number, &amax,  &lapack_info.GetInfoRef());
  }
  
  
  /*** RowMajor ***/
  
  
  template<class Prop0, class Allocator0,
	   class Allocator1, class Allocator2>
  void GetScalingFactors(const Matrix<float, Prop0, RowMajor, Allocator0>& A,
			 Vector<float, Vect_Full, Allocator1>& row_scale, 
			 Vector<float, Vect_Full, Allocator2>& col_scale, 
			 float& row_condition_number, 
			 float& col_condition_number, float& amax, 
			 LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, col_scale, row_scale, string("GetScalingFactors(A, X, Y, ")
             + string(" rowcnd, colcnd, amax)"));
#endif
    
    int m = A.GetM(), n = A.GetN();
    int lda = A.GetLD();
    sgeequ_(&n, &m, A.GetData(), &lda, col_scale.GetData(), 
	    row_scale.GetData(), &col_condition_number, &row_condition_number,
	    &amax,  &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop0, class Allocator0,
	   class Allocator1, class Allocator2>
  void GetScalingFactors(const Matrix<double, Prop0, RowMajor, Allocator0>& A,
			 Vector<double, Vect_Full, Allocator1>& row_scale, 
			 Vector<double, Vect_Full, Allocator2>& col_scale, 
			 double& row_condition_number, 
			 double& col_condition_number, double& amax, 
			 LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, col_scale, row_scale, string("GetScalingFactors(A, X, Y, ")
             + string(" rowcnd, colcnd, amax)"));
#endif
    
    int m = A.GetM(), n = A.GetN();
    int lda = A.GetLD();
    dgeequ_(&n, &m, A.GetData(), &lda, col_scale.GetData(), 
	    row_scale.GetData(), &col_condition_number, &row_condition_number,
	    &amax,  &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop0, class Allocator0,
	   class Allocator1, class Allocator2>
  void GetScalingFactors(const Matrix<complex<float>, Prop0, RowMajor, 
			 Allocator0>& A,
			 Vector<float, Vect_Full, Allocator1>& row_scale, 
			 Vector<float, Vect_Full, Allocator2>& col_scale, 
			 float& row_condition_number, 
			 float& col_condition_number, float& amax, 
			 LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, col_scale, row_scale, string("GetScalingFactors(A, X, Y,")
	     + string(" rowcnd, colcnd, amax)"));
#endif
    
    int m = A.GetM(), n = A.GetN();
    int lda = A.GetLD();
    cgeequ_(&n, &m, A.GetDataVoid(), &lda, col_scale.GetData(), 
	    row_scale.GetData(),  &col_condition_number, 
	    &row_condition_number, &amax,  &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop0, class Allocator0,
	   class Allocator1, class Allocator2>
  void GetScalingFactors(const Matrix<complex<double>, Prop0, RowMajor, 
			 Allocator0>& A,
			 Vector<double, Vect_Full, Allocator1>& row_scale, 
			 Vector<double, Vect_Full, Allocator2>& col_scale, 
			 double& row_condition_number, 
			 double& col_condition_number, double& amax, 
			 LapackInfo& info = lapack_info)
  {
    
#ifdef SELDON_CHECK_BOUNDARIES
    CheckDim(A, col_scale, row_scale, string("GetScalingFactors(A, X, Y, ")
	     + string("rowcnd, colcnd, amax)"));
#endif
    
    int m = A.GetM(), n = A.GetN();
    int lda = A.GetLD();
    zgeequ_(&n, &m, A.GetDataVoid(), &lda, col_scale.GetData(), 
	    row_scale.GetData(),  &col_condition_number, 
	    &row_condition_number, &amax,  &lapack_info.GetInfoRef());
  }
  
  
  // GetScalingFactors //
  ///////////////////////
  
  
  // Generic method, which factorizes a matrix and solve the linear system
  // b is overwritten by the solution
  template<class T, class Prop, class Storage, class Allocator,
	   class Allocator1, class Allocator2>
  void GetAndSolveLU(Matrix<T, Prop, Storage, Allocator>& A,
		     Vector<int, Vect_Full, Allocator1>& P, 
		     Vector<T, Vect_Full, Allocator2>& b,
		     LapackInfo& info = lapack_info)
  {
    GetLU(A, P, info);
    if (info.GetInfo() == 0)
      SolveLU(A, P, b, info);
    else
      cout << "An error occured during the factorization phase" << endl;
  }
  
  
} // namespace Seldon.

#define SELDON_FILE_LAPACK_LINEAREQUATIONS_CXX
#endif