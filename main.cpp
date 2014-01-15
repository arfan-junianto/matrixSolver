//
//  main.cpp
//  Program that allows you to find the point or line (or plane) of intersection of up to three planes, by putting them in reduced row-echelon form.
//
//  Created by Emily Walls on 13-03-29 (YY-MM-DD)
//  Improvement of using pointers to reduce multiples added on 13-07-04
//  13-13-07 Minor change - program will actually change signs on rows that contain zeros, if necessary (and row isn't all zeros) & reduces them
//

#include <iostream>
#include <math.h>
#include <sstream>
using namespace std;
string convertInt(int i) // cast an integer variable to a string variable - no exception handling...yet!
{
     string String = static_cast<ostringstream*>( &(ostringstream() << i) )->str();
     return String;
}
void displayArray(double array[4][3], bool varOn) // varOn is whether or not variables (x,y,z) will be displayed
{
     cout << endl;
     for (int c = 0; c < 3; c++)
     {
          string display = "";
          for (int r = 0; r < 4; r++)
          {
               if (varOn == true)
               {
                    if (r == 0) // All of this code here is so that output at the end doesn't look like -1x + 1y + -6z = 8,
                    {           // but instead looks like -x + y - 6z = 8. It is souly for aesthetic reasons.
                         if (fabs(array[r][c]) != 1)
                              cout << array[r][c];
                         else if (array[r][c] == -1) // don't display 1 in front
                              cout << "-";
                    }
                    if (array[r][c] > 1 && r != 3)
                    {
                         display = "+ ";
                         display += convertInt(array[r][c]); // Conversion is necessary, otherwise this isn't added to the string
                    }
                    else if (array[r][c] == 1 && r != 3) // don't display a one unless after equals sign
                    {
                         display = "+ ";
                    }
                    else if (array[r][c] == -1 && r != 3)
                    {
                         display = "- ";
                    }
                    else if (array[r][c] == 0 && r != 3 && r != 0)
                    {
                         display = "+ 0";
                    }
                    else if (r == 3)
                         cout << array[r][c];
                    else if (array[r][c] < -1 && r != 0 && r != 3)
                    {
                         display = "- ";
                         display += convertInt(-array[r][c]); // instead of adding a negative, make it subtracting a positive
                    }
               }
               else if (varOn == false)
                    cout << array[r][c]; // don't be fancy when displaying just matrix, instead of equations
               if (varOn == 1) // only display as equations at the end, when this is set to 1 (on)
               {
                    switch (r)
                    {
                         case 0:
                              cout << "x ";
                              break;
                         case 1:
                              cout << display << "y ";
                              break;
                         case 2:
                              cout << display << "z = ";
                              break;
                         case 3:
                              cout << endl; // r will never be any other value, so default case is unnecessary
                              break;
                    }
               }
               else
                    switch (r)
               {
                    case 0:
                         cout << " ";
                         break;
                    case 1:
                         cout << " ";
                         break;
                    case 2:
                         cout << " | ";
                         break;
                    case 3:
                         cout << endl;
                         break;
               }
               if (r == 3 && c == 2) // last value in array
                    cout << endl;
          }
     }
}
void lineOrPlane(double array[4][3])
{
     if (((array[0][1] == 0 && array[1][1] == 0 && array[2][1] == 0 && array[3][1] == 0) && (array[0][0] == 0 && array[1][0] == 0 && array[2][0] == 0 && array[3][0] == 0)) || ((array[0][1] == 0 && array[1][1] == 0 && array[2][1] == 0 && array[3][1] == 0) && (array[0][2] == 0 && array[1][2] == 0 && array[2][2] == 0 && array[3][2] == 0)) || ((array[0][2] == 0 && array[1][2] == 0 && array[2][2] == 0 && array[3][2] == 0) && (array[0][0] == 0 && array[1][0] == 0 && array[2][0] == 0 && array[3][0] == 0))) // if two of the rows are all 0s, solution is a plane
     {
          if (array[0][0] == array[0][1] && array[0][1] == array[0][2] && array[0][2] == array[1][0] && array[1][0] == array[1][1] && array[1][1] == array[1][2] && array[1][2] == array[2][2] && array[2][2] == array[2][3] && array[2][3] == array[3][0] && array[3][0] == array[3][1] && array[3][1] == array[3][2] && array[3][2] == 0)
          {
               cout << "∴ the solution is every point in 3D space." << endl; // This isn't really necessary - the only time this will
               // occur is when 12 0's are entered.
               // Without this, though, the program would end without any comment about the solution.
          }
          else
          {
               cout << "∴ there is an infinite number of solutions to this system. I.e., the planes are coincident." << endl;
               cout << "Final equations (use to create parametric equations or a vector equation for the plane):" << endl;
               displayArray(array, 1);
          }
     }
     else
     {
          cout << "∴ there is an infinite number of solutions to this system. I.e., the planes intersect at a line." << endl;
          cout << "Final equations (use to create parametric or symmetric equations, or a vector equation for the line):" << endl;
          displayArray(array, 1);
     }
}
void firstPositive(double array[4][3], int display)
{
     for (int i = 0; i < 3; i++)
     {
          if (array[i][i] < 0) // final step in row-echelon form: make leading 1s positive
          {
               
               if (array[0][i] != 0)
                    array[0][i] = -array[0][i];
               if (array[1][i] != 0)
                    array[1][i] = -array[1][i];
               if (array[2][i] != 0)
                    array[2][i] = -array[2][i];
               if (array[3][i] != 0)
                    array[3][i] = -array[3][i];
               if (display == 2)
               {
                    cout << "Changing signs on row " << i + 1 << "...\n";
                    displayArray(array, 0);
               }
          }
     }
}
void reduce(double array[4][3], int display) // original array will be modified since arrays are pointers
{
     // if everything in a row is negative (ignore augmented part), make everything in the row positive
     for (int i = 0; i < 3; i++)
     {
          if (array[0][i] == array[1][i] && array[1][i] == array[2][i] && array[2][i] == array[3][i] && array[3][i] == 0)
          {
               // do nothing -- only used to have an else statement which has code that does nothing when the row is all zeros
          }
          else if (array[0][i] <= 0 && array[1][i] <= 0 && array[2][i] <= 0)
          {
               if (array[0][i] != 0) // these if statements prevent a 0 from becoming -0 (not sure why that happens otherwise...)
                    array[0][i] = -array[0][i];
               if (array[1][i] != 0)
                    array[1][i] = -array[1][i];
               if (array[2][i] != 0)
                    array[2][i] = -array[2][i];
               if (array[3][i] != 0)
                    array[3][i] = -array[3][i];
               if (display == 2)
               {
                    cout << "Changing signs on row " << i + 1 << "...\n";
                    displayArray(array, 0);
               }
          }
     }
     // then, reduce the rows:
     // check each row and determine whether or not it can be reduced (keeping each value integral)
     for (int i = 0; i < 3; i++)
     {
          int temp = 1; // this should always be overwritten
          for (int k = 0; k < 3; k++)
          {
               if (array[k][i] != 0)
               {
                    temp = fabs(array[k][i]);
                    k = 4; // loop ends when this criterion is met
               }
          }
          if (fabs(array[1][i]) < temp && array[1][i] != 0) // don't do this if the value is zero
               temp = fabs(array[1][i]);
          if (fabs(array[2][i]) < temp && array[2][i] != 0)
               temp = fabs(array[2][i]);
          if (fabs(array[3][i]) < temp && array[3][i] != 0)
               temp = fabs(array[3][i]);// set temp equal to smallest absolute value in row
          for (int j = temp; j > 1; j--) // divide each row by j, if possible. Stop once j is 1, of course
          {
               if (fmod(array[0][i], j) == 0 && fmod(array[1][i], j) == 0 && fmod(array[2][i], j) == 0 && fmod(array[3][i], j) == 0)
               {    // fmod is % for doubles
                    array[0][i] = array[0][i]/j;
                    array[1][i] = array[1][i]/j;
                    array[2][i] = array[2][i]/j;
                    array[3][i] = array[3][i]/j;
                    if (display == 2)
                    {
                         cout << "Dividing row " << i + 1 << " by " << j << "...\n";
                         displayArray(array, 0);
                    }
                    j = 1; // causes loop to end for reducing (since reduces by largest value it can the first time)
               }
          }
     }
}
void reduceMultiples(double *pA, double *pB) // more efficient than having two separate methods to reduce these multiples! Use pointers!
{
     int temp = *pA;
     if (*pB < *pA) // set to smaller of the two, so reduction occurs more efficiently
          temp = *pB;
     for (int i = temp; i > 1; i--)
     {
          if (fmod(*pA, i) == 0 && fmod(*pB, i) == 0)
          {
               *pA /= i;
               *pB /= i;
          }
     }
}
void swapRows(double array[4][3], int first, int second, int display) // first and second are row numbers which must be swapped
{
     int temp0, temp1, temp2, temp3;
     temp0 = array[0][first];
     temp1 = array[1][first];
     temp2 = array[2][first];
     temp3 = array[3][first];
     array[0][first] = array[0][second];
     array[1][first] = array[1][second];
     array[2][first] = array[2][second];
     array[3][first] = array[3][second];
     array[0][second] = temp0;
     array[1][second] = temp1;
     array[2][second] = temp2;
     array[3][second] = temp3;
     if (display == 2)
     {
          cout << "Swapping row " << first + 1 << " with row " << second + 1 << "...\n"; // first and second are 1 less than actual row #s
          displayArray(array, 0);
     }
}
int main (int argc, const char * argv[])
{
     // declare variables
     double m1 = 1;
     double m2 = 1;
     double matrix[4][3];
     int choice = 1;
     bool quit = false;
     string decide;
     int counter = 0;
     
     cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nCalculate the Intersection of Up to Three Planes.\nProgram created by Emily Walls on March 30/13." << endl;
     cout << endl << "Would you like to display the matrix after each calculation,\nand the calculations performed on it?\n1)No\n2)Yes\n\n" << endl;
     
     cin >> choice;
     if (choice == 1) // make default choice to display calculations
          cout << endl << "Matrix WILL NOT be displayed after each calculation." << endl;
     else
     {
          cout << endl << "Matrix WILL be displayed after each calculation." << endl;
          choice = 2; // allows calculations to be shown even if user didn't enter 2 (default is that they are shown!)
     }
     while (quit == false)
     {
          cout << "\n\nEnter plane equations in matrix form. If you wish to find the" << endl;
          cout << "intersection of just two planes, enter four zeros in the third row.\n" << endl;
          
          for (int c = 0; c < 3; c++)
          {
               for (int r = 0; r < 4; r++)
               {
                    cin >> matrix[r][c];
               }
          }
          
          cout << endl;
          if (matrix[0][0] == 0)
          {
               for (int i = 0; i < 4; i++)
               {
                    if (matrix[i][1] == 0)
                         counter++;
               }
               if (matrix[0][1] != 0 && counter != 4)
               {
                    swapRows(matrix, 0, 1, choice); // don't do this if row 2 is all zeros
               }
               else if (matrix[0][2] != 0)
               {
                    swapRows(matrix, 0, 2, choice);
               }
               else // all x-values are 0
               {
                    if (matrix[1][0] == 0)
                    {
                         if (matrix[1][1] != 0)
                         {
                              swapRows(matrix, 0, 1, choice);
                         }
                         else if (matrix[1][2] != 0)
                         {
                              swapRows(matrix, 0, 2, choice);
                         }
                    }
               }
          }
          counter = 0;
          if (matrix[0][2] != 0 && matrix[0][1] == 0)
          {
               swapRows(matrix, 1, 2, choice);
          }
          if (matrix[1][1] == 0)
          {
               for (int i = 0; i < 4; i++)
               {
                    if (matrix[i][1] == 0)
                         counter++;
               }
               if (matrix[1][2] != 0)
               {
                    swapRows(matrix, 1, 2, choice);
               }
               else if (matrix[1][0] != 0 && counter != 4)
               {
                    swapRows(matrix, 1, 0, choice); // don't do this if row 2 is all zeros
               }
          }
          counter = 0;
          if (matrix[1][2] != 0 && matrix[2][2] == 0)
          {
               swapRows(matrix, 1, 2, choice);
          }
          reduce(matrix, choice);
          if (matrix[0][2] != 0)
          {
               m1 = matrix[0][0];
               m2 = matrix[0][2];
               reduceMultiples(&m1, &m2);
               if (m1 != 0 && m2 != 0)
               {
                    matrix[0][2] = matrix[0][0] * m2 - matrix[0][2] * m1;
                    matrix[1][2] = matrix[1][0] * m2 - matrix[1][2] * m1;
                    matrix[2][2] = matrix[2][0] * m2 - matrix[2][2] * m1;
                    matrix[3][2] = matrix[3][0] * m2 - matrix[3][2] * m1;
                    if (choice == 2)
                    {
                         if (m1 < 0)
                         {
                              cout << "R3 = " << m2 << "R1 " << "+ " << -m1 << "R3...\n";
                              displayArray(matrix, 0);
                         }
                         else
                         {
                              cout << "R3 = " << m2 << "R1 " << "- " << m1 << "R3...\n";
                              displayArray(matrix, 0);
                         }
                    }
               }
          }
          if (matrix[1][2] != 0 && matrix[2][2] == 0)
          {
               swapRows(matrix, 1, 2, choice); // need to redo first calculation if this happens
               m1 = matrix[0][0];
               m2 = matrix[0][2];
               reduceMultiples(&m1, &m2);
               if (m1 != 0 && m2 != 0)
               {
                    matrix[0][2] = matrix[0][0] * m2 - matrix[0][2] * m1;
                    matrix[1][2] = matrix[1][0] * m2 - matrix[1][2] * m1;
                    matrix[2][2] = matrix[2][0] * m2 - matrix[2][2] * m1;
                    matrix[3][2] = matrix[3][0] * m2 - matrix[3][2] * m1;
                    if (choice == 2)
                    {
                         if (m1 < 0)
                         {
                              cout << "R3 = " << m2 << "R1 " << "+ " << -m1 << "R3...\n";
                              displayArray(matrix, 0);
                         }
                         else
                         {
                              cout << "R3 = " << m2 << "R1 " << "- " << m1 << "R3...\n";
                              displayArray(matrix, 0);
                         }
                    }
               }
          }
          reduce(matrix, choice);
          
          if (matrix[0][1] != 0)
          {
               m1 = matrix[0][0];
               m2 = matrix[0][1];
               reduceMultiples(&m1, &m2);
               if (m1 != 0 && m2 != 0)
               {
                    matrix[0][1] = matrix[0][0] * m2 - matrix[0][1] * m1;
                    matrix[1][1] = matrix[1][0] * m2 - matrix[1][1] * m1;
                    matrix[2][1] = matrix[2][0] * m2 - matrix[2][1] * m1;
                    matrix[3][1] = matrix[3][0] * m2 - matrix[3][1] * m1;
                    if (choice == 2)
                    {
                         if (m1 < 0)
                         {
                              cout << "R2 = " << m2 << "R1 " << "+ " << -m1 << "R2...\n";
                              displayArray(matrix, 0);
                         }
                         else
                         {
                              cout << "R2 = " << m2 << "R1 " << "- " << m1 << "R2...\n";
                              displayArray(matrix, 0);
                         }
                    }
               }
          }
          if (matrix[1][1] == 0)
          {
               for (int i = 0; i < 4; i++)
               {
                    if (matrix[i][1] == 0)
                         counter++;
               }
               if (matrix[1][2] != 0)
               {
                    swapRows(matrix, 1, 2, choice);
               }
               else if (matrix[1][0] != 0 && counter != 4)
               {
                    swapRows(matrix, 1, 0, choice); // don't do this if row 2 is all zeros
               }
          }
          reduce(matrix, choice);
          if (matrix[1][2] != 0)
          {
               m1 = matrix[1][1];
               m2 = matrix[1][2];
               reduceMultiples(&m1, &m2);
               if (m1 != 0 && m2 != 0)
               {
                    matrix[1][2] = matrix[1][1] * m2 - matrix[1][2] * m1;
                    matrix[2][2] = matrix[2][1] * m2 - matrix[2][2] * m1;
                    matrix[3][2] = matrix[3][1] * m2 - matrix[3][2] * m1;
                    if (choice == 2)
                    {
                         if (m1 < 0)
                         {
                              cout << "R3 = " << m2 << "R2 " << "+ " << -m1 << "R3...\n";
                              displayArray(matrix, 0);
                         }
                         else
                         {
                              cout << "R3 = " << m2 << "R2 " << "- " << m1 << "R3...\n";
                              displayArray(matrix, 0);
                         }
                    }
               }
          }
          
          reduce(matrix, choice);
          if (matrix[1][0] != 0)
          {
               m1 = matrix[1][1];
               m2 = matrix[1][0];
               reduceMultiples(&m1, &m2);
               if (m1 != 0 && m2 != 0)
               {
                    matrix[0][0] = matrix[0][1] * m2 - matrix[0][0] * m1;
                    matrix[1][0] = matrix[1][1] * m2 - matrix[1][0] * m1;
                    matrix[2][0] = matrix[2][1] * m2 - matrix[2][0] * m1;
                    matrix[3][0] = matrix[3][1] * m2 - matrix[3][0] * m1;
                    if (choice == 2)
                    {
                         if (m1 < 0)
                         {
                              cout << "R1 = " << m2 << "R2 " << "+ " << -m1 << "R1...\n";
                              displayArray(matrix, 0);
                         }
                         else
                         {
                              cout << "R1 = " << m2 << "R2 " << "- " << m1 << "R1...\n";
                              displayArray(matrix, 0);
                         }
                    }
               }
          }
          reduce(matrix, choice);
          if (matrix[2][0] != 0)
          {
               m1 = matrix[2][2];
               m2 = matrix[2][0];
               reduceMultiples(&m1, &m2);
               if (m1 != 0 && m2 != 0)
               {
                    matrix[0][0] = matrix[0][2] * m2 - matrix[0][0] * m1;
                    matrix[1][0] = matrix[1][2] * m2 - matrix[1][0] * m1;
                    matrix[2][0] = matrix[2][2] * m2 - matrix[2][0] * m1;
                    matrix[3][0] = matrix[3][2] * m2 - matrix[3][0] * m1;
                    if (choice == 2)
                    {
                         if (m1 < 0)
                         {
                              cout << "R1 = " << m2 << "R3 " << "+ " << -m1 << "R1...\n";
                              displayArray(matrix, 0);
                         }
                         else
                         {
                              cout << "R1 = " << m2 << "R3 " "- " << m1 << "R1...\n";
                              displayArray(matrix, 0);
                         }
                    }
               }
          }
          reduce(matrix, choice);
          if (matrix[2][1] != 0)
          {
               m1 = matrix[2][2];
               m2 = matrix[2][1];
               reduceMultiples(&m1, &m2);
               if (m1 != 0 && m2 != 0)
               {
                    matrix[1][1] = matrix[1][2] * m2 - matrix[1][1] * m1;
                    matrix[2][1] = matrix[2][2] * m2 - matrix[2][1] * m1;
                    matrix[3][1] = matrix[3][2] * m2 - matrix[3][1] * m1;
                    if (choice == 2)
                    {
                         if (m1 < 0)
                         {
                              cout << "R2 = " << m2 << "R3 " << "+ " << -m1 << "R2...\n";
                              displayArray(matrix, 0);
                         }
                         else
                         {
                              cout << "R2 = " << m2 << "R3 " << "- " << m1 << "R2...\n";
                              displayArray(matrix, 0);
                         }
                    }
               }
          }
          firstPositive(matrix, choice); // final step in row echelon form: make leading numbers positives (should be ones, but won't always be
          // due to avoidance of fractions
          reduce(matrix, choice);
          if ((matrix[0][1] == 0 && matrix[1][1] == 0 && matrix[2][1] == 0 && matrix[3][1] != 0) || (matrix[0][0] == 0 && matrix[1][0] == 0 && matrix[2][0] == 0 && matrix[3][0] != 0) || (matrix[0][2] == 0 && matrix[1][2] == 0 && matrix[2][2] == 0 && matrix[3][2] != 0))
          { // that is, if one of the rows is inadmissible, i.e. 0x+0y+0z=/=0
               cout << "∴ there is no solution to the system. I.e., the planes do not intersect." << endl;
          }
          else if (((matrix[0][0] != 0) && matrix[1][0] == 0 && matrix[2][0] == 0) && ((matrix[1][1] != 0) && matrix[0][1] == 0 && matrix[2][1] == 0) && ((matrix[2][2] != 0) && matrix[0][2] == 0 && matrix[1][2] == 0))
          {
               if (matrix[0][0] != 0)
               {
                    cout << "∴ the solution is the point:" << endl;
                    if (matrix[0][0] == 1)
                         cout << "x = " << matrix[3][0] << endl;
                    else if (matrix[0][0] == -1)
                         cout << "x = " << -matrix[3][0] << endl; // since leading negatives are changed to positives, this shouldn't ever execute
                    else if (fmod(matrix[3][0], matrix[0][0]) == 0) // if they divide evenly, display the quotient
                         cout << "x = " << (matrix[3][0]/matrix[0][0]) << endl;
                    else                                         // if they don't divide evenly, display as a fraction
                         cout << "x = " << matrix[3][0] << "/" << matrix[0][0] << " = " << (matrix[3][0]/matrix[0][0]) <<  endl;
                    // fraction will always be in reduced form because of matrix always being reduced
                    if (matrix[1][1] != 0)
                    {
                         if (matrix[1][1] == 1)
                              cout << "y = " << matrix[3][1] << endl;
                         else if (matrix[1][1] == -1)
                              cout << "y = " << -matrix[3][1] << endl;
                         else if (fmod(matrix[3][1], matrix[1][1]) == 0)
                              cout << "y = " << (matrix[3][1]/matrix[1][1]) << endl;
                         else
                              cout << "y = " << matrix[3][1] << "/" << matrix[1][1] << " = " << (matrix[3][1]/matrix[1][1]) << endl;
                    }
                    if (matrix[2][2] != 0)
                    {
                         if (matrix[2][2] == 1)
                              cout << "z = " << matrix[3][2] << endl;
                         else if (matrix[2][2] == -1)
                              cout << "z = " << -matrix[3][2] << endl;
                         else if (fmod(matrix[3][2], matrix[2][2]) == 0)
                              cout << "z = " << matrix[3][2]/matrix[2][2] << endl;
                         else
                              cout << "z = " << matrix[3][2] << "/" << matrix[2][2] << " = " << (matrix[3][2]/matrix[2][2]) << endl;
                    }
               }
          }
          else
          {
               lineOrPlane(matrix); // only run this method if previous if statement fails (so, if the solution is not a point)
          }
          cout << "\n\nWould you like to solve another matrix? (y/n)\n";
          cin >> decide; // getline(cin, decide); causes an infinite loop, for some reason
          if (decide[0] == 'n' || decide[0] == 'N')
          {
               cout << "\n\nGoodbye!\n";
               quit = true;
          }
     }
     cin.ignore(); // make console screen stay
     return 0;
}