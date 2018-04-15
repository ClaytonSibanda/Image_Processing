#ifndef IMAGEOPS
#define IMAGEOPS

class Image
{
private:
int width, height;
std::unique_ptr<unsigned char[]> data;

public:
  //constructors go here
  Image(int w,int h);

//copy constructor
Image(Image &img);
//copy assignment operator
Image& operator=(Image &);
//move constructor
Image(Image && img);
//move assignment operator
Image& operator =(Image &&);
~Image();
//getters and setters
int getWidth()const{
  return width;
}
void setWidth(int w){
  width=w;
}
int getHeight()const{
  return height;
}
void setHieght(int h){
  height=h;
}

//operators overloaded here
Image operator+(Image &);
//subtraction operator overloaded here
Image operator-(Image &);

};




#endif
