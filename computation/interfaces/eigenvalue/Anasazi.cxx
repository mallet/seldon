// Copyright (C) 2013 Marc Duruflé
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

#ifndef SELDON_FILE_ANASAZI_CXX

#include "Anasazi.hxx"

namespace Seldon
{

  //! real case, z = x, zimag = y
  template<class T>
  void SetComplexEigenvalue(const T& x, const T& y, T& z, T& zimag)
  {
    z = x; zimag = y;
  }


  //! real case, z = (x, y), zimag = 0
  template<class T>
  void SetComplexEigenvalue(const T& x, const T& y, complex<T>& z, complex<T>& zimag)
  {
    z = complex<T>(x, y);
    zimag = 0;
  }

  
  //! computation of eigenvalues and related eigenvectors
  /*!
    \param[in,out] var eigenproblem to solve
    \param[out] eigen_values eigenvalue
    \param[out] eigen_vectors eigenvectors
  */
  template<class EigenProblem, class T, class Allocator1,
           class Allocator2, class Allocator3>
  void FindEigenvaluesAnasazi(EigenProblem& var,
			      Vector<T, VectFull, Allocator1>& eigen_values,
			      Vector<T, VectFull, Allocator2>& lambda_imag,
			      Matrix<T, General, ColMajor, Allocator3>& eigen_vectors)
  {
    int n = var.GetM();
    string which("LM");
    switch (var.GetTypeSorting())
      {
      case EigenProblem::SORTED_REAL : which = "LR"; break;
      case EigenProblem::SORTED_IMAG : which = "LI"; break;
      case EigenProblem::SORTED_MODULUS : which = "LM"; break;
      }
    
    if (var.GetTypeSpectrum() == var.SMALL_EIGENVALUES)
      {
        switch (var.GetTypeSorting())
          {
          case EigenProblem::SORTED_REAL : which = "SR"; break;
          case EigenProblem::SORTED_IMAG : which = "SI"; break;
          case EigenProblem::SORTED_MODULUS : which = "SM"; break;
          }
      }

    // initializaing of computation
    var.Init(n);
    
    T shiftr = var.GetShiftValue(), shifti = var.GetImagShiftValue();    
    T zero, one;
    SetComplexZero(zero);
    SetComplexOne(one);
        
    // mass matrix for diagonal case, and Cholesky case
    typedef typename EigenProblem::MassValue Tmass;
    Vector<Tmass> Dh_diag;
    int print_level = var.GetPrintLevel();

    int solver = var.GetEigensolverType();
    
    typedef Anasazi::MultiVec<T>  MV;
    
    int nev = var.GetNbAskedEigenvalues();
    int nb_blocks = var.GetNbBlocks();
    int blockSize = var.GetNbArnoldiVectors();
    int maxIters = var.GetNbMaximumIterations();
    int maxRestarts = var.GetNbMaximumRestarts();
    typename ClassComplexType<T>::Treal tol = var.GetStoppingCriterion();
    
    // Create parameter list to pass into solver
    Teuchos::ParameterList MyPL;
    MyPL.set("Which", which);
    MyPL.set("Block Size", blockSize);    
    MyPL.set("Maximum Iterations", maxIters);
    
    // orthogonalisation manager : DGKS or SVQB
    if (var.GetOrthoManager() == var.ORTHO_SVQB)
      MyPL.set("Orthogonalization", "SVQB");
    else
      MyPL.set("Orthogonalization", "DGKS");
    
    MyPL.set("Verbosity", print_level);
    MyPL.set("Convergence Tolerance", tol);
        
    // MyPL.set("Relative Convergence Tolerance", tol);
    // MyPL.set("Convergence Norm", "2");
    // MyPL.set("Use Locking", useLocking_);
    // MyPL.set("Relative Locking Tolerance", rellocktol_);
    // locktol_ = convtol_/10;
    // MyPL.set("Locking Tolerance", locktol_);
    // MyPL.set("Locking Norm", "2"));
    // MyPL.set("Max Locked", maxLocked_);
    // MyPL.set("Locking Quorum", lockQuorum_);
    // MyPL.set("Full Ortho",fullOrtho_);
    
    // parameters relative to BlockDavidson and BlockKrylovSchur
    MyPL.set("Num Blocks", nb_blocks);
    //MyPL.set("Num Restart Blocks", nb_blocks-1);
    MyPL.set("Maximum Restarts", maxRestarts);
    //MyPL.set("In Situ Restarting", string());
    
    // parameters relative to BlockKrylovSchur
    // MyPL.set("Extra NEV Blocks", 0);
    // MyPL.set("Dynamic Extra NEV", string())
    // MyPL.set("Step Size", 0);
    // MyPL.get("Orthogonalization Constant", kappa);
       
    // Create initial vectors
    //cout << "Calcul valeurs propres Anasazi" << endl;
    Teuchos::RCP<MV> ivec = Teuchos::rcp( new Anasazi::MyMultiVec<T>(n, blockSize) );
    ivec->MvRandom();

    typedef Anasazi::OperatorAnasaziEigen<EigenProblem, T> OPsub;
    typedef Anasazi::Operator<T> OP;
    Teuchos::RCP<const OP> A, M, Op;
    A = Teuchos::rcp(new Anasazi::OperatorAnasaziEigen<EigenProblem, T>(var, OPsub::OPERATOR_A));
    M = Teuchos::rcp(new Anasazi::OperatorAnasaziEigen<EigenProblem, T>(var, OPsub::OPERATOR_M));
    Op = Teuchos::rcp(new Anasazi::OperatorAnasaziEigen<EigenProblem, T>(var, OPsub::OPERATOR_OP));

    // Create eigenproblem
    Teuchos::RCP<Anasazi::BasicEigenproblem<T, MV, OP> > MyProblem;
    if (solver == var.SOLVER_LOBPCG || solver == var.SOLVER_BD)
      MyProblem = Teuchos::rcp( new Anasazi::BasicEigenproblem<T, MV, OP>(A, M, ivec) );
    else
      MyProblem = Teuchos::rcp( new Anasazi::BasicEigenproblem<T, MV, OP>(Op, M, ivec) );
    
    // Inform the eigenproblem that the operator A is symmetric
    bool isherm = var.IsHermitianProblem();
    
    // Set the number of eigenvalues requested and the blocksize the solver should use
    MyProblem->setNEV(nev);
    
    if (var.DiagonalMass() || var.UseCholeskyFactoForMass())
      {	
        // solving a standard eigenvalue problem
        if (var.DiagonalMass())
	  {
	    Vector<Tmass> Dh_diag;
	    
	    // computation of M
            var.ComputeDiagonalMass(Dh_diag);
	    
            // computation of M^{-1/2}
            var.FactorizeDiagonalMass(Dh_diag);
            Dh_diag.Clear();
          }
	else
	  {
	    // computation of M for Cholesky factorisation
            var.ComputeMassForCholesky();
            
            // computation of Cholesky factorisation M = L L^T
            var.FactorizeCholeskyMass();
          }
		
	if (var.GetComputationalMode() == var.REGULAR_MODE)
          {
	    // computation of the stiffness matrix
            var.ComputeStiffnessMatrix();
	  }
	else
	  {
            // computation and factorization of K - sigma M
            var.ComputeAndFactorizeStiffnessMatrix(-shiftr, one);
	  }
      }
    else
      {
	if (var.GetComputationalMode() == var.INVERT_MODE)
          {	    
            // we consider standard problem M^-1 K U = lambda U
            // drawback : the matrix is non-symmetric even if K and M are symmetric
	    isherm = false;
	    if (var.GetTypeSpectrum() != var.CENTERED_EIGENVALUES)
              {
		// large eigenvalues of M^-1 K
                // computation and factorisation of mass matrix
                var.ComputeAndFactorizeStiffnessMatrix(one, zero);
                
                // computation of stiffness matrix
                var.ComputeStiffnessMatrix();
              }
            else
              {
                // large eigenvalues of (K - sigma M)^-1 M
                // computation and factorization of (K - sigma M)
                var.ComputeAndFactorizeStiffnessMatrix(-shiftr, one);

                // computation of M
                var.ComputeMassMatrix();
              }
	  }
	else if (var.GetComputationalMode() == var.REGULAR_MODE)
	  {
	    if (solver == var.SOLVER_BKS)
	      {
		cout << "generalized eigenproblem not implemented for this solver" << endl;
		abort();
	      }
	    
	    // factorization of the mass matrix
            // var.ComputeAndFactorizeStiffnessMatrix(one, zero);
	    
            // computation of stiffness and mass matrix
            var.ComputeStiffnessMatrix();
            var.ComputeMassMatrix();
	    
	  }
	else
	  {
	    cout << "not implemented " << endl;
	    abort();
	  }
      }

    if (!isherm)
      {
	if (solver != var.SOLVER_BKS)
	  {
	    cout << "Only Block-Krylov Schur (SOLVER_BKS) "
		 << " can be used for nonsymmetric system" << endl;
	    abort();
	  }
      }

    MyProblem->setHermitian(isherm);
    
    // Inform the eigenproblem that you are done passing it information
    bool pb_set = MyProblem->setProblem();
    if (!pb_set)
      {
	cout << "Anasazi::BasicEigenproblem::SetProblem() failed "<< endl;
	abort();
      }
    
    // Create the eigensolver 
    Teuchos::RCP< Anasazi::SolverManager<T, MV, OP> > MySolver;
    if (solver == var.SOLVER_LOBPCG)
      MySolver = Teuchos::rcp( new Anasazi::LOBPCGSolMgr<T, MV, OP>(MyProblem, MyPL));
    else if (solver == var.SOLVER_BKS)
      MySolver = Teuchos::rcp( new Anasazi::BlockKrylovSchurSolMgr<T, MV, OP>(MyProblem, MyPL));
    else if (solver == var.SOLVER_BD)
      MySolver = Teuchos::rcp( new Anasazi::BlockDavidsonSolMgr<T, MV, OP>(MyProblem, MyPL));
    else
      {
	cout << "Invalid Anasazi solver: " << solver << endl;	
	abort();
      }
    
    // Solve the problem to the specified tolerances or length
    int returnCode = MySolver->solve();
    if (returnCode != Anasazi::Converged)
      {
	cout << "Anasazi's solver did not converge" << endl;
	abort();
      }
    
    // Get the eigenvalues and eigenvectors from the eigenproblem
    const Anasazi::Eigensolution<T, MV>& sol = MyProblem->getSolution();
    
    eigen_values.Reallocate(sol.Evals.size());
    lambda_imag.Reallocate(sol.Evals.size());    
    eigen_vectors.Reallocate(n, sol.Evals.size());
    typename ClassComplexType<T>::Treal lr, li;
    //typename ClassComplexType<T>::Tcplx Iwp(0, 1), mu;
    //typename ClassComplexType<T>::Tcplx shift = shiftr + Iwp*shifti;
    for (unsigned int i = 0; i < sol.Evals.size(); i++)
      {
	lr = sol.Evals[i].realpart;
	li = sol.Evals[i].imagpart;
	
	SetComplexEigenvalue(lr, li, eigen_values(i), lambda_imag(i));
	
	T* x = static_cast<Anasazi::MyMultiVec<T>& >(*sol.Evecs)[i];
	for (int j = 0; j < n; j++)
	  eigen_vectors(j, i) = x[j];
      }
    
    // modifies eigenvalues and eigenvectors if needed
    ApplyScalingEigenvec(var, eigen_values, lambda_imag, eigen_vectors,
                         shiftr, shifti);
    
    // clears eigenproblem
    var.Clear();
  }
  
}
			 
#define SELDON_FILE_ARPACK_CXX
#endif