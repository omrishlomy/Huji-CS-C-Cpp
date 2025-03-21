#include "User.h"
#include "RecommendationSystem.h"


void User::add_movie_to_user(const std::string &name, int year,
                       const std::vector<double> &features,
                       double rate){
  sp_movie new_movie = rs_->add_movie_to_rs(name, year, features);
  auto iter = ranks_.find(new_movie);
  if(iter != ranks_.end()){ //the movie exsists
    iter->second = rate;
  }
  ranks_[new_movie] = rate;


}


sp_movie User::get_rs_recommendation_by_content() const
{
   return rs_->recommend_by_content(*this);
}
sp_movie User::get_rs_recommendation_by_cf(int k) const{
  return rs_->recommend_by_cf(*this,k);
}
double User::get_rs_prediction_score_for_movie(const std::string& name, int
year,
                                         int k) const{
  sp_movie search_movie = rs_->get_movie(name,year);
  return rs_->predict_movie_score (*this,search_movie,k);
}

std::ostream &operator<<(std::ostream &os,User &user){
  os << "name: " << user.get_name() << std::endl;
   os << (*user.rs_);
   os << std::endl;
   return os;

}