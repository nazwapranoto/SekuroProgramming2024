#include <iostream>
using namespace std;
class Shape
{
protected:
    float area;
    float keliling;
public:
virtual float calculateArea() {
    return 0; 
}
virtual float calculateKeliling() { return 0; 
}
};
class Rectangle : public 
Shape{
    private :
    float width;
    float length;

    public:
    Rectangle(float w, float l)
    {
        this->width = w;
        this->length = l;

    }
    float calculateArea() 
    {
        area = width * length;
        return area;
    }

    float calculateKeliling()
    {
        keliling = 2*(width+length);
        return keliling;
    }


};

int main()
{
Rectangle rect (5.0, 4.0);
Shape* shape1 = &rect;
float area = shape1 -> calculateArea();
float keliling = shape1->calculateKeliling();

cout<<"Area = "<<area<<endl;
cout<<"keliling = "<<keliling<<endl;

return 0;

}