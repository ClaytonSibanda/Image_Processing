#include "imageops.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;
Image::Image(int w,int h,std::unique_ptr<unsigned char[]> d):width(w),height(h){
data=std::move(d);
}

//copy constructors
Image::Image(Image &img){
  if(this!=&img){
    //free the resource held by the incoming obj incase its holding on to something


    //then copy over
    width=img.width;
    height=img.height;
    //now deep copy of the array

    int length=width*height;
      std::copy(img.data.get(),img.data.get()+length,data.get());
  }

}

//copy assignment operator

Image & Image::operator=(Image & img){


  if(this!=&img){
    delete [] data.get();
      width=img.width;
      height=img.height;

      //now deep copy of the array
      int length=width*height;

    //allocate memory for data
      std::unique_ptr<unsigned char[]> data(new unsigned char[length]);

      std::copy(img.data.get(),img.data.get()+length,data.get());
  }
  return *this;
}

//move constructor

Image::Image(Image &&img):width(img.width),height(img.height){

//now move the array
data=move(img.data);

img.width=0;
img.height=0;
img.data.reset(nullptr);
  }



//move assignment operator

Image & Image::operator=(Image && img){


  if(this!=&img){
    delete [] data.get();

    width=img.width;
    height=img.height;
    int length=width*height;
    std::unique_ptr<unsigned char[]> data(new unsigned char[length]);

      data=move(img.data);

      img.width=0;
      img.height=0;
      img.data.reset(nullptr);
  }
  return *this;
}



//destructor
Image::~Image(){
  cout<<"destructor called"<<endl;
}

//Image Image::operator+(Image & img){
//    //add the two integers in here
//
//    Image returnImg(img.width,img.height);
//
//    int length= img.width * img.height;
//
//    for(int i=0;i<length;++i){
//       returnImg.data[i]=this->data[i]+img.data[i];
//    }
//
//    return  returnImg;
//
//}

Image SBNCLA002::load(std::string filename) {

    ifstream file("shrek_rectangular.pgm", ios::in | ios::binary);
    if (!file) {
        cout << "cannot open file" << endl;
    }
    string line;
    vector <string> strV;
    bool isAfter = false;
    int width;
    int length;
    int height;
    while (getline(file, line)) {
        if (line == "255") {
            isAfter = true;
            stringstream ss(strV[strV.size() - 1]);
            ss >> height;
            ss >> width;
            length = height * width;
        unique_ptr<unsigned char[]> buffer (new unsigned char[length]);

            //now read the binary data
// cout<<"The current position is "<<file.tellg()<<endl;
            file.read((char *) buffer.get(), length);
            //create image object here
            // for(int i=0;i<length;i++){
            //   std::cout << buffer[i] << '\n';
            //   if(i==50)
            //   break;
            // }
            Image returnImage(width,height,std::move(buffer));
            file.close();

            return returnImage;
        }

        if (!isAfter) {
            strV.push_back(line);
          //  cout << line << endl;
        }

    }

}

void Image::save(std::string filename){
  int length = this->width*this->height;
    ofstream file(filename,ios::out|ios::binary|ios::app);
    file<<"P5"<<endl;
    file<<this->height<<" "<<this->width<<endl;
    file<<"255"<<endl;
    //cout<<"file pos is "<<file.tellp()<<endl;

    file.write((char*)(this->data.get()),length);

    file.close();

  //  std::cout<<"The height is "<<this->height<<" "<<this->width<<endl;
}


void Image::copy( Image& rhs)
{
  Image::iterator    beg = this->begin();
    Image::iterator   end = this->end();
  Image::iterator    inStart = rhs.begin();
  Image::iterator inEnd  = rhs.end();

  while ( beg  !=  end) { *beg=*inStart; ++beg; ++inStart; }
}

Image Image::operator+(Image & img ) {
    int length =width*height;
    int length2= img.height*img.width;
   if(length==length2){
    Image::iterator beg1=img.begin();
    Image::iterator end1=img.end();
    Image::iterator beg2=this->begin();

    unique_ptr<unsigned char[]> buffer (new unsigned char[length]);

       Image sumImage(width,height,std::move(buffer));
       Image::iterator beg3=sumImage.begin();
  // cout<<"Test each item "<<*beg1<<" "<<*beg2<<endl;
    while(beg1!=end1){

    *beg3=(*beg1+*beg2);
        ++beg1;
        ++beg2;
        ++beg3;
      }


   return sumImage;}
}


Image Image::operator-(Image & img ) {
    int length =width*height;
    int length2= img.height*img.width;
   if(length==length2){
    Image::iterator beg1=img.begin();
    Image::iterator end1=img.end();
    Image::iterator beg2=this->begin();

    unique_ptr<unsigned char[]> buffer (new unsigned char[length]);

       Image sumImage(width,height,std::move(buffer));
       Image::iterator beg3=sumImage.begin();
  // cout<<"Test each item "<<*beg1<<" "<<*beg2<<endl;
    while(beg1!=end1){

    *beg3=(*beg1-*beg2);
        ++beg1;
        ++beg2;
        ++beg3;
      }


   return sumImage;}
}
