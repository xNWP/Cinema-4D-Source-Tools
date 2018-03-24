#ifdef __API_INTERN__
	#error "Not in the kernel"
#endif

#include "c4d_memory.h"
#include "c4d_general.h"
#include "c4d_coffee.h"

Coffee* Coffee::Alloc()
{
	return C4DOS.Co->GeCoffeeAlloc();
}

void Coffee::Free(Coffee*& cof)
{
	C4DOS.Co->GeCoffeeFree(cof);
}

Bool GeCoffeeCompileString(Coffee* cof, const String& src)
{
	return C4DOS.Co->GeCoffeeCompileString(cof, src);
}

Bool GeCoffeeCompileFile(Coffee* cof, const Filename& file)
{
	return C4DOS.Co->GeCoffeeCompileFile(cof, file);
}

Coffee* GetCoffeeMaster(void)
{
	return C4DOS.Co->CoGetMaster();
}

VALUE* GeCoffeeAddGlobalSymbol(Coffee* cof, const String& name)
{
	return C4DOS.Co->GeCoffeeAddGlobalSymbol(cof, name);
}

VALUE* GeCoffeeFindGlobalSymbol(Coffee* cof, const String& name)
{
	return C4DOS.Co->GeCoffeeFindGlobalSymbol(cof, name);
}

Bool GeCoffeeExecute(Coffee* cof, VALUE* func, GeData* retval, GeData* arg1, GeData* arg2, GeData* arg3)
{
	return C4DOS.Co->GeCoffeeExecute(cof, func, retval, arg1, arg2, arg3);
}

Bool GeCoffeeGeData2Value(Coffee* cof, const GeData& src, VALUE* dest)
{
	return C4DOS.Co->GeCoffeeGeData2Value(cof, src, dest);
}

Bool GeCoffeeValue2GeData(Coffee* cof, VALUE* src, GeData* dest)
{
	return C4DOS.Co->GeCoffeeValue2GeData(cof, src, dest);
}

Bool GeCoffeeGetLastError(Coffee* cof, String* err_string, Int32* err_line, Int32* err_pos)
{
	return C4DOS.Co->GeCoffeeGetLastError(cof, err_string, err_line, err_pos);
}

Bool CodeEditor_Open(BaseList2D* obj, CodeEditorCallback* callback, const BaseContainer& bc)
{
	return C4DOS.Co->CodeEditor_Open(obj, callback, bc);
}

OBJECT* Coffee::AllocDynamic(BaseList2D* bl, Bool coffeeallocation)
{
	return C4DOS.Co->CoAllocDynamic(this, bl, coffeeallocation);
}
CLASS* Coffee::AddInheritance(Int32 id, const String& name, const String& from, Bool use_constructor)
{
	return C4DOS.Co->CoAddInheritance(this, id, name, from, use_constructor);
}
Bool Coffee::CompileFile(const Filename& fn, Bool tofile)
{
	return C4DOS.Co->CoCompileFile(this, fn, tofile);
}

VALUE::VALUE(void)
{
	v_type = COFFEE_VTYPE_NIL;
}

Bool VALUE::IsType(COFFEE_VTYPE type) const
{
	if (type == COFFEE_VTYPE_NUMBER)
	{
		if (v_type == COFFEE_VTYPE_LONG)
			return true;
		if (v_type == COFFEE_VTYPE_FLOAT)
			return true;
		return false;
	}
	return type == v_type;
}

Int32 VALUE::GetInt32(Int32* err) const
{
	Int32 r = 0;
	if (err)
		*err = 0;
	if (v_type == COFFEE_VTYPE_LONG)
		r = v.v_integer;
	else if (v_type == COFFEE_VTYPE_FLOAT)
		r = (Int32)v.v_float;
	else if (err)
		*err = -1;
	return r;
}

Float VALUE::GetFloat(Int32* err) const
{
	Float r = 0.0;
	if (err)
		*err = 0;
	if (v_type == COFFEE_VTYPE_LONG)
		r = (Float)v.v_integer;
	else if (v_type == COFFEE_VTYPE_FLOAT)
		r = v.v_float;
	else if (err)
		*err = -1;
	return r;
}

Vector VALUE::GetVector(Int32* err) const
{
	if (err)
		*err = 0;
	if (v_type == COFFEE_VTYPE_VECTOR)
		return *((Vector*)v.v_vector);
	else if (err)
		*err = -1;
	return Vector(0.0);
}

void* VALUE::GetVoid(Int32* err) const
{
	if (err)
		*err = 0;
	if (v_type == COFFEE_VTYPE_VOID)
		return v.v_void;
	else if (err)
		*err = -1;
	return nullptr;
}

OBJECT* VALUE::GetObject(Int32* err)
{
	return C4DOS.Co->CoValGetObject(this, err);
}

Bool VALUE::IsInstanceOf(VALUE* cl, Int32* err)
{
	return C4DOS.Co->CoValIsInstanceOf(this, cl, err);
}

COFFEE_VTYPE VALUE::GetType(void) const
{
	return v_type;
}

void VALUE::SetNil(void)
{
	v_type = COFFEE_VTYPE_NIL;
	v.v_integer = 0;
}

void VALUE::SetInt32(Int32 i)
{
	v_type = COFFEE_VTYPE_LONG;
	v.v_integer = i;
}

void VALUE::SetFloat(Float f)
{
	v_type = COFFEE_VTYPE_FLOAT;
	v.v_float = f;
}

void VALUE::SetVector(const Vector& ve)
{
	v_type = COFFEE_VTYPE_VECTOR;
	(*((Vector*)v.v_vector)) = ve;
}

void VALUE::SetString(CSTRING* s)
{
	C4DOS.Co->CoValSetString(this, s);
}

void VALUE::SetArray(ARRAY* a)
{
	C4DOS.Co->CoValSetArray(this, a);
}

void VALUE::SetObject(OBJECT* o)
{
	C4DOS.Co->CoValSetObject(this, o);
}

void VALUE::SetVoid(const void* vo)
{
	v_type = COFFEE_VTYPE_VOID;
	v.v_void = (void*)vo;
}

String VALUE::GetString(void)
{
	return C4DOS.Co->CoValGetString(this);
}

VALUE* VALUE::GetArrayMember(Int32 i)
{
	return C4DOS.Co->CoValGetArrayMember(this, i);
}

VALUE* VALUE::GetObjMember(Int32 i)
{
	return C4DOS.Co->CoValGetObjMember(this, i);
}

Int32 VALUE::GetSize(void)
{
	return C4DOS.Co->CoValGetSize(this);
}

UChar* VALUE::GetBytes(void)
{
	return C4DOS.Co->CoValGetBytes(this);
}

void Coffee::ErrCheckType(VALUE* v, COFFEE_VTYPE vType, Int32* err)
{
	C4DOS.Co->CoErrCheckType(this, v, vType, err);
}

void Coffee::ErrCheckObjectType(VALUE* v, const String& cl_name, Int32* err)
{
	C4DOS.Co->CoErrCheckObjectType(this, v, cl_name, err);
}

void Coffee::ErrCheckArgCount(Int32 argc, Int32 cnt, Int32* err)
{
	C4DOS.Co->CoErrCheckArgCount(this, argc, cnt, err);
}

CSTRING*	Coffee::AllocString(const String& s)
{
	return C4DOS.Co->CoAllocString(this, s);
}

OBJECT*	Coffee::NewObject(const String& cl_name)
{
	return C4DOS.Co->CoNewObject(this, cl_name);
}

Bool Coffee::AddClassMethod(const String& name, CLASS* c, COFFEE_STYPE type, V_CODE fcn, Int32 argc)
{
	return C4DOS.Co->CoAddClassMethod(this, name, c, type, fcn, argc);
}

VALUE*	Coffee::GetGlobalClass(const String& name)
{
	return C4DOS.Co->CoGetGlobalClass(this, name);
}

void Coffee::Wrongcnt(Int32 n, Int32 cnt)
{
	C4DOS.Co->CoWrongcnt(this, n, cnt);
}

CLASS* Coffee::AddGlobalClass(const String& name, const String& parent)
{
	return C4DOS.Co->CoAddGlobalClass(this, name, parent);
}

Bool Coffee::AddClassMember(const String& name, CLASS* c, COFFEE_STYPE symbolType)
{
	return C4DOS.Co->CoAddClassMember(this, name, c, symbolType);
}

ARRAY* Coffee::NewArray(Int32 size)
{
	return C4DOS.Co->CoNewArray(this, size);
}

Bool Coffee::AddGlobalSymbol(const String& name, const VALUE* v, COFFEE_STYPE symbolType)
{
	return C4DOS.Co->CoAddGlobalSymbol(this, name, v, symbolType);
}

Bool Coffee::AddGlobalFunction(const String& name, V_CODE fcn)
{
	return C4DOS.Co->CoAddGlobalFunction(this, name, fcn);
}

Int32 Coffee::GetType(void)
{
	return C4DOS.Co->CoGetType(this);
}

const Filename&	Coffee::GetRootFile(void)
{
	return C4DOS.Co->CoGetRootFile(this);
}

void Coffee::SetRootFile(const Filename& fn)
{
	C4DOS.Co->CoSetRootFile(this, fn);
}

void Coffee::SetError(Int32 type, const String& s1, const String& s2)
{
	C4DOS.Co->CoSetError(this, type, s1, s2);
}

void Coffee::InstallErrorHook(COFFEE_ERRORHANDLER* priv_hndl, void* priv_data)
{
	C4DOS.Co->CoInstallErrorHook(this, priv_hndl, priv_data);
}
