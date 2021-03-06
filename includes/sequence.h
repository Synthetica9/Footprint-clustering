//The MIT License (MIT)
//
//Copyright (c) 2016 Sal Wolffs
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include <string>
#include <tuple>
#include <cstddef>
#include <iterator>

#include "nucleotide.h"
namespace footprint_analysis {

/// Nucleotide sequence class. (UNIMPLEMENTED)

/// Alternative for std::vector<Nucleotide>. Provides utilities like complement
/// and similarity scoring.
/// \todo This needs to be implemented as described above.
class Sequence
{
private:
    using Location = std::pair<size_t,size_t>;

    using vNuc = std::vector<Nucleotide>;
    vNuc seq;
    //TODO: Implement features promised in documentation
public:
    using iterator = typename vNuc::iterator;
    using const_iterator = typename vNuc::const_iterator;

    Sequence();
    Sequence(std::vector<Nucleotide> seq);
    Sequence(std::vector<Nucleotide> const & chrseq, Location loc);
    Sequence(std::vector<Nucleotide> const & chrseq, size_t begin, size_t end);

    std::vector<Nucleotide> const & getseq() const;
    operator std::vector<Nucleotide> () const;

    Nucleotide const & operator[](size_t const i) const;
    Nucleotide & operator[](size_t const i);

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    //overwrite this sequence by its join in the lattice of
    //IUPAC ambiguous sequences.
    Sequence & absorb_join(Sequence const & other);

    //return the reversed point-wise complement of our sequence.
    Sequence complement() const;

    size_t size() const;
};

template <typename Obj,typename It>
Obj fold_join(It begin,It end);

//Define complementary sequences as equivalent, and send the argument to
//the representative of its equivalence class: the lexicographically lowest
//member of that class.
Sequence reprSeqFromSeq(Sequence const & seq);

std::vector<Sequence> joinsFromIndexClusters(
    std::vector<std::vector<size_t>> const & clusters,
    std::vector<Sequence> const & lookup);
bool operator==(Sequence const &,Sequence const &);
bool operator<(Sequence const &,Sequence const &);
bool operator<=(Sequence const &,Sequence const &);
bool operator>(Sequence const &,Sequence const &);
bool operator>=(Sequence const &,Sequence const &);
} // namespace footprint_analysis
#endif // SEQUENCE_H
