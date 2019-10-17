��$      �declarations��	Namespace���)��}�(�name��lexer��Token���� �����}�(�type�K�pos�h�SourcePosition���)��}�(�file��TC:\dev\Cinema-4D-Source-Tools\frameworks\core.framework\source\maxon\iostream_pipe.h��index�K �line�KhKub�escaped��ub�owner�N�children�]�(h �	Directive���)��}�(hNhhh]��code�h�#if 1�����}�(hK
hh)��}�(hhhK hKhKubh�ububh �Include���)��}�(h�maxon/iostreams.h�hhh]��quote��"��template�Nubh)��}�(hh�maxon�����}�(hKhh)��}�(hhhK_hKhKubh�ubhhh]�(h)��}�(hh�URLFLAGS�����}�(hKhh)��}�(hhhM�hKhKubh�ubhh0h]�h �	Attribute���)��}�(hh�PIPE_CREATE�����}�(hKhh)��}�(hhhM�hKhKubh�ubhh9h]��
simpleName�hH�access��public��kind�h�MAXON_ATTRIBUTE�����}�(hKhh)��}�(hhhM�hKhKubh�ubh/N�friend�NhN�id�N�point�N�
artificial�K �doclist�]�h��///< Set to true, if the named pipe should be created, otherwise an existing pipe will be used. This flag is ignored for unnamed pipes. Depending on the OS the name might be modified.
�����}�(hKhh)��}�(hhhM�hKhK.ubh�uba�doc���///< Set to true, if the named pipe should be created, otherwise an existing pipe will be used. This flag is ignored for unnamed pipes. Depending on the OS the name might be modified.
��annotations�}��	anonymous��ubahMh=hNhOhP�	namespace�h/NhWNhNhXNhYNhZK h[]�h�E/// Parameters for UrlInterface::SetData(), UrlInterface::GetData().
�����}�(hKhh)��}�(hhhK�hKhKubh�ubahc�E/// Parameters for UrlInterface::SetData(), UrlInterface::GetData().
�he}�hg��preprocessorConditions�]��root�hh N�containsResourceId���registry���usings����minIndentation�K�maxIndentation�K�firstMember��ubh)��}�(hNhh0h]�h h�#ifdef MAXON_TARGET_WINDOWS�����}�(hK
hh)��}�(hhhM|hKhKubh�ububh �	TypeAlias���)��}�(hh�
PIPEHANDLE�����}�(hKhh)��}�(hhhM�hKhKubh�ubhh0h]�hMh�hNhOhP�	typealias�h/NhWNhNhXNhYNhZK h[]�hch	he}�hg��bases�]��void*�hOh	��aubh)��}�(hNhh0h]�h h�#else�����}�(hK
hh)��}�(hhhM�hKhKubh�ububh�)��}�(hh�
PIPEHANDLE�����}�(hKhh)��}�(hhhM�hKhKubh�ubhh0h]�hMh�hNhOhPh�h/NhWNhNhXNhYNhZK h[]�hch	he}�hg�h�]��int�hOh	��aubh)��}�(hNhh0h]�h h�#endif�����}�(hK
hh)��}�(hhhM�hKhKubh�ububh �Class���)��}�(hh�IoPipeInOutputStreamInterface�����}�(hKhh)��}�(hhhM�hK hKubh�ubhh0h]�(h �Function���)��}�(hh�GetReadHandle�����}�(hKhh)��}�(hhhM�hK%hKubh�ubhh�h]�hMh�hNh�public�����}�(hKhh)��}�(hhhM�hK#hKubh�ubhPh�MAXON_METHOD�����}�(hKhh)��}�(hhhM�hK%hKubh�ubh/NhWNhNhXNhYNhZK h[]�hch	he}�hg��static���explicit���deleted���retType��
PIPEHANDLE��const���params�]��
observable�N�result�Nubh�)��}�(hh�GetWriteHandle�����}�(hKhh)��}�(hhhM�hK&hKubh�ubhh�h]�hMh�hNh�hPh�MAXON_METHOD�����}�(hKhh)��}�(hhhM�hK&hKubh�ubh/NhWNhNhXNhYNhZK h[]�hch	he}�hg�hۉh܉h݉hތ
PIPEHANDLE�h��h�]�h�Nh�NubehMh�hNhOhP�class�h/NhWNhNhXh�*"net.maxon.interface.iopipeinoutputstream"�����}�(hKhh)��}�(hhhM[hK"hKIubh�ubhYNhZK h[]�h�,/// Creates a pipe stream for in and output
�����}�(hKhh)��}�(hhhM5hKhKubh�ubahc�,/// Creates a pipe stream for in and output
�he}�hg�h�]��InOutputStreamInterface�hOh	��a�	interface�K�refKind�Khۉ�refClass��IoPipeInOutputStreamRef��baseInterfaces�]�j	  h	��a�derived���isError���implementation���	component���finalComponent���forward���
singleImpl���hasStaticMethods���generic�N�refClassForwardDeclared���missingInterfaces���ambiguousCalls�]��	selfCalls�]��methodNames�}�ubh�)��}�(hj  hh0h]�(h�)��}�(hh�hj#  hh�hMh�hNh�hPh�h/NhWNhNhXNhYNhZK h[h�hch	heh�hg�hۉh܉h݉h�h�h��h�h�h�Nh�Nubh�)��}�(hh�hj#  hh�hMh�hNh�hPh�h/NhWNhNhXNhYNhZK h[h�hch	heh�hg�hۉh܉h݉h�h�h��h�h�h�Nh�NubehMj  hNhOhPh�h/NhWNhNhXNhYNhZKh[h�hc�,/// Creates a pipe stream for in and output
�he}�hg�h�]��3InOutputStreamInterface::ReferenceClassHelper::type�hOh	��aj  Nj  Nhۉj  Nj  Nj  �j  �j  �j  �j  �j  �j  �j  �j  Nj  �j  ��source�h�ubehMh4hNhOhPhhh/NhWNhNhXNhYNhZK h[]�hch	he}�hg�hr]�hthh Nhu�hv�hw��hyK hzK h{�ubh)��}�(hNhhh]�h h�#endif�����}�(hK
hh)��}�(hhhM|hK3hKubh�ububehMhhNhOhPhhh/NhWNhNhXNhYNhZK h[]�hch	he}�hg�hr]�hthh ]�(hh)h0h9hDh|h�h�h�h�h�j#  j4  ehu�hv�hw���hxx1�h0�hxx2�h0�snippets�}�hyK hzK h{�ub.