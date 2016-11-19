//
// Created by Zal on 11/19/16.
//

#include <assert.h>
#include <utility>
#include "BinaryMatrix.h"

#define intPair std::pair<int, int>

void BinaryMatrix::BinaryMatrix(int w, int h) {
    this->width = w;
    this->height = h;
    this->baseSize = sizeof(char);

    int n = w*h;
    this->dataLength = (n % baseSize == 0)? n/baseSize : n/baseSize +1;
    this->data = new char[dataLength];
}

void BinaryMatrix::~BinaryMatrix() {
    delete[] data;
}

void BinaryMatrix::T() {
    this->transposed = !this->transposed;
}

// Binary matrix multiplciation is the Haddamard product of the matrices
// It is different from the regular matrix mutltiplication
BinaryMatrix BinaryMatrix::binMultiply(const BinaryMatrix& other) {
    BinaryMatrix res(this->width, this->height);
    for(int i = 0; i < this->dataLength; ++i) {
        res.data[i] = !(this->data[i] ^ other.data[i]);
    }
    return res;
}

std::pair<int, int> elem_accessor(int i, int rows, int cols, bool transposed) {
    if (transposed) {
        return std::make_pair(i % rows, i / rows);
    } else {
        return std::make_pair(i / cols, i % cols);
    }
}

BinaryMatrix BinaryMatrix::tBinMultiply(const BinaryMatrix& other) {
    int w = this->width;
    int h = this->height;
    if (this->transposed) {
        w = other.width;
        h = other.height;
    }
    int this_n = this->dataLength;
    int other_n = other.dataLength;
    BinaryMatrix res(w, h);
    for (int bit_id = 0; bit_id < (w * h); ++bit_id) {
        std::pair<int, int> this_rc = elem_accessor(bit_id, this_n, 8, this->transposed);
        std::pair<int, int> other_rc = elem_accessor(bit_id, other_n, 8, other.transposed);
        res.data[bit_id] = this->data[this_rc.first][this_rc.second]
                        * other.data[other_rc.first][other_rc.second];
    }
    return res;
}

//The operations are done row-wise
double* BinaryMatrix::doubleMultiply(const double* other) {

    double* res = new double[this->height][this->width];
    for(int row=0; row < this->height; ++row) {
        for(int col=0; col < this->width; ++col) {

        }
    }

    return res;
}

// Remember it's 0-based
char BinaryMatrix::getBitPos(int row, int col) {
    int i = (row+1) * (col+1);
    intPair pos = elem_accessor(i, this->dataLength, this->baseSize, this->transposed);
    return (this->data[pos.first]>>pos.second & 1);
}

BinaryMatrix BinaryMatrix::operator*(const BinaryMatrix& other ) {
    if(this->transposed != other.transposed) {
        assert(this->width == other.height);
        assert(this->height == other.width);
        return this->tBinMultiply(other);
    }
    else {
        assert(this->width == other.width);
        assert(this->height == other.height);
        return this->binMultiply(other);
    }
}
