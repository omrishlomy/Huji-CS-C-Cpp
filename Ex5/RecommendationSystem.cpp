#include "RecommendationSystem.h"
#include <cmath>
#include <set>
#include "algorithm"
#include <queue>
#define MIN_VAL (-100000.0)



sp_movie RecommendationSystem::string_to_ptr(std::string name){
   for(const auto &i: features_) {
     if (i.first->get_name() == name) {
       return i.first;
       }
     }
   return nullptr;
   }

 RecommendationSystem::RecommendationSystem() {}

 #ifdef GET_MOVIEX
 sp_movie RecommendationSystem::get_movieX(int index) const{
   int j = 0;
   for(auto i: movies) {
     if (j == index) {
       return i.first;
       }
     j++;
     }
   return nullptr;
}
 #endif

 sp_movie RecommendationSystem::get_movie(const std::string &name, int year)
 const{
 for(const auto &i: features_) {
 if (i.first->get_name() == name && i.first->get_year() == year) {
 return i.first;
 }
 }
 return nullptr;
 }

 sp_movie RecommendationSystem::add_movie_to_rs(const std::string& name,int
 year,
 const std::vector<double>& features){
 Movie m1 = Movie(name, year);
sp_movie sp = std::make_shared<Movie>(m1);
 features_[sp] = features;
 return sp;
 }
 typedef std::unordered_map<std::string, double> avrg_map;
 /**
 * a function that calculates the movie with highest score based on movie
 * features
* @param ranks user ranking to use for algorithm
 * @return shared pointer to movie in system
 */

 sp_movie RecommendationSystem::recommend_by_content(const User& user){
   double sum = 0, num_movies = 0;
   avrg_map average_map;
   rank_map ranks = user.get_ranks();
   for(const auto &i: features_){
     sp_movie movie = string_to_ptr(i.first->get_name());
     if (ranks[movie] != 0.0){
       num_movies++;
       sum += ranks[movie];
       std::pair<std::string, double> map_pair (i.first->get_name(),
       ranks[movie]);
       average_map.insert(map_pair); }}
   for(auto &i: average_map){
     i.second -= (sum/num_movies); }
   size_t feat_size = features_.begin()->second.size();
   std::vector<double> pref_vec;
   pref_vec.reserve (feat_size);
   for (size_t i=0; i< feat_size; i++){
    pref_vec.push_back(0); }
   for(auto &i: features_){
     std::string movie_name = i.first->get_name();
     std::unordered_map<std::string,double>::const_iterator got =
     average_map.find(movie_name);
     if ( got == average_map.end()){
       continue; }
     sp_movie movie = string_to_ptr(movie_name);
     for (size_t m=0; m< feat_size; m++) {
       pref_vec[m] += (features_[movie][m] * average_map[movie_name]); }}
   double max_similarity = MIN_VAL, ans = 0.0;
   sp_movie ret_movie = nullptr;
   for(auto &a: features_){
     ans = 0.0;
    std::string movie_name = a.first->get_name();
     sp_movie movie = string_to_ptr(movie_name);
     std::unordered_map<std::string,double>::const_iterator got =
     average_map.find(movie_name);
     if ( got == average_map.end()){
       double abs_val_p = 0.0, abs_val_f = 0.0;
       for (size_t i=0; i< feat_size; i++){
         ans += pref_vec[i] * features_[movie][i];
         abs_val_p += pow(pref_vec[i],2);
         abs_val_f += pow(features_[movie][i],2); }
       abs_val_f = sqrt(abs_val_f);
       abs_val_p = sqrt(abs_val_p);
      ans = ans/(abs_val_f * abs_val_p);
       if (max_similarity < ans){
         max_similarity = ans;
         ret_movie = movie; }}}
   return ret_movie;}

 /**
 * a function that calculates the movie with highest predicted score based on
 * ranking of other movies
 * @param ranks user ranking to use for algorithm
 * @param k
 * @return shared pointer to movie in system */
 sp_movie RecommendationSystem::recommend_by_cf(const User& user, int k){
   rank_map ranks = user.get_ranks();
   avrg_map unseen_map;
   for(auto &i: features_){
     std::string movie_name = i.first->get_name();
     sp_movie movie = get_movie(movie_name, i.first->get_year());
     std::pair<std::string, double> map_pair (movie_name, 0.0);
     if (ranks[movie] == 0.0) {
       unseen_map.insert(map_pair);
       }

     }
   double max = MIN_VAL;
   std::string ret_movie;
   for(auto &i: unseen_map) {
     double result = predict_movie_score(user, string_to_ptr(i.first),k);
     if (result > max) {
       max = result;
       ret_movie = i.first;
       }
     }
   return string_to_ptr(ret_movie);
   }


// ** Predict a user rating for a movie given argument using item cf procedure
 //* with k most similar movies.
 //* @param user_rankings: ranking to use
 //* @param movie: movie to predict
 //* @param k:
 //* @return score based on algorithm as described in pdf
 //*/
 double RecommendationSystem::predict_movie_score(const User &user,
 const sp_movie &movie,int k){
 avrg_map seen_map;
 rank_map ranks = user.get_ranks();
 for(auto &i: features_){sp_movie seen_movie = string_to_ptr(i
 .first->get_name());
std::pair<std::string, double> map_pair (i.first->get_name(),
                                              ranks[movie]);
 if (ranks[seen_movie] > 0.0) {
 seen_map.insert(map_pair);
 }
 }
 double abs_val_s = 0.0, abs_val_u = 0.0, ans=0.0;
 size_t feat_size = features_.begin()->second.size();
 avrg_map predi_map;
 for(auto &j: seen_map) {
 sp_movie seen_movie = string_to_ptr(j.first);
 ans = 0.0, abs_val_s = 0.0, abs_val_u = 0.0;
 for (size_t r=0; r< feat_size; r++){
 ans += (features_[movie][r] * features_[seen_movie][r]);
 abs_val_s += pow(features_[seen_movie][r],2);
 abs_val_u += pow(features_[movie][r],2);
 }
 abs_val_u = sqrt(abs_val_u);
 abs_val_s = sqrt(abs_val_s);
 ans /= (abs_val_u * abs_val_s);
 std::pair<std::string, double> map_pair (j.first, ans);
 predi_map.insert(map_pair);
 }
 double max = MIN_VAL;
 avrg_map k_max_map;
 std::string biggest_movie;
 for (int ik=0; ik < k; ik++){
 for(auto &a: predi_map){
 if(a.second > max){
 max = a.second;
 biggest_movie = a.first;
 }
 }
 std::pair<std::string, double> map_pair (biggest_movie,max);
 k_max_map.insert(map_pair);
 predi_map.erase(biggest_movie);
 max = MIN_VAL;
 }
 double result = 0.0, denomi =0.0 ;
 for(auto &a: k_max_map){

 result += (a.second * ranks[string_to_ptr(a.first)]);
 denomi += a.second;
 }
 return result/denomi;
 }

 bool RecommendationSystem::sort_func(Movie &m1, Movie &m2){
   return m1 < m2;
   }

 std::ostream& operator<< (std::ostream& stream, RecommendationSystem &rs){
   std::vector<Movie> sorted_movies;
   sorted_movies.reserve (rs.features_.size());
   for(const auto &movie: rs.features_){
     sorted_movies.push_back(*(movie.first));
     }
  std::sort(sorted_movies.begin(),sorted_movies.end(),
                 RecommendationSystem::sort_func);
   for(auto &i: sorted_movies){
     stream << i;
     }
   return stream;
   }