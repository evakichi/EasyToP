#include <iostream>
#include <clang-c/Index.h>

using namespace std;

int main(int argc,char *argv[])
{
	CXIndex Idx = clang_createIndex(1,1);
	CXTranslationUnit TU = clang_createTranslationUnit(Idx, argv[1]);
	CXCursor cursor = clang_getTranslationUnitCursor(TU);

	CXType type = clang_getCursorType(cursor);
	CXString typeSpelling = clang_getTypeSpelling(type);
	cout << "test:" << clang_getCString(typeSpelling) << endl;

	clang_disposeTranslationUnit(TU);
	clang_disposeIndex(Idx);
	return 0;
}

