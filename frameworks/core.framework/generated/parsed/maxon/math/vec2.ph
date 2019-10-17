����      �declarations��	Namespace���)��}�(�name��lexer��Token���� �����}�(�type�K�pos�h�SourcePosition���)��}�(�file��PC:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\vec2.h��index�K �line�KhKub�escaped��ub�owner�N�children�]�(h �	Directive���)��}�(hNhhh]��code�h�#ifndef MAXON_VECTORMODE�����}�(hK
hh)��}�(hhhK)hKhKubh�ububh)��}�(hNhhh]�h h�#endif�����}�(hK
hh)��}�(hhhK�hKhKubh�ububh)��}�(hh�maxon�����}�(hKhh)��}�(hhhK�hKhKubh�ubhhh]�(h)��}�(hNhh0h]�h h�#ifdef STRIDE�����}�(hK
hh)��}�(hhhK�hKhKubh�ububh)��}�(hNhh0h]�h h�#else�����}�(hK
hh)��}�(hhhMhKhKubh�ububh �Class���)��}�(hh�Vec2�����}�(hKhh)��}�(hhhMKhKhK.ubh�ubhh0h]�(h �	TypeAlias���)��}�(hh�Rebind�����}�(hKhh)��}�(hhhMvhKhKubh�ubhhMh]��
simpleName�h\�access��public��kind��	typealias��template�h �Template���)��}��params�]�h �TypeTemplateParam���)��}�(hh)��}�(hhhMdhKhKub�pack��hh�U�����}�(hKhh)��}�(hhhMmhKhKubh�ub�default�N�variance�Nubasb�friend�NhN�id�N�point�N�
artificial�K �doclist�]��doc�h	�annotations�}��	anonymous���bases�]��Vec2<U,STRIDE>�hch	��aubhW)��}�(hh�VectorStrideType�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��"std::integral_constant<Int,STRIDE>�hch	��aubhW)��}�(hh�	ValueType�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��T�hch	��aubhW)��}�(hh�ValueTypeParam�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��typename ByValueParam<T>::type�hch	��aubhW)��}�(hh�	Unstrided�����}�(hKhh)��}�(hhhM$hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��	Vec2<T,1>�hch	��aubhW)��}�(hh�BoolType�����}�(hKhh)��}�(hhhM�hKhKubh�ubhhMh]�hah�hbhchdhehfNh|NhNh}Nh~NhK h�]�(h�U/// The type returned by comparisons. If the template argument for T is a SIMD type,
�����}�(hKhh)��}�(hhhM>hKhKubh�ubh�K/// this will be a SIMD type, too, which contains the per-element results.
�����}�(hKhh)��}�(hhhM�hKhKubh�ubeh���/// The type returned by comparisons. If the template argument for T is a SIMD type,
/// this will be a SIMD type, too, which contains the per-element results.
�h�}�h��h�]��decltype(T()==T())�hch	��aubh)��}�(hNhhMh]�h h�#ifdef STRIDE�����}�(hK
hh)��}�(hhhMhKhKubh�ububh �Variable���)��}�(hh�x�����}�(hKhh)��}�(hhhMhKhKubh�ubhhMh]�hah�hbhchd�variable�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h���static��ubh�)��}�(hh�y�����}�(hKhh)��}�(hhhMhKhKubh�ubhhMh]�hah�hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh)��}�(hNhhMh]�h h�#else�����}�(hK
hh)��}�(hhhM"hKhKubh�ububhL)��}�(hh�`anonymous#C:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\vec2.h(31,2)�����}�(hKhh)��}�(hhhM)hKhKubh�ubhhMh]�(h�)��}�(hh�x�����}�(hKhh)��}�(hhhM3hKhKubh�ubhj  h]�haj  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�	_xpadding�����}�(hKhh)��}�(hhhM8hKhKubh�ubhj  h]�haj$  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubehaj  hbhchd�class�hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��	interface�N�refKind�Nh���refClass�N�baseInterfaces�N�derived���isError���implementation���	component���finalComponent���forward���
singleImpl���hasStaticMethods���generic�N�refClassForwardDeclared���missingInterfaces���ambiguousCalls�]��	selfCalls�]��methodNames�}�ubhL)��}�(hh�`anonymous#C:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\math\vec2.h(32,2)�����}�(hKhh)��}�(hhhMOhK hKubh�ubhhMh]�(h�)��}�(hh�y�����}�(hKhh)��}�(hhhMYhK hKubh�ubhjE  h]�hajR  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubh�)��}�(hh�	_ypadding�����}�(hKhh)��}�(hhhM^hK hKubh�ubhjE  h]�haj^  hbhchdh�hfNh|Nh�T�h}Nh~NhK h�]�h�h	h�}�h��h��ubehajI  hbhchdj,  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]�j0  Nj1  Nh��j2  Nj3  Nj4  �j5  �j6  �j7  �j8  �j9  �j:  �j;  �j<  Nj=  �j>  �j?  ]�jA  ]�jC  }�ubh)��}�(hNhhMh]�h h�#endif�����}�(hK
hh)��}�(hhhMthK!hKubh�ububh �Function���)��}�(h�constructor�hhMh]�hajy  hbhchdjy  hfNh|NhNh}Nh~NhK h�]�h�//// Initializes all vector components with 0.0
�����}�(hKhh)��}�(hhhM}hK#hKubh�ubah��//// Initializes all vector components with 0.0
�h�}�h��h���explicit���deleted���retType��void��const��hk]��
observable�N�result�Nubjv  )��}�(hjy  hhMh]�hajy  hbhchdjy  hfNh|NhNh}Nh~NhK h�]�h�4/// Initializes all vector components with a scalar
�����}�(hKhh)��}�(hhhM�hK&hKubh�ubah��4/// Initializes all vector components with a scalar
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�h �	Parameter���)��}�(h�ValueTypeParam�hh�in�����}�(hKhh)��}�(hhhMhK'hKubh�ubhzNhs��input���output��ubaj�  Nj�  Nubjv  )��}�(hjy  hhMh]�hajy  hbhchdjy  hfNh|NhNh}Nh~NhK h�]�h�3/// Initializes all vector components individually
�����}�(hKhh)��}�(hhhM2hK)hKubh�ubah��3/// Initializes all vector components individually
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�(j�  )��}�(h�ValueTypeParam�hh�ix�����}�(hKhh)��}�(hhhM�hK*hKubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�ValueTypeParam�hh�iy�����}�(hKhh)��}�(hhhM�hK*hK2ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubjv  )��}�(hjy  hhMh]�hajy  hbhchdjy  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�hK-hKubhs�hh�T2�����}�(hKhh)��}�(hhhM�hK-hKubh�ubhzNh{Nubh �NontypeTemplateParam���)��}�(hh)��}�(hhhM�hK-hKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hK-hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�3/// Initializes components from another 2d vector.
�����}�(hKhh)��}�(hhhM�hK,hKubh�ubah��3/// Initializes components from another 2d vector.
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j�  )��}�(h�const Vec2<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM$hK-hKCubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hjy  hhMh]�hajy  hbhchdjy  hfhh)��}�hk]�j�  )��}�(hh)��}�(hhhM�hK0hKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hK0hKubh�ubhzNh�Int�h{Nubasbh|NhNh}Nh~NhK h�]�h�3/// Initializes components from another 2d vector.
�����}�(hKhh)��}�(hhhMDhK/hKubh�ubah��3/// Initializes components from another 2d vector.
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j�  )��}�(h�const Vec2<T, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hK0hK,ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hjy  hhMh]�hajy  hbhchdjy  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhMhK3hKubhs�hh�T2�����}�(hKhh)��}�(hhhMhK3hKubh�ubhzNh{Nubj�  )��}�(hh)��}�(hhhM"hK3hKubhs�hh�S2�����}�(hKhh)��}�(hhhM&hK3hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�N/// Initializes components from a 3d vector. The z-component of v is ignored.
�����}�(hKhh)��}�(hhhM�hK2hKubh�ubah��N/// Initializes components from a 3d vector. The z-component of v is ignored.
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j�  )��}�(h�const Vec3<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhMLhK3hKCubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hjy  hhMh]�hajy  hbhchdjy  hfNh|NhNh}Nh~NhK h�]�h�6/// Skips initialization of vector (for better speed)
�����}�(hKhh)��}�(hhhMlhK5hKubh�ubah��6/// Skips initialization of vector (for better speed)
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j�  )��}�(h�ENUM_DONT_INITIALIZE�hh�v�����}�(hKhh)��}�(hhhM�hK6hK%ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hjy  hhMh]�hajy  hbhchdjy  hfNh|NhNh}Nh~NhK h�]�(h��/// When STRIDE is not 1, we have to provide copy constructor and operator because the default ones would also copy the padding.
�����}�(hKhh)��}�(hhhM�hK8hKubh�ubh��/// When STRIDE is 1, we want to avoid to declare them (because then the type wouldn't be trivially copyable any longer), so we use DummyParamType for the parameter in that case.
�����}�(hKhh)��}�(hhhMQhK9hKubh�ubeh�X4  /// When STRIDE is not 1, we have to provide copy constructor and operator because the default ones would also copy the padding.
/// When STRIDE is 1, we want to avoid to declare them (because then the type wouldn't be trivially copyable any longer), so we use DummyParamType for the parameter in that case.
�h�}�h��h��j�  �j�  �j�  j�  j�  �hk]�j�  )��}�(h�Gconst typename std::conditional<STRIDE==1, DummyParamType, Vec2>::type&�hh�src�����}�(hKhh)��}�(hhhMchK:hK`ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�
operator =�����}�(hKhh)��}�(hhhM�	hKChKubh�ubhhMh]�haj}  hbhchd�function�hfNh|NhNh}Nh~NhK h�]�(h�/// Copies the source vector.
�����}�(hKhh)��}�(hhhM�hK?hKubh�ubh�)/// @param[in] src								Source vector.
�����}�(hKhh)��}�(hhhM	hK@hKubh�ubh�/// @return												*this.
�����}�(hKhh)��}�(hhhM0	hKAhKubh�ubeh��e/// Copies the source vector.
/// @param[in] src								Source vector.
/// @return												*this.
�h�}�h��h��j�  �j�  �j�  �Vec2&�j�  �hk]�j�  )��}�(h�Gconst typename std::conditional<STRIDE==1, DummyParamType, Vec2>::type&�hh�src�����}�(hKhh)��}�(hhhM
hKChK]ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator []�����}�(hKhh)��}�(hhhM�
hKKhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�p/// Accesses vector component: index 0 is 'x', index 1 is 'y'. All other values must not be used and will crash
�����}�(hKhh)��}�(hhhM=
hKJhKubh�ubah��p/// Accesses vector component: index 0 is 'x', index 1 is 'y'. All other values must not be used and will crash
�h�}�h��h��j�  �j�  �j�  �T&�j�  �hk]�j�  )��}�(h�Int�hh�l�����}�(hKhh)��}�(hhhM�
hKKhKubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator []�����}�(hKhh)��}�(hhhM�hKRhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�q/// Accesses vector component: index 0 is 'x', index 1 is 'y'.  All other values must not be used and will crash
�����}�(hKhh)��}�(hhhM	hKQhKubh�ubah��q/// Accesses vector component: index 0 is 'x', index 1 is 'y'.  All other values must not be used and will crash
�h�}�h��h��j�  �j�  �j�  �ValueTypeParam�j�  �hk]�j�  )��}�(h�Int�hh�l�����}�(hKhh)��}�(hhhM�hKRhK!ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator +=�����}�(hKhh)��}�(hhhM)hKYhK'ubh�ubhhMh]�haj�  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhMhKYhKubhs�hh�T2�����}�(hKhh)��}�(hhhMhKYhKubh�ubhzNh{Nubj�  )��}�(hh)��}�(hhhMhKYhKubhs�hh�S2�����}�(hKhh)��}�(hhhMhKYhKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�/// Adds two vectors
�����}�(hKhh)��}�(hhhM�hKXhKubh�ubah��/// Adds two vectors
�h�}�h��h��j�  �j�  �j�  �Vec2&�j�  �hk]�j�  )��}�(h�const Vec2<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhMIhKYhKGubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator +=�����}�(hKhh)��}�(hhhM^hKfhKubh�ubhhMh]�haj  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h�/// Adds a vector.
�����}�(hKhh)��}�(hhhM�hKahKubh�ubh��/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
�����}�(hKhh)��}�(hhhM�hKbhKubh�ubh�-/// @param[in] v									Vector to be added.
�����}�(hKhh)��}�(hhhM�hKchKubh�ubh�/// @return												*this.
�����}�(hKhh)��}�(hhhM�hKdhKubh�ubeh�X   /// Adds a vector.
/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
/// @param[in] v									Vector to be added.
/// @return												*this.
�h�}�h��h��j�  �j�  �j�  �Vec2&�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v�����}�(hKhh)��}�(hhhMvhKfhK ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator -=�����}�(hKhh)��}�(hhhM�hKnhK'ubh�ubhhMh]�hajE  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�hKnhKubhs�hh�T2�����}�(hKhh)��}�(hhhM�hKnhKubh�ubhzNh{Nubj�  )��}�(hh)��}�(hhhM�hKnhKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hKnhKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�/// Subtracts two vectors
�����}�(hKhh)��}�(hhhM�hKmhKubh�ubah��/// Subtracts two vectors
�h�}�h��h��j�  �j�  �j�  �Vec2&�j�  �hk]�j�  )��}�(h�const Vec2<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM	hKnhKGubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator -=�����}�(hKhh)��}�(hhhM3hK{hKubh�ubhhMh]�hajz  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h�/// Subtracts a vector.
�����}�(hKhh)��}�(hhhM�hKvhKubh�ubh��/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
�����}�(hKhh)��}�(hhhM�hKwhKubh�ubh�=/// @param[in] v									Vector to be substracted from this.
�����}�(hKhh)��}�(hhhMthKxhKubh�ubh�/// @return												*this.
�����}�(hKhh)��}�(hhhM�hKyhKubh�ubeh�X5  /// Subtracts a vector.
/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
/// @param[in] v									Vector to be substracted from this.
/// @return												*this.
�h�}�h��h��j�  �j�  �j�  �Vec2&�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v�����}�(hKhh)��}�(hhhMKhK{hK ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhM�hK�hK'ubh�ubhhMh]�haj�  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM�hK�hKubhs�hh�T2�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhzNh{Nubj�  )��}�(hh)��}�(hhhM�hK�hKubhs�hh�S2�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�*/// Multiplies two vectors component-wise
�����}�(hKhh)��}�(hhhM~hK�hKubh�ubah��*/// Multiplies two vectors component-wise
�h�}�h��h��j�  �j�  �j�  �Vec2&�j�  �hk]�j�  )��}�(h�const Vec2<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hK�hKGubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhM%hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h�+/// Multiplies with vector component-wise.
�����}�(hKhh)��}�(hhhM}hK�hKubh�ubh��/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubh�7/// @param[in] v									Vector to be multiplied with.
�����}�(hKhh)��}�(hhhMlhK�hKubh�ubh�/// @return												*this.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubeh�XB  /// Multiplies with vector component-wise.
/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector.
/// @param[in] v									Vector to be multiplied with.
/// @return												*this.
�h�}�h��h��j�  �j�  �j�  �Vec2&�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v�����}�(hKhh)��}�(hhhM=hK�hK ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhMphK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �Vec2&�j�  �hk]�j�  )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhM�hK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator /=�����}�(hKhh)��}�(hhhMOhK�hKubh�ubhhMh]�haj*  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�V/// Divides each vector component by a scalar. The passed argument is checked for 0.0
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��V/// Divides each vector component by a scalar. The passed argument is checked for 0.0
�h�}�h��h��j�  �j�  �j�  �Vec2&�j�  �hk]�j�  )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhMjhK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�hajG  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�(j�  )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhMhK�hK-ubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Vec2&�hh�v�����}�(hKhh)��}�(hhhMhK�hK<ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubjv  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�hajs  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhMMhK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhM�hK�hK&ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhMnhK�hKhubh�ubhhMh]�haj�  hbhchdj�  hfhh)��}�hk]�hn)��}�(hh)��}�(hhhMhK�hKubhs�hh�S�����}�(hKhh)��}�(hhhMhK�hKubh�ubhzNh{Nubasbh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �OVec2<typename MultiplicativePromotion<T, S, std::is_scalar<S>::value>::type, 1>�j�  �hk]�j�  )��}�(h�S�hh�s�����}�(hKhh)��}�(hhhM{hK�hKuubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�
operator /�����}�(hKhh)��}�(hhhM7hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�R/// Divides each vector component by a scalar. The scalar value is tested for 0.0
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��R/// Divides each vector component by a scalar. The scalar value is tested for 0.0
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�ValueTypeParam�hh�s�����}�(hKhh)��}�(hhhMQhK�hK&ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�*/// Multiplies two vectors component-wise
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah��*/// Multiplies two vectors component-wise
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v�����}�(hKhh)��}�(hhhM�hK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�
operator +�����}�(hKhh)��}�(hhhM>hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�/// Adds two vectors
�����}�(hKhh)��}�(hhhMhK�hKubh�ubah��/// Adds two vectors
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v�����}�(hKhh)��}�(hhhMUhK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�
operator -�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h� /// Subtracts vector v2 from v1
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubah�� /// Subtracts vector v2 from v1
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v�����}�(hKhh)��}�(hhhM�hK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�
operator -�����}�(hKhh)��}�(hhhM%hK�hKubh�ubhhMh]�haj.  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�/// Negates vector v
�����}�(hKhh)��}�(hhhMhK�hKubh�ubah��/// Negates vector v
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�operator ==�����}�(hKhh)��}�(hhhM�hK�hK*ubh�ubhhMh]�hajB  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhMlhK�hKubhs�hh�T2�����}�(hKhh)��}�(hhhMuhK�hKubh�ubhzNh{Nubj�  )��}�(hh)��}�(hhhMyhK�hKubhs�hh�S2�����}�(hKhh)��}�(hhhM}hK�hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�(h�/// Equality operator.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubh��/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubh�,/// @param[in] v									Comparison vector.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubh�F/// @return												True if this and v are equal, otherwise false.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubeh�XJ  /// Equality operator.
/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector
/// @param[in] v									Comparison vector.
/// @return												True if this and v are equal, otherwise false.
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  )��}�(h�const Vec2<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM�hK�hKJubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator ==�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h�/// Equality operator.
�����}�(hKhh)��}�(hhhM6hK�hKubh�ubh��/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector
�����}�(hKhh)��}�(hhhMNhK�hKubh�ubh�,/// @param[in] v									Comparison vector.
�����}�(hKhh)��}�(hhhMhK�hKubh�ubh�F/// @return												True if this and v are equal, otherwise false.
�����}�(hKhh)��}�(hhhM=hK�hKubh�ubeh�XJ  /// Equality operator.
/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector
/// @param[in] v									Comparison vector.
/// @return												True if this and v are equal, otherwise false.
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v�����}�(hKhh)��}�(hhhMhK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator !=�����}�(hKhh)��}�(hhhM� hK�hK*ubh�ubhhMh]�haj�  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM� hK�hKubhs�hh�T2�����}�(hKhh)��}�(hhhM� hK�hKubh�ubhzNh{Nubj�  )��}�(hh)��}�(hhhM� hK�hKubhs�hh�S2�����}�(hKhh)��}�(hhhM� hK�hKubh�ubhzNh�Int�h{Nubesbh|NhNh}Nh~NhK h�]�(h�/// Inequality operator.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubh�,/// @param[in] v									Comparison vector.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubh�F/// @return												False if this and v are equal, otherwise true.
�����}�(hKhh)��}�(hhhM�hK�hKubh�ubeh���/// Inequality operator.
/// @param[in] v									Comparison vector.
/// @return												False if this and v are equal, otherwise true.
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  )��}�(h�const Vec2<T2, S2>&�hh�v�����}�(hKhh)��}�(hhhM� hK�hKJubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator !=�����}�(hKhh)��}�(hhhM#hK�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h�/// Inequality operator.
�����}�(hKhh)��}�(hhhMN!hK�hKubh�ubh��/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector
�����}�(hKhh)��}�(hhhMh!hK�hKubh�ubh�,/// @param[in] v									Comparison vector.
�����}�(hKhh)��}�(hhhM*"hK�hKubh�ubh�F/// @return												False if this and v are equal, otherwise true.
�����}�(hKhh)��}�(hhhMW"hK�hKubh�ubeh�XL  /// Inequality operator.
/// We repeat the function template as non-template function, this allows the usage in contexts where the parameter is not a vector itself, but something with a conversion operator to a vector
/// @param[in] v									Comparison vector.
/// @return												False if this and v are equal, otherwise true.
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v�����}�(hKhh)��}�(hhhM#hK�hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�LessThanOrEqual�����}�(hKhh)��}�(hhhM$hMhKubh�ubhhMh]�haj(  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v�����}�(hKhh)��}�(hhhM-$hMhK(ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�LessThan�����}�(hKhh)��}�(hhhM%hMhKubh�ubhhMh]�haj>  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v�����}�(hKhh)��}�(hhhM)%hMhK ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�GetHashCode�����}�(hKhh)��}�(hhhM�&hMhKubh�ubhhMh]�hajT  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h�N/// Returns the hash code of the vector (used for hash maps and comparisons).
�����}�(hKhh)��}�(hhhM�%hMhKubh�ubh�//// @return												The vector's hash code.
�����}�(hKhh)��}�(hhhM&hMhKubh�ubeh��}/// Returns the hash code of the vector (used for hash maps and comparisons).
/// @return												The vector's hash code.
�h�}�h��h��j�  �j�  �j�  �UInt�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�IsEqual�����}�(hKhh)��}�(hhhM'hMhKubh�ubhhMh]�hajn  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�G/// Tests component-wise if the difference is no bigger than 'epsilon'
�����}�(hKhh)��}�(hhhM�&hMhKubh�ubah��G/// Tests component-wise if the difference is no bigger than 'epsilon'
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�(j�  )��}�(h�const Vec2&�hh�other�����}�(hKhh)��}�(hhhM3'hMhKubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�ValueTypeParam�hh�epsilon�����}�(hKhh)��}�(hhhMI'hMhK5ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubjv  )��}�(hh�Dot�����}�(hKhh)��}�(hhhM�'hM$hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhM�'hM$hKubh�ubhNh}Nh~NhK h�]�h�(/// Calculates dot product of v1 and v2
�����}�(hKhh)��}�(hhhM�'hM#hKubh�ubah��(/// Calculates dot product of v1 and v2
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�(j�  )��}�(h�const Vec2&�hh�v1�����}�(hKhh)��}�(hhhM�'hM$hKubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Vec2&�hh�v2�����}�(hKhh)��}�(hhhM�'hM$hK+ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubjv  )��}�(hh�Abs�����}�(hKhh)��}�(hhhM�)hM.hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhM�)hM.hKubh�ubhNh}Nh~NhK h�]�(h�:/// returns the vector with absolute value for each entry
�����}�(hKhh)��}�(hhhM�(hM*hKubh�ubh�2/// @param[in] v1									input vector to work on
�����}�(hKhh)��}�(hhhM�(hM+hKubh�ubh�L/// @return												component wise absolute value vector of input vector
�����}�(hKhh)��}�(hhhM�(hM,hKubh�ubeh���/// returns the vector with absolute value for each entry
/// @param[in] v1									input vector to work on
/// @return												component wise absolute value vector of input vector
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v1�����}�(hKhh)��}�(hhhM�)hM.hK#ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�Dot�����}�(hKhh)��}�(hhhMn*hM4hKVubh�ubhhMh]�haj�  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM$*hM4hKubhs�hh�T2�����}�(hKhh)��}�(hhhM-*hM4hKubh�ubhzNh{Nubj�  )��}�(hh)��}�(hhhM1*hM4hKubhs�hh�S2�����}�(hKhh)��}�(hhhM5*hM4hKubh�ubhzNh�Int�h{Nubesbh|h�friend�����}�(hKhh)��}�(hhhM9*hM4hK!ubh�ubhNh}Nh~NhK h�]�h�(/// Calculates dot product of v1 and v2
�����}�(hKhh)��}�(hhhM�)hM3hKubh�ubah��(/// Calculates dot product of v1 and v2
�h�}�h��h��j�  �j�  �j�  �-typename MultiplicativePromotion<T, T2>::type�j�  �hk]�(j�  )��}�(h�const Vec2&�hh�v1�����}�(hKhh)��}�(hhhM~*hM4hKfubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Vec2<T2, S2>&�hh�v2�����}�(hKhh)��}�(hhhM�*hM4hK~ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubjv  )��}�(hh�IsZero�����}�(hKhh)��}�(hhhM�*hM:hKubh�ubhhMh]�haj3  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�&/// Checks if each component is zero.
�����}�(hKhh)��}�(hhhM�*hM9hKubh�ubah��&/// Checks if each component is zero.
�h�}�h��h��j�  �j�  �j�  �BoolType�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�SetZero�����}�(hKhh)��}�(hhhMU+hM@hKubh�ubhhMh]�hajG  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�!/// Sets all components to zero.
�����}�(hKhh)��}�(hhhM.+hM?hKubh�ubah��!/// Sets all components to zero.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�
GetAverage�����}�(hKhh)��}�(hhhM�+hMFhKubh�ubhhMh]�haj[  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�5/// Calculates the average value of 'x', 'y' and 'z'
�����}�(hKhh)��}�(hhhMw+hMEhKubh�ubah��5/// Calculates the average value of 'x', 'y' and 'z'
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�GetSum�����}�(hKhh)��}�(hhhM,hMLhKubh�ubhhMh]�hajo  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�+/// Calculates the sum of 'x', 'y' and 'z'
�����}�(hKhh)��}�(hhhM�+hMKhKubh�ubah��+/// Calculates the sum of 'x', 'y' and 'z'
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�Min�����}�(hKhh)��}�(hhhMz,hMRhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhMi,hMRhKubh�ubhNh}Nh~NhK h�]�h�./// Calculates the minimum of each component.
�����}�(hKhh)��}�(hhhM:,hMQhKubh�ubah��./// Calculates the minimum of each component.
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�(j�  )��}�(h�const Vec2&�hh�a�����}�(hKhh)��}�(hhhM�,hMRhK#ubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Vec2&�hh�other�����}�(hKhh)��}�(hhhM�,hMRhK2ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubjv  )��}�(hh�Max�����}�(hKhh)��}�(hhhM;-hMXhKubh�ubhhMh]�haj�  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhM*-hMXhKubh�ubhNh}Nh~NhK h�]�h�./// Calculates the maximum of each component.
�����}�(hKhh)��}�(hhhM�,hMWhKubh�ubah��./// Calculates the maximum of each component.
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�(j�  )��}�(h�const Vec2&�hh�a�����}�(hKhh)��}�(hhhMK-hMXhK#ubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Vec2&�hh�other�����}�(hKhh)��}�(hhhMZ-hMXhK2ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubjv  )��}�(hh�ClampMin�����}�(hKhh)��}�(hhhM�-hM^hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�'/// Set the minimum of each component.
�����}�(hKhh)��}�(hhhM�-hM]hKubh�ubah��'/// Set the minimum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j�  )��}�(h�const Vec2&�hh�other�����}�(hKhh)��}�(hhhM�-hM^hKubh�ubhz�Vec2()�hs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�ClampMax�����}�(hKhh)��}�(hhhM}.hMehKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�'/// Set the maximum of each component.
�����}�(hKhh)��}�(hhhMP.hMdhKubh�ubah��'/// Set the maximum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j�  )��}�(h�const Vec2&�hh�other�����}�(hKhh)��}�(hhhM�.hMehKubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�SetMin�����}�(hKhh)��}�(hhhM/hMlhKubh�ubhhMh]�haj  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhM/hMlhKubh�ubhNh}Nh~NhK h�]�h�'/// Set the minimum of each component.
�����}�(hKhh)��}�(hhhM�.hMkhKubh�ubah��'/// Set the minimum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�(j�  )��}�(h�Vec2&�hh�a�����}�(hKhh)��}�(hhhM/hMlhKubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Vec2&�hh�other�����}�(hKhh)��}�(hhhM+/hMlhK*ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubjv  )��}�(hh�SetMax�����}�(hKhh)��}�(hhhM�/hMrhKubh�ubhhMh]�hajB  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhMw/hMrhKubh�ubhNh}Nh~NhK h�]�h�'/// Set the maximum of each component.
�����}�(hKhh)��}�(hhhMO/hMqhKubh�ubah��'/// Set the maximum of each component.
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�(j�  )��}�(h�Vec2&�hh�a�����}�(hKhh)��}�(hhhM�/hMrhKubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Vec2&�hh�other�����}�(hKhh)��}�(hhhM�/hMrhK*ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubjv  )��}�(hh�Clamp01�����}�(hKhh)��}�(hhhM0hMxhKubh�ubhhMh]�hajn  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�?/// Returns a vector that is clamped to the range [0.0 .. 1.0]
�����}�(hKhh)��}�(hhhM�/hMwhKubh�ubah��?/// Returns a vector that is clamped to the range [0.0 .. 1.0]
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�	GetLength�����}�(hKhh)��}�(hhhM�0hM~hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�%/// Returns the length of the vector
�����}�(hKhh)��}�(hhhM_0hM}hKubh�ubah��%/// Returns the length of the vector
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�GetSquaredLength�����}�(hKhh)��}�(hhhM�0hM�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�-/// Returns the squared length of the vector
�����}�(hKhh)��}�(hhhM�0hM�hKubh�ubah��-/// Returns the squared length of the vector
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�GetNormalized�����}�(hKhh)��}�(hhhMs1hM�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�@/// Returns a normalized vector, so that GetLength(vector)==1.0
�����}�(hKhh)��}�(hhhM(1hM�hKubh�ubah��@/// Returns a normalized vector, so that GetLength(vector)==1.0
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�
operator !�����}�(hKhh)��}�(hhhM'2hM�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�@/// Returns a normalized vector, so that GetLength(vector)==1.0
�����}�(hKhh)��}�(hhhM�1hM�hKubh�ubah��@/// Returns a normalized vector, so that GetLength(vector)==1.0
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�	Normalize�����}�(hKhh)��}�(hhhM�2hM�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�5/// Normalizes this vector, so that GetLength()==1.0
�����}�(hKhh)��}�(hhhM�2hM�hKubh�ubah��5/// Normalizes this vector, so that GetLength()==1.0
�h�}�h��h��j�  �j�  �j�  �void�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�GetAngle�����}�(hKhh)��}�(hhhMW3hM�hKubh�ubhhMh]�haj�  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhMN3hM�hKubh�ubhNh}Nh~NhK h�]�h�4/// Calculates angle (in radians) between v1 and v2
�����}�(hKhh)��}�(hhhM3hM�hKubh�ubah��4/// Calculates angle (in radians) between v1 and v2
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�(j�  )��}�(h�const Vec2&�hh�v1�����}�(hKhh)��}�(hhhMl3hM�hK ubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Vec2&�hh�v2�����}�(hKhh)��}�(hhhM|3hM�hK0ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubjv  )��}�(hh�ToString�����}�(hKhh)��}�(hhhMw5hM�hK	ubh�ubhhMh]�haj	  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h�./// Returns a readable string of the content.
�����}�(hKhh)��}�(hhhML4hM�hKubh�ubh�j/// @param[in] formatStatement		Nullptr or additional formatting instruction. See also @ref format_float.
�����}�(hKhh)��}�(hhhM{4hM�hKubh�ubh�-/// @return												The converted result.
�����}�(hKhh)��}�(hhhM�4hM�hKubh�ubeh���/// Returns a readable string of the content.
/// @param[in] formatStatement		Nullptr or additional formatting instruction. See also @ref format_float.
/// @return												The converted result.
�h�}�h��h��j�  �j�  �j�  �String�j�  �hk]�j�  )��}�(h�const FormatStatement*�hh�formatStatement�����}�(hKhh)��}�(hhhM�5hM�hK)ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�Cross�����}�(hKhh)��}�(hhhM�6hM�hKubh�ubhhMh]�haj;	  hbhchdj�  hfNh|h�friend�����}�(hKhh)��}�(hhhM�6hM�hKubh�ubhNh}Nh~NhK h�]�h�y/// Calculates the cross product of a 2d vector. This is the vector (Y, -X), i.e., the clockwise rotation by 90 degrees.
�����}�(hKhh)��}�(hhhM"6hM�hKubh�ubah��y/// Calculates the cross product of a 2d vector. This is the vector (Y, -X), i.e., the clockwise rotation by 90 degrees.
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�const Vec2&�hh�v1�����}�(hKhh)��}�(hhhM�6hM�hK%ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�GetMin�����}�(hKhh)��}�(hhhM7hM�hKubh�ubhhMh]�haj^	  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�'/// Returns the minimum of 'x' and 'y'
�����}�(hKhh)��}�(hhhM�6hM�hKubh�ubah��'/// Returns the minimum of 'x' and 'y'
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�GetMax�����}�(hKhh)��}�(hhhMn7hM�hKubh�ubhhMh]�hajr	  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�h�'/// Returns the maximum of 'x' and 'y'
�����}�(hKhh)��}�(hhhMD7hM�hKubh�ubah��'/// Returns the maximum of 'x' and 'y'
�h�}�h��h��j�  �j�  �j�  �T�j�  �hk]�j�  Nj�  Nubjv  )��}�(hh�GetRightRotated�����}�(hKhh)��}�(hhhM�9hM�hKubh�ubhhMh]�haj�	  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h�u/// Returns a vector where the components have been rotated to the right (in the usual (x, y)-representation). E.g.,
�����}�(hKhh)��}�(hhhM�7hM�hKubh�ubh�;/// with a value of 1 for rots, the result will be (y, x).
�����}�(hKhh)��}�(hhhMn8hM�hKubh�ubh�q/// @param[in] rots								Number of rotations, may be negative. The result depends only on the number modulo 2.
�����}�(hKhh)��}�(hhhM�8hM�hKubh�ubh�7/// @return												Vector with rotated components.
�����}�(hKhh)��}�(hhhM9hM�hKubh�ubeh�XX  /// Returns a vector where the components have been rotated to the right (in the usual (x, y)-representation). E.g.,
/// with a value of 1 for rots, the result will be (y, x).
/// @param[in] rots								Number of rotations, may be negative. The result depends only on the number modulo 2.
/// @return												Vector with rotated components.
�h�}�h��h��j�  �j�  �j�  �	Unstrided�j�  �hk]�j�  )��}�(h�Int�hh�rots�����}�(hKhh)��}�(hhhM�9hM�hK ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�operator *=�����}�(hKhh)��}�(hhhM�:hM�hKubh�ubhhMh]�haj�	  hbhchdj�  hfhh)��}�hk]�hn)��}�(hh)��}�(hhhM�:hM�hKubhs�hh�T2�����}�(hKhh)��}�(hhhM�:hM�hKubh�ubhzNh{Nubasbh|NhNh}Nh~NhK h�]�h�!/// Transforms point by a matrix
�����}�(hKhh)��}�(hhhMY:hM�hKubh�ubah��!/// Transforms point by a matrix
�h�}�h��h��j�  �j�  �j�  �Vec2&�j�  �hk]�j�  )��}�(h�const Mat2<T2>&�hh�m�����}�(hKhh)��}�(hhhM�:hM�hK;ubh�ubhzNhs�j�  �j�  �ubaj�  Nj�  Nubjv  )��}�(hh�	NullValue�����}�(hKhh)��}�(hhhM�<hM�hKubh�ubhhMh]�haj�	  hbhchdj�  hfNh|NhNh}Nh~NhK h�]�(h�K/// Returns a null value of the vector (see nullvalue.h for more details).
�����}�(hKhh)��}�(hhhM�;hM�hKubh�ubh�3/// @return												A null value of the vector.
�����}�(hKhh)��}�(hhhM�;hM�hKubh�ubeh��~/// Returns a null value of the vector (see nullvalue.h for more details).
/// @return												A null value of the vector.
�h�}�h��h��j�  �j�  �j�  �const Vec2&�j�  �hk]�j�  Nj�  NubehahQhbhchdj,  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM(hKhKubhs�hh�T�����}�(hKhh)��}�(hhhM1hKhKubh�ubhzNh{Nubj�  )��}�(hh)��}�(hhhM4hKhKubhs�hh�STRIDE�����}�(hKhh)��}�(hhhM8hKhKubh�ubhz�1�h�Int�h{Nubesbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]�j0  Nj1  Nh��j2  Nj3  Nj4  �j5  �j6  �j7  �j8  �j9  �j:  �j;  �j<  Nj=  �j>  �j?  ]�jA  ]�jC  }�ubh)��}�(hNhh0h]�h h�#ifndef STRIDE�����}�(hK
hh)��}�(hhhM�<hM�hKubh�ububjv  )��}�(hh�
operator *�����}�(hKhh)��}�(hhhM�=hM�hK�ubh�ubhh0h]�haj!
  hbhchdj�  hfhh)��}�hk]�(hn)��}�(hh)��}�(hhhM=hM�hKubhs�hh�T�����}�(hKhh)��}�(hhhM=hM�hKubh�ubhzNh{Nubj�  )��}�(hh)��}�(hhhM =hM�hKubhs�hh�STR�����}�(hKhh)��}�(hhhM$=hM�hKubh�ubhzNh�Int�h{Nubhn)��}�(hh)��}�(hhhM)=hM�hK ubhs�hh�S�����}�(hKhh)��}�(hhhM2=hM�hK)ubh�ubhzNh{Nubesbh|NhNh}Nh~NhK h�]�h�1/// Multiplies each vector component by a scalar
�����}�(hKhh)��}�(hhhM�<hM�hKubh�ubah��1/// Multiplies each vector component by a scalar
�h�}�h��h��j�  �j�  �j�  �OVec2<typename MultiplicativePromotion<T, S, std::is_scalar<S>::value>::type, 1>�j�  �hk]�(j�  )��}�(h�S�hh�s�����}�(hKhh)��}�(hhhM�=hM�hK�ubh�ubhzNhs�j�  �j�  �ubj�  )��}�(h�const Vec2<T, STR>&�hh�v�����}�(hKhh)��}�(hhhM�=hM�hK�ubh�ubhzNhs�j�  �j�  �ubej�  Nj�  Nubjv  )��}�(hh�PrivateGetDataType�����}�(hKhh)��}�(hhhMS>hM�hKKubh�ubhh0h]�haji
  hbhchdj�  hfhh)��}�hk]�(j�  )��}�(hh)��}�(hhhM>hM�hKubhs�hh�POLICY�����}�(hKhh)��}�(hhhM'>hM�hKubh�ubhzNh�GET_DATATYPE_POLICY�h{Nubhn)��}�(hh)��}�(hhhM/>hM�hK'ubhs�hh�T�����}�(hKhh)��}�(hhhM8>hM�hK0ubh�ubhzNh{Nubesbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h��j�  �j�  �j�  �Result<DataType>�j�  �hk]�(j�  )��}�(h�Vec2<T, 1>**�h�anonymous_param_1�hzNhs�j�  �j�  �ubj�  )��}�(h�OverloadRank0�h�anonymous_param_2�hzNhs�j�  �j�  �ubej�  Nj�  �DataType�ubhL)��}�(h�IsZeroInitialized<Vec2<T,1>>�hh0h]�hah�IsZeroInitialized�����}�(hKhh)��}�(hhhMy?hM�hKubh�ubhbhchdj,  hfhh)��}�hk]�hn)��}�(hh)��}�(hhhMf?hM�hKubhs�hh�T�����}�(hKhh)��}�(hhhMo?hM�hKubh�ubhzNh{Nubasbh|NhNh}Nh~NhK h�]�h�h	h�}�h��h�]��IsZeroInitialized<T>�h�public�����}�(hKhh)��}�(hhhM�?hM�hK>ubh�ubh	��aj0  Nj1  Nh��j2  Nj3  Nj4  �j5  �j6  �j7  �j8  �j9  �j:  �j;  �j<  Nj=  �j>  �j?  ]�jA  ]�jC  }�ubh)��}�(hNhh0h]�h h�#endif�����}�(hK
hh)��}�(hhhM�?hM�hKubh�ububehah4hbhchd�	namespace�hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h���preprocessorConditions�]��root�hh N�containsResourceId���registry���usings����minIndentation�K �maxIndentation�K�firstMember��ubehahhbhchdj�
  hfNh|NhNh}Nh~NhK h�]�h�h	h�}�h��j�
  ]�j�
  hh ]�(hh'h0h9hBhMj
  j
  je
  j�
  j�
  ej�
  �j�
  �j�
  ���hxx1�N�hxx2�N�snippets�}�j�
  K j�
  K j�
  �ub.