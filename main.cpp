//
// Created by clayza on 2018/04/19.
//

#include "imageops.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc,char* argv[]){

    //main -a l1 l2 output
    //main -i l1 output
    string action =argv[1];
    string i1;
    string i2;
    string output=argv[argc-1];
    if(argc ==5){
        i1=argv[2];
        i2=argv[3];

    }
    if(argc==4){
        i1=argv[2];
    }

    if(action=="-a"){
    Image img1= SBNCLA002::load(i1);
    Image img2=SBNCLA002::load(i2);
    Image imgSum =img1+img2;
    imgSum.save(output);
    }
    if(action=="-s"){
      Image img1= SBNCLA002::load(i1);
      Image img2=SBNCLA002::load(i2);
      Image imgSum =img1-img2;
      imgSum.save(output);
    }


    return 0;
}
