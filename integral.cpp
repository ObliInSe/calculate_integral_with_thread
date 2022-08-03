#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

class Integral
{
public:
	Integral(const float coef_x_3, const float coef_x_2, const float coef_x_1, const float coef_x_0, const float e);
	void Rectangle_Method(const float i)
	{
		this->integral = this->integral + (coef_x_3 * pow(i,3)+coef_x_2*pow(i,2) + coef_x_1 * (i) + coef_x_0)* e;
		cout <<i<<"\t"<<"\t Potok:"<< this_thread::get_id() << endl;
	}
	float Get_Integral() const
	{
		return integral;
	}
private:
	long float integral=0;
	long float coef_x_3;
	long float coef_x_2;
	long float coef_x_1;
	long float coef_x_0;
	float e;
};


int main()
{
	cout << "Start" << endl;
	long float up_limit_integration = 16;
	float down_limit_integration=15;
	float coef_x_3=0; 
	float coef_x_2=0;
	float coef_x_1=0;
	float coef_x_0=2;
	float e=0.001;	
	Integral integral(coef_x_3,coef_x_2,coef_x_1,coef_x_0,e);
	for (float i = up_limit_integration; i > down_limit_integration; i-=e*4)
	{
		thread thread_1([&integral,&i]() {integral.Rectangle_Method(i); });
		thread thread_2([&integral, &i,&e]() {integral.Rectangle_Method(i-e); });
		thread thread_3([&integral, &i, &e]() {integral.Rectangle_Method(i-e*2); });
		thread thread_4([&integral, &i, &e]() {integral.Rectangle_Method(i-e*3); });
		thread_1.join();
		thread_2.join();
		thread_3.join();
		thread_4.join();
		cout << endl << endl;
	}	
	cout <<"Integral =  "<< integral.Get_Integral() << endl;
	return 0;
}

Integral::Integral(const float coef_x_3, const float coef_x_2, const float coef_x_1, const float coef_x_0,const float e)
{
	this->coef_x_3 = coef_x_3;
	this->coef_x_2 = coef_x_2;
	this->coef_x_1 = coef_x_1;
	this->coef_x_0 = coef_x_0;
	this->e = e;
}
