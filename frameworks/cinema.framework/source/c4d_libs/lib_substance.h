/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef LIB_SUBSTANCE_H__
#define LIB_SUBSTANCE_H__

#include "c4d_library.h"
#ifdef __API_INTERN__
#include "basedocument.h"
#else
#include "c4d_basedocument.h"
#endif

/// @addtogroup group_substancelibrary Substance Library
/// @ingroup group_library
/// @{
/// @since R18
/// @see The @ref page_overview_substance article.

//-------------------------------------------------------------------------------------------------
/// The Substance library contains everything needed to control the Substance Engine integration in @C4D.
/// Main topics are:
///   - Importing Substance assets into @C4D
///   - Creating materials from Substance assets and/or manually mapping Substance output channels into @C4D materials (or other places)
///   - Manipulating Substance Input parameters
///
/// Importing Substance Assets:
/// @note There's also the command ID_SUBSTANCE_COMMAND_LOADASSET, which may be shorter, if user interaction is wanted.
/// @code
/// void MySubstanceImport()
/// {
///   BaseDocument* const doc = GetActiveDocument();
///   if (doc == nullptr)
///     return;
///
///   // Setup import parameters
///   Filename fn = "some_path/nice_substance.sbsar";
///   SUBSTANCE_IMPORT_COPY copyMode = SUBSTANCE_IMPORT_COPY::NO; // do not copy the Substance archive into the project directory and use absolute path to refer to the file
///   const Bool errPopup = false; // Don't open any error messages
///   const Bool addUndo = true; // Yes, please add an undo step for the import
///   const Bool noMaterial = true; // No material will be created on import
///   BaseList2D* myImportedAsset = nullptr;
///   SUBSTANCE_IMPORT_RESULT result;
///
///   // Import
///   doc->StartUndo(); // DON'T FORGET, mandatory since we chose to add an undo step
///   result = ImportSubstance(doc, fn, copyMode, errPopup, addUndo, noMaterial, &myImportedAsset);
///   doc->EndUndo(); // DON'T FORGET, mandatory since we chose to add an undo step
///   if (result != SUBSTANCE_IMPORT_RESULT::SUCCESS)
///   {
///     // something went wrong, handle error here...
///     return;
///   }
///   // The substance got successfully inserted into the document
///   // ...
///   // return;
/// }
/// @endcode
/// 
/// Auto-creating basic material from a Substance:
/// @code
/// void MySubstanceCreateMaterial()
/// {
///   BaseDocument* const doc = GetActiveDocument();
///   if (doc == nullptr)
///     return;
///   BaseList2D* asset = GetFirstSubstance(doc);
///   if (asset == nullptr)
///   {
///     // No Substance asset in the scene
///     return;
///   }
///
///   const Int32 graphIdx = 0; // Use the first graph of the Substance
///   const SUBSTANCE_MATERIAL_MODE mode = SUBSTANCE_MATERIAL_MODE::METALLIC; // Use PBR metallic/roughness workflow
///   BaseMaterial* const mat = CreateMaterial(myImportedAsset, graphIdx, mode);
///   if (mat == nullptr)
///   {
///     // Failed to create material
///     return;
///   }
///   doc->InsertMaterial(mat);
/// }
/// @endcode
///
/// Iterate over all graphs, inputs and outputs of a Substance:
/// @code
/// void MyPrintAllSubstances()
/// {
///   BaseDocument* const doc = GetActiveDocument();
///   if (doc == nullptr)
///     return;
///   AutoAlloc<AtomArray> arrSubstances;
///   if (arrSubstances == nullptr)
///     return;
///   const Bool onlySelected = false; // Get all Substances in the document
///   GetSubstances(doc, arrSubstances, onlySelected);
///   for (Int32 idxSubstance = 0; idxSubstance < arrSubstances->GetCount(); ++idxSubstance)
///   {
///     BaseList2D* const asset = static_cast<BaseList2D*>(arrSubstances->GetIndex(idxSubstance));
///     if (asset == nullptr)
///       continue; // This should not happen, but safe is safe
///
///     GePrint("Substance: " + asset->GetName();
///
///     String graphName = "";
///     void* lastGraph = nullptr, graph = nullptr;
///
///     while (graph = GetSubstanceGraph(asset, lastGraph, graphName))
///     {
///       GePrint("  Graph: " + graphName);
///
///       UInt32 inputUid;
///       Int32 inputDescId;
///       Int32 inputNumElements;
///       SUBSTANCE_INPUT_TYPE inputType;
///       String inputName;
///       void* lastInput = nullptr, input = nullptr;
///
///       GePrint("  Inputs:");
///       while (input = GetSubstanceInput(asset, graph, lastInput, inputUid, inputDescId, inputNumElements, inputType, inputName))
///       {
///         GePrint("    " + inputName + " (" + String::HexToString(inputUid) + ", " + String::IntToString(inputDescId) + ", " + String::IntToString(inputNuMElements) + ", " + String::IntToString((Int32)inputType) + ")");
///         lastInput = input;
///       }
///
///       UInt32 outputUid;
///       UInt32 outputType;
///       String outputName;
///       void* lastOutput = nullptr, output = nullptr;
///
///       GePrint("  Outputs:");
///       while (output = GetSubstanceOutput(asset, graph, lastOutput, outputUid, outputType, outputName, nullptr))
///       {
///         GePrint("    " + outputName + " (" + String::HexToString(outputUid) + ", " + String::IntToString((Int32)outputType) + ")");
///         lastOutput = output;
///       }
///       lastGraph = graph;
///     }
///   }
/// }
/// @endcode
///
/// Changing Substance input parameters:
/// This basically works the same as with every other NodeData based entity in @C4D, via SetParameter(). @see SUBSTANCE_INPUT_TYPE
/// @warn Under no circumstances the BaseContainer of Substance assets should be accessed directly.
/// The IDs for use with SetParameter() can be obtained via GetSubstanceInput().
///
///
/// Chapter Substance shader and its parameters:
/// The Substance shader has two parameters, SUBSTANCESHADER_ASSET and SUBSTANCESHADER_CHANNEL.
///
/// SUBSTANCESHADER_ASSET is a link to a Substance asset.
/// SUBSTANCESHADER_CHANNEL stores the outputUid (to be obtained via GetSubstanceOutput()) of the selected Substance output channel.
//-------------------------------------------------------------------------------------------------

/// @addtogroup group_substance_plugin_ids Substance Plugin IDs
/// @ingroup group_enumeration
/// @{
/// Substance Plugin IDs
static const Int32 ID_SUBSTANCE_ASSET										= 1032106;		///< ID of the Substance asset
static const Int32 ID_SUBSTANCE_SHADER									= 1032171;		///< ID of the Substance shader
static const Int32 ID_SUBSTANCE_LIBRARY									= 1034607;		///< ID of Substance library
static const Int32 ID_SUBSTANCE_PREFERENCES							= 1036471;		///< ID of Substance preferences
static const Int32 ID_SUBSTANCE_PRESET									= 1036526;		///< ID of the Substance content browser preset
/// @}

/// @addtogroup group_substance_command_ids Substance Command IDs
/// @ingroup group_enumeration
/// @{
/// Substance Command IDs, use with CallCommand()
static const Int32 ID_SUBSTANCE_COMMAND_LOADASSET				= 1032109;		///< Opens a file requester and imports the chosen Substance asset into the active document.
static const Int32 ID_SUBSTANCE_COMMAND_REIMPORT				= 1036975;		///< Reloads the Substance assets currently selected in Substance Asset Manager
static const Int32 ID_SUBSTANCE_COMMAND_OPENMANAGER			= 1032108;		///< Opens the Substance Asset Manager.
static const Int32 ID_SUBSTANCE_COMMAND_SELECT_ALL			= 1037143;		///< Selects all Substance assets in the active document
static const Int32 ID_SUBSTANCE_COMMAND_DESELECT_ALL		= 1037144;		///< Deselects all Substance assets in the active document
static const Int32 ID_SUBSTANCE_COMMAND_SYNCTRCLIENTS		= 1036066;		///< Synchronizes the Substance Engine setting of all TeamRender clients based on the setting in Substance preferences
/// @}

/// @addtogroup group_substance_message_ids Substance Message IDs
/// @ingroup group_enumeration
/// @{
/// Substance Message IDs, use with Message()
static const Int32 MSG_SUBSTANCE_SHD_GETBITMAP					= 1035319;		///< Send to a Substance shader to request its texture, thought for external renderers, the corresponding data is SubstanceShdGetBitmap
/// @}

//----------------------------------------------------------------------------------------
/// Data structure for message MSG_SUBSTANCE_SHD_GETBITMAP.
/// @see group_substance_message_ids
//----------------------------------------------------------------------------------------
struct SubstanceShdGetBitmap // structure for message MSG_SUBSTANCE_SHD_GETBITMAP
{
	BaseBitmap*			_pBmp;			///< Pass as nullptr, contains pointer to texture bitmap on return, sender owns pointed bitmap
	ICONDATAFLAGS		_bmpflags;	///< Pass ICONDATAFLAGS_0, currently not in use

	SubstanceShdGetBitmap() : _pBmp(nullptr), _bmpflags(ICONDATAFLAGS_0)
	{
	}
};

/// @note Values need to match Fsubstanceimport resource
/// @addtogroup SUBSTANCE_MATERIAL_MODE
/// @ingroup group_enumeration
/// @{
enum class SUBSTANCE_MATERIAL_MODE
{
	STANDARD		= 0,		///< Create standard material
	METALLIC		= 1,		///< Create metallic material
	GLOSSY			= 2,		///< Create glossy material
	AUTO				= 3,		///< Use heuristic to choose one of the three above (see C4D's user manual)
	NONE				= 100,	///< Do not create material
} ENUM_END_LIST(SUBSTANCE_MATERIAL_MODE);
/// @}

/// @addtogroup SUBSTANCE_IMPORT_RESULT
/// @ingroup group_enumeration
/// @{
enum class SUBSTANCE_IMPORT_RESULT
{
	SUCCESS,					///< Success
	DOESNOTEXIST,			///< File not found
	NOTANASSET,				///< Wrong file format
	UNKNOWNERROR,			///< On MemoryError or when invalid parameters were passed
} ENUM_END_LIST(SUBSTANCE_IMPORT_RESULT);
/// @}


/// @note Values need to match Fsubstanceimport resource
/// @addtogroup SUBSTANCE_IMPORT_COPY
/// @ingroup group_enumeration
/// @{
enum class SUBSTANCE_IMPORT_COPY
{
	YES,	///< Automatically copy file to project directory (relative file path)
	NO,		///< Do not copy file to project directory (absolute file path)
	ASK,	///< Ask user
} ENUM_END_LIST(SUBSTANCE_IMPORT_COPY);
/// @}

/// @addtogroup SUBSTANCE_INPUT_TYPE
/// @ingroup group_enumeration
/// @{
enum class SUBSTANCE_INPUT_TYPE
{
	INTEGER,			///< Integer, one DescId, Int32
	INTEGER_2,		///< Two component integer vector, two DescIds, Int32
	INTEGER_3,		///< Three component integer vector, three DescIds, Int32
	INTEGER_4,		///< Four component integer vector, four DescIds, Int32
	BOOL,					///< Boolean, one DescId, Bool
	FLOAT,				///< Float, one DescId, Float
	FLOAT_2,			///< Two component float vector, two DescIds, Float
	FLOAT_3,			///< Three component float vector, three DescIds Float
	FLOAT_4,			///< Four component float vector, four Desc Ids, Float
	IMAGE,				///< Image input, one DescId, Filename
	STRING,				///< String, one DescId, String
	COLOR_RGB,		///< RGB color vector, one DescId, Vector
	COLOR_RGBA,		///< RGBA color vector, two DescIds, Vector and Float
	RESOLUTION,		///< Substance output resolution, two DescIds, Integer, range 4 to 11, 2^n pixels (16 pixels to 2048 pixels)
} ENUM_END_LIST(SUBSTANCE_INPUT_TYPE);
/// @}

/// @name Create
/// @{

//----------------------------------------------------------------------------------------
/// Import a Substance Asset file (.sbsar) into @formatParam{doc}. 
/// @param[in] doc								Pointer to the document to import into
/// @param[in] fn									Filename of the Substance Asset file
/// @param[in,out] copyFile				@enumerateEnum{SUBSTANCE_IMPORT_COPY}, determines, if Substance Asset files are copied into the project folder (and therefore referenced with relative path).\n
///																If set to ASK, user's choice will be returned.
///																@note When set to ASK, the function obviously has to be called in a context, where user interaction is allowed.
/// @param[in] errPopup						If set to true, problems will be communicated to the user with a message requester.
///																@note When set to true, the function obviously has to be called in a context, where user interaction is allowed.
/// @param[in] addUndo						If set to true, an undo step will be added for the import. Caller has to care for the surrounding StartUndo() and EndUndo() calls.
/// @param[in] noMaterial					By default, materials will be created based on the configuration in preferences. Set to true, to suppress any creation of materials.
/// @param[in,out] assetPtr				A pointer to a Substance asset pointer. If not nullptr, the pointer to the imported Substance Asset will be returned here.
/// @return												@enumerateEnum{SUBSTANCE_IMPORT_RESULT}
//----------------------------------------------------------------------------------------
SUBSTANCE_IMPORT_RESULT ImportSubstance(BaseDocument* const doc, const Filename& fn, SUBSTANCE_IMPORT_COPY& copyFile, Bool errPopup, Bool addUndo, Bool noMaterial, BaseList2D** assetPtr);

//----------------------------------------------------------------------------------------
/// Create a Cinema 4D standard material from @formatParam{asset}.
/// @param[in] asset							Pointer to a Substance asset
/// @param[in] graphIndex					Index of the graph to use (for multi-graph Substances)
/// @param[in] mode								@enumerateEnum{SUBSTANCE_MATERIAL_MODE}, material creation mode
/// @return												The created material, @callerOwnsPointed{material}
//----------------------------------------------------------------------------------------
BaseMaterial* CreateMaterial(BaseList2D* const asset, Int32 graphIndex, SUBSTANCE_MATERIAL_MODE mode);

//----------------------------------------------------------------------------------------
/// Create a Substance shader linked to @formatParam{asset}.
/// @param[in] asset							Pointer to a Substance asset
/// @return												The created Substance shader, @callerOwnsPointed{shader}
//----------------------------------------------------------------------------------------
BaseShader* CreateSubstanceShader(BaseList2D* const asset);

//----------------------------------------------------------------------------------------
/// Creates a Substance shader, links it to @formatParam{asset}, sets the Substance output to @formatParam{outputUid} and assigns the shader
/// to @formatParam{channelId} of @formatParam{c4dMaterial}.
/// @param[in] asset							Pointer to a Substance asset, the pointed Substance asset needs to be part of the document
/// @param[in] c4dMaterial				Pointer to the Material
/// @param[in] channelId					@enumerateEnum{CHANNEL}
/// @param[in] outputUid					Unique ID of the Substance output to use
/// @param[in] addUndo						If set to true, an undo step will be added for the import. Caller has to care for the surrounding StartUndo() and EndUndo() calls.
/// @return												@trueIfOtherwiseFalse{success}
//----------------------------------------------------------------------------------------
Bool AssignChannelToMaterial(BaseList2D* const asset, Material* const c4dMaterial, Int32 channelId, Int32 outputUid, Bool addUndo);

/// @}

/// @name Get and Insert
/// @{

//----------------------------------------------------------------------------------------
/// Get a pointer to the first Substance asset in @formatParam{doc} (if any).
/// @param[in] doc								Pointer to the document
/// @return												Pointer to the first Substance asset or nullptr, if none exists, @cinemaOwnsPointed{Substance asset}
//----------------------------------------------------------------------------------------
BaseList2D* GetFirstSubstance(BaseDocument* const doc);

//----------------------------------------------------------------------------------------
/// Have an @formatParam{arr} filled with pointers to all (or only selected) Substance assets in @formatParam{doc}.
/// @param[in] doc								Pointer to the document
/// @param[in] arr								Pointer to the AtomArray to fill, @callerOwnsPointed{array}
/// @param[in] selected						Set to true to get only selected Substance assets
//----------------------------------------------------------------------------------------
void GetSubstances(BaseDocument* const doc, AtomArray* arr, Bool selected);

//----------------------------------------------------------------------------------------
/// Insert @formatParam{asset} into in the @formatParam{doc} (as last element).
/// @param[in] doc								Pointer to the document
/// @param[in] asset							Pointer to the Substance asset, on success @C4D takes over the ownership of the pointed Substance asset.
/// @return												@trueIfOtherwiseFalse{success}
//----------------------------------------------------------------------------------------
Bool InsertLastSubstance(BaseDocument* const doc, BaseList2D* asset);

/// @}

/// @name Graphs, Inputs, Outputs
/// @{

//----------------------------------------------------------------------------------------
/// This function may be used to iterate over the graphs of @formatParam{asset}. 
/// @param[in] asset							Pointer to a Substance asset
/// @param[in] prevGraph					Pass nullptr to get the first graph, pass a graph pointer to get the following graph.
/// @param[out] name							Name of the returned graph
/// @return												Pointer to identify the graph, may not be dereferenced, @cinemaOwnsPointed{graph}
//----------------------------------------------------------------------------------------
void* GetSubstanceGraph(BaseList2D* const asset, void* const prevGraph, String& name);

//----------------------------------------------------------------------------------------
/// This function may be used to iterate over the inputs of a @formatParam{graph} of @formatParam{asset}. 
/// @param[in] asset							Pointer to a Substance asset
/// @param[in] graph							Pointer to the graph
/// @param[in] prevInput					Pass nullptr to get the first input, pass an input pointer to get the following input.
/// @param[out] inputUid					Unique ID of the input
/// @param[out] firstId						ID of the first component of the input parameter in Cinema 4D (see also @formatParam{numElements}). This ID can be used to create a DescId for SetParameter().
/// @param[out] numElements				Number of description elements used in Cinema 4D to represent the Substance input parameter
/// @param[out] type							@enumerateEnum{SUBSTANCE_INPUT_TYPE}, data type of the input
/// @param[out] name							Name of the returned input
/// @return												Pointer to identify the input, may not be dereferenced, @cinemaOwnsPointed{input}
//----------------------------------------------------------------------------------------
void* GetSubstanceInput(BaseList2D* const asset, void* const graph, void* const prevInput, UInt32& inputUid, Int32& firstId, Int32& numElements, SUBSTANCE_INPUT_TYPE& type, String& name);

//----------------------------------------------------------------------------------------
/// This function may be used to iterate over the outputs of a @formatParam{graph} of @formatParam{asset}. 
/// @param[in] asset							Pointer to a Substance asset
/// @param[in] graph							Pointer to the graph
/// @param[in] prevOutput					Pass nullptr to get the first output, pass an output pointer to get the following output.
/// @param[out] outputUid					Unique ID of the output
/// @param[out] type							Output type ID
/// @param[out] name							Name of the returned output
/// @param[in,out] bmpPtr					A pointer to a BaseBitmap pointer. If not nullptr, a pointer to a clone of the output channel bitmap will be returned here. @callerOwnsPointed{BaseBitmap}
/// @return												Pointer to identify the output, may not be dereferenced, @cinemaOwnsPointed{output}
//----------------------------------------------------------------------------------------
void* GetSubstanceOutput(BaseList2D* const asset, void* const graph, void* const prevOutput, UInt32& outputUid, UInt32& type, String& name, BaseBitmap** bmpPtr);

/// @}

/// @name Preferences
/// @{

//----------------------------------------------------------------------------------------
/// Convenience function to get the material creation mode set in Substance preferences
/// @return												@enumerateEnum{SUBSTANCE_MATERIAL_MODE}
//----------------------------------------------------------------------------------------
SUBSTANCE_MATERIAL_MODE PrefsGetMaterialModeSetting();

//----------------------------------------------------------------------------------------
/// Convenience function to get the preview mode for Content Browser set in Substance preferences
/// @return												Zero for mosaic preview, otherwise rendered preview scene
//----------------------------------------------------------------------------------------
Int32 PrefsGetPreviewSetting();

/// @}

/// @name Misc
/// @{

//----------------------------------------------------------------------------------------
/// Check if @formatParam{mat} contains any Substance shaders.
/// @param[in] mat								Pointer to a material to check for Substance shaders
/// @return												@trueIfOtherwiseFalse{the material uses a Substance shader}
//----------------------------------------------------------------------------------------
Bool MaterialUsesSubstance(BaseMaterial* const mat);

//----------------------------------------------------------------------------------------
/// Returns an image with previews of the output channels of @formatParam{asset}.
/// @note While the Substance asset won't have to be re-rendered, this operation still involves downscaling of all Substance outputs.
/// @param[in] asset							Pointer to the Substance asset
/// @param[in] w									Width of the preview image
/// @param[in] h									Height of the preview image
/// @return												Pointer to the resulting BaseBitmap, @callerOwnsPointed{BaseBitmap}
//----------------------------------------------------------------------------------------
BaseBitmap* GetSubstanceMosaicPreview(BaseList2D* const asset, Int32 w, Int32 h);

/// @}

/// @name Private
/// @{

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
void UpdateImageInputPaths(BaseList2D* const asset, String& path);

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
void CloneReferencedSubstances(BaseDocument* const doc, BaseShader* const shd, BaseDocument* const ddoc, BaseShader* const dshd);

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
void CloneReferencedSubstancesObject(BaseDocument* const docSrc, BaseObject* const opSrc, BaseDocument* const docDst, BaseObject* const opDst);

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
void InsertSubstancePreviewScene(BaseDocument* const doc, BaseList2D* const asset);

/// @}

/// @}

/// @cond IGNORE

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

struct SubstanceLibrary : public C4DLibrary
{
	SUBSTANCE_IMPORT_RESULT					(*ImportSubstance)									(BaseDocument* const doc, const Filename& fn, SUBSTANCE_IMPORT_COPY& copyFile, Bool guiOp, Bool addUndo, Bool noMaterial, BaseList2D** assetPtr);
	Bool														(*AssignAssetChannelToMaterial)			(BaseList2D* const asset, Material* const c4dMaterial, const Int32 channelId, Int32 uid, Bool addUndo);
	BaseList2D*											(*GetFirstSubstance)								(BaseDocument* const doc);
	void														(*GetSubstances)										(BaseDocument* const doc, AtomArray* arr, Bool selected);
	Bool														(*SubstanceInsertLast)							(BaseDocument* const doc, BaseList2D* const asset);
	void														(*CloneReferencedSubstances)				(BaseDocument* const doc, BaseShader* const shd, BaseDocument* const ddoc, BaseShader* const dshd);
	void														(*CloneReferencedSubstancesObject)	(BaseDocument* const docSrc, BaseObject* const opSrc, BaseDocument* const docDst, BaseObject* const opDst);
	void														(*InsertSubstancePreviewScene)			(BaseDocument* const doc, BaseList2D* const bl2d);
	void														(*UpdateImageInputPaths)						(BaseList2D* const asset, String& path);
	BaseBitmap*											(*GetSubstanceMosaicPreview)				(BaseList2D* const asset, Int32 w, Int32 h);
	SUBSTANCE_MATERIAL_MODE					(*PrefsGetCreateMaterialSetting)		();
	Int32														(*PrefsGetPreviewSetting)						();
	BaseMaterial*										(*CreateMaterial)										(BaseList2D* const asset, Int32 graphIndex, SUBSTANCE_MATERIAL_MODE mode);
	BaseShader*											(*CreateSubstanceShader)						(BaseList2D* const asset);
	void*														(*SubstanceGetGraph)								(BaseList2D* const asset, void* const prevGraph, String& name);
	void*														(*SubstanceGetInput)								(BaseList2D* const asset, void* const graph, void* const prevInput, UInt32& uid, Int32& firstDescId, Int32& numElements, SUBSTANCE_INPUT_TYPE& type, String& name);
	void*														(*SubstanceGetOutput)								(BaseList2D* const asset, void* const graph, void* const prevOutput, UInt32& uid, UInt32& type, String& name, BaseBitmap** bmpPtr);
	Bool														(*MaterialUsesSubstance)						(BaseMaterial* const mat);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

/// @endcond

#endif // LIB_SUBSTANCE_H__
