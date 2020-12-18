#include "vmtparser.h"

#include "error.h"
#include "sharedgrammar.h"
#include "tao/pegtl.hpp"
#include "vmtformat.h"

// case insensitive string compare
static bool istrcmp(const std::string &str1, const std::string &str2) {
  using namespace std;
  if (str1.length() != str2.length())
    return false;

  for (std::uint8_t i = 0; i < str1.length(); ++i)
    if (tolower(str1[i]) != tolower(str2[i]))
      return false;

  return true;
}

namespace vmt_grammar {
using namespace tao;
using namespace shared_grammar;

/* File Objects */
struct shadertype : pegtl::identifier {};

struct basetexture_value : filepath {};

struct basetexture
    : template_keyvalue_pair<pegtl::istring<'$', 'b', 'a', 's', 'e', 't', 'e',
                                            'x', 't', 'u', 'r', 'e'>,
                             basetexture_value> {};

struct bumpmap_value : filepath {};

struct bumpmap : template_keyvalue_pair<
                     pegtl::istring<'$', 'b', 'u', 'm', 'p', 'm', 'a', 'p'>,
                     bumpmap_value> {};

struct ssbump_value : integer {};

struct ssbump
    : template_keyvalue_pair<pegtl::istring<'$', 's', 's', 'b', 'u', 'm', 'p'>,
                             ssbump_value> {};

struct translucent_value : integer {};

struct translucent
    : template_keyvalue_pair<pegtl::istring<'$', 't', 'r', 'a', 'n', 's', 'l',
                                            'u', 'c', 'e', 'n', 't'>,
                             translucent_value> {};

struct shader
    : template_opt_class<shadertype,

                         basetexture, bumpmap, ssbump, translucent, comments> {
};

struct vmt_file : pegtl::until<pegtl::eof, pegtl::sor<

                                               comments, shader,

                                               pegtl::any>> {};

/* Actions */
template <typename Rule> struct action : pegtl::nothing<Rule> {};

template <> struct action<shadertype> {
  template <typename Input>
  static void apply(const Input &in, ValveMaterialType &vmt) {
    if (istrcmp(in.string(), "character"))
      vmt.Shader = VMTTypes::ShaderType::CHARACTER;
    else if (istrcmp(in.string(), "lightmappedgeneric"))
      vmt.Shader = VMTTypes::ShaderType::LIGHTMAPPEDGENERIC;
    else {
      maxon::String err = "Unknwon shader type: "_s + in.string().c_str();
      LogError(err);
      vmt.Shader = VMTTypes::ShaderType::UNKNOWN;
    }
  }
};

template <> struct action<basetexture_value> {
  template <typename Input>
  static void apply(const Input &in, ValveMaterialType &vmt) {
    if (vmt.Parameters.find(VMTTypes::ParameterType::BASETEXTURE) !=
        std::end(vmt.Parameters)) {
      LogError("BaseTexture redefinition.");
      return;
    }

    vmt.Parameters[VMTTypes::ParameterType::BASETEXTURE] =
        String(in.string().c_str());
  }
};

template <> struct action<bumpmap_value> {
  template <typename Input>
  static void apply(const Input &in, ValveMaterialType &vmt) {
    if (vmt.Parameters.find(VMTTypes::ParameterType::BUMPMAP) !=
        std::end(vmt.Parameters)) {
      LogError("BumpMap redefinition.");
      return;
    }

    vmt.Parameters[VMTTypes::ParameterType::BUMPMAP] =
        String(in.string().c_str());
  }
};

template <> struct action<ssbump_value> {
  template <typename Input>
  static void apply(const Input &in, ValveMaterialType &vmt) {
    if (vmt.Parameters.find(VMTTypes::ParameterType::SSBUMP) !=
        std::end(vmt.Parameters)) {
      LogError("ssbump redefinition.");
      return;
    }

    vmt.Parameters[VMTTypes::ParameterType::SSBUMP] =
        bool(std::stoi(in.string()));
  }
};

template <> struct action<translucent_value> {
  template <typename Input>
  static void apply(const Input &in, ValveMaterialType &vmt) {
    if (vmt.Parameters.find(VMTTypes::ParameterType::TRANSLUCENT) !=
        std::end(vmt.Parameters)) {
      LogError("translucent redefinition.");
      return;
    }

    vmt.Parameters[VMTTypes::ParameterType::TRANSLUCENT] =
        bool(std::stoi(in.string()));
  }
};
} // namespace vmt_grammar

maxon::Bool ParseVMT(const Filename &file, ValveMaterialType &vmt) {
  tao::pegtl::file_input infile(file.GetString().GetCStringCopy());

  maxon::Bool bOk;
  try {
    bOk = tao::pegtl::parse<vmt_grammar::vmt_file, vmt_grammar::action>(infile,
                                                                        vmt);
  } catch (tao::pegtl::parse_error &e) {
    LogErrorWhat(e);
    return false;
  } catch (tao::pegtl::input_error &e) {
    LogErrorWhat(e);
    return false;
  }

  /* check for errors */
  if (!bOk) {
    return false;
  }

  return true;
}