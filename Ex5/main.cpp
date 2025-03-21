#include "usersLoader.h"
#include "User.h"
#include "RecommendationSystemLoader.cpp"





int main(){
  std::vector<User> users = UsersLoader::create_users(  "UsersLoader_input"
                                                       ".txt", RecommendationSystemLoader::create_rs_from_movies
      ("RecommendationSystemLoader_input.txt") );


}