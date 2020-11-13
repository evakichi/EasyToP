#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/DeclVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

using namespace std;
using namespace clang;
using namespace clang::tooling;
using namespace llvm;

// ***************************************************************************
//          プリプロセッサからのコールバック処理
// ***************************************************************************

class PPCallbacksTracker : public PPCallbacks {
private:
    Preprocessor &PP;
public:
    PPCallbacksTracker(Preprocessor &pp) : PP(pp) {}
    void InclusionDirective(SourceLocation HashLoc,
                          const Token &IncludeTok,
                          StringRef FileName, 
                          bool IsAngled,
                          CharSourceRange FilenameRange,
                          const FileEntry *File,
                          StringRef SearchPath,
                          StringRef RelativePath,
                          const clang::Module *Imported)  {
        errs() << "InclusionDirective : ";
        if (File) {
            if (IsAngled)   errs() << "<" << File->getName() << ">\n";
            else            errs() << "\"" << File->getName() << "\"\n";
        } else {
            errs() << "not found file ";
            if (IsAngled)   errs() << "<" << FileName << ">\n";
            else            errs() << "\"" << FileName << "\"\n";
        }
    }
};

// ***************************************************************************
//          ASTウォークスルー
// ***************************************************************************

//llvm\tools\clang\include\clang\AST\DeclVisitor.hの36行目参照↓voidは指定できない。
class ExampleVisitor : public DeclVisitor<ExampleVisitor, bool> {
private:
    PrintingPolicy      Policy;
    const SourceManager &SM;
public:
    ExampleVisitor(CompilerInstance *CI) : Policy(PrintingPolicy(CI->getASTContext().getPrintingPolicy())),
                                           SM(CI->getASTContext().getSourceManager()) {
        Policy.Bool = 1;    // print()にてboolが_Boolと表示されないようにする
    }   //↑http://clang.llvm.org/doxygen/structclang_1_1PrintingPolicy.html#a4a4cff4f89cc3ec50381d9d44bedfdab
private:
    // インデント制御
    struct CIndentation {
        int             IndentLevel;
        CIndentation() : IndentLevel(0) { }
        void Indentation(raw_ostream &OS) const {
            for (int i=0; i < IndentLevel; ++i) OS << "  ";
        }
        // raw_ostream<<演算子定義
        friend raw_ostream &operator<<(raw_ostream &OS, const CIndentation &aCIndentation) {
            aCIndentation.Indentation(OS);
            return OS;
        }
    } indentation;
    class CIndentationHelper {
    private:
        ExampleVisitor  *parent;
    public:
        CIndentationHelper(ExampleVisitor *aExampleVisitor) : parent(aExampleVisitor) {
            parent->indentation.IndentLevel++;
        }
        ~CIndentationHelper() { parent->indentation.IndentLevel--; }
    };
    #define INDENTATION CIndentationHelper CIndentationHelper(this)
public:
    // DeclContextメンバーの1レベルの枚挙処理
    void EnumerateDecl(DeclContext *aDeclContext) {
        for (DeclContext::decl_iterator i = aDeclContext->decls_begin(), e = aDeclContext->decls_end(); i != e; i++) {
            Decl *D = *i;
            if (indentation.IndentLevel == 0) {
                errs() << "TopLevel : " << D->getDeclKindName();                                    // Declの型表示
                if (NamedDecl *N = dyn_cast<NamedDecl>(D))  errs() << " " << N->getNameAsString();  // NamedDeclなら名前表示
                errs() << " (" << D->getLocation().printToString(SM) << ")\n";                      // ソース上の場所表示
            }
            Visit(D);       // llvm\tools\clang\include\clang\AST\DeclVisitor.hの38行目
        }
    }

    // class/struct/unionの処理
    virtual bool VisitCXXRecordDecl(CXXRecordDecl *aCXXRecordDecl, bool aForce=false) {
        // 参照用(class foo;のような宣言)なら追跡しない
        if (!aCXXRecordDecl->isCompleteDefinition()) {
    return true;
        }

        // 名前無しなら表示しない(ただし、強制表示されたら表示する:Elaborated用)
        if (!aCXXRecordDecl->getIdentifier() && !aForce) {
    return true;
        }

        errs() << indentation << "<<<====================================\n";

        // TopLevelなら参考のためlibToolingでも表示する
        if (indentation.IndentLevel == 0) {
            aCXXRecordDecl->print(errs(), Policy);
            errs() << "\n";
            errs() << indentation << "--------------------\n";
        }

        // クラス定義の処理
        errs() << indentation << "CXXRecordDecl : " << aCXXRecordDecl->getNameAsString() << " {\n";
        {
            INDENTATION;

            // 基底クラスの枚挙処理
            for (CXXRecordDecl::base_class_iterator Base = aCXXRecordDecl->bases_begin(), BaseEnd = aCXXRecordDecl->bases_end();
                 Base != BaseEnd;
                 ++Base) {                                          // ↓型名を取り出す(例えば、Policy.Bool=0の時、bool型は"_Bool"となる)
                errs() << indentation << "Base : " << Base->getType().getAsString(Policy) << "\n";
            }

            // メンバーの枚挙処理
            EnumerateDecl(aCXXRecordDecl);
        }
        errs() << indentation << "}\n";
        errs() << indentation << "====================================>>>\n";
        return true;
    }

    // メンバー変数の処理
    virtual bool VisitFieldDecl(FieldDecl *aFieldDecl) {
        // 名前無しclass/struct/unionでメンバー変数が直接定義されている時の対応
        CXXRecordDecl *R=NULL;      // 名前無しの時、内容を表示するためにCXXRecordDeclをポイントする
        const clang::Type *T = aFieldDecl->getType().split().Ty;
        if (T->getTypeClass() == clang::Type::Elaborated) {
            R = cast<ElaboratedType>(T)->getNamedType()->getAsCXXRecordDecl();
            if (R && (R->getIdentifier()))  R = NULL;
        }
        // 内容表示
        if (R) {
            errs() << indentation << "FieldDecl : <no-name-type> " << aFieldDecl->getNameAsString() << "\n";
            VisitCXXRecordDecl(R, true);    // 名前無しclass/struct/unionの内容表示
        } else {
            errs() << indentation << "FieldDecl : " << aFieldDecl->getType().getAsString(Policy) << " " << aFieldDecl->getNameAsString() << "\n";
        }
        return true;
    }

    // namespaceの処理(配下を追跡する)
    virtual bool VisitNamespaceDecl(NamespaceDecl *aNamespaceDecl) {
        errs() << "NamespaceDecl : namespace " << aNamespaceDecl->getNameAsString() << " {\n";
        EnumerateDecl(aNamespaceDecl);
        errs() << "} end of namespace " << aNamespaceDecl->getNameAsString() << "\n";
        return true;
    }

    // extern "C"/"C++"の処理(配下を追跡する)
    virtual bool VisitLinkageSpecDecl(LinkageSpecDecl*aLinkageSpecDecl) {
        string lang;
        switch (aLinkageSpecDecl->getLanguage()) {
        case LinkageSpecDecl::lang_c:   lang="C"; break;
        case LinkageSpecDecl::lang_cxx: lang="C++"; break;
        }
        errs() << "LinkageSpecDecl : extern \"" << lang << "\" {\n";
        EnumerateDecl(aLinkageSpecDecl);
        errs() << "} end of extern \"" << lang << "\"\n";
        return true;
    }
};

// ***************************************************************************
//          定番の処理
// ***************************************************************************

class ExampleASTConsumer : public ASTConsumer {
private:
    ExampleVisitor *visitor; // doesn't have to be private
public:
    explicit ExampleASTConsumer(CompilerInstance *CI) : visitor(new ExampleVisitor(CI)) {
        // プリプロセッサからのコールバック登録
        Preprocessor &PP = CI->getPreprocessor();
        PP.addPPCallbacks(make_unique<PPCallbacksTracker>(PP));
    }
    // AST解析結果の受取
    virtual void HandleTranslationUnit(ASTContext &Context) {
        errs() << "\n\nHandleTranslationUnit()\n";
        visitor->EnumerateDecl(Context.getTranslationUnitDecl());
    }
};

class ExampleFrontendAction : public SyntaxOnlyAction /*ASTFrontendAction*/ {
public:
    virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) {
        return make_unique<ExampleASTConsumer>(&CI); // pass CI pointer to ASTConsumer
    }
};

static cl::OptionCategory MyToolCategory("My tool options");
int main(int argc, const char **argv)
{
    CommonOptionsParser op(argc, argv, MyToolCategory);
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());
    return Tool.run(newFrontendActionFactory<ExampleFrontendAction>().get());
}


//clang++ $(llvm-config --cppflags --cxxflags --ldflags)  parser2.cpp   -L$(llvm-config --libdir) -lclang -lclang-cpp $(llvm-config --libs --system-libs)
//Original from https://qiita.com/Chironian/items/6021d35bf2750341d80c