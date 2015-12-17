#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;


struct pos /// matrix cell
{
	int x;
	int y;
};

const int size = 30; /// size of the matrix side


// fill a cell return true if cell was free
// before this function, run fu valid_el(...) 
// They will be merged in the future;
bool fill_el(int mas[size][size], struct pos el, int value)
{
	if (mas[el.y][el.x] == 0)
	{
		mas[el.y][el.x] = value;
		return true;
	}
	else
		return false;
}
// check if the position in the bound matrix
bool valid_el(struct pos el, int szw, int szh)
{
	return (el.x >= 0 && el.x<szw && el.y >= 0 && el.y<szh);
}
// print a letter in the cell
void cout_cell(int val)
{
	cout << ' ' << (char) ('A' + (char)(val - 2));
}


// recusive function
// struct pos el - a start cell
// bnew = a new fill
// int value - value for a filling
int fill(int mas[size][size], struct pos el, int szw, int szh, int value, bool bnew)
{

	struct pos u, d, l, r;       /// neighbouring cells
	static int filled = 1;       /// counter
	if (bnew == true)filled = 1; /// reset couner 
	l.y = el.y;     ///  a left cell
	l.x = el.x - 1;
	r.y = el.y;     /// a right cel
	r.x = el.x + 1;
	u.y = el.y - 1; /// an up cell
	u.x = el.x;
	d.y = el.y + 1; /// a down cell
	d.x = el.x;

	if (valid_el(r, szw, szh))  
	if (fill_el(mas, r, value)) 
	{                           
		fill(mas, r, szw, szh, value, false); /// recurse
		++filled;                 /// increment counter
	}
	if (valid_el(l, szw, szh))
	if (fill_el(mas, l, value))
	{
		fill(mas, l, szw, szh, value, false);
		++filled;
	}
	if (valid_el(u, szw, szh))
	if (fill_el(mas, u, value))
	{
		fill(mas, u, szw, szh, value, false);
		++filled;
	}
	if (valid_el(d, szw, szh))
	if (fill_el(mas, d, value))
	{
		fill(mas, d, szw, szh, value, false);
		++filled;
	}
	/// count of filled cells
	return filled;
}

void paper()
{
	int mass[size][size];   /// the matrix
	int z = size*size / 3;  /// 25% -  holes
	int i, j;        /// for cycles
	struct pos cell; /// a current cell

	for (i = 0; i<size; ++i)
	for (j = 0; j<size; ++j)
		mass[i][j] = 0; /// an initialize

	do
	{
		i = rand() % size; /// random y
		j = rand() % size; /// random x

		if (mass[i][j] == 0) /// if it is not a hole
		{
			mass[i][j] = 1; /// made a hole
			--z; // 
		}
	} while (z>0); /// fill all percsent cells


	for (i = 0; i<size; ++i) /// show on screen
	{
		for (j = 0; j < size; ++j)
			cout << " " << mass[i][j];
		cout << endl;
	}
	cout << endl;

	int fl;      /// count cell
	int val = 2; /// 0-clear, 1-a hole, 2-n - filled
	int find;    /// if clear cell was found

	
	do{
		find = 0;
		for (i = 0; i<size; ++i)
		{
			for (j = 0; j<size; ++j)
			if (mass[i][j] == 0)
			{
				find = 1;         
				mass[i][j] = val; /// fill from 2 to n val 
				break;
			}
			if (find == 1) break; 
		}

		cell.y = i; /// cell for begin a filling
		cell.x = j;
		fl = fill(mass, cell, size, size, val, true); /// make a new filling
		if (fl != 0)
		{
			if (i<size && j<size) /// its all ?
			{
				/// show an info
				cout_cell(val);
				cout << " part:" << setw(5) << fl << " x:" << setw(3) << j << " y:" << setw(3)  << i << endl;
			}
			++val; /// choose a next symbol for fill
		}
	} while (i<size && j<size); /// while all is'nt filled

	cout << endl;
	for (i = 0; i<size; ++i) /// show a result
	{
		for (j = 0; j<size; ++j)
		if (mass[i][j] != 1)
			cout_cell(mass[i][j]);
		else
			cout << " ."; 
		cout << endl;
	}
	cout << "Count parts:" << val - 3 << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	paper();
	return 0;
}

