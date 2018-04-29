#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "imageops.h"

TEST_CASE("MOVE AND COPY SEMANTICS","[MOVECOPYSEMANTICS]"){
  unsigned char* buffer = new unsigned char[6]{255,2,3,12,2,4};

  unsigned char* buffer1 = new unsigned char[6]{255,2,3,12,2,4};
  Image i1(3,3,nullptr);

  // std::cout<<"jus before"<<std::endl;
    SECTION("COPY ASSIGNMENT OPERATOR"){
Image i2(3,3,nullptr);
        i1.getData().reset(buffer1);

  i2=i1;
   std::cout<<i1.getWidth()<<std::endl;
    REQUIRE(i1.getWidth()==i2.getWidth());
    REQUIRE(i1.getHeight()==i2.getHeight());
    REQUIRE(i1.getData()[2]==i2.getData()[2]);
    REQUIRE(i1.getData()[0]!=i2.getData()[2]);
    REQUIRE(i1.getData()[1]==i2.getData()[1]);
    REQUIRE(i1.getData()[4]==i2.getData()[4]);

  }
  SECTION("MOVE ASSIGNMENT OPERATOR"){
    Image i2(3,3,nullptr);
    i1.getData().reset(buffer1);
    i2=std::move(i1);
      REQUIRE(i1.getWidth()!=i2.getWidth());
      REQUIRE(i1.getHeight()!=i2.getHeight());
      // REQUIRE(i1!=nullptr);
  }

}


TEST_CASE("ITERATOR AND OPERATORS","[ITERATORS]")
{
  unsigned char* buffer = new unsigned char[6]{255,2,3,12,2,4};
  unsigned char* buffer1 = new unsigned char[6]{255,2,3,12,2,4};

  Image i1(3,3,nullptr);
  Image inv(3,3,nullptr);
  i1.getData().reset(buffer);
inv.getData().reset(buffer1);

//
SECTION("* OPERATOR"){
  Image::iterator beg=i1.begin();
  Image::iterator end=i1.end();

  REQUIRE(*(beg)==255);
  REQUIRE(beg!=end);

}
SECTION("+ OPERATOR"){
  Image::iterator beg=i1.begin();
  Image::iterator end=i1.end();
  REQUIRE(*(beg)==255);
  ++beg;
  REQUIRE(*(beg)==2);
  ++beg;
  REQUIRE(*(beg)==3);
  ++beg;
  REQUIRE(*(beg)==12);
}
SECTION("- OPERATOR"){
  Image::iterator beg=inv.begin();
  Image::iterator end=inv.end();
  REQUIRE(*(beg)==255);
  ++beg;
  std::cout<<*(end)<<std::endl;
  --beg;
  REQUIRE(*(beg)==255);
  ++beg;
  ++beg;
  --beg;
  REQUIRE(*(beg)==2);
  ++beg;
  ++beg;
  ++beg;
  --beg;
  REQUIRE(*(beg)==12);
}


}




TEST_CASE("ADDITION AND SUBRACTION","[ADDITION SUBRACTION]")
{
  unsigned char* buffer = new unsigned char[5]{255,2,3,12,2};
  unsigned char* buffer1= new unsigned char[5]{3,5,255,1,2};
Image i1(5,5,nullptr);
Image i2(5,5,nullptr);
i1.getData().reset(buffer);
i2.getData().reset(buffer1);

SECTION("ADDITION"){
  Image iSum = i1+i2;
// std::cout<<"This is "<<(int)i1.getData()[3]<<std::endl;
//
REQUIRE(iSum.getData()[0]==255);
REQUIRE(iSum.getData()[3]==13);
REQUIRE(iSum.getData()[4]==4);
REQUIRE(iSum.getData()[2]==255);
  }

SECTION("SUBTRACTION"){
Image iDif= i1-i2;
REQUIRE(iDif.getData()[4]==0);
REQUIRE(iDif.getData()[3]==11);
REQUIRE(iDif.getData()[1]==0);
REQUIRE(iDif.getData()[2]==0);
}

}








TEST_CASE("THRESHOLDING,INVERTING AND MASKING","[THRESHOLDING INVERTING MASKING]")
{
  unsigned char* buffer = new unsigned char[6]{255,0,3,12,2,4};
  unsigned char* buffer1= new unsigned char[6]{3,5,255,1,2,7};
Image i1(3,3,nullptr);
Image i2(3,3,nullptr);
i1.getData().reset(buffer);
i2.getData().reset(buffer1);

SECTION("INVERTING"){
  !i1;

REQUIRE(i1.getData()[0]==0);
REQUIRE(i1.getData()[1]==255);
REQUIRE(i1.getData()[3]==243);
REQUIRE(i1.getData()[4]==253);
  }

  SECTION("THRESHOLDING"){
    i1*5;
  // std::cout<<"This is "<<(int)i1.getData()[3]<<std::endl;
  //
  REQUIRE(i1.getData()[0]==255);
  REQUIRE(i1.getData()[1]==0);
  REQUIRE(i1.getData()[3]==255);
  REQUIRE(i1.getData()[4]==0);
    }

SECTION("MASKING"){
Image iMask= i1/i2;
REQUIRE(iMask.getData()[0]==3);
REQUIRE(iMask.getData()[2]==0);
REQUIRE(iMask.getData()[1]==0);
REQUIRE(iMask.getData()[2]==0);
}

}
