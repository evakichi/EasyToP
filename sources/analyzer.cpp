#include <iostream>
#include <clang-c/Index.h>
using namespace std;

ostream &operator<<(ostream &stream, const CXString &str)
{
	stream << clang_getCString(str);
	clang_disposeString(str);
	return stream;
}


CXChildVisitResult cVisitForloop(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
	cout << clang_getCursorSpelling(cursor) << endl;
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
			switch (clang_getCursorKind(c))
			{
			case CXCursor_ForStmt:
				cout << "It's For loop!!" << endl;
				cout << clang_getCursorSpelling(c) << endl;
				clang_visitChildren(c,cVisitForloop,nullptr);
				break;
			case CXCursor_IntegerLiteral:
				cout << "It's IntegerLiteral!!" <<  clang_EvalResult_getAsInt(clang_Cursor_Evaluate(c)) <<endl;
				break;
			case CXCursor_BinaryOperator:
				cout << "It's binary operator!!" << clang_getTypeSpelling(clang_getCursorType(c)) << endl;
				break;
			case CXCursor_CompoundAssignOperator:
				cout << "It's compound operator!!" << clang_getCursorDisplayName(c) << clang_getTypeSpelling(clang_getCursorType(c)) << endl;
				break;
			case CXCursor_UnaryOperator:
				cout << "It's unary operator!!" << clang_getCursorDisplayName(c)  << endl;
				break;
			default:
				cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
					<< clang_getCursorKindSpelling(clang_getCursorKind(c))  
				 	<< "' parent '" << clang_getCursorSpelling(parent) << "'\n";
				break;
			}
			return CXChildVisit_Recurse;
		},
		nullptr);

	clang_disposeTranslationUnit(unit);
	clang_disposeIndex(index);
}
