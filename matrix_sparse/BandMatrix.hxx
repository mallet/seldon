#ifndef SELDON_FILE_BAND_MATRIX_HXX

namespace Seldon
{
  class BandedCol : public ColSparse
  {
  };
  
  class ArrowCol : public ColSparse
  {
  };
  
  
  //! base class for a banded-matrix
  template <class T, class Prop, class Storage,
            class Allocator = SELDON_DEFAULT_ALLOCATOR<T> >
  class Matrix_Band
  {
  public :
    typedef T entry_type;
    
    // Attributes.
  protected:
    //! number of extra-diagonals in lower part
    int kl_;
    //! number of extra-diagonals in upper part
    int ku_;
    //! number of rows and columns
    int m_, n_;
    //! values are stored in a dense matrix (in Lapack format)
    Matrix<T, General, ColMajor, Allocator> data_;

  public :
    Matrix_Band();
    
    int GetKL() const;
    int GetKU() const;
    int GetM() const;
    int GetN() const;
    int GetDataSize() const;
    int64_t GetMemorySize() const;
    
    void Clear();
    void Zero();
    void HideMessages();    
    void Reallocate(int m, int n, int kl = 0, int ku = 0);
 
    T* GetData() const;
           
    void AddInteraction(int i, int j, const T& val);
    void AddInteractionRow(int i, int n,
			   const IVect& num, const Vector<T>& val);

    void ClearRow(int i);
    
    const T operator()(int i, int j) const;

    Matrix<T, Prop, Storage, Allocator>& operator *=(const T& alpha);
    
    T& Get(int i, int j);
    const T& Get(int i, int j) const;

    T& Val(int i, int j);
    const T& Val(int i, int j) const;
    
    void Set(int, int, const T&);

    void SetIdentity();
    
    template<class T0>
    void Fill(const T0& x);
    
    void FillRand();
    void Copy(const Matrix<T, General, ArrayRowSparse>& A);
    
    void Factorize();
    void Factorize(IVect&);
    
    template<class T0>
    void Add_(const T0& alpha,
	      const Matrix<T, General, BandedCol, Allocator>& A);
    
    template<class StatusA, class T0, class T1>
    void MltAdd(const T0& alpha, const StatusA& trans,
                const Vector<T1>& x, Vector<T1>& y) const;
    
    template<class T1>
    void Solve(Vector<T1>& x) const;

    template<class T1>
    void Solve(const IVect&, Vector<T1>& x) const;
    
    void Write(string FileName) const;
    void Write(ostream& FileStream) const;
    void WriteText(string FileName) const;
    void WriteText(ostream& FileStream) const;
    
  };

  
  //! banded matrix stored by columns (Lapack format)
  template<class T, class Allocator>
  class Matrix<T, General, BandedCol, Allocator>
    : public Matrix_Band<T, General, BandedCol, Allocator>
  {
  };

  
  //! base class for arrow matrix (banded matrix + dense columns/rows)
  template <class T, class Prop, class Storage,
            class Allocator = SELDON_DEFAULT_ALLOCATOR<T> >
  class Matrix_Arrow : public Matrix_Band<T, Prop, Storage, Allocator>
  {
    // Attributes.
  protected:
    //! last rows
    Matrix<T, General, RowMajor, Allocator> last_rows_;
    //! last columns
    Matrix<T, General, ColMajor, Allocator> last_columns_;
    //! last block
    Matrix<T, General, ColMajor, Allocator> last_block_;
    
  public :
    Matrix_Arrow();
    
    int GetM() const;
    int GetN() const;
    int GetNbLastRow() const;
    int GetNbLastCol() const;
    int GetDataSize() const;
    int64_t GetMemorySize() const;
    
    void Clear();
    void Zero();
    void HideMessages();
    void Reallocate(int m, int n, int kl = 0, int ku = 0,
                    int nb_last_row = 0, int nb_last_col = 0);
    
    void AddInteraction(int i, int j, const T& val);
    void AddInteractionRow(int i, int n,
			   const IVect& num, const Vector<T>& val);

    void ClearRow(int i);
    
    const T operator()(int i, int j) const;
    
    Matrix<T, Prop, Storage, Allocator>& operator *=(const T& alpha);
    
    T& Get(int i, int j);
    const T& Get(int i, int j) const;

    T& Val(int i, int j);
    const T& Val(int i, int j) const;
    
    void Set(int, int, const T&);

    void SetIdentity();
    
    template<class T0>
    void Fill(const T0& x);
    
    void FillRand();
    
    void Factorize();
    
    template<class T0>
    void Add_(const T0& alpha,
	      const Matrix<T, General, ArrowCol, Allocator>& A);
    
    template<class StatusA, class T0, class T1>
    void MltAdd(const T0& alpha, const StatusA& trans,
                const Vector<T1>& x, Vector<T1>& y) const;
    
    template<class T1>
    void Solve(Vector<T1>& x);
    
    void Write(string FileName) const;
    void Write(ostream& FileStream) const;
    void WriteText(string FileName) const;
    void WriteText(ostream& FileStream) const;
    
  };

  
  //! arrow matrix stored by columns
  /*!
    The band part is stored in Lapack "fashion",
    whereas the last rows/columns are dense
    and stored by columns as ColMajor matrices
  */
  template<class T, class Allocator>
  class Matrix<T, General, ArrowCol, Allocator>
    : public Matrix_Arrow<T, General, ArrowCol, Allocator>
  {
  };

  
  // fonctions for the LU factorization and resolution
  
  template<class T, class Allocator>
  void GetLU(Matrix<T, General, BandedCol, Allocator>& A,
             Matrix<T, General, BandedCol, Allocator>& mat_lu,
	     bool keep_matrix = false);
  
  template<class T, class Allocator>
  void GetLU(Matrix<T, General, BandedCol, Allocator>& A);

#ifdef SELDON_WITH_LAPACK
  template<class Allocator>
  void GetLU(Matrix<double, General, BandedCol, Allocator>& A,
             Vector<int>& ipivot, LapackInfo& info = lapack_info);

  template<class Allocator>
  void SolveLU(const Matrix<double, General, BandedCol, Allocator>& A,
               const Vector<int>& ipivot, Vector<double>& b,
               LapackInfo& info = lapack_info);

  template<class Allocator>
  void SolveLU(const Matrix<double, General, BandedCol, Allocator>& A,
               const Vector<int>& ipivot, Vector<complex<double> >& b,
               LapackInfo& info = lapack_info);  

  template<class Allocator>
  void GetLU(Matrix<complex<double>, General, BandedCol, Allocator>& A,
             Vector<int>& ipivot, LapackInfo& info = lapack_info);

  template<class Allocator>
  void SolveLU(const Matrix<complex<double>,
	       General, BandedCol, Allocator>& A,
               const Vector<int>& ipivot, Vector<complex<double> >& b,
               LapackInfo& info = lapack_info);
#else
  template<class T, class Allocator>
  void GetLU(Matrix<T, General, BandedCol, Allocator>& A,
             Vector<int>& ipivot);

  template<class T, class Allocator>
  void SolveLU(const Matrix<T, General, BandedCol, Allocator>& A,
               const Vector<int>& ipivot, Vector<T>& b);
#endif


  template<class T, class Allocator>
  void Copy(const Matrix<T, General, ArrayRowSparse, Allocator>& A,
            Matrix<T, General, BandedCol, Allocator>& B);
  
  template<class T, class Allocator, class T1>
  void SolveLU(Matrix<T, General, BandedCol, Allocator>& A, Vector<T1>& x);

  template<class T0, class T1, class Allocator>
  void Add(const T0& alpha,
	   const Matrix<T1, General, BandedCol, Allocator>& A,
           Matrix<T1, General, BandedCol, Allocator>& B);

  template<class T0, class T1, class T, class T2, class Allocator>
  void MltAdd(const T0& alpha,
	      const Matrix<T, General, BandedCol, Allocator>& A,
              const Vector<T2>& x, const T1& beta, Vector<T2>& y);

  template<class T0, class T1, class T, class T2, class Allocator>
  void MltAdd(const T0& alpha, const class_SeldonNoTrans& trans,
              const Matrix<T, General, BandedCol, Allocator>& A,
              const Vector<T2>& x, const T1& beta, Vector<T2>& y);

  template<class T0, class T1, class T, class T2, class Allocator>
  void MltAdd(const T0& alpha, const class_SeldonTrans& trans,
              const Matrix<T, General, BandedCol, Allocator>& A,
              const Vector<T2>& x, const T1& beta, Vector<T2>& y);

  template<class T0, class T1, class T, class T2, class Allocator>
  void MltAdd(const T0& alpha, const class_SeldonConjTrans& trans,
              const Matrix<T, General, BandedCol, Allocator>& A,
              const Vector<T2>& x, const T1& beta, Vector<T2>& y);

  template<class T, class Allocator, class T1>
  void Mlt(const Matrix<T, General, BandedCol, Allocator>& A,
           const Vector<T1>& x, Vector<T1>& y);

  template<class T, class Allocator, class T1>
  void Mlt(const class_SeldonNoTrans& trans,
           const Matrix<T, General, BandedCol, Allocator>& A,
           const Vector<T1>& x, Vector<T1>& y);

  template<class T, class Allocator, class T1>
  void Mlt(const class_SeldonTrans& trans,
           const Matrix<T, General, BandedCol, Allocator>& A,
           const Vector<T1>& x, Vector<T1>& y);

  template<class T, class Allocator, class T1>
  void Mlt(const class_SeldonConjTrans& trans,
           const Matrix<T, General, BandedCol, Allocator>& A,
           const Vector<T1>& x, Vector<T1>& y);

  template<class T0, class T1, class Allocator>
  void Mlt(const T0& alpha,
           Matrix<T1, General, BandedCol, Allocator>& A);

  template<class T, class Allocator>
  ostream& operator<<(ostream& out,
		      const Matrix<T, General, BandedCol, Allocator>& A);

  template<class T, class Allocator>
  void GetLU(Matrix<T, General, ArrowCol, Allocator>& A,
             Matrix<T, General, ArrowCol, Allocator>& mat_lu,
	     bool keep_matrix = false);

  template<class T, class Allocator>
  void GetLU(Matrix<T, General, ArrowCol, Allocator>& A);
  
  template<class T, class Allocator, class T1>
  void SolveLU(Matrix<T, General, ArrowCol, Allocator>& A, Vector<T1>& x);

  template<class T0, class T1, class Allocator>
  void Add(const T0& alpha,
	   const Matrix<T1, General, ArrowCol, Allocator>& A,
           Matrix<T1, General, ArrowCol, Allocator>& B);

  template<class T0, class T1, class T, class T2, class Allocator>
  void MltAdd(const T0& alpha,
	      const Matrix<T, General, ArrowCol, Allocator>& A,
              const Vector<T2>& x, const T1& beta, Vector<T2>& y);

  template<class T0, class T1, class T, class T2, class Allocator>
  void MltAdd(const T0& alpha, const class_SeldonNoTrans& trans,
              const Matrix<T, General, ArrowCol, Allocator>& A,
              const Vector<T2>& x, const T1& beta, Vector<T2>& y);

  template<class T0, class T1, class T, class T2, class Allocator>
  void MltAdd(const T0& alpha, const class_SeldonTrans& trans,
              const Matrix<T, General, ArrowCol, Allocator>& A,
              const Vector<T2>& x, const T1& beta, Vector<T2>& y);

  template<class T0, class T1, class T, class T2, class Allocator>
  void MltAdd(const T0& alpha, const class_SeldonConjTrans& trans,
              const Matrix<T, General, ArrowCol, Allocator>& A,
              const Vector<T2>& x, const T1& beta, Vector<T2>& y);
  
  template<class T, class Allocator, class T1>
  void Mlt(const Matrix<T, General, ArrowCol, Allocator>& A,
           const Vector<T1>& x, Vector<T1>& y);

  template<class T, class Allocator, class T1>
  void Mlt(const class_SeldonNoTrans& trans,
           const Matrix<T, General, ArrowCol, Allocator>& A,
           const Vector<T1>& x, Vector<T1>& y);

  template<class T, class Allocator, class T1>
  void Mlt(const class_SeldonTrans& trans,
           const Matrix<T, General, ArrowCol, Allocator>& A,
           const Vector<T1>& x, Vector<T1>& y);

  template<class T, class Allocator, class T1>
  void Mlt(const class_SeldonConjTrans& trans,
           const Matrix<T, General, ArrowCol, Allocator>& A,
           const Vector<T1>& x, Vector<T1>& y);

  template<class T0, class T1, class Allocator>
  void Mlt(const T0& alpha,
           Matrix<T1, General, ArrowCol, Allocator>& A);

  template<class T, class Prop, class Allocator,
           class T1, class Allocator1, class T2, class Allocator2>
  void ScaleMatrix(Matrix<T, Prop, BandedCol, Allocator>& A,
                   const Vector<T1, VectFull, Allocator1>& Drow,
                   const Vector<T2, VectFull, Allocator2>& Dcol);
  
  template<class T, class Allocator>
  ostream& operator<<(ostream& out,
		      const Matrix<T, General, ArrowCol, Allocator>& A);
  
}

#define SELDON_FILE_BAND_MATRIX_HXX
#endif