#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Tree
{
	string Data;
	Tree *Left, *Right, *Parent;
};
typedef Tree*PTree;

void LL(PTree &p)
{
	PTree leftson = p->Left;
	p->Left = leftson->Right;
	leftson->Right = p;
	p = leftson;
}
void R(PTree &x)	// правый поворот
{
	PTree p = x->Parent;
	if (p->Parent != nullptr && p->Parent->Left == p)
		p->Parent->Left = x;
	else
		if (p->Parent != nullptr && p->Parent->Right == p)
			p->Parent->Right = x;
	x->Parent = p->Parent;
	p->Parent = x;
	p->Left = x->Right;
	if (x->Right != nullptr)
		x->Right->Parent = p;
	x->Right = p;
}
void L(PTree &x)	// левый поворот
{
	PTree p = x->Parent;
	if (p->Parent != nullptr && p->Parent->Left == p)
		p->Parent->Left = x;
	else
		if (p->Parent != nullptr && p->Parent->Right == p)
			p->Parent->Right = x;
	x->Parent = p->Parent;
	p->Parent = x;
	p->Right = x->Left;
	if (x->Left != nullptr)
		x->Left->Parent = p;
	x->Left = p;
}
void Splay(PTree &x, PTree &Root)	// перемещение вершины в корень дерева
{
	while (true)
	{
		if (x->Parent == nullptr)
			break;
		if (x->Parent->Parent == nullptr)
		{
			if (x == x->Parent->Left)
				R(x);
			else 
				L(x);
			break;
		}
		if (x->Parent == x->Parent->Parent->Left)
			if (x == x->Parent->Left)
			{
				R(x->Parent);
				R(x);
			}
			else
			{
				L(x);
				R(x);
			}
		else
			if ( x == x->Parent->Right)
			{
				L(x->Parent);
				L(x);
			}
			else
			{	
				R(x);
				L(x);
			}
	}
	Root = x;
}
void Insert(PTree &Root, PTree &p, string data)	// вставка вершины в дерево
{
	if (Root == nullptr)
	{
		Root = new Tree;
		Root->Data = data;
		Root->Left = nullptr;
		Root->Right = nullptr;
		if (Root != p)
			Root->Parent = p;
		else
			Root->Parent = nullptr;
		return;
	}
	if (data < Root->Data)
		Insert(Root->Left, Root, data);
	else
		if (data > Root->Data)
			Insert(Root->Right, Root, data);
}
void Print(PTree Root, int lvl, ofstream &fout)		// вывод дерева в файл
{
	if (Root == nullptr)
		return;
	Print(Root->Right, lvl + 1, fout);
	for (int i = 0; i < lvl; i++)
		fout << setw(7) << ' ';
	fout << setw(7) << Root->Data << endl;
	Print(Root->Left, lvl + 1, fout);
}
void Delete(PTree &Root)	// освобождение памяти из-под дерева
{
	if (Root == nullptr)
		return;
	Delete(Root->Left);
	Delete(Root->Right);
	delete Root;
}
int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	PTree Root = nullptr, x;
	string data;
	Insert(Root, Root, "3");
	Insert(Root, Root, "2");
	Insert(Root, Root, "1");
	Print(Root, 0, fout);
	LL(Root);
	Print(Root, 0, fout);
	fin.close();
	fout.close();
	Delete(Root);	// освобождение памяти из-под дерева
	return 0;
}