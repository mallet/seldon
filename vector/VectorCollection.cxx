// Copyright (C) 2010, INRIA
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


#ifndef SELDON_FILE_VECTOR_VECTORCOLLECTION_CXX


#include "VectorCollection.hxx"


namespace Seldon
{


  //////////////////////
  // VECTORCOLLECTION //
  //////////////////////


  /**************
   * DESTRUCTOR *
   **************/


  //! Destructor.
  /*! The inner vectors are nullified so that their memory blocks should not
    be deallocated.
  */
  template <class T, class Allocator >
  Vector<T, Collection, Allocator>::~Vector()
  {
    for (size_t i = 0; i < Nvector_; i++)
      vector_(i).Nullify();
    label_map_.clear();
    label_vector_.clear();
  }


  //! Clears the vector collection.
  /*! The inner vectors are nullified so that their memory blocks should not
    be deallocated.
  */
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>::Clear()
  {
    for (size_t i = 0; i < Nvector_; i++)
      vector_(i).Nullify();
    vector_.Clear();
    length_sum_.Clear();
    length_.Clear();
    Nvector_ = 0;
    this->m_ = 0;
    label_map_.clear();
    label_vector_.clear();
  }


  //! Reallocates the vector collection.
  /*! This method first clears the collection. Then it allocates a new vector
    of size \a i, and puts this vector in the collection. On exit, the
    collection is only composed of this vector of size \a i.
    \param[in] i new size.
  */
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>::Reallocate(size_t i)
  {
    Clear();
    vector_type v;
    v.Reallocate(i);
    AddVector(v);
    v.Nullify();
  }


  //! Clears the vector collection.
  /*! The inner vectors are cleared and the memory
    blocks are deallocated.
  */
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>::Deallocate()
  {
    for (size_t i = 0; i < Nvector_; i++)
      vector_(i).Clear();
    vector_.Clear();
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


  //! Returns the vector index of the aggregated vector named \a name.
  /*!
    \param[in] name name of the aggregated vector.
    \return The vector index of the aggregated vector.
  */
  template <class T, class Allocator >
  size_t Vector<T, Collection, Allocator>
  ::GetVectorIndex(string name) const
  {
    map<string,size_t>::const_iterator label_iterator = label_map_.find(name);
    if (label_iterator == label_map_.end())
      throw WrongArgument("VectorCollection::GetVectorIndex(string name)",
			  "Unknown vector name: \"" + name + "\".");
    return label_iterator->second;
  }


  /*! \brief Returns the index of the first element of the aggregated vector
    named \a name. */
  /*!
    \param[in] name name of the aggregated vector.
    \return The index of the first element of the aggregated vector.
  */
  template <class T, class Allocator >
  size_t Vector<T, Collection, Allocator>::GetIndex(string name) const
  {
    map<string,size_t>::const_iterator label_iterator = label_map_.find(name);
    if (label_iterator == label_map_.end())
      throw WrongArgument("VectorCollection::GetIndex(string name)",
			  string("Unknown vector name: \"") + name + "\".");
    return (label_iterator->second == 0) ?
      0 : length_sum_(label_iterator->second - 1);
  }


  //! Returns one of the aggregated vectors.
  /*!
    \param[in] name the name of the vector to be returned.
    \return The aggregated vector named \a name.
  */
  template <class T, class Allocator >
  typename
  Vector<T, Collection, Allocator>::const_vector_reference
  Vector<T, Collection, Allocator>::GetVector(string name) const
  {
    map<string,size_t>::const_iterator label_iterator;
    label_iterator = label_map_.find(name);
    if (label_iterator == label_map_.end())
      throw WrongArgument("VectorCollection::SetVector(string name)",
			  string("Unknown vector name: \"") + name + "\".");
    return GetVector(label_iterator->second);
  }


  //! Returns one of the aggregated vectors.
  /*!
    \param[in] name the name of the vector to be returned.
    \return The aggregated vector named \a name.
  */
  template <class T, class Allocator >
  typename Vector<T, Collection, Allocator>::vector_reference
  Vector<T, Collection, Allocator>::GetVector(string name)
  {
    map<string,size_t>::iterator label_iterator;
    label_iterator = label_map_.find(name);
    if (label_iterator == label_map_.end())
      throw WrongArgument("VectorCollection::SetVector(string name)",
			  string("Unknown vector name: \"") + name + "\".");
    return GetVector(label_iterator->second);
  }


  /*********************************
   * ELEMENT ACCESS AND ASSIGNMENT *
   *********************************/


  //! Access operator.
  /*!
    \param[in] i index.
    \return The value of the vector at 'i'.
  */
  template <class T, class Allocator >
  typename Vector<T, Collection, Allocator>::reference
  Vector<T, Collection, Allocator>::operator() (size_t i)
  {
#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= this->m_)
      throw WrongIndex("VectorCollection::operator()",
		       string("Index should be in [0, ")
                       + to_str(this->m_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    size_t j = 0;
    while (i >= length_sum_(j))
      j++;
    return (j == 0) ? vector_(j)(i) : vector_(j)(i - length_sum_(j - 1));
  }


  //! Access operator.
  /*!
    \param[in] i index.
    \return The value of the vector at 'i'.
  */
  template <class T, class Allocator >
  typename Vector<T, Collection, Allocator>::const_reference
  Vector<T, Collection, Allocator>::operator() (size_t i) const
  {
#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= this->m_)
      throw WrongIndex("VectorCollection::operator()",
		       string("Index should be in [0, ")
                       + to_str(this->m_ - 1)
		       + "], but is equal to " + to_str(i) + ".");
#endif

    size_t j = 0;
    while (i >= length_sum_(j))
      j++;
    return (j == 0) ? vector_(j)(i) : vector_(j)(i - length_sum_(j - 1));
  }


  //! Duplicates a vector collection (assignment operator).
  /*!
    \param[in] X vector collection to be copied.
    \note Memory is duplicated: 'X' is therefore independent from the current
    instance after the copy.
  */
  template <class T, class Allocator >
  Vector<T, Collection, Allocator>&
  Vector<T, Collection, Allocator>::operator=
  (const Vector<T, Collection, Allocator>& X)
  {
    this->Copy(X);
    return *this;
  }


  //! Duplicates a vector collection.
  /*!
    \param[in] X vector collection to be copied.
    \note Memory is duplicated: 'X' is therefore independent from the current
    instance after the copy.
  */
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>
  ::Copy(const Vector<T, Collection, Allocator>& X, bool duplicate_data)
  {
    Clear();
    for (size_t i = 0; i < X.GetNvector(); i++)
      AddVector(X.GetVector(i), "", duplicate_data);
    label_map_.insert(X.label_map_.begin(), X.label_map_.end());
    label_vector_.assign(X.label_vector_.begin(), X.label_vector_.end());
  }


  //! Copies the values of a full vector into the current vector.
  /*!
    \param[in] X full vector to be copied.
    \note Memory is duplicated: 'X' is therefore independent from the current
    instance after the copy.
  */
  template <class T, class Allocator >
  template <class T0, class Allocator0>
  void Vector<T, Collection, Allocator>
  ::Copy(const Vector<T0, VectFull, Allocator0>& X, bool duplicate_data)
  {
#ifdef SELDON_CHECK_BOUNDS
    if (this->m_ != X.GetM())
      throw WrongIndex("VectorCollection::Copy(X)",
		       string("The size of X should be equal to ")
                       + to_str(this->m_ - 1)
		       + ", but is equal to " + to_str(X.GetM()) + ".");
#endif

    for (size_t i = 0; i < X.GetM(); i++)
      (*this)(i) = X(i);
  }


  //! Adds a vector to the list of vectors.
  /*! The vector is "appended" to the existing data.
    \param[in] vector vector to be appended.
    \param[in] name name of the vector to be appended.
  */
  template <class T, class Allocator >
  template <class T0, class Storage0, class Allocator0>
  void Vector<T, Collection, Allocator>
  ::AddVector(const Vector<T0, Storage0, Allocator0>& vector,
	      string name, bool duplicate_data)
  {
    Nvector_++;
    length_.PushBack(0);
    length_sum_.PushBack(this->m_);

    // Resizes 'vector_'.
    collection_type new_vector(Nvector_);
    for (size_t i = 0; i < Nvector_ - 1; i++)
      {
	new_vector(i).SetData(vector_(i));
	vector_(i).Nullify();
      }
    vector_.Clear();
    vector_.SetData(new_vector);
    new_vector.Nullify();

    // Adds the new vector.
    SetVector(Nvector_ - 1, vector, name, duplicate_data);
    if (name != "")
      SetName(Nvector_ - 1, name);
  }


  //! Sets a vector in the list of vectors.
  /*!
    \param[in] i index of the vector to be set.
    \param[in] vector vector to which the \a i th vector is set.
    \param[in] name new name of the  \a i th vector.
  */
  template <class T, class Allocator >
  template <class T0, class Storage0, class Allocator0>
  void Vector<T, Collection, Allocator>
  ::SetVector(size_t i, const Vector<T0, Storage0, Allocator0>& vector,
	      string name, bool duplicate_data)
  {
    size_t size_difference;
    size_difference = vector.GetM() - vector_(i).GetM();
    this->m_ += size_difference;
    length_(i) = vector.GetM();
    for (size_t k = i; k < Nvector_; k++)
      length_sum_(k) += size_difference;
    vector_(i).Nullify();
    if (duplicate_data)
      vector_(i).Copy(vector);
    else
      vector_(i).SetData(vector);
    if (name != "")
      SetName(i, name);
  }


  //! Sets a vector in the list of vectors.
  /*!
    \param[in] name name of the vector to be set.
    \param[in] vector new value of the vector.
  */
  template <class T, class Allocator >
  template <class T0, class Storage0, class Allocator0>
  void Vector<T, Collection, Allocator>
  ::SetVector(string name, const Vector<T0, Storage0, Allocator0>& vector,
              bool duplicate_data)
  {
    map<string,size_t>::iterator label_iterator;
    label_iterator = label_map_.find(name);
    if (label_iterator == label_map_.end())
      throw WrongArgument("VectorCollection::SetVector(string name, Vector)",
			  string("Unknown vector name: \"") + name + "\".");
    SetVector(label_iterator->second, vector, duplicate_data);
  }


  //! Sets the name of a given underlying vector.
  /*!
    \param[in] i a given index.
    \param[in] name name of the underlying vector.
  */
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>
  ::SetName(size_t i, string name)
  {

#ifdef SELDON_CHECK_BOUNDS
    if (i < 0 || i >= Nvector_)
      throw WrongIndex("VectorCollection::SetName(size_t i, string name)",
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


  //! Changes the length of the collection and sets its data array.
  /*!
    \param[in] X collection with the vectors to which the current collection
    will point on exit.
  */
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>
  ::SetData(const Vector<T, Collection, Allocator>& X)
  {
    Clear();
    for (size_t i = 0; i < X.GetNvector(); i++)
      AddVector(X.GetVector(i));
    label_map_.insert(X.label_map_.begin(), X.label_map_.end());
    label_vector_.assign(X.label_vector_.begin(), X.label_vector_.end());
  }


  //! Nullifies vectors of the collection without memory deallocation.
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>::Nullify()
  {
    for (size_t i = 0; i < Nvector_; i++)
      vector_(i).Nullify();
    for (size_t i = 0; i < Nvector_; i++)
      length_(i) = length_sum_(i) = 0;
  }


  ///////////////////////
  // CONVENIENT METHOD //
  ///////////////////////


  //! Fills the collection with a given value.
  /*!
    \param x value to fill the collection with.
  */
  template <class T, class Allocator>
  template <class T0>
  void Vector<T, Collection, Allocator>::Fill(const T0& x)
  {
    for (size_t i = 0; i < Nvector_; i++)
      vector_(i).Fill(x);
  }


  //! Displays the vector.
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>::Print() const
  {
    for (size_t i = 0; i < GetNvector(); i++)
      {
        if (i < int(label_vector_.size()) && label_vector_[i] != "")
          cout << label_vector_[i] << ":" << endl;
        else
          cout << "(noname):" << endl;
	vector_(i).Print();
      }
    cout << endl;
  }


  //! Writes the inner vectors in a file.
  /*!
    The length of the vector (integer) and all elements of the vector are
    stored in binary format.
    \param FileName file name.
    \param with_size if set to 'false', the length of the vector is not saved.
  */
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>
  ::Write(string FileName, bool with_size) const
  {
    ofstream FileStream;
    FileStream.open(FileName.c_str(), ofstream::binary);

#ifdef SELDON_CHECK_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("Vector<Collection>::Write(string FileName)",
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
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>
  ::Write(ostream& FileStream, bool with_size) const
  {

#ifdef SELDON_CHECK_IO
    // Checks if the stream is ready.
    if (!FileStream.good())
      throw IOError("Vector<Collection>::Write(ostream& FileStream)",
                    "The stream is not ready.");
#endif
    if (with_size)
      FileStream
        .write(reinterpret_cast<char*>(const_cast<size_t*>(&this->m_)),
               sizeof(size_t));

    for (size_t i = 0; i < GetNvector(); i++)
      vector_(i).Write(FileStream, false);

#ifdef SELDON_CHECK_IO
    // Checks if data was written.
    if (!FileStream.good())
      throw IOError("Vector<Collection>::Write(ostream& FileStream)",
                    "Output operation failed.");
#endif
  }


  //! Writes the vector in a file.
  /*!
    All elements of the vector are stored in text format. The length is not
    stored.
    \param FileName file name.
  */
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>
  ::WriteText(string FileName) const
  {
    ofstream FileStream;
    FileStream.precision(cout.precision());
    FileStream.flags(cout.flags());
    FileStream.open(FileName.c_str());

#ifdef SELDON_CHECK_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("Vector<Collection>::WriteText(string FileName)",
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
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>
  ::WriteText(ostream& FileStream) const
  {

#ifdef SELDON_CHECK_IO
    // Checks if the stream is ready.
    if (!FileStream.good())
      throw IOError("Vector<Collection>::Write(ostream& FileStream)",
                    "The stream is not ready.");
#endif

    for (size_t i = 0; i < GetNvector(); i++)
      vector_(i).WriteText(FileStream);

#ifdef SELDON_CHECK_IO
    // Checks if data was written.
    if (!FileStream.good())
      throw IOError("Vector<Collection>::Write(ostream& FileStream)",
                    "Output operation failed.");
#endif
  }


  //! Sets the vector from a file.
  /*! Sets the vector according to a binary file that stores the length of the
    collection (number of inner vectors), followed by the inner vectors (i.e.,
    an integer followed by data).
    \param FileName file name.
  */
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>::Read(string FileName)
  {
    ifstream FileStream;
    FileStream.open(FileName.c_str(), ifstream::binary);

#ifdef SELDON_CHECK_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("Vector<Collection>::Read(string FileName)",
                    string("Unable to open file \"") + FileName + "\".");
#endif

    Vector<size_t> length;
    length.Read(FileStream);

    this->Read(FileStream, length);

    FileStream.close();
  }


  //! Sets the vector from a file.
  /*!
    Sets the vector according to a binary file that stores the length of the
    vector (integer) and all elements.
    \param FileName file name.
  */
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>
  ::Read(string FileName, Vector<size_t, VectFull, MallocAlloc<size_t> >& length)
  {
    ifstream FileStream;
    FileStream.open(FileName.c_str(), ifstream::binary);

#ifdef SELDON_CHECK_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("Vector<Collection>::Read(string FileName)",
                    string("Unable to open file \"") + FileName + "\".");
#endif

    this->Read(FileStream, length);

    FileStream.close();
  }


  //! Sets the vector from a file stream.
  /*!
    Sets the vector according to a binary file stream that stores the length
    of the vector (integer) and all elements.
    \param FileStream file stream.
  */
  template <class T, class Allocator >
  void Vector<T, Collection, Allocator>
  ::Read(istream& FileStream,
         Vector<size_t, VectFull, MallocAlloc<size_t> >& length)
  {

#ifdef SELDON_CHECK_IO
    // Checks if the stream is ready.
    if (!FileStream.good())
      throw IOError("Vector<Collection>::Read(istream& FileStream)",
                    "The stream is not ready.");
#endif

    T working_vector;
    working_vector.Read(FileStream);

    Vector<size_t, VectFull, MallocAlloc<size_t> > length_sum;
    size_t Nvector;

    Clear();
    Nvector = length.GetSize();
    length_sum.Reallocate(Nvector);
    length_sum(0) = length(0);
    for (size_t i = 1; i < Nvector; i++)
      length_sum(i) = length_sum(i - 1) + length(i);

    T U, V;
    U.SetData(length(0), &working_vector.GetData()[0]);
    V.Copy(U);
    AddVector(V);
    U.Nullify();
    V.Nullify();
    for (size_t i = 1; i < Nvector; i++)
      {
	U.SetData(length(i), &working_vector.GetData()[length_sum(i - 1)]);
	V.Copy(U);
	AddVector(V);
	U.Nullify();
	V.Nullify();
      }

#ifdef SELDON_CHECK_IO
    // Checks if data was read.
    if (!FileStream.good())
      throw IOError("Vector<Collection>::Read(istream& FileStream)",
                    "Input operation failed.");
#endif

  }


  //! operator<< overloaded for vector collections.
  /*!
    \param[in] out output stream.
    \param[in] V vector collection to be put in the stream.
    \return The updated stream.
  */
  template <class T, class Allocator>
  ostream&  operator <<
  (ostream& out, const Vector<T, Collection, Allocator>& V)
  {
    for (size_t i = 0; i < V.GetNvector() - 1; i++)
      out << V.GetVector(i) << '\t';
    if (V.GetNvector() != 0)
      out << V.GetVector(V.GetNvector() - 1);
    return out;
  }


} // namespace Seldon.


#define SELDON_FILE_VECTOR_VECTORCOLLECTION_CXX
#endif
