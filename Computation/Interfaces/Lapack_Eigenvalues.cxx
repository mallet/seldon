// Copyright (C) 2001-2004 Vivien Mallet
// Author : Marc Durufle
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

#ifndef SELDON_FILE_LAPACK_EIGENVALUES_CXX

namespace Seldon
{
  
  
  template<class T, class Prop, class Storage, class Allocator>
  void TransposeSquareMatrix(Matrix<T, Prop, Storage, Allocator>& A)
  {
    T value;
    for (int i = 0; i < A.GetM(); i++)
      for (int j = i + 1; j < A.GetM(); j++)
	{
	  value = A(i,j);
	  A(i,j) = A(j,i);
	  A(j,i) = value;
	}
  }
  
  
  template<class T, class Prop, class Storage, class Allocator>
  void TransposeConjSquareMatrix(Matrix<T, Prop, Storage, Allocator>& A)
  {
    T value;
    for (int i = 0; i < A.GetM(); i++)
      {
	A(i,i) = conj(A(i,i));
	for (int j = i+1; j < A.GetM(); j++)
	  {
	    value = A(i,j);
	    A(i,j) = conj(A(j,i));
	    A(j,i) = conj(value);
	  }
      }
  }
  
  
  /////////////////////////////////
  // STANDARD EIGENVALUE PROBLEM //
  
  
  /* RowMajor */
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<float, Prop, RowMajor, Allocator1>& A,
		      Vector<float, Vect_Full, Allocator2>& wr,
		      Vector<float, Vect_Full, Allocator3>& wi,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM(), lwork = 6*n;
    char jobvl('N');
    char jobvr('N');
    Vector<float> work(lwork);
    sgeev_(&jobvl, &jobvr, &n, A.GetData(), &n, wr.GetData(), wi.GetData(),
	   A.GetData(), &n, A.GetData(), &n, work.GetData(),
	   &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<float, Prop, RowMajor, Allocator1>& A,
			      Vector<float, Vect_Full, Allocator2>& wr,
			      Vector<float, Vect_Full, Allocator3>& wi,
			      Matrix<float, General, RowMajor, Allocator4>& zr,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM(), lwork = 6*n;
    char jobvl('V');
    char jobvr('N');
    Vector<float> work(lwork);
    sgeev_(&jobvl, &jobvr, &n, A.GetData(), &n, wr.GetData(), wi.GetData(),
	   zr.GetData(), &n, zr.GetData(), &n, work.GetData(), &lwork,
	   &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(zr);
    // conjugate if necessary
    int i = 0;
    while (i < n)
      {
	if (i < (n-1))
	  if (wr(i) == wr(i+1))
	    {
	      for (int j = 0; j < n; j++)
		zr(j,i+1) = -zr(j,i+1);
	      
	      i++;
	    }
	
	i++;
      }
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<float>, Prop, RowMajor, Allocator1>& A,
		      Vector<complex<float>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobl('N'), jobr('N'); int lwork = 3*n;
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(2*n);
    cgeev_(&jobl, &jobr, &n, A.GetDataVoid(), &n, w.GetDataVoid(),
	   A.GetDataVoid(), &n, A.GetData(), &n, work.GetDataVoid(), &lwork,
	   rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop, RowMajor, Allocator1>& A,
			      Vector<complex<float>, Vect_Full, Allocator2>& w,
			      Matrix<complex<float>,
			      General, RowMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobl('V'), jobr('N'); int lwork = 3*n;
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(2*n);
    cgeev_(&jobl, &jobr, &n, A.GetDataVoid(), &n, w.GetDataVoid(),
	   z.GetDataVoid(), &n, z.GetData(), &n, work.GetDataVoid(), &lwork,
	   rwork.GetData(), &lapack_info.GetInfoRef());
    
    TransposeConjSquareMatrix(z);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<double, Prop, RowMajor, Allocator1>& A,
		      Vector<double, Vect_Full, Allocator2>& wr,
		      Vector<double, Vect_Full, Allocator3>& wi,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM(), lwork = 6*n;
    char jobvl('N'), jobvr('N'); Vector<double> work(lwork);
    dgeev_(&jobvl, &jobvr, &n, A.GetData(), &n, wr.GetData(), wi.GetData(),
	   A.GetData(), &n, A.GetData(), &n, work.GetData(),
	   &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<double, Prop, RowMajor, Allocator1>& A,
			      Vector<double, Vect_Full, Allocator2>& wr,
			      Vector<double, Vect_Full, Allocator3>& wi,
			      Matrix<double, General, RowMajor, Allocator4>& zr,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM(), lwork = 6*n;
    char jobvl('V'), jobvr('N'); Vector<double> work(lwork);
    dgeev_(&jobvl, &jobvr, &n, A.GetData(), &n, wr.GetData(), wi.GetData(),
	   zr.GetData(), &n, zr.GetData(), &n, work.GetData(), &lwork,
	   &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(zr);
    // conjugate if necessary
    int i = 0;
    while (i < n)
      {
	if (i < (n-1))
	  if (wr(i) == wr(i+1))
	    {
	      for (int j = 0; j < n; j++)
		zr(j,i+1) = -zr(j,i+1);
	      
	      i++;
	    }
	
	i++;
      }
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<double>, Prop, RowMajor, Allocator1>& A,
		      Vector<complex<double>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobl('N'), jobr('N'); int lwork = 3*n;
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(2*n);
    zgeev_(&jobl, &jobr, &n, A.GetDataVoid(), &n, w.GetDataVoid(),
	   A.GetDataVoid(), &n, A.GetData(), &n, work.GetDataVoid(), &lwork,
	   rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop, RowMajor, Allocator1>& A,
			      Vector<complex<double>,
			      Vect_Full, Allocator2>& w,
			      Matrix<complex<double>,
			      General, RowMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobl('V'), jobr('N'); int lwork = 3*n;
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(2*n);
    zgeev_(&jobl, &jobr, &n, A.GetDataVoid(), &n, w.GetDataVoid(),
	   z.GetDataVoid(), &n, z.GetData(), &n, work.GetDataVoid(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
    
    TransposeConjSquareMatrix(z);
  }
  
  
  /* ColMajor */
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<float, Prop, ColMajor, Allocator1>& A,
		      Vector<float, Vect_Full, Allocator2>& wr,
		      Vector<float, Vect_Full, Allocator3>& wi,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM(), lwork = 6*n;
    char jobvl('N'), jobvr('N'); Vector<float> work(lwork);
    sgeev_(&jobvl, &jobvr, &n, A.GetData(), &n, wr.GetData(), wi.GetData(),
	   A.GetData(), &n, A.GetData(), &n, work.GetData(), &lwork,
	   &lapack_info.GetInfoRef());
  }
  
  template<class Prop, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<float, Prop, ColMajor, Allocator1>& A,
			      Vector<float, Vect_Full, Allocator2>& wr,
			      Vector<float, Vect_Full, Allocator3>& wi,
			      Matrix<float, General, ColMajor, Allocator4>&zr,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM(), lwork = 6*n;
    char jobvl('N'), jobvr('V');
    Vector<float> work(lwork);
    sgeev_(&jobvl, &jobvr, &n, A.GetData(), &n, wr.GetData(), wi.GetData(),
	   zr.GetData(), &n, zr.GetData(), &n, work.GetData(),
	   &lwork, &lapack_info.GetInfoRef());
    
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<float>, Prop, ColMajor, Allocator1>& A,
		      Vector<complex<float>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobl('N'), jobr('N'); int lwork = 3*n;
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(2*n);
    cgeev_(&jobl, &jobr, &n, A.GetDataVoid(), &n, w.GetDataVoid(),
	   A.GetDataVoid(), &n, A.GetData(), &n, work.GetDataVoid(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop, ColMajor, Allocator1>& A,
			      Vector<complex<float>,
			      Vect_Full, Allocator2>& w,
			      Matrix<complex<float>,
			      General, ColMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobl('N'), jobr('V'); int lwork = 3*n;
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(2*n);
    cgeev_(&jobl, &jobr, &n, A.GetDataVoid(), &n, w.GetDataVoid(),
	   z.GetDataVoid(), &n, z.GetData(), &n, work.GetDataVoid(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<double, Prop, ColMajor, Allocator1>& A,
		      Vector<double, Vect_Full, Allocator2>& wr,
		      Vector<double, Vect_Full, Allocator3>& wi,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM(), lwork = 6*n;
    char jobvl('N'), jobvr('N'); Vector<double> work(lwork);
    dgeev_(&jobvl, &jobvr, &n, A.GetData(), &n, wr.GetData(), wi.GetData(),
	   A.GetData(), &n, A.GetData(), &n, work.GetData(), &lwork,
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<double, Prop, ColMajor, Allocator1>& A,
			      Vector<double, Vect_Full, Allocator2>& wr,
			      Vector<double, Vect_Full, Allocator3>& wi,
			      Matrix<double, General, ColMajor, Allocator4>&zr,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM(), lwork = 6*n;
    char jobvl('N'), jobvr('V');
    Vector<double> work(lwork);
    dgeev_(&jobvl, &jobvr, &n, A.GetData(), &n, wr.GetData(), wi.GetData(),
	   zr.GetData(), &n, zr.GetData(), &n, work.GetData(),
	   &lwork, &lapack_info.GetInfoRef());
    
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<double>, Prop, ColMajor, Allocator1>& A,
		      Vector<complex<double>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobl('N'), jobr('N'); int lwork = 3*n;
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(2*n);
    zgeev_(&jobl, &jobr, &n, A.GetDataVoid(), &n, w.GetDataVoid(),
	   A.GetDataVoid(), &n, A.GetData(), &n, work.GetDataVoid(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop, ColMajor, Allocator1>& A,
			      Vector<complex<double>,
			      Vect_Full, Allocator2>& w,
			      Matrix<complex<double>,
			      General, ColMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobl('N'), jobr('V'); int lwork = 3*n;
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(2*n);
    zgeev_(&jobl, &jobr, &n, A.GetDataVoid(), &n, w.GetDataVoid(),
	   z.GetDataVoid(), &n, z.GetData(), &n, work.GetDataVoid(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /* RowSym */
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<float, Prop, RowSym, Allocator1>& A,
		      Vector<float, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 3*n; Vector<float> work(lwork);
    ssyev_(&job, &uplo, &n, A.GetData(), &n, w.GetData(), work.GetData(),
	   &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<float, Prop, RowSym, Allocator1>& A,
			      Vector<float, Vect_Full, Allocator2>& w,
			      Matrix<float, General, RowMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('V');
    int lwork = 3*n; Vector<float> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
 
    ssyev_(&job, &uplo, &n, z.GetData(), &n, w.GetData(), work.GetData(),
	   &lwork, &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(z);
  }
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<float>, Prop, RowSym, Allocator1>& A,
		      Vector<complex<float>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvalues(B, w);
  }
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop, RowSym, Allocator1>& A,
			      Vector<complex<float>,
			      Vect_Full, Allocator2>& w,
			      Matrix<complex<float>,
			      General, RowMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, RowMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvaluesEigenvec(B, w, z);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<double, Prop, RowSym, Allocator1>& A,
		      Vector<double, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 3*n; Vector<double> work(lwork);
    dsyev_(&job, &uplo, &n, A.GetData(), &n, w.GetData(), work.GetData(),
	   &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<double, Prop, RowSym, Allocator1>& A,
			      Vector<double, Vect_Full, Allocator2>& w,
			      Matrix<double, General, RowMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('V');
    int lwork = 3*n; Vector<double> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
 
    dsyev_(&job, &uplo, &n, z.GetData(), &n, w.GetData(), work.GetData(),
	   &lwork, &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(z);
  }
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<double>, Prop, RowSym, Allocator1>& A,
		      Vector<complex<double>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvalues(B, w);
  }
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop, RowSym, Allocator1>& A,
			      Vector<complex<double>,
			      Vect_Full, Allocator2>& w,
			      Matrix<complex<double>,
			      General, RowMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, RowMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvaluesEigenvec(B, w, z);
  }
  
  
  /* ColSym */
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<float, Prop, ColSym, Allocator1>& A,
		      Vector<float, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('N'); int lwork = 3*n; Vector<float> work(lwork);
    ssyev_(&job, &uplo, &n, A.GetData(), &n, w.GetData(), work.GetData(),
	   &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<float, Prop, ColSym, Allocator1>& A,
			      Vector<float, Vect_Full, Allocator2>& w,
			      Matrix<float, General, ColMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('V');
    int lwork = 3*n; Vector<float> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    ssyev_(&job, &uplo, &n, z.GetData(), &n, w.GetData(),
	   work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<float>, Prop, ColSym, Allocator1>& A,
		      Vector<complex<float>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvalues(B, w);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop, ColSym, Allocator1>& A,
			      Vector<complex<float>,
			      Vect_Full, Allocator2>& w,
			      Matrix<complex<float>,
			      General, ColMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvaluesEigenvec(B, w, z);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<double, Prop, ColSym, Allocator1>& A,
		      Vector<double, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('N'); int lwork = 3*n; Vector<double> work(lwork);
    dsyev_(&job, &uplo, &n, A.GetData(), &n, w.GetData(), work.GetData(),
	   &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<double, Prop, ColSym, Allocator1>& A,
			      Vector<double, Vect_Full, Allocator2>& w,
			      Matrix<double, General, ColMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('V');
    int lwork = 3*n; Vector<double> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    dsyev_(&job, &uplo, &n, z.GetData(), &n, w.GetData(),
	   work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<double>, Prop, ColSym, Allocator1>& A,
		      Vector<complex<double>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvalues(B, w);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop, ColSym, Allocator1>& A,
			      Vector<complex<double>,
			      Vect_Full, Allocator2>& w,
			      Matrix<complex<double>,
			      General, ColMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvaluesEigenvec(B, w, z);
  }
  
  
  /* RowHerm */
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<float>, Prop, RowHerm, Allocator1>& A,
		      Vector<float, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 2*n; Vector<complex<float> > work(lwork);
    Vector<float> rwork(3*n);
    cheev_(&job, &uplo, &n, A.GetDataVoid(), &n, w.GetData(),
	   work.GetDataVoid(), &lwork, rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop, RowHerm, Allocator1>& A,
			      Vector<float, Vect_Full, Allocator2>& w,
			      Matrix<complex<float>,
			      General, RowMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('V');
    int lwork = 2*n; Vector<complex<float> > work(lwork);
    Vector<float> rwork(3*n);
    z.Reallocate(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    cheev_(&job, &uplo,&n, z.GetDataVoid(),&n, w.GetData(), work.GetDataVoid(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(z);
  }
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<double>, Prop, RowHerm, Allocator1>& A,
		      Vector<double, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 2*n; Vector<complex<double> > work(lwork);
    Vector<double> rwork(3*n);
    zheev_(&job, &uplo, &n, A.GetDataVoid(), &n, w.GetData(),
	   work.GetDataVoid(), &lwork, rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop, RowHerm, Allocator1>& A,
			      Vector<double, Vect_Full, Allocator2>& w,
			      Matrix<complex<double>,
			      General, RowMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('V');
    int lwork = 2*n; Vector<complex<double> > work(lwork);
    Vector<double> rwork(3*n);
    z.Reallocate(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    zheev_(&job, &uplo,&n, z.GetDataVoid(),&n, w.GetData(), work.GetDataVoid(),
	   &lwork, rwork.GetData() , &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(z);
  }
  
  
  /* ColHerm */
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<float>, Prop, ColHerm, Allocator1>& A,
		      Vector<float, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('N'); int lwork = 2*n;
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(3*n);
    cheev_(&job, &uplo, &n, A.GetDataVoid(), &n, w.GetData(),
	   work.GetDataVoid(), &lwork, rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop, ColHerm, Allocator1>& A,
			      Vector<float, Vect_Full, Allocator2>& w,
			      Matrix<complex<float>,
			      General, ColMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('V'); int lwork = 2*n;
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(3*n);
    z.Reallocate(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    cheev_(&job, &uplo, &n, z.GetDataVoid(), &n,
	   w.GetData(), work.GetDataVoid(),
	   &lwork, rwork.GetData() , &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<double>, Prop, ColHerm, Allocator1>& A,
		      Vector<double, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('N'); int lwork = 2*n;
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(3*n);
    zheev_(&job, &uplo, &n, A.GetDataVoid(), &n, w.GetData(),
	   work.GetDataVoid(), &lwork, rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop, ColHerm, Allocator1>& A,
			      Vector<double, Vect_Full, Allocator2>& w,
			      Matrix<complex<double>,
			      General, ColMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('V'); int lwork = 2*n;
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(3*n);
    z.Reallocate(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    zheev_(&job, &uplo, &n, z.GetDataVoid(), &n,
	   w.GetData(), work.GetDataVoid(),
	   &lwork, rwork.GetData() , &lapack_info.GetInfoRef());
  }
  
  
  /* RowSymPacked */
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<float, Prop, RowSymPacked, Allocator1>& A,
		      Vector<float, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('N');
    Vector<float> work(3*n);
    sspev_(&job, &uplo, &n, A.GetData(), w.GetData(), A.GetData(), &n,
	   work.GetData() , &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<float, Prop,RowSymPacked, Allocator1>& A,
			      Vector<float, Vect_Full, Allocator2>& w,
			      Matrix<float, General, RowMajor, Allocator3>&z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('V');
    Vector<float> work(3*n);
    sspev_(&job, &uplo, &n, A.GetData(), w.GetData(), z.GetData(), &n,
	   work.GetData() , &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(z);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<float>, Prop, RowSymPacked, Allocator1>& A,
		      Vector<complex<float>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvalues(B, w);
  }
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<float>, Prop,
			      RowSymPacked, Allocator1>& A,
			      Vector<complex<float>,Vect_Full, Allocator2>& w,
			      Matrix<complex<float>,
			      General, RowMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, RowMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvaluesEigenvec(B, w, z);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<double, Prop, RowSymPacked, Allocator1>& A,
		      Vector<double, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('N'); Vector<double> work(3*n);
    dspev_(&job, &uplo, &n, A.GetData(), w.GetData(), A.GetData(), &n,
	   work.GetData() , &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<double,Prop,RowSymPacked, Allocator1>& A,
			      Vector<double, Vect_Full, Allocator2>& w,
			      Matrix<double, General, RowMajor, Allocator3>&z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('V'); Vector<double> work(3*n);
    dspev_(&job, &uplo, &n, A.GetData(), w.GetData(), z.GetData(), &n,
	   work.GetData() , &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(z);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<double>, Prop, RowSymPacked, Allocator1>& A,
		      Vector<complex<double>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvalues(B, w);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<double>, Prop,
			      RowSymPacked, Allocator1>& A,
			      Vector<complex<double>,Vect_Full, Allocator2>& w,
			      Matrix<complex<double>,
			      General, RowMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, RowMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvaluesEigenvec(B, w, z);
  }
  
  
  /* ColSymPacked */
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<float, Prop, ColSymPacked, Allocator1>& A,
		      Vector<float, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('N');
    Vector<float> work(3*n);
    sspev_(&job, &uplo, &n, A.GetData(), w.GetData(), A.GetData(),
	   &n, work.GetData() , &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<float, Prop,ColSymPacked, Allocator1>& A,
			      Vector<float, Vect_Full, Allocator2>& w,
			      Matrix<float, General, ColMajor, Allocator3>&z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('V');
    Vector<float> work(3*n);
    sspev_(&job, &uplo, &n, A.GetData(), w.GetData(), z.GetData(),
	   &n, work.GetData() , &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<float>,
		      Prop, ColSymPacked, Allocator1>& A,
		      Vector<complex<float>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvalues(B, w);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop, ColSymPacked, Allocator1>& A,
			      Vector<complex<float>, Vect_Full, Allocator2>& w,
			      Matrix<complex<float>,
			      General, ColMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvaluesEigenvec(B, w, z);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<double, Prop, ColSymPacked, Allocator1>& A,
		      Vector<double, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('N'); Vector<double> work(3*n);
    dspev_(&job, &uplo, &n, A.GetData(), w.GetData(), A.GetData(),
	   &n, work.GetData() , &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<double,Prop,ColSymPacked, Allocator1>& A,
			      Vector<double, Vect_Full, Allocator2>& w,
			      Matrix<double, General, ColMajor, Allocator3>&z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('V');
    Vector<double> work(3*n);
    dspev_(&job, &uplo, &n, A.GetData(), w.GetData(), z.GetData(),
	   &n, work.GetData() , &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<double>,
		      Prop, ColSymPacked, Allocator1>& A,
		      Vector<complex<double>, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvalues(B, w);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop, ColSymPacked, Allocator1>& A,
			      Vector<complex<double>, Vect_Full, Allocator2>& w,
			      Matrix<complex<double>,
			      General, ColMajor, Allocator3>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, ColMajor> B(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	B(i,j) = A(i,j);
    
    GetEigenvaluesEigenvec(B, w, z);
  }
  
  
  /* RowHermPacked */
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<float>,
		      Prop, RowHermPacked, Allocator1>& A,
		      Vector<float, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('N');
    Vector<complex<float> > work(2*n);
    Vector<float> rwork(3*n);
    chpev_(&job, &uplo, &n, A.GetDataVoid(), w.GetData(), A.GetDataVoid(), &n,
	   work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop, RowHermPacked, Allocator1>& A,
			      Vector<float, Vect_Full, Allocator2>& w,
			      Matrix<complex<float>,
			      General, RowMajor, Allocator3>&z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('V');
    Vector<complex<float> > work(2*n);
    Vector<float> rwork(3*n);
    chpev_(&job, &uplo, &n, A.GetDataVoid(), w.GetData(), z.GetDataVoid(),
	   &n, work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(z);
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<double>,
		      Prop, RowHermPacked, Allocator1>& A,
		      Vector<double, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('N');
    Vector<complex<double> > work(2*n);
    Vector<double> rwork(3*n);
    zhpev_(&job, &uplo, &n, A.GetDataVoid(), w.GetData(), A.GetDataVoid(), &n,
	   work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop, RowHermPacked, Allocator1>& A,
			      Vector<double, Vect_Full, Allocator2>& w,
			      Matrix<complex<double>,
			      General, RowMajor, Allocator3>&z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('L'); char job('V');
    Vector<complex<double> > work(2*n);
    Vector<double> rwork(3*n);
    zhpev_(&job, &uplo, &n, A.GetDataVoid(), w.GetData(), z.GetDataVoid(),
	   &n, work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(z);
  }
  
  
  /* ColHermPacked */
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<float>,
		      Prop, ColHermPacked, Allocator1>& A,
		      Vector<float, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U');
    char job('N');
    Vector<complex<float> > work(2*n);
    Vector<float> rwork(3*n);
    chpev_(&job, &uplo, &n, A.GetDataVoid(), w.GetData(), A.GetDataVoid(), &n,
	   work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop, ColHermPacked, Allocator1>& A,
			      Vector<float, Vect_Full, Allocator2>& w,
			      Matrix<complex<float>,
			      General, ColMajor, Allocator3>&z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('V');
    Vector<complex<float> > work(2*n);
    Vector<float> rwork(3*n);
    chpev_(&job, &uplo, &n, A.GetDataVoid(), w.GetData(), z.GetDataVoid(), &n,
	   work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2>
  void GetEigenvalues(Matrix<complex<double>,
		      Prop, ColHermPacked, Allocator1>& A,
		      Vector<double, Vect_Full, Allocator2>& w,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U');
    char job('N');
    Vector<complex<double> > work(2*n);
    Vector<double> rwork(3*n);
    zhpev_(&job, &uplo, &n, A.GetDataVoid(), w.GetData(), A.GetDataVoid(), &n,
	   work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop, class Allocator1, class Allocator2, class Allocator3>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop, ColHermPacked, Allocator1>& A,
			      Vector<double, Vect_Full, Allocator2>& w,
			      Matrix<complex<double>,
			      General, ColMajor, Allocator3>&z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char uplo('U'); char job('V');
    Vector<complex<double> > work(2*n);
    Vector<double> rwork(3*n);
    zhpev_(&job, &uplo, &n, A.GetDataVoid(), w.GetData(), z.GetDataVoid(), &n,
	   work.GetDataVoid(), rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  // STANDARD EIGENVALUE PROBLEM //
  /////////////////////////////////
  
  
  ////////////////////////////////////
  // GENERALIZED EIGENVALUE PROBLEM //
  
  
  /* RowSym */
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<float, Prop1, RowSym, Allocator1>& A,
		      Matrix<float, Prop2, RowSym, Allocator2>& B,
		      Vector<float, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 3*n; Vector<float> work(lwork);
    
    ssygv_(&itype, &job, &uplo, &n, A.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<float, Prop1, RowSym, Allocator1>& A,
			      Matrix<float, Prop2, RowSym, Allocator2>& B,
			      Vector<float, Vect_Full, Allocator3>& w,
			      Matrix<float, General, RowMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('V');
    int lwork = 3*n; Vector<float> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    ssygv_(&itype, &job, &uplo, &n, z.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<complex<float>, Prop1, RowSym, Allocator1>& A,
		      Matrix<complex<float>, Prop2, RowSym, Allocator2>& B,
		      Vector<complex<float>, Vect_Full, Allocator4>& alpha,
		      Vector<complex<float>, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N');
    int lwork = 2*n; Vector<complex<float> > work(lwork);
    Vector<float> rwork(8*n);
    
    cggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha.GetData(), beta.GetData(), A.GetData(), &n, A.GetData(), &n,
	   work.GetData(), &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Allocator1,
	   class Allocator2, class Allocator4,
	   class Allocator5, class Allocator6>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop1, RowSym, Allocator1>& A,
			      Matrix<complex<float>,
			      Prop2, RowSym, Allocator2>& B,
			      Vector<complex<float>,
			      Vect_Full, Allocator4>& alpha,
			      Vector<complex<float>,
			      Vect_Full, Allocator5>& beta,
			      Matrix<complex<float>,
			      Prop3, RowMajor, Allocator6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('V'), jobvr('N');
    int lwork = 2*n; Vector<complex<float> > work(lwork);
    Vector<float> rwork(8*n);
    
    cggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha.GetData(), beta.GetData(), V.GetData(), &n, V.GetData(), &n,
	   work.GetData(), &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
    
    TransposeConjSquareMatrix(V);
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<double, Prop1, RowSym, Allocator1>& A,
		      Matrix<double, Prop2, RowSym, Allocator2>& B,
		      Vector<double, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 3*n; Vector<double> work(lwork);
    
    dsygv_(&itype, &job, &uplo, &n, A.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<double, Prop1, RowSym, Allocator1>& A,
			      Matrix<double, Prop2, RowSym, Allocator2>& B,
			      Vector<double, Vect_Full, Allocator3>& w,
			      Matrix<double, General, RowMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('V');
    int lwork = 3*n; Vector<double> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    dsygv_(&itype, &job, &uplo, &n, z.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<complex<double>, Prop1, RowSym, Allocator1>& A,
		      Matrix<complex<double>, Prop2, RowSym, Allocator2>& B,
		      Vector<complex<double>, Vect_Full, Allocator4>& alpha,
		      Vector<complex<double>, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N');
    int lwork = 2*n; Vector<complex<double> > work(lwork);
    Vector<double> rwork(8*n);
    
    zggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha.GetData(), beta.GetData(), A.GetData(), &n, A.GetData(), &n,
	   work.GetData(), &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Allocator1,
	   class Allocator2, class Allocator4,
	   class Allocator5, class Allocator6>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop1, RowSym, Allocator1>& A,
			      Matrix<complex<double>,
			      Prop2, RowSym, Allocator2>& B,
			      Vector<complex<double>,
			      Vect_Full, Allocator4>& alpha,
			      Vector<complex<double>,
			      Vect_Full, Allocator5>& beta,
			      Matrix<complex<double>,
			      Prop3, RowMajor, Allocator6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('V'), jobvr('N');
    int lwork = 2*n; Vector<complex<double> > work(lwork);
    Vector<double> rwork(8*n);
    
    zggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha.GetData(), beta.GetData(), V.GetData(), &n, V.GetData(), &n,
	   work.GetData(), &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
    
    TransposeConjSquareMatrix(V);
  }
  
  
  /* ColSym */
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<float, Prop1, ColSym, Allocator1>& A,
		      Matrix<float, Prop2, ColSym, Allocator2>& B,
		      Vector<float, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('N');
    int lwork = 3*n; Vector<float> work(lwork);
    
    ssygv_(&itype, &job, &uplo, &n, A.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<float, Prop1, ColSym, Allocator1>& A,
			      Matrix<float, Prop2, ColSym, Allocator2>& B,
			      Vector<float, Vect_Full, Allocator3>& w,
			      Matrix<float, General, ColMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('V');
    int lwork = 3*n; Vector<float> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    ssygv_(&itype, &job, &uplo, &n, z.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<complex<float>, Prop1, ColSym, Allocator1>& A,
		      Matrix<complex<float>, Prop2, ColSym, Allocator2>& B,
		      Vector<complex<float>, Vect_Full, Allocator4>& alpha,
		      Vector<complex<float>, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N'); int lwork = 2*n;
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(8*n);
    
    cggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha.GetData(), beta.GetData(), A.GetData(), &n, A.GetData(), &n,
	   work.GetData(), &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Alloc1,
	   class Alloc2, class Alloc4, class Alloc5, class Alloc6>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop1, ColSym, Alloc1>& A,
			      Matrix<complex<float>,
			      Prop2, ColSym, Alloc2>& B,
			      Vector<complex<float>, Vect_Full, Alloc4>& alpha,
			      Vector<complex<float>, Vect_Full, Alloc5>& beta,
			      Matrix<complex<float>,
			      Prop3, ColMajor, Alloc6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('V');
    int lwork = 2*n; Vector<complex<float> > work(lwork);
    Vector<float> rwork(8*n);
    
    cggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha.GetData(), beta.GetData(), V.GetData(), &n, V.GetData(), &n,
	   work.GetData(), &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<double, Prop1, ColSym, Allocator1>& A,
		      Matrix<double, Prop2, ColSym, Allocator2>& B,
		      Vector<double, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('N');
    int lwork = 3*n; Vector<double> work(lwork);
    
    dsygv_(&itype, &job, &uplo, &n, A.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<double, Prop1, ColSym, Allocator1>& A,
			      Matrix<double, Prop2, ColSym, Allocator2>& B,
			      Vector<double, Vect_Full, Allocator3>& w,
			      Matrix<double, General, ColMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('V');
    int lwork = 3*n; Vector<double> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    dsygv_(&itype, &job, &uplo, &n, z.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<complex<double>, Prop1, ColSym, Allocator1>& A,
		      Matrix<complex<double>, Prop2, ColSym, Allocator2>& B,
		      Vector<complex<double>, Vect_Full, Allocator4>& alpha,
		      Vector<complex<double>, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N'); int lwork = 2*n;
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(8*n);
    
    zggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha.GetData(), beta.GetData(), A.GetData(), &n, A.GetData(), &n,
	   work.GetData(), &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Alloc1,
	   class Alloc2, class Alloc4, class Alloc5, class Alloc6>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop1, ColSym, Alloc1>& A,
			      Matrix<complex<double>,
			      Prop2, ColSym, Alloc2>& B,
			      Vector<complex<double>, Vect_Full, Alloc4>& alpha,
			      Vector<complex<double>, Vect_Full, Alloc5>& beta,
			      Matrix<complex<double>,
			      Prop3, ColMajor, Alloc6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('V');
    int lwork = 2*n; Vector<complex<double> > work(lwork);
    Vector<double> rwork(8*n);
    
    zggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha.GetData(), beta.GetData(), V.GetData(), &n, V.GetData(), &n,
	   work.GetData(), &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /* RowHerm */
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<complex<float>, Prop1, RowHerm, Allocator1>& A,
		      Matrix<complex<float>, Prop2, RowHerm, Allocator2>& B,
		      Vector<float, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 2*n; Vector<float> work(lwork);
    Vector<float> rwork(3*n);
    chegv_(&itype, &job, &uplo, &n, A.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop1, RowHerm, Allocator1>& A,
			      Matrix<complex<float>,
			      Prop2, RowHerm, Allocator2>& B,
			      Vector<float, Vect_Full, Allocator3>& w,
			      Matrix<complex<float>,
			      General, RowMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('V');
    int lwork = 2*n; Vector<float> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    Vector<float> rwork(3*n);
    chegv_(&itype, &job, &uplo, &n, z.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<complex<double>, Prop1, RowHerm, Allocator1>& A,
		      Matrix<complex<double>, Prop2, RowHerm, Allocator2>& B,
		      Vector<double, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 3*n; Vector<double> work(lwork);
    Vector<double> rwork(3*n);
    zhegv_(&itype, &job, &uplo, &n, A.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop1, RowHerm, Allocator1>& A,
			      Matrix<complex<double>,
			      Prop2, RowHerm, Allocator2>& B,
			      Vector<double, Vect_Full, Allocator3>& w,
			      Matrix<complex<double>,
			      General, RowMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('V');
    int lwork = 3*n; Vector<double> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    Vector<double> rwork(3*n);
    zhegv_(&itype, &job, &uplo, &n, z.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  /* ColHerm */
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<complex<float>, Prop1, ColHerm, Allocator1>& A,
		      Matrix<complex<float>, Prop2, ColHerm, Allocator2>& B,
		      Vector<float, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('N');
    int lwork = 2*n; Vector<float> work(lwork);
    Vector<float> rwork(3*n);
    chegv_(&itype, &job, &uplo, &n, A.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop1, ColHerm, Allocator1>& A,
			      Matrix<complex<float>,
			      Prop2, ColHerm, Allocator2>& B,
			      Vector<float, Vect_Full, Allocator3>& w,
			      Matrix<complex<float>,
			      General, ColMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('V');
    int lwork = 3*n; Vector<float> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    Vector<float> rwork(3*n);
    chegv_(&itype, &job, &uplo, &n, z.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork,
	   rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<complex<double>, Prop1, ColHerm, Allocator1>& A,
		      Matrix<complex<double>, Prop2, ColHerm, Allocator2>& B,
		      Vector<double, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('N');
    int lwork = 3*n; Vector<double> work(lwork);
    Vector<double> rwork(3*n);
    zhegv_(&itype, &job, &uplo, &n, A.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork, rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop1, ColHerm, Allocator1>& A,
			      Matrix<complex<double>,
			      Prop2, ColHerm, Allocator2>& B,
			      Vector<double, Vect_Full, Allocator3>& w,
			      Matrix<complex<double>,
			      General, ColMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('V');
    int lwork = 3*n; Vector<double> work(lwork);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	z(i,j) = A(i,j);
    
    Vector<double> rwork(3*n);
    zhegv_(&itype, &job, &uplo, &n, z.GetData(), &n, B.GetData(), &n,
	   w.GetData(), work.GetData(), &lwork,
	   rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /* RowSymPacked */
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<float, Prop1, RowSymPacked, Allocator1>& A,
		      Matrix<float, Prop2, RowSymPacked, Allocator2>& B,
		      Vector<float, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 3*n; Vector<float> work(lwork);
    
    sspgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   A.GetData(), &n, work.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<float,
			      Prop1, RowSymPacked, Allocator1>& A,
			      Matrix<float,
			      Prop2, RowSymPacked, Allocator2>& B,
			      Vector<float, Vect_Full, Allocator3>& w,
			      Matrix<float,
			      General, RowMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('V');
    int lwork = 3*n; Vector<float> work(lwork);
    sspgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   z.GetData(), &n, work.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvalues(Matrix<complex<float>,
		      Prop1, RowSymPacked, Allocator1>& A,
		      Matrix<complex<float>,
		      Prop2, RowSymPacked, Allocator2>& B,
		      Vector<complex<float>, Vect_Full, Allocator3>& alpha,
		      Vector<complex<float>, Vect_Full, Allocator4>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, ColMajor> C(n,n), D(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	{
	  C(i,j) = A(i,j);
	  D(i,j) = B(i,j);
	}
    
    GetEigenvalues(C, D, alpha, beta);
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4, class Allocator5>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop1, RowSymPacked, Allocator1>& A,
			      Matrix<complex<float>,
			      Prop2, RowSymPacked, Allocator2>& B,
			      Vector<complex<float>,
			      Vect_Full, Allocator3>& alpha,
			      Vector<complex<float>,
			      Vect_Full, Allocator4>& beta,
			      Matrix<complex<float>,
			      General, RowMajor, Allocator5>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, RowMajor> C(n,n), D(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	{
	  C(i,j) = A(i,j);
	  D(i,j) = B(i,j);
	}
    
    GetEigenvaluesEigenvec(C, D, alpha, beta, z);
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<double, Prop1, RowSymPacked, Allocator1>& A,
		      Matrix<double, Prop2, RowSymPacked, Allocator2>& B,
		      Vector<double, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 3*n; Vector<double> work(lwork);
    
    dspgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   A.GetData(), &n, work.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<double,
			      Prop1, RowSymPacked, Allocator1>& A,
			      Matrix<double,
			      Prop2, RowSymPacked, Allocator2>& B,
			      Vector<double, Vect_Full, Allocator3>& w,
			      Matrix<double,
			      General, RowMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('V');
    int lwork = 3*n; Vector<double> work(lwork);
    dspgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   z.GetData(), &n, work.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvalues(Matrix<complex<double>,
		      Prop1, RowSymPacked, Allocator1>& A,
		      Matrix<complex<double>,
		      Prop2, RowSymPacked, Allocator2>& B,
		      Vector<complex<double>, Vect_Full, Allocator3>& alpha,
		      Vector<complex<double>, Vect_Full, Allocator4>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, ColMajor> C(n,n), D(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	{
	  C(i,j) = A(i,j);
	  D(i,j) = B(i,j);
	}
    
    GetEigenvalues(C, D, alpha, beta);
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4, class Allocator5>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop1, RowSymPacked, Allocator1>& A,
			      Matrix<complex<double>,
			      Prop2, RowSymPacked, Allocator2>& B,
			      Vector<complex<double>,
			      Vect_Full, Allocator3>& alpha,
			      Vector<complex<double>,
			      Vect_Full, Allocator4>& beta,
			      Matrix<complex<double>,
			      General, RowMajor, Allocator5>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, RowMajor> C(n,n), D(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	{
	  C(i,j) = A(i,j);
	  D(i,j) = B(i,j);
	}
    
    GetEigenvaluesEigenvec(C, D, alpha, beta, z);
  }
  
  
  /* ColSymPacked */
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<float, Prop1, ColSymPacked, Allocator1>& A,
		      Matrix<float, Prop2, ColSymPacked, Allocator2>& B,
		      Vector<float, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('N');
    int lwork = 3*n; Vector<float> work(lwork);
    
    sspgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   A.GetData(), &n, work.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<float,
			      Prop1, ColSymPacked, Allocator1>& A,
			      Matrix<float,
			      Prop2, ColSymPacked, Allocator2>& B,
			      Vector<float, Vect_Full, Allocator3>& w,
			      Matrix<float,
			      General, ColMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('V'); int lwork = 3*n;
    Vector<float> work(lwork);
    
    sspgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   z.GetData(), &n, work.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvalues(Matrix<complex<float>,
		      Prop1, ColSymPacked, Allocator1>& A,
		      Matrix<complex<float>,
		      Prop2, ColSymPacked, Allocator2>& B,
		      Vector<complex<float>, Vect_Full, Allocator3>& alpha,
		      Vector<complex<float>, Vect_Full, Allocator4>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, ColMajor> C(n,n), D(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	{
	  C(i,j) = A(i,j);
	  D(i,j) = B(i,j);
	}
    
    GetEigenvalues(C, D, alpha, beta);
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4, class Allocator5>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop1, ColSymPacked, Allocator1>& A,
			      Matrix<complex<float>,
			      Prop2, ColSymPacked, Allocator2>& B,
			      Vector<complex<float>, 
			      Vect_Full, Allocator3>& alpha,
			      Vector<complex<float>,
			      Vect_Full, Allocator4>& beta,
			      Matrix<complex<float>,
			      General, ColMajor, Allocator5>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<float>, General, ColMajor> C(n,n), D(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	{
	  C(i,j) = A(i,j);
	  D(i,j) = B(i,j);
	}
    
    GetEigenvaluesEigenvec(C, D, alpha, beta, z);
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<double, Prop1, ColSymPacked, Allocator1>& A,
		      Matrix<double, Prop2, ColSymPacked, Allocator2>& B,
		      Vector<double, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('N');
    int lwork = 3*n; Vector<double> work(lwork);
    
    dspgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   A.GetData(), &n, work.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<double,
			      Prop1, ColSymPacked, Allocator1>& A,
			      Matrix<double,
			      Prop2, ColSymPacked, Allocator2>& B,
			      Vector<double, Vect_Full, Allocator3>& w,
			      Matrix<double,
			      General, ColMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('V'); int lwork = 3*n;
    Vector<double> work(lwork);
    
    dspgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   z.GetData(), &n, work.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvalues(Matrix<complex<double>,
		      Prop1, ColSymPacked, Allocator1>& A,
		      Matrix<complex<double>,
		      Prop2, ColSymPacked, Allocator2>& B,
		      Vector<complex<double>, Vect_Full, Allocator3>& alpha,
		      Vector<complex<double>, Vect_Full, Allocator4>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, ColMajor> C(n,n), D(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	{
	  C(i,j) = A(i,j);
	  D(i,j) = B(i,j);
	}
    
    GetEigenvalues(C, D, alpha, beta);
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4, class Allocator5>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop1, ColSymPacked, Allocator1>& A,
			      Matrix<complex<double>,
			      Prop2, ColSymPacked, Allocator2>& B,
			      Vector<complex<double>, 
			      Vect_Full, Allocator3>& alpha,
			      Vector<complex<double>,
			      Vect_Full, Allocator4>& beta,
			      Matrix<complex<double>,
			      General, ColMajor, Allocator5>& z,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    Matrix<complex<double>, General, ColMajor> C(n,n), D(n,n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
	{
	  C(i,j) = A(i,j);
	  D(i,j) = B(i,j);
	}
    
    GetEigenvaluesEigenvec(C, D, alpha, beta, z);
  }
  
  
  /* RowHermPacked */
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<complex<float>,
		      Prop1, RowHermPacked, Allocator1>& A,
		      Matrix<complex<float>,
		      Prop2, RowHermPacked, Allocator2>& B,
		      Vector<float, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 2*n;
    Vector<float> work(lwork);
    Vector<float> rwork(3*n);
    chpgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   A.GetData(), &n, work.GetData(), rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop1, RowHermPacked, Allocator1>& A,
			      Matrix<complex<float>,
			      Prop2, RowHermPacked, Allocator2>& B,
			      Vector<float, Vect_Full, Allocator3>& w,
			      Matrix<complex<float>,
			      General, RowMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('V'); int lwork = 2*n;
    Vector<float> work(lwork);
    Vector<float> rwork(3*n);
    chpgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   z.GetData(), &n, work.GetData(), rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<complex<double>,
		      Prop1, RowHermPacked, Allocator1>& A,
		      Matrix<complex<double>,
		      Prop2, RowHermPacked, Allocator2>& B,
		      Vector<double, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('N');
    int lwork = 2*n;
    Vector<double> work(lwork);
    Vector<double> rwork(3*n);
    zhpgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   A.GetData(), &n, work.GetData(), rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop1, RowHermPacked, Allocator1>& A,
			      Matrix<complex<double>,
			      Prop2, RowHermPacked, Allocator2>& B,
			      Vector<double, Vect_Full, Allocator3>& w,
			      Matrix<complex<double>,
			      General, RowMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('L'); char job('V'); int lwork = 2*n;
    Vector<double> work(lwork);
    Vector<double> rwork(3*n);
    zhpgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   z.GetData(), &n, work.GetData(), rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  /* ColHermPacked */
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<complex<float>,
		      Prop1, ColHermPacked, Allocator1>& A,
		      Matrix<complex<float>,
		      Prop2, ColHermPacked, Allocator2>& B,
		      Vector<float, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('N');
    int lwork = 2*n;
    Vector<float> work(lwork);
    Vector<float> rwork(3*n);
    chpgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(),
	   w.GetData(), A.GetData(), &n, work.GetData(),
	   rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop1, ColHermPacked, Allocator1>& A,
			      Matrix<complex<float>,
			      Prop2, ColHermPacked, Allocator2>& B,
			      Vector<float, Vect_Full, Allocator3>& w,
			      Matrix<complex<float>,
			      General, ColMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('V');
    int lwork = 3*n;
    Vector<float> work(lwork);
    Vector<float> rwork(3*n);
    chpgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   z.GetData(), &n, work.GetData(), rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3>
  void GetEigenvalues(Matrix<complex<double>,
		      Prop1, ColHermPacked, Allocator1>& A,
		      Matrix<complex<double>,
		      Prop2, ColHermPacked, Allocator2>& B,
		      Vector<double, Vect_Full, Allocator3>& w,
		      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('N');
    int lwork = 2*n;
    Vector<double> work(lwork);
    Vector<double> rwork(3*n);
    zhpgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(),
	   w.GetData(), A.GetData(), &n, work.GetData(),
	   rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop1, ColHermPacked, Allocator1>& A,
			      Matrix<complex<double>,
			      Prop2, ColHermPacked, Allocator2>& B,
			      Vector<double, Vect_Full, Allocator3>& w,
			      Matrix<complex<double>,
			      General, ColMajor, Allocator4>& z,
			      LapackInfo& info = lapack_info)
  {
    int itype = 1;
    int n = A.GetM();
    char uplo('U'); char job('V');
    int lwork = 3*n;
    Vector<double> work(lwork);
    Vector<double> rwork(3*n);
    zhpgv_(&itype, &job, &uplo, &n, A.GetData(), B.GetData(), w.GetData(),
	   z.GetData(), &n, work.GetData(), rwork.GetData(),
	   &lapack_info.GetInfoRef());
  }
  
  
  /* RowMajor */
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3,
	   class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<float, Prop1, RowMajor, Allocator1>& A,
		      Matrix<float, Prop2, RowMajor, Allocator2>& B,
		      Vector<float, Vect_Full, Allocator3>& alpha_real,
		      Vector<float, Vect_Full, Allocator4>& alpha_imag,
		      Vector<float, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N');
    int lwork = 8*n+16; Vector<float> work(lwork);
    
    sggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha_real.GetData(), alpha_imag.GetData(), beta.GetData(),
	   A.GetData(), &n, A.GetData(), &n, 
	   work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Allocator1,
	     class Allocator2, class Allocator3, class Allocator4,
	   class Allocator5, class Allocator6>
  void GetEigenvaluesEigenvec(Matrix<float, Prop1, RowMajor, Allocator1>& A,
			      Matrix<float, Prop2, RowMajor, Allocator2>& B,
			      Vector<float, Vect_Full, Allocator3>& alpha_real,
			      Vector<float, Vect_Full, Allocator4>& alpha_imag,
			      Vector<float, Vect_Full, Allocator5>& beta,
			      Matrix<float, Prop3, RowMajor, Allocator6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('V'), jobvr('N');
    int lwork = 8*n+16; Vector<float> work(lwork);
    
    sggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha_real.GetData(), alpha_imag.GetData(), beta.GetData(),
	   V.GetData(), &n, V.GetData(), &n, 
	   work.GetData(), &lwork, &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(V);
    // conjugate if necessary
    int i = 0;
    while (i < n)
      {
	if (i < (n-1))
	  if (alpha_real(i) == alpha_real(i+1))
	    {
	      for (int j = 0; j < n; j++)
		V(j,i+1) = -V(j,i+1);
	      
	      i++;
	    }
	
	i++;
      }
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<complex<float>, Prop1, RowMajor, Allocator1>& A,
		      Matrix<complex<float>, Prop2, RowMajor, Allocator2>& B,
		      Vector<complex<float>, Vect_Full, Allocator4>& alpha,
		      Vector<complex<float>, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N'); int lwork = 2*n;
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(8*n);
    
    cggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha.GetData(), beta.GetData(), A.GetData(), &n, A.GetData(), &n,
	   work.GetData(), &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Allocator1,
	   class Allocator2, class Allocator4,
	   class Allocator5, class Allocator6>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop1, RowMajor, Allocator1>& A,
			      Matrix<complex<float>,
			      Prop2, RowMajor, Allocator2>& B,
			      Vector<complex<float>,
			      Vect_Full, Allocator4>& alpha,
			      Vector<complex<float>,
			      Vect_Full, Allocator5>& beta,
			      Matrix<complex<float>,
			      Prop3, RowMajor, Allocator6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('V'), jobvr('N');
    int lwork = 2*n; Vector<complex<float> > work(lwork);
    Vector<float> rwork(8*n);
    
    cggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n, alpha.GetData(),
	   beta.GetData(), V.GetData(), &n, V.GetData(), &n, work.GetData(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
    
    TransposeConjSquareMatrix(V);
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3,
	   class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<double, Prop1, RowMajor, Allocator1>& A,
		      Matrix<double, Prop2, RowMajor, Allocator2>& B,
		      Vector<double, Vect_Full, Allocator3>& alpha_real,
		      Vector<double, Vect_Full, Allocator4>& alpha_imag,
		      Vector<double, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N');
    int lwork = 8*n+16; Vector<double> work(lwork);
    
    dggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha_real.GetData(), alpha_imag.GetData(), beta.GetData(),
	   A.GetData(), &n, A.GetData(), &n, 
	   work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Allocator1,
	     class Allocator2, class Allocator3, class Allocator4,
	   class Allocator5, class Allocator6>
  void GetEigenvaluesEigenvec(Matrix<double, Prop1, RowMajor, Allocator1>& A,
			      Matrix<double, Prop2, RowMajor, Allocator2>& B,
			      Vector<double, Vect_Full, Allocator3>& alpha_real,
			      Vector<double, Vect_Full, Allocator4>& alpha_imag,
			      Vector<double, Vect_Full, Allocator5>& beta,
			      Matrix<double, Prop3, RowMajor, Allocator6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('V'), jobvr('N');
    int lwork = 8*n+16; Vector<double> work(lwork);
    
    dggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha_real.GetData(), alpha_imag.GetData(), beta.GetData(),
	   V.GetData(), &n, V.GetData(), &n, 
	   work.GetData(), &lwork, &lapack_info.GetInfoRef());
    
    TransposeSquareMatrix(V);
    // conjugate if necessary
    int i = 0;
    while (i < n)
      {
	if (i < (n-1))
	  if (alpha_real(i) == alpha_real(i+1))
	    {
	      for (int j = 0; j < n; j++)
		V(j,i+1) = -V(j,i+1);
	      
	      i++;
	    }
	
	i++;
      }
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<complex<double>, Prop1, RowMajor, Allocator1>& A,
		      Matrix<complex<double>, Prop2, RowMajor, Allocator2>& B,
		      Vector<complex<double>, Vect_Full, Allocator4>& alpha,
		      Vector<complex<double>, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N'); int lwork = 2*n;
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(8*n);
    
    zggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha.GetData(), beta.GetData(), A.GetData(), &n, A.GetData(), &n,
	   work.GetData(), &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Allocator1,
	   class Allocator2, class Allocator4,
	   class Allocator5, class Allocator6>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop1, RowMajor, Allocator1>& A,
			      Matrix<complex<double>,
			      Prop2, RowMajor, Allocator2>& B,
			      Vector<complex<double>,
			      Vect_Full, Allocator4>& alpha,
			      Vector<complex<double>,
			      Vect_Full, Allocator5>& beta,
			      Matrix<complex<double>,
			      Prop3, RowMajor, Allocator6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('V'), jobvr('N');
    int lwork = 2*n; Vector<complex<double> > work(lwork);
    Vector<double> rwork(8*n);
    
    zggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n, alpha.GetData(),
	   beta.GetData(), V.GetData(), &n, V.GetData(), &n, work.GetData(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
    
    TransposeConjSquareMatrix(V);
  }
  
  
  /* ColMajor */
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3,
	   class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<float, Prop1, ColMajor, Allocator1>& A,
		      Matrix<float, Prop2, ColMajor, Allocator2>& B,
		      Vector<float, Vect_Full, Allocator3>& alpha_real,
		      Vector<float, Vect_Full, Allocator4>& alpha_imag,
		      Vector<float, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N');
    int lwork = 8*n+16; Vector<float> work(lwork);
    
    sggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha_real.GetData(), alpha_imag.GetData(), beta.GetData(),
	   A.GetData(), &n, A.GetData(), &n, 
	   work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Allocator1,
	   class Allocator2, class Allocator3, class Allocator4,
	   class Allocator5, class Allocator6>
  void GetEigenvaluesEigenvec(Matrix<float, Prop1, ColMajor, Allocator1>& A,
			      Matrix<float, Prop2, ColMajor, Allocator2>& B,
			      Vector<float,
			      Vect_Full, Allocator3>& alpha_real,
			      Vector<float,
			      Vect_Full, Allocator4>& alpha_imag,
			      Vector<float, Vect_Full, Allocator5>& beta,
			      Matrix<float, Prop3, ColMajor, Allocator6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('V'), jobvr('N');
    int lwork = 8*n+16; Vector<float> work(lwork);
    
    sggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(),
	   &n, alpha_real.GetData(), alpha_imag.GetData(),
	   beta.GetData(), V.GetData(), &n, V.GetData(), &n, 
	   work.GetData(), &lwork, &lapack_info.GetInfoRef());
    
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<complex<float>, Prop1, ColMajor, Allocator1>& A,
		      Matrix<complex<float>, Prop2, ColMajor, Allocator2>& B,
		      Vector<complex<float>, Vect_Full, Allocator4>& alpha,
		      Vector<complex<float>, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N'); int lwork = 2*n;
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(8*n);
    
    cggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(),
	   &n, alpha.GetData(),
	   beta.GetData(), A.GetData(), &n, A.GetData(), &n, work.GetData(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Allocator1,
	   class Allocator2, class Allocator4,
	   class Allocator5, class Allocator6>
  void GetEigenvaluesEigenvec(Matrix<complex<float>,
			      Prop1, ColMajor, Allocator1>& A,
			      Matrix<complex<float>,
			      Prop2, ColMajor, Allocator2>& B,
			      Vector<complex<float>,
			      Vect_Full, Allocator4>& alpha,
			      Vector<complex<float>,
			      Vect_Full, Allocator5>& beta,
			      Matrix<complex<float>,
			      Prop3, ColMajor, Allocator6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('V'); int lwork = 2*n;
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(8*n); 
    cggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(),
	   &n, alpha.GetData(),
	   beta.GetData(), V.GetData(), &n, V.GetData(), &n, work.GetData(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator3,
	   class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<double, Prop1, ColMajor, Allocator1>& A,
		      Matrix<double, Prop2, ColMajor, Allocator2>& B,
		      Vector<double, Vect_Full, Allocator3>& alpha_real,
		      Vector<double, Vect_Full, Allocator4>& alpha_imag,
		      Vector<double, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N');
    int lwork = 8*n+16; Vector<double> work(lwork);
    
    dggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(), &n,
	   alpha_real.GetData(), alpha_imag.GetData(), beta.GetData(),
	   A.GetData(), &n, A.GetData(), &n, 
	   work.GetData(), &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Allocator1,
	   class Allocator2, class Allocator3, class Allocator4,
	   class Allocator5, class Allocator6>
  void GetEigenvaluesEigenvec(Matrix<double, Prop1, ColMajor, Allocator1>& A,
			      Matrix<double, Prop2, ColMajor, Allocator2>& B,
			      Vector<double,
			      Vect_Full, Allocator3>& alpha_real,
			      Vector<double,
			      Vect_Full, Allocator4>& alpha_imag,
			      Vector<double, Vect_Full, Allocator5>& beta,
			      Matrix<double, Prop3, ColMajor, Allocator6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('V'), jobvr('N');
    int lwork = 8*n+16; Vector<double> work(lwork);
    
    dggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(),
	   &n, alpha_real.GetData(), alpha_imag.GetData(),
	   beta.GetData(), V.GetData(), &n, V.GetData(), &n, 
	   work.GetData(), &lwork, &lapack_info.GetInfoRef());
    
  }
  
  
  template<class Prop1, class Prop2, class Allocator1,
	   class Allocator2, class Allocator4, class Allocator5>
  void GetEigenvalues(Matrix<complex<double>, Prop1, ColMajor, Allocator1>& A,
		      Matrix<complex<double>, Prop2, ColMajor, Allocator2>& B,
		      Vector<complex<double>, Vect_Full, Allocator4>& alpha,
		      Vector<complex<double>, Vect_Full, Allocator5>& beta,
		      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('N'); int lwork = 2*n;
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(8*n);
    
    zggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(),
	   &n, alpha.GetData(),
	   beta.GetData(), A.GetData(), &n, A.GetData(), &n, work.GetData(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Prop2, class Prop3, class Allocator1,
	   class Allocator2, class Allocator4,
	   class Allocator5, class Allocator6>
  void GetEigenvaluesEigenvec(Matrix<complex<double>,
			      Prop1, ColMajor, Allocator1>& A,
			      Matrix<complex<double>,
			      Prop2, ColMajor, Allocator2>& B,
			      Vector<complex<double>,
			      Vect_Full, Allocator4>& alpha,
			      Vector<complex<double>,
			      Vect_Full, Allocator5>& beta,
			      Matrix<complex<double>,
			      Prop3, ColMajor, Allocator6>& V,
			      LapackInfo& info = lapack_info)
  {
    int n = A.GetM();
    char jobvl('N'), jobvr('V'); int lwork = 2*n;
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(8*n); 
    zggev_(&jobvl, &jobvr, &n, A.GetData(), &n, B.GetData(),
	   &n, alpha.GetData(),
	   beta.GetData(), V.GetData(), &n, V.GetData(), &n, work.GetData(),
	   &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  // GENERALIZED EIGENVALUE PROBLEM //
  ////////////////////////////////////
  
  
  //////////////////////////////////
  // SINGULAR VALUE DECOMPOSITION //
  
  
  /* RowMajor */
  
  
  template<class Prop1, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetSVD(Matrix<float, Prop1, RowMajor, Allocator1>& A,
	      Vector<float, Vect_Full, Allocator4>& lambda,
	      Matrix<float, General, RowMajor, Allocator2>& u,
	      Matrix<float, General, RowMajor, Allocator3>& v,
	      LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); int n = A.GetM();
    char jobl('A'), jobr('A');
    int lwork = max(3*min(m,n)+max(m,n), 5*min(m,n));
    Vector<float> work(lwork);
    sgesvd_(&jobl, &jobr, &m, &n, A.GetData(), &n, lambda.GetData(),
	    u.GetData(), &n, v.GetData(), &n, work.GetData(),
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetSVD(Matrix<complex<float>, Prop1, RowMajor, Allocator1>& A,
	      Vector<complex<float>, Vect_Full, Allocator4>& lambda,
	      Matrix<complex<float>, General, RowMajor, Allocator2>& u,
	      Matrix<complex<float>, General, RowMajor, Allocator3>& v,
	      LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); int n = A.GetM();
    char jobl('A'), jobr('A');
    int lwork = 2*min(m,n)+max(m,n);
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(5*min(m,n));
    cgesvd_(&jobl, &jobr, &m, &n, A.GetDataVoid(), &n, lambda.GetDataVoid(),
	    u.GetDataVoid(), &n, v.GetDataVoid(), &n, work.GetDataVoid(),
	    &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  template<class Prop1, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetSVD(Matrix<double, Prop1, RowMajor, Allocator1>& A,
	      Vector<double, Vect_Full, Allocator4>& lambda,
	      Matrix<double, General, RowMajor, Allocator2>& u,
	      Matrix<double, General, RowMajor, Allocator3>& v,
	      LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); int n = A.GetM();
    char jobl('A'), jobr('A');
    int lwork = max(3*min(m,n)+max(m,n), 5*min(m,n));
    Vector<double> work(lwork);
    dgesvd_(&jobl, &jobr, &m, &n, A.GetData(), &n, lambda.GetData(),
	    u.GetData(), &n, v.GetData(), &n, work.GetData(),
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetSVD(Matrix<complex<double>, Prop1, RowMajor, Allocator1>& A,
	      Vector<complex<double>, Vect_Full, Allocator4>& lambda,
	      Matrix<complex<double>, General, RowMajor, Allocator2>& u,
	      Matrix<complex<double>, General, RowMajor, Allocator3>& v,
	      LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); int n = A.GetM();
    char jobl('A'), jobr('A');
    int lwork = 2*min(m,n)+max(m,n);
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(5*min(m,n));
    zgesvd_(&jobl, &jobr, &m, &n, A.GetDataVoid(), &n, lambda.GetDataVoid(),
	    u.GetDataVoid(), &n, v.GetDataVoid(), &n, work.GetDataVoid(),
	    &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  /* ColMajor */
  
  
  template<class Prop1, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetSVD(Matrix<float, Prop1, ColMajor, Allocator1>& A,
	      Vector<float, Vect_Full, Allocator4>& lambda,
	      Matrix<float, General, ColMajor, Allocator2>& u,
	      Matrix<float, General, ColMajor, Allocator3>& v,
	      LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); int n = A.GetM();
    char jobl('A'), jobr('A');
    int lwork = max(3*min(m,n)+max(m,n), 5*min(m,n));
    Vector<float> work(lwork);
    sgesvd_(&jobl, &jobr, &m, &n, A.GetData(), &n, lambda.GetData(),
	    u.GetData(), &n, v.GetData(), &n, work.GetData(),
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetSVD(Matrix<complex<float>, Prop1, ColMajor, Allocator1>& A,
	      Vector<complex<float>, Vect_Full, Allocator4>& lambda,
	      Matrix<complex<float>, General, ColMajor, Allocator2>& u,
	      Matrix<complex<float>, General, ColMajor, Allocator3>& v,
	      LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); int n = A.GetM();
    char jobl('A'), jobr('A');
    int lwork = 2*min(m,n)+max(m,n);
    Vector<complex<float> > work(lwork);
    Vector<float> rwork(5*min(m,n));
    cgesvd_(&jobl, &jobr, &m, &n, A.GetDataVoid(), &n, lambda.GetDataVoid(),
	    u.GetDataVoid(), &n, v.GetDataVoid(), &n, work.GetDataVoid(),
	    &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetSVD(Matrix<double, Prop1, ColMajor, Allocator1>& A,
	      Vector<double, Vect_Full, Allocator4>& lambda,
	      Matrix<double, General, ColMajor, Allocator2>& u,
	      Matrix<double, General, ColMajor, Allocator3>& v,
	      LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); int n = A.GetM();
    char jobl('A'), jobr('A');
    int lwork = max(3*min(m,n)+max(m,n), 5*min(m,n));
    Vector<double> work(lwork);
    dgesvd_(&jobl, &jobr, &m, &n, A.GetData(), &n, lambda.GetData(),
	    u.GetData(), &n, v.GetData(), &n, work.GetData(),
	    &lwork, &lapack_info.GetInfoRef());
  }
  
  
  template<class Prop1, class Allocator1, class Allocator2,
	   class Allocator3, class Allocator4>
  void GetSVD(Matrix<complex<double>, Prop1, ColMajor, Allocator1>& A,
	      Vector<complex<double>, Vect_Full, Allocator4>& lambda,
	      Matrix<complex<double>, General, ColMajor, Allocator2>& u,
	      Matrix<complex<double>, General, ColMajor, Allocator3>& v,
	      LapackInfo& info = lapack_info)
  {
    int m = A.GetM(); int n = A.GetM();
    char jobl('A'), jobr('A');
    int lwork = 2*min(m,n)+max(m,n);
    Vector<complex<double> > work(lwork);
    Vector<double> rwork(5*min(m,n));
    zgesvd_(&jobl, &jobr, &m, &n, A.GetDataVoid(), &n, lambda.GetDataVoid(),
	    u.GetDataVoid(), &n, v.GetDataVoid(), &n, work.GetDataVoid(),
	    &lwork, rwork.GetData(), &lapack_info.GetInfoRef());
  }
  
  
  // SINGULAR VALUE DECOMPOSITION //
  //////////////////////////////////
  
  
} // end namespace

#define SELDON_FILE_LAPACK_EIGENVALUES_CXX
#endif