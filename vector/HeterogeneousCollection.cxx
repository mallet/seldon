// Copyright (C) 2001-2009 INRIA
// Author(s): Marc Fragu, Vivien Mallet
//
// This file is part of the linear-algebra library Seldon,
// http://seldon.sourceforge.net/.
//
// Seldon is free software; you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your option)
// any later version.
//
// Seldon is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Seldon. If not, see http://www.gnu.org/licenses/.


#ifndef SELDON_FILE_VECTOR_HETEROGENEOUSCOLLECTION_CXX


#include "HeterogeneousCollection.hxx"


namespace Seldon
{


  ////////////////////////////////////
  // VECTOR HETEROGENEOUSCOLLECTION //
  ////////////////////////////////////


  /**************
   * DESTRUCTOR *
   **************/


  //! Destructor.
  /*! The inner vectors are nullified so that their memory blocks should not
    be deallocated.
  */
  template <class T, template <class U> class Allocator >
  Vector<FloatDouble, DenseSparseCollection, Allocator<T> >::~Vector()
  {
    float_dense_c_.Clear();
    float_sparse_c_.Clear();
    double_dense_c_.Clear();
    double_sparse_c_.Clear();
    collection_.Clear();
    subvector_.Clear();
    length_sum_.Clear();
    length_.Clear();
    Nvector_ = 0;
    this->m_ = 0;
    label_map_.clear();
    label_vector_.clear();
  }


  //! Clears the vector collection.
  /*! The inner vectors are nullified so that their memory blocks should not
    be deallocated.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::Clear()
  {
    float_dense_c_.Clear();
    float_sparse_c_.Clear();
    double_dense_c_.Clear();
    double_sparse_c_.Clear();
    collection_.Clear();
    subvector_.Clear();
    length_sum_.Clear();
    length_.Clear();
    Nvector_ = 0;
    this->m_ = 0;
    label_map_.clear();
    label_vector_.clear();
  }


  //! Clears the vector collection.
  /*! The inner vectors are cleared and the memory
    blocks are deallocated.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::Deallocate()
  {
    float_dense_c_.Deallocate();
    float_sparse_c_.Deallocate();
    double_dense_c_.Deallocate();
    double_sparse_c_.Deallocate();
    collection_.Clear();
    subvector_.Clear();
    length_sum_.Clear();
    length_.Clear();
    Nvector_ = 0;
    this->m_ = 0;
    label_map_.clear();
    label_vector_.clear();
  }


  /**********************
   * VECTORS MANAGEMENT *
   **********************/


  //! Adds a vector to the list of vectors.
  /*! The vector is "appended" to the existing data.
    \param[in] vector vector to be appended.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::AddVector(const Vector<float, VectFull, Allocator<float> >& vector)
  {
    Nvector_++;
    size_t m = vector.GetM();
    this->m_+= m;
    length_.PushBack(m);
    length_sum_.PushBack(this->m_);
    collection_.PushBack(0);
    subvector_.PushBack(float_dense_c_.GetNvector());
    float_dense_c_.AddVector(vector);
  }


  //! Adds a vector to the list of vectors.
  /*! The vector is "appended" to the existing data.
    \param[in] vector vector to be appended.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::AddVector(const Vector<float, VectSparse, Allocator<float> >& vector)
  {
    Nvector_++;
    size_t m = vector.GetM();
    this->m_+= m;
    length_.PushBack(m);
    length_sum_.PushBack(this->m_);
    collection_.PushBack(1);
    subvector_.PushBack(float_sparse_c_.GetNvector());
    float_sparse_c_.AddVector(vector);
  }


  //! Adds a vector to the list of vectors.
  /*! The vector is "appended" to the existing data.
    \param[in] vector vector to be appended.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::AddVector(const Vector<double, VectFull, Allocator<double> >& vector)
  {
    Nvector_++;
    size_t m = vector.GetM();
    this->m_+= m;
    length_.PushBack(m);
    length_sum_.PushBack(this->m_);
    collection_.PushBack(2);
    subvector_.PushBack(double_dense_c_.GetNvector());
    double_dense_c_.AddVector(vector);
  }


  //! Adds a vector to the list of vectors.
  /*! The vector is "appended" to the existing data.
    \param[in] vector vector to be appended.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::AddVector(const Vector<double, VectSparse, Allocator<double> >& vector)
  {
    Nvector_++;
    size_t m = vector.GetM();
    this->m_+= m;
    length_.PushBack(m);
    length_sum_.PushBack(this->m_);
    collection_.PushBack(3);
    subvector_.PushBack(double_sparse_c_.GetNvector());
    double_sparse_c_.AddVector(vector);
  }


  //! Adds a vector to the list of vectors.
  /*! The vector is "appended" to the existing data.
    \param[in] vector vector to be appended.
    \param[in] name name of the vector to be appended.
  */
  template <class T, template <class U> class Allocator >
  template <class T0, class Storage0, class Allocator0>
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::AddVector(const Vector<T0, Storage0, Allocator0>& vector, string name)
  {
    AddVector(vector);
    SetName(Nvector_ - 1, name);
  }


  //! Sets a vector in the list of vectors.
  /*!
    \param[in] i a given index.
    \param[in] vector vector to be appended.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::SetVector(size_t i, const Vector<float, VectFull, Allocator<float> >& vector)
  {

#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= Nvector_)
      throw WrongIndex("Vector<FloatDouble, DenseSparseCollection>"
		       "::SetVector(size_t i, Vector<float, VectFull>)",
		       string("Index should be in [0, ")
                       + to_str(Nvector_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    if (collection_(i) != 0)
      WrongArgument("Vector<FloatDouble, DenseSparseCollection>"
                    "::SetVector(size_t i, Vector<float, VectFull>)",
                    string("The ") + to_str(i) + "-th inner vector "
                    "should be of type " + GetType(i) + ".");

    size_t size_difference;
    size_difference = vector.GetM() - length_(i);
    this->m_ += size_difference;
    length_(i) = vector.GetM();
    for (size_t k = i; k < Nvector_; k++)
      length_sum_(k) += size_difference;
    float_dense_c_.SetVector(subvector_(i), vector);
  }


  //! Sets a vector in the list of vectors.
  /*!
    \param[in] i a given index.
    \param[in] vector vector to be appended.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::SetVector(size_t i,
	      const Vector<float, VectSparse, Allocator<float> >& vector)
  {

#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= Nvector_)
      throw WrongIndex("Vector<FloatDouble, DenseSparseCollection>"
                       "::SetVector(size_t i, Vector<float, VectSparse>)",
		       string("Index should be in [0, ")
                       + to_str(Nvector_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    if (collection_(i) != 1)
      WrongArgument("Vector<FloatDouble, DenseSparseCollection>"
                    "::SetVector(size_t i, Vector<float, VectSparse>)",
                    string("The ") + to_str(i) + "-th inner vector "
                    "should be of type " + GetType(i) + ".");

    size_t size_difference;
    size_difference = vector.GetM() - length_(i);
    this->m_ += size_difference;
    length_(i) = vector.GetM();
    for (size_t k = i; k < Nvector_; k++)
      length_sum_(k) += size_difference;
    float_sparse_c_.SetVector(subvector_(i), vector);
  }


  //! Sets a vector in the list of vectors.
  /*!
    \param[in] i a given index.
    \param[in] vector vector to be appended.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::SetVector(size_t i,
	      const Vector<double, VectFull, Allocator<double> >& vector)
  {

#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= Nvector_)
      throw WrongIndex("Vector<FloatDouble, DenseSparseCollection>"
                       "::SetVector(size_t i, Vector<double, VectFull>)",
		       string("Index should be in [0, ")
                       + to_str(Nvector_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    if (collection_(i) != 2)
      WrongArgument("Vector<FloatDouble, DenseSparseCollection>"
                    "::SetVector(size_t i, Vector<double, VectFull>)",
                    string("The ") + to_str(i) + "-th inner vector "
                    "should be of type " + GetType(i) + ".");

    size_t size_difference;
    size_difference = vector.GetM() - length_(i);
    this->m_ += size_difference;
    length_(i) = vector.GetM();
    for (size_t k = i; k < Nvector_; k++)
      length_sum_(k) += size_difference;
    double_dense_c_.SetVector(subvector_(i), vector);
  }


  //! Sets a vector in the list of vectors.
  /*!
    \param[in] i a given index.
    \param[in] vector vector to be appended.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::SetVector(size_t i,
	      const Vector<double, VectSparse, Allocator<double> >& vector)
  {

#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= Nvector_)
      throw WrongIndex("Vector<FloatDouble, DenseSparseCollection>"
                       "::SetVector(size_t i, Vector<double, VectSparse>)",
		       string("Index should be in [0, ")
                       + to_str(Nvector_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    if (collection_(i) != 3)
      WrongArgument("Vector<FloatDouble, DenseSparseCollection>"
                    "::SetVector(size_t i, Vector<double, VectSparse>)",
                    string("The ") + to_str(i) + "-th inner vector "
                    "should be of type " + GetType(i) + ".");

    size_t size_difference;
    size_difference = vector.GetM() - length_(i);
    this->m_ += size_difference;
    length_(i) = vector.GetM();
    for (size_t k = i; k < Nvector_; k++)
      length_sum_(k) += size_difference;
    double_sparse_c_.SetVector(subvector_(i), vector);
  }


  //! Sets a vector in the list of vectors.
  /*!
    \param[in] i index of the vector to be set.
    \param[in] vector new value of the vector.
    \param[in] name new name of the vector.
  */
  template <class T, template <class U> class Allocator >
  template <class T0, class Storage0, class Allocator0>
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::SetVector(size_t i, const Vector<T0, Storage0, Allocator0>& vector,
	      string name)
  {
    SetVector(i, vector);
    SetName(i, name);
  }


  //! Sets a vector in the list of vectors.
  /*!
    \param[in] name name of the vector to be set.
    \param[in] vector new value of the vector.
  */
  template <class T, template <class U> class Allocator >
  template <class T0, class Storage0, class Allocator0>
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::SetVector(string name, const Vector<T0, Storage0, Allocator0>& vector)
  {
    map<string,size_t>::iterator label_iterator;
    label_iterator = label_map_.find(name);
    if (label_iterator == label_map_.end())
      throw WrongArgument("Vector<FloatDouble, DenseSparseCollection>"
                          "::SetVector(string name, Vector)",
			  string("Unknown vector name: \"") + name + "\".");
    SetVector(label_iterator->second, vector);
  }


  //! Sets a vector in the list of vectors.
  /*!
    \param[in] i a given index.
    \param[in] name name of the underlying vector.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::SetName(size_t i, string name)
  {
#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= Nvector_)
      throw WrongIndex("Vector<FloatDouble, DenseSparseCollection>"
		       "::SetVector(size_t i, string name)",
		       string("Index should be in [0, ")
                       + to_str(Nvector_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    if (i >= size_t(label_vector_.size()))
      label_vector_.resize(Nvector_, "");

    if (label_vector_[i] != "")
      label_map_.erase(label_vector_[i]);

    label_vector_[i] = name;
    label_map_[name] = i;
  }


  //! Nullifies vectors of the collection without memory deallocation.
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >::Nullify()
  {
    Clear();
  }


  //! Returns one of the aggregated vectors.
  /*!
    \param[in] i the index of the vector to be returned.
    \return The \a i th aggregated vector.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::GetVector(size_t i, typename
	      Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
	      ::float_dense_v& vector) const
  {
#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= Nvector_)
      throw WrongIndex("Vector<FloatDouble, DenseSparseCollection>"
                       "::GetVector(size_t i, Vector<float, VectFull>&)",
		       string("Index should be in [0, ")
                       + to_str(Nvector_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    if (collection_(i) != 0)
      WrongArgument("Vector<FloatDouble, DenseSparseCollection>"
                    "::GetVector(size_t i, Vector<float, VectFull>&)",
                    string("The ") + to_str(i) + "-th inner vector "
                    "is of type " + GetType(i) + ".");

    vector.SetData(float_dense_c_.GetVector(subvector_(i)));
  }


  //! Returns one of the aggregated vectors.
  /*!
    \param[in] i the index of the vector to be returned.
    \return The \a i th aggregated vector.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::GetVector(size_t i, typename
	      Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
	      ::float_sparse_v& vector) const
  {
#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= Nvector_)
      throw WrongIndex("Vector<FloatDouble, DenseSparseCollection>"
                       "::GetVector(size_t i, Vector<float, VectSparse>&)",
		       string("Index should be in [0, ")
                       + to_str(Nvector_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    if (collection_(i) != 1)
      WrongArgument("Vector<FloatDouble, DenseSparseCollection>"
                    "::GetVector(size_t i, Vector<float, VectSparse>&)",
                    string("The ") + to_str(i) + "-th inner vector "
                    "is of type " + GetType(i) + ".");

    vector.SetData(float_sparse_c_.GetVector(subvector_(i)));
  }


  //! Returns one of the aggregated vectors.
  /*!
    \param[in] i the index of the vector to be returned.
    \return The \a i th aggregated vector.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::GetVector(size_t i, typename
	      Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
	      ::double_dense_v& vector) const
  {
#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= Nvector_)
      throw WrongIndex("Vector<FloatDouble, DenseSparseCollection>"
                       "::GetVector(size_t i, Vector<double, VectDense>&)",
		       string("Index should be in [0, ")
                       + to_str(Nvector_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    if (collection_(i) != 2)
      WrongArgument("Vector<FloatDouble, DenseSparseCollection>"
                    "::GetVector(size_t i, Vector<double, VectDense>&)",
                    string("The ") + to_str(i) + "-th inner vector "
                    "is of type " + GetType(i) + ".");

    vector.SetData(double_dense_c_.GetVector(subvector_(i)));
  }


  //! Returns one of the aggregated vectors.
  /*!
    \param[in] i the index of the vector to be returned.
    \return The \a i th aggregated vector.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::GetVector(size_t i, typename
	      Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
	      ::double_sparse_v& vector) const
  {
#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= Nvector_)
      throw WrongIndex("Vector<FloatDouble, DenseSparseCollection>"
                       "::GetVector(size_t i, Vector<double, VectSparse>&)",
		       string("Index should be in [0, ")
                       + to_str(Nvector_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    if (collection_(i) != 3)
      WrongArgument("Vector<FloatDouble, DenseSparseCollection>"
                    "::GetVector(size_t i, Vector<double, VectSparse>&)",
                    string("The ") + to_str(i) + "-th inner vector "
                    "is of type " + GetType(i) + ".");

    vector.SetData(double_sparse_c_.GetVector(subvector_(i)));
  }


  //! Returns one of the aggregated vectors.
  /*!
    \param[in] i the index of the vector to be returned.
    \return The \a i th aggregated vector.
  */
  template <class T, template <class U> class Allocator >
  template <class T0, class Storage0, class Allocator0>
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::GetVector(string name,Vector<T0, Storage0, Allocator0>& vector) const
  {
    map<string,size_t>::const_iterator label_iterator;
    label_iterator = label_map_.find(name);
    if (label_iterator == label_map_.end())
      throw WrongArgument("Vector<FloatDouble, DenseSparseCollection>"
                          "::SetVector(string name)",
			  string("Unknown vector name ") + name + ".");
    GetVector(label_iterator->second, vector);
  }


  /*********************************
   * ELEMENT ACCESS AND ASSIGNMENT *
   *********************************/


  //! Access operator.
  /*!
    \param[in] i index.
    \return The value of the vector at 'i'.
  */
  template <class T, template <class U> class Allocator >
  double
  Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::operator() (size_t i) const
  {
#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= this->m_)
      throw WrongIndex("Vector<FloatDouble, DenseSparse>::operator()",
		       string("Index should be in [0, ")
                       + to_str(this->m_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    size_t j = 0;
    while (i >= length_sum_(j))
      j++;

    switch (collection_(j))
      {
      case 0:
	return (j == 0) ? double(float_dense_c_.GetVector(subvector_(j))(i)) :
	  double(float_dense_c_.
		 GetVector(subvector_(j))(i - length_sum_(j - 1)));
      case 1:
	return (j == 0) ? double(float_sparse_c_.GetVector(subvector_(j))(i)):
	  double(float_sparse_c_.
		 GetVector(subvector_(j))(i - length_sum_(j - 1)));
      case 2:
	return j == 0 ? double_dense_c_.GetVector(subvector_(j))(i) :
	  double_dense_c_.GetVector(subvector_(j))(i - length_sum_(j - 1));
      case 3:
	return j == 0 ? double_sparse_c_.GetVector(subvector_(j))(i) :
	  double_sparse_c_.GetVector(subvector_(j))(i - length_sum_(j - 1));
      default:
	return 0.;
      }
  }


  //! Duplicates a vector collection.
  /*!
    \param[in] X vector collection to be copied.
    \note Memory is duplicated: 'X' is therefore independent from the current
    instance after the copy.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::Copy(const Vector<FloatDouble, DenseSparseCollection, Allocator<T> >& X)
  {
    Clear();
    this->m_ = X.GetM();
    collection_.Copy(X.collection_);
    subvector_.Copy(X.subvector_);
    length_.Copy(X.length_);
    length_sum_.Copy(X.length_sum_);

    float_dense_c_.Copy(X.float_dense_c_);
    float_sparse_c_.Copy(X.float_sparse_c_);
    double_dense_c_.Copy(X.double_dense_c_);
    double_sparse_c_.Copy(X.double_sparse_c_);

    label_map_.insert(X.label_map_.begin(), X.label_map_.end());
    label_vector_.assign(X.label_vector_.begin(), X.label_vector_.end());
  }


  //! Multiplies a vector collection by a scalar.
  /*!
    \param[in] alpha scalar.
  */
  template <class T, template <class U> class Allocator >
  template<class T0>
  Vector<FloatDouble, DenseSparseCollection, Allocator<T> >&
  Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::operator*= (const T0& alpha)
  {
    float_dense_c_ *= alpha;
    float_sparse_c_ *= alpha;
    double_dense_c_ *= alpha;
    double_sparse_c_ *= alpha;
    return *this;
  }


  ////////////////////////
  // CONVENIENT METHODS //
  ////////////////////////


  //! Displays the vector.
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::Print() const
  {
    for (size_t i = 0; i < Nvector_; i++)
      {
	if (i < size_t(label_vector_.size()) && label_vector_[i] != "")
	  cout << label_vector_[i] << ":" << endl;
	else
          cout << "(noname):" << endl;

	switch(collection_(i))
	  {
	  case 0:
	    float_dense_c_.GetVector(subvector_(i)).Print();
	    break;
	  case 1:
	    float_sparse_c_.GetVector(subvector_(i)).Print();
	    break;
	  case 2:
	    double_dense_c_.GetVector(subvector_(i)).Print();
	    break;
	  case 3:
	    double_sparse_c_.GetVector(subvector_(i)).Print();
	    break;
	  }
      }
  }


  //! Writes the inner vectors in a file.
  /*!
    The length of the vector (integer) and all elements of the vector are
    stored in binary format.
    \param FileName file name.
    \param with_size if set to 'false', the length of the vector is not saved.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::Write(string FileName, bool with_size) const
  {
    ofstream FileStream;
    FileStream.open(FileName.c_str(), ofstream::binary);

#ifdef SELDON_CHECK_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("Vector<FloatDouble, DenseSparseCollection>"
                    "::Write(string FileName)",
                    string("Unable to open file \"") + FileName + "\".");
#endif

    this->Write(FileStream, with_size);

    FileStream.close();
  }


  //! Writes the vector in a file stream.
  /*!
    The length of the vector (integer) and all elements of the vector are
    stored in binary format.
    \param FileStream file stream.
    \param with_size if set to 'false', the length of the vector is not saved.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::Write(ostream& FileStream, bool with_size) const
  {

#ifdef SELDON_CHECK_IO
    // Checks if the stream is ready.
    if (!FileStream.good())
      throw IOError("Vector<FloatDouble, DenseSparseCollection>"
                    "::Write(ostream& FileStream)",
                    "The stream is not ready.");
#endif
    if (with_size)
      FileStream
        .write(reinterpret_cast<char*>(const_cast<size_t*>(&this->Nvector_)),
               sizeof(size_t));

    collection_.Write(FileStream, with_size);

    for (size_t i = 0; i < Nvector_; i++)
      {
	switch (collection_(i))
	  {
	  case 0:
	    float_dense_c_.GetVector(subvector_(i)).Write(FileStream);
	    break;
	  case 1:
	    float_sparse_c_.GetVector(subvector_(i)).Write(FileStream);
	    break;
	  case 2:
	    double_dense_c_.GetVector(subvector_(i)).Write(FileStream);
	    break;
	  case 3:
	    double_sparse_c_.GetVector(subvector_(i)).Write(FileStream);
	    break;
	  }
      }

#ifdef SELDON_CHECK_IO
    // Checks if data was written.
    if (!FileStream.good())
      throw IOError("Vector<FloatDouble, DenseSparseCollection>"
                    "::Write(ostream& FileStream)",
                    "Output operation failed.");
#endif
  }


  //! Writes the vector in a file.
  /*!
    All elements of the vector are stored in text format. The length is not
    stored.
    \param FileName file name.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::WriteText(string FileName) const
  {
    ofstream FileStream;
    FileStream.precision(cout.precision());
    FileStream.flags(cout.flags());
    FileStream.open(FileName.c_str());

#ifdef SELDON_CHECK_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("Vector<FloatDouble, DenseSparseCollection>"
                    "::WriteText(string FileName)",
                    string("Unable to open file \"") + FileName + "\".");
#endif

    this->WriteText(FileStream);

    FileStream.close();
  }


  //! Writes the vector in a file stream.
  /*!
    All elements of the vector are stored in text format. The length is not
    stored.
    \param FileStream file stream.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::WriteText(ostream& FileStream) const
  {

#ifdef SELDON_CHECK_IO
    // Checks if the stream is ready.
    if (!FileStream.good())
      throw IOError("Vector<FloatDouble, DenseSparseCollection>"
                    "::Write(ostream& FileStream)",
                    "The stream is not ready.");
#endif

    for (size_t i = 0; i < Nvector_; i++)
      {
	switch (collection_(i))
	  {
	  case 0:
	    float_dense_c_.GetVector(subvector_(i)).WriteText(FileStream);
	    break;
	  case 1:
	    float_sparse_c_.GetVector(subvector_(i)).WriteText(FileStream);
	    break;
	  case 2:
	    double_dense_c_.GetVector(subvector_(i)).WriteText(FileStream);
	    break;
	  case 3:
	    double_sparse_c_.GetVector(subvector_(i)).WriteText(FileStream);
	    break;
	  }
      }

#ifdef SELDON_CHECK_IO
    // Checks if data was written.
    if (!FileStream.good())
      throw IOError("Vector<FloatDouble, DenseSparseCollection>"
                    "::Write(ostream& FileStream)",
                    "Output operation failed.");
#endif
  }


  //! Sets the vector from a file.
  /*!
    Sets the vector according to a binary file that stores the length of the
    vector (integer) and all elements.
    \param FileName file name.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::Read(string FileName)
  {
    ifstream FileStream;
    FileStream.open(FileName.c_str(), ifstream::binary);

#ifdef SELDON_CHECK_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("Vector<FloatDouble, DenseSparseCollection>"
                    "::Read(string FileName)",
                    string("Unable to open file \"") + FileName + "\".");
#endif

    this->Read(FileStream);

    FileStream.close();
  }


  //! Sets the vector from a file stream.
  /*!
    Sets the vector according to a binary file stream that stores the length
    of the vector (integer) and all elements.
    \param FileStream file stream.
  */
  template <class T, template <class U> class Allocator >
  void Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::Read(istream& FileStream)
  {

#ifdef SELDON_CHECK_IO
    // Checks if the stream is ready.
    if (!FileStream.good())
      throw IOError("Vector<FloatDouble, DenseSparseCollection>"
                    "::Read(istream& FileStream)",
                    "The stream is not ready.");
#endif

    size_t* Nvector = new size_t;
    FileStream.read(reinterpret_cast<char*>(Nvector), sizeof(size_t));



    Vector<size_t, VectFull, MallocAlloc<size_t> > collection(*Nvector);
    collection.Read(FileStream);

    Clear();

    float_dense_v v0;
    float_sparse_v v1;
    double_dense_v v2;
    double_sparse_v v3;

    for (size_t i = 0; i < *Nvector; i++)
      {
	switch (collection(i))
	  {
	  case 0:
	    v0.Read(FileStream);
	    AddVector(v0);
	    v0.Nullify();
	    break;
	  case 1:
	    v1.Read(FileStream);
	    AddVector(v1);
	    v1.Nullify();
	    break;
	  case 2:
	    v2.Read(FileStream);
	    AddVector(v2);
	    v2.Nullify();
	    break;
	  case 3:
	    v3.Read(FileStream);
	    AddVector(v3);
	    v3.Nullify();
	    break;
	  }
      }

    delete Nvector;

#ifdef SELDON_CHECK_IO
    // Checks if data was read.
    if (!FileStream.good())
      throw IOError("Vector<FloatDouble, DenseSparseCollection>"
                    "::Read(istream& FileStream)",
                    "Input operation failed.");
#endif

  }


  //! operator<< overloaded for vector collections.
  /*!
    \param[in] out output stream.
    \param[in] V vector collection to be put in the stream.
    \return The updated stream.
  */
  template <class T, template <class U> class Allocator >
  ostream&  operator <<
  (ostream& out,
   const Vector<FloatDouble, DenseSparseCollection, Allocator<T> >& V)
  {
    Vector<float, VectFull, Allocator<float> > v0;
    Vector<float, VectSparse, Allocator<float> > v1;
    Vector<double, VectFull, Allocator<double> > v2;
    Vector<double, VectSparse, Allocator<double> > v3;
    for (size_t i = 0; i < V.GetNvector(); i++)
      {
	switch (V.GetCollectionIndex()(i))
	  {
	  case 0:
	    V.GetVector(i, v0);
	    out << v0 << '\t';
	    v0.Nullify();
	    break;
	  case 1:
	    V.GetVector(i, v1);
	    out << v1 << '\t';
	    v1.Nullify();
	    break;
	  case 2:
	    V.GetVector(i, v2);
	    out << v2 << '\t';
	    v2.Nullify();
	    break;
	  case 3:
	    V.GetVector(i, v3);
	    out << v3 << '\t';
	    v3.Nullify();
	    break;
	  }
      }
    return out;
  }


  //////////////////////
  // PROTECTED METHOD //
  //////////////////////


  //! Returns the type of an inner vector in a string.
  /*!
    \param[in] i index of the vector.
    \return The type in format "Vector<{float,double},
    {VectFull,VectSparse}>".
  */
  template <class T, template <class U> class Allocator >
  string Vector<FloatDouble, DenseSparseCollection, Allocator<T> >
  ::GetType(size_t i) const
  {
    if (collection_(i) == 0)
      return "Vector<float, VectDense>";
    else if (collection_(i) == 1)
      return "Vector<float, VectSparse>";
    else if (collection_(i) == 2)
      return "Vector<double, VectDense>";
    else
      return "Vector<double, VectSparse>";
  }


} // namespace Seldon.


#define SELDON_FILE_VECTOR_HETEROGENEOUSCOLLECTION_CXX
#endif
