#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "imageops.h"

// TEST_CASE("MOVE AND COPY SEMANTICS","[MOVECOPYSEMANTICS]"){
// unsigned char buffer[5] = {1,2,3,12,2};
// unsigned char buffer1[5]={1,2,3,12,2};
//   Image i1(5,5,nullptr);
//
//   // Image i2(5,5,buffer1);
//   std::cout<<"jus before"<<std::endl;
//     SECTION("COPY ASSIGNMENT OPERATOR"){
//
//         i1.getData().reset(buffer);
//
//   //  i1=i2;
//     // REQUIRE(i1.getWidth()==i1.getWidth());
//     // REQUIRE(i1.getHeight()==i1.getHeight());
//
//   }
//   std::cout<<"gets here"<<std::endl;
//   // SECTION("")
//
// }
TEST_CASE("ADDITION AND SUBRACTION","[ADDITION SUBRACTION]")
{
  unsigned char* buffer = new unsigned char[5]{1,2,3,12,2};
  unsigned char* buffer1= new unsigned char[5]{3,5,3,1,2};
Image i1(5,5,nullptr);
Image i2(5,5,nullptr);
i1.getData().reset(buffer);
i2.getData().reset(buffer1);

SECTION("ADDITION"){
  Image iSum = i1+i2;
// std::cout<<"This is "<<(int)i1.getData()[3]<<std::endl;
//
REQUIRE(iSum.getData()[0]==4);
REQUIRE(iSum.getData()[2]==6);
REQUIRE(iSum.getData()[4]==4);
  }
//
//
}
