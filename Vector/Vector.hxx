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

#ifndef SELDON_FILE_VECTOR_HXX

#include "../Common/Common.hxx"
#include "../Common/Properties.hxx"
#include "../Common/Storage.hxx"
#include "../Common/Errors.hxx"
#include "../Common/Allocator.hxx"

namespace Seldon
{


  //! Base structure for all vectors.
  /*!
    It stores data and the vector size. It defines basic
    methods as well.
  */
  template <class T, class Allocator = SELDON_DEFAULT_ALLOCATOR<T> >
  class Vector_Base
  {
    // typdef declarations.
  public:
    typedef typename Allocator::value_type value_type;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;

    // Static attributes.
  protected:
    static Allocator vect_allocator_;

    // Attributes.
  protected:
    // Number of elements.
    int m_;
    // Pointer to stored elements.
    pointer data_;

    // Methods.
  public:
    // Constructors.
    Vector_Base();
    explicit Vector_Base(int i);
    Vector_Base(const Vector_Base<T, Allocator>& A);
  
    // Destructor.
    ~Vector_Base();

    // Basic methods.
    int GetM() const;
    int GetLength() const;
    int GetSize() const;
    pointer GetData() const;
    const_pointer GetDataConst() const;
    void* GetDataVoid() const;
    const void* GetDataConstVoid() const;

  };


  // Vector allocator.
  template <class T, class Allocator>
  Allocator Vector_Base<T, Allocator>::vect_allocator_;


  //! Full vector class.
  /*!
    Basic vector class (i.e. not sparse).
  */
  template <class T, class Allocator>
  class Vector<T, Vect_Full, Allocator>: public Vector_Base<T, Allocator>
  {
    // typedef declaration.
  public:
    typedef typename Allocator::value_type value_type;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;

    // Attributes.
  private:

    // Methods.
  public:
    // Constructor.
    explicit Vector()  throw();
    explicit Vector(int i);
    Vector(const Vector<T, Vect_Full, Allocator>& A);
    
    // Destructor.
    ~Vector();
    void Clear();

    // Memory management.
    void Reallocate(int i);
    void SetData(int i, pointer data);
    void Nullify();

    // Element access and affectation.
    reference operator() (int i);
#ifndef SWIG
    const_reference operator() (int i) const;
    Vector<T, Vect_Full, Allocator>& operator= (const Vector<T, Vect_Full,
						Allocator>& X);
#endif
    void Copy(const Vector<T, Vect_Full, Allocator>& X);
    void Append(const T& x);

    // Basic functions.
    int GetDataSize();

    // Convenient functions.
    void Zero();
    void Fill();
    template <class T0>
    void Fill(const T0& x);
    template <class T0>
#ifndef SWIG
    Vector<T, Vect_Full, Allocator>& operator= (const T0& X);
#endif
    void FillRand();
    void Print() const;

    // Norms.
    value_type GetNormInf() const;
    int GetNormInfIndex() const;

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

#ifndef SWIG
  template <class T, class Storage, class Allocator>
  ostream& operator << (ostream& out,
			const Vector<T, Storage, Allocator>& V);
#endif


} // namespace Seldon.

#define SELDON_FILE_VECTOR_HXX
#endif