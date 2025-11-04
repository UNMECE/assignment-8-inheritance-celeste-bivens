#include <iostream>
#include <cmath>

class Field{
    private: 
        double *component;
    
    public: 
        //Default constructor
        Field()
        {
            component = new double[3];//array with 3 doubles (x, y, z)
            component[0] = 0.0;
            component[1] = 0.0;
            component[2] = 0.0;

            std::cout << "Default Constructor called" << std::endl;
        }

        Field(double x, double y, double z)
        {
            component = new double[3];//array with 3 doubles (x, y, z)
            component[0] = x;
            component[1] = y;
            component[2] = z;

            std::cout << "Constructor called" << std::endl;
        }

        void set_x(double x){component[0] = x;}
        double get_x(){return component[0];}

        void set_y(double y){component[1] = y;}
        double get_y(){return component[1];}

        void set_z(double z){component[2] = z;}
        double get_z(){return component[2];}

        double magnitude(){
            auto x = get_x();
            auto y = get_y();
            auto z = get_z();
            auto mag = sqrt(x*x + y*y + z*z);
            return mag;
        }

        void print_magnitude(){
            std::cout << "Magnitude is: " << magnitude() << std::endl;
        }
        
        //destructor
        ~Field(){
            delete [] component;
            std::cout << "Destructor called" << std::endl;
        }
        
};

//Electric and Magnetic Field are under the base class of Field.
class Electric_field : public Field{
    //Constructor using base class Field
    private: 
        double E_value; //what we're solving for...

    public: 

        //default constructor using base class Field
        Electric_field() : Field() {}

        //parametric constructor using base class Field
        Electric_field(double x, double y, double z) : Field(x, y, z){}

        void display_components(){
            auto x = get_x();
            auto y = get_y();
            auto z = get_z();
            std::cout << "Components: (" << x <<", " << y << ", " << z <<") " <<std::endl;
        }

        //calculate E field.
        double Calculate_E_value(){
            double r = 0.5; //distance = 0.5 m
            double Q = 0.00024;//example charge is 0.0024+ coulumbs.
            double const k = 8.854e-12;//Permitivity of free space: 8.854 * 10^-12 faarads/m

            //E = Q/4pi(r^2)k
            auto E_value = (Q /4 * M_PI * (r*r) *k);
            return E_value;
        }

        //Copy constructor
        //Initializing our base class to retrieve the new values
        Electric_field(Electric_field &other) : Field(other.get_x(), other.get_y(), other.get_z()){
            std::cout << "copy constructor called" << std::endl;
        }

        //overload operator (+)
        Electric_field operator+(Electric_field &other)
        {
            auto x = this->get_x() + other.get_x();
            auto y = this->get_y() + other.get_y();
            auto z = this->get_z() + other.get_z();

            return Electric_field (x,y,z);
        }

        //overload operator <<
        friend std::ostream& operator<<(std::ostream &os, Electric_field &other){

            os << other.get_x() << ' ' << other.get_y() << ' ' << other.get_z();
            return os;
        } 


};

class Magnetic_field : public Field{
    private: 
        double B_value; //what we're solving for...

    public: 
        //default constructor using base class Field
        Magnetic_field() : Field() {}

        //constructor using base class Field
        Magnetic_field(double x, double y, double z) : Field(x,y,z) {}

        //copy constructor
        Magnetic_field(Magnetic_field &other) : Field(other.get_x(), other.get_y(), other.get_z()){
            std::cout << "copy constructor called" << std::endl;
        }

        //calculate mag field
        double Calculate_B_value() {
            double r = 0.5; //distance = 0.5 m
            double const mu_0 = (4e-10 * M_PI); //Permeability of free space/magnetic constant. 
            double I = 2.75e-10;//example value for current

            //B = I/2pi(r^2)*mew_0
            double B = (I / 2 * M_PI * (r*r) * mu_0);
            return B;
        }

        void display_components(){
            auto x = get_x();
            auto y = get_y();
            auto z = get_z();
            std::cout << "components: (" << x <<", " << y << ", " << z <<") " <<std::endl;
        }

        //overload operator <<
        friend std::ostream& operator<<(std::ostream &os, Magnetic_field &other){

            os << other.get_x() << ' ' << other.get_y() << ' ' << other.get_z();
            return os;
        } 

        //overload constructor (+)
        Magnetic_field operator+(Magnetic_field &other)
        {
            auto x = this->get_x() + other.get_x();
            auto y = this->get_y() + other.get_y();
            auto z = this->get_z() + other.get_z();

            return Magnetic_field (x,y,z);
        }     
};



int main(){
    //Electric_field objects
    Electric_field default_e_Field;//Calling default destructor once
    Electric_field e1(0,1e5,1e3);
    Electric_field e2(1e-24, 2e5, 3e-6);

    //Magnetic field objects
    Magnetic_field default_m_Field;//Calling default destructor once
    Magnetic_field m1(0,1e-23, 1e5);
    Magnetic_field m2(23, 2e4, 3e-20);

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "========Electric Field calculations======="<<std::endl;
    e1.display_components();
    e2.display_components();
    std::cout<< "Value for Electric Field: "<< e1.Calculate_E_value() <<" coulumbs" << std::endl;
    std::cout << "Copy constructor demonstration: (" << e2 <<") "<< std::endl;
    Electric_field e3 = e1 + e2;
    std::cout << "Overload operator demonstration: (" << e3 << ") " << std::endl;
    Electric_field e4 = e3;
    std::cout << "New object for Electric field: (" << e4 <<") "<< std::endl;

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "=========Magnetic Field calculations======="<<std::endl;    
    m1.display_components();
    m2.display_components();
    std::cout << "Value for mag field: " << m1.Calculate_B_value() <<" A" << std::endl;
    std::cout << "Copy constructor demonstration: (" << m2 <<") "<< std::endl;
    Magnetic_field m3 = m1 + m2;
    std::cout << "Overload operator demonstration: (" << m3 << ") " << std::endl;
    Magnetic_field m4 = m3;
    std::cout << "New object for Magnetic field: (" << m4 <<") " << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;


    return 0;
}