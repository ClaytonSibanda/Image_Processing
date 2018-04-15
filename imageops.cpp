Image::Image(int w,int h):width(w),height(h){

}

//copy constructors
Image::Image(Image &img){
  if(this!=&img){
    //free the resource held by the incoming obj incase its holding on to something

    delete [] data.get();

    //then coppy over
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
      std::copy(img.data.get(),img.data.get()+length,data.get());
  }
  return *this;
}

//mve constructor

Image::Image(Image &&img):width(img.width),height(img.height){

//now move the array
data=img.data;

img.width=0;
img.height=0;
img.data.reset(nullptr);
  }

}

//move assignment operator

Image & Image::operator=(Image && img){


  if(this!=&img){
    delete [] data.get();

    width=img.width;
    height=img.height;
    data=img.data;

      img.width=0;
      img.height=0;
      img.data.reset(nullptr);
  }
  return *this;
}



//destructor
~Image(){
  cout<<"destructor called"<<endl;
}
