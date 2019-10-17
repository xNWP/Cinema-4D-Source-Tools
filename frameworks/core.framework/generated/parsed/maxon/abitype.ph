���      �declarations��	Namespace���)��}�(�name��lexer��Token���� �����}�(�type�K�pos�h�SourcePosition���)��}�(�file��NC:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\abitype.h��index�K �line�KhKub�escaped��ub�owner�N�children�]�(h �	Directive���)��}�(hNhhh]��code�h�#if 1�����}�(hK
hh)��}�(hhhK hKhKubh�ububh �Include���)��}�(h�maxon/apibase.h�hhh]��quote��"��template�Nubh)��}�(hh�maxon�����}�(hKhh)��}�(hhhKOhKhKubh�ubhhh]�(h �Class���)��}�(hh�ABIParamType�����}�(hKhh)��}�(hhhM�hKhK5ubh�ubhh0h]�h �	TypeAlias���)��}�(hh�type�����}�(hKhh)��}�(hhhM�hKhKubh�ubhh;h]��
simpleName�hJ�access��public��kind��	typealias�h/N�friend�NhN�id�N�point�N�
artificial�K �doclist�]��doc�h	�annotations�}��	anonymous���bases�]��T�hQh	��aubahOh?hPhQhR�class�h/h �Template���)��}��params�]�(h �TypeTemplateParam���)��}�(hh)��}�(hhhM�hKhKub�pack��hh�T�����}�(hKhh)��}�(hhhM�hKhKubh�ub�default�N�variance�Nubhj)��}�(hh)��}�(hhhM�hKhKubho�hh�CHECK�����}�(hKhh)��}�(hhhM�hKhK ubh�ubhv�void�hwNubesbhTNhNhUNhVNhWK hX]�(h�l/// <tt>ABIParamType<T>::type</tt> is an erased type which is compatible with T with respect to the calling
�����}�(hKhh)��}�(hhhK�hK
hKubh�ubh�>/// convention of the ABI when used for a function parameter.
�����}�(hKhh)��}�(hhhMhKhKubh�ubh�]/// For example, ABIParamType maps all integral, enumeration, pointer and reference types to
�����}�(hKhh)��}�(hhhM]hKhKubh�ubh�`/// the signed integral type of the same size (reference types are treated like pointer types).
�����}�(hKhh)��}�(hhhM�hKhKubh�ubh�Z/// The typical use is to reduce the number of instantiations of stub function templates,
�����}�(hKhh)��}�(hhhMhKhKubh�ubh�T/// because those stubs will work correctly even if only the erased types are used.
�����}�(hKhh)��}�(hhhMthKhKubh�ubh�///
�����}�(hKhh)��}�(hhhM�hKhKubh�ubh�b/// @tparam T											Type for which the erased, ABI-compatible param type shall be determined.
�����}�(hKhh)��}�(hhhM�hKhKubh�ubehZX{  /// <tt>ABIParamType<T>::type</tt> is an erased type which is compatible with T with respect to the calling
/// convention of the ABI when used for a function parameter.
/// For example, ABIParamType maps all integral, enumeration, pointer and reference types to
/// the signed integral type of the same size (reference types are treated like pointer types).
/// The typical use is to reduce the number of instantiations of stub function templates,
/// because those stubs will work correctly even if only the erased types are used.
///
/// @tparam T											Type for which the erased, ABI-compatible param type shall be determined.
�h[}�h]�h^]��	interface�N�refKind�N�static���refClass�N�baseInterfaces�N�derived���isError���implementation���	component���finalComponent���forward���
singleImpl���hasStaticMethods���generic�N�refClassForwardDeclared���missingInterfaces���ambiguousCalls�]��	selfCalls�]��methodNames�}�ubh:)��}�(h�aABIParamType<T,typename std::enable_if<std::is_enum<T>::value||std::is_integral<T>::value>::type>�hh0h]�hE)��}�(hh�type�����}�(hKhh)��}�(hhhMmhKhKubh�ubhh�h]�hOh�hPhQhRhSh/NhTNhNhUNhVNhWK hX]�hZh	h[}�h]�h^]���typename std::conditional<sizeof(T)==1,Char,typename std::conditional<sizeof(T)==2,Int16,typename std::conditional<sizeof(T)==4,Int32,Int64>::type>::type>::type�hQh	��aubahOh�ABIParamType�����}�(hKhh)��}�(hhhM�hKhKubh�ubhPhQhRhbh/hd)��}�hg]�hj)��}�(hh)��}�(hhhM�hKhKubho�hh�T�����}�(hKhh)��}�(hhhM�hKhKubh�ubhvNhwNubasbhTNhNhUNhVNhWK hX]�hZh	h[}�h]�h^]�h�Nh�Nh��h�Nh�Nh��h��h��h��h��h��hhÉh�NhŉhƉh�]�h�]�h�}�ubh:)��}�(h�#ABIParamType<Block<T,STRIDED,MOVE>>�hh0h]�hE)��}�(hh�type�����}�(hKhh)��}�(hhhM�hK hKubh�ubhh�h]�hOj   hPhQhRhSh/NhTNhNhUNhVNhWK hX]�hZh	h[}�h]�h^]��Block<Int,STRIDED>�hQh	��aubahOh�ABIParamType�����}�(hKhh)��}�(hhhM\hKhK7ubh�ubhPhQhRhbh/hd)��}�hg]�(hj)��}�(hh)��}�(hhhM0hKhKubho�hh�T�����}�(hKhh)��}�(hhhM9hKhKubh�ubhvNhwNubh �NontypeTemplateParam���)��}�(hh)��}�(hhhM<hKhKubho�hh�STRIDED�����}�(hKhh)��}�(hhhMAhKhKubh�ubhvNh�Bool�hwNubj  )��}�(hh)��}�(hhhMJhKhK%ubho�hh�MOVE�����}�(hKhh)��}�(hhhMOhKhK*ubh�ubhvNh�Bool�hwNubesbhTNhNhUNhVNhWK hX]�hZh	h[}�h]�h^]�h�Nh�Nh��h�Nh�Nh��h��h��h��h��h��hhÉh�NhŉhƉh�]�h�]�h�}�ubh:)��}�(h�HABIParamType<T,typename std::enable_if<std::is_pointer<T>::value>::type>�hh0h]�hE)��}�(hh�type�����}�(hKhh)��}�(hhhMhK%hKubh�ubhj;  h]�hOjC  hPhQhRhSh/NhTNhNhUNhVNhWK hX]�hZh	h[}�h]�h^]��ABIParamType<size_t>::type�hQh	��aubahOh�ABIParamType�����}�(hKhh)��}�(hhhM�hK#hKubh�ubhPhQhRhbh/hd)��}�hg]�hj)��}�(hh)��}�(hhhM�hK#hKubho�hh�T�����}�(hKhh)��}�(hhhM�hK#hKubh�ubhvNhwNubasbhTNhNhUNhVNhWK hX]�hZh	h[}�h]�h^]�h�Nh�Nh��h�Nh�Nh��h��h��h��h��h��hhÉh�NhŉhƉh�]�h�]�h�}�ubh:)��}�(h�JABIParamType<T,typename std::enable_if<std::is_reference<T>::value>::type>�hh0h]�hE)��}�(hh�type�����}�(hKhh)��}�(hhhM�hK*hKubh�ubhjf  h]�hOjn  hPhQhRhSh/NhTNhNhUNhVNhWK hX]�hZh	h[}�h]�h^]��ABIParamType<void*>::type�hQh	��aubahOh�ABIParamType�����}�(hKhh)��}�(hhhM_hK(hKubh�ubhPhQhRhbh/hd)��}�hg]�hj)��}�(hh)��}�(hhhMLhK(hKubho�hh�T�����}�(hKhh)��}�(hhhMUhK(hKubh�ubhvNhwNubasbhTNhNhUNhVNhWK hX]�hZh	h[}�h]�h^]�h�Nh�Nh��h�Nh�Nh��h��h��h��h��h��hhÉh�NhŉhƉh�]�h�]�h�}�ubhE)��}�(hh�ABIReturnType�����}�(hKhh)��}�(hhhM�hK5hKubh�ubhh0h]�hOj�  hPhQhRhSh/hd)��}�hg]�hj)��}�(hh)��}�(hhhM�hK5hKubho�hh�T�����}�(hKhh)��}�(hhhM�hK5hKubh�ubhvNhwNubasbhTNhNhUNhVNhWK hX]�(h�m/// <tt>ABIReturnType<T>::type</tt> is an erased type which is compatible with T with respect to the calling
�����}�(hKhh)��}�(hhhM5hK.hKubh�ubh�8/// convention of the ABI when used for a return value.
�����}�(hKhh)��}�(hhhM�hK/hKubh�ubh�///
�����}�(hKhh)��}�(hhhM�hK0hKubh�ubh�/// @see ABIParamType
�����}�(hKhh)��}�(hhhM�hK1hKubh�ubh�///
�����}�(hKhh)��}�(hhhM�hK2hKubh�ubh�c/// @tparam T											Type for which the erased, ABI-compatible return type shall be determined.
�����}�(hKhh)��}�(hhhM�hK3hKubh�ubehZX&  /// <tt>ABIReturnType<T>::type</tt> is an erased type which is compatible with T with respect to the calling
/// convention of the ABI when used for a return value.
///
/// @see ABIParamType
///
/// @tparam T											Type for which the erased, ABI-compatible return type shall be determined.
�h[}�h]�h^]��ABIParamType<T>�hQh	��aubehOh4hPhQhR�	namespace�h/NhTNhNhUNhVNhWK hX]�hZh	h[}�h]��preprocessorConditions�]��root�hh N�containsResourceId���registry���usings����minIndentation�K �maxIndentation�K �firstMember��ubh)��}�(hNhhh]�h h�#endif�����}�(hK
hh)��}�(hhhM�hK9hKubh�ububehOhhPhQhRj�  h/NhTNhNhUNhVNhWK hX]�hZh	h[}�h]�j�  ]�j�  hh ]�(hh)h0h;h�h�j;  jf  j�  j�  ej�  �j�  �j�  ���hxx1�N�hxx2�N�snippets�}�j�  K j�  K j�  �ub.