/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_GENERAL_H__
#define C4D_GENERAL_H__

#ifdef __API_INTERN__

	#include "ge_math.h"
	#include "operatingsystem.h"

	class String;

	//----------------------------------------------------------------------------------------
	/// @markDeprecated Use the individual functions for each plugin type instead.
	/// See Plugin Types.
	//----------------------------------------------------------------------------------------
	Bool GeRegisterPlugin(PLUGINTYPE type, Int32 id, const String& str, void* data, Int32 datasize);

	//----------------------------------------------------------------------------------------
	/// @markInternal
	//----------------------------------------------------------------------------------------
	Bool GeRegisterPluginAPI(Int32 api_version, PLUGINTYPE type, Int32 id, const String *name, void *data, Int32 datasize);

	//----------------------------------------------------------------------------------------
	/// Opens a standard rename dialog.
	/// @param[in,out] str						The string with the name to change. Assigned the new name. @callerOwnsPointed{string}
	/// @return												@trueIfOtherwiseFalse{the name was changed}
	//----------------------------------------------------------------------------------------
	Bool RenameDialog(String* str);

	/// @addtogroup POPUPEDITTEXTCALLBACK
	/// @ingroup group_enumeration
	/// @{
	#define POPUPEDITTEXTCALLBACK_TEXTCHANGED	1			///< Text was changed.
	#define POPUPEDITTEXTCALLBACK_CLOSED			2			///< Window was closed.
	#define POPUPEDITTEXTCALLBACK_CANCELED		3			///< Operation was canceled.
	#define POPUPEDITTEXTCALLBACK_CURSOR_UP		4			///< %User exited by pressing the up key.
	#define POPUPEDITTEXTCALLBACK_CURSOR_DOWN	5			///< %User exited by pressing the down key.
	/// @}

	//----------------------------------------------------------------------------------------
	/// Callback definition for PopupEditText().
	/// @param[in] mode								The callback mode: @enumerateEnum{POPUPEDITTEXTCALLBACK}
	/// @param[in] text								The new text.
	/// @param[in] userdata						The user data.
	//----------------------------------------------------------------------------------------
	typedef void PopupEditTextCallback (Int32 mode, const String &text, void* userdata);

	//----------------------------------------------------------------------------------------
	/// Opens a small popup window at (@formatParam{screenx}, @formatParam{screeny}) where the user can edit the @formatParam{changeme} string. The result is reported to the @formatParam{func} callback.
	/// @param[in] screenx						The X screen coordinate of the window.
	/// @param[in] screeny						The Y screen coordinate of the window.
	/// @param[in] width							The width of the window.
	/// @param[in] height							The height of the window.
	/// @param[in,out] changeme				The string to change.
	/// @param[in] flags							@markUnused
	/// @param[in] func								The callback function.
	/// @param[in] userdata						The user data. Passed along to the callback.
	/// @return												@trueIfOtherwiseFalse{the popup edit text could be opened}
	//----------------------------------------------------------------------------------------
	Bool PopupEditText(Int32 screenx, Int32 screeny, Int32 width, Int32 height, const String& changeme, Int32 flags, PopupEditTextCallback* func, void* userdata);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	void RestartApplication(const Utf16Char* param = nullptr, Int32 exitcode = 0, const Utf16Char** path = nullptr);

	//----------------------------------------------------------------------------------------
	/// Sets the exit code returned by @C4D when it exits.
	/// @param[in] exitCode						The exit code.
	//----------------------------------------------------------------------------------------
	void SetExitCode(Int32 exitCode);

#else

	#include "c4d_string.h"
	#include "operatingsystem.h"
	#include "c4d_baselist.h"
	#include "c4d_misc.h"

	class Filename;
	class GeDialog;
	class GeUserArea;
	class GeListHead;
	class BaseList2D;

	/// @addtogroup NEWPARSERERROR
	/// @ingroup group_enumeration
	/// @{
	#define NEWPARSERERROR_BADSTRING		(1 << 0)			///< Error in the string.
	#define NEWPARSERERROR_BADEXECUTION	(1 << 1)			///< Error in the execution.
	#define NEWPARSERERROR_MEMORYERROR	(1 << 2)			///< Memory error.
	#define NEWPARSERERROR_NUMBERERROR	(1 << 3)			///< Invalid number error.
	/// @}

	/// @addtogroup UNIT
	/// @ingroup group_enumeration
	/// @{
	#define UNIT_NONE	0				///< No units.
	#define UNIT_KM		1				///< Kilometer.
	#define UNIT_M		2				///< Meter.
	#define UNIT_CM		3				///< Centimeter.
	#define UNIT_MM		4				///< Millimeter.
	#define UNIT_UM		5				///< Micrometer.
	#define UNIT_NM		6				///< Nanometer.
	#define UNIT_MILE	7				///< Mile.
	#define UNIT_YARD	8				///< Yard.
	#define UNIT_FEET	9				///< Feet.
	#define UNIT_INCH	10			///< Inch.
	/// @}

	/// @addtogroup ANGLE
	/// @ingroup group_enumeration
	/// @{
	#define ANGLE_DEG	0			///< Degrees.
	#define ANGLE_RAD	1			///< Radians.
	/// @}

	/// @addtogroup RES
	/// @ingroup group_enumeration
	/// @{
	enum Result
	{
		RES_FALSE		= 0,			// function result not ok
		RES_TRUE		= 1,			// function result ok
		RES_MEM_ERR	= 2,			// memory error
		RES_STOP		= 3,			// stop execution (e.g. user break) but no mem error

		RES_DUM
	} ENUM_END_LIST(Result);
	/// @}

	//----------------------------------------------------------------------------------------
	/// Class to hold cached parser data.
	/// @addAllocFreeAutoAllocNote
	//----------------------------------------------------------------------------------------
	class ParserCache
	{
	private:
		ParserCache();
		~ParserCache(void);

	public:

		//----------------------------------------------------------------------------------------
		/// @allocatesA{parser cache}
		/// @return												@allocReturn{parser cache}
		//----------------------------------------------------------------------------------------
		static ParserCache* Alloc(void);

		//----------------------------------------------------------------------------------------
		/// @destructsAlloc{parser caches}
		/// @param[in,out] p							@theToDestruct{parser cache}
		//----------------------------------------------------------------------------------------
		static void Free(ParserCache*& p);

		//----------------------------------------------------------------------------------------
		/// Copies the parser cache.
		/// @param[out] dest							The destination parser cache. @callerOwnsPointed{parser cache}
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool CopyTo(ParserCache* dest);
	};

	//----------------------------------------------------------------------------------------
	/// A class to evaluate mathematical expressions.
	/// @addAllocFreeAutoAllocNote
	//----------------------------------------------------------------------------------------
	class Parser
	{
	private:
		Parser();
		~Parser();

	public:
		//----------------------------------------------------------------------------------------
		/// @allocatesA{parser}
		/// @return												@allocReturn{parser}
		//----------------------------------------------------------------------------------------
		static Parser* Alloc(void);

		//----------------------------------------------------------------------------------------
		/// @destructsAlloc{parsers}
		/// @param[in,out] pr							@theToDestruct{parser}
		//----------------------------------------------------------------------------------------
		static void Free(Parser*& pr);

		//----------------------------------------------------------------------------------------
		/// Evaluates a string using the variables added with AddVar() and the built-in expressions supported by @C4D. (See the Formula object in the manual.)
		/// @note Calls internally Init() and Calculate(), or if the string has not changed ReEval().
		/// @param[in] str								The expression to evaluate.
		/// @param[out] error							Assigned an error value if failed: @enumerateEnum{NEWPARSERERROR}
		/// @param[out] res								Assigned the result of the expression.
		/// @param[in] unit								The unit used in the expression: @enumerateEnum{UNIT}
		/// @param[in] angletype					The angle unit used in the expression: @enumerateEnum{ANGLE}
		/// @param[in] basis							The base of the number system used in the expression.
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool Eval(const String& str, Int32* error, Float* res, Int32 unit = UNIT_NONE, Int32 angletype = ANGLE_DEG, Int32 basis = 10);

		//----------------------------------------------------------------------------------------
		/// Evaluates a string using the integer variables added with AddVarLong() and the built-in expressions supported by @C4D. (See the Formula object in the manual.)
		/// @note Calls internally Init() and CalculateLong(), or if the string has not changed ReEvalLong().
		/// @param[in] str								The expression to evaluate.
		/// @param[out] error							Assigned an error values if failed: @enumerateEnum{NEWPARSERERROR}
		/// @param[out] res								Assigned the result of the expression.
		/// @param[in] unit								The unit used in the expression: @enumerateEnum{UNIT}
		/// @param[in] basis							The base of the number system used in the expression.
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool EvalLong(const String& str, Int32* error, Int32* res, Int32 unit, Int32 basis);

		//----------------------------------------------------------------------------------------
		/// Adds a variable to the parser to be evaluated.\n
		/// @b Example:
		/// @code
		/// Float vu;
		///
		/// for (i=0; i<1000; i++)
		/// {
		/// 	vu = i*0.2;
		/// 	parser->AddVar("u",&vu,true);
		///
		/// 	parser->Eval("Sin(u)",...);
		/// }
		/// @endcode
		/// @param[in] str								The name of the variable to add, this is the name that will be used in the expression string.
		/// @param[in] value							Assigned the evaluated value for the variable.
		/// @param[in] case_sensitive			@trueIfOtherwiseFalse{the variable string is case sensitive}
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool AddVar(const String& str, Float* value, Bool case_sensitive = false);

		//----------------------------------------------------------------------------------------
		/// Removes a variable from the parser evaluation.
		/// @param[in] s									The name of the variable to be removed.
		/// @param[in] case_sensitive			@trueIfOtherwiseFalse{the variable string is case sensitive}
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool RemoveVar(const String& s, Bool case_sensitive = false);

		//----------------------------------------------------------------------------------------
		/// Remove all variables from the parser evaluation.
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool RemoveAllVars(void);

		//----------------------------------------------------------------------------------------
		/// Retrieves the cached parser data.
		/// @param[out] p									Assigned the parser cache. @callerOwnsPointed{parser cache}\n
		///																This is used for instance by the Calculate() method. It makes possible to use multiple caches with one parser.
		//----------------------------------------------------------------------------------------
		void GetParserData(ParserCache* p);

		//----------------------------------------------------------------------------------------
		/// Initializes the parser with an expression string.
		/// @param[in] s									The expression string for the initialization.
		/// @param[out] error							Assigned an error value if failed: @enumerateEnum{NEWPARSERERROR}
		/// @param[in] unit								The unit used in the expression: @enumerateEnum{UNIT}
		/// @param[in] angle_unit					The angle unit used in the expression: @enumerateEnum{ANGLE}
		/// @param[in] base								The base of the number system used in the expression.
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool Init(const String& s, Int32* error, Int32 unit = UNIT_NONE, Int32 angle_unit = ANGLE_DEG, Int32 base = 10);

		//----------------------------------------------------------------------------------------
		/// Re-evaluates the expression.
		/// @warning The expression string must not change prior to using this method.
		/// @param[out] result						Assigned the result of the expression.
		/// @param[out] error							Assigned an error values if failed: @enumerateEnum{NEWPARSERERROR}
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool ReEval(Float* result, Int32* error);

		//----------------------------------------------------------------------------------------
		/// Calculates the result for an expression in an existing parser cache.
		/// @see GetParserData()
		/// @param[in] pdat								A parser cache.
		/// @param[out] result						Assigned the result of the expression.
		/// @param[out] error							Assigned an error values if failed: @enumerateEnum{NEWPARSERERROR}
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool Calculate(const ParserCache* pdat, Float* result, Int32* error);

		//----------------------------------------------------------------------------------------
		/// Adds an integer variable to the parser to be evaluated.
		/// @b Example:
		/// @code
		/// for (i=0; i<1000; i++)
		/// {
		/// 	parser->AddVar("i",&i,true);
		///
		/// 	parser->EvalLong("2*i",...);
		/// }
		/// @endcode
		/// @param[in] str								The name of the variable to add, this is the name that will be used in the string.
		/// @param[in] value							Assigned the evaluated value for the variable.
		/// @param[in] case_sensitive			@trueIfOtherwiseFalse{the variable string is case sensitive}
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool AddVarLong(const String& str, Int32* value, Bool case_sensitive = false);

		//----------------------------------------------------------------------------------------
		/// Re-evaluates the expression.
		/// @warning The expression string must not change prior to using this method.
		/// @param[out] result						Assigned the result of the expression.
		/// @param[out] error							Assigned an error values if failed: @enumerateEnum{NEWPARSERERROR}
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool ReEvalLong(Int32* result, Int32* error);

		//----------------------------------------------------------------------------------------
		/// Calculates the result for an expression in an existing parser cache.
		/// @see GetParserData()
		/// @param[in] pdat								A parser cache.
		/// @param[out] result						Assigned the result of the expression.
		/// @param[out] error							Assigned an error values if failed: @enumerateEnum{NEWPARSERERROR}
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool CalculateLong(const ParserCache* pdat, Int32* result, Int32* error);

		//----------------------------------------------------------------------------------------
		/// Resets certain functions used by the parser (Random etc.).\n
		/// This is necessary in animated situations, otherwise results will not be consistent for the same frame.
		/// @param[in] p									The parser cache to reset.
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool Reset(ParserCache* p = nullptr);

		/// @name Shader Code Generation
		/// @{

		//----------------------------------------------------------------------------------------
		/// Returns an OpenGL Shading Language representation of the parsed expression.
		/// @since R17.032
		/// @warning	Init() must be called before using this function, as it uses internally-cached data.
		///						Knowledge of the OpenGL Shading Language is required for correct use of this function.
		/// @note	The generated OpenGL shader code assigns the result of the expression to a float variable with the given name (it must be a valid GLSL identifier).\n
		///				Each expression variable name is converted to upper case before being inserted into the shader code.\n
		///				Variable names with spaces are not supported and must be valid GLSL identifiers.\n
		///				Declarations of these expression variables (such as those defined with AddVar()) must be added by the caller to the start of the code string and initialized with default values.\n
		///				It is advisable to add braces around these declarations and the generated code so as to avoid naming conflicts.
		/// @param[in] resultVariableName	The name of the variable in the shade code to which the result will be assigned.
		/// @param[out] result						The generated shader code.
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool GenerateShaderCode(const String& resultVariableName, String* result);

		//----------------------------------------------------------------------------------------
		/// Returns an OpenGL Shading Language representation of the parsed expression.
		/// @since R17.032
		/// @warning	Knowledge of the OpenGL Shading Language is required for correct use of this function.
		/// @note	The generated OpenGL shader code assigns the result of the expression to a float variable with the given name (it must be a valid GLSL identifier).\n
		///				Each expression variable name is converted to upper case before being inserted into the shader code.\n
		///				Variable names with spaces are not supported and must be valid GLSL identifiers.\n
		///				Declarations of these expression variables (such as those defined with AddVar()) must be added by the caller to the start of the code string and initialized with default values.\n
		///				It is advisable to add braces around these declarations and the generated code so as to avoid naming conflicts.
		/// @param[in] pdat								A parser cache.
		/// @param[in] resultVariableName	The name of the variable in the shade code to which the result will be assigned.
		/// @param[out] result						The generated shader code.
		/// @return												@trueIfOtherwiseFalse{successful}
		//----------------------------------------------------------------------------------------
		Bool GenerateShaderCodeFromCache(const ParserCache* pdat, const String& resultVariableName, String* result);

		/// @}
	};

	struct SerialInfo
	{
		String	nr,								///< The first @em 11 digits of the @C4D serial number.
						name,							///< The name of the user.
						organization,			///< The organization entered in the user registration.
						street,						///< The street entered in the user registration.
						city,							///< The city entered in the user registration.
						country;					///< The country entered in the user registration.
	};

	//----------------------------------------------------------------------------------------
	/// Retrieves the registration information for @C4D.\n
	/// A multi-license has the following formating: <tt>201[100]00519-ABCDEF</tt>\n
	/// The third, fourth and fifth digits equal the number of licenses, in the above example it is 100 licenses.
	/// To check for multi and single license use:
	/// @code
	/// SerialInfo si;
	/// GeGetSerialInfo(SERIALINFO_MULTILICENSE, &si);
	///
	/// if(si.nr.Content())
	/// {
	/// 	// multi-license, do something
	/// }
	/// else
	/// {
	/// 	GeGetSerialInfo(SERIALINFO_CINEMA4D, &si);
	///
	/// 	// single-license, do something
	/// }
	/// @endcode
	/// @param[in] type								The serial information to retrieve: @enumerateEnum{SERIALINFO}
	/// @param[out] si								Filled with the serial information.
	//----------------------------------------------------------------------------------------
	void GeGetSerialInfo(SERIALINFO type, SerialInfo* si);

	//----------------------------------------------------------------------------------------
	/// Retrieves the type of @C4D application that is running.
	/// @return												The version type: @enumerateEnum{VERSIONTYPE}
	//----------------------------------------------------------------------------------------
	VERSIONTYPE GeGetVersionType(void);

	//----------------------------------------------------------------------------------------
	/// Checks if either a NET server or client application is running.
	/// @return												@trueIfOtherwiseFalse{NET is running}
	//----------------------------------------------------------------------------------------
	inline Bool IsNet() { VERSIONTYPE t = GeGetVersionType(); return t == VERSIONTYPE_NET_CLIENT || t == VERSIONTYPE_NET_SERVER_UNLIMITED || t == VERSIONTYPE_NET_SERVER_3; }

	//----------------------------------------------------------------------------------------
	/// Checks if a NET server application is running.
	/// @return												@trueIfOtherwiseFalse{NET is running as server}
	//----------------------------------------------------------------------------------------
	inline Bool IsServer() { VERSIONTYPE t = GeGetVersionType(); return t == VERSIONTYPE_NET_SERVER_UNLIMITED || t == VERSIONTYPE_NET_SERVER_3; }

	//----------------------------------------------------------------------------------------
	/// Checks if a NET client application is running.
	/// @return												@trueIfOtherwiseFalse{NET is running as client}
	//----------------------------------------------------------------------------------------
	inline Bool IsClient() { VERSIONTYPE t = GeGetVersionType(); return t == VERSIONTYPE_NET_CLIENT; }

	//----------------------------------------------------------------------------------------
	/// Retrieves system information flags.
	/// @return												The system information: @enumerateEnum{SYSTEMINFO}
	//----------------------------------------------------------------------------------------
	SYSTEMINFO GeGetSystemInfo(void);

	//----------------------------------------------------------------------------------------
	/// Sets the type of mouse pointer.
	/// @warning Should only be called from the main thread.
	/// @param[in] v									The mouse pointer: @enumerateEnum{MOUSE}
	//----------------------------------------------------------------------------------------
	void GeShowMouse(Int32 v);

	//----------------------------------------------------------------------------------------
	/// Retrieves the screen dimensions in pixels.
	/// @param[in] x									The screen X coordinates to identify which display information is read (for multi-display setups).
	/// @param[in] y									The screen Y coordinates to identify which display information is read (for multi-display setups).
	/// @param[in] whole_screen				@formatConstant{true} if dimensions of the whole screen (including task bar etc.) are returned, otherwise @formatConstant{false}.
	/// @param[out] sx1								Assigned the minimum X coordinate (left).
	/// @param[out] sy1								Assigned the minimum Y coordinate (top).
	/// @param[out] sx2								Assigned the maximum X coordinate (right).
	/// @param[out] sy2								Assigned the maximum Y coordinate (bottom).
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GeGetScreenDimensions(Int32 x, Int32 y, Bool whole_screen, Int32* sx1, Int32* sy1, Int32* sx2, Int32* sy2);

	//----------------------------------------------------------------------------------------
	/// Retrieves the current timer count in milliseconds.
	/// @return												The current timer count in milliseconds.
	//----------------------------------------------------------------------------------------
	inline Int32 GeGetTimer(void) { return C4DOS.Ge->GetTimer(); }

	//----------------------------------------------------------------------------------------
	/// Get the current timer count in milliseconds.
	/// @return												The current timer count in milliseconds.
	//----------------------------------------------------------------------------------------
	inline Float64 GeGetMilliSeconds(void) { return C4DOS.Ge->GeGetMilliSeconds(); }

	//----------------------------------------------------------------------------------------
	/// Retrieves a string that contains the type of line ending characters for the running OS.
	/// @return												The type of line ending.
	//----------------------------------------------------------------------------------------
	String GeGetLineEnd(void);

	//----------------------------------------------------------------------------------------
	/// Retrieves the default frames per second.
	/// @return												The default FPS value.
	//----------------------------------------------------------------------------------------
	Int32 GeGetDefaultFPS(void);

	//----------------------------------------------------------------------------------------
	/// Retrieves information about @C4D's application runtime.
	/// @param[in] info								The information type: @enumerateEnum{CINEMAINFO}
	/// @return												The @C4D's information.
	//----------------------------------------------------------------------------------------
	UInt32 GeGetCinemaInfo(CINEMAINFO info);

	//----------------------------------------------------------------------------------------
	/// Displays a message box with the string as the text.
	/// @param[in] str								The dialog box message.
	/// @param[in] flags							The flags: @enumerateEnum{GEMB}
	/// @return												The result from the message box: @enumerateEnum{GEMB_R}
	//----------------------------------------------------------------------------------------
	GEMB_R GeOutString(const String& str, GEMB flags);

	//----------------------------------------------------------------------------------------
	/// Retrieves the type of OS that is running @C4D.
	/// @return												The OS running: @enumerateEnum{OPERATINGSYSTEM}
	//----------------------------------------------------------------------------------------
	OPERATINGSYSTEM GeGetCurrentOS(void);

	//----------------------------------------------------------------------------------------
	/// Retrieves the byte order for the platform that @C4D is running on.
	/// @return												The byte order: @enumerateEnum{BYTEORDER}
	//----------------------------------------------------------------------------------------
	BYTEORDER GeGetByteOrder(void);

	//----------------------------------------------------------------------------------------
	/// Retrieves the color values for the default @C4D gray.
	/// @param[out] r									Assigned the red component of the gray color.
	/// @param[out] g									Assigned the green component of the gray color.
	/// @param[out] b									Assigned the blue component of the gray color.
	//----------------------------------------------------------------------------------------
	void GeGetGray(Int32* r, Int32* g, Int32* b);

	//----------------------------------------------------------------------------------------
	/// Opens a color chooser dialog for the user to select a color.
	/// @param[in] col								Assigned the chosen color.
	/// @param[in] flags							Usually @em 0 or one of the following flags to use the correct color profile for display: @ref DR_COLORFIELD_ICC_BASEDOC or @ref DR_COLORFIELD_ICC_BPTEX.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GeChooseColor(Vector* col, Int32 flags);

	//----------------------------------------------------------------------------------------
	/// Opens a URL in the user's default web browser.
	/// @note The passed URL string has to be spec conform, see <a href="http://www.ietf.org/rfc/rfc1738.txt">IETF - Uniform Resource Locators</a>.
	/// @param[in] webaddress					The URL to open.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GeOpenHTML(const String& webaddress);

	//----------------------------------------------------------------------------------------
	/// Opens a font chooser dialog for the user to select a font.
	/// @param[in] bc									Assigned the selected font settings.
	/// @return												@trueIfOtherwiseFalse{a new font was chosen}
	//----------------------------------------------------------------------------------------
	Bool GeChooseFont(BaseContainer* bc);

	//----------------------------------------------------------------------------------------
	/// @markDeprecated Use the individual functions for each plugin type instead.\n
	/// See Plugin Types.
	//----------------------------------------------------------------------------------------
	Bool GeRegisterPlugin(PLUGINTYPE type, Int32 id, const String& str, void* data, Int32 datasize);

	//----------------------------------------------------------------------------------------
	/// Outputs a string to the @C4D console window.
	/// @param[in] str								The string to display in the console window.
	//----------------------------------------------------------------------------------------
	void GePrint(const String& str);

	//----------------------------------------------------------------------------------------
	/// Outputs a string to the @C4D debug console window.\n
	/// See Debug Information.
	/// @param[in] str								The string to display in the debug console window.
	//----------------------------------------------------------------------------------------
	void GeConsoleOut(const String& str);

	//----------------------------------------------------------------------------------------
	/// Retrieves information from a movie file.
	/// @param[in] fn									The filename of the movie file to retrieve the information from.
	/// @param[out] frames						Assigned the number of frames.
	/// @param[out] fps								Assigned the number of frames per second.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GeGetMovieInfo(const Filename& fn, Int32* frames, Float* fps);

	//----------------------------------------------------------------------------------------
	/// Opens a standard rename dialog.
	/// @param[in,out] str						The string with the name to change. Assigned the new name. @callerOwnsPointed{string}
	/// @return												@trueIfOtherwiseFalse{the name was changed}
	//----------------------------------------------------------------------------------------
	Bool RenameDialog(String* str);

	//----------------------------------------------------------------------------------------
	/// Retrieves the version of @C4D that is running.
	/// @return												The version of @C4D.
	//----------------------------------------------------------------------------------------
	inline Int32 GetC4DVersion(void) { return C4DOS.version; }

	//----------------------------------------------------------------------------------------
	/// Retrieves the degree character (&deg;).
	/// @return												A string containing the degree character.
	//----------------------------------------------------------------------------------------
	String GeGetDegreeChar();

	//----------------------------------------------------------------------------------------
	/// Retrieves the percent character (%).
	/// @return												A string containing the percent character.
	//----------------------------------------------------------------------------------------
	String GeGetPercentChar();

	/// @name Swap/Intel/Motorola Conversions
	/// @{

	//----------------------------------------------------------------------------------------
	/// Swaps the bytes of ::Int values. (Converting between big endian and little endian.)
	/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
	/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
	//----------------------------------------------------------------------------------------
	inline void lSwap(void* adr, Int cnt = 1) { C4DOS.Ge->lSwap(adr, cnt); }

	//----------------------------------------------------------------------------------------
	/// Swaps the low and high bytes of ::UInt values. (Converting between big endian and little endian.)
	/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
	/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
	//----------------------------------------------------------------------------------------
	inline void wSwap(void* adr, Int cnt = 1) { C4DOS.Ge->wSwap(adr, cnt); }

	//----------------------------------------------------------------------------------------
	/// Convert ::Int values to Intel format. If already in Intel (i.e on a PC) the values remain unchanged.
	/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
	/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
	//----------------------------------------------------------------------------------------
	inline void lIntel(void* adr, Int cnt = 1) { C4DOS.Ge->lIntel(adr, cnt); }

	//----------------------------------------------------------------------------------------
	/// Converts ::UInt values to Intel format. If already in Intel (i.e on a PC) the values remain unchanged.
	/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
	/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
	//----------------------------------------------------------------------------------------
	inline void wIntel(void* adr, Int cnt = 1) { C4DOS.Ge->wIntel(adr, cnt); }

//----------------------------------------------------------------------------------------
/// Converts ::Int values to Motorola format. If already in Motorola (i.e on a Mac) the values remain unchanged.
/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
//----------------------------------------------------------------------------------------
	inline void lMotor(void* adr, Int cnt = 1) { C4DOS.Ge->lMotor(adr, cnt); }

	//----------------------------------------------------------------------------------------
	/// Convert ::UInt values to Motorola format. If already in Motorola (i.e on a Mac) then the values remain unchanged.
	/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
	/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
	//----------------------------------------------------------------------------------------
	inline void wMotor(void* adr, Int cnt = 1) { C4DOS.Ge->wMotor(adr, cnt); }

	//----------------------------------------------------------------------------------------
	/// Swaps the bytes of ::Int64 values. (Converting between big endian and little endian.)
	/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
	/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
	//----------------------------------------------------------------------------------------
	inline void llSwap(void* adr, Int cnt = 1) { C4DOS.Ge->llSwap(adr, cnt); }

	//----------------------------------------------------------------------------------------
	/// Converts ::Int64 values to Intel format. If already in Intel (i.e on a PC) the values remain unchanged.
	/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
	/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
	//----------------------------------------------------------------------------------------
	inline void llIntel(void* adr, Int cnt = 1) { C4DOS.Ge->llIntel(adr, cnt); }

	//----------------------------------------------------------------------------------------
	/// Converts ::Int64 values to Motorola format. If already in Motorola (i.e on a Mac) the values remain unchanged.
	/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
	/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
	//----------------------------------------------------------------------------------------
	inline void llMotor(void* adr, Int cnt = 1) { C4DOS.Ge->llMotor(adr, cnt); }

	//----------------------------------------------------------------------------------------
	/// Swaps the bytes of ::Int values. (Converting between big endian and little endian.)
	/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
	/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
	//----------------------------------------------------------------------------------------
	inline void vlSwap(void* adr, Int32 cnt = 1)
	{
	#ifdef MAXON_TARGET_64BIT
		C4DOS.Ge->llSwap(adr, cnt);
	#else
		C4DOS.Ge->lSwap(adr, cnt);
	#endif
	}

	//----------------------------------------------------------------------------------------
	/// Converts ::Int values to Intel format. If already in Intel (i.e on a PC) then the values remain unchanged.
	/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
	/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
	//----------------------------------------------------------------------------------------
	inline void vlIntel(void* adr, Int32 cnt = 1)
	{
	#ifdef MAXON_TARGET_64BIT
		C4DOS.Ge->llIntel(adr, cnt);
	#else
		C4DOS.Ge->lIntel(adr, cnt);
	#endif
	}

	//----------------------------------------------------------------------------------------
	/// Converts Int values to Motorola format. If already in Motorola (i.e on a Mac) then the values remain unchanged.
	/// @param[in] adr								The address of the memory. @callerOwnsPointed{memory buffer or variable at @formatParam{adr}}
	/// @param[in] cnt								The number of elements in the memory buffer at @formatParam{adr} (@em 1 for a single element or variable).
	//----------------------------------------------------------------------------------------
	inline void vlMotor(void* adr, Int32 cnt = 1)
	{
	#ifdef MAXON_TARGET_64BIT
		C4DOS.Ge->llMotor(adr, cnt);
	#else
		C4DOS.Ge->lMotor(adr, cnt);
	#endif
	}

	/// @}

	/// @name Background Handler
	/// @{

	//----------------------------------------------------------------------------------------
	/// Adds a background handler with the given @formatParam{typeclass} and @formatParam{priority}. Remove it with GeRemoveBackgroundHandler().\n
	/// A background handler is a hook that @C4D processes when idle.\n
	/// The advantage over a regular thread or timer is that it always will be called at a certain position. As a result it will not block other @C4D operations (noticeable slowdown).\n
	/// @C4D itself uses background handler for example to redraw the view if it was stopped, to render material previews, to update the material preview in AM & MM, to draw the ants in @BP3D etc.
	/// @warning Background handlers must only be used if you know exactly what you are doing. They need to be thoroughly tested since a bug introduced can mess up the whole application's behavior.
	/// @param[in] handler						The background handler.
	/// @param[in] tdata							The private data. This will be passed on to the handler.
	/// @param[in] typeclass					@uniquePluginID\n
	///																There can be many handlers with the same class as long as they have different @formatParam{tdata}.
	/// @param[in] priority						The handler priority. Higher absolute values are evaluated before lower. A negative value means that it does not block positive priorities.\n
	///																Examples:
	///																@code
	///																#define BACKGROUNDHANDLER_PRIORITY_RENDERACTIVEMATERIAL			 5000
	///																#define BACKGROUNDHANDLER_PRIORITY_REDRAWVIEW								 4000
	///																#define BACKGROUNDHANDLER_PRIORITY_RENDERINACTIVEMATERIALS	 3000
	///																#define BACKGROUNDHANDLER_PRIORITY_RENDEREXTERNAL						-1000
	///																#define BACKGROUNDHANDLER_PRIORITY_REDRAWANTS								-2000
	///																#define BACKGROUNDHANDLER_PRIORITY_PREVIEWCACHE							 6000
	///																#define BACKGROUNDHANDLER_PRIORITY_PREVIEWCACHE_ANIMATION		 2000
	///																#define BACKGROUNDHANDLER_PRIORITY_PREVIEWCACHE_ASYNC				 3500
	///																@endcode
	///																The external render thread (output window) does not block the editor display.\n
	///																However, if e.g. an inactive material is being rendered the view will not be redrawn until the other thread finishes.
	//----------------------------------------------------------------------------------------
	void GeAddBackgroundHandler(BackgroundHandler* handler, void* tdata, Int32 typeclass, Int32 priority);

	//----------------------------------------------------------------------------------------
	/// Removes background handlers added with GeAddBackgroundHandler().
	/// @param[in] tdata							The registered data.
	/// @param[in] typeclass					The registered type class ID.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GeRemoveBackgroundHandler(void* tdata, Int32 typeclass);

	//----------------------------------------------------------------------------------------
	/// Stops all running background threads of the given @formatParam{typeclass}. If @formatParam{typeclass}==@em 0 all threads are stopped.
	/// @param[in] typeclass					The type class ID to stop, or @em 0 for all classes.
	/// @param[in] flags							If @formatParam{typeclass} is @ref BACKGROUNDHANDLER_TYPECLASS_C4D then the flags have the following meaning:: @enumerateEnum{BACKGROUNDHANDLERFLAGS}\n
	///																For own type classes define flags as needed, they will be routed to the background handler function.\n
	///																For example @c GeStopBackgroundThreads(BACKGROUNDHANDLER_TYPECLASS_C4D, BACKGROUNDHANDLER_FLAGS_EDITORRENDDER) will only stop the editor renderer (if it was running).\n
	///																@c GeStopBackgroundThreads(0, BACKGROUNDHANDLERFLAGS_SHUTDOWN) will kill anything running.
	//----------------------------------------------------------------------------------------
	void GeStopBackgroundThreads(Int32 typeclass, BACKGROUNDHANDLERFLAGS flags);

	//----------------------------------------------------------------------------------------
	/// Checks if any of the background threads matching @formatParam{typeclass} is running. If @formatParam{typeclass}==@em 0 all threads are checked.\n
	/// For example @c GeCheckBackgroundThreadsRunning(BACKGROUNDHANDLER_TYPECLASS_C4D, true) checks if @C4D is doing anything right now.\n
	/// If @formatParam{all}=@formatConstant{false} was passed it would not check for the external renderer and ants (which are always running in a @BP3D selection).
	/// @param[in] typeclass					The type class ID to check, or @em 0 for all classes.
	/// @param[in] all								If @formatConstant{true}, negative priorities are also checked.
	/// @return												@trueIfOtherwiseFalse{the specified background threads are running}
	//----------------------------------------------------------------------------------------
	Bool GeCheckBackgroundThreadsRunning(Int32 typeclass, Bool all);

	//----------------------------------------------------------------------------------------
	/// Called by @C4D when it is idle. It checks the background handlers if they have something to do.
	/// @param[in] typeclass					A specific type class ID, or @em 0 for all classes.
	//----------------------------------------------------------------------------------------
	void GeProcessBackgroundThreads(Int32 typeclass);

	/// @}

	//----------------------------------------------------------------------------------------
	/// Sets the type of mouse pointer.
	/// @param[in] l									The mouse pointer: @enumerateEnum{MOUSE}
	//----------------------------------------------------------------------------------------
	void SetMousePointer(Int32 l);

	//----------------------------------------------------------------------------------------
	/// Displays a bitmap into the Picture Viewer.
	/// @warning Must be called from the main thread.
	/// @param[in] fn									The filename of the bitmap to display.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool ShowBitmap(const Filename& fn);

	//----------------------------------------------------------------------------------------
	/// Displays a bitmap into the Picture Viewer.
	/// @note The bitmap will be copied for display.
	/// @warning Must be called from the main thread.
	/// @param[in] bm									The bitmap to display.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool ShowBitmap(BaseBitmap* bm);

	//----------------------------------------------------------------------------------------
	/// Stops all running threads.
	/// @note Be sure to call this routine always when a document is modified asynchronously.
	//----------------------------------------------------------------------------------------
	void StopAllThreads(void);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	Bool ShutdownThreads(Bool shutdown);

	/// @name Status
	/// @{

	//----------------------------------------------------------------------------------------
	/// Clears the status bar text.
	//----------------------------------------------------------------------------------------
	void StatusClear(void);

	//----------------------------------------------------------------------------------------
	/// Sets the status bar progress bar spinning. Needs to be triggered for every spin step.\n
	/// Use this to indicate that a plugin is still processing even if the progress bar is not increasing.
	//----------------------------------------------------------------------------------------
	void StatusSetSpin(void);

	//----------------------------------------------------------------------------------------
	/// Sets the status bar progress bar.
	/// @param[in] p									The percentage of the progress (@em 0-@em 100).
	//----------------------------------------------------------------------------------------
	void StatusSetBar(Int32 p);

	//----------------------------------------------------------------------------------------
	/// Sets the status bar text.
	/// @param[in] str								The text to display.
	//----------------------------------------------------------------------------------------
	void StatusSetText(const String& str);

	//----------------------------------------------------------------------------------------
	/// Clears the NET status bar text.
	/// @warning Reserved for Team %Render and should not be used externally.
	//----------------------------------------------------------------------------------------
	void StatusNetClear(void);

	//----------------------------------------------------------------------------------------
	/// Sets the NET status bar to @formatParam{status} state.
	/// @warning Reserved for Team %Render and should not be used externally.
	/// @param[in] status							The NET status state: @enumerateEnum{STATUSNETSTATE}
	//----------------------------------------------------------------------------------------
	void StatusSetNetLoad(STATUSNETSTATE status);

	//----------------------------------------------------------------------------------------
	/// Sets the NET status bar progress and custom color.
	/// @warning Reserved for Team %Render and should not be used externally.
	/// @param[in] p									The percentage of the progress (@em 0-@em 100).
	/// @param[in] dat								The color for the NET status bar. Can be a color constant @ref COLOR_BG, @ref COLOR_TEXT, etc. or a color Vector.
	//----------------------------------------------------------------------------------------
	void StatusSetNetBar(Int32 p, const GeData& dat);

	//----------------------------------------------------------------------------------------
	/// Sets the NET status bar text.
	/// @warning Reserved for Team %Render and should not be used externally.
	/// @param[in] str								The text to display.
	//----------------------------------------------------------------------------------------
	void StatusSetNetText(const String& str);

	/// @}

	//----------------------------------------------------------------------------------------
	/// Adds a custom event. Results in a @c CoreMessage().
	/// @see The article @link page_core_messages Core Messages@endlink for more information.
	/// @param[in] messageid					The message ID. @uniquePluginID\n
	///																Use a unique plugin ID to make sure that there is no collision.
	/// @param[in] p1									The first private data for the sent message.
	/// @param[in] p2									The second private data for the sent message.
	//----------------------------------------------------------------------------------------
	void SpecialEventAdd(Int32 messageid, UInt p1 = 0, UInt p2 = 0);

	//----------------------------------------------------------------------------------------
	/// Adds a global event to @C4D's event queue. Results in a @c CoreMessage().
	/// @see The article @link page_core_messages Core Messages@endlink for more information.
	/// @param[in] eventflag					The event to add: @enumerateEnum{EVENT}
	//----------------------------------------------------------------------------------------
	void EventAdd(EVENT eventflag = EVENT_0);

	//----------------------------------------------------------------------------------------
	/// Sends a synchronous event message (for example to make the Timeline, Timeslider etc. do an instant redraw).
	/// @param[in] messageid					The synchronous message to send: @enumerateEnum{EVMSG}
	/// @param[in] destid							@markPrivate
	/// @param[in] p1									@markPrivate
	/// @param[in] p2									@markPrivate
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GeSyncMessage(Int32 messageid, Int32 destid = 0, UInt p1 = 0, UInt p2 = 0);

	//----------------------------------------------------------------------------------------
	/// Redraws the editor views.
	/// @warning Must be called from the main thread.
	/// @param[in] flags							The draw flags: @enumerateEnum{DRAWFLAGS}
	/// @param[in] bd									The view to redraw when @ref DRAWFLAGS_ONLY_BASEDRAW is set in @formatParam{flags}.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool DrawViews(DRAWFLAGS flags, BaseDraw* bd = nullptr);

	//----------------------------------------------------------------------------------------
	/// Sends a modeling command.\n
	/// @b Examples:
	/// @code
	/// ModelingCommandData cd;
	/// cd.doc = doc;
	/// cd.op = op;
	/// if (!SendModelingCommand(MCOMMAND_CURRENTSTATETOOBJECT, cd)) return false;
	/// res = static_cast<BaseObject*>(cd.result->GetIndex(0));
	/// @endcode
	/// @code
	/// BaseContainer bc;
	/// bc.SetFloat(MDATA_SPLINE_CHAMFERRADIUS, 100.0);
	/// ModelingCommandData cd;
	/// cd.doc = doc;
	/// cd.bc = &bc;
	/// cd.op = op;
	/// if (!SendModelingCommand(MCOMMAND_SPLINE_CHAMFER, cd)) return false;
	/// @endcode
	/// @note It is usually not possible to use SendModelingCommand() during ModifyObject() or similarly functions.\n
	///				The object needs to be cloned (or put into a different document). The problem is that SendModelingCommand() rebuilds the caches, invalidating all the view caches.
	/// @param[in] command						There are several groups of IDs to use.\n
	///																First there are the internal modeling commands: (IDs are for ModelingCommandData::bc.)\n
	///																@enumerateEnum{MCOMMAND}\n
	///																Then there are the modeling library tool IDs, look up the parameters in the resource files:
	///																@enumerateEnum{ModelingToolsParameters}\n
	///																Finally there are the modeling library menu commands. (These have no parameters.)\n
	///																@enumerateEnum{ModelingToolsNoParameters}\n
	/// @param[in] data								The data for the command. Can be filled with the result for some commands.
	/// @return												@trueIfOtherwiseFalse{the command was executed}
	//----------------------------------------------------------------------------------------
	Bool SendModelingCommand(Int32 command, ModelingCommandData& data);

	//----------------------------------------------------------------------------------------
	/// Retrieves the global texture path.
	/// @param[in] i									The index of the texture path (@em 0-@em 9).
	/// @return												The global texture path for @C4D.
	//----------------------------------------------------------------------------------------
	Filename GetGlobalTexturePath(Int32 i);

	//----------------------------------------------------------------------------------------
	/// Sets the global texture path.
	/// @param[in] i									The index of the texture path (@em 0-@em 9).
	/// @param[in] fn									The texture path.
	//----------------------------------------------------------------------------------------
	void SetGlobalTexturePath(Int32 i, const Filename& fn);

	//----------------------------------------------------------------------------------------
	/// Generates the texture filename for a given texture image.
	/// @param[in] docpath						The filename of the document for the texture.
	/// @param[in] srcname						The filename of the image.
	/// @param[in] suggestedfolder		A suggested folder path for the image. Can be an empty Filename.
	/// @param[out] dstname						Assigned the generated path.
	/// @param[in] service						An optional NET render service for the operation. @callerOwnsPointed{service}
	/// @param[in] bt									An optional thread for the operation. @callerOwnsPointed{thread}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GenerateTexturePath(const Filename& docpath, const Filename& srcname, const Filename& suggestedfolder, Filename* dstname, NetRenderService* service = nullptr, BaseThread* bt = nullptr);

	//----------------------------------------------------------------------------------------
	/// Checks if the texture @formatParam{texfilename} is in the search path for files located in @formatParam{docpath}.
	/// @param[in] texfilename				The texture file name.
	/// @param[in] docpath						The document path.
	/// @return												@trueIfOtherwiseFalse{the texture file is in the search path}
	//----------------------------------------------------------------------------------------
	Bool IsInSearchPath(const Filename& texfilename, const Filename& docpath);

	//----------------------------------------------------------------------------------------
	/// Flushes the given texture.
	/// @param[in] docpath						The filename of the document with the texture.
	/// @param[in] name								The name of the texture to flush.
	/// @param[in] suggestedfolder		A suggested folder path for the image. Can be an empty Filename.
	//----------------------------------------------------------------------------------------
	void FlushTexture(const Filename& docpath, const String& name, const Filename& suggestedfolder);

	//----------------------------------------------------------------------------------------
	/// Flushes all unused textures.
	//----------------------------------------------------------------------------------------
	void FlushUnusedTextures(void);

	//----------------------------------------------------------------------------------------
	/// Retrieves the main @C4D settings container.
	/// @return												The main @C4D settings: @enumerateEnum{WPREF}
	//----------------------------------------------------------------------------------------
	BaseContainer GetWorldContainer(void);

	//----------------------------------------------------------------------------------------
	/// Retrieves the main @C4D settings container that can be changed directly.
	/// @note There are a few settings that are transferred to the world container within the call GetWorldContainer(), for example @ref WPREF_UNITS_BASIC to @ref WPREF_COLOR_SYSTEM_COLORCHOOSER.\n
	///				These settings cannot be set using GetWorldContainerInstance().
	/// @return												The main @C4D settings: @enumerateEnum{WPREF}
	//----------------------------------------------------------------------------------------
	BaseContainer* GetWorldContainerInstance(void);

	//----------------------------------------------------------------------------------------
	/// Saves the main @C4D preferences.
	//----------------------------------------------------------------------------------------
	void SaveWorldPreferences();

	//----------------------------------------------------------------------------------------
	/// Sets the main @C4D settings container.\n
	/// See GetWorldContainer() for values.
	/// @param[in] bc									The settings container.
	//----------------------------------------------------------------------------------------
	void SetWorldContainer(const BaseContainer& bc);

	//----------------------------------------------------------------------------------------
	/// Retrieves a main @C4D color.
	/// @param[in] colid							The color ID to get: @enumerateEnum{VIEWCOLOR}
	/// @return												The color value.
	//----------------------------------------------------------------------------------------
	Vector GetViewColor(Int32 colid);

	//----------------------------------------------------------------------------------------
	/// Sets one of the main @C4D colors.
	/// @param[in] colid							The color ID to set: @enumerateEnum{VIEWCOLOR}
	/// @param[in] col								The new color.
	//----------------------------------------------------------------------------------------
	void SetViewColor(Int32 colid, const Vector& col);

	//----------------------------------------------------------------------------------------
	/// Displays an error dialog for incorrectly entered values.
	/// @param[in] type								The check value range type: @enumerateEnum{CHECKVALUERANGE}
	/// @param[in] x									The lowest value.
	/// @param[in] y									The highest value.
	/// @param[in] is									The values type: @enumerateEnum{CHECKVALUEFORMAT}
	//----------------------------------------------------------------------------------------
	void ErrorStringDialog(CHECKVALUERANGE type, Float x, Float y, CHECKVALUEFORMAT is);

	//----------------------------------------------------------------------------------------
	/// Reads private serial information for a plugin. @C4D will store this data encrypted.
	/// @param[in] pluginid						@uniquePluginID
	/// @param[in] buffer							The buffer to take the data.
	/// @param[in] size								The size of the buffer. This must not exceed @em 3500.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool ReadPluginInfo(Int32 pluginid, void* buffer, Int32 size);

	//----------------------------------------------------------------------------------------
	///
	/// @param[in] pluginid						@uniquePluginID
	/// @param[in] buffer							The buffer with the data.
	/// @param[in] size								The size of the buffer. This must not exceed @em 3500.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool WritePluginInfo(Int32 pluginid, void* buffer, Int32 size);

	//----------------------------------------------------------------------------------------
	/// Reads user-specific data (e.g. login data for a user account).
	/// @note Use this method instead of ReadPluginInfo() in a license server environment.
	/// @param[in] pluginid						@uniquePluginID
	/// @param[in] buffer							The data buffer. @callerOwnsPointed{buffer}
	/// @param[in] size								The buffer size.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool ReadRegInfo(Int32 pluginid, void* buffer, Int32 size);

	//----------------------------------------------------------------------------------------
	/// Writes user-specific data (e.g. login data for a user account).
	/// @note Use this method instead of WritePluginInfo() in a license server environment.
	/// @param[in] pluginid						@uniquePluginID
	/// @param[in] buffer							The data buffer. @callerOwnsPointed{buffer}
	/// @param[in] size								The buffer size.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool WriteRegInfo(Int32 pluginid, void* buffer, Int32 size);

	//----------------------------------------------------------------------------------------
	/// Retrieves a container stored with SetWorldPluginData() from the @C4D preferences.
	/// @note This can be used by any plugin to store preferences.
	/// @param[in] id									The plugin ID that the container was stored with.
	/// @return												The retrieved container. @cinemaOwnsPointed{container}
	//----------------------------------------------------------------------------------------
	BaseContainer* GetWorldPluginData(Int32 id);

	//----------------------------------------------------------------------------------------
	/// Stores a container in the @C4D preferences.
	/// @note This can be used by any plugin to store preferences.
	/// @param[in] id									The plugin ID that the container should be associated with.
	/// @param[in] bc									The container to set.
	/// @param[in] add								If @formatConstant{true}, the container values are merged with the ones currently stored for the ID. Otherwise the previous values are lost.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetWorldPluginData(Int32 id, const BaseContainer& bc, Bool add = true);

	//----------------------------------------------------------------------------------------
	/// Retrieves a tool plugin container stored in a document.
	/// @param[in] doc								The document. @callerOwnsPointed{document}
	/// @param[in] id									The tool plugin ID.
	/// @return												The retrieved tool plugin container.
	//----------------------------------------------------------------------------------------
	BaseContainer* GetToolPluginData(BaseDocument* doc, Int32 id);

	//----------------------------------------------------------------------------------------
	/// Checks if the active tool is ghosted.
	/// @return												@trueIfOtherwiseFalse{the active tool is not ghosted}
	//----------------------------------------------------------------------------------------
	Bool GeIsActiveToolEnabled(void);

	//----------------------------------------------------------------------------------------
	/// Enumerates information about the available languages.\n
	/// Start with @formatParam{index}==@em 0 and then iterate with @formatParam{index}++ until the function returns @formatConstant{false}.
	/// @param[in] index							The language index.
	/// @param[out] extension					Assigned the language extension.
	/// @param[out] name							Assigned the human readable language name.
	/// @param[out] default_language	Assigned @formatConstant{true} if this is the default language, otherwise @formatConstant{false}.
	/// @return												@trueIfOtherwiseFalse{there was a language at @formatParam{index}}
	//----------------------------------------------------------------------------------------
	Bool GeGetLanguage(Int32 index, String* extension, String* name, Bool* default_language);

	//----------------------------------------------------------------------------------------
	/// Sets the standard suffix of a given bitmap saver plugin.\n
	/// e.g. if @formatParam{name} is @em "C:\test" and @formatParam{id} is @em 1106 (Photoshop PSD) then the returned Filename will be @em "C:\test.psd".
	/// @param[in] name								The filename.
	/// @param[in] id									The ID of the bitmap saver plugin.
	/// @return												The given file @formatParam{name} with the concatenated suffix.
	//----------------------------------------------------------------------------------------
	Filename GeFilterSetSuffix(const Filename& name, Int32 id);

	//----------------------------------------------------------------------------------------
	/// Identifies the file in @formatParam{name}.
	/// @param[in] name								The file to check.
	/// @param[in] probe							The start of a small chunk of data from the start of the file for testing this file type.\n
	///																Usually the probe size is @em 1024 bytes. @callerOwnsPointed{data}
	/// @param[in] probesize					The size of the @formatParam{probe} array.
	/// @param[in] recognition				The identification flags: @enumerateEnum{IDENTIFYFILE}
	/// @param[in] bp									For image formats this is filled with a pointer to the image loader that was identified.
	/// @return												The identification result: @enumerateEnum{IDENTIFYFILE}
	//----------------------------------------------------------------------------------------
	IDENTIFYFILE GeIdentifyFile(const Filename& name, UChar* probe, Int32 probesize, IDENTIFYFILE recognition, BasePlugin** bp);

	//----------------------------------------------------------------------------------------
	/// Retrieves the list head for scripts (@ref ID_COFFEESCRIPT).
	/// @param[in] type								Currently @em 0 is user scripts and @em 1 is system scripts.\n
	///																The user scripts are located in library/scripts whereas system scripts are in resource/scripts.)
	/// @return												The script list head. @cinemaOwnsPointed{list head}
	//----------------------------------------------------------------------------------------
	GeListHead* GetScriptHead(Int32 type);

	//----------------------------------------------------------------------------------------
	/// Retrieves the dynamic ID of the @ref ID_COFFEESCRIPT script @formatParam{bl}.\n
	/// Every script gets a dynamic ID when loaded, which is just like a regular plugin ID.\n
	/// This is necessary in many parts of the program. It is only when loading and saving the scripts that the unique (script) names are used; the ID is created dynamically at loading time.
	/// @param[in] bl									The script to get the ID for. @callerOwnsPointed{script}
	/// @return												The dynamic script ID.
	//----------------------------------------------------------------------------------------
	Int32 GetDynamicScriptID(BaseList2D* bl);

	//----------------------------------------------------------------------------------------
	/// Retrieves the command line arguments used to start @C4D in args.
	/// @note Linux only.
	/// @param[in] args								Filled with the command line arguments.
	/// @return												@trueIfOtherwiseFalse{the command line arguments could be retrieved}
	//----------------------------------------------------------------------------------------
	Bool GetCommandLineArgs(C4DPL_CommandLineArgs& args);

	//----------------------------------------------------------------------------------------
	/// Retrieves a user presentable name from an object type ID. For example @c GetObjectName(Onull) returns @em "Null".
	/// @param[in] type								An object type ID.
	/// @return												The object name for @formatParam{type}.
	//----------------------------------------------------------------------------------------
	String GetObjectName(Int32 type);

	//----------------------------------------------------------------------------------------
	/// Retrieves a user presentable name from a tag type ID.
	/// @param[in] type								A tag type ID.
	/// @return												The tag name for @formatParam{type}.
	//----------------------------------------------------------------------------------------
	String GetTagName(Int32 type);

	//----------------------------------------------------------------------------------------
	/// The inverse of GetObjectName(). Returns an object type from an object name.
	/// @param[in] name								An object name.
	/// @return												The object type for @formatParam{name}.
	//----------------------------------------------------------------------------------------
	Int32 GetObjectType(const String& name);

	//----------------------------------------------------------------------------------------
	/// The inverse of GetTagName(). Returns a tag type from a tag @formatParam{name}.
	/// @param[in] name								A tag name.
	/// @return												The tag type for @formatParam{name}.
	//----------------------------------------------------------------------------------------
	Int32 GetTagType(const String& name);

	class Registry : public GeListNode
	{
	private:
		Registry();
		~Registry();

	public:
		//----------------------------------------------------------------------------------------
		/// Gets the next Registry in the list. Convenience version of GeListNode::GetNext().
		/// @return												The next Registry, or @formatConstant{nullptr} if there is none. @cinemaOwnsPointed{registry}
		//----------------------------------------------------------------------------------------
		Registry* GetNext(void) { return (Registry*)AtCall(GetNext) (); }

		//----------------------------------------------------------------------------------------
		/// Gets the previous Registry in the list. Convenience version of GeListNode::GetNext().
		/// @return												The previous Registry, or @formatConstant{nullptr} if there is none. @cinemaOwnsPointed{registry}
		//----------------------------------------------------------------------------------------
		Registry* GetPred(void) { return (Registry*)AtCall(GetPred) (); }

		//----------------------------------------------------------------------------------------
		/// Retrieves the main ID for the registry entry.
		/// @return												The main ID: @enumerateEnum{REGISTRYTYPE}
		//----------------------------------------------------------------------------------------
		REGISTRYTYPE GetMainID(void);

		//----------------------------------------------------------------------------------------
		/// Retrieves the sub ID for the registry entry.
		/// @return												The sub ID.
		//----------------------------------------------------------------------------------------
		Int32 GetSubID(void);

		//----------------------------------------------------------------------------------------
		/// Retrieves the data stored in the registry entry.
		/// @return												The stored data.
		//----------------------------------------------------------------------------------------
		void* GetData(void);
	};

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	Bool GeRegistryAdd(Int32 sub_id, REGISTRYTYPE main_id, void* data);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	Bool GeRegistryRemove(Int32 sub_id, REGISTRYTYPE main_id);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	Registry* GeRegistryFind(Int32 sub_id, REGISTRYTYPE main_id);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	Registry* GeRegistryGetLast(REGISTRYTYPE main_id);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	Registry* GeRegistryGetFirst(REGISTRYTYPE main_id);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	Bool GeRegistryGetAutoID(Int32* id);

	//----------------------------------------------------------------------------------------
	/// Sends a plugin message to other plugins. These messages can be received with @c PluginMessage(). The message is sent to all plugin modules.
	/// @param[in] id									The ID of the message.
	/// @param[in] data								The message data. It is highly recommended as caller to own the pointed object and to not rely on the receiver to take the ownership.
	/// @return												@trueIfOtherwiseFalse{the message could be sent}
	//----------------------------------------------------------------------------------------
	Bool GePluginMessage(Int32 id, void* data);

	//----------------------------------------------------------------------------------------
	/// Checks if a task is running.
	/// @param[in] type								The task: @enumerateEnum{CHECKISRUNNING}
	/// @return												@trueIfOtherwiseFalse{the task running}
	//----------------------------------------------------------------------------------------
	Bool CheckIsRunning(CHECKISRUNNING type);

	//----------------------------------------------------------------------------------------
	/// Retrieves the default filename for a category.\n
	/// In the following example the name @ref DEFAULTFILENAME_SHADER_VOLUME is placed in front of the shader name, placing the material in the Shader category:
	/// @code
	/// RegisterMaterialPlugin(Mmy, GeGetDefaultFilename(DEFAULTFILENAME_SHADER_VOLUME)+String("MyMaterial"), 0, MyClass::Alloc, "Mmy", 0);
	/// @endcode
	/// @param[in] id									The category ID: @enumerateEnum{DEFAULTFILENAME_SHADER}
	/// @return												The filename to prepend to the material name.
	//----------------------------------------------------------------------------------------
	String GeGetDefaultFilename(Int32 id);

	//----------------------------------------------------------------------------------------
	/// Finds and makes @formatParam{bl} visible in its manager.
	/// @param[in] bl									The object to find. @callerOwnsPointed{object}
	//----------------------------------------------------------------------------------------
	void FindInManager(BaseList2D* bl);

	//----------------------------------------------------------------------------------------
	/// Sleeps for @formatParam{milliseconds} ms.
	/// @markDeprecated Do not use for idle loops. Wait()/GetResult() for condition variables/jobs/threads must be used.
	/// @param[in] milliseconds				The time to sleep in milliseconds.
	//----------------------------------------------------------------------------------------
	void GeSleep(Int32 milliseconds);

	//----------------------------------------------------------------------------------------
	/// Checks if code is run from within the main thread of @C4D.
	/// @return												@trueIfOtherwiseFalse{called from the main thread}
	//----------------------------------------------------------------------------------------
	Bool GeIsMainThread();

	//----------------------------------------------------------------------------------------
	/// Checks if code is run from within the main thread of @C4D and if the main thread does not execute any drawing code currently.
	/// @since R16.038
	/// @note	This routine can be used to make sure that no illegal code is called during a drawing operation.\n
	///				In @C4D the drawing will be started threaded or non-threaded, depending on the situation.\n
	///				It is not allowed to add e.g. undos or delete objects or materials while the drawing is in progress (this would lead to immediate crashes).\n
	///				If your code calls other routines that are not aware of their context
	///				(e.g. some code within a Message that does not know whether it was called from a drawing thread or during a command call)\n
	///				GeIsMainThreadAndNoDrawThread() can be used to detect the correct situation.
	/// @return												@trueIfOtherwiseFalse{called from the main thread and main thread does not execute a drawing operation}
	//----------------------------------------------------------------------------------------
	Bool GeIsMainThreadAndNoDrawThread();

	//----------------------------------------------------------------------------------------
	/// Helper function to detect floating point errors/exceptions. @markPrivate
	//----------------------------------------------------------------------------------------
	Int32 GeDebugSetFloatingPointChecks(Int32 on);

	// The following class is a tool to disable floating point exceptions in debug mode
	// use as
	//	{
	//		GeDebugDisableFPExceptions	disable_exceptions;
	//		... do something here (3rd party code with divisions by zero etc.)
	//	}
	// in a code block to disable floating point exceptions in debug mode
	class GeDebugDisableFPExceptions
	{
	public:
		// Constructor will disable floating point exceptions
		GeDebugDisableFPExceptions()
		{
			restore = GeDebugSetFloatingPointChecks(false);
		}

		// Destructor will restore the previous state
		~GeDebugDisableFPExceptions()
		{
			GeDebugSetFloatingPointChecks(restore);
		}

	private:
		Int32 restore;
	};

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	inline void _GeDebugBreak(Int32 line, const Char* file) { C4DOS.Ge->GeDebugBreak(line, file); }

	//----------------------------------------------------------------------------------------
	/// Prints a string to the debug console using @c vsprintf() syntax.
	/// @note Requires that the API is build in debug mode i.e. @c MAXON_TARGET_DEBUG is defined.
	/// @param[in] s									The string to print. Limited to @em 2048 characters.\n
	///																Following parameters are format for @c vsprintf().
	//----------------------------------------------------------------------------------------
	void GeDebugOut(const Char* s, ...);

	//----------------------------------------------------------------------------------------
	/// Prints a string to the debug console.
	/// @note Requires that the API is build in debug mode i.e. @c MAXON_TARGET_DEBUG is defined.
	/// @param[in] s									The string to print. Limited to @em 2048 characters.
	//----------------------------------------------------------------------------------------
	void GeDebugOut(const String& s);

	/// @cond IGNORE

	#include <stdio.h>
	#include <stdarg.h>
	inline int sprintf_safe(char* _DstBuf, int _MaxCount, const char* _Format, ...)
	{
		if (_MaxCount <= 0)
			return 0;

		va_list arp;
		va_start(arp, _Format);
		int res = vsnprintf(_DstBuf, _MaxCount, _Format, arp);
		if (res < 0 || res >= _MaxCount - 1)
		{
			if (res < 0)
				CriticalStop();
			_DstBuf[_MaxCount - 1] = 0;
			res = _MaxCount - 1;
		}
		va_end(arp);
		return res;
	}

	inline int vsprintf_safe(char* _DstBuf, int _MaxCount, const char* _Format, va_list _ArgList)
	{
		if (_MaxCount <= 0)
			return 0;

		int res = vsnprintf(_DstBuf, _MaxCount, _Format, _ArgList);
		if (res < 0 || res >= _MaxCount - 1)
		{
			if (res < 0)
				CriticalStop();
			_DstBuf[_MaxCount - 1] = 0;
			res = _MaxCount - 1;
		}
		return res;
	}

/// @endcond

	//----------------------------------------------------------------------------------------
	/// Used to select any GUI element with a lasso.
	//----------------------------------------------------------------------------------------
	class LassoSelection
	{
	private:
		LassoSelection();
		~LassoSelection();

	public:
		/// @name Alloc/Free
		/// @{

		//----------------------------------------------------------------------------------------
		/// @allocatesA{lasso selection}
		/// @return												@allocReturn{lasso selection}
		//----------------------------------------------------------------------------------------
		static LassoSelection* Alloc();

		//----------------------------------------------------------------------------------------
		/// @destructsAlloc{lasso selections}
		/// @param[in,out] ls							@theToDestruct{lasso selection}
		//----------------------------------------------------------------------------------------
		static void Free(LassoSelection*& ls);

		/// @}

		/// @name Start
		/// @{

		//----------------------------------------------------------------------------------------
		/// Starts the lasso selection in a dialog.\n
		/// If @formatParam{start_x}, @formatParam{start_y} and @formatParam{start_button} are not passed then the call waits for the user to click. It is only needed to pass them if the mouse has already been hit.\n
		/// Optionally specify a visual clipping boundary rectangle from (@formatParam{sx1},@formatParam{sy1}) to (@formatParam{sx2},@formatParam{sy2}).
		/// @param[in] dlg								The dialog to draw the lasso in. @callerOwnsPointed{dialog}
		/// @param[in] mode								The lasso mode: @enumerateEnum{MOUSESELECT}
		/// @param[in] start_x						The start X position, or @ref NOTOK to wait for mouse down.
		/// @param[in] start_y						The start Y position, or @ref NOTOK to wait for mouse down.
		/// @param[in] start_button				The start button, or @ref NOTOK to wait for mouse down: @enumerateEnum{BFM_INPUT_CHANNEL}
		/// @param[in] sx1								The optional left X coordinate of the clipping boundary.
		/// @param[in] sy1								The optional top Y coordinate of the clipping boundary.
		/// @param[in] sx2								The optional right X coordinate of the clipping boundary.
		/// @param[in] sy2								The optional bottom Y coordinate of the clipping boundary.
		/// @return												@trueIfOtherwiseFalse{the user selected elements in the dialog with the lasso}
		//----------------------------------------------------------------------------------------
		Bool Start(GeDialog& dlg, Int32 mode, Int32 start_x = NOTOK, Int32 start_y = NOTOK, Int32 start_button = NOTOK, Int32 sx1 = NOTOK, Int32 sy1 = NOTOK, Int32 sx2 = NOTOK, Int32 sy2 = NOTOK);

		//----------------------------------------------------------------------------------------
		/// Starts the lasso selection in a user area.\n
		/// If @formatParam{start_x}, @formatParam{start_y} and @formatParam{start_button} are not passed then the call waits for the user to click. It is only needed to pass them if the mouse has already been hit.\n
		/// Optionally specify a visual clipping boundary rectangle from (@formatParam{sx1},@formatParam{sy1}) to (@formatParam{sx2},@formatParam{sy2}).
		/// @param[in] ua									The user area to draw the lasso in. @callerOwnsPointed{user area}
		/// @param[in] mode								The lasso mode: @enumerateEnum{MOUSESELECT}
		/// @param[in] start_x						The start X position, or @ref NOTOK to wait for mouse down.
		/// @param[in] start_y						The start Y position, or @ref NOTOK to wait for mouse down.
		/// @param[in] start_button				The start button, or @ref NOTOK to wait for mouse down: @enumerateEnum{BFM_INPUT_CHANNEL}
		/// @param[in] sx1								The optional left X coordinate of the clipping boundary.
		/// @param[in] sy1								The optional top Y coordinate of the clipping boundary.
		/// @param[in] sx2								The optional right X coordinate of the clipping boundary.
		/// @param[in] sy2								The optional bottom Y coordinate of the clipping boundary.
		/// @return												@trueIfOtherwiseFalse{the user selected elements in the user area with the lasso}
		//----------------------------------------------------------------------------------------
		Bool Start(GeUserArea& ua, Int32 mode, Int32 start_x = NOTOK, Int32 start_y = NOTOK, Int32 start_button = NOTOK, Int32 sx1 = NOTOK, Int32 sy1 = NOTOK, Int32 sx2 = NOTOK, Int32 sy2 = NOTOK);

		//----------------------------------------------------------------------------------------
		/// Starts the lasso selection in an editor window.\n
		/// If @formatParam{start_x}, @formatParam{start_y} and @formatParam{start_button} are not passed then the call waits for the user to click. It is only needed to pass them if the mouse has already been hit.\n
		/// Optionally specify a visual clipping boundary rectangle from (@formatParam{sx1},@formatParam{sy1}) to (@formatParam{sx2},@formatParam{sy2}).
		/// @param[in] win								The editor window to draw the lasso in. @callerOwnsPointed{editor window}
		/// @param[in] mode								The lasso mode: @enumerateEnum{MOUSESELECT}
		/// @param[in] start_x						The start X position, or @ref NOTOK to wait for mouse down.
		/// @param[in] start_y						The start Y position, or @ref NOTOK to wait for mouse down.
		/// @param[in] start_button				The start button, or @ref NOTOK to wait for mouse down: @enumerateEnum{BFM_INPUT_CHANNEL}
		/// @param[in] sx1								The optional left X coordinate of the clipping boundary.
		/// @param[in] sy1								The optional top Y coordinate of the clipping boundary.
		/// @param[in] sx2								The optional right X coordinate of the clipping boundary.
		/// @param[in] sy2								The optional bottom Y coordinate of the clipping boundary.
		/// @return												@trueIfOtherwiseFalse{the user selected elements in the editor window with the lasso}
		//----------------------------------------------------------------------------------------
		Bool Start(EditorWindow* win, Int32 mode, Int32 start_x = NOTOK, Int32 start_y = NOTOK, Int32 start_button = NOTOK, Int32 sx1 = NOTOK, Int32 sy1 = NOTOK, Int32 sx2 = NOTOK, Int32 sy2 = NOTOK);

		/// @}

		/// @name Check/Test
		/// @{

		//----------------------------------------------------------------------------------------
		/// Checks if the user did not move the mouse.
		/// @return												@trueIfOtherwiseFalse{the user single clicked}
		//----------------------------------------------------------------------------------------
		Bool CheckSingleClick();

		//----------------------------------------------------------------------------------------
		/// Tests if the point (@formatParam{x},@formatParam{y}) is inside the lasso selection.
		/// @param[in] x									The X coordinate.
		/// @param[in] y									The Y coordinate.
		/// @return												@trueIfOtherwiseFalse{the point is within the lasso}
		//----------------------------------------------------------------------------------------
		Bool Test(Int32 x, Int32 y);

		//----------------------------------------------------------------------------------------
		/// Tests if the 2D polygon <tt>a-b-c-d</tt> is inside the selection. The point @c c can be equal to @c d in case of a triangle.
		/// @param[in] pa									The first point.
		/// @param[in] pb									The second point.
		/// @param[in] pc									The third point.
		/// @param[in] pd									The fourth point, or equal to pc for triangles.
		/// @return												@trueIfOtherwiseFalse{the polygon is within the lasso}
		//----------------------------------------------------------------------------------------
		Bool TestPolygon(const Vector& pa, const Vector& pb, const Vector& pc, const Vector& pd);

		/// @}

		/// @name Miscellaneous
		/// @{

		//----------------------------------------------------------------------------------------
		/// Gets the mode passed to Start().
		/// @return												The lasso mode: @enumerateEnum{MOUSESELECT}
		//----------------------------------------------------------------------------------------
		Int32 GetMode();

		//----------------------------------------------------------------------------------------
		/// Gets the selection rectangle.
		/// @param[out] x1								Assigned the X coordinate of the top-left rectangle corner.
		/// @param[out] y1								Assigned the Y coordinate of the top-left rectangle corner.
		/// @param[out] x2								Assigned the X coordinate of the bottom-right rectangle corner.
		/// @param[out] y2								Assigned the Y coordinate of the bottom-right rectangle corner.
		/// @return												@trueIfOtherwiseFalse{the selection rectangle was retrieved}
		//----------------------------------------------------------------------------------------
		Bool GetRectangle(Float& x1, Float& y1, Float& x2, Float& y2);

		/// @}
	};

	//----------------------------------------------------------------------------------------
	/// Sends a core message.
	/// @see The article @link page_core_messages Core Messages@endlink for more information.
	///
	/// @b Examples:
	/// @code
	/// // Check if command id is enabled
	/// BaseContainer msg(COREMSG_CINEMA_GETCOMMANDENABLED);
	/// msg.SetInt32(COREMSG_CINEMA_GETCOMMANDENABLED, id);
	/// Bool enabled = SendCoreMessage(COREMSG_CINEMA, msg, 0).GetInt32();
	/// @endcode
	/// @code
	/// // Get the machine features
	/// GeData data = SendCoreMessage(COREMSG_CINEMA, BaseContainer(COREMSG_CINEMA_GETMACHINEFEATURES), 0);
	/// BaseContainer* bc = data.GetContainer();
	/// @endcode
	/// @code
	/// // Execute an editor command
	/// BaseContainer msg(COREMSG_CINEMA_EXECUTEEDITORCOMMAND);
	/// msg.SetInt32(COREMSG_CINEMA_EXECUTEEDITORCOMMAND, id);
	/// msg.SetInt32(COREMSG_CINEMA_EXECUTESUBID, subid);
	/// SendCoreMessage(COREMSG_CINEMA, msg, 0);
	/// @endcode
	/// @code
	/// // Execute the options dialog of an editor command
	/// BaseContainer msg(COREMSG_CINEMA_EXECUTEEDITORCOMMAND);
	/// msg.SetInt32(COREMSG_CINEMA_EXECUTEEDITORCOMMAND, cmdID);
	/// msg.SetInt32(COREMSG_CINEMA_EXECUTESUBID, subID);
	/// msg.SetInt32(COREMSG_CINEMA_EXECUTEOPTIONMODE, true); // true to open the options dialog
	/// SendCoreMessage(COREMSG_CINEMA, msg, 0);
	/// @endcode
	/// @param[in] coreid							The core message ID: @ref COREMSG_CINEMA.
	/// @param[in] msg								The message container: @enumerateEnum{COREMSG}
	/// @param[in] eventid						The event ID.
	/// @return												The data.
	//----------------------------------------------------------------------------------------
	GeData SendCoreMessage(Int32 coreid, const BaseContainer& msg, Int32 eventid = 0);

		/// @addtogroup COREMSG_CINEMA
		/// @ingroup group_enumeration
		/// @{
		#define COREMSG_CINEMA 'CMci'			///< Requests to @C4D core.
		/// @}

	//----------------------------------------------------------------------------------------
	/// On a Mac @c GetMachineFeatures().GetString(MACHINEINFO_MACHINEMODEL) returns the model name which is set in the OS like @em "iMac4,1" or @em "MacBookPro8,2".\n
	/// If this string is pass to GetMacModel() a much more human readable string like @em "iMac Intel Core 2 Duo (aluminum enclosure) (Mid 2007)" or @em "MacBook Pro Intel Core i5, Intel Core i7, 13 (Early 2011)".
	/// @param[in] machinemodel				The machine model returned by @c GetMachineFeatures().GetString(MACHINEINFO_MACHINEMODEL).
	/// @return												The Mac model.
	//----------------------------------------------------------------------------------------
	String GetMacModel(const String& machinemodel);

	enum MachineFeaturesType
	{
		CURRENT			 = 0, // Get Machine features for the currently active OpenGL type.
		HARDWARE_OGL = 1, // Get Machine features for Hardware OpenGL.
		SOFTWARE_OGL = 2  // Get Machine features for Software OpenGL.
	} ENUM_END_LIST(MachineFeaturesType);

	//----------------------------------------------------------------------------------------
	/// Retrieves the features of the computer.
	/// @return												The container with the machine features:\n
	///																@enumerateEnum{MACHINEINFO}\n
	///																@enumerateEnum{OPENGL}
	//----------------------------------------------------------------------------------------
	BaseContainer GetMachineFeatures(MachineFeaturesType type = MachineFeaturesType::HARDWARE_OGL);

		/// @addtogroup COREMSG
		/// @ingroup group_enumeration
		/// @{
	#define COREMSG_CINEMA_GETMACHINEFEATURES			'gOGL'			///< Retrieves machine features:\n
																														///< @enumerateEnum{OPENGL}\n
																														///< @enumerateEnum{MACHINEINFO}

		/// @}

		/// @addtogroup OPENGL
		/// @ingroup group_containerid
		/// @{
		#define OPENGL_TYPE_AVAILABLE													1000
		#define OPENGL_EXTENSION_STRING												1003
		#define OPENGL_SUPPORT_GL_EXT_SEPARATE_SPECULAR_COLOR	1004
		#define OPENGL_SUPPORT_ENHANCED												1005
		#define OPENGL_RENDERER_NAME													1006
		#define OPENGL_VERSION_STRING													1007
		#define OPENGL_VENDOR_NUM															1008
			#define OPENGL_VENDOR_UNKNOWN												0
			#define OPENGL_VENDOR_NVIDIA												1
			#define OPENGL_VENDOR_ATI														2
			#define OPENGL_VENDOR_INTEL													3
			#define OPENGL_VENDOR_APPLE													4
		#define OPENGL_VENDOR_NAME														1009
		#define OPENGL_SHADING_LANGUAGE_VERSION_STRING				1010
		#define OPENGL_VERTEXBUFFER_OBJECT										1011
		#define OPENGL_FRAMEBUFFER_OBJECT											1012
		#define OPENGL_MULTITEXTURE														1013
		#define OPENGL_MAX_2DTEXTURE_SIZE											1014
		#define OPENGL_MAX_3DTEXTURE_SIZE											1015
		#define OPENGL_MAX_TEXCOORD														1016
		#define OPENGL_MAX_TEX_IMAGE_UNITS_VERTEX							1017
		#define OPENGL_MAX_TEX_IMAGE_UNITS_FRAGMENT						1018
		#define OPENGL_MAX_VP_INSTRUCTIONS										1019
		#define OPENGL_MAX_FP_INSTRUCTIONS										1020
		#define OPENGL_FLOATINGPOINT_TEXTURE									1021
		#define OPENGL_NONPOWEROF2_TEXTURE										1022
		#define OPENGL_DEPTH_TEXTURE													1023
		#define OPENGL_CG_TOOLKIT															1024
		#define OPENGL_MAX_TEXTURE_INDIRECTIONS								1025
		#define OPENGL_CG_LATEST_VERTEX_PROFILE								1026
		#define OPENGL_CG_LATEST_FRAGMENT_PROFILE							1027
		#define OPENGL_CG_LATEST_VERTEX_PROFILE_NAME					1028
		#define OPENGL_CG_LATEST_FRAGMENT_PROFILE_NAME				1029
		#define OPENGL_DRIVER_VERSION_STRING									1030	// Only supported on Windows
		#define OPENGL_CG_VERSION_STRING											1031
		#define OPENGL_FBO_Z_DEPTH														1033
		#define OPENGL_FRAMEBUFFER_OBJECT_MULTISAMPLE					1034	// Int32 Maximum samples.
		#define OPENGL_MAX_ELEMENT_VERTICES										1035
		#define OPENGL_MAX_ELEMENT_INDICES										1036
		#define OPENGL_MAX_TEX_IMAGE_UNITS_GEOMETRY						1037
		#define OPENGL_CG_LATEST_GEOMETRY_PROFILE							1038
		#define OPENGL_CG_LATEST_GEOMETRY_PROFILE_NAME				1039
		#define OPENGL_VERSION_INT														1040
		#define OPENGL_GLSL_VERSION_INT												1041
		#define OPENGL_MAX_RENDERBUFFER_SAMPLES								1042
		#define OPENGL_RENDERBUFFER_MASK											1043	// UInt64
		#define OPENGL_RENDER_TO_FP16_TEXTURE									1044
		#define OPENGL_RENDER_TO_FP32_TEXTURE									1045
		#define OPENGL_STEREO_BUFFER													1046
		#define OPENGL_DRIVER_OUTDATED												1047	// only supported on Windows
		#define OPENGL_SUPPORT_PRIMITIVERESTARTINDEX					1048
		#define OPENGL_SUPPORT_GEOMETRYSHADER									1049
		#define OPENGL_SUPPORT_OSX_10_7												1050
		#define OPENGL_MAX_TEX_IMAGE_UNITS_TESS_CONTROL				1051
		#define OPENGL_MAX_TEX_IMAGE_UNITS_TESS_EVAL					1052
		#define OPENGL_MAX_TESSELLATION_LEVEL									1053
		/// @}

	/// @addtogroup MACHINEINFO
	/// @ingroup group_containerid
	/// @{
		#define MACHINEINFO_OSTYPE							2000			///< String The OS.
		#define MACHINEINFO_OSVERSION						2001			///< String The OS version.
		#define MACHINEINFO_PROCESSORTYPE				2002			///< String The processor type.
		#define MACHINEINFO_PROCESSORNAME				2003			///< String The processor name.
		#define MACHINEINFO_PROCESSORFEATURES		2004			///< String The processor features.
		#define MACHINEINFO_NUMBEROFPROCESSORS	2005			///< ::Int32 The number of processors.
		#define MACHINEINFO_MACHINEMODEL				2006			///< String The name of the computer model (Mac only).
		#define MACHINEINFO_COMPUTERNAME				2007			///< String The computer name.
		#define MACHINEINFO_USERNAME						2008			///< String The user name.
		#define MACHINEINFO_PROCESSORSPEED_MHZ	2009			///< ::Float Processor speed in MHz.
		#define MACHINEINFO_C4DBUILDID					2010			///< String The @C4D build ID.
		#define MACHINEINFO_C4DTYPE							2011			///< String The @C4D single or double precision build type (32/64 bit).
		#define MACHINEINFO_PROCESSORHTCOUNT		2012			///< ::Int32 The number of logical processors per core, @em 1 == no Hyper-threading.
		#define MACHINEINFO_PHYSICAL_RAM_SIZE		2013			///< ::Int64 The physical memory size.

		#define MACHINEINFO_LOADEDPLUGINS				3000			///< The names of the loaded plugins.
	/// @}

	//----------------------------------------------------------------------------------------
	/// Retrieves @C4D memory statistics.
	/// @param[in] stat								Assigned the memory statistics: @enumerateEnum{C4D_MEMORY_STAT}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GeGetMemoryStat(BaseContainer& stat);

	/// @addtogroup C4D_MEMORY_STAT
	/// @ingroup group_containerid
	/// @{
	#define C4D_MEMORY_STAT_MEMORY_INUSE							1				///< ::Int64: Bytes in use.
	#define C4D_MEMORY_STAT_MEMORY_PEAK								2				///< ::Int64: Peak usage in bytes.
	#define C4D_MEMORY_STAT_NO_OF_ALLOCATIONS_TOTAL		3				///< ::Int64: Total number of allocations.
	#define C4D_MEMORY_STAT_NO_OF_ALLOCATIONS_CURRENT	4				///< ::Int64: Current number of allocations.
	#define C4D_MEMORY_STAT_EOGL_TEXBUFFER						5				///< ::Int64: Texture buffer usage.
	#define C4D_MEMORY_STAT_EOGL_VERTEXBUFFER					6				///< ::Int64: Vertex buffer usage.
	#define C4D_MEMORY_STAT_LOWMEMCNT									7				///< ::Int32: Number of low memory conditions (out of memory).
	#define C4D_MEMORY_STAT_EOGL_VERTEXBUFFER_CNT			8				///< ::Int32: Number of VBOs (Vertex Buffer Objects).
	#define C4D_MEMORY_STAT_EOGL_TEXTUREBUFFER_CNT		9				///< ::Int32: Number of texture buffers.
	#define C4D_MEMORY_STAT_OPENGL_TOTAL							10			///< ::Int32: Total OpenGL memory in KB.
	#define C4D_MEMORY_STAT_OPENGL_FREE								11			///< ::Int32: Free OpenGL memory in KB.
	/// @}

	/// @addtogroup POPUPEDITTEXTCALLBACK
	/// @ingroup group_enumeration
	/// @{
	#define POPUPEDITTEXTCALLBACK_TEXTCHANGED	1			///< Text was changed.
	#define POPUPEDITTEXTCALLBACK_CLOSED			2			///< Window was closed.
	#define POPUPEDITTEXTCALLBACK_CANCELED		3			///< Operation was canceled.
	#define POPUPEDITTEXTCALLBACK_CURSOR_UP		4			///< %User exited by pressing the up key.
	#define POPUPEDITTEXTCALLBACK_CURSOR_DOWN	5			///< %User exited by pressing the down key.
	/// @}

	//----------------------------------------------------------------------------------------
	/// Opens a small popup window at (@formatParam{screenx}, @formatParam{screeny}) where the user can edit the @formatParam{changeme} string. The result is reported to the @formatParam{func} callback.
	/// @param[in] screenx						The X screen coordinate of the window.
	/// @param[in] screeny						The Y screen coordinate of the window.
	/// @param[in] width							The width of the window.
	/// @param[in] height							The height of the window.
	/// @param[in,out] changeme				The string to change.
	/// @param[in] flags							@markUnused
	/// @param[in] func								The callback function.
	/// @param[in] userdata						The user data. Passed along to the callback.
	/// @return												@trueIfOtherwiseFalse{the popup edit text could be opened}
	//----------------------------------------------------------------------------------------
	Bool PopupEditText(Int32 screenx, Int32 screeny, Int32 width, Int32 height, const String& changeme, Int32 flags, PopupEditTextCallback* func, void* userdata);

	//----------------------------------------------------------------------------------------
	/// Starts the editor renderer.
	/// @param[in] active_only				@formatConstant{true} for active object only.
	/// @param[in] raybrush						@formatConstant{true} for ray brush mode.
	/// @param[in] x1									The X coordinate of the first corner of the render rectangle.
	/// @param[in] y1									The Y coordinate of the first corner of the render rectangle.
	/// @param[in] x2									The X coordinate of the second corner of the render rectangle.
	/// @param[in] y2									The Y coordinate of the second corner of the render rectangle.
	/// @param[in] bt									The thread for the operation. @callerOwnsPointed{thread}
	/// @param[in] bd									The view to draw to. @callerOwnsPointed{view}
	/// @param[in] newthread					If @formatConstant{true}, then the editor render is done asynchronously. In that case pass @formatConstant{nullptr} for the thread.
	//----------------------------------------------------------------------------------------
	void StartEditorRender(Bool active_only, Bool raybrush, Int32 x1, Int32 y1, Int32 x2, Int32 y2, BaseThread* bt, BaseDraw* bd, Bool newthread);

	//----------------------------------------------------------------------------------------
	/// Converts @formatParam{val} to a string.
	/// @param[in] val								The value to convert to a string. Must be of type ::Float, ::Int32 or BaseTime.
	/// @param[in] format							The format: @enumerateEnum{FORMAT_NUMBERS}
	/// @param[in] fps								The frames per second, for time values.
	/// @param[in] bUnit							If @formatConstant{true} the unit is included in the formatted string.
	/// @return												The formatted string.
	//----------------------------------------------------------------------------------------
	String FormatNumber(const GeData& val, Int32 format, Int32 fps, Bool bUnit = true);

	//----------------------------------------------------------------------------------------
	/// Converts a string to a data value of type ::Float, ::Int32 or BaseTime.
	/// @param[in] text								The string to convert to a value.
	/// @param[in] format							The format: @enumerateEnum{FORMAT_NUMBERS}
	/// @param[in] fps								The frames per second, for time values.
	/// @param[in] lengthunit					Can be used to override the units conversion. By default it will use the document's units.\n
	///																For example a string of @em "50" will result in @em 0.5 if the document's units are Meters and the unit display setting is centimeters.\n
	///																If @formatParam{lengthunit} is specified its value will be used instead of the document's units setting.
	/// @return												The converted value.
	//----------------------------------------------------------------------------------------
	GeData StringToNumber(const String& text, Int32 format, Int32 fps, const LENGTHUNIT* lengthunit = nullptr);

	//----------------------------------------------------------------------------------------
	/// Executes commands.
	/// @param[in] id									The command ID.
	/// @param[in] subid							The sub ID. (Used for scripts.)
	//----------------------------------------------------------------------------------------
	void CallCommand(Int32 id, Int32 subid = 0);

	//----------------------------------------------------------------------------------------
	/// Gets the name of a command.
	/// @param[in] id									The command ID.
	/// @return												The command name.
	//----------------------------------------------------------------------------------------
	String GetCommandName(Int32 id);

	//----------------------------------------------------------------------------------------
	/// Gets the help string of a command.
	/// @param[in] id									The ID of the command.
	/// @return												The help string.
	//----------------------------------------------------------------------------------------
	String GetCommandHelp(Int32 id);

	//----------------------------------------------------------------------------------------
	/// Checks if a command is enabled.
	/// @param[in] id									The ID of the command.
	/// @return												@trueIfOtherwiseFalse{the command is enabled}
	//----------------------------------------------------------------------------------------
	Bool IsCommandEnabled(Int32 id);

	//----------------------------------------------------------------------------------------
	/// Checks if a command is checked.
	/// @param[in] id									The ID of the command.
	/// @return												@trueIfOtherwiseFalse{the command is checked}
	//----------------------------------------------------------------------------------------
	Bool IsCommandChecked(Int32 id);

	//----------------------------------------------------------------------------------------
	/// Checks if it is possible to send a mail.
	/// @return												@trueIfOtherwiseFalse{it is possible to send mail using SendMail()}
	//----------------------------------------------------------------------------------------
	Bool SendMailAvailable();

	//----------------------------------------------------------------------------------------
	/// Sends a mail using the operating system mail API.
	/// @note Check first with SendMailAvailable() that mailing is allowed.
	/// @warning ::String/::Filename arrays parameters must end with an empty @ref String()/@ref Filename().
	/// @param[in] t_subject					The subject.
	/// @param[in] t_to								The destination addresses String array, or @formatConstant{nullptr}. String array must end with an empty String().
	/// @param[in] t_cc								The Cc addresses String array, or @formatConstant{nullptr}. String array must end with an empty String().
	/// @param[in] t_bcc							The Bcc addresses String array, or @formatConstant{nullptr}. String array must end with an empty String().
	/// @param[in] t_attachments			The attachments Filename array, or @formatConstant{nullptr}. Filename array must end with an empty Filename().
	/// @param[in] t_body							The text body.
	/// @param[in] flags							The flags: @ref SENDMAIL_SENDDIRECTLY.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SendMail(const String& t_subject, const String* t_to, const String* t_cc, const String* t_bcc, Filename* t_attachments, const String& t_body, Int32 flags);
		#define SENDMAIL_SENDDIRECTLY	1

	//----------------------------------------------------------------------------------------
	/// Retrieves system environment variables.
	/// @param[in] varname						The environment variable name.
	/// @param[out] result						Assigned the retrieved value, if available.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GetSystemEnvironmentVariable(const String& varname, String& result);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	Bool AskForAdministratorPrivileges(const String& msg, const String& caption, Bool allowsuperuser, void** token);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	void EndAdministratorPrivileges();

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	void RestartApplication(const Utf16Char* param = nullptr, Int32 exitcode = 0, const Utf16Char** path = nullptr);

	//----------------------------------------------------------------------------------------
	/// Sets the exit code returned by @C4D when it exits.
	/// @param[in] exitCode						The exit code.
	//----------------------------------------------------------------------------------------
	void SetExitCode(Int32 exitCode);

	//----------------------------------------------------------------------------------------
	/// Forces a redraw of the GUI, for example after a change of the preferences or Linear Workflow settings.
	//----------------------------------------------------------------------------------------
	void GeUpdateUI();

	//----------------------------------------------------------------------------------------
	/// @markInternal
	//----------------------------------------------------------------------------------------
	class DebugTimer
	{
		Int32 m_lasttime;
		Char* m_str;

	public:
		explicit DebugTimer(Char* str)
		{
			m_lasttime = GeGetTimer();
			m_str = str;
		}
		~DebugTimer()
		{
			if (m_lasttime != 0)
				GeDebugOut(m_str, GeGetTimer() - m_lasttime);
		}
	};

	/// @addtogroup SHORTCUT
	/// @ingroup group_containerid
	/// @{
	#define SHORTCUT_PLUGINID		1000			///< ::Int32 Command ID.
	#define SHORTCUT_ADDRESS		1001			///< ::Int32 Manager ID, registered with RegisterManagerInformation(), or @em 0 for global shortcuts.
	#define SHORTCUT_OPTIONMODE	1002			///< ::Bool @formatConstant{true} to bring up the options dialog.
	/// @}

	//----------------------------------------------------------------------------------------
	/// Retrieves the global shortcut count.
	/// @return												The number of shortcuts.
	//----------------------------------------------------------------------------------------
	Int32 GetShortcutCount();

	//----------------------------------------------------------------------------------------
	/// Retrieves the shortcut at @formatParam{index}.
	/// @param[in] index							The shortcut index: @em 0 <= @formatParam{index} < GetShortcutCount()
	/// @return												The retrieved shortcut.
	//----------------------------------------------------------------------------------------
	BaseContainer GetShortcut(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Adds the shortcut in @formatParam{bc} to the shortcut list.
	/// @param[in] bc									The container for the shortcut to add: @enumerateEnum{SHORTCUT}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool AddShortcut(const BaseContainer& bc);

	//----------------------------------------------------------------------------------------
	/// Removes the shortcut at @formatParam{index}.
	/// @param[in] index							The shortcut index: @em 0 <= @formatParam{index} < GetShortcutCount()
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool RemoveShortcut(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Loads shortcuts.
	/// @param[in] fn									The file with the shortcuts to load.
	/// @param[in] add								@formatConstant{true} to add the shortcuts, instead of replacing.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool LoadShortcutSet(const Filename& fn, Bool add);

	//----------------------------------------------------------------------------------------
	/// Save shortcuts.
	/// @param[in] fn									The file to save the shortcuts to.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SaveShortcutSet(const Filename& fn);

	//----------------------------------------------------------------------------------------
	/// Finds all shortcuts assigned to a command.
	/// @param[in] pluginid						The plugin ID to search for.
	/// @param[out] indexarray				Filled with the found IDs. @callerOwnsPointed{array}
	/// @param[in] maxarrayelements		The size of @formatParam{indexarray}
	/// @return												The number of shortcuts found.
	//----------------------------------------------------------------------------------------
	Int32 FindShortcutsFromID(Int32 pluginid, Int32* indexarray, Int32 maxarrayelements);

	//----------------------------------------------------------------------------------------
	/// Finds all commands that are assigned to a shortcut.
	/// @param[in] scut								The shortcut to search for.
	/// @param[in] idarray						Filled with the found IDs. @callerOwnsPointed{array}
	/// @param[in] maxarrayelements		The size of @formatParam{indexarray}.
	/// @return												The number of shortcuts found.
	//----------------------------------------------------------------------------------------
	Int32 FindShortcuts(const BaseContainer& scut, Int32* idarray, Int32 maxarrayelements);

	//----------------------------------------------------------------------------------------
	/// Checks if a shortcut key and qualifier are assigned to a command.
	/// @param[in] id									The plugin ID of the command.
	/// @param[in] key								The shortcut key.
	/// @param[in] qual								The qualifier key.
	/// @return												@trueIfOtherwiseFalse{the shortcut/qualifier is assigned}
	//----------------------------------------------------------------------------------------
	Bool CheckCommandShortcut(Int32 id, Int32 key, Int32 qual);

	//----------------------------------------------------------------------------------------
	/// Adds @formatParam{op} into document @formatParam{doc}.\n
	/// This function takes care for modifiers to add the new object at a certain place in the hierarchy.\n
	/// For example if shift is pressed while a new object is created it will be inserted below the active object.
	/// @param[in] doc								The current document.
	/// @param[in] op									The object to insert.
	/// @param[in] activeobj					The active object, or @formatConstant{nullptr} if no object is active.
	//----------------------------------------------------------------------------------------
	void InsertCreateObject(BaseDocument* doc, BaseObject* op, BaseObject* activeobj = nullptr);

	/// @addtogroup CLIPBOARDOWNER
	/// @ingroup group_enumeration
	/// @{
	#define CLIPBOARDOWNER_BODYPAINT			200000243			///< @BP3D owns the clipboard.
	#define CLIPBOARDOWNER_PICTUREVIEWER	200000244			///< The Picture Viewer owns the clipboard.
	/// @}

	//----------------------------------------------------------------------------------------
	/// Copies a string to the clipboard.
	/// @param[in] text								The string to copy.
	//----------------------------------------------------------------------------------------
	void CopyToClipboard(const String& text);

	//----------------------------------------------------------------------------------------
	/// Copies a bitmap to the clipboard.
	/// @param[in] map								The bitmap to copy. @callerOwnsPointed{bitmap}
	/// @param[in] ownerid						The owner ID: @enumerateEnum{CLIPBOARDOWNER}
	//----------------------------------------------------------------------------------------
	void CopyToClipboard(BaseBitmap* map, Int32 ownerid);

	//----------------------------------------------------------------------------------------
	/// Retrieves a string from the clipboard.
	/// @param[out] txt								@trueIfOtherwiseFalse{a string could be retrieved from the clipboard}
	//----------------------------------------------------------------------------------------
	Bool GetStringFromClipboard(String* txt);

	//----------------------------------------------------------------------------------------
	/// Retrieves a bitmap from the clipboard.
	/// @param[out] map								The bitmap to get. @callerOwnsPointed{bitmap}
	/// @return												@trueIfOtherwiseFalse{a bitmap could be retrieved from the clipboard}
	//----------------------------------------------------------------------------------------
	Bool GetBitmapFromClipboard(BaseBitmap* map);

	//----------------------------------------------------------------------------------------
	/// Retrieves the type of the clipboard.
	/// @return												The type of the clipboard: @enumerateEnum{CLIPBOARDTYPE}
	//----------------------------------------------------------------------------------------
	CLIPBOARDTYPE GetClipboardType(void);

	//----------------------------------------------------------------------------------------
	/// Retrieves the owner ID of the clipboard.
	/// @return												The owner ID: @enumerateEnum{CLIPBOARDOWNER}
	//----------------------------------------------------------------------------------------
	Int32 GetC4DClipboardOwner(void);

	//----------------------------------------------------------------------------------------
	/// Opens a browser popup window (e.g. the Sky object's preset popup).
	/// @param[in] mx									The X coordinate of the window.
	/// @param[in] my									The Y coordinate of the window.
	/// @param[in] defw								The width of the window.
	/// @param[in] defh								The height of the window.
	/// @param[in] pluginwindowid			A unique plugin window ID.
	/// @param[in] presettypeid				The preset plugin type ID or a type matching SDKBrowserPluginInterfaceInfo::GetPluginID().
	/// @param[in] userdata						The user data. @callerOwnsPointed{data}
	/// @param[in] callback						The popup callback.
	//----------------------------------------------------------------------------------------
	void BrowserLibraryPopup(Int32 mx, Int32 my, Int32 defw, Int32 defh, Int32 pluginwindowid, Int32 presettypeid, void* userdata, BrowserPopupCallback callback);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	const BaseBitmap* GetCursorBitmap(Int32 type, Int32& hotspotx, Int32& hotspoty);

#endif

#endif // C4D_GENERAL_H__