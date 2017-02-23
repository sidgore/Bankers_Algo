#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
#include "./bank.h"
using namespace std;

int main() {
	int ret;
	int Alloc[10][10], Max_res[10][10], Need[10][10], Available[1][10], n, m,
			p_id;
	char choice;
	Bank* b = new Bank();
	cout << endl << "Welcome to BANKER'S ALGORITHM for Deadlock Avoidance"
			<< endl;

	cout << "How many processes do you have in mind? ";
	cin >> n;
	b->setprocesses(n);
	cout << endl << " Now enter the number of resources ";

	cin >> m;
	b->setresources(m);
	b->setallocation(Alloc, n, m);
	b->setmaxallocation(Max_res, n, m);
	cout << endl << "Available resources :" << endl;
	b->setavailable(m, Available);

	b->findneed(n, m, Need, Alloc, Max_res, Available);

	cout << endl << "Allocation Matrix";
	b->print(Alloc, n, m);
	cout << endl << "Maximum Requirement Matrix";
	b->print(Max_res, n, m);
	cout << endl << "Need Matrix";
	b->print(Need, n, m);
	int a[10];
	int is_safe = b->Is_Safe(Alloc, Need, Available, n, m, a);
	ret = b->post_check(Alloc, Need, Available, n, m, is_safe, a);
	if (ret != 0) {
		cout << "Do you want to make an additional request ? " << endl;
		cout << "Press Y/y for Yes or any other key to exit)";
		cin >> choice;
		if (choice == 'Y' || choice == 'y') {
			cout << " Enter process no. : ";
			cin >> p_id;
			b->resource_request(Alloc, Need, Available, p_id - 1, m);
			int c[10];
			int is_safe = b->Is_Safe(Alloc, Need, Available, n, m, c);
			ret = b->post_check(Alloc, Need, Available, n, m, is_safe, c);
			if (ret == 0)
				abort();
		}
	}

	return 0;
}
