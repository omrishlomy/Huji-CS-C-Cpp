
#include "Movie.h"
#define HASH_START 17
#define RES_MULT 31
#include <string>

/**
 * hash function used for a unordered_map (implemented for you)
 * @param movie shared pointer to movie
 * @return an integer for the hash map
 */
std::size_t sp_movie_hash(const sp_movie& movie){
    std::size_t res = HASH_START;
    res = res * RES_MULT + std::hash<std::string>()(movie->get_name());
    res = res * RES_MULT + std::hash<int>()(movie->get_year());
    return res;
}

std::ostream& operator<<(std::ostream &os,const Movie &movie){
  os<< movie.get_name() << "(" << movie.get_year() << ")" << std::endl;
  return os;
}
bool Movie::operator<(const Movie &rhs)const{
  if(year_==rhs.get_year() && name_ == rhs.get_name()){return false;}
  if(year_ != rhs.get_year()){
    return year_ < rhs.get_year();}
  return name_ < rhs.get_name();
}
/**
 * equal function used for an unordered_map (implemented for you)
 * @param m1
 * @param m2
 * @return true if the year and name are equal else false
 */
bool sp_movie_equal(const sp_movie& m1,const sp_movie& m2){
    return !(*m1 < *m2) && !(*m2 < *m1);
}
