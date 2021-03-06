#include "tensor.h"

using namespace std;

int main() {
	try {
		//make a 4D tensor, fill with ones
		//dimensions are 3 x 2 x 5 x 8
		Tensor t1({3,2,5,8}, 1.0);
		cout << t1[0][0][0][0] << "\n"; //should be 1

		//set value
		t1[0][1][3][5] = 20;
		cout << t1[0][1][3][5] << "\n"; //should be 20
		
		//set all values of this subtensor
		t1[0][1] = 10;
		cout << t1[0][0][3][5] << "\n"; //still 1
		cout << t1[0][1][3][5] << "\n"; //should be 10
		cout << t1[0][1][3][6] << "\n"; //should be 10
		
		//make a copy; has its own data
		Tensor t2(t1);
		t2[0][1][2] = 3;
		cout << t2[0][1][3][6] << "\n"; //still 10
		cout << t1[0][1][2][6] << "\n"; //still 10
		cout << t2[0][1][2][6] << "\n"; //should be 3
		
		//"=" operator copies values over
		t2[0][1][4] = t1[2][0][1]; 
		cout << t2[0][1][4][6] << "\n"; //should be 1
		
		//some arithmetic
		t1 = 1;
		t2 = 2;
		t2 += 4*(t1 - t2/2 - 6)*t2/3; //should be -14
		cout << t2[0][0][0][0] << "\n";
		
		//arithmetic on subtensors
		t2[0][0] += t1[2][1]*2;
		cout << t2[0][0][0][0] << "\n"; //should be -12
		cout << t2[0][1][0][0] << "\n"; //still -14
		
		Tensor t3({5,8}, 10.0);
		t2[1][1] = t3*5;
		cout << t2[1][1][0][0] << "\n"; //should be 50
		
		//copy subtensor
		Tensor t4(t1[0][1][4]);
		cout << t4[1] << "\n"; //should be 1
	}
	catch(const char* err) {
		cout << "Error: " << err << "\n";
 	}
}