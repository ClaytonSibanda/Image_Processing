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

Image::Image(int w,int h,unsigned char *buffer):width(w),height(h){
data.reset(buffer);
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
      //std::copy(img.data.get(),img.data.get()+length,data.get());
      //cout<<" about to copy array"<<endl;

    for(int i=0;i<length;i++){
      img.data.get()[i]=data.get()[i];
    }

  }

}



//copy assignment operator

Image & Image::operator=(Image & img){


  if(this!=&img){
    cout<<"now copying"<<endl;

   data.reset(new unsigned char[img.height*img.width]);

      width=img.width;
      height=img.height;

      //now deep copy of the array
      int length=width*height;

    //allocate memory for data
    // data= std::unique_ptr<unsigned char[]>(new unsigned char[length]);

    std::copy(img.data.get(),img.data.get()+length,data.get());
    // for(int i=0;i<length;i++){
    //   data.get()[i]=img.data.get()[i];
    //   // cout<<<<endl;
    // }
      cout<<" finished copying"<<endl;
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


Image SBNCLA002::load(std::string filename) {

     ifstream file(filename, ios::in | ios::binary);
    Image i(0,0,std::move(nullptr));
    file>>i;
    //then read the image file from here
    return i;
}

void Image::save(std::string filename){

    ofstream file(filename,ios::out|ios::binary|ios::app);
    file<<(*this);


  //  std::cout<<"The height is "<<this->height<<" "<<this->width<<endl;
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
  // cout<<"Test each item "<<endl;
  //cout<<*beg1<<" "<<*beg2<<endl;
    while(beg1!=end1){
  //cout<<"out is "<<*beg1<<endl;
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

//implement invert operator
void Image::operator!(){

    Image::iterator beg=this->begin();
    Image::iterator end=this->end();
    while(beg!=end){
      *beg=255-*beg;
      ++beg;
    }

}

Image Image::operator/(Image & img){
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
if(*beg2==255){
  *beg3=*beg1;
}
else{
  *beg3=0;
}
      ++beg1;
      ++beg2;
      ++beg3;
    }


  return sumImage;}
}


void Image::operator*(int f){

  Image::iterator beg=this->begin();
  Image::iterator end=this->end();
  while(beg!=end){
    if(*beg>f)
      *beg=255;
    else
    *beg=0;
    ++beg;
  }
}

void operator<<(ofstream &file,Image &img){

  int length = img.width*img.height;
  file<<"P5"<<endl;
  file<<img.height<<" "<<img.width<<endl;
  file<<"255"<<endl;
  //cout<<"file pos is "<<file.tellp()<<endl;

  file.write((char*)(img.data.get()),length);

  file.close();
}

void operator>>(ifstream &file,Image &img){
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


          file.read((char *) buffer.get(), length);

          Image returnImage(width,height,std::move(buffer));
          file.close();
          img=returnImage;

      }

      if (!isAfter) {
          strV.push_back(line);
      }

  }
}
