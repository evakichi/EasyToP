#include <iostream>
#include <clang-c/Index.h>
using namespace std;

ostream &operator<<(ostream &stream, const CXString &str)
{
	stream << clang_getCString(str);
	clang_disposeString(str);
	return stream;
}


CXChildVisitResult cvisit(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
	cout << clang_getCursorSpelling(cursor) << endl;
	cout << clang_getCursorKindSpelling(clang_getCursorKind(cursor)) << endl;
	return CXChildVisit_Recurse;
}
int main(int argc, char *argv[])
{
	CXIndex index = clang_createIndex(0, 0);
	CXTranslationUnit unit = clang_parseTranslationUnit(
		index,
		argv[1], nullptr, 0,
		nullptr, 0,
		CXTranslationUnit_None);
	if (unit == nullptr)
	{
		cerr << "Unable to parse translation unit. Quitting." << endl;
		exit(-1);
	}

	CXCursor cursor = clang_getTranslationUnitCursor(unit);
	clang_visitChildren(
		cursor,
		[](CXCursor c, CXCursor parent, CXClientData client_data) {
			if (clang_getCursorKind(c) == CXCursor_ForStmt)
			{
				cout << "It's For loop!!" << endl;
				cout << clang_getCursorSpelling(c) << endl;
				clang_visitChildren(c,cvisit,nullptr);
			}				
			else
				cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
					 << clang_getCursorKindSpelling(clang_getCursorKind(c))  
				 	<< "' parent '" << clang_getCursorSpelling(parent) << "'\n";
			return CXChildVisit_Recurse;
		},
		nullptr);

	clang_disposeTranslationUnit(unit);
	clang_disposeIndex(index);
}
