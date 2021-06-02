//
//  index.hpp
//  cpp_course
//
//  Created by Kristoffer Sahlin on 4/21/21.
//

#ifndef index_hpp
#define index_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <deque>
#include <tuple>
#include "robin_hood.h"


uint64_t hash(std::string kmer);
static inline uint64_t hash64(uint64_t key, uint64_t mask);
//typedef robin_hood::unordered_map< uint64_t , std::vector< std::tuple<unsigned int, unsigned int>> > seq_index1;
//typedef robin_hood::unordered_map< uint64_t , std::vector< std::tuple<unsigned int, unsigned int, unsigned int>> > seq_index2;
//typedef robin_hood::unordered_map< uint64_t , std::vector<unsigned int> > seq_index;
//typedef robin_hood::unordered_map< uint64_t , std::vector< std::tuple<unsigned int, unsigned int, unsigned int, unsigned int>> > seq_index3;

typedef std::vector< std::tuple<uint64_t, unsigned int, unsigned int, unsigned int>> mers_vector;
typedef std::vector< std::tuple<unsigned int, unsigned int, unsigned int>> mers_vector_reduced;
typedef robin_hood::unordered_map< uint64_t, std::tuple<unsigned int, unsigned int >> kmer_lookup;

//static inline void make_string_to_hashvalues(std::string &seq, std::vector<uint64_t> &string_hashes, int k, uint64_t kmask);
static inline void get_next_strobe(std::vector<uint64_t> &string_hashes, uint64_t strobe_hashval, unsigned int &strobe_pos_next, uint64_t &strobe_hashval_next,  unsigned int w_start, unsigned int w_end, uint64_t q);


mers_vector seq_to_kmers(int k, std::string &seq, unsigned int ref_index);
mers_vector seq_to_randstrobes2(int n, int k, int w_min, int w_max, std::string &seq, unsigned int ref_index, int w);
mers_vector seq_to_randstrobes3(int n, int k, int w_min, int w_max, std::string &seq, unsigned int ref_index, int w);

typedef robin_hood::unordered_map< unsigned int, std::vector< std::tuple<uint64_t, unsigned int, unsigned int, unsigned int>>> pos_index;
mers_vector construct_flat_vector(pos_index &tmp_index);
unsigned int index_vector(mers_vector  &mers_vector, kmer_lookup &mers_index, float f);
mers_vector_reduced remove_kmer_hash_from_flat_vector(mers_vector &flat_vector);
void filter_repetitive_strobemers(mers_vector &flat_vector, kmer_lookup &mers_index, mers_vector &flat_vector_reduced, kmer_lookup &mers_index_reduced, unsigned int filter_cutoff);

struct hit {
    unsigned int ref_id;
    unsigned int query_s;
    unsigned int query_e;
    unsigned int ref_s;
    unsigned int ref_e;
    unsigned int hit_count;
};

struct nam {
    unsigned int ref_id;
    unsigned int query_s;
    unsigned int query_e;
    unsigned int query_last_hit_pos;
    unsigned int ref_s;
    unsigned int ref_e;
    unsigned int ref_last_hit_pos;
    unsigned int n_hits = 0;
    unsigned int previous_query_start;
    unsigned int previous_ref_start;
    unsigned int is_rc = false;
    float score;
};

struct aln_info {
    unsigned int ed;
    unsigned int ref_offset;
    std::string cigar;
};

struct final_alignment {
    unsigned int ref_start;
    unsigned int ed;
    std::string cigar;
    bool is_rc;
    unsigned int ref_id;
};

#endif /* index_hpp */



