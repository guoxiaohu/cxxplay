#include <iostream>
#include <vector>

using namespace std;

// print matrix
void printMatrix(vector<vector<double>> &mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

// back substitution to get solution x
// assume matrix is upper triangle
vector<double> backSubstitution(vector<vector<double>> &mat, vector<double> &b, int n)
{
    // Initialize solution
    vector<double> x(n, 0);

    // Solve for x_n
    // index start from 0~n-1
    x[n - 1] = b[n - 1] / mat[n - 1][n - 1];

    // Solve for the remaining x_i
    for (int i = n - 2; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            sum += mat[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / mat[i][i];
    }

    return x;
}

// Init upper triangular (including diagonal) part of the matrix to be nonzero
void initializeUpperTriangular(vector<vector<double>> &mat, int n)
{
    srand(time(nullptr));
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            mat[i][j] = rand() % 10 + 1; // Random number between 1 and 10
        }
    }
}

// Initialize the vector b to be non-zero
void initializeB(vector<double> &b, int n)
{
    srand(time(nullptr));
    for (int i = 0; i < n; i++)
    {
        b[i] = rand() % 10 + 1; // Random number between 1 and 10
    }
}

// validation using Ax-b
bool validateSolution(vector<vector<double>> &mat, vector<double> &b, vector<double> &x, int n)
{
    // Check if Ax = b
    for (int i = 0; i < n; i++)
    {
        double sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += mat[i][j] * x[j];
        }
        if (abs(sum - b[i]) > 0.001)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    // Take input matrix size
    int n;
    cout << "Enter matrix size: ";
    cin >> n;

    // Init matrix as upper triangular with non-zero values
    vector<vector<double>> mat(n, vector<double>(n, 0));
    initializeUpperTriangular(mat, n);

    // Print matrix
    cout << "the matrix is: " << endl;
    printMatrix(mat, n);

    // Init vector b with non-zero values
    vector<double> b(n, 0);
    initializeB(b, n);
    cout << "rhs vector is: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << b[i] << endl;
    }

    // back substitution
    vector<double> x = backSubstitution(mat, b, n);

    // Print the solution x
    cout << "Solution vector is: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << x[i] << endl;
    }

    // Validate
    if (validateSolution(mat, b, x, n))
    {
        cout << "Solution is correct! PASS!!!" << endl;
    }
    else
    {
        cout << "Solution is incorrect! FAIL!!!" << endl;
    }

    return 0;
}
