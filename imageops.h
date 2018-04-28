#ifndef IMAGEOPS
#define IMAGEOPS

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
class Image
{
private:
int width, height;
std::unique_ptr<unsigned char[]> data;

public:
  //constructors go here
  Image(int ,int ,std::unique_ptr<unsigned char[]>);

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
std::unique_ptr<unsigned char[]>& getData(){
  return data;
}
void setWidth(int w){
  width=w;
}

int getHeight()const{
  return height;
}
void setHeight(int h){
  height=h;
}

//operators overloaded here
Image operator+(Image &);
//subtraction operator overloaded here
Image operator-(Image &);

//invertor operator overloaded here
void operator!(void);

//overload / operator for masking images
Image operator/(Image &);

//Threshold operator
void operator*(int );

//I/O operators overloading here

friend void operator>>(std::ifstream &,Image &);
friend void operator<<(std::ofstream &,Image &);

//iterator starts here

    class iterator
    {
    private:
        unsigned char *ptr;
// construct only via Image class (begin/end)
        iterator(unsigned char *p) : ptr(p) {}
    public:
//copy construct is public
        iterator( const iterator & rhs) : ptr(rhs.ptr) {}
// define overloaded ops: *, ++, --, =
        iterator & operator=(const iterator & rhs)
        {
          *this =rhs;

          return *this;
        }

        iterator &operator++(){
          this->ptr+=1;
          return *this;

        }

        iterator &operator--(){
          this->ptr-=1;
          return *this;

        }

        bool operator!=(const iterator & it){
         return this->ptr!=it.ptr;
        }

        unsigned char& operator*(){
            return *(ptr);
        }

// other methods for iterator
    friend class Image;

    };
    void copy(Image&);
    iterator begin(void) const { return iterator(data.get());}
    iterator end(void) const{return iterator(begin().ptr+(height)*(width));}

    void save(std::string);
    friend Image load(std::string);
};

namespace SBNCLA002{
    Image load(std::string);

}


#endif
