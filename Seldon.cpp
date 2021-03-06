// Copyright (C) 2001-2009 Vivien Mallet
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

#define INSTANCE_BEGIN_LOOP(storage) int InstanceBeginLoop(storage input) {return input.GetBeginLoop(0);}
#define INSTANCE_END_LOOP(storage) int InstanceEndLoop(storage input) {return input.GetEndLoop(0,0,0);}

#ifndef SELDON_FILE_SELDON_CPP

#include "Seldon.hxx"
#include "SeldonComplexMatrixHeader.hxx"
namespace Seldon
{
  template class MallocAlloc<int>;

  template class Vector_Base<int, MallocAlloc<int> >;
  template class Vector<int, VectFull, MallocAlloc<int> >;

  template class MallocAlloc<float>;
  template class Vector_Base<float, MallocAlloc<float> >;
  template class Vector<float, VectFull, MallocAlloc<float> >;

  template class Vector<Vector<int, VectFull, MallocAlloc<int> >, Collection,
                MallocAlloc<Vector<int, VectFull, MallocAlloc<int> > > >;

  template class MallocAlloc<double>;
  template class Vector_Base<double, MallocAlloc<double> >;
  template class Vector<double, VectFull, MallocAlloc<double> >;
  template class Vector<Vector<double, VectFull, MallocAlloc<double> >,
            Collection, MallocAlloc<Vector<double, VectFull, MallocAlloc<double> > > >;

  template class Matrix_Base<int, MallocAlloc<int> >;
  template class Matrix_Pointers<int, General, RowMajor, MallocAlloc<int> >;
  template class Matrix<int, General, RowMajor, MallocAlloc<int> >;
  template class Matrix_Base<float, MallocAlloc<float> >;
  template class Matrix_Pointers<float, General, RowMajor, MallocAlloc<float> >;
  template class Matrix<float, General, RowMajor, MallocAlloc<float> >;
  template class Matrix_Base<double, MallocAlloc<double> >;
  template class Matrix_Pointers<double, General, RowMajor, MallocAlloc<double> >;
  template class Matrix<double, General, RowMajor, MallocAlloc<double> >;


  template class Array3D<int, MallocAlloc<int> >;
  template class Array3D<float, MallocAlloc<float> >;
  template class Array3D<double, MallocAlloc<double> >;
  template class Array4D<int, MallocAlloc<int> >;
  template class Array4D<float, MallocAlloc<float> >;
  template class Array4D<double, MallocAlloc<double> >;

  template class Vector<double, VectSparse, MallocAlloc<double> >;

  template class Matrix_Sparse<double, General, RowSparse, MallocAlloc<double> >;
  template class Matrix<double, General, RowSparse, MallocAlloc<double> >;

  template class MallocAlloc<complex<double> >;
  template class Matrix_Base<complex<double>, MallocAlloc<complex<double> > >;


  template class Matrix_Pointers<complex<double>, General, ColComplexSparse, MallocAlloc<complex<double> > >;
  template class Matrix_ComplexSparse<complex<double>, General, ColComplexSparse, MallocAlloc<complex<double > > >;
  template class Matrix<complex<double>, General, ColComplexSparse, MallocAlloc<complex<double > > >;

  template class Matrix_Pointers<complex<double>, General, RowComplexSparse, MallocAlloc<complex<double> > >;
  template class Matrix_ComplexSparse<complex<double>, General, RowComplexSparse, MallocAlloc<complex<double > > >;
  template class Matrix<complex<double>, General, RowComplexSparse, MallocAlloc<complex<double > > >;


  template class Matrix_Pointers<complex<double>, Symmetric, RowSymComplexSparse, MallocAlloc<complex<double> > >;
  template class Matrix_ComplexSparse<complex<double>, Symmetric, RowSymComplexSparse, MallocAlloc<complex<double > > >;
  template class Matrix<complex<double>, Symmetric, RowSymComplexSparse, MallocAlloc<complex<double > > >;

  template class Matrix_Pointers<complex<double>, Symmetric, ColSymComplexSparse, MallocAlloc<complex<double> > >;
  template class Matrix_ComplexSparse<complex<double>, Symmetric, ColSymComplexSparse, MallocAlloc<complex<double > > >;
  template class Matrix<complex<double>, Symmetric, ColSymComplexSparse, MallocAlloc<complex<double > > >;

  template void ConvertMatrix_to_Coordinates(const Matrix<double, General, RowSparse, MallocAlloc<double> >& A,
                                             Vector<size_t>& IndRow, Vector<size_t>& IndCol,
                                             Vector<double, VectFull>& Val,
                                             size_t index = 0, bool sym = false);

#ifndef SWIG
  template void ConvertMatrix_from_Coordinates(Vector<size_t>& IndRow, Vector<size_t>& IndCol,
                                               Vector<double, VectFull>& Val,
                                               Matrix<double, General, RowSparse, MallocAlloc<double> >& A,
                                               size_t index = 0);
#endif

  INSTANCE_BEGIN_LOOP(ColSymComplexSparse)
  INSTANCE_BEGIN_LOOP(RowMajor)
  INSTANCE_END_LOOP(RowMajor)
  INSTANCE_BEGIN_LOOP(RowSparse)
  INSTANCE_END_LOOP(RowSparse)
  INSTANCE_BEGIN_LOOP(RowSymComplexSparse)
  INSTANCE_BEGIN_LOOP(RowComplexSparse)
  INSTANCE_BEGIN_LOOP(ColComplexSparse)

  Str instance(const Str input)
  {
    Str dummy;
    return Str(input);
  }

  void SetComplex(complex<int> input, int input2)
  {
    SetComplexReal(input2, input);
  }


  // Skips one vector in an input stream.
  void skip_vector_double(istream& input_stream)
  {
    int size;
    input_stream.read(reinterpret_cast<char*>(&size), sizeof(int));
    input_stream.seekg(size * sizeof(double), istream::cur);
  }

  // Skips one matrix in an input stream.
  void skip_matrix_double(istream& input_stream)
  {
    int m, n;
    input_stream.read(reinterpret_cast<char*>(&m), sizeof(int));
    input_stream.read(reinterpret_cast<char*>(&n), sizeof(int));
    input_stream.seekg(m * n * sizeof(double), istream::cur);
  }

}


#define SELDON_FILE_SELDON_CPP
#endif
