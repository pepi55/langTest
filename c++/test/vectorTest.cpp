#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	vector<int> VectorInt(19,22);

	for (long i = 0; i < 5; i++) {
		try {
			cout << "Element " << i << ": " << VectorInt.at(i) << endl;
		} catch (exception& e) {
			cout << "Element " << i << ": index exceeds vector dimensions." << endl;
		}
	}

	return EXIT_SUCCESS;
}
