/* Copyright (C) 2011 Xavier Pujol.

   This file is part of fplll. fplll is free software: you
   can redistribute it and/or modify it under the terms of the GNU Lesser
   General Public License as published by the Free Software Foundation,
   either version 2.1 of the License, or (at your option) any later version.

   fplll is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with fplll. If not, see <http://www.gnu.org/licenses/>. */

#ifndef FPLLL_BKZ_H
#define FPLLL_BKZ_H

#include "lll.h"

FPLLL_BEGIN_NAMESPACE

template<class FT>
class BKZAutoAbort {
public:
  BKZAutoAbort(MatGSO<Integer, FT>& m, int numRows, int startRow = 0) : m(m),
    oldSlope(numeric_limits<double>::max()), noDec(-1), numRows(numRows), startRow(startRow) {}
  bool testAbort();

private:
  MatGSO<Integer, FT>& m;
  vector<double> x;
  double oldSlope;
  int noDec;
  int numRows;
  int startRow;
};

/* The matrix must be LLL-reduced */
template<class FT>
class BKZReduction {
public:
  BKZReduction(MatGSO<Integer, FT>& m, LLLReduction<Integer, FT>& lllObj,
               const BKZParam& param);
  ~BKZReduction();

  /**
     Run enumeration to find a new shortest vecto in the sublattice B[kappa,kappa+blockSize]

     @param kappa Start row
     @param blockSize Block size to use, this may be < param.blockSize
     @param param Parameters to use for this enumeration (blockSize is ignored)
     @param clean Did we change anything?
  */
  
  bool svpReduction(int kappa, int blockSize, const BKZParam &param, bool& clean);
  bool bkzLoop(const int loop, int& kappaMax, const BKZParam &param, int minRow, int maxRow, bool& clean);
  bool bkz();
  void dumpGSO(const std::string filename, const std::string prefix, bool append = true);

  int status;

private:
  void printParams(const BKZParam &param, ostream &out);
  bool setStatus(int newStatus);

  const BKZParam& param;
  int numRows;
  MatGSO<Integer, FT>& m;
  LLLReduction<Integer, FT>& lllObj;
  FastEvaluator<FT> evaluator;
  FT delta;

  // Temporary data
  const vector<FT> emptyTarget, emptySubTree;
  FT maxDist, deltaMaxDist;
  double cputimeStart;
};

FPLLL_END_NAMESPACE

#endif
