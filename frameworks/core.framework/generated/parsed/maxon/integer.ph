��)      �declarations��	Namespace���)��}�(�name��lexer��Token���� �����}�(�type�K�pos�h�SourcePosition���)��}�(�file��NC:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\integer.h��index�K �line�KhKub�escaped��ub�owner�N�children�]�(h �	Directive���)��}�(hNhhh]��code�h�#if 1�����}�(hK
hh)��}�(hhhK hKhKubh�ububh �Include���)��}�(h�maxon/apibase.h�hhh]��quote��"��template�Nubh)��}�(hh�maxon�����}�(hKhh)��}�(hhhKOhKhKubh�ubhhh]�(h)��}�(hNhh0h]�h h�#ifdef MAXON_ASSEMBLY_GCC_TODO�����}�(hK
hh)��}�(hhhKuhKhKubh�ububh �	TypeAlias���)��}�(hh�UIntegerBase�����}�(hKhh)��}�(hhhK�hKhKubh�ubhh0h]��
simpleName�hH�access��public��kind��	typealias�h/N�friend�NhN�id�N�point�N�
artificial�K �doclist�]��doc�h	�annotations�}��	anonymous���bases�]��UInt�hOh	��aubh)��}�(hNhh0h]�h h�#else�����}�(hK
hh)��}�(hhhK�hKhKubh�ububhC)��}�(hh�UIntegerBase�����}�(hKhh)��}�(hhhK�hKhKubh�ubhh0h]�hMhmhNhOhPhQh/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h\]��UInt32�hOh	��aubh)��}�(hNhh0h]�h h�#endif�����}�(hK
hh)��}�(hhhK�hKhKubh�ububh �Class���)��}�(hh�UInteger�����}�(hKhh)��}�(hhhK�hKhKubh�ubhh0h]�(hC)��}�(hh�Half�����}�(hKhh)��}�(hhhM�hKhKubh�ubhh�h]�hMh�hNh�public�����}�(hKhh)��}�(hhhM�hKhKubh�ubhPhQh/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h\]��UInteger<N/2>�hOh	��aubh �Function���)��}�(h�constructor�hh�h]�hMh�hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[��static���explicit���deleted���retType��void��const���params�]��
observable�N�result�Nubh�)��}�(hh�hh�h]�hMh�hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h�h�h��h�]�h �	Parameter���)��}�(h�Half�hh�low�����}�(hKhh)��}�(hhhMhKhKubh�ub�default�N�pack���input���output��ubah�Nh�Nubh�)��}�(hh�hh�h]�hMh�hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h�h�h��h�]�(h�)��}�(h�Half�hh�high�����}�(hKhh)��}�(hhhM=hKhKubh�ubh�NhÉhĈhŉubh�)��}�(h�Half�hh�low�����}�(hKhh)��}�(hhhMHhKhKubh�ubh�NhÉhĈhŉubeh�Nh�Nubh�)��}�(hh�
operator *�����}�(hKhh)��}�(hhhM|hKhKubh�ubhh�h]�hMh�hNh�hP�function�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��UInteger<N*2>�h��h�]�h�)��}�(h�const UInteger&�hh�other�����}�(hKhh)��}�(hhhM�hKhK-ubh�ubh�NhÉhĈhŉubah�Nh�Nubh�)��}�(hh�
operator <�����}�(hKhh)��}�(hhhMRhK%hKubh�ubhh�h]�hMh�hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��Bool�h��h�]�h�)��}�(h�const UInteger&�hh�other�����}�(hKhh)��}�(hhhMmhK%hK"ubh�ubh�NhÉhĈhŉubah�Nh�Nubh�)��}�(hh�operator ==�����}�(hKhh)��}�(hhhM�hK'hKubh�ubhh�h]�hMj  hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��Bool�h��h�]�h�)��}�(h�const UInteger&�hh�other�����}�(hKhh)��}�(hhhM�hK'hK#ubh�ubh�NhÉhĈhŉubah�Nh�Nubh�)��}�(hh�AddMixed�����}�(hKhh)��}�(hhhMhhK+hKubh�ubhh�h]�hMj%  hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��void�h��h�]�h�)��}�(h�const Half&�hh�half�����}�(hKhh)��}�(hhhM}hK+hKubh�ubh�NhÉhĈhŉubah�Nh�Nubh�)��}�(hh�AddLowToHigh�����}�(hKhh)��}�(hhhM�hK2hKubh�ubhh�h]�hMj;  hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��Bool�h��h�]�h�)��}�(h�const UInteger&�hh�value�����}�(hKhh)��}�(hhhM�hK2hK$ubh�ubh�NhÉhĈhŉubah�Nh�Nubh�)��}�(hh�AddHigh�����}�(hKhh)��}�(hhhM#hK7hKubh�ubhh�h]�hMjQ  hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��void�h��h�]�h�)��}�(h�const UInteger&�hh�value�����}�(hKhh)��}�(hhhM;hK7hKubh�ubh�NhÉhĈhŉubah�Nh�Nubh�)��}�(hh�Add�����}�(hKhh)��}�(hhhMxhK=hKubh�ubhh�h]�hMjg  hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��Bool�h��h�]�h�)��}�(h�const UInteger&�hh�value�����}�(hKhh)��}�(hhhM�hK=hKubh�ubh�NhÉhĈhŉubah�Nh�Nubh�)��}�(hh�Inc�����}�(hKhh)��}�(hhhMhKChKubh�ubhh�h]�hMj}  hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��Bool�h��h�]�h�Nh�Nubh�)��}�(hh�operator ++�����}�(hKhh)��}�(hhhM@hKHhKubh�ubhh�h]�hMj�  hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��	UInteger&�h��h�]�h�Nh�Nubh�)��}�(hh�operator ++�����}�(hKhh)��}�(hhhMyhKNhKubh�ubhh�h]�hMj�  hNh�hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��	UInteger&�h��h�]�h�)��}�(h�int�h�anonymous_param_1�h�NhÉhĈhŉubah�Nh�Nubh �Variable���)��}�(hh�_low�����}�(hKhh)��}�(hhhM�hKUhKubh�ubhh�h]�hMj�  hNh�private�����}�(hKhh)��}�(hhhM�hKThKubh�ubhP�variable�h/NhRNh�Half�hSNhTNhUK hV]�hXh	hY}�h[�h��ubj�  )��}�(hh�_high�����}�(hKhh)��}�(hhhM�hKVhKubh�ubhh�h]�hMj�  hNj�  hPj�  h/NhRNh�Half�hSNhTNhUK hV]�hXh	hY}�h[�h��ubehMh�hNhOhP�class�h/h �Template���)��}�h�]�h �NontypeTemplateParam���)��}�(hh)��}�(hhhK�hKhKubhÉhh�N�����}�(hKhh)��}�(hhhK�hKhKubh�ubh�Nh�Int��variance�NubasbhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h\]��	interface�N�refKind�Nh���refClass�N�baseInterfaces�N�derived���isError���implementation���	component���finalComponent���forward���
singleImpl���hasStaticMethods���generic�N�refClassForwardDeclared���missingInterfaces���ambiguousCalls�]��	selfCalls�]��methodNames�}�ubh�)��}�(h� UInteger<SIZEOF(UIntegerBase)*8>�hh0h]�(h�)��}�(hh�hj�  h]�hMh�hNh�public�����}�(hKhh)��}�(hhhMhK[hKubh�ubhPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h�h�h��h�]�h�)��}�(h�UInt�hh�value�����}�(hKhh)��}�(hhhM-hK\hKubh�ubh0�hÉhĈhŉubah�Nh�NubhC)��}�(hh�	UInteger2�����}�(hKhh)��}�(hhhMThK^hKubh�ubhj�  h]�hMj  hNj�  hPhQh/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h\]��!UInteger<SIZEOF(UIntegerBase)*16>�hOh	��aubh�)��}�(hh�
operator *�����}�(hKhh)��}�(hhhM�hK`hKubh�ubhj�  h]�hMj  hNj�  hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��	UInteger2�h��h�]�h�)��}�(h�const UInteger&�hh�other�����}�(hKhh)��}�(hhhM�hK`hK'ubh�ubh�NhÉhĈhŉubah�Nh�Nubh�)��}�(hh�
operator <�����}�(hKhh)��}�(hhhMbhKihKubh�ubhj�  h]�hMj3  hNj�  hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��Bool�h��h�]�h�)��}�(h�const UInteger&�hh�other�����}�(hKhh)��}�(hhhM}hKihK"ubh�ubh�NhÉhĈhŉubah�Nh�Nubh�)��}�(hh�operator ==�����}�(hKhh)��}�(hhhM�hKkhKubh�ubhj�  h]�hMjI  hNj�  hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��Bool�h��h�]�h�)��}�(h�const UInteger&�hh�other�����}�(hKhh)��}�(hhhM�hKkhK#ubh�ubh�NhÉhĈhŉubah�Nh�Nubh�)��}�(hh�Add�����}�(hKhh)��}�(hhhM-	hKohKubh�ubhj�  h]�hMj_  hNj�  hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��Bool�h��h�]�h�)��}�(h�const UInteger&�hh�value�����}�(hKhh)��}�(hhhMA	hKohKubh�ubh�NhÉhĈhŉubah�Nh�Nubh�)��}�(hh�Inc�����}�(hKhh)��}�(hhhM�	hKvhKubh�ubhj�  h]�hMju  hNj�  hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��Bool�h��h�]�h�Nh�Nubh�)��}�(hh�operator ++�����}�(hKhh)��}�(hhhM�	hK{hKubh�ubhj�  h]�hMj�  hNj�  hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��	UInteger&�h��h�]�h�Nh�Nubh�)��}�(hh�operator ++�����}�(hKhh)��}�(hhhM
hK�hKubh�ubhj�  h]�hMj�  hNj�  hPh�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h��h��h��h��	UInteger&�h��h�]�h�)��}�(h�int�h�anonymous_param_1�h�NhÉhĈhŉubah�Nh�Nubj�  )��}�(hh�_value�����}�(hKhh)��}�(hhhMF
hK�hKubh�ubhj�  h]�hMj�  hNh�private�����}�(hKhh)��}�(hhhM7
hK�hKubh�ubhPj�  h/NhRNh�UInt�hSNhTNhUK hV]�hXh	hY}�h[�h��ubehMh�UInteger�����}�(hKhh)��}�(hhhM�hKYhKubh�ubhNhOhPj�  h/j�  )��}�h�]�j�  )��}�(hh)��}�(hhhM�hKYhKubhÉhNh�Nhh	j�  NubasbhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h\]�j�  Nj�  Nh��j�  Nj�  Nj�  �j�  �j�  �j�  �j�  �j�  �j�  �j�  �j�  Nj�  �j�  �j�  ]�j�  ]�j�  }�ubhC)��}�(hh�NativeUInteger�����}�(hKhh)��}�(hhhMX
hK�hKubh�ubhh0h]�hMj�  hNhOhPhQh/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�h\]��UInteger<SIZEOF(Int)*8>�hOh	��aubh�)��}�(hh�LessThan�����}�(hKhh)��}�(hhhMJhK�hKubh�ubhh0h]�hMj�  hNhOhPh�h/NhRNhNhSNhTNhUK hV]�(h�U/// Returns true if <tt>a1*a2</tt> is less than <tt>b1*b2</tt>. The products and the
�����}�(hKhh)��}�(hhhM�
hK�hKubh�ubh�W/// comparison are carried out with the double bit width of @c Int so that no overflow
�����}�(hKhh)��}�(hhhM5hK�hKubh�ubh�/// occurs.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubh�D/// @param[in] a1									First factor of first comparison operand.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubh�E/// @param[in] a2									Second factor of first comparison operand.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubh�E/// @param[in] b1									First factor of second comparison operand.
�����}�(hKhh)��}�(hhhM!hK�hKubh�ubh�F/// @param[in] b2									Second factor of second comparison operand.
�����}�(hKhh)��}�(hhhMfhK�hKubh�ubh�7/// @return												True if <tt>a1*a2 < b1*b2</tt>.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubehXX  /// Returns true if <tt>a1*a2</tt> is less than <tt>b1*b2</tt>. The products and the
/// comparison are carried out with the double bit width of @c Int so that no overflow
/// occurs.
/// @param[in] a1									First factor of first comparison operand.
/// @param[in] a2									Second factor of first comparison operand.
/// @param[in] b1									First factor of second comparison operand.
/// @param[in] b2									Second factor of second comparison operand.
/// @return												True if <tt>a1*a2 < b1*b2</tt>.
�hY}�h[�h��h��h��h��Bool�h��h�]�(h�)��}�(h�UInt�hh�a1�����}�(hKhh)��}�(hhhMXhK�hKubh�ubh�NhÉhĈhŉubh�)��}�(h�UInt�hh�a2�����}�(hKhh)��}�(hhhMahK�hK$ubh�ubh�NhÉhĈhŉubh�)��}�(h�UInt�hh�b1�����}�(hKhh)��}�(hhhMjhK�hK-ubh�ubh�NhÉhĈhŉubh�)��}�(h�UInt�hh�b2�����}�(hKhh)��}�(hhhMshK�hK6ubh�ubh�NhÉhĈhŉubeh�Nh�NubehMh4hNhOhP�	namespace�h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[��preprocessorConditions�]��root�hh N�containsResourceId���registry���usings����minIndentation�K �maxIndentation�K �firstMember��ubh)��}�(hNhhh]�h h�#endif�����}�(hK
hh)��}�(hhhM�hK�hKubh�ububehMhhNhOhPj1  h/NhRNhNhSNhTNhUK hV]�hXh	hY}�h[�j4  ]�j6  hh ]�(hh)h0h9hDh`hihwh�j�  j�  j�  j>  ej7  �j8  �j9  ���hxx1�N�hxx2�N�snippets�}�j;  K j<  K j=  �ub.