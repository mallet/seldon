// Copyright (C) 2001-2005 Vivien Mallet
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

// To be included by Seldon.hxx

#ifndef SELDON_FILE_MATRIX_POINTERS_HXX

#include "../Common/Common.hxx"
#include "../Common/Properties.hxx"
#include "../Common/Storage.hxx"
#include "../Common/Errors.hxx"
#include "../Common/Allocator.hxx"

namespace Seldon
{
  

  //! Full matrix class.
  template <class T, class Prop, class Storage,
	    class Allocator = SELDON_DEFAULT_ALLOCATOR<T> >
  class Matrix_Pointers: public Matrix_Base<T, Allocator>
  {
    // typedef declaration.
  public:
    typedef typename Allocator::value_type value_type;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;

    // Attributes.
  protected:
    pointer* me_;

    // Methods.
  public:
    // Constructor.
    Matrix_Pointers();
    Matrix_Pointers(int i, int j);

    // Destructor.
    ~Matrix_Pointers();
    void Clear();

    // Basic methods.
    int GetDataSize() const;

    // Memory management.
    void Reallocate(int i, int j);
    void SetData(int i, int j, pointer data);
    void Nullify();

    // Element access and affectation.
    reference operator() (int i, int j);
#ifndef SWIG
    const_reference operator() (int i, int j) const;
#endif
    reference Val(int i, int j);
#ifndef SWIG
    const_reference Val(int i, int j) const;
    reference operator[] (int i);
    const_reference operator[] (int i) const;
    Matrix_Pointers<T, Prop, Storage, Allocator>&
    operator= (const Matrix_Pointers<T, Prop, Storage, Allocator>& A);
#endif
    void Copy(const Matrix_Pointers<T, Prop, Storage, Allocator>& A);

    // Convenient functions.
    int GetLD() const;
    void Zero();
    void SetIdentity();
    void Fill();
    template <class T0>
    void Fill(const T0& x);
#ifndef SWIG
    template <class T0>
    Matrix_Pointers<T, Prop, Storage, Allocator>& operator= (const T0& x);
#endif
    void FillRand();
    void Print() const;
    void Print(int a, int b, int m, int n) const;
    void Print(int l) const;

    // Input/output functions.
    void Write(string FileName) const;
#ifndef SWIG
    void Write(ofstream& FileStream) const;
#endif
    void WriteText(string FileName) const;
#ifndef SWIG
    void WriteText(ofstream& FileStream) const;
#endif
    void Read(string FileName);
#ifndef SWIG
    void Read(ifstream& FileStream);
#endif

  };


  //! Column-major full-matrix class.
  template <class T, class Prop, class Allocator>
  class Matrix<T, Prop, ColMajor, Allocator>:
    public Matrix_Pointers<T, Prop, ColMajor, Allocator>
  {
  public:
    Matrix()  throw();
    Matrix(int i, int j);

#ifndef SWIG
    template <class T0>
    Matrix<T, Prop, ColMajor, Allocator>& operator= (const T0& x);
#endif
  };


  //! Row-major full-matrix class.
  template <class T, class Prop, class Allocator>
  class Matrix<T, Prop, RowMajor, Allocator>:
    public Matrix_Pointers<T, Prop, RowMajor, Allocator>
  {
  public:
    Matrix()  throw();
    Matrix(int i, int j);

#ifndef SWIG
    template <class T0>
    Matrix<T, Prop, RowMajor, Allocator>& operator= (const T0& x);
#endif
  };


} // namespace Seldon.

#define SELDON_FILE_MATRIX_POINTERS_HXX
#endif