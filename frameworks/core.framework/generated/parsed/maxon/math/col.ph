��      �declarations��	Namespace���)��}�(�name��lexer��Token���� �����}�(�type�K�pos�h�SourcePosition���)��}�(�file��OC:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\col.h��index�K �line�KhKub�escaped��ub�owner�N�children�]�(h �	Directive���)��}�(hNhhh]��code�h�#ifndef MAXON_VECTORMODE�����}�(hK
hh)��}�(hhhK)hKhKubh�ububh)��}�(hNhhh]�h h�#endif�����}�(hK
hh)��}�(hhhK�hKhKubh�ububh)��}�(hh�maxon�����}�(hKhh)��}�(hhhK�hKhKubh�ubhhh]�(h)��}�(hNhh0h]�h h�#ifdef STRIDE�����}�(hK
hh)��}�(hhhK�hKhKubh�ububh)��}�(hNhh0h]�h h�#else�����}�(hK
hh)��}�(hhhMhKhKubh�ububh �Class���)��}�(hh�Col3�����}�(hKhh)��}�(hhhMHhKhK.ubh�ubhh0h]�(h �	TypeAlias���)��}�(hh�Rebind�����}�(hKhh)��}�(hhhMshKhKubh�ubhhMh]��
simpleName�h\�access��public��kind��	typealias��template�h �Template���)��}��params�]�h �TypeTemplateParam���)��}�(hh)��}�(hhhMahKhKub�pack��hh�U�����}�(hKhh)��}�(hhhMjhKhKubh�ub�default�N�variance�Nubasb�friend�NhN�id�N�point�N�
artificial�K �doclist�]��doc�h	�annotations�}��	anonymous���bases�]��Col3<U,STRIDE>�hch	��aubhW)��}�(hh�VectorStrideType�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��"std::integral_constant<Int,STRIDE>�hch	��aubhW)��}�(hh�	ValueType�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��T�hch	��aubhW)��}�(hh�ValueTypeParam�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��typename ByValueParam<T>::type�hch	��aubhW)��}�(hh�	Unstrided�����}�(hKhh)��}�(hhhM!hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��	Col3<T,1>�hch	��aubhW)��}�(hh�BoolType�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�(h�U/// The type returned by comparisons. If the template argument for T is a SIMD type,
�����}�(hKhh)��}�(hhhM;hKhKubh�ubh�K/// this will be a SIMD type, too, which contains the per-element results.
�����}�(hKhh)��}�(hhhM�hKhKubh�ubeh���/// The type returned by comparisons. If the template argument for T is a SIMD type,
/// this will be a SIMD type, too, which contains the per-element results.
�h�}�h��h�]��decltype(T()==T())�hch	��aubh)��}�(hNhhMh]�h h�#ifdef STRIDE�����}�(hK
hh)��}�(hhhMhKhKubh�ububh �Variable���)��}�(hh�r�����}�(hKhh)��}�(hhhMhKhKubh�ubhhMh]�hah�hbhchd�variable�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h���static��ubh�)��}�(hh�g�����}�(hKhh)��}�(hhhMhKhKubh�ubhhMh]�hah�hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�b�����}�(hKhh)��}�(hhhM"hKhKubh�ubhhMh]�haj  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh)��}�(hNhhMh]�h h�#else�����}�(hK
hh)��}�(hhhM%hKhKubh�ububhL)��}�(hh�_anonymous#C:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\col.h(32,2)�����}�(hKhh)��}�(hhhM-hK hKubh�ubhhMh]�(h�)��}�(hh�r�����}�(hKhh)��}�(hhhM7hK hKubh�ubhj  h]�haj$  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�	_xpadding�����}�(hKhh)��}�(hhhM<hK hKubh�ubhj  h]�haj0  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubehaj  hbhchd�class�hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��	interface�N�refKind�Nh���refClass�N�baseInterfaces�N�derived���isError���implementation���	component���finalComponent���forward���
singleImpl���hasStaticMethods���generic�N�refClassForwardDeclared���missingInterfaces���ambiguousCalls�]��	selfCalls�]��methodNames�}�ubhL)��}�(hh�_anonymous#C:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\col.h(33,2)�����}�(hKhh)��}�(hhhMShK!hKubh�ubhhMh]�(h�)��}�(hh�g�����}�(hKhh)��}�(hhhM]hK!hKubh�ubhjQ  h]�haj^  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�	_ypadding�����}�(hKhh)��}�(hhhMbhK!hKubh�ubhjQ  h]�hajj  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubehajU  hbhchdj8  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]�j<  Nj=  Nh��j>  Nj?  Nj@  �jA  �jB  �jC  �jD  �jE  �jF  �jG  �jH  NjI  �jJ  �jK  ]�jM  ]�jO  }�ubhL)��}�(hh�_anonymous#C:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\col.h(34,2)�����}�(hKhh)��}�(hhhMyhK"hKubh�ubhhMh]�(h�)��}�(hh�b�����}�(hKhh)��}�(hhhM�hK"hKubh�ubhjx  h]�haj�  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�	_zpadding�����}�(hKhh)��}�(hhhM�hK"hKubh�ubhjx  h]�haj�  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubehaj|  hbhchdj8  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]�j<  Nj=  Nh��j>  Nj?  Nj@  �jA  �jB  �jC  �jD  �jE  �jF  �jG  �jH  NjI  �jJ  �jK  ]�jM  ]�jO  }�ubh)��}�(hNhhMh]�h h�#endif�����}�(hK
hh)��}�(hhhM�hK#hKubh�ububh �Function���)��}�(h�constructor�hhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�//// Initializes all vector components with 0.0
�����}�(hKhh)��}�(hhhM�hK%hKubh�ubah��//// Initializes all vector components with 0.0
�h�}�h��h���explicit���deleted���retType��void��const��hk]��
observable�N�result�Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�4/// Initializes all vector components with a scalar
�����}�(hKhh)��}�(hhhM�hK(hKubh�ubah��4/// Initializes all vector components with a scalar
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�h �	Parameter���)��}�(h�ValueTypeParam�hh�in�����}�(hKhh)��}�(hhhMIhK)hKubh�ubhzNhs��input���output��ubaj�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�3/// Initializes all vector components individually
�����}�(hKhh)��}�(hhhMihK+hKubh�ubah��3/// Initializes all vector components individually
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�(j�  )��}�(h�ValueTypeParam�hh�ix�����}�(hKhh)��}�(hhhM�hK,hKubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�ValueTypeParam�hh�iy�����}�(hKhh)��}�(hhhM�hK,hK2ubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�ValueTypeParam�hh�iz�����}�(hKhh)��}�(hhhM�hK,hKEubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM>hK/hKubhs�hh�T2�����}�(hKhh)��}�(hhhMGhK/hKubh�ubhzNh{Nubh �NontypeTemplateParam���)��}�(hh)��}�(hhhMKhK/hKubhs�hh�S2�����}�(hKhh)��}�(hhhMOhK/hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�3/// Initializes components from another 3d vector.
�����}�(hKhh)��}�(hhhM hK.hKubh�ubah��3/// Initializes components from another 3d vector.
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j�  )��}�(h�const Col3<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhMuhK/hKCubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�hK0hKubhs�hh�T2�����}�(hKhh)��}�(hhhM�hK0hKubh�ubhzNh{Nubj  )��}�(hh)��}�(hhhM�hK0hKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hK0hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j�  )��}�(h�const Vec3<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hK0hKCubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhMhK1hKubhs�hh�T2�����}�(hKhh)��}�(hhhMhK1hKubh�ubhzNh{Nubj  )��}�(hh)��}�(hhhM!hK1hKubhs�hh�S2�����}�(hKhh)��}�(hhhM%hK1hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j�  )��}�(h�const Col4<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhMKhK1hKCubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfhh)��}�hk]�j  )��}�(hh)��}�(hhhM�hK3hKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hK3hKubh�ubhzNh�Int�h{Nubasbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j�  )��}�(h�const Col3<T, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hK3hK,ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�6/// Skips initialization of vector (for better speed)
�����}�(hKhh)��}�(hhhM�hK5hKubh�ubah��6/// Skips initialization of vector (for better speed)
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j�  )��}�(h�ENUM_DONT_INITIALIZE�hh�v�����}�(hKhh)��}�(hhhM7hK6hK%ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j�  )��}�(h�Gconst typename std::conditional<STRIDE==1, DummyParamType, Col3>::type&�hh�src�����}�(hKhh)��}�(hhhM�hK:hK`ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator =�����}�(hKhh)��}�(hhhM	hK>hKubh�ubhhMh]�haj�  hbhchd�function�hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �Col3&�j�  �hk]�j�  )��}�(h�Gconst typename std::conditional<STRIDE==1, DummyParamType, Col3>::type&�hh�src�����}�(hKhh)��}�(hhhMX	hK>hK]ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator []�����}�(hKhh)��}�(hhhM 
hKGhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h��/// Accesses vector component: index 0 is 'r', index 1 is 'g', index 2 is 'b'. All other values must not be used and will crash
�����}�(hKhh)��}�(hhhM�	hKFhKubh�ubah���/// Accesses vector component: index 0 is 'r', index 1 is 'g', index 2 is 'b'. All other values must not be used and will crash
�h�}�h��h��j�  �j�  �j�  �T&�j�  �hk]�j�  )��}�(h�Int�hh�l�����}�(hKhh)��}�(hhhM0
hKGhKubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator []�����}�(hKhh)��}�(hhhM	hKNhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h��/// Accesses vector component: index 0 is 'r', index 1 is 'g', index 2 is 'b'.  All other values must not be used and will crash
�����}�(hKhh)��}�(hhhMx
hKMhKubh�ubah���/// Accesses vector component: index 0 is 'r', index 1 is 'g', index 2 is 'b'.  All other values must not be used and will crash
�h�}�h��h��j�  �j�  �j�  �ValueTypeParam�j�  �hk]�j�  )��}�(h�Int�hh�l�����}�(hKhh)��}�(hhhMhKNhK!ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator +=�����}�(hKhh)��}�(hhhM�hKUhK'ubh�ubhhMh]�haj  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�hKUhKubhs�hh�T2�����}�(hKhh)��}�(hhhM�hKUhKubh�ubhzNh{Nubj  )��}�(hh)��}�(hhhM�hKUhKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hKUhKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�/// Adds two vectors
�����}�(hKhh)��}�(hhhMmhKThKubh�ubah��/// Adds two vectors
�h�}�h��h��j�  �j�  �j�  �Col3&�j�  �hk]�j�  )��}�(h�const Col3<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hKUhKGubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator +=�����}�(hKhh)��}�(hhhM�hK^hKubh�ubhhMh]�hajK  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �Col3&�j�  �hk]�j�  )��}�(h�const Col3&�hh�v�����}�(hKhh)��}�(hhhM�hK^hK ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator -=�����}�(hKhh)��}�(hhhMehKghK'ubh�ubhhMh]�haja  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhMJhKghKubhs�hh�T2�����}�(hKhh)��}�(hhhMShKghKubh�ubhzNh{Nubj  )��}�(hh)��}�(hhhMWhKghKubhs�hh�S2�����}�(hKhh)��}�(hhhM[hKghKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�/// Subtracts two vectors
�����}�(hKhh)��}�(hhhM%hKfhKubh�ubah��/// Subtracts two vectors
�h�}�h��h��j�  �j�  �j�  �Col3&�j�  �hk]�j�  )��}�(h�const Col3<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hKghKGubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator -=�����}�(hKhh)��}�(hhhM�hKphKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �Col3&�j�  �hk]�j�  )��}�(h�const Col3&�hh�v�����}�(hKhh)��}�(hhhM�hKphK ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhM2hKyhK'ubh�ubhhMh]�haj�  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhMhKyhKubhs�hh�T2�����}�(hKhh)��}�(hhhM hKyhKubh�ubhzNh{Nubj  )��}�(hh)��}�(hhhM$hKyhKubhs�hh�S2�����}�(hKhh)��}�(hhhM(hKyhKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�*/// Multiplies two vectors component-wise
�����}�(hKhh)��}�(hhhM�hKxhKubh�ubah��*/// Multiplies two vectors component-wise
�h�}�h��h��j�  �j�  �j�  �Col3&�j�  �hk]�j�  )��}�(h�const Col3<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhMRhKyhKGubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhMXhK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �Col3&�j�  �hk]�j�  )��}�(h�const Col3&�hh�v�����}�(hKhh)��}�(hhhMphK�hK ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �Col3&�j�  �hk]�j�  )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhMhK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator /=�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�V/// Divides each vector component by a scalar. The passed argument is checked for 0.0
�����}�(hKhh)��}�(hhhM;hK�hKubh�ubah��V/// Divides each vector component by a scalar. The passed argument is checked for 0.0
�h�}�h��h��j�  �j�  �j�  �Col3&�j�  �hk]�j�  )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhM�hK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhMGhK�hKubh�ubhhMh]�haj1  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhM6hK�hKubh�ubhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhMhK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�(j�  )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhMahK�hK-ubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Col3&�hh�v�����}�(hKhh)��}�(hhhMphK�hK<ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubj�  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj]  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhM hK�hK&ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM�hK�hKhubh�ubhhMh]�hajz  hbhchdj�  hfhh)��}�hk]�hn)��}�(hh)��}�(hhhMvhK�hKubhs�hh�S�����}�(hKhh)��}�(hhhMhK�hKubh�ubhzNh{Nubasbh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhM:hK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �OCol3<typename MultiplicativePromotion<T, S, std::is_scalar<S>::value>::type, 1>�j�  �hk]�j�  )��}�(h�S�hh�s�����}�(hKhh)��}�(hhhM�hK�hKuubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator /�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�R/// Divides each vector component by a scalar. The scalar value is tested for 0.0
�����}�(hKhh)��}�(hhhMEhK�hKubh�ubah��R/// Divides each vector component by a scalar. The scalar value is tested for 0.0
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhM�hK�hK&ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhMChK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�*/// Multiplies two vectors component-wise
�����}�(hKhh)��}�(hhhMhK�hKubh�ubah��*/// Multiplies two vectors component-wise
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�const Col3&�hh�v�����}�(hKhh)��}�(hhhMZhK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator +�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�/// Adds two vectors
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��/// Adds two vectors
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�const Col3&�hh�v�����}�(hKhh)��}�(hhhM�hK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator -�����}�(hKhh)��}�(hhhM<hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h� /// Subtracts vector v2 from v1
�����}�(hKhh)��}�(hhhMhK�hKubh�ubah�� /// Subtracts vector v2 from v1
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�const Col3&�hh�v�����}�(hKhh)��}�(hhhMShK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator -�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�/// Negates vector v
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��/// Negates vector v
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�operator ==�����}�(hKhh)��}�(hhhMhK�hK*ubh�ubhhMh]�haj,  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�hK�hKubhs�hh�T2�����}�(hKhh)��}�(hhhMhK�hKubh�ubhzNh{Nubj  )��}�(hh)��}�(hhhMhK�hKubhs�hh�S2�����}�(hKhh)��}�(hhhM	hK�hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  )��}�(h�const Col3<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM6hK�hKJubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator ==�����}�(hKhh)��}�(hhhM;hK�hKubh�ubhhMh]�hajZ  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  )��}�(h�const Col3&�hh�v�����}�(hKhh)��}�(hhhMShK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator !=�����}�(hKhh)��}�(hhhM�hK�hK*ubh�ubhhMh]�hajp  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�hK�hKubhs�hh�T2�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhzNh{Nubj  )��}�(hh)��}�(hhhM�hK�hKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  )��}�(h�const Col3<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hK�hKJubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator !=�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  )��}�(h�const Col3&�hh�v�����}�(hKhh)��}�(hhhM�hK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�GetHashCode�����}�(hKhh)��}�(hhhM;hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �UInt�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�IsEqual�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�G/// Tests component-wise if the difference is no bigger than 'epsilon'
�����}�(hKhh)��}�(hhhMyhK�hKubh�ubah��G/// Tests component-wise if the difference is no bigger than 'epsilon'
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�(j�  )��}�(h�const Col3&�hh�other�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�ValueTypeParam�hh�epsilon�����}�(hKhh)��}�(hhhM�hK�hK5ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubj�  )��}�(hh�Abs�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhNh}Nh~NhK h�]�(h�:/// returns the vector with absolute value for each entry
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubh�2/// @param[in] v1									input vector to work on
�����}�(hKhh)��}�(hhhMhK�hKubh�ubh�L/// @return												component wise absolute value vector of input vector
�����}�(hKhh)��}�(hhhM9hK�hKubh�ubeh���/// returns the vector with absolute value for each entry
/// @param[in] v1									input vector to work on
/// @return												component wise absolute value vector of input vector
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�const Col3&�hh�v1�����}�(hKhh)��}�(hhhMhK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�IsZero�����}�(hKhh)��}�(hhhMthK�hKubh�ubhhMh]�haj  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�&/// Checks if each component is zero.
�����}�(hKhh)��}�(hhhMDhK�hKubh�ubah��&/// Checks if each component is zero.
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�SetZero�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj*  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�!/// Sets all components to zero.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��!/// Sets all components to zero.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�
GetAverage�����}�(hKhh)��}�(hhhM>hMhKubh�ubhhMh]�haj>  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�5/// Calculates the average value of 'r', 'g' and 'b'
�����}�(hKhh)��}�(hhhMhMhKubh�ubah��5/// Calculates the average value of 'r', 'g' and 'b'
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�GetSum�����}�(hKhh)��}�(hhhM�hM
hKubh�ubhhMh]�hajR  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�+/// Calculates the sum of 'r', 'g' and 'b'
�����}�(hKhh)��}�(hhhM~hM	hKubh�ubah��+/// Calculates the sum of 'r', 'g' and 'b'
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�Min�����}�(hKhh)��}�(hhhMhMhKubh�ubhhMh]�hajf  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhMhMhKubh�ubhNh}Nh~NhK h�]�h�./// Calculates the minimum of each component.
�����}�(hKhh)��}�(hhhM�hMhKubh�ubah��./// Calculates the minimum of each component.
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�(j�  )��}�(h�const Col3&�hh�a�����}�(hKhh)��}�(hhhM'hMhK#ubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Col3&�hh�other�����}�(hKhh)��}�(hhhM6hMhK2ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubj�  )��}�(hh�Max�����}�(hKhh)��}�(hhhM�hMhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhM�hMhKubh�ubhNh}Nh~NhK h�]�h�./// Calculates the maximum of each component.
�����}�(hKhh)��}�(hhhM�hMhKubh�ubah��./// Calculates the maximum of each component.
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�(j�  )��}�(h�const Col3&�hh�a�����}�(hKhh)��}�(hhhM hMhK#ubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Col3&�hh�other�����}�(hKhh)��}�(hhhM hMhK2ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubj�  )��}�(hh�ClampMin�����}�(hKhh)��}�(hhhM� hMhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�'/// Set the minimum of each component.
�����}�(hKhh)��}�(hhhM� hMhKubh�ubah��'/// Set the minimum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j�  )��}�(h�const Col3&�hh�other�����}�(hKhh)��}�(hhhM� hMhKubh�ubhz�Col3()�hs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�ClampMax�����}�(hKhh)��}�(hhhMu!hM$hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�'/// Set the maximum of each component.
�����}�(hKhh)��}�(hhhMH!hM#hKubh�ubah��'/// Set the maximum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j�  )��}�(h�const Col3&�hh�other�����}�(hKhh)��}�(hhhM�!hM$hKubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�SetMin�����}�(hKhh)��}�(hhhM$"hM,hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhM"hM,hKubh�ubhNh}Nh~NhK h�]�h�'/// Set the minimum of each component.
�����}�(hKhh)��}�(hhhM�!hM+hKubh�ubah��'/// Set the minimum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�(j�  )��}�(h�Col3&�hh�a�����}�(hKhh)��}�(hhhM1"hM,hKubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Col3&�hh�other�����}�(hKhh)��}�(hhhM@"hM,hK*ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubj�  )��}�(hh�SetMax�����}�(hKhh)��}�(hhhM�"hM2hKubh�ubhhMh]�haj%  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhM�"hM2hKubh�ubhNh}Nh~NhK h�]�h�'/// Set the maximum of each component.
�����}�(hKhh)��}�(hhhMd"hM1hKubh�ubah��'/// Set the maximum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�(j�  )��}�(h�Col3&�hh�a�����}�(hKhh)��}�(hhhM�"hM2hKubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Col3&�hh�other�����}�(hKhh)��}�(hhhM�"hM2hK*ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubj�  )��}�(hh�Clamp01�����}�(hKhh)��}�(hhhM"#hM8hKubh�ubhhMh]�hajQ  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�?/// Returns a vector that is clamped to the range [0.0 .. 1.0]
�����}�(hKhh)��}�(hhhM�"hM7hKubh�ubah��?/// Returns a vector that is clamped to the range [0.0 .. 1.0]
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�ToString�����}�(hKhh)��}�(hhhM%hMBhK	ubh�ubhhMh]�haje  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h�./// Returns a readable string of the content.
�����}�(hKhh)��}�(hhhM�#hM>hKubh�ubh�j/// @param[in] formatStatement		Nullptr or additional formatting instruction. See also @ref format_float.
�����}�(hKhh)��}�(hhhM$hM?hKubh�ubh�-/// @return												The converted result.
�����}�(hKhh)��}�(hhhM}$hM@hKubh�ubeh���/// Returns a readable string of the content.
/// @param[in] formatStatement		Nullptr or additional formatting instruction. See also @ref format_float.
/// @return												The converted result.
�h�}�h��h��j�  �j�  �j�  �String�j�  �hk]�j�  )��}�(h�const FormatStatement*�hh�formatStatement�����}�(hKhh)��}�(hhhM.%hMBhK)ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�	GetVector�����}�(hKhh)��}�(hhhM|&hMJhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�&/// Reinterprets the color as vector.
�����}�(hKhh)��}�(hhhM>&hMIhKubh�ubah��&/// Reinterprets the color as vector.
�h�}�h��h��j�  �j�  �j�  �const Vec3<T, STRIDE>&�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�	GetVector�����}�(hKhh)��}�(hhhM�&hMKhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �Vec3<T, STRIDE>&�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�GetMin�����}�(hKhh)��}�(hhhM-'hMNhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�,/// Returns the minimum of 'r', 'g' and 'b'
�����}�(hKhh)��}�(hhhM�&hMMhKubh�ubah��,/// Returns the minimum of 'r', 'g' and 'b'
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�GetMax�����}�(hKhh)��}�(hhhM�'hM[hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�,/// Returns the maximum of 'r', 'g' and 'b'
�����}�(hKhh)��}�(hhhM�'hMZhKubh�ubah��,/// Returns the maximum of 'r', 'g' and 'b'
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�GetRightRotated�����}�(hKhh)��}�(hhhMb*hMmhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h�x/// Returns a vector where the components have been rotated to the right (in the usual (r, g, b)-representation). E.g.,
�����}�(hKhh)��}�(hhhM�(hMhhKubh�ubh�>/// with a value of 1 for rots, the result will be (b, r, g).
�����}�(hKhh)��}�(hhhM)hMihKubh�ubh�q/// @param[in] rots								Number of rotations, may be negative. The result depends only on the number modulo 3.
�����}�(hKhh)��}�(hhhMR)hMjhKubh�ubh�7/// @return												Vector with rotated components.
�����}�(hKhh)��}�(hhhM�)hMkhKubh�ubeh�X^  /// Returns a vector where the components have been rotated to the right (in the usual (r, g, b)-representation). E.g.,
/// with a value of 1 for rots, the result will be (b, r, g).
/// @param[in] rots								Number of rotations, may be negative. The result depends only on the number modulo 3.
/// @return												Vector with rotated components.
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�Int�hh�rots�����}�(hKhh)��}�(hhhMv*hMmhK ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhM�+hM�hKubh�ubhhMh]�haj  hbhchdj�  hfhh)��}�hk]�hn)��}�(hh)��}�(hhhM�+hM�hKubhs�hh�T2�����}�(hKhh)��}�(hhhM�+hM�hKubh�ubhzNh{Nubasbh|NhNh}Nh~NhK h�]�h�!/// Transforms color by a matrix
�����}�(hKhh)��}�(hhhMv+hM�hKubh�ubah��!/// Transforms color by a matrix
�h�}�h��h��j�  �j�  �j�  �Col3&�j�  �hk]�j�  )��}�(h�const Mat3<T2>&�hh�m�����}�(hKhh)��}�(hhhM�+hM�hK;ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubj�  )��}�(hh�	NullValue�����}�(hKhh)��}�(hhhM�,hM�hKubh�ubhhMh]�haj0  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �const Col3&�j�  �hk]�j�  Nj�  NubehahQhbhchdj8  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM%hKhKubhs�hh�T�����}�(hKhh)��}�(hhhM.hKhKubh�ubhzNh{Nubj  )��}�(hh)��}�(hhhM1hKhKubhs�hh�STRIDE�����}�(hKhh)��}�(hhhM5hKhKubh�ubhz�1�h�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]�j<  Nj=  Nh��j>  Nj?  Nj@  �jA  �jB  �jC  �jD  �jE  �jF  �jG  �jH  NjI  �jJ  �jK  ]�jM  ]�jO  }�ubh)��}�(hNhh0h]�h h�#ifndef STRIDE�����}�(hK
hh)��}�(hhhM--hM�hKubh�ububj�  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM�-hM�hK�ubh�ubhh0h]�haje  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhMw-hM�hKubhs�hh�T�����}�(hKhh)��}�(hhhM�-hM�hKubh�ubhzNh{Nubj  )��}�(hh)��}�(hhhM�-hM�hKubhs�hh�STR�����}�(hKhh)��}�(hhhM�-hM�hKubh�ubhzNh�Int�h{Nubhn)��}�(hh)��}�(hhhM�-hM�hK ubhs�hh�S�����}�(hKhh)��}�(hhhM�-hM�hK)ubh�ubhzNh{Nubesbh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhM<-hM�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �OCol3<typename MultiplicativePromotion<T, S, std::is_scalar<S>::value>::type, 1>�j�  �hk]�(j�  )��}�(h�S�hh�s�����}�(hKhh)��}�(hhhM�-hM�hK�ubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Col3<T, STR>&�hh�v�����}�(hKhh)��}�(hhhM.hM�hK�ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubj�  )��}�(hh�PrivateGetDataType�����}�(hKhh)��}�(hhhM�.hM�hKKubh�ubhh0h]�haj�  hbhchdj�  hfhh)��}�hk]�(j  )��}�(hh)��}�(hhhM.hM�hKubhs�hh�POLICY�����}�(hKhh)��}�(hhhM�.hM�hKubh�ubhzNh�GET_DATATYPE_POLICY�h{Nubhn)��}�(hh)��}�(hhhM�.hM�hK'ubhs�hh�T�����}�(hKhh)��}�(hhhM�.hM�hK0ubh�ubhzNh{Nubesbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �Result<DataType>�j�  �hk]�(j�  )��}�(h�Col3<T, 1>**�h�anonymous_param_1�hzNhs�j�  �j�  �ubj�  )��}�(h�OverloadRank0�h�anonymous_param_2�hzNhs�j�  �j�  �ubej�  Nj�  �DataType�ubhL)��}�(h�IsZeroInitialized<Col3<T,1>>�hh0h]�hah�IsZeroInitialized�����}�(hKhh)��}�(hhhM�/hM�hKubh�ubhbhchdj8  hfhh)��}�hk]�hn)��}�(hh)��}�(hhhM�/hM�hKubhs�hh�T�����}�(hKhh)��}�(hhhM�/hM�hKubh�ubhzNh{Nubasbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��IsZeroInitialized<T>�h�public�����}�(hKhh)��}�(hhhM�/hM�hK>ubh�ubh	��aj<  Nj=  Nh��j>  Nj?  Nj@  �jA  �jB  �jC  �jD  �jE  �jF  �jG  �jH  NjI  �jJ  �jK  ]�jM  ]�jO  }�ubh)��}�(hNhh0h]�h h�#endif�����}�(hK
hh)��}�(hhhM0hM�hKubh�ububehah4hbhchd�	namespace�hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h���preprocessorConditions�]��root�hh N�containsResourceId���registry���usings����minIndentation�K �maxIndentation�K�firstMember��ubehahhbhchdj	  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��j	  ]�j
	  hh ]�(hh'h0h9hBhMjX  ja  j�  j�  j�  ej	  �j	  �j	  ���hxx1�N�hxx2�N�snippets�}�j	  K j	  K j	  �ub.