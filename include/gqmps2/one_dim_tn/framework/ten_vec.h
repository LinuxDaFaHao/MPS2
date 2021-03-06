// SPDX-License-Identifier: LGPL-3.0-only

/*
* Author: Rongyang Sun <sun-rongyang@outlook.com>
* Creation Date: 2020-08-19 21:36
*
* Description: GraceQ/MPS2 project. A fix size tensor vector class.
*/

/**
@file ten_vec.h
@brief A fix size tensor vector class.
*/
#ifndef GQMPS2_ONE_DIM_TN_FRAMEWORK_TEN_VEC_H
#define GQMPS2_ONE_DIM_TN_FRAMEWORK_TEN_VEC_H


#include "gqmps2/one_dim_tn/framework/duovector.h"    // DuoVector
#include "gqten/gqten.h"    // GQTensor, bfread, bfwrite

#include <string>     // string
#include <fstream>    // ifstream


namespace gqmps2 {
using namespace gqten;


/**
A fix size tensor vector.

@tparam TenT Type of the element tensor.
*/
template <typename TenT>
class TenVec : public DuoVector<TenT> {
public:
  /**
  Create a TenVec using its size.

  @param size The size of the vector.
  */
  TenVec(const size_t size) : DuoVector<TenT>(size) {}

  /**
  Load element tensor from a file.

  @param idx The index of the element.
  @param file The file which contains the tensor to be loaded.
  */
  void LoadTen(const size_t idx, const std::string &file) {
    this->alloc(idx);
    std::ifstream ifs(file, std::ifstream::binary);
    ifs >> (*this)[idx];
    ifs.close();
  }

  /**
  Dump element tensor to a file.

  @param idx The index of the element.
  @param file The element tensor will be dumped to this file.
  */
  void DumpTen(const size_t idx, const std::string &file) const {
    std::ofstream ofs(file, std::ofstream::binary);
    ofs << (*this)[idx];
    ofs.close();
  }

  /**
  Dump element tensor to a file.

  @param idx The index of the element.
  @param file The element tensor will be dumped to this file.
  @param release_mem Whether release memory after dump.
  */
  void DumpTen(
      const size_t idx,
      const std::string &file,
      const bool release_mem = false
  ) {
    std::ofstream ofs(file, std::ofstream::binary);
    ofs << (*this)[idx];
    ofs.close();
    if (release_mem) { this->dealloc(idx); }
  }
};
} /* gqmps2 */
#endif /* ifndef GQMPS2_ONE_DIM_TN_FRAMEWORK_TEN_VEC_H */
