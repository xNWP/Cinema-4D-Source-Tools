/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_COFFEE_H__
#define C4D_COFFEE_H__

#ifdef __API_INTERN__
abc def xyz
#endif

class String;
class Coffee;
class Value;
class GeData;


//----------------------------------------------------------------------------------------
/// Retrieves the global @COFFEE master engine.
/// @return												The @COFFEE master. @cinemaOwnsPointed{@COFFEE engine}
//----------------------------------------------------------------------------------------
Coffee* GetCoffeeMaster(void);

//----------------------------------------------------------------------------------------
/// Compiles the @COFFEE code in @formatParam{src}. Error information can be retrieved with GeCoffeeGetLastError().
/// @param[in] cof								A @COFFEE engine, either allocated manually or retrieved from GetCoffeeMaster(). @callerOwnsPointed{@COFFEE engine}
/// @param[in] src								The @COFFEE source code.
/// @return												@trueIfOtherwiseFalse{the compilation was successful}
//----------------------------------------------------------------------------------------
Bool GeCoffeeCompileString(Coffee* cof, const String& src);

//----------------------------------------------------------------------------------------
/// Compiles the @COFFEE code in @formatParam{file}. Error information can be retrieved with GeCoffeeGetLastError().
/// @param[in] cof								A @COFFEE engine, either allocated manually or retrieved from GetCoffeeMaster(). @callerOwnsPointed{@COFFEE engine}
/// @param[in] file								The @COFFEE source file.
/// @return												@trueIfOtherwiseFalse{the compilation was successful}
//----------------------------------------------------------------------------------------
Bool GeCoffeeCompileFile(Coffee* cof, const Filename& file);

//----------------------------------------------------------------------------------------
/// Adds a global symbol to the @COFFEE engine. Useful to provide global input parameter if the symbols are set with GeCoffeeGeData2Value().
/// @note This must be done before compilation.
/// @param[in] cof								A @COFFEE engine, either allocated manually or retrieved from GetCoffeeMaster(). @callerOwnsPointed{@COFFEE engine}
/// @param[in] name								The name of the symbol.
/// @return												The symbol handle or @formatConstant{nullptr} if it could not be added.
//----------------------------------------------------------------------------------------
VALUE* GeCoffeeAddGlobalSymbol(Coffee* cof, const String& name);


//----------------------------------------------------------------------------------------
/// Finds a global symbol in the @COFFEE engine. Used to find function entries for the GeCoffeeExecute() call.
/// @note This must be done after compilation.
/// @param[in] cof								A @COFFEE engine, either allocated manually or retrieved from GetCoffeeMaster(). @callerOwnsPointed{@COFFEE engine}
/// @param[in] name								The name of the symbol.
/// @return												The symbol handle or @formatConstant{nullptr} if it could not be added.
//----------------------------------------------------------------------------------------
VALUE* GeCoffeeFindGlobalSymbol(Coffee* cof, const String& name);

//----------------------------------------------------------------------------------------
/// Executes a compiled script of a @COFFEE engine, essentially by calling <tt>*@formatParam{retval} = (*@formatParam{func})(*@formatParam{arg1}, *@formatParam{arg2}, *@formatParam{arg3})</tt>. Error information can be retrieved with GeCoffeeGetLastError().
/// @param[in] cof								A @COFFEE engine, either allocated manually or retrieved from GetCoffeeMaster(). @callerOwnsPointed{@COFFEE engine}
/// @param[in] func								The function entry point. Use GeCoffeeFindGlobalSymbol() to find the function to call. @callerOwnsPointed{VALUE}
/// @param[out] retval						Assigned the return value of the function if not @formatConstant{nullptr}. @callerOwnsPointed{::GeData}
/// @param[out] arg1							Used for the first argument of the function if not @formatConstant{nullptr}. @callerOwnsPointed{::GeData}
/// @param[out] arg2							Used for the second argument of the function if not @formatConstant{nullptr}. @callerOwnsPointed{::GeData}
/// @param[out] arg3							Used for the third argument of the function if not @formatConstant{nullptr}. @callerOwnsPointed{::GeData}
/// @return												@trueIfOtherwiseFalse{the execution was successful}
//----------------------------------------------------------------------------------------
Bool GeCoffeeExecute(Coffee* cof, VALUE* func, GeData* retval = nullptr, GeData* arg1 = nullptr, GeData* arg2 = nullptr, GeData* arg3 = nullptr);

//----------------------------------------------------------------------------------------
/// Assigns a GeData value to a global variable in a @COFFEE engine.
/// @param[in] cof								A @COFFEE engine, either allocated manually or retrieved from GetCoffeeMaster(). @callerOwnsPointed{@COFFEE engine}
/// @param[in] src								The source value.
/// @param[in] dest								The destination variable. @callerOwnsPointed{::VALUE}
/// @return												@trueIfOtherwiseFalse{the value was assigned}
//----------------------------------------------------------------------------------------
Bool GeCoffeeGeData2Value(Coffee* cof, const GeData& src, VALUE* dest);

//----------------------------------------------------------------------------------------
/// Retrieves a GeData value from a global variable in a @COFFEE engine.
/// @param[in] cof								A @COFFEE engine, either allocated manually or retrieved from GetCoffeeMaster(). @callerOwnsPointed{@COFFEE engine}
/// @param[in] src								The source variable.
/// @param[in] dest								The destination value. @callerOwnsPointed{::VALUE}
/// @return												@trueIfOtherwiseFalse{the value was retrieved}
//----------------------------------------------------------------------------------------
Bool GeCoffeeValue2GeData(Coffee* cof, VALUE* src, GeData* dest);

//----------------------------------------------------------------------------------------
/// Returns error information from failed compilations or executions.
/// @param[in] cof								A @COFFEE engine, either allocated manually or retrieved from GetCoffeeMaster(). @callerOwnsPointed{@COFFEE engine}
/// @param[out] err_string				Assigned the error string. @callerOwnsPointed{::String}
/// @param[out] err_line					Assigned the error line, or @ref NOTOK if the error cannot be located. @callerOwnsPointed{::Int32}
/// @param[out] err_pos						Assigned the error position, or @ref NOTOK if the error cannot be located. @callerOwnsPointed{::Int32}
/// @return												@trueIfOtherwiseFalse{the error information was retrieved}
//----------------------------------------------------------------------------------------
Bool GeCoffeeGetLastError(Coffee* cof, String* err_string, Int32* err_line, Int32* err_pos);

//----------------------------------------------------------------------------------------
/// Opens the @C4D code editor.
/// @param[in] obj								The object that the source belongs to. @callerOwnsPointed{object}
/// @param[in] callback						A callback to set and retrieve the edited source code. @callerOwnsPointed{callback}
/// @param[in] bc									The settings for the editor that will be opened: @enumerateEnum{CODEEDITOR}
/// @return												@trueIfOtherwiseFalse{the editor was opened}
//----------------------------------------------------------------------------------------
Bool CodeEditor_Open(BaseList2D* obj, CodeEditorCallback* callback, const BaseContainer& bc = BaseContainer());

/// @addtogroup COFFEE_STYPE
/// @ingroup group_enumeration
/// @{
enum COFFEE_STYPE
{
	COFFEE_STYPE_CLASS		= 1,			///< Class definition.
	COFFEE_STYPE_DATA			= 2,			///< Public data.
	COFFEE_STYPE_CDATA		= 3,			///< Protected/static data.
	COFFEE_STYPE_PDATA		= 4,			///< Private data.
	COFFEE_STYPE_FUNCTION	= 5,			///< Function.
	COFFEE_STYPE_METHOD		= 6,			///< Public method.
	COFFEE_STYPE_CMETHOD	= 7,			///< Protected method.
	COFFEE_STYPE_PMETHOD	= 8				///< Private method.
} ENUM_END_LIST(COFFEE_STYPE);
/// @}

/// @addtogroup COFFEE_VTYPE
/// @ingroup group_enumeration
/// @{
enum COFFEE_VTYPE
{
	COFFEE_VTYPE_NIL				= 0,			///< Nil.
	COFFEE_VTYPE_LONG				= 1,			///< ::Int32. Use VALUE::GetInt32() to access the data.
	COFFEE_VTYPE_FLOAT			= 2,			///< ::Float. Use VALUE::GetFloat() to access the data.
	COFFEE_VTYPE_VECTOR			= 3,			///< ::Vector. Use VALUE::GetVector() to access the data.
	COFFEE_VTYPE_VOID				= 4,			///< @c void*. Used for unknown or foreign classes/objects, where only the pointer is known, for example in the connection to C++ classes.
	COFFEE_VTYPE_BYTES			= 5,			///< Bytes. Use VALUE::GetSize() and VALUE::GetBytes() to access the data.
	COFFEE_VTYPE_STRING			= 6,			///< String. Use VALUE::GetString() to access the data.
	COFFEE_VTYPE_CLASS			= 7,			///< Class. Can be used with C4DAtom::IsInstanceOf(). Cannot currently be used to instantiate objects.
	COFFEE_VTYPE_OBJECT			= 8,			///< Object. Used for things created with @c new() in @COFFEE that are not arrays. Use VALUE::GetObjMember() to access members.
	COFFEE_VTYPE_ARRAY			= 9,			///< Array. Use VALUE::GetArrayMember() to access the array.
	COFFEE_VTYPE_BYTECODE		= 10,			///< @markInternal
	COFFEE_VTYPE_CODE				= 11,			///< @markInternal
	COFFEE_VTYPE_EXTCODE		= 12,			///< @markInternal

	COFFEE_VTYPE_EXCEPTION	= 13,			///< @markInternal
	COFFEE_VTYPE_SEXCEPTION	= 14,			///< @markInternal
	COFFEE_VTYPE_DICTIONARY	= 15,			///< @markInternal
	COFFEE_VTYPE_ENTRY			= 16,			///< @markInternal
	COFFEE_VTYPE_INSTANCE		= 17,			///< @markInternal

	COFFEE_VTYPE_NUMBER			= 99			///< Number. Abstract type that can be used with VALUE::IsType() to check if a value is of type ::Float or ::Int32.
} ENUM_END_LIST(COFFEE_VTYPE);
/// @}

/// @addtogroup CoffeeError
/// @ingroup group_enumeration
/// @{
enum CoffeeError
{
	COFFEEERROR_BBLOCK			= 1,				///< Bad type.
	COFFEEERROR_MEM					= 2,				///< Not enough memory.
	COFFEEERROR_ARGV				= 3,				///< Too many parameters.
	COFFEEERROR_ARGW				= 4,				///< Too few parameters.
	COFFEEERROR_BTYP				= 5,				///< Incompatible values.
	COFFEEERROR_BOPCODE			= 6,				///< Wrong PCODE.
	COFFEEERROR_NPROC				= 7,				///< Not a function.
	COFFEEERROR_BMETHOD			= 8,				///< Not a member function.
	COFFEEERROR_NMETHOD			= 9,				///< Member not found.
	COFFEEERROR_NPUBLIC			= 10,				///< Member is not public.
	COFFEEERROR_MPROTECTED	= 11,				///< Member is accessible.
	COFFEEERROR_MPRIVATE		= 12,				///< Member is not accessible.
	COFFEEERROR_SUBSCR			= 13,				///< Subscript out of range.
	COFFEEERROR_STACKOV			= 14,				///< Stack overflow.
	COFFEEERROR_DIV0				= 15,				///< Division by @em 0.
	COFFEEERROR_EXEPT				= 16,				///< Unhandled exception.
	COFFEEERROR_INVALIDID		= 17,				///< Invalid description ID for object.
	COFFEEERROR_PARAMACCESS	= 18,				///< Parameter access failed.
	COFFEEERROR_PARAMVALUE	= 19,				///< Parameter value not accessible (object unknown).
	COFFEEERROR_PARAMTYPE		= 20,				///< Wrong parameter value type.
	COFFEEERROR_EDEC				= 100,			///< Declaration expected.
	COFFEEERROR_EMDEC				= 101,			///< Member declaration expected.
	COFFEEERROR_EFUNC				= 102,			///< Function declaration expected.
	COFFEEERROR_IRDEF				= 103,			///< Expression already defined.
	COFFEEERROR_ECNAME			= 104,			///< Class name expected.
	COFFEEERROR_TMLOOP			= 105,			///< Too many nested loops.
	COFFEEERROR_BOLOOP			= 106,			///< Break without loop/switch.
	COFFEEERROR_COLOOP			= 107,			///< Continue without loop.
	COFFEEERROR_SOLOOP			= 108,			///< Case/default not allowed here.
	COFFEEERROR_NCASE				= 109,			///< Switch without case.
	COFFEEERROR_NVAR				= 110,			///< Variables declaration not allowed here.
	COFFEEERROR_ELVAL				= 111,			///< Left value expected.
	COFFEEERROR_NCLASSM			= 112,			///< Not a class member.
	COFFEEERROR_BPARENT			= 113,			///< Object is protected.
	COFFEEERROR_NPARENT			= 114,			///< Variable or function expected.
	COFFEEERROR_BSUPER			= 115,			///< Expression expected.
	COFFEEERROR_NSUPER			= 116,			///< @c super() in constructor expected.
	COFFEEERROR_PROTECT			= 117,			///< Object is protected.
	COFFEEERROR_EVAR				= 118,			///< Variable or function expected.
	COFFEEERROR_EPRIM				= 119,			///< Expression expected.
	COFFEEERROR_ISPACE			= 120,			///< Not enough memory for PCODE.
	COFFEEERROR_ECLOSE			= 121,			///< Expected.
	COFFEEERROR_PARGV				= 122,			///< Too many parameters.
	COFFEEERROR_PARGW				= 123,			///< Too few parameters.
	COFFEEERROR_SYNTAX			= 124,			///< Syntax error.
	COFFEEERROR_INCLUDE			= 125,			///< Error in include.
	COFFEEERROR_VARONLY			= 126,			///< Only variables allowed.
	COFFEEERROR_CLASSB			= 200,			///< Class with base class.
	COFFEEERROR_CLASS				= 201,			///< Class.
	COFFEEERROR_FUNC				= 202,			///< Function.
	COFFEEERROR_MEMBERF			= 203,			///< Class method.
	COFFEEERROR_EXPECT			= 204				///< Expected something but got something else.
} ENUM_END_LIST(CoffeeError);
/// @}

//----------------------------------------------------------------------------------------
/// Represents values for the Coffee engine.
//----------------------------------------------------------------------------------------
class VALUE
{
	COFFEE_VTYPE v_type;
	union
	{
		Int32 v_integer;
		Float v_float;
		Float v_vector[3];
		void* v_void;
	} v;

public:

	/// @name Constructor
	/// @{

	//----------------------------------------------------------------------------------------
	/// Constructor.
	//----------------------------------------------------------------------------------------
	VALUE();

	/// @}

	/// @name Type
	/// @{

	//----------------------------------------------------------------------------------------
	/// Checks if the value is of a certain @formatParam{type}.
	/// @param[in] type								The type to check: @enumerateEnum{COFFEE_VTYPE}
	/// @return												@trueIfOtherwiseFalse{the value is of the given @formatParam{type}}
	//----------------------------------------------------------------------------------------
	Bool IsType(COFFEE_VTYPE type) const;

	//----------------------------------------------------------------------------------------
	/// Gets the type of the value.
	/// @return												The value type: @enumerateEnum{COFFEE_VTYPE}
	//----------------------------------------------------------------------------------------
	COFFEE_VTYPE GetType(void) const;

	/// @}

	/// @name Get Value
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets an ::Int32 from the value.
	/// @param[out] err								If not @formatConstant{nullptr}, the error code is assigned in case of an error (or @em 0 if no error occurred).\n
	/// 															See @ref CoffeeError for error codes.
	/// @return												The ::Int32 value.
	//----------------------------------------------------------------------------------------
	Int32 GetInt32(Int32* err = nullptr) const;

	//----------------------------------------------------------------------------------------
	/// Gets a ::Float from the value.
	/// @param[out] err								If not @formatConstant{nullptr}, the error code is assigned in case of an error (or @em 0 if no error occurred).\n
	/// 															See @ref CoffeeError for error codes.
	/// @return												The ::Float value.
	//----------------------------------------------------------------------------------------
	Float GetFloat(Int32* err = nullptr) const;

	//----------------------------------------------------------------------------------------
	/// Gets a ::Vector from the value.
	/// @param[out] err								If not @formatConstant{nullptr}, the error code is assigned in case of an error (or @em 0 if no error occurred).\n
	/// 															See @ref CoffeeError for error codes.
	/// @return												The ::Vector value.
	//----------------------------------------------------------------------------------------
	Vector GetVector(Int32* err = nullptr) const;

	//----------------------------------------------------------------------------------------
	/// Gets a @c void* from the value.
	/// @param[out] err								If not @formatConstant{nullptr}, the error code is assigned in case of an error (or @em 0 if no error occurred).\n
	/// 															See @ref CoffeeError for error codes.
	/// @return												The @c void*.
	//----------------------------------------------------------------------------------------
	void* GetVoid(Int32* err = nullptr) const;

	/// @}

	/// @name Set Value
	/// @{

	//----------------------------------------------------------------------------------------
	/// Sets the value to nil.
	//----------------------------------------------------------------------------------------
	void SetNil(void);

	//----------------------------------------------------------------------------------------
	/// Sets the value to an ::Int32.
	/// @param[in] i									The ::Int32 value.
	//----------------------------------------------------------------------------------------
	void SetInt32(Int32 i);

	//----------------------------------------------------------------------------------------
	/// Sets the value to a ::Float.
	/// @param[in] f									The ::Float value.
	//----------------------------------------------------------------------------------------
	void SetFloat(Float f);

	//----------------------------------------------------------------------------------------
	/// Sets the value to a ::Vector.
	/// @param[in] v									The ::Vector value.
	//----------------------------------------------------------------------------------------
	void SetVector(const Vector& v);

	//----------------------------------------------------------------------------------------
	/// Sets the value to a @c void*.
	/// @param[in] v									The @c void* value.
	//----------------------------------------------------------------------------------------
	void SetVoid(const void* v);

	/// @}

	/// @name Object
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets a @COFFEE object from the value.
	/// @param[out] err								If not @formatConstant{nullptr}, the error code is assigned in case of an error (or @em 0 if no error occurred).\n
	/// 															See @ref CoffeeError for error codes.
	/// @return												The @COFFEE object value.
	//----------------------------------------------------------------------------------------
	OBJECT* GetObject(Int32* err = nullptr);

	//----------------------------------------------------------------------------------------
	/// Sets the value to a @COFFEE object.
	/// @param[in] o									The @COFFEE object value.
	//----------------------------------------------------------------------------------------
	void SetObject(OBJECT* o);

	//----------------------------------------------------------------------------------------
	/// Gets members from object values.
	/// @param[in] nr									The member index.
	/// @return												The member value, or @formatConstant{nullptr} if the index was invalid.
	//----------------------------------------------------------------------------------------
	VALUE* GetObjMember(Int32 nr);

	/// @}

	/// @name Array
	/// @{

	//----------------------------------------------------------------------------------------
	/// Sets the value to an array.
	/// @param[in] a									The @COFFEE array value.
	//----------------------------------------------------------------------------------------
	void SetArray(ARRAY* a);

	//----------------------------------------------------------------------------------------
	/// Gets members from array values.
	/// @param[in] i									The array index.
	/// @return												The member value, or @formatConstant{nullptr} if the index was invalid.
	//----------------------------------------------------------------------------------------
	VALUE* GetArrayMember(Int32 i);

	/// @}

	/// @name String
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets a string from the value.
	/// @return												The string value.
	//----------------------------------------------------------------------------------------
	String GetString(void);

	//----------------------------------------------------------------------------------------
	/// Sets the value to a @COFFEE string.
	/// @param[in] s									The @COFFEE string value.
	//----------------------------------------------------------------------------------------
	void SetString(CSTRING* s);

	/// @}

	/// @name Byte Array
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets a byte array data.
	/// @return												The byte array pointer. @theOwnsPointed{value,array}
	//----------------------------------------------------------------------------------------
	UChar* GetBytes(void);

	/// @}

	/// @name String/Array/Byte Array Size
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the size of strings, arrays and byte arrays values.
	/// @return												The size of the value.
	//----------------------------------------------------------------------------------------
	Int32 GetSize(void);

	/// @}

	/// @name IsInstanceOf
	/// @{

	//----------------------------------------------------------------------------------------
	/// Checks if the value is an instance of class @formatParam{cl}.
	/// @param[in] cl									The class value to check against.
	/// @param[out] err								If not @formatConstant{nullptr}, the error code is assigned in case of an error (or @em 0 if no error occurred).\n
	/// 															See @ref CoffeeError for error codes.
	/// @return												@trueIfOtherwiseFalse{the value is an instance of class @formatParam{cl}}
	//----------------------------------------------------------------------------------------
	Bool IsInstanceOf(VALUE* cl, Int32* err = nullptr);

	/// @}
};

//----------------------------------------------------------------------------------------
/// The @COFFEE engine class. Allows to extend the language and to add objects to the environment.
/// @addAllocFreeAutoAllocNote
//----------------------------------------------------------------------------------------
class Coffee
{
private:
	Coffee();
	~Coffee();

public:
	/// @name Alloc/Free
	/// @{

	//----------------------------------------------------------------------------------------
	/// @allocatesA{@COFFEE engine}
	/// @return												@allocReturn{@COFFEE engine}
	//----------------------------------------------------------------------------------------
	static Coffee* Alloc();

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{@COFFEE engines}
	/// @param[in,out] cof						@theToDestruct{@COFFEE engine}
	//----------------------------------------------------------------------------------------
	static void Free(Coffee*& cof);

	/// @}

	/// @name Global/Class Symbols
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets a class in the global namespace.
	/// @param[in] name								The name of the class to find.
	/// @return												The class, or @formatConstant{nullptr} if the class was not found.
	//----------------------------------------------------------------------------------------
	VALUE* GetGlobalClass(const String& name);

	//----------------------------------------------------------------------------------------
	/// Adds a class to the global namespace.
	/// @param[in] name								The name of the class to add.
	/// @param[in] parent							The optional parent class name.
	/// @return												The added class, or @formatConstant{nullptr} if the operation failed.
	//----------------------------------------------------------------------------------------
	CLASS* AddGlobalClass(const String& name, const String& parent = String());

	//----------------------------------------------------------------------------------------
	/// Adds a symbol to the global namespace.
	/// @param[in] name								The name of the symbol to add.
	/// @param[in] v									The value to add.
	/// @param[in] type								The type of the symbol: @enumerateEnum{COFFEE_STYPE}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool AddGlobalSymbol(const String& name, const VALUE* v, COFFEE_STYPE type);

	//----------------------------------------------------------------------------------------
	/// Adds a function to the global namespace.
	/// @param[in] name								The name of the function to add.
	/// @param[in] fcn								The function pointer.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool AddGlobalFunction(const String& name, V_CODE fcn);

	//----------------------------------------------------------------------------------------
	/// Adds a member to a class.
	/// @param[in] name								The name of the member to add.
	/// @param[in] c									The class to add the member to.
	/// @param[in] type								The member type: @enumerateEnum{COFFEE_STYPE}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool AddClassMember(const String& name, CLASS* c, COFFEE_STYPE type);

	//----------------------------------------------------------------------------------------
	/// Adds a method to a class.
	/// @param[in] name								The name of the member function to add.
	/// @param[in] c									The class to add the method to.
	/// @param[in] type								The member type: @enumerateEnum{COFFEE_STYPE}
	/// @param[in] fcn								The member function pointer.
	/// @param[in] argc								An optional argument count.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool AddClassMethod(const String& name, CLASS* c, COFFEE_STYPE type, V_CODE fcn, Int32 argc = -1);

	/// @}

	/// @name Alloc/New
	/// @{

	//----------------------------------------------------------------------------------------
	/// Allocates a @COFFEE string.
	/// @param[in] s									The string to allocate.
	/// @return												The allocated string, or @formatConstant{nullptr} if the operation failed.
	//----------------------------------------------------------------------------------------
	CSTRING* AllocString(const String& s);

	//----------------------------------------------------------------------------------------
	/// Allocates a @COFFEE object.
	/// @param[in] cl_name						The name of the class to instantiate.
	/// @return												The allocated object, or @formatConstant{nullptr} if the operation failed.
	//----------------------------------------------------------------------------------------
	OBJECT* NewObject(const String& cl_name);

	//----------------------------------------------------------------------------------------
	/// Allocates a @COFFEE array.
	/// @param[in] size								The size of the array to allocate.
	/// @return												The allocated array, or @formatConstant{nullptr} if the operation failed.
	//----------------------------------------------------------------------------------------
	ARRAY* NewArray(Int32 size);

	/// @}

	/// @name Error
	/// @{

	//----------------------------------------------------------------------------------------
	/// Raises an error if @formatParam{n} is not equal to @formatParam{cnt}.
	/// @param[in] n									The count to check.
	/// @param[in] cnt								The correct count.
	//----------------------------------------------------------------------------------------
	void Wrongcnt(Int32 n, Int32 cnt);

	//----------------------------------------------------------------------------------------
	/// Raises an error if value @formatParam{v} is not of the specified @formatParam{type}.
	/// @param[in] v									The value to check.
	/// @param[in] type								The correct type: @enumerateEnum{COFFEE_VTYPE}
	/// @param[out] err								If not @formatConstant{nullptr}, the error code is assigned in case of an error (or @em 0 if no error occurred).\n
	/// 															See @ref CoffeeError for error codes.
	//----------------------------------------------------------------------------------------
	void ErrCheckType(VALUE* v, COFFEE_VTYPE type, Int32* err = nullptr);

	//----------------------------------------------------------------------------------------
	/// Raises an error if @formatParam{v} is not of the class specified by @formatParam{cl_name}.
	/// @param[in] v									The value to check.
	/// @param[in] cl_name						The correct class name.
	/// @param[out] err								If not @formatConstant{nullptr}, the error code is assigned in case of an error (or @em 0 if no error occurred).\n
	/// 															See @ref CoffeeError for error codes.
	//----------------------------------------------------------------------------------------
	void ErrCheckObjectType(VALUE* v, const String& cl_name, Int32* err = nullptr);

	//----------------------------------------------------------------------------------------
	/// Raises an error if the argument count @formatParam{argc} is not equal to @formatParam{cnt}.
	/// @param[in] argc								The argument count to check.
	/// @param[in] cnt								The correct argument count.
	/// @param[out] err								If not @formatConstant{nullptr}, the error code is assigned in case of an error (or @em 0 if no error occurred).\n
	/// 															See @ref CoffeeError for error codes.
	//----------------------------------------------------------------------------------------
	void ErrCheckArgCount(Int32 argc, Int32 cnt, Int32* err = nullptr);

	//----------------------------------------------------------------------------------------
	/// Raises a general error.
	/// @param[in] type								The error type: @enumerateEnum{CoffeeError}
	/// @param[in] s1									The first error parameter.
	/// @param[in] s2									The second error parameter.
	//----------------------------------------------------------------------------------------
	void SetError(Int32 type, const String& s1 = String(), const String& s2 = String());

	//----------------------------------------------------------------------------------------
	/// Installs an error handler that is used instead of the standard @C4D @COFFEE console output.\n
	/// If the error handler returns @formatConstant{false}, then no further @C4D output is generated, otherwise @C4D prints the standard console stuff.
	/// @b Example:
	/// @code
	/// static Bool CofError(void* priv_data, const BaseContainer &bc)
	/// {
	/// 	GePrint(String("[FAIL] Pos ") + String::IntToString(bc.GetInt32(3)) + String(" : ") + bc.GetString(5));
	/// 	return false;
	/// }
	///
	/// cof->InstallErrorHook(CofError, nullptr);
	/// @endcode
	/// @see ::COFFEE_ERRORHANDLER callback for more information.
	/// @param[in] priv_hndl					The error handler hook.
	/// @param[in] priv_data					The private data that is passed to the hook. @callerOwnsPointed{data}
	//----------------------------------------------------------------------------------------
	void InstallErrorHook(COFFEE_ERRORHANDLER* priv_hndl, void* priv_data);

	/// @}

	/// @name Miscellaneous
	/// @{


	//----------------------------------------------------------------------------------------
	/// Returns @ref Tcoffeeexpression if the @COFFEE engine instance is within a @COFFEE expression tag. Currently there are no other types used.
	/// @return												The type of the @COFFEE engine instance.
	//----------------------------------------------------------------------------------------
	Int32 GetType(void);

	//----------------------------------------------------------------------------------------
	/// Gets the root file for the @COFFEE engine.
	/// @return												The root file.
	//----------------------------------------------------------------------------------------
	const Filename& GetRootFile(void);

	//----------------------------------------------------------------------------------------
	/// Sets the root file for the @COFFEE engine.
	/// @param[in] fn									The root file.
	//----------------------------------------------------------------------------------------
	void SetRootFile(const Filename& fn);

	//----------------------------------------------------------------------------------------
	/// Allocates a @COFFEE object connected to @formatParam{bl}.
	/// @param[in] bl									The object to link to.
	/// @param[in] coffeeallocation		If @formatConstant{true} then @formatParam{bl} will be deleted at the next garbage collection, if it has not been inserted somewhere.\n
	/// 															If @formatConstant{false} @formatParam{bl} will continue to exist afterwards.
	/// @return												The allocated object, or @formatConstant{nullptr} if the operation failed.
	//----------------------------------------------------------------------------------------
	OBJECT* AllocDynamic(BaseList2D* bl, Bool coffeeallocation);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	CLASS* AddInheritance(Int32 id, const String& name, const String& from, Bool use_constructor = true);

	//----------------------------------------------------------------------------------------
	/// Compiles a @COFFEE source code file and optionally creates the compiled binary file.\n
	/// @b Example:
	/// @code
	/// // Compiles the selected source code file and writes the compiled binary
	///
	/// AutoAlloc<Coffee> cof;
	/// if (!cof) return false;
	///
	/// Filename fn;
	/// if (fn.FileSelect(FILESELECTTYPE_ANYTHING, FILESELECT_LOAD, "Select C.O.F.F.E.E. File"))
	/// {
	/// 	if (cof->CompileFile(fn, true))
	/// 		GePrint("Success");
	/// 	else
	/// 		GePrint("Failed");
	/// }
	/// @endcode
	/// @param[in] fn									The filename for the @COFFEE source code file.
	/// @param[in] tofile							If @formatConstant{true} a compiled binary file will be written at the same path as the source code file.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool CompileFile(const Filename& fn, Bool tofile);

	/// @}
};

#endif // C4D_COFFEE_H__
