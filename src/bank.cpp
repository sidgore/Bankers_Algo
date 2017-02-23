#include <iostream>
#include <iterator>
#include <algorithm>
#include "./bank.h"
using namespace std;

Bank::Bank() {
	m = 0;
	n = 0;
	pid = 0;

	this->A = A;
	M = new int*[10];
	for (int i = 0; i < 10; i++)
		M[i] = new int[10];
	N = new int*[10];
	for (int i = 0; i < 10; i++)
		N[i] = new int[10];

	W = new int*[1];
	for (int i = 0; i < 10; i++)
		W[i] = new int[10];
}

void Bank::setallocation(int A[10][10], int& n, int& m) {
	int i = 0;

	while (i < n) {
		cout << endl << "Process   " << i + 1 << endl;
		int j = 0;
		while (j < m) {
			cout << " Allocation for resource :" << j + 1;
			cin >> A[i][j];
			j++;
		}
		i++;
	}
}

void Bank::setmaxallocation(int M[10][10], int& n, int& m) {
	int i = 0;

	while (i < n) {
		cout << endl << "Process " << endl << i + 1;
		int j = 0;
		while (j < m) {
			cout << " Maximum for resource :" << j + 1;
			cin >> M[i][j];
			j++;
		}
		i++;
	}
}

int Bank::getallocation(int A[10][10], int i, int j) {
	return A[i][j];
}

int Bank::getmaxallocation(int M[10][10], int i, int j) {
	return M[i][j];
}

void Bank::setprocesses(int n) {
	this->n = n;

}

void Bank::setresources(int m) {
	this->m = m;

}

void Bank::setavailable(int& m, int W[1][10]) {
	int i = 0;
	while (i < m) {
		cout << " Resource: " << i + 1;
		cin >> W[0][i];
		i++;
	}
}

void Bank::findneed(int&n, int&m, int N[10][10], int A[10][10], int M[10][10],
		int W[1][10]) {
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {

			N[i][j] = getmaxallocation(M, i, j) - getallocation(A, i, j);

		}

}

void Bank::print(int x[][10], int n, int m) {
	int i = 0;
	while (i < n) {
		cout << endl;
		int j = 0;
		while (j < m) {
			cout << "  " << x[i][j];
			j++;
		}
		i++;
	}

}

void Bank::resource_request(int A[10][10], int N[10][10], int AV[10][10],
		int pid, int m) {
	int request[1][10];
	int i = 0;
	cout << "ENTER MORE REQUEST:" << endl;
	while (i < m) {
		cout << " Request for resource-" << i + 1;
		cin >> request[0][i];
		i++;
	}
	i = 0;
	while (i < m) {
		if (request[0][i] > N[pid][i]) {
			cout << endl << " Error encountered" << endl;

			abort();
		}
		i++;
	}
	i = 0;
	while (i < m) {
		if (request[0][i] > AV[0][i]) {
			cout << endl << "Resources unavailable" << endl;
			abort();
		}
		i++;
	}
	i = 0;
	while (i < m) {
		AV[0][i] = AV[0][i] - request[0][i];
		A[pid][i] = A[pid][i] + request[0][i];
		N[pid][i] = N[pid][i] - request[0][i];

		i++;
	}
}

int Bank::post_check(int A[][10], int N[][10], int W[1][10], int n, int m,
		int is_safe, int a[]) {

	if (is_safe != 0) {
		cout << endl << endl;
		int i = 0;
		while (i < n) {
			cout << " P " << a[i];
			i++;
		}
		cout << endl << "Congrats, the system is in in a safe state" << endl;
		return 1;
	} else {
		cout << endl << "Sorry,There was a deadlock." << endl;

		return 0;
	}
}

int Bank::Is_Safe(int A[][10], int N[][10], int AV[1][10], int n, int m,
		int a[]) {

	int i, j, k, x = 0;
	int F[10], W[1][10];
	int flag1 = 0, flag2 = 0;
	i = 0;
	while (i < n) {
		F[i] = 0;
		i++;
	}
	i = 0;
	while (i < m) {
		W[0][i] = AV[0][i];
		i++;
	}
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			if (F[i] == 0) {
				flag2 = 0;
				j = 0;
				while (j < m) {
					if (N[i][j] > W[0][j])
						flag2 = 1;
					j++;
				}
				if (flag2 == 0 && F[i] == 0) {
					j = 0;
					while (j < m) {
						W[0][j] = W[0][j] + A[i][j];
						j++;
					}
					F[i] = 1;
					flag1++;
					a[x++] = i;
				}
			}
		}
		if (flag1 == n)
			return 1;
	}
	return 0;
}
