// Copyright (C) 2001-2008 Vivien Mallet
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

#ifndef SELDON_FILE_SOLVER_HXX

#include "Computation/Basic_Functions/Matrix_Conversions.cxx"

#ifdef SELDON_WITH_MUMPS
#include "Computation/Interfaces/Direct/Mumps.cxx"
#endif

#ifdef SELDON_WITH_UMFPACK
#include "Computation/Interfaces/Direct/UmfPack.cxx"
#endif

#ifdef SELDON_WITH_SUPERLU
#include "Computation/Interfaces/Direct/SuperLU.cxx"
#endif

#define SELDON_FILE_SOLVER_HXX
#endif