���      �declarations��	Namespace���)��}�(�name��lexer��Token���� �����}�(�type�K�pos�h�SourcePosition���)��}�(�file��OC:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\cpuyield.h��index�K �line�KhKub�escaped��ub�owner�N�children�]�(h �	Directive���)��}�(hNhhh]��code�h�#if 1�����}�(hK
hh)��}�(hhhK hKhKubh�ububh �Include���)��}�(h�maxon/apibase.h�hhh]��quote��"��template�Nubh)��}�(hNhhh]�h h�!#if defined(MAXON_TARGET_WINDOWS)�����}�(hK
hh)��}�(hhhKGhKhKubh�ububh()��}�(h�intrin.h�hhh]�h-�<�h/Nubh)��}�(hNhhh]�h h�%#elif defined(MAXON_TARGET_CPU_INTEL)�����}�(hK
hh)��}�(hhhK~hKhKubh�ububh()��}�(h�xmmintrin.h�hhh]�h-h=h/Nubh)��}�(hNhhh]�h h�#endif�����}�(hK
hh)��}�(hhhK�hK
hKubh�ububh)��}�(hh�maxon�����}�(hKhh)��}�(hhhK�hKhKubh�ubhhh]�(h �Class���)��}�(hh�CpuYieldState�����}�(hKhh)��}�(hhhK�hKhKubh�ubhhTh]�(h �Variable���)��}�(hh�LOOPS_START_COUNT�����}�(hKhh)��}�(hhhM�hK.hKubh�ubhh_h]��
simpleName�hn�access�h�public�����}�(hKhh)��}�(hhhM�hK-hKubh�ub�kind��variable�h/N�friend�Nh�	const Int��id�N�point�N�
artificial�K �doclist�]��doc�h	�annotations�}��	anonymous���static��ubh)��}�(hNhh_h]�h h�#ifdef	MAXON_TARGET_WINDOWS�����}�(hK
hh)��}�(hhhM�hK0hKubh�ububhi)��}�(hh�LOOPS_MAX_GRANULARITY�����}�(hKhh)��}�(hhhM�hK2hKubh�ubhh_h]�hsh�hthwh{h|h/Nh}Nh�	const Int�hNh�Nh�K h�]�h�h	h�}�h��h��ubhi)��}�(hh�LOOPS_BEFORE_YIELD�����}�(hKhh)��}�(hhhM�	hK3hKubh�ubhh_h]�hsh�hthwh{h|h/Nh}Nh�	const Int�hNh�Nh�K h�]�h�h	h�}�h��h��ubhi)��}�(hh�LOOPS_BEFORE_SLEEP�����}�(hKhh)��}�(hhhM%
hK4hKubh�ubhh_h]�hsh�hthwh{h|h/Nh}Nh�	const Int�hNh�Nh�K h�]�h�h	h�}�h��h��ubh)��}�(hNhh_h]�h h�#else�����}�(hK
hh)��}�(hhhM
hK6hKubh�ububhi)��}�(hh�LOOPS_MAX_GRANULARITY�����}�(hKhh)��}�(hhhM�
hK8hKubh�ubhh_h]�hsh�hthwh{h|h/Nh}Nh�	const Int�hNh�Nh�K h�]�h�h	h�}�h��h��ubhi)��}�(hh�LOOPS_BEFORE_YIELD�����}�(hKhh)��}�(hhhM�
hK9hKubh�ubhh_h]�hsh�hthwh{h|h/Nh}Nh�	const Int�hNh�Nh�K h�]�h�h	h�}�h��h��ubhi)��}�(hh�LOOPS_BEFORE_SLEEP�����}�(hKhh)��}�(hhhMghK:hKubh�ubhh_h]�hsh�hthwh{h|h/Nh}Nh�	const Int�hNh�Nh�K h�]�h�h	h�}�h��h��ubh)��}�(hNhh_h]�h h�#endif�����}�(hK
hh)��}�(hhhM�hK<hKubh�ububhi)��}�(hh�LOCK_ACQUIRE�����}�(hKhh)��}�(hhhMhK?hKubh�ubhh_h]�hsh�hthwh{h|h/Nh}Nh�
const UInt�hNh�Nh�K h�]�h�h	h�}�h��h��ubhi)��}�(hh�	LOCK_SPIN�����}�(hKhh)��}�(hhhM*hK@hKubh�ubhh_h]�hsh�hthwh{h|h/Nh}Nh�
const UInt�hNh�Nh�K h�]�h�h	h�}�h��h��ubhi)��}�(hh�LOCK_RELEASE�����}�(hKhh)��}�(hhhMMhKAhKubh�ubhh_h]�hsj  hthwh{h|h/Nh}Nh�
const UInt�hNh�Nh�K h�]�h�h	h�}�h��h��ubhi)��}�(hh�MAX_STATE_ENUM�����}�(hKhh)��}�(hhhMshKBhKubh�ubhh_h]�hsj  hthwh{h|h/Nh}Nh�
const UInt�hNh�Nh�K h�]�h�h	h�}�h��h��ubh �	TypeAlias���)��}�(hh�SwitchDelegate�����}�(hKhh)��}�(hhhM�hKEhKubh�ubhh_h]�hsj"  hthwh{�	typealias�h/Nh}NhNhNh�Nh�K h�]�h�h	h�}�h���bases�]��0void(*)(CpuYieldState*state,const void*resource)��public�h	��aubhi)��}�(hh�_count�����}�(hKhh)��}�(hhhM<hKGhKubh�ubhh_h]�hsj3  hthwh{h|h/Nh}Nh�Int�hNh�Nh�K h�]�h�h	h�}�h��h��ubhi)��}�(hh�	_loopSize�����}�(hKhh)��}�(hhhMIhKHhKubh�ubhh_h]�hsj?  hthwh{h|h/Nh}Nh�Int�hNh�Nh�K h�]�h�h	h�}�h��h��ubehshchtj-  h{�class�h/Nh}NhNhNh�Nh�K h�]�h�h	h�}�h��j*  ]��	interface�N�refKind�Nh���refClass�N�baseInterfaces�N�derived���isError���implementation���	component���finalComponent���forward���
singleImpl���hasStaticMethods���generic�N�refClassForwardDeclared���missingInterfaces���ambiguousCalls�]��	selfCalls�]��methodNames�}�ubhi)��}�(hh�g_CpuYieldDelegate�����}�(hKhh)��}�(hhhM�hKMhKEubh�ubhhTh]�hsjd  htj-  h{h|h/Nh}Nh�CpuYieldState::SwitchDelegate�hNh�Nh�K h�]�h�h	h�}�h��h��ubh^)��}�(hh�CpuYield�����}�(hKhh)��}�(hhhM;hKPhKubh�ubhhTh]�(h �Function���)��}�(h�constructor�hjl  h]�hsjy  hth�public�����}�(hKhh)��}�(hhhM`hKRhKubh�ubh{jy  h/Nh}NhNhNh�Nh�K h�]�h�h	h�}�h��h���explicit���deleted���retType��void��const���params�]��
observable�N�result�Nubjv  )��}�(hh�Reset�����}�(hKhh)��}�(hhhM�hKYhKubh�ubhjl  h]�hsj�  htj}  h{�function�h/Nh}NhNhNh�Nh�K h�]�h�h	h�}�h��h��j�  �j�  �j�  �void�j�  �j�  ]�j�  Nj�  Nubjv  )��}�(hh�Pause�����}�(hKhh)��}�(hhhMOhKfhKubh�ubhjl  h]�hsj�  htj}  h{j�  h/Nh}NhNhNh�Nh�K h�]�(h�Z/// Pauses a little while until the contended resource hopefully becomes available again.
�����}�(hKhh)��}�(hhhMKhK`hKubh�ubh�W/// Depending on the number of calls this will either just do a light spin loop or it 
�����}�(hKhh)��}�(hhhM�hKahKubh�ubh�]/// might put the thread to sleep. Furthermore offending threads might be logged to diagnose
�����}�(hKhh)��}�(hhhM�hKbhKubh�ubh�"/// deadlocks or bad performance.
�����}�(hKhh)��}�(hhhM\hKchKubh�ubh�n/// @param[in] res								The contended resource because of which Pause has to be called. Might be a nullptr.
�����}�(hKhh)��}�(hhhMhKdhKubh�ubeh�X�  /// Pauses a little while until the contended resource hopefully becomes available again.
/// Depending on the number of calls this will either just do a light spin loop or it 
/// might put the thread to sleep. Furthermore offending threads might be logged to diagnose
/// deadlocks or bad performance.
/// @param[in] res								The contended resource because of which Pause has to be called. Might be a nullptr.
�h�}�h��h��j�  �j�  �j�  �void�j�  �j�  ]�h �	Parameter���)��}�(h�const void*�hh�res�����}�(hKhh)��}�(hhhMahKfhKubh�ub�default��nullptr��pack���input���output��ubaj�  Nj�  Nubjv  )��}�(hh�Wait�����}�(hKhh)��}�(hhhM�hK|hKubh�ubhjl  h]�hsj�  htj}  h{j�  h/Nh}NhNhNh�Nh�K h�]�h�h	h�}�h��h��j�  �j�  �j�  �void�j�  �j�  ]�j�  )��}�(h�Int�hh�cnt�����}�(hKhh)��}�(hhhM�hK|hKubh�ubj�  Nj�  �j�  �j�  �ubaj�  Nj�  Nubh)��}�(hNhjl  h]�h h�#ifndef MAXON_TARGET_CPU_INTEL�����}�(hK
hh)��}�(hhhMKhK�hKubh�ububjv  )��}�(hh�	_mm_pause�����}�(hKhh)��}�(hhhM�hK�hKubh�ubhjl  h]�hsj�  hth�private�����}�(hKhh)��}�(hhhMAhK�hKubh�ubh{j�  h/Nh}NhNhNh�Nh�K h�]�h�h	h�}�h��h��j�  �j�  �j�  �void�j�  �j�  ]�j�  Nj�  Nubh)��}�(hNhjl  h]�h h�#endif�����}�(hK
hh)��}�(hhhM�hK�hKubh�ububehsjp  htj-  h{jG  h/Nh}NhNhNh�Nh�K h�]�h�h	h�}�h��j*  ]��CpuYieldState�h�	protected�����}�(hKhh)��}�(hhhMFhKPhKubh�ubh	��ajK  NjL  Nh��jM  NjN  NjO  �jP  �jQ  �jR  �jS  �jT  �jU  �jV  �jW  NjX  �jY  �jZ  ]�j\  ]�j^  }�ubehshXhtj-  h{�	namespace�h/Nh}NhNhNh�Nh�K h�]�h�h	h�}�h���preprocessorConditions�]��root�hh N�containsResourceId���registry���usings����minIndentation�K �maxIndentation�K �firstMember��ubh)��}�(hNhhh]�h h�#endif�����}�(hK
hh)��}�(hhhMhK�hKubh�ububehshhtj-  h{j  h/Nh}NhNhNh�Nh�K h�]�h�h	h�}�h��j"  ]�j$  hh ]�(hh)h0h9h>hGhKhTh_j`  jl  j,  ej%  �j&  �j'  ���hxx1�N�hxx2�N�snippets�}�j)  K j*  K j+  �ub.