typedef struct {
  const void *data;
  unsigned private_flags;
} CXString;

typedef struct {
  CXString *Strings;
  unsigned Count;
} CXStringSet;

enum CXCursorKind {
  /* Declarations */
  /**
   * A declaration whose specific kind is not exposed via this
   * interface.
   *
   * Unexposed declarations have the same operations as any other kind
   * of declaration; one can extract their location information,
   * spelling, find their definitions, etc. However, the specific kind
   * of the declaration is not reported.
   */
  CXCursor_UnexposedDecl = 1,
  /** A C or C++ struct. */
  CXCursor_StructDecl = 2,
  /** A C or C++ union. */
  CXCursor_UnionDecl = 3,
  /** A C++ class. */
  CXCursor_ClassDecl = 4,
  /** An enumeration. */
  CXCursor_EnumDecl = 5,
  /**
   * A field (in C) or non-static data member (in C++) in a
   * struct, union, or C++ class.
   */
  CXCursor_FieldDecl = 6,
  /** An enumerator constant. */
  CXCursor_EnumConstantDecl = 7,
  /** A function. */
  CXCursor_FunctionDecl = 8,
  /** A variable. */
  CXCursor_VarDecl = 9,
  /** A function or method parameter. */
  CXCursor_ParmDecl = 10,
  /** An Objective-C \@interface. */
  CXCursor_ObjCInterfaceDecl = 11,
  /** An Objective-C \@interface for a category. */
  CXCursor_ObjCCategoryDecl = 12,
  /** An Objective-C \@protocol declaration. */
  CXCursor_ObjCProtocolDecl = 13,
  /** An Objective-C \@property declaration. */
  CXCursor_ObjCPropertyDecl = 14,
  /** An Objective-C instance variable. */
  CXCursor_ObjCIvarDecl = 15,
  /** An Objective-C instance method. */
  CXCursor_ObjCInstanceMethodDecl = 16,
  /** An Objective-C class method. */
  CXCursor_ObjCClassMethodDecl = 17,
  /** An Objective-C \@implementation. */
  CXCursor_ObjCImplementationDecl = 18,
  /** An Objective-C \@implementation for a category. */
  CXCursor_ObjCCategoryImplDecl = 19,
  /** A typedef. */
  CXCursor_TypedefDecl = 20,
  /** A C++ class method. */
  CXCursor_CXXMethod = 21,
  /** A C++ namespace. */
  CXCursor_Namespace = 22,
  /** A linkage specification, e.g. 'extern "C"'. */
  CXCursor_LinkageSpec = 23,
  /** A C++ constructor. */
  CXCursor_Constructor = 24,
  /** A C++ destructor. */
  CXCursor_Destructor = 25,
  /** A C++ conversion function. */
  CXCursor_ConversionFunction = 26,
  /** A C++ template type parameter. */
  CXCursor_TemplateTypeParameter = 27,
  /** A C++ non-type template parameter. */
  CXCursor_NonTypeTemplateParameter = 28,
  /** A C++ template template parameter. */
  CXCursor_TemplateTemplateParameter = 29,
  /** A C++ function template. */
  CXCursor_FunctionTemplate = 30,
  /** A C++ class template. */
  CXCursor_ClassTemplate = 31,
  /** A C++ class template partial specialization. */
  CXCursor_ClassTemplatePartialSpecialization = 32,
  /** A C++ namespace alias declaration. */
  CXCursor_NamespaceAlias = 33,
  /** A C++ using directive. */
  CXCursor_UsingDirective = 34,
  /** A C++ using declaration. */
  CXCursor_UsingDeclaration = 35,
  /** A C++ alias declaration */
  CXCursor_TypeAliasDecl = 36,
  /** An Objective-C \@synthesize definition. */
  CXCursor_ObjCSynthesizeDecl = 37,
  /** An Objective-C \@dynamic definition. */
  CXCursor_ObjCDynamicDecl = 38,
  /** An access specifier. */
  CXCursor_CXXAccessSpecifier = 39,

  CXCursor_FirstDecl = CXCursor_UnexposedDecl,
  CXCursor_LastDecl = CXCursor_CXXAccessSpecifier,

  /* References */
  CXCursor_FirstRef = 40, /* Decl references */
  CXCursor_ObjCSuperClassRef = 40,
  CXCursor_ObjCProtocolRef = 41,
  CXCursor_ObjCClassRef = 42,
  /**
   * A reference to a type declaration.
   *
   * A type reference occurs anywhere where a type is named but not
   * declared. For example, given:
   *
   * \code
   * typedef unsigned size_type;
   * size_type size;
   * \endcode
   *
   * The typedef is a declaration of size_type (CXCursor_TypedefDecl),
   * while the type of the variable "size" is referenced. The cursor
   * referenced by the type of size is the typedef for size_type.
   */
  CXCursor_TypeRef = 43,
  CXCursor_CXXBaseSpecifier = 44,
  /**
   * A reference to a class template, function template, template
   * template parameter, or class template partial specialization.
   */
  CXCursor_TemplateRef = 45,
  /**
   * A reference to a namespace or namespace alias.
   */
  CXCursor_NamespaceRef = 46,
  /**
   * A reference to a member of a struct, union, or class that occurs in
   * some non-expression context, e.g., a designated initializer.
   */
  CXCursor_MemberRef = 47,
  /**
   * A reference to a labeled statement.
   *
   * This cursor kind is used to describe the jump to "start_over" in the
   * goto statement in the following example:
   *
   * \code
   *   start_over:
   *     ++counter;
   *
   *     goto start_over;
   * \endcode
   *
   * A label reference cursor refers to a label statement.
   */
  CXCursor_LabelRef = 48,

  /**
   * A reference to a set of overloaded functions or function templates
   * that has not yet been resolved to a specific function or function template.
   *
   * An overloaded declaration reference cursor occurs in C++ templates where
   * a dependent name refers to a function. For example:
   *
   * \code
   * template<typename T> void swap(T&, T&);
   *
   * struct X { ... };
   * void swap(X&, X&);
   *
   * template<typename T>
   * void reverse(T* first, T* last) {
   *   while (first < last - 1) {
   *     swap(*first, *--last);
   *     ++first;
   *   }
   * }
   *
   * struct Y { };
   * void swap(Y&, Y&);
   * \endcode
   *
   * Here, the identifier "swap" is associated with an overloaded declaration
   * reference. In the template definition, "swap" refers to either of the two
   * "swap" functions declared above, so both results will be available. At
   * instantiation time, "swap" may also refer to other functions found via
   * argument-dependent lookup (e.g., the "swap" function at the end of the
   * example).
   *
   * The functions \c clang_getNumOverloadedDecls() and
   * \c clang_getOverloadedDecl() can be used to retrieve the definitions
   * referenced by this cursor.
   */
  CXCursor_OverloadedDeclRef = 49,

  /**
   * A reference to a variable that occurs in some non-expression
   * context, e.g., a C++ lambda capture list.
   */
  CXCursor_VariableRef = 50,

  CXCursor_LastRef = CXCursor_VariableRef,

  /* Error conditions */
  CXCursor_FirstInvalid = 70,
  CXCursor_InvalidFile = 70,
  CXCursor_NoDeclFound = 71,
  CXCursor_NotImplemented = 72,
  CXCursor_InvalidCode = 73,
  CXCursor_LastInvalid = CXCursor_InvalidCode,

  /* Expressions */
  CXCursor_FirstExpr = 100,

  /**
   * An expression whose specific kind is not exposed via this
   * interface.
   *
   * Unexposed expressions have the same operations as any other kind
   * of expression; one can extract their location information,
   * spelling, children, etc. However, the specific kind of the
   * expression is not reported.
   */
  CXCursor_UnexposedExpr = 100,

  /**
   * An expression that refers to some value declaration, such
   * as a function, variable, or enumerator.
   */
  CXCursor_DeclRefExpr = 101,

  /**
   * An expression that refers to a member of a struct, union,
   * class, Objective-C class, etc.
   */
  CXCursor_MemberRefExpr = 102,

  /** An expression that calls a function. */
  CXCursor_CallExpr = 103,

  /** An expression that sends a message to an Objective-C
   object or class. */
  CXCursor_ObjCMessageExpr = 104,

  /** An expression that represents a block literal. */
  CXCursor_BlockExpr = 105,

  /** An integer literal.
   */
  CXCursor_IntegerLiteral = 106,

  /** A floating point number literal.
   */
  CXCursor_FloatingLiteral = 107,

  /** An imaginary number literal.
   */
  CXCursor_ImaginaryLiteral = 108,

  /** A string literal.
   */
  CXCursor_StringLiteral = 109,

  /** A character literal.
   */
  CXCursor_CharacterLiteral = 110,

  /** A parenthesized expression, e.g. "(1)".
   *
   * This AST node is only formed if full location information is requested.
   */
  CXCursor_ParenExpr = 111,

  /** This represents the unary-expression's (except sizeof and
   * alignof).
   */
  CXCursor_UnaryOperator = 112,

  /** [C99 6.5.2.1] Array Subscripting.
   */
  CXCursor_ArraySubscriptExpr = 113,

  /** A builtin binary operation expression such as "x + y" or
   * "x <= y".
   */
  CXCursor_BinaryOperator = 114,

  /** Compound assignment such as "+=".
   */
  CXCursor_CompoundAssignOperator = 115,

  /** The ?: ternary operator.
   */
  CXCursor_ConditionalOperator = 116,

  /** An explicit cast in C (C99 6.5.4) or a C-style cast in C++
   * (C++ [expr.cast]), which uses the syntax (Type)expr.
   *
   * For example: (int)f.
   */
  CXCursor_CStyleCastExpr = 117,

  /** [C99 6.5.2.5]
   */
  CXCursor_CompoundLiteralExpr = 118,

  /** Describes an C or C++ initializer list.
   */
  CXCursor_InitListExpr = 119,

  /** The GNU address of label extension, representing &&label.
   */
  CXCursor_AddrLabelExpr = 120,

  /** This is the GNU Statement Expression extension: ({int X=4; X;})
   */
  CXCursor_StmtExpr = 121,

  /** Represents a C11 generic selection.
   */
  CXCursor_GenericSelectionExpr = 122,

  /** Implements the GNU __null extension, which is a name for a null
   * pointer constant that has integral type (e.g., int or long) and is the same
   * size and alignment as a pointer.
   *
   * The __null extension is typically only used by system headers, which define
   * NULL as __null in C++ rather than using 0 (which is an integer that may not
   * match the size of a pointer).
   */
  CXCursor_GNUNullExpr = 123,

  /** C++'s static_cast<> expression.
   */
  CXCursor_CXXStaticCastExpr = 124,

  /** C++'s dynamic_cast<> expression.
   */
  CXCursor_CXXDynamicCastExpr = 125,

  /** C++'s reinterpret_cast<> expression.
   */
  CXCursor_CXXReinterpretCastExpr = 126,

  /** C++'s const_cast<> expression.
   */
  CXCursor_CXXConstCastExpr = 127,

  /** Represents an explicit C++ type conversion that uses "functional"
   * notion (C++ [expr.type.conv]).
   *
   * Example:
   * \code
   *   x = int(0.5);
   * \endcode
   */
  CXCursor_CXXFunctionalCastExpr = 128,

  /** A C++ typeid expression (C++ [expr.typeid]).
   */
  CXCursor_CXXTypeidExpr = 129,

  /** [C++ 2.13.5] C++ Boolean Literal.
   */
  CXCursor_CXXBoolLiteralExpr = 130,

  /** [C++0x 2.14.7] C++ Pointer Literal.
   */
  CXCursor_CXXNullPtrLiteralExpr = 131,

  /** Represents the "this" expression in C++
   */
  CXCursor_CXXThisExpr = 132,

  /** [C++ 15] C++ Throw Expression.
   *
   * This handles 'throw' and 'throw' assignment-expression. When
   * assignment-expression isn't present, Op will be null.
   */
  CXCursor_CXXThrowExpr = 133,

  /** A new expression for memory allocation and constructor calls, e.g:
   * "new CXXNewExpr(foo)".
   */
  CXCursor_CXXNewExpr = 134,

  /** A delete expression for memory deallocation and destructor calls,
   * e.g. "delete[] pArray".
   */
  CXCursor_CXXDeleteExpr = 135,

  /** A unary expression. (noexcept, sizeof, or other traits)
   */
  CXCursor_UnaryExpr = 136,

  /** An Objective-C string literal i.e. @"foo".
   */
  CXCursor_ObjCStringLiteral = 137,

  /** An Objective-C \@encode expression.
   */
  CXCursor_ObjCEncodeExpr = 138,

  /** An Objective-C \@selector expression.
   */
  CXCursor_ObjCSelectorExpr = 139,

  /** An Objective-C \@protocol expression.
   */
  CXCursor_ObjCProtocolExpr = 140,

  /** An Objective-C "bridged" cast expression, which casts between
   * Objective-C pointers and C pointers, transferring ownership in the process.
   *
   * \code
   *   NSString *str = (__bridge_transfer NSString *)CFCreateString();
   * \endcode
   */
  CXCursor_ObjCBridgedCastExpr = 141,

  /** Represents a C++0x pack expansion that produces a sequence of
   * expressions.
   *
   * A pack expansion expression contains a pattern (which itself is an
   * expression) followed by an ellipsis. For example:
   *
   * \code
   * template<typename F, typename ...Types>
   * void forward(F f, Types &&...args) {
   *  f(static_cast<Types&&>(args)...);
   * }
   * \endcode
   */
  CXCursor_PackExpansionExpr = 142,

  /** Represents an expression that computes the length of a parameter
   * pack.
   *
   * \code
   * template<typename ...Types>
   * struct count {
   *   static const unsigned value = sizeof...(Types);
   * };
   * \endcode
   */
  CXCursor_SizeOfPackExpr = 143,

  /* Represents a C++ lambda expression that produces a local function
   * object.
   *
   * \code
   * void abssort(float *x, unsigned N) {
   *   std::sort(x, x + N,
   *             [](float a, float b) {
   *               return std::abs(a) < std::abs(b);
   *             });
   * }
   * \endcode
   */
  CXCursor_LambdaExpr = 144,

  /** Objective-c Boolean Literal.
   */
  CXCursor_ObjCBoolLiteralExpr = 145,

  /** Represents the "self" expression in an Objective-C method.
   */
  CXCursor_ObjCSelfExpr = 146,

  /** OpenMP 5.0 [2.1.5, Array Section].
   */
  CXCursor_OMPArraySectionExpr = 147,

  /** Represents an @available(...) check.
   */
  CXCursor_ObjCAvailabilityCheckExpr = 148,

  /**
   * Fixed point literal
   */
  CXCursor_FixedPointLiteral = 149,

  /** OpenMP 5.0 [2.1.4, Array Shaping].
   */
  CXCursor_OMPArrayShapingExpr = 150,

  /**
   * OpenMP 5.0 [2.1.6 Iterators]
   */
  CXCursor_OMPIteratorExpr = 151,

  /** OpenCL's addrspace_cast<> expression.
   */
  CXCursor_CXXAddrspaceCastExpr = 152,

  CXCursor_LastExpr = CXCursor_CXXAddrspaceCastExpr,

  /* Statements */
  CXCursor_FirstStmt = 200,
  /**
   * A statement whose specific kind is not exposed via this
   * interface.
   *
   * Unexposed statements have the same operations as any other kind of
   * statement; one can extract their location information, spelling,
   * children, etc. However, the specific kind of the statement is not
   * reported.
   */
  CXCursor_UnexposedStmt = 200,

  /** A labelled statement in a function.
   *
   * This cursor kind is used to describe the "start_over:" label statement in
   * the following example:
   *
   * \code
   *   start_over:
   *     ++counter;
   * \endcode
   *
   */
  CXCursor_LabelStmt = 201,

  /** A group of statements like { stmt stmt }.
   *
   * This cursor kind is used to describe compound statements, e.g. function
   * bodies.
   */
  CXCursor_CompoundStmt = 202,

  /** A case statement.
   */
  CXCursor_CaseStmt = 203,

  /** A default statement.
   */
  CXCursor_DefaultStmt = 204,

  /** An if statement
   */
  CXCursor_IfStmt = 205,

  /** A switch statement.
   */
  CXCursor_SwitchStmt = 206,

  /** A while statement.
   */
  CXCursor_WhileStmt = 207,

  /** A do statement.
   */
  CXCursor_DoStmt = 208,

  /** A for statement.
   */
  CXCursor_ForStmt = 209,

  /** A goto statement.
   */
  CXCursor_GotoStmt = 210,

  /** An indirect goto statement.
   */
  CXCursor_IndirectGotoStmt = 211,

  /** A continue statement.
   */
  CXCursor_ContinueStmt = 212,

  /** A break statement.
   */
  CXCursor_BreakStmt = 213,

  /** A return statement.
   */
  CXCursor_ReturnStmt = 214,

  /** A GCC inline assembly statement extension.
   */
  CXCursor_GCCAsmStmt = 215,
  CXCursor_AsmStmt = CXCursor_GCCAsmStmt,

  /** Objective-C's overall \@try-\@catch-\@finally statement.
   */
  CXCursor_ObjCAtTryStmt = 216,

  /** Objective-C's \@catch statement.
   */
  CXCursor_ObjCAtCatchStmt = 217,

  /** Objective-C's \@finally statement.
   */
  CXCursor_ObjCAtFinallyStmt = 218,

  /** Objective-C's \@throw statement.
   */
  CXCursor_ObjCAtThrowStmt = 219,

  /** Objective-C's \@synchronized statement.
   */
  CXCursor_ObjCAtSynchronizedStmt = 220,

  /** Objective-C's autorelease pool statement.
   */
  CXCursor_ObjCAutoreleasePoolStmt = 221,

  /** Objective-C's collection statement.
   */
  CXCursor_ObjCForCollectionStmt = 222,

  /** C++'s catch statement.
   */
  CXCursor_CXXCatchStmt = 223,

  /** C++'s try statement.
   */
  CXCursor_CXXTryStmt = 224,

  /** C++'s for (* : *) statement.
   */
  CXCursor_CXXForRangeStmt = 225,

  /** Windows Structured Exception Handling's try statement.
   */
  CXCursor_SEHTryStmt = 226,

  /** Windows Structured Exception Handling's except statement.
   */
  CXCursor_SEHExceptStmt = 227,

  /** Windows Structured Exception Handling's finally statement.
   */
  CXCursor_SEHFinallyStmt = 228,

  /** A MS inline assembly statement extension.
   */
  CXCursor_MSAsmStmt = 229,

  /** The null statement ";": C99 6.8.3p3.
   *
   * This cursor kind is used to describe the null statement.
   */
  CXCursor_NullStmt = 230,

  /** Adaptor class for mixing declarations with statements and
   * expressions.
   */
  CXCursor_DeclStmt = 231,

  /** OpenMP parallel directive.
   */
  CXCursor_OMPParallelDirective = 232,

  /** OpenMP SIMD directive.
   */
  CXCursor_OMPSimdDirective = 233,

  /** OpenMP for directive.
   */
  CXCursor_OMPForDirective = 234,

  /** OpenMP sections directive.
   */
  CXCursor_OMPSectionsDirective = 235,

  /** OpenMP section directive.
   */
  CXCursor_OMPSectionDirective = 236,

  /** OpenMP single directive.
   */
  CXCursor_OMPSingleDirective = 237,

  /** OpenMP parallel for directive.
   */
  CXCursor_OMPParallelForDirective = 238,

  /** OpenMP parallel sections directive.
   */
  CXCursor_OMPParallelSectionsDirective = 239,

  /** OpenMP task directive.
   */
  CXCursor_OMPTaskDirective = 240,

  /** OpenMP master directive.
   */
  CXCursor_OMPMasterDirective = 241,

  /** OpenMP critical directive.
   */
  CXCursor_OMPCriticalDirective = 242,

  /** OpenMP taskyield directive.
   */
  CXCursor_OMPTaskyieldDirective = 243,

  /** OpenMP barrier directive.
   */
  CXCursor_OMPBarrierDirective = 244,

  /** OpenMP taskwait directive.
   */
  CXCursor_OMPTaskwaitDirective = 245,

  /** OpenMP flush directive.
   */
  CXCursor_OMPFlushDirective = 246,

  /** Windows Structured Exception Handling's leave statement.
   */
  CXCursor_SEHLeaveStmt = 247,

  /** OpenMP ordered directive.
   */
  CXCursor_OMPOrderedDirective = 248,

  /** OpenMP atomic directive.
   */
  CXCursor_OMPAtomicDirective = 249,

  /** OpenMP for SIMD directive.
   */
  CXCursor_OMPForSimdDirective = 250,

  /** OpenMP parallel for SIMD directive.
   */
  CXCursor_OMPParallelForSimdDirective = 251,

  /** OpenMP target directive.
   */
  CXCursor_OMPTargetDirective = 252,

  /** OpenMP teams directive.
   */
  CXCursor_OMPTeamsDirective = 253,

  /** OpenMP taskgroup directive.
   */
  CXCursor_OMPTaskgroupDirective = 254,

  /** OpenMP cancellation point directive.
   */
  CXCursor_OMPCancellationPointDirective = 255,

  /** OpenMP cancel directive.
   */
  CXCursor_OMPCancelDirective = 256,

  /** OpenMP target data directive.
   */
  CXCursor_OMPTargetDataDirective = 257,

  /** OpenMP taskloop directive.
   */
  CXCursor_OMPTaskLoopDirective = 258,

  /** OpenMP taskloop simd directive.
   */
  CXCursor_OMPTaskLoopSimdDirective = 259,

  /** OpenMP distribute directive.
   */
  CXCursor_OMPDistributeDirective = 260,

  /** OpenMP target enter data directive.
   */
  CXCursor_OMPTargetEnterDataDirective = 261,

  /** OpenMP target exit data directive.
   */
  CXCursor_OMPTargetExitDataDirective = 262,

  /** OpenMP target parallel directive.
   */
  CXCursor_OMPTargetParallelDirective = 263,

  /** OpenMP target parallel for directive.
   */
  CXCursor_OMPTargetParallelForDirective = 264,

  /** OpenMP target update directive.
   */
  CXCursor_OMPTargetUpdateDirective = 265,

  /** OpenMP distribute parallel for directive.
   */
  CXCursor_OMPDistributeParallelForDirective = 266,

  /** OpenMP distribute parallel for simd directive.
   */
  CXCursor_OMPDistributeParallelForSimdDirective = 267,

  /** OpenMP distribute simd directive.
   */
  CXCursor_OMPDistributeSimdDirective = 268,

  /** OpenMP target parallel for simd directive.
   */
  CXCursor_OMPTargetParallelForSimdDirective = 269,

  /** OpenMP target simd directive.
   */
  CXCursor_OMPTargetSimdDirective = 270,

  /** OpenMP teams distribute directive.
   */
  CXCursor_OMPTeamsDistributeDirective = 271,

  /** OpenMP teams distribute simd directive.
   */
  CXCursor_OMPTeamsDistributeSimdDirective = 272,

  /** OpenMP teams distribute parallel for simd directive.
   */
  CXCursor_OMPTeamsDistributeParallelForSimdDirective = 273,

  /** OpenMP teams distribute parallel for directive.
   */
  CXCursor_OMPTeamsDistributeParallelForDirective = 274,

  /** OpenMP target teams directive.
   */
  CXCursor_OMPTargetTeamsDirective = 275,

  /** OpenMP target teams distribute directive.
   */
  CXCursor_OMPTargetTeamsDistributeDirective = 276,

  /** OpenMP target teams distribute parallel for directive.
   */
  CXCursor_OMPTargetTeamsDistributeParallelForDirective = 277,

  /** OpenMP target teams distribute parallel for simd directive.
   */
  CXCursor_OMPTargetTeamsDistributeParallelForSimdDirective = 278,

  /** OpenMP target teams distribute simd directive.
   */
  CXCursor_OMPTargetTeamsDistributeSimdDirective = 279,

  /** C++2a std::bit_cast expression.
   */
  CXCursor_BuiltinBitCastExpr = 280,

  /** OpenMP master taskloop directive.
   */
  CXCursor_OMPMasterTaskLoopDirective = 281,

  /** OpenMP parallel master taskloop directive.
   */
  CXCursor_OMPParallelMasterTaskLoopDirective = 282,

  /** OpenMP master taskloop simd directive.
   */
  CXCursor_OMPMasterTaskLoopSimdDirective = 283,

  /** OpenMP parallel master taskloop simd directive.
   */
  CXCursor_OMPParallelMasterTaskLoopSimdDirective = 284,

  /** OpenMP parallel master directive.
   */
  CXCursor_OMPParallelMasterDirective = 285,

  /** OpenMP depobj directive.
   */
  CXCursor_OMPDepobjDirective = 286,

  /** OpenMP scan directive.
   */
  CXCursor_OMPScanDirective = 287,

  /** OpenMP tile directive.
   */
  CXCursor_OMPTileDirective = 288,

  /** OpenMP canonical loop.
   */
  CXCursor_OMPCanonicalLoop = 289,

  /** OpenMP interop directive.
   */
  CXCursor_OMPInteropDirective = 290,

  /** OpenMP dispatch directive.
   */
  CXCursor_OMPDispatchDirective = 291,

  /** OpenMP masked directive.
   */
  CXCursor_OMPMaskedDirective = 292,

  /** OpenMP unroll directive.
   */
  CXCursor_OMPUnrollDirective = 293,

  /** OpenMP metadirective directive.
   */
  CXCursor_OMPMetaDirective = 294,

  /** OpenMP loop directive.
   */
  CXCursor_OMPGenericLoopDirective = 295,

  CXCursor_LastStmt = CXCursor_OMPGenericLoopDirective,

  /**
   * Cursor that represents the translation unit itself.
   *
   * The translation unit cursor exists primarily to act as the root
   * cursor for traversing the contents of a translation unit.
   */
  CXCursor_TranslationUnit = 300,

  /* Attributes */
  CXCursor_FirstAttr = 400,
  /**
   * An attribute whose specific kind is not exposed via this
   * interface.
   */
  CXCursor_UnexposedAttr = 400,

  CXCursor_IBActionAttr = 401,
  CXCursor_IBOutletAttr = 402,
  CXCursor_IBOutletCollectionAttr = 403,
  CXCursor_CXXFinalAttr = 404,
  CXCursor_CXXOverrideAttr = 405,
  CXCursor_AnnotateAttr = 406,
  CXCursor_AsmLabelAttr = 407,
  CXCursor_PackedAttr = 408,
  CXCursor_PureAttr = 409,
  CXCursor_ConstAttr = 410,
  CXCursor_NoDuplicateAttr = 411,
  CXCursor_CUDAConstantAttr = 412,
  CXCursor_CUDADeviceAttr = 413,
  CXCursor_CUDAGlobalAttr = 414,
  CXCursor_CUDAHostAttr = 415,
  CXCursor_CUDASharedAttr = 416,
  CXCursor_VisibilityAttr = 417,
  CXCursor_DLLExport = 418,
  CXCursor_DLLImport = 419,
  CXCursor_NSReturnsRetained = 420,
  CXCursor_NSReturnsNotRetained = 421,
  CXCursor_NSReturnsAutoreleased = 422,
  CXCursor_NSConsumesSelf = 423,
  CXCursor_NSConsumed = 424,
  CXCursor_ObjCException = 425,
  CXCursor_ObjCNSObject = 426,
  CXCursor_ObjCIndependentClass = 427,
  CXCursor_ObjCPreciseLifetime = 428,
  CXCursor_ObjCReturnsInnerPointer = 429,
  CXCursor_ObjCRequiresSuper = 430,
  CXCursor_ObjCRootClass = 431,
  CXCursor_ObjCSubclassingRestricted = 432,
  CXCursor_ObjCExplicitProtocolImpl = 433,
  CXCursor_ObjCDesignatedInitializer = 434,
  CXCursor_ObjCRuntimeVisible = 435,
  CXCursor_ObjCBoxable = 436,
  CXCursor_FlagEnum = 437,
  CXCursor_ConvergentAttr = 438,
  CXCursor_WarnUnusedAttr = 439,
  CXCursor_WarnUnusedResultAttr = 440,
  CXCursor_AlignedAttr = 441,
  CXCursor_LastAttr = CXCursor_AlignedAttr,

  /* Preprocessing */
  CXCursor_PreprocessingDirective = 500,
  CXCursor_MacroDefinition = 501,
  CXCursor_MacroExpansion = 502,
  CXCursor_MacroInstantiation = CXCursor_MacroExpansion,
  CXCursor_InclusionDirective = 503,
  CXCursor_FirstPreprocessing = CXCursor_PreprocessingDirective,
  CXCursor_LastPreprocessing = CXCursor_InclusionDirective,

  /* Extra Declarations */
  /**
   * A module import declaration.
   */
  CXCursor_ModuleImportDecl = 600,
  CXCursor_TypeAliasTemplateDecl = 601,
  /**
   * A static_assert or _Static_assert node
   */
  CXCursor_StaticAssert = 602,
  /**
   * a friend declaration.
   */
  CXCursor_FriendDecl = 603,
  CXCursor_FirstExtraDecl = CXCursor_ModuleImportDecl,
  CXCursor_LastExtraDecl = CXCursor_FriendDecl,

  /**
   * A code completion overload candidate.
   */
  CXCursor_OverloadCandidate = 700
};

typedef struct {
  enum CXCursorKind kind;
  int xdata;
  const void *data[3];
} CXCursor;

typedef void *CXIndex;

typedef struct CXTargetInfoImpl *CXTargetInfo;

typedef struct CXTranslationUnitImpl *CXTranslationUnit;

typedef void *CXClientData;

struct CXUnsavedFile {
  const char *Filename;
  const char *Contents;
  unsigned long Length;
};

typedef void *CXPrintingPolicy;

enum CXChildVisitResult {
  /**
   * Terminates the cursor traversal.
   */
  CXChildVisit_Break,
  /**
   * Continues the cursor traversal with the next sibling of
   * the cursor just visited, without visiting its children.
   */
  CXChildVisit_Continue,
  /**
   * Recursively traverse the children of this cursor, using
   * the same visitor and client data.
   */
  CXChildVisit_Recurse
};

typedef struct {
  const void *ptr_data[2];
  unsigned int_data;
} CXSourceLocation;

/**
 * Identifies a half-open character range in the source code.
 *
 * Use clang_getRangeStart() and clang_getRangeEnd() to retrieve the
 * starting and end locations from a source range, respectively.
 */
typedef struct {
  const void *ptr_data[2];
  unsigned begin_int_data;
  unsigned end_int_data;
} CXSourceRange;

typedef void *CXFile;

enum CXTypeKind {
  /**
   * Represents an invalid type (e.g., where no type is available).
   */
  CXType_Invalid = 0,

  /**
   * A type whose specific kind is not exposed via this
   * interface.
   */
  CXType_Unexposed = 1,

  /* Builtin types */
  CXType_Void = 2,
  CXType_Bool = 3,
  CXType_Char_U = 4,
  CXType_UChar = 5,
  CXType_Char16 = 6,
  CXType_Char32 = 7,
  CXType_UShort = 8,
  CXType_UInt = 9,
  CXType_ULong = 10,
  CXType_ULongLong = 11,
  CXType_UInt128 = 12,
  CXType_Char_S = 13,
  CXType_SChar = 14,
  CXType_WChar = 15,
  CXType_Short = 16,
  CXType_Int = 17,
  CXType_Long = 18,
  CXType_LongLong = 19,
  CXType_Int128 = 20,
  CXType_Float = 21,
  CXType_Double = 22,
  CXType_LongDouble = 23,
  CXType_NullPtr = 24,
  CXType_Overload = 25,
  CXType_Dependent = 26,
  CXType_ObjCId = 27,
  CXType_ObjCClass = 28,
  CXType_ObjCSel = 29,
  CXType_Float128 = 30,
  CXType_Half = 31,
  CXType_Float16 = 32,
  CXType_ShortAccum = 33,
  CXType_Accum = 34,
  CXType_LongAccum = 35,
  CXType_UShortAccum = 36,
  CXType_UAccum = 37,
  CXType_ULongAccum = 38,
  CXType_BFloat16 = 39,
  CXType_Ibm128 = 40,
  CXType_FirstBuiltin = CXType_Void,
  CXType_LastBuiltin = CXType_Ibm128,

  CXType_Complex = 100,
  CXType_Pointer = 101,
  CXType_BlockPointer = 102,
  CXType_LValueReference = 103,
  CXType_RValueReference = 104,
  CXType_Record = 105,
  CXType_Enum = 106,
  CXType_Typedef = 107,
  CXType_ObjCInterface = 108,
  CXType_ObjCObjectPointer = 109,
  CXType_FunctionNoProto = 110,
  CXType_FunctionProto = 111,
  CXType_ConstantArray = 112,
  CXType_Vector = 113,
  CXType_IncompleteArray = 114,
  CXType_VariableArray = 115,
  CXType_DependentSizedArray = 116,
  CXType_MemberPointer = 117,
  CXType_Auto = 118,

  /**
   * Represents a type that was referred to using an elaborated type keyword.
   *
   * E.g., struct S, or via a qualified name, e.g., N::M::type, or both.
   */
  CXType_Elaborated = 119,

  /* OpenCL PipeType. */
  CXType_Pipe = 120,

  /* OpenCL builtin types. */
  CXType_OCLImage1dRO = 121,
  CXType_OCLImage1dArrayRO = 122,
  CXType_OCLImage1dBufferRO = 123,
  CXType_OCLImage2dRO = 124,
  CXType_OCLImage2dArrayRO = 125,
  CXType_OCLImage2dDepthRO = 126,
  CXType_OCLImage2dArrayDepthRO = 127,
  CXType_OCLImage2dMSAARO = 128,
  CXType_OCLImage2dArrayMSAARO = 129,
  CXType_OCLImage2dMSAADepthRO = 130,
  CXType_OCLImage2dArrayMSAADepthRO = 131,
  CXType_OCLImage3dRO = 132,
  CXType_OCLImage1dWO = 133,
  CXType_OCLImage1dArrayWO = 134,
  CXType_OCLImage1dBufferWO = 135,
  CXType_OCLImage2dWO = 136,
  CXType_OCLImage2dArrayWO = 137,
  CXType_OCLImage2dDepthWO = 138,
  CXType_OCLImage2dArrayDepthWO = 139,
  CXType_OCLImage2dMSAAWO = 140,
  CXType_OCLImage2dArrayMSAAWO = 141,
  CXType_OCLImage2dMSAADepthWO = 142,
  CXType_OCLImage2dArrayMSAADepthWO = 143,
  CXType_OCLImage3dWO = 144,
  CXType_OCLImage1dRW = 145,
  CXType_OCLImage1dArrayRW = 146,
  CXType_OCLImage1dBufferRW = 147,
  CXType_OCLImage2dRW = 148,
  CXType_OCLImage2dArrayRW = 149,
  CXType_OCLImage2dDepthRW = 150,
  CXType_OCLImage2dArrayDepthRW = 151,
  CXType_OCLImage2dMSAARW = 152,
  CXType_OCLImage2dArrayMSAARW = 153,
  CXType_OCLImage2dMSAADepthRW = 154,
  CXType_OCLImage2dArrayMSAADepthRW = 155,
  CXType_OCLImage3dRW = 156,
  CXType_OCLSampler = 157,
  CXType_OCLEvent = 158,
  CXType_OCLQueue = 159,
  CXType_OCLReserveID = 160,

  CXType_ObjCObject = 161,
  CXType_ObjCTypeParam = 162,
  CXType_Attributed = 163,

  CXType_OCLIntelSubgroupAVCMcePayload = 164,
  CXType_OCLIntelSubgroupAVCImePayload = 165,
  CXType_OCLIntelSubgroupAVCRefPayload = 166,
  CXType_OCLIntelSubgroupAVCSicPayload = 167,
  CXType_OCLIntelSubgroupAVCMceResult = 168,
  CXType_OCLIntelSubgroupAVCImeResult = 169,
  CXType_OCLIntelSubgroupAVCRefResult = 170,
  CXType_OCLIntelSubgroupAVCSicResult = 171,
  CXType_OCLIntelSubgroupAVCImeResultSingleRefStreamout = 172,
  CXType_OCLIntelSubgroupAVCImeResultDualRefStreamout = 173,
  CXType_OCLIntelSubgroupAVCImeSingleRefStreamin = 174,

  CXType_OCLIntelSubgroupAVCImeDualRefStreamin = 175,

  CXType_ExtVector = 176,
  CXType_Atomic = 177
};

typedef struct {
  enum CXTypeKind kind;
  void *data[2];
} CXType;

typedef enum CXChildVisitResult (*CXCursorVisitor)(CXCursor cursor,
                                                   CXCursor parent,
                                                   CXClientData client_data);

enum CXPrintingPolicyProperty {
  CXPrintingPolicy_Indentation,
  CXPrintingPolicy_SuppressSpecifiers,
  CXPrintingPolicy_SuppressTagKeyword,
  CXPrintingPolicy_IncludeTagDefinition,
  CXPrintingPolicy_SuppressScope,
  CXPrintingPolicy_SuppressUnwrittenScope,
  CXPrintingPolicy_SuppressInitializers,
  CXPrintingPolicy_ConstantArraySizeAsWritten,
  CXPrintingPolicy_AnonymousTagLocations,
  CXPrintingPolicy_SuppressStrongLifetime,
  CXPrintingPolicy_SuppressLifetimeQualifiers,
  CXPrintingPolicy_SuppressTemplateArgsInCXXConstructors,
  CXPrintingPolicy_Bool,
  CXPrintingPolicy_Restrict,
  CXPrintingPolicy_Alignof,
  CXPrintingPolicy_UnderscoreAlignof,
  CXPrintingPolicy_UseVoidForZeroParams,
  CXPrintingPolicy_TerseOutput,
  CXPrintingPolicy_PolishForDeclaration,
  CXPrintingPolicy_Half,
  CXPrintingPolicy_MSWChar,
  CXPrintingPolicy_IncludeNewlines,
  CXPrintingPolicy_MSVCFormatting,
  CXPrintingPolicy_ConstantsAsWritten,
  CXPrintingPolicy_SuppressImplicitBase,
  CXPrintingPolicy_FullyQualifiedName,

  CXPrintingPolicy_LastProperty = CXPrintingPolicy_FullyQualifiedName
};

enum CXTranslationUnit_Flags {
  /**
   * Used to indicate that no special translation-unit options are
   * needed.
   */
  CXTranslationUnit_None = 0x0,

  /**
   * Used to indicate that the parser should construct a "detailed"
   * preprocessing record, including all macro definitions and instantiations.
   *
   * Constructing a detailed preprocessing record requires more memory
   * and time to parse, since the information contained in the record
   * is usually not retained. However, it can be useful for
   * applications that require more detailed information about the
   * behavior of the preprocessor.
   */
  CXTranslationUnit_DetailedPreprocessingRecord = 0x01,

  /**
   * Used to indicate that the translation unit is incomplete.
   *
   * When a translation unit is considered "incomplete", semantic
   * analysis that is typically performed at the end of the
   * translation unit will be suppressed. For example, this suppresses
   * the completion of tentative declarations in C and of
   * instantiation of implicitly-instantiation function templates in
   * C++. This option is typically used when parsing a header with the
   * intent of producing a precompiled header.
   */
  CXTranslationUnit_Incomplete = 0x02,

  /**
   * Used to indicate that the translation unit should be built with an
   * implicit precompiled header for the preamble.
   *
   * An implicit precompiled header is used as an optimization when a
   * particular translation unit is likely to be reparsed many times
   * when the sources aren't changing that often. In this case, an
   * implicit precompiled header will be built containing all of the
   * initial includes at the top of the main file (what we refer to as
   * the "preamble" of the file). In subsequent parses, if the
   * preamble or the files in it have not changed, \c
   * clang_reparseTranslationUnit() will re-use the implicit
   * precompiled header to improve parsing performance.
   */
  CXTranslationUnit_PrecompiledPreamble = 0x04,

  /**
   * Used to indicate that the translation unit should cache some
   * code-completion results with each reparse of the source file.
   *
   * Caching of code-completion results is a performance optimization that
   * introduces some overhead to reparsing but improves the performance of
   * code-completion operations.
   */
  CXTranslationUnit_CacheCompletionResults = 0x08,

  /**
   * Used to indicate that the translation unit will be serialized with
   * \c clang_saveTranslationUnit.
   *
   * This option is typically used when parsing a header with the intent of
   * producing a precompiled header.
   */
  CXTranslationUnit_ForSerialization = 0x10,

  /**
   * DEPRECATED: Enabled chained precompiled preambles in C++.
   *
   * Note: this is a *temporary* option that is available only while
   * we are testing C++ precompiled preamble support. It is deprecated.
   */
  CXTranslationUnit_CXXChainedPCH = 0x20,

  /**
   * Used to indicate that function/method bodies should be skipped while
   * parsing.
   *
   * This option can be used to search for declarations/definitions while
   * ignoring the usages.
   */
  CXTranslationUnit_SkipFunctionBodies = 0x40,

  /**
   * Used to indicate that brief documentation comments should be
   * included into the set of code completions returned from this translation
   * unit.
   */
  CXTranslationUnit_IncludeBriefCommentsInCodeCompletion = 0x80,

  /**
   * Used to indicate that the precompiled preamble should be created on
   * the first parse. Otherwise it will be created on the first reparse. This
   * trades runtime on the first parse (serializing the preamble takes time) for
   * reduced runtime on the second parse (can now reuse the preamble).
   */
  CXTranslationUnit_CreatePreambleOnFirstParse = 0x100,

  /**
   * Do not stop processing when fatal errors are encountered.
   *
   * When fatal errors are encountered while parsing a translation unit,
   * semantic analysis is typically stopped early when compiling code. A common
   * source for fatal errors are unresolvable include files. For the
   * purposes of an IDE, this is undesirable behavior and as much information
   * as possible should be reported. Use this flag to enable this behavior.
   */
  CXTranslationUnit_KeepGoing = 0x200,

  /**
   * Sets the preprocessor in a mode for parsing a single file only.
   */
  CXTranslationUnit_SingleFileParse = 0x400,

  /**
   * Used in combination with CXTranslationUnit_SkipFunctionBodies to
   * constrain the skipping of function bodies to the preamble.
   *
   * The function bodies of the main file are not skipped.
   */
  CXTranslationUnit_LimitSkipFunctionBodiesToPreamble = 0x800,

  /**
   * Used to indicate that attributed types should be included in CXType.
   */
  CXTranslationUnit_IncludeAttributedTypes = 0x1000,

  /**
   * Used to indicate that implicit attributes should be visited.
   */
  CXTranslationUnit_VisitImplicitAttributes = 0x2000,

  /**
   * Used to indicate that non-errors from included files should be ignored.
   *
   * If set, clang_getDiagnosticSetFromTU() will not report e.g. warnings from
   * included files anymore. This speeds up clang_getDiagnosticSetFromTU() for
   * the case where these warnings are not of interest, as for an IDE for
   * example, which typically shows only the diagnostics in the main file.
   */
  CXTranslationUnit_IgnoreNonErrorsFromIncludedFiles = 0x4000,

  /**
   * Tells the preprocessor not to skip excluded conditional blocks.
   */
  CXTranslationUnit_RetainExcludedConditionalBlocks = 0x8000
};

typedef void *CXCompletionString;

enum CXCompletionChunkKind {
  /**
   * A code-completion string that describes "optional" text that
   * could be a part of the template (but is not required).
   *
   * The Optional chunk is the only kind of chunk that has a code-completion
   * string for its representation, which is accessible via
   * \c clang_getCompletionChunkCompletionString(). The code-completion string
   * describes an additional part of the template that is completely optional.
   * For example, optional chunks can be used to describe the placeholders for
   * arguments that match up with defaulted function parameters, e.g. given:
   *
   * \code
   * void f(int x, float y = 3.14, double z = 2.71828);
   * \endcode
   *
   * The code-completion string for this function would contain:
   *   - a TypedText chunk for "f".
   *   - a LeftParen chunk for "(".
   *   - a Placeholder chunk for "int x"
   *   - an Optional chunk containing the remaining defaulted arguments, e.g.,
   *       - a Comma chunk for ","
   *       - a Placeholder chunk for "float y"
   *       - an Optional chunk containing the last defaulted argument:
   *           - a Comma chunk for ","
   *           - a Placeholder chunk for "double z"
   *   - a RightParen chunk for ")"
   *
   * There are many ways to handle Optional chunks. Two simple approaches are:
   *   - Completely ignore optional chunks, in which case the template for the
   *     function "f" would only include the first parameter ("int x").
   *   - Fully expand all optional chunks, in which case the template for the
   *     function "f" would have all of the parameters.
   */
  CXCompletionChunk_Optional,
  /**
   * Text that a user would be expected to type to get this
   * code-completion result.
   *
   * There will be exactly one "typed text" chunk in a semantic string, which
   * will typically provide the spelling of a keyword or the name of a
   * declaration that could be used at the current code point. Clients are
   * expected to filter the code-completion results based on the text in this
   * chunk.
   */
  CXCompletionChunk_TypedText,
  /**
   * Text that should be inserted as part of a code-completion result.
   *
   * A "text" chunk represents text that is part of the template to be
   * inserted into user code should this particular code-completion result
   * be selected.
   */
  CXCompletionChunk_Text,
  /**
   * Placeholder text that should be replaced by the user.
   *
   * A "placeholder" chunk marks a place where the user should insert text
   * into the code-completion template. For example, placeholders might mark
   * the function parameters for a function declaration, to indicate that the
   * user should provide arguments for each of those parameters. The actual
   * text in a placeholder is a suggestion for the text to display before
   * the user replaces the placeholder with real code.
   */
  CXCompletionChunk_Placeholder,
  /**
   * Informative text that should be displayed but never inserted as
   * part of the template.
   *
   * An "informative" chunk contains annotations that can be displayed to
   * help the user decide whether a particular code-completion result is the
   * right option, but which is not part of the actual template to be inserted
   * by code completion.
   */
  CXCompletionChunk_Informative,
  /**
   * Text that describes the current parameter when code-completion is
   * referring to function call, message send, or template specialization.
   *
   * A "current parameter" chunk occurs when code-completion is providing
   * information about a parameter corresponding to the argument at the
   * code-completion point. For example, given a function
   *
   * \code
   * int add(int x, int y);
   * \endcode
   *
   * and the source code \c add(, where the code-completion point is after the
   * "(", the code-completion string will contain a "current parameter" chunk
   * for "int x", indicating that the current argument will initialize that
   * parameter. After typing further, to \c add(17, (where the code-completion
   * point is after the ","), the code-completion string will contain a
   * "current parameter" chunk to "int y".
   */
  CXCompletionChunk_CurrentParameter,
  /**
   * A left parenthesis ('('), used to initiate a function call or
   * signal the beginning of a function parameter list.
   */
  CXCompletionChunk_LeftParen,
  /**
   * A right parenthesis (')'), used to finish a function call or
   * signal the end of a function parameter list.
   */
  CXCompletionChunk_RightParen,
  /**
   * A left bracket ('[').
   */
  CXCompletionChunk_LeftBracket,
  /**
   * A right bracket (']').
   */
  CXCompletionChunk_RightBracket,
  /**
   * A left brace ('{').
   */
  CXCompletionChunk_LeftBrace,
  /**
   * A right brace ('}').
   */
  CXCompletionChunk_RightBrace,
  /**
   * A left angle bracket ('<').
   */
  CXCompletionChunk_LeftAngle,
  /**
   * A right angle bracket ('>').
   */
  CXCompletionChunk_RightAngle,
  /**
   * A comma separator (',').
   */
  CXCompletionChunk_Comma,
  /**
   * Text that specifies the result type of a given result.
   *
   * This special kind of informative chunk is not meant to be inserted into
   * the text buffer. Rather, it is meant to illustrate the type that an
   * expression using the given completion string would have.
   */
  CXCompletionChunk_ResultType,
  /**
   * A colon (':').
   */
  CXCompletionChunk_Colon,
  /**
   * A semicolon (';').
   */
  CXCompletionChunk_SemiColon,
  /**
   * An '=' sign.
   */
  CXCompletionChunk_Equal,
  /**
   * Horizontal space (' ').
   */
  CXCompletionChunk_HorizontalSpace,
  /**
   * Vertical space ('\\n'), after which it is generally a good idea to
   * perform indentation.
   */
  CXCompletionChunk_VerticalSpace
};

typedef struct {
  /**
   * The kind of entity that this completion refers to.
   *
   * The cursor kind will be a macro, keyword, or a declaration (one of the
   * *Decl cursor kinds), describing the entity that the completion is
   * referring to.
   *
   * \todo In the future, we would like to provide a full cursor, to allow
   * the client to extract additional information from declaration.
   */
  enum CXCursorKind CursorKind;

  /**
   * The code-completion string that describes how to insert this
   * code-completion result into the editing buffer.
   */
  CXCompletionString CompletionString;
} CXCompletionResult;

typedef struct {
  /**
   * The code-completion results.
   */
  CXCompletionResult *Results;

  /**
   * The number of code-completion results stored in the
   * \c Results array.
   */
  unsigned NumResults;
} CXCodeCompleteResults;

enum CXCodeComplete_Flags {
  /**
   * Whether to include macros within the set of code
   * completions returned.
   */
  CXCodeComplete_IncludeMacros = 0x01,

  /**
   * Whether to include code patterns for language constructs
   * within the set of code completions, e.g., for loops.
   */
  CXCodeComplete_IncludeCodePatterns = 0x02,

  /**
   * Whether to include brief documentation within the set of code
   * completions returned.
   */
  CXCodeComplete_IncludeBriefComments = 0x04,

  /**
   * Whether to speed up completion by omitting top- or namespace-level entities
   * defined in the preamble. There's no guarantee any particular entity is
   * omitted. This may be useful if the headers are indexed externally.
   */
  CXCodeComplete_SkipPreamble = 0x08,

  /**
   * Whether to include completions with small
   * fix-its, e.g. change '.' to '->' on member access, etc.
   */
  CXCodeComplete_IncludeCompletionsWithFixIts = 0x10
};

typedef void *CXDiagnostic;

extern "C" {

#define CINDEX_LINKAGE __declspec(dllimport)

CINDEX_LINKAGE enum CXCursorKind clang_getCursorKind(CXCursor);
CINDEX_LINKAGE CXCursor clang_getCursorSemanticParent(CXCursor cursor);
CINDEX_LINKAGE CXString clang_getCursorPrettyPrinted(CXCursor Cursor,
                                                     CXPrintingPolicy Policy);
CINDEX_LINKAGE const char *clang_getCString(CXString string);

CINDEX_LINKAGE void clang_disposeString(CXString string);
CINDEX_LINKAGE CXString clang_getCursorKindSpelling(enum CXCursorKind Kind);
CINDEX_LINKAGE CXString clang_getCursorSpelling(CXCursor);
CINDEX_LINKAGE CXType clang_getCursorType(CXCursor C);
CINDEX_LINKAGE CXString clang_getTypeSpelling(CXType CT);
CINDEX_LINKAGE CXIndex clang_createIndex(int excludeDeclarationsFromPCH,
                                         int displayDiagnostics);
CINDEX_LINKAGE void clang_disposeIndex(CXIndex index);

CINDEX_LINKAGE unsigned clang_visitChildren(CXCursor parent,
                                            CXCursorVisitor visitor,
                                            CXClientData client_data);
CINDEX_LINKAGE void clang_getExpansionLocation(CXSourceLocation location,
                                               CXFile *file, unsigned *line,
                                               unsigned *column,
                                               unsigned *offset);
CINDEX_LINKAGE CXString clang_getFileName(CXFile SFile);
CINDEX_LINKAGE CXSourceLocation clang_getCursorLocation(CXCursor);
CINDEX_LINKAGE CXCursor clang_getCursorReferenced(CXCursor);
CINDEX_LINKAGE unsigned clang_isCursorDefinition(CXCursor);
CINDEX_LINKAGE unsigned clang_CXXMethod_isVirtual(CXCursor C);
CINDEX_LINKAGE int clang_Cursor_isNull(CXCursor cursor);
CINDEX_LINKAGE CXCursor clang_getTranslationUnitCursor(CXTranslationUnit);
CINDEX_LINKAGE CXPrintingPolicy clang_getCursorPrintingPolicy(CXCursor);
CINDEX_LINKAGE void clang_PrintingPolicy_setProperty(CXPrintingPolicy Policy,
                                 enum CXPrintingPolicyProperty Property,
                                 unsigned Value);
CINDEX_LINKAGE CXPrintingPolicy clang_getCursorPrintingPolicy(CXCursor);
CINDEX_LINKAGE void clang_PrintingPolicy_dispose(CXPrintingPolicy Policy);
CINDEX_LINKAGE unsigned clang_getNumCompletionChunks(CXCompletionString completion_string);
CINDEX_LINKAGE void clang_disposeTranslationUnit(CXTranslationUnit);
CINDEX_LINKAGE CXTranslationUnit clang_parseTranslationUnit(
    CXIndex CIdx, const char *source_filename,
    const char *const *command_line_args, int num_command_line_args,
    struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files,
    unsigned options);
CINDEX_LINKAGE int
clang_reparseTranslationUnit(CXTranslationUnit TU, unsigned num_unsaved_files,
                             struct CXUnsavedFile *unsaved_files,
                             unsigned options);
CINDEX_LINKAGE unsigned clang_getNumDiagnostics(CXTranslationUnit Unit);
CINDEX_LINKAGE CXDiagnostic clang_getDiagnostic(CXTranslationUnit Unit,
                                                unsigned Index);
CINDEX_LINKAGE CXSourceLocation clang_getDiagnosticLocation(CXDiagnostic);
CINDEX_LINKAGE CXString clang_getDiagnosticSpelling(CXDiagnostic);
CINDEX_LINKAGE void clang_disposeDiagnostic(CXDiagnostic Diagnostic);
CINDEX_LINKAGE enum CXCompletionChunkKind
clang_getCompletionChunkKind(CXCompletionString completion_string,
                             unsigned chunk_number);
CINDEX_LINKAGE CXString clang_getCompletionChunkText(
    CXCompletionString completion_string, unsigned chunk_number);
CINDEX_LINKAGE CXCompletionString clang_getCompletionChunkCompletionString(
    CXCompletionString completion_string, unsigned chunk_number);
CINDEX_LINKAGE CXString clang_getCompletionParent(
    CXCompletionString completion_string, enum CXCursorKind *kind);
CINDEX_LINKAGE unsigned
clang_getCompletionPriority(CXCompletionString completion_string);
CINDEX_LINKAGE
CXCodeCompleteResults *
clang_codeCompleteAt(CXTranslationUnit TU, const char *complete_filename,
                     unsigned complete_line, unsigned complete_column,
                     struct CXUnsavedFile *unsaved_files,
                     unsigned num_unsaved_files, unsigned options);
CINDEX_LINKAGE
void clang_disposeCodeCompleteResults(CXCodeCompleteResults *Results);

};