���      �declarations��	Namespace���)��}�(�name��lexer��Token���� �����}�(�type�K�pos�h�SourcePosition���)��}�(�file��PC:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\vec4.h��index�K �line�KhKub�escaped��ub�owner�N�children�]�(h �	Directive���)��}�(hNhhh]��code�h�#ifndef MAXON_VECTORMODE�����}�(hK
hh)��}�(hhhK)hKhKubh�ububh)��}�(hNhhh]�h h�#endif�����}�(hK
hh)��}�(hhhK�hKhKubh�ububh)��}�(hh�maxon�����}�(hKhh)��}�(hhhK�hKhKubh�ubhhh]�(h)��}�(hNhh0h]�h h�#ifdef STRIDE�����}�(hK
hh)��}�(hhhK�hKhKubh�ububh)��}�(hNhh0h]�h h�#else�����}�(hK
hh)��}�(hhhMhKhKubh�ububh �Class���)��}�(hh�Vec4�����}�(hKhh)��}�(hhhMMhKhK.ubh�ubhh0h]�(h �	TypeAlias���)��}�(hh�Rebind�����}�(hKhh)��}�(hhhMxhKhKubh�ubhhMh]��
simpleName�h\�access��public��kind��	typealias��template�h �Template���)��}��params�]�h �TypeTemplateParam���)��}�(hh)��}�(hhhMfhKhKub�pack��hh�U�����}�(hKhh)��}�(hhhMohKhKubh�ub�default�N�variance�Nubasb�friend�NhN�id�N�point�N�
artificial�K �doclist�]��doc�h	�annotations�}��	anonymous���bases�]��Vec4<U,STRIDE>�hch	��aubhW)��}�(hh�VectorStrideType�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��"std::integral_constant<Int,STRIDE>�hch	��aubhW)��}�(hh�	ValueType�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��T�hch	��aubhW)��}�(hh�ValueTypeParam�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��typename ByValueParam<T>::type�hch	��aubhW)��}�(hh�	Unstrided�����}�(hKhh)��}�(hhhM&hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��	Vec4<T,1>�hch	��aubhW)��}�(hh�BoolType�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�(h�U/// The type returned by comparisons. If the template argument for T is a SIMD type,
�����}�(hKhh)��}�(hhhM@hKhKubh�ubh�K/// this will be a SIMD type, too, which contains the per-element results.
�����}�(hKhh)��}�(hhhM�hKhKubh�ubeh���/// The type returned by comparisons. If the template argument for T is a SIMD type,
/// this will be a SIMD type, too, which contains the per-element results.
�h�}�h��h�]��decltype(T()==T())�hch	��aubh)��}�(hNhhMh]�h h�#ifdef STRIDE�����}�(hK
hh)��}�(hhhM
hKhKubh�ububh �Variable���)��}�(hh�x�����}�(hKhh)��}�(hhhMhKhKubh�ubhhMh]�hah�hbhchd�variable�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h���static��ubh�)��}�(hh�y�����}�(hKhh)��}�(hhhM!hKhKubh�ubhhMh]�hah�hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�z�����}�(hKhh)��}�(hhhM'hKhKubh�ubhhMh]�haj  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�w�����}�(hKhh)��}�(hhhM-hKhKubh�ubhhMh]�haj  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh)��}�(hNhhMh]�h h�#else�����}�(hK
hh)��}�(hhhM0hK hKubh�ububhL)��}�(hh�`anonymous#C:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\vec4.h(33,2)�����}�(hKhh)��}�(hhhM7hK!hKubh�ubhhMh]�(h�)��}�(hh�x�����}�(hKhh)��}�(hhhMAhK!hKubh�ubhj#  h]�haj0  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�	_xpadding�����}�(hKhh)��}�(hhhMFhK!hKubh�ubhj#  h]�haj<  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubehaj'  hbhchd�class�hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��	interface�N�refKind�Nh���refClass�N�baseInterfaces�N�derived���isError���implementation���	component���finalComponent���forward���
singleImpl���hasStaticMethods���generic�N�refClassForwardDeclared���missingInterfaces���ambiguousCalls�]��	selfCalls�]��methodNames�}�ubhL)��}�(hh�`anonymous#C:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\vec4.h(34,2)�����}�(hKhh)��}�(hhhM]hK"hKubh�ubhhMh]�(h�)��}�(hh�y�����}�(hKhh)��}�(hhhMghK"hKubh�ubhj]  h]�hajj  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�	_ypadding�����}�(hKhh)��}�(hhhMlhK"hKubh�ubhj]  h]�hajv  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubehaja  hbhchdjD  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]�jH  NjI  Nh��jJ  NjK  NjL  �jM  �jN  �jO  �jP  �jQ  �jR  �jS  �jT  NjU  �jV  �jW  ]�jY  ]�j[  }�ubhL)��}�(hh�`anonymous#C:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\vec4.h(35,2)�����}�(hKhh)��}�(hhhM�hK#hKubh�ubhhMh]�(h�)��}�(hh�z�����}�(hKhh)��}�(hhhM�hK#hKubh�ubhj�  h]�haj�  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�	_zpadding�����}�(hKhh)��}�(hhhM�hK#hKubh�ubhj�  h]�haj�  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubehaj�  hbhchdjD  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]�jH  NjI  Nh��jJ  NjK  NjL  �jM  �jN  �jO  �jP  �jQ  �jR  �jS  �jT  NjU  �jV  �jW  ]�jY  ]�j[  }�ubhL)��}�(hh�`anonymous#C:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\vec4.h(36,2)�����}�(hKhh)��}�(hhhM�hK$hKubh�ubhhMh]�(h�)��}�(hh�w�����}�(hKhh)��}�(hhhM�hK$hKubh�ubhj�  h]�haj�  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�	_wpadding�����}�(hKhh)��}�(hhhM�hK$hKubh�ubhj�  h]�haj�  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubehaj�  hbhchdjD  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]�jH  NjI  Nh��jJ  NjK  NjL  �jM  �jN  �jO  �jP  �jQ  �jR  �jS  �jT  NjU  �jV  �jW  ]�jY  ]�j[  }�ubh)��}�(hNhhMh]�h h�#endif�����}�(hK
hh)��}�(hhhM�hK%hKubh�ububh �Function���)��}�(h�constructor�hhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�//// Initializes all vector components with 0.0
�����}�(hKhh)��}�(hhhM�hK'hKubh�ubah��//// Initializes all vector components with 0.0
�h�}�h��h���explicit���deleted���retType��void��const��hk]��
observable�N�result�Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�4/// Initializes all vector components with a scalar
�����}�(hKhh)��}�(hhhM-hK*hKubh�ubah��4/// Initializes all vector components with a scalar
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�h �	Parameter���)��}�(h�ValueTypeParam�hh�in�����}�(hKhh)��}�(hhhMhK+hKubh�ubhzNhs��input���output��ubaj�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�3/// Initializes all vector components individually
�����}�(hKhh)��}�(hhhM�hK-hKubh�ubah��3/// Initializes all vector components individually
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�(j   )��}�(h�ValueTypeParam�hh�ix�����}�(hKhh)��}�(hhhM�hK.hKubh�ubhzNhs�j
  �j  �ubj   )��}�(h�ValueTypeParam�hh�iy�����}�(hKhh)��}�(hhhM
hK.hK2ubh�ubhzNhs�j
  �j  �ubj   )��}�(h�ValueTypeParam�hh�iz�����}�(hKhh)��}�(hhhMhK.hKEubh�ubhzNhs�j
  �j  �ubj   )��}�(h�ValueTypeParam�hh�iw�����}�(hKhh)��}�(hhhM0hK.hKXubh�ubhzNhs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�hK1hKubhs�hh�T2�����}�(hKhh)��}�(hhhM�hK1hKubh�ubhzNh{Nubh �NontypeTemplateParam���)��}�(hh)��}�(hhhM�hK1hKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hK1hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�3/// Initializes components from another 4d vector.
�����}�(hKhh)��}�(hhhMWhK0hKubh�ubah��3/// Initializes components from another 4d vector.
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j   )��}�(h�const Vec4<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hK1hKCubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM@hK4hKubhs�hh�T2�����}�(hKhh)��}�(hhhMIhK4hKubh�ubhzNh{NubjN  )��}�(hh)��}�(hhhMMhK4hKubhs�hh�S2�����}�(hKhh)��}�(hhhMQhK4hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�3/// Initializes components from another 4d vector.
�����}�(hKhh)��}�(hhhMhK3hKubh�ubah��3/// Initializes components from another 4d vector.
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j   )��}�(h�const Col4<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhMwhK4hKCubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfhh)��}�hk]�jN  )��}�(hh)��}�(hhhM�hK7hKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hK7hKubh�ubhzNh�Int�h{Nubasbh|NhNh}Nh~NhK h�]�h�3/// Initializes components from another 4d vector.
�����}�(hKhh)��}�(hhhM�hK6hKubh�ubah��3/// Initializes components from another 4d vector.
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j   )��}�(h�const Vec4<T, S2>&�hh�v�����}�(hKhh)��}�(hhhMhK7hK,ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�hK;hKubhs�hh�T2�����}�(hKhh)��}�(hhhM�hK;hKubh�ubhzNh{NubjN  )��}�(hh)��}�(hhhM�hK;hKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hK;hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�(h�]/// Initializes components from a 3d vector and add an additional value for the w-component.
�����}�(hKhh)��}�(hhhM5hK9hKubh�ubh�$/// The default value for w is 1.0.
�����}�(hKhh)��}�(hhhM�hK:hKubh�ubeh���/// Initializes components from a 3d vector and add an additional value for the w-component.
/// The default value for w is 1.0.
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�(j   )��}�(h�const Vec3<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hK;hKCubh�ubhzNhs�j
  �j  �ubj   )��}�(h�T�hh�iw�����}�(hKhh)��}�(hhhM�hK;hKHubh�ubhz�T(1)�hs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�6/// Skips initialization of vector (for better speed)
�����}�(hKhh)��}�(hhhM8hK=hKubh�ubah��6/// Skips initialization of vector (for better speed)
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j   )��}�(h�ENUM_DONT_INITIALIZE�hh�v�����}�(hKhh)��}�(hhhM�hK>hK%ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�GetColor�����}�(hKhh)��}�(hhhM�hKAhKubh�ubhhMh]�haj  hbhchd�function�hfNh|NhNh}Nh~NhK h�]�h�&/// Reinterprets the vector as color.
�����}�(hKhh)��}�(hhhM�hK@hKubh�ubah��&/// Reinterprets the vector as color.
�h�}�h��h��j�  �j�  �j�  �const Col4<T, STRIDE>&�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�GetColor�����}�(hKhh)��}�(hhhMO	hKDhKubh�ubhhMh]�haj,  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�&/// Reinterprets the vector as color.
�����}�(hKhh)��}�(hhhM	hKChKubh�ubah��&/// Reinterprets the vector as color.
�h�}�h��h��j�  �j�  �j�  �Col4<T, STRIDE>&�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�
GetVector3�����}�(hKhh)��}�(hhhM�	hKGhKubh�ubhhMh]�haj@  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�)/// Gets the x/y/z components without w.
�����}�(hKhh)��}�(hhhM�	hKFhKubh�ubah��)/// Gets the x/y/z components without w.
�h�}�h��h��j�  �j�  �j�  �const Vec3<T, STRIDE>&�j�  �hk]�j�  Nj�  Nubj�  )��}�(hj�  hhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h��/// When STRIDE is not 1, we have to provide copy constructor and operator because the default ones would also copy the padding.
�����}�(hKhh)��}�(hhhM
hKIhKubh�ubh��/// When STRIDE is 1, we want to avoid to declare them (because then the type wouldn't be trivially copyable any longer), so we use DummyParamType for the parameter in that case.
�����}�(hKhh)��}�(hhhM�
hKJhKubh�ubeh�X4  /// When STRIDE is not 1, we have to provide copy constructor and operator because the default ones would also copy the padding.
/// When STRIDE is 1, we want to avoid to declare them (because then the type wouldn't be trivially copyable any longer), so we use DummyParamType for the parameter in that case.
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j   )��}�(h�Gconst typename std::conditional<STRIDE==1, DummyParamType, Vec4>::type&�hh�src�����}�(hKhh)��}�(hhhM�hKKhK`ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator =�����}�(hKhh)��}�(hhhM�hKThKubh�ubhhMh]�hajp  hbhchdj  hfNh|NhNh}Nh~NhK h�]�(h�/// Copies the source vector.
�����}�(hKhh)��}�(hhhM hKPhKubh�ubh�)/// @param[in] src								Source vector.
�����}�(hKhh)��}�(hhhM?hKQhKubh�ubh�/// @return												*this.
�����}�(hKhh)��}�(hhhMihKRhKubh�ubeh��e/// Copies the source vector.
/// @param[in] src								Source vector.
/// @return												*this.
�h�}�h��h��j�  �j�  �j�  �Vec4&�j�  �hk]�j   )��}�(h�Gconst typename std::conditional<STRIDE==1, DummyParamType, Vec4>::type&�hh�src�����}�(hKhh)��}�(hhhM?hKThK]ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator []�����}�(hKhh)��}�(hhhMhK^hKubh�ubhhMh]�haj�  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h��/// Accesses vector component: index 0 is 'x', index 1 is 'y', index 2 is 'z'. All other values must not be used and will crash
�����}�(hKhh)��}�(hhhM�hK]hKubh�ubah���/// Accesses vector component: index 0 is 'x', index 1 is 'y', index 2 is 'z'. All other values must not be used and will crash
�h�}�h��h��j�  �j�  �j�  �T&�j�  �hk]�j   )��}�(h�Int�hh�l�����}�(hKhh)��}�(hhhM$hK^hKubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator []�����}�(hKhh)��}�(hhhM�hKehKubh�ubhhMh]�haj�  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h��/// Accesses vector component: index 0 is 'x', index 1 is 'y', index 2 is 'z'.  All other values must not be used and will crash
�����}�(hKhh)��}�(hhhMlhKdhKubh�ubah���/// Accesses vector component: index 0 is 'x', index 1 is 'y', index 2 is 'z'.  All other values must not be used and will crash
�h�}�h��h��j�  �j�  �j�  �ValueTypeParam�j�  �hk]�j   )��}�(h�Int�hh�l�����}�(hKhh)��}�(hhhMhKehK!ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator +=�����}�(hKhh)��}�(hhhM�hKlhK'ubh�ubhhMh]�haj�  hbhchdj  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�hKlhKubhs�hh�T2�����}�(hKhh)��}�(hhhM�hKlhKubh�ubhzNh{NubjN  )��}�(hh)��}�(hhhM�hKlhKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hKlhKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�/// Adds two vectors
�����}�(hKhh)��}�(hhhMahKkhKubh�ubah��/// Adds two vectors
�h�}�h��h��j�  �j�  �j�  �Vec4&�j�  �hk]�j   )��}�(h�const Vec4<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hKlhKGubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator +=�����}�(hKhh)��}�(hhhM�hK{hKubh�ubhhMh]�haj  hbhchdj  hfNh|NhNh}Nh~NhK h�]�(h�/// Adds a vector.
�����}�(hKhh)��}�(hhhMchKvhKubh�ubh��/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
�����}�(hKhh)��}�(hhhMwhKwhKubh�ubh�-/// @param[in] v									Vector to be added.
�����}�(hKhh)��}�(hhhM:hKxhKubh�ubh�/// @return												*this.
�����}�(hKhh)��}�(hhhMhhKyhKubh�ubeh�X   /// Adds a vector.
/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
/// @param[in] v									Vector to be added.
/// @return												*this.
�h�}�h��h��j�  �j�  �j�  �Vec4&�j�  �hk]�j   )��}�(h�const Vec4&�hh�v�����}�(hKhh)��}�(hhhMhK{hK ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator -=�����}�(hKhh)��}�(hhhM�hK�hK'ubh�ubhhMh]�haj7  hbhchdj  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhMqhK�hKubhs�hh�T2�����}�(hKhh)��}�(hhhMzhK�hKubh�ubhzNh{NubjN  )��}�(hh)��}�(hhhM~hK�hKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�/// Subtracts two vectors
�����}�(hKhh)��}�(hhhMLhK�hKubh�ubah��/// Subtracts two vectors
�h�}�h��h��j�  �j�  �j�  �Vec4&�j�  �hk]�j   )��}�(h�const Vec4<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hK�hKGubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator -=�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�hajl  hbhchdj  hfNh|NhNh}Nh~NhK h�]�(h�/// Subtracts a vector.
�����}�(hKhh)��}�(hhhMShK�hKubh�ubh��/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
�����}�(hKhh)��}�(hhhMlhK�hKubh�ubh�=/// @param[in] v									Vector to be substracted from this.
�����}�(hKhh)��}�(hhhM/hK�hKubh�ubh�/// @return												*this.
�����}�(hKhh)��}�(hhhMmhK�hKubh�ubeh�X5  /// Subtracts a vector.
/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
/// @param[in] v									Vector to be substracted from this.
/// @return												*this.
�h�}�h��h��j�  �j�  �j�  �Vec4&�j�  �hk]�j   )��}�(h�const Vec4&�hh�v�����}�(hKhh)��}�(hhhMhK�hK ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhM�hK�hK'ubh�ubhhMh]�haj�  hbhchdj  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�hK�hKubhs�hh�T2�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhzNh{NubjN  )��}�(hh)��}�(hhhM�hK�hKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�*/// Multiplies two vectors component-wise
�����}�(hKhh)��}�(hhhMQhK�hKubh�ubah��*/// Multiplies two vectors component-wise
�h�}�h��h��j�  �j�  �j�  �Vec4&�j�  �hk]�j   )��}�(h�const Vec4<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hK�hKGubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhMhK�hKubh�ubhhMh]�haj�  hbhchdj  hfNh|NhNh}Nh~NhK h�]�(h�+/// Multiplies with vector component-wise.
�����}�(hKhh)��}�(hhhMhhK�hKubh�ubh��/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubh�7/// @param[in] v									Vector to be multiplied with.
�����}�(hKhh)��}�(hhhMWhK�hKubh�ubh�/// @return												*this.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubeh�XB  /// Multiplies with vector component-wise.
/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
/// @param[in] v									Vector to be multiplied with.
/// @return												*this.
�h�}�h��h��j�  �j�  �j�  �Vec4&�j�  �hk]�j   )��}�(h�const Vec4&�hh�v�����}�(hKhh)��}�(hhhM(hK�hK ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj�  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhMshK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �Vec4&�j�  �hk]�j   )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhM�hK�hK#ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator /=�����}�(hKhh)��}�(hhhMfhK�hKubh�ubhhMh]�haj  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�V/// Divides each vector component by a scalar. The passed argument is checked for 0.0
�����}�(hKhh)��}�(hhhM	hK�hKubh�ubah��V/// Divides each vector component by a scalar. The passed argument is checked for 0.0
�h�}�h��h��j�  �j�  �j�  �Vec4&�j�  �hk]�j   )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhM�hK�hK#ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM hK�hKubh�ubhhMh]�haj9  hbhchdj  hfNh|h�friend�����}�(hKhh)��}�(hhhMhK�hKubh�ubhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�(j   )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhM:hK�hK-ubh�ubhzNhs�j
  �j  �ubj   )��}�(h�const Vec4&�hh�v�����}�(hKhh)��}�(hhhMIhK�hK<ubh�ubhzNhs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haje  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j   )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhM�hK�hK&ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM�hK�hKhubh�ubhhMh]�haj�  hbhchdj  hfhh)��}�hk]�hn)��}�(hh)��}�(hhhM_hK�hKubhs�hh�S�����}�(hKhh)��}�(hhhMhhK�hKubh�ubhzNh{Nubasbh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhM#hK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �OVec4<typename MultiplicativePromotion<T, S, std::is_scalar<S>::value>::type, 1>�j�  �hk]�j   )��}�(h�S�hh�s�����}�(hKhh)��}�(hhhM�hK�hKuubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator /�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj�  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�R/// Divides each vector component by a scalar. The scalar value is tested for 0.0
�����}�(hKhh)��}�(hhhM5hK�hKubh�ubah��R/// Divides each vector component by a scalar. The scalar value is tested for 0.0
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j   )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhM�hK�hK&ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM;hK�hKubh�ubhhMh]�haj�  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�*/// Multiplies two vectors component-wise
�����}�(hKhh)��}�(hhhMhK�hKubh�ubah��*/// Multiplies two vectors component-wise
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j   )��}�(h�const Vec4&�hh�v�����}�(hKhh)��}�(hhhMRhK�hK#ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator +�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj�  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�/// Adds two vectors
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��/// Adds two vectors
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j   )��}�(h�const Vec4&�hh�v�����}�(hKhh)��}�(hhhM�hK�hK#ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator -�����}�(hKhh)��}�(hhhMFhK�hKubh�ubhhMh]�haj  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h� /// Subtracts vector v2 from v1
�����}�(hKhh)��}�(hhhMhK�hKubh�ubah�� /// Subtracts vector v2 from v1
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j   )��}�(h�const Vec4&�hh�v�����}�(hKhh)��}�(hhhM]hK�hK#ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�
operator -�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj   hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�/// Negates vector v
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��/// Negates vector v
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�operator ==�����}�(hKhh)��}�(hhhMq hMhK*ubh�ubhhMh]�haj4  hbhchdj  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhMS hMhKubhs�hh�T2�����}�(hKhh)��}�(hhhM\ hMhKubh�ubhzNh{NubjN  )��}�(hh)��}�(hhhM` hMhKubhs�hh�S2�����}�(hKhh)��}�(hhhMd hMhKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�(h�/// Equality operator.
�����}�(hKhh)��}�(hhhMahK�hKubh�ubh�,/// @param[in] v									Comparison vector.
�����}�(hKhh)��}�(hhhMyhK�hKubh�ubh�F/// @return												True if this and v are equal, otherwise false.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubeh���/// Equality operator.
/// @param[in] v									Comparison vector.
/// @return												True if this and v are equal, otherwise false.
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j   )��}�(h�const Vec4<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM� hMhKJubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator ==�����}�(hKhh)��}�(hhhM�"hMhKubh�ubhhMh]�haju  hbhchdj  hfNh|NhNh}Nh~NhK h�]�(h�/// Equality operator.
�����}�(hKhh)��}�(hhhM5!hMhKubh�ubh��/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector
�����}�(hKhh)��}�(hhhMM!hMhKubh�ubh�,/// @param[in] v									Comparison vector.
�����}�(hKhh)��}�(hhhM"hM	hKubh�ubh�F/// @return												True if this and v are equal, otherwise false.
�����}�(hKhh)��}�(hhhM<"hM
hKubh�ubeh�XJ  /// Equality operator.
/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector
/// @param[in] v									Comparison vector.
/// @return												True if this and v are equal, otherwise false.
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j   )��}�(h�const Vec4&�hh�v�����}�(hKhh)��}�(hhhM #hMhK#ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator !=�����}�(hKhh)��}�(hhhM�$hMhK*ubh�ubhhMh]�haj�  hbhchdj  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�$hMhKubhs�hh�T2�����}�(hKhh)��}�(hhhM�$hMhKubh�ubhzNh{NubjN  )��}�(hh)��}�(hhhM�$hMhKubhs�hh�S2�����}�(hKhh)��}�(hhhM�$hMhKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�(h�/// Inequality operator.
�����}�(hKhh)��}�(hhhM�#hMhKubh�ubh�,/// @param[in] v									Comparison vector.
�����}�(hKhh)��}�(hhhM�#hMhKubh�ubh�F/// @return												False if this and v are equal, otherwise true.
�����}�(hKhh)��}�(hhhM�#hMhKubh�ubeh���/// Inequality operator.
/// @param[in] v									Comparison vector.
/// @return												False if this and v are equal, otherwise true.
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j   )��}�(h�const Vec4<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�$hMhKJubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�operator !=�����}�(hKhh)��}�(hhhM2'hM!hKubh�ubhhMh]�haj�  hbhchdj  hfNh|NhNh}Nh~NhK h�]�(h�/// Inequality operator.
�����}�(hKhh)��}�(hhhM}%hMhKubh�ubh��/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector
�����}�(hKhh)��}�(hhhM�%hMhKubh�ubh�,/// @param[in] v									Comparison vector.
�����}�(hKhh)��}�(hhhMY&hMhKubh�ubh�F/// @return												False if this and v are equal, otherwise true.
�����}�(hKhh)��}�(hhhM�&hMhKubh�ubeh�XL  /// Inequality operator.
/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector
/// @param[in] v									Comparison vector.
/// @return												False if this and v are equal, otherwise true.
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j   )��}�(h�const Vec4&�hh�v�����}�(hKhh)��}�(hhhMJ'hM!hK#ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�LessThanOrEqual�����}�(hKhh)��}�(hhhMX(hM)hKubh�ubhhMh]�haj  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j   )��}�(h�const Vec4&�hh�v�����}�(hKhh)��}�(hhhMt(hM)hK(ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�GetHashCode�����}�(hKhh)��}�(hhhM�)hM2hKubh�ubhhMh]�haj*  hbhchdj  hfNh|NhNh}Nh~NhK h�]�(h�N/// Returns the hash code of the vector (used for hash maps and comparisons).
�����}�(hKhh)��}�(hhhM)hM/hKubh�ubh�//// @return												The vector's hash code.
�����}�(hKhh)��}�(hhhMj)hM0hKubh�ubeh��}/// Returns the hash code of the vector (used for hash maps and comparisons).
/// @return												The vector's hash code.
�h�}�h��h��j�  �j�  �j�  �UInt�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�IsEqual�����}�(hKhh)��}�(hhhM�*hM8hKubh�ubhhMh]�hajD  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�G/// Tests component-wise if the difference is no bigger than 'epsilon'
�����}�(hKhh)��}�(hhhM<*hM7hKubh�ubah��G/// Tests component-wise if the difference is no bigger than 'epsilon'
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�(j   )��}�(h�const Vec4&�hh�other�����}�(hKhh)��}�(hhhM�*hM8hKubh�ubhzNhs�j
  �j  �ubj   )��}�(h�ValueTypeParam�hh�epsilon�����}�(hKhh)��}�(hhhM�*hM8hK5ubh�ubhzNhs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hh�Dot�����}�(hKhh)��}�(hhhM�+hM>hKubh�ubhhMh]�hajj  hbhchdj  hfNh|h�friend�����}�(hKhh)��}�(hhhMz+hM>hKubh�ubhNh}Nh~NhK h�]�h�(/// Calculates dot product of v1 and v2
�����}�(hKhh)��}�(hhhMQ+hM=hKubh�ubah��(/// Calculates dot product of v1 and v2
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�(j   )��}�(h�const Vec4&�hh�v1�����}�(hKhh)��}�(hhhM�+hM>hKubh�ubhzNhs�j
  �j  �ubj   )��}�(h�const Vec4&�hh�v2�����}�(hKhh)��}�(hhhM�+hM>hK+ubh�ubhzNhs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hh�Abs�����}�(hKhh)��}�(hhhMs-hMHhKubh�ubhhMh]�haj�  hbhchdj  hfNh|h�friend�����}�(hKhh)��}�(hhhMb-hMHhKubh�ubhNh}Nh~NhK h�]�(h�:/// Returns the vector with absolute value for each entry
�����}�(hKhh)��}�(hhhMK,hMDhKubh�ubh�2/// @param[in] v1									input vector to work on
�����}�(hKhh)��}�(hhhM�,hMEhKubh�ubh�L/// @return												component wise absolute value vector of input vector
�����}�(hKhh)��}�(hhhM�,hMFhKubh�ubeh���/// Returns the vector with absolute value for each entry
/// @param[in] v1									input vector to work on
/// @return												component wise absolute value vector of input vector
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j   )��}�(h�const Vec4&�hh�v1�����}�(hKhh)��}�(hhhM�-hMHhK#ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�Dot�����}�(hKhh)��}�(hhhML.hMNhKVubh�ubhhMh]�haj�  hbhchdj  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM.hMNhKubhs�hh�T2�����}�(hKhh)��}�(hhhM.hMNhKubh�ubhzNh{NubjN  )��}�(hh)��}�(hhhM.hMNhKubhs�hh�S2�����}�(hKhh)��}�(hhhM.hMNhKubh�ubhzNh�Int�h{Nubesbh|h�friend�����}�(hKhh)��}�(hhhM.hMNhK!ubh�ubhNh}Nh~NhK h�]�h�(/// Calculates dot product of v1 and v2
�����}�(hKhh)��}�(hhhM�-hMMhKubh�ubah��(/// Calculates dot product of v1 and v2
�h�}�h��h��j�  �j�  �j�  �-typename MultiplicativePromotion<T, T2>::type�j�  �hk]�(j   )��}�(h�const Vec4&�hh�v1�����}�(hKhh)��}�(hhhM\.hMNhKfubh�ubhzNhs�j
  �j  �ubj   )��}�(h�const Vec4<T2, S2>&�hh�v2�����}�(hKhh)��}�(hhhMt.hMNhK~ubh�ubhzNhs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hh�IsZero�����}�(hKhh)��}�(hhhM�.hMThKubh�ubhhMh]�haj	  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�&/// Checks if each component is zero.
�����}�(hKhh)��}�(hhhM�.hMShKubh�ubah��&/// Checks if each component is zero.
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�SetZero�����}�(hKhh)��}�(hhhMi/hMZhKubh�ubhhMh]�haj  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�!/// Sets all components to zero.
�����}�(hKhh)��}�(hhhMB/hMYhKubh�ubah��!/// Sets all components to zero.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�
GetAverage�����}�(hKhh)��}�(hhhM�/hM`hKubh�ubhhMh]�haj1  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�;/// Calculates the average value of 'x', 'y', 'z' and 'w'.
�����}�(hKhh)��}�(hhhM�/hM_hKubh�ubah��;/// Calculates the average value of 'x', 'y', 'z' and 'w'.
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�GetSum�����}�(hKhh)��}�(hhhMD0hMfhKubh�ubhhMh]�hajE  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�1/// Calculates the sum of 'x', 'y', 'z' and 'w'.
�����}�(hKhh)��}�(hhhM0hMehKubh�ubah��1/// Calculates the sum of 'x', 'y', 'z' and 'w'.
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�Min�����}�(hKhh)��}�(hhhM�0hMlhKubh�ubhhMh]�hajY  hbhchdj  hfNh|h�friend�����}�(hKhh)��}�(hhhM�0hMlhKubh�ubhNh}Nh~NhK h�]�h�./// Calculates the minimum of each component.
�����}�(hKhh)��}�(hhhMs0hMkhKubh�ubah��./// Calculates the minimum of each component.
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�(j   )��}�(h�const Vec4&�hh�a�����}�(hKhh)��}�(hhhM�0hMlhK#ubh�ubhzNhs�j
  �j  �ubj   )��}�(h�const Vec4&�hh�other�����}�(hKhh)��}�(hhhM�0hMlhK2ubh�ubhzNhs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hh�Max�����}�(hKhh)��}�(hhhM�1hMrhKubh�ubhhMh]�haj�  hbhchdj  hfNh|h�friend�����}�(hKhh)��}�(hhhM�1hMrhKubh�ubhNh}Nh~NhK h�]�h�./// Calculates the maximum of each component.
�����}�(hKhh)��}�(hhhMr1hMqhKubh�ubah��./// Calculates the maximum of each component.
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�(j   )��}�(h�const Vec4&�hh�a�����}�(hKhh)��}�(hhhM�1hMrhK#ubh�ubhzNhs�j
  �j  �ubj   )��}�(h�const Vec4&�hh�other�����}�(hKhh)��}�(hhhM�1hMrhK2ubh�ubhzNhs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hh�ClampMin�����}�(hKhh)��}�(hhhM�2hMxhKubh�ubhhMh]�haj�  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�'/// Set the minimum of each component.
�����}�(hKhh)��}�(hhhMq2hMwhKubh�ubah��'/// Set the minimum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j   )��}�(h�const Vec4&�hh�other�����}�(hKhh)��}�(hhhM�2hMxhKubh�ubhz�Vec4()�hs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�ClampMax�����}�(hKhh)��}�(hhhMl3hM�hKubh�ubhhMh]�haj�  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�'/// Set the maximum of each component.
�����}�(hKhh)��}�(hhhM?3hM�hKubh�ubah��'/// Set the maximum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j   )��}�(h�const Vec4&�hh�other�����}�(hKhh)��}�(hhhM�3hM�hKubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�SetMin�����}�(hKhh)��}�(hhhM84hM�hKubh�ubhhMh]�haj�  hbhchdj  hfNh|h�friend�����}�(hKhh)��}�(hhhM,4hM�hKubh�ubhNh}Nh~NhK h�]�h�'/// Set the minimum of each component.
�����}�(hKhh)��}�(hhhM4hM�hKubh�ubah��'/// Set the minimum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�(j   )��}�(h�Vec4&�hh�a�����}�(hKhh)��}�(hhhME4hM�hKubh�ubhzNhs�j
  �j  �ubj   )��}�(h�const Vec4&�hh�other�����}�(hKhh)��}�(hhhMT4hM�hK*ubh�ubhzNhs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hh�SetMax�����}�(hKhh)��}�(hhhM�4hM�hKubh�ubhhMh]�haj	  hbhchdj  hfNh|h�friend�����}�(hKhh)��}�(hhhM�4hM�hKubh�ubhNh}Nh~NhK h�]�h�'/// Set the maximum of each component.
�����}�(hKhh)��}�(hhhMx4hM�hKubh�ubah��'/// Set the maximum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�(j   )��}�(h�Vec4&�hh�a�����}�(hKhh)��}�(hhhM�4hM�hKubh�ubhzNhs�j
  �j  �ubj   )��}�(h�const Vec4&�hh�other�����}�(hKhh)��}�(hhhM�4hM�hK*ubh�ubhzNhs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hh�Clamp01�����}�(hKhh)��}�(hhhM65hM�hKubh�ubhhMh]�hajD	  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�?/// Returns a vector that is clamped to the range [0.0 .. 1.0]
�����}�(hKhh)��}�(hhhM�4hM�hKubh�ubah��?/// Returns a vector that is clamped to the range [0.0 .. 1.0]
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�	GetLength�����}�(hKhh)��}�(hhhM�5hM�hKubh�ubhhMh]�hajX	  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�%/// Returns the length of the vector
�����}�(hKhh)��}�(hhhM�5hM�hKubh�ubah��%/// Returns the length of the vector
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�GetSquaredLength�����}�(hKhh)��}�(hhhMN6hM�hKubh�ubhhMh]�hajl	  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�-/// Returns the squared length of the vector
�����}�(hKhh)��}�(hhhM6hM�hKubh�ubah��-/// Returns the squared length of the vector
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�GetNormalized�����}�(hKhh)��}�(hhhM�6hM�hKubh�ubhhMh]�haj�	  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�@/// Returns a normalized vector, so that GetLength(vector)==1.0
�����}�(hKhh)��}�(hhhM�6hM�hKubh�ubah��@/// Returns a normalized vector, so that GetLength(vector)==1.0
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�
operator !�����}�(hKhh)��}�(hhhM�7hM�hKubh�ubhhMh]�haj�	  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�@/// Returns a normalized vector, so that GetLength(vector)==1.0
�����}�(hKhh)��}�(hhhMk7hM�hKubh�ubah��@/// Returns a normalized vector, so that GetLength(vector)==1.0
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�	Normalize�����}�(hKhh)��}�(hhhMw8hM�hKubh�ubhhMh]�haj�	  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�5/// Normalizes this vector, so that GetLength()==1.0
�����}�(hKhh)��}�(hhhM<8hM�hKubh�ubah��5/// Normalizes this vector, so that GetLength()==1.0
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�GetAngle�����}�(hKhh)��}�(hhhM,9hM�hKubh�ubhhMh]�haj�	  hbhchdj  hfNh|h�friend�����}�(hKhh)��}�(hhhM#9hM�hKubh�ubhNh}Nh~NhK h�]�h�4/// Calculates angle (in radians) between v1 and v2
�����}�(hKhh)��}�(hhhM�8hM�hKubh�ubah��4/// Calculates angle (in radians) between v1 and v2
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�(j   )��}�(h�const Vec4&�hh�v1�����}�(hKhh)��}�(hhhMA9hM�hK ubh�ubhzNhs�j
  �j  �ubj   )��}�(h�const Vec4&�hh�v2�����}�(hKhh)��}�(hhhMQ9hM�hK0ubh�ubhzNhs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hh�ToString�����}�(hKhh)��}�(hhhML;hM�hK	ubh�ubhhMh]�haj�	  hbhchdj  hfNh|NhNh}Nh~NhK h�]�(h�./// Returns a readable string of the content.
�����}�(hKhh)��}�(hhhM!:hM�hKubh�ubh�j/// @param[in] formatStatement		Nullptr or additional formatting instruction. See also @ref format_float.
�����}�(hKhh)��}�(hhhMP:hM�hKubh�ubh�-/// @return												The converted result.
�����}�(hKhh)��}�(hhhM�:hM�hKubh�ubeh���/// Returns a readable string of the content.
/// @param[in] formatStatement		Nullptr or additional formatting instruction. See also @ref format_float.
/// @return												The converted result.
�h�}�h��h��j�  �j�  �j�  �String�j�  �hk]�j   )��}�(h�const FormatStatement*�hh�formatStatement�����}�(hKhh)��}�(hhhMl;hM�hK)ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�GetMin�����}�(hKhh)��}�(hhhM�<hM�hKubh�ubhhMh]�haj
  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�2/// Returns the minimum of 'x', 'y', 'z' and 'w'.
�����}�(hKhh)��}�(hhhMS<hM�hKubh�ubah��2/// Returns the minimum of 'x', 'y', 'z' and 'w'.
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�GetMax�����}�(hKhh)��}�(hhhM�<hM�hKubh�ubhhMh]�haj%
  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�2/// Returns the maximum of 'x', 'y', 'z' and 'w'.
�����}�(hKhh)��}�(hhhM�<hM�hKubh�ubah��2/// Returns the maximum of 'x', 'y', 'z' and 'w'.
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�GetRightRotated�����}�(hKhh)��}�(hhhMX?hM�hKubh�ubhhMh]�haj9
  hbhchdj  hfNh|NhNh}Nh~NhK h�]�(h�{/// Returns a vector where the components have been rotated to the right (in the usual (x, y, z, w)-representation). E.g.,
�����}�(hKhh)��}�(hhhM�=hM�hKubh�ubh�A/// with a value of 1 for rots, the result will be (w, x, y, z).
�����}�(hKhh)��}�(hhhM>hM�hKubh�ubh�q/// @param[in] rots								Number of rotations, may be negative. The result depends only on the number modulo 4.
�����}�(hKhh)��}�(hhhMM>hM�hKubh�ubh�7/// @return												Vector with rotated components.
�����}�(hKhh)��}�(hhhM�>hM�hKubh�ubeh�Xd  /// Returns a vector where the components have been rotated to the right (in the usual (x, y, z, w)-representation). E.g.,
/// with a value of 1 for rots, the result will be (w, x, y, z).
/// @param[in] rots								Number of rotations, may be negative. The result depends only on the number modulo 4.
/// @return												Vector with rotated components.
�h�}�h��h��j�  �j�  �j�  �Vec4�j�  �hk]�j   )��}�(h�Int�hh�rots�����}�(hKhh)��}�(hhhMl?hM�hKubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�
NormalizeW�����}�(hKhh)��}�(hhhMW@hM�hKubh�ubhhMh]�hajh
  hbhchdj  hfNh|NhNh}Nh~NhK h�]�h�-/// Scales this vector such that w equals 1.
�����}�(hKhh)��}�(hhhM$@hM�hKubh�ubah��-/// Scales this vector such that w equals 1.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j�  Nj�  Nubj�  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhMaAhMhKubh�ubhhMh]�haj|
  hbhchdj  hfhh)��}�hk]�hn)��}�(hh)��}�(hhhMOAhMhKubhs�hh�V�����}�(hKhh)��}�(hhhMXAhMhKubh�ubhzNh{Nubasbh|NhNh}Nh~NhK h�]�h�"/// Multiplies vector by a matrix
�����}�(hKhh)��}�(hhhM"AhMhKubh�ubah��"/// Multiplies vector by a matrix
�h�}�h��h��j�  �j�  �j�  �Vec4&�j�  �hk]�j   )��}�(h�const SqMat4<V>&�hh�m�����}�(hKhh)��}�(hhhM~AhMhK;ubh�ubhzNhs�j
  �j  �ubaj�  Nj�  Nubj�  )��}�(hh�	NullValue�����}�(hKhh)��}�(hhhM�ChMhKubh�ubhhMh]�haj�
  hbhchdj  hfNh|NhNh}Nh~NhK h�]�(h�K/// Returns a null value of the vector (see nullvalue.h for more details).
�����}�(hKhh)��}�(hhhMChMhKubh�ubh�3/// @return												A null value of the vector.
�����}�(hKhh)��}�(hhhMXChMhKubh�ubeh��~/// Returns a null value of the vector (see nullvalue.h for more details).
/// @return												A null value of the vector.
�h�}�h��h��j�  �j�  �j�  �const Vec4&�j�  �hk]�j�  Nj�  NubehahQhbhchdjD  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM*hKhKubhs�hh�T�����}�(hKhh)��}�(hhhM3hKhKubh�ubhzNh{NubjN  )��}�(hh)��}�(hhhM6hKhKubhs�hh�STRIDE�����}�(hKhh)��}�(hhhM:hKhKubh�ubhz�1�h�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]�jH  NjI  Nh��jJ  NjK  NjL  �jM  �jN  �jO  �jP  �jQ  �jR  �jS  �jT  NjU  �jV  �jW  ]�jY  ]�j[  }�ubh)��}�(hNhh0h]�h h�#ifndef STRIDE�����}�(hK
hh)��}�(hhhM.DhMhKubh�ububj�  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM�DhMhK�ubh�ubhh0h]�haj�
  hbhchdj  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhMxDhMhKubhs�hh�T�����}�(hKhh)��}�(hhhM�DhMhKubh�ubhzNh{NubjN  )��}�(hh)��}�(hhhM�DhMhKubhs�hh�STR�����}�(hKhh)��}�(hhhM�DhMhKubh�ubhzNh�Int�h{Nubhn)��}�(hh)��}�(hhhM�DhMhK ubhs�hh�S�����}�(hKhh)��}�(hhhM�DhMhK)ubh�ubhzNh{Nubesbh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhM=DhMhKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �OVec4<typename MultiplicativePromotion<T, S, std::is_scalar<S>::value>::type, 1>�j�  �hk]�(j   )��}�(h�S�hh�s�����}�(hKhh)��}�(hhhM�DhMhK�ubh�ubhzNhs�j
  �j  �ubj   )��}�(h�const Vec4<T, STR>&�hh�v�����}�(hKhh)��}�(hhhMEhMhK�ubh�ubhzNhs�j
  �j  �ubej�  Nj�  Nubj�  )��}�(hh�PrivateGetDataType�����}�(hKhh)��}�(hhhM�EhM!hKKubh�ubhh0h]�haj0  hbhchdj  hfhh)��}�hk]�(jN  )��}�(hh)��}�(hhhM�EhM!hKubhs�hh�POLICY�����}�(hKhh)��}�(hhhM�EhM!hKubh�ubhzNh�GET_DATATYPE_POLICY�h{Nubhn)��}�(hh)��}�(hhhM�EhM!hK'ubhs�hh�T�����}�(hKhh)��}�(hhhM�EhM!hK0ubh�ubhzNh{Nubesbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �Result<DataType>�j�  �hk]�(j   )��}�(h�Vec4<T, 1>**�h�anonymous_param_1�hzNhs�j
  �j  �ubj   )��}�(h�OverloadRank0�h�anonymous_param_2�hzNhs�j
  �j  �ubej�  Nj�  �DataType�ubhL)��}�(h�IsZeroInitialized<Vec4<T,1>>�hh0h]�hah�IsZeroInitialized�����}�(hKhh)��}�(hhhM�FhM(hKubh�ubhbhchdjD  hfhh)��}�hk]�hn)��}�(hh)��}�(hhhM�FhM(hKubhs�hh�T�����}�(hKhh)��}�(hhhM�FhM(hKubh�ubhzNh{Nubasbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��IsZeroInitialized<T>�h�public�����}�(hKhh)��}�(hhhM�FhM(hK>ubh�ubh	��ajH  NjI  Nh��jJ  NjK  NjL  �jM  �jN  �jO  �jP  �jQ  �jR  �jS  �jT  NjU  �jV  �jW  ]�jY  ]�j[  }�ubh)��}�(hNhh0h]�h h�#endif�����}�(hK
hh)��}�(hhhMGhM)hKubh�ububehah4hbhchd�	namespace�hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h���preprocessorConditions�]��root�hh N�containsResourceId���registry���usings����minIndentation�K �maxIndentation�K�firstMember��ubehahhbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��j�  ]�j�  hh ]�(hh'h0h9hBhMj�
  j�
  j,  jZ  j  ej�  �j�  �j�  ���hxx1�N�hxx2�N�snippets�}�j�  K j�  K j�  �ub.