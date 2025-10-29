#include <iostream>
#include <cmath>
//Physical constants?

double const S = 8.854e-12;//Permitivvity of free space


class Field{
    private: 
        double x;
        double y;
        double z;
    
    public: 
        //Default constructor
        Field(double x_val = 0.0, double y_val = 0.0, double z_val = 0.0) : x(x_val), y(y_val), z(z_val)//colon same as x = x_val
        //learned from lesson6 slides
        {
            std::cout << "Default Constructor called" << std::endl;
        }

        double magnitude(){
            auto mag = sqrt(x*x + y*y + z*z);
            return mag;
        }

        void print_magnitude(){
            std::cout << "Magnitude is: " << magnitude() << std::endl;
        }

        void print_components(){
            std::cout << "components: (" << x <<", " << y << ", " << z <<") " <<std::endl;
        }
        
        ~Field(){}
        
};

//Electric and Magnetic Field are under the base class of Field.
class Electric_field : public Field{
    //Constructor using base class Field
    private: 
        double r; //distance
        double Q; //charge in coulumbs
        double E_value; //what we're solving for...

    public: 
        Electric_field(double x_val, double y_val, double z_val) : Field(x_val, y_val, z_val) {} 

        //solving for E
        double electric_field_at_distance_r(){
            return 0;
        }
        void display(){
            std::cout << "Electric field magnitude: " << magnitude() << std::endl;
        }

};

class Magnetic_field : public Field{
    private: 
        double r; //distance
        double B_value; //what we're solving for...

    public: 
        Magnetic_field(double x_val, double y_val, double z_val) : Field(x_val, y_val, z_val) {}

        void display(){
            std::cout << "Magnetic field magnitude: " << magnitude() << std::endl;
        }

};



int main(){

    Electric_field e1(1,2,1);
    Magnetic_field m1(1,1,1);

    std::cout << "--------------------" << std::endl;
    e1.print_components();
    e1.display();
    m1.print_components();
    m1.display();

    return 0;
}