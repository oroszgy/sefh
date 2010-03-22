

/*
function init()
parameters: 
	dir: a directory path with lex files
	language_code: MS language code (http://wiki.services.openoffice.org/wiki/Languages)
	code_page: input code page, in consol: 852, in win dialog: 1250 (http://en.wikipedia.org/wiki/Code_page)
	session_mode: not used

If return value is negative, it means error.
If return value >=0, it means a session id (which will be used in other function calls).
*/
extern "C" int init(const char* dir, int language_code, int code_page, int session_mode);
extern "C" int initW(const unsigned short* dir, int language_code, int session_mode);

/*
function close
paremeter:
	id: the seession id
it closes this session	
*/
extern "C" int close(int id);

/*
function stem
paremeters:
	id: session id (which was previously initialized)
	input: input string, one word
	out: output buffer
	out_size: size of out
	only_stem: if it is 1, it means the output will contain only stem, without part of speech info

If return value is 0 means success.
If return value is negative, it means error:
	-1: no such session with that id
	-2: unknown word
	-3: out buffer is too small
*/
extern "C" int stem(int id, const char* input, char* out, int out_size, int options);
extern "C" int stemW(int id, 
					 const unsigned short* input, 
					 unsigned short* out, 
					 int out_size, 
					 int options);

/*
function get_synonims
paremeters:
	id: session id (which was previously initialized)
	input: input string, one word
	out: output buffer
	out_size: size of out
	options: 0=>simple list, 1=>xml

If return value is 0 means success.
If return value is negative, it means error:
	-1: no such session with that id
	-2: unknown word
	-3: out buffer is too small
*/
extern "C" int get_synonims(int id, const char* input, char* out, int out_size, int options);
extern "C" int get_synonimsW(int id, 
					 const unsigned short* input, 
					 unsigned short* out, 
					 int out_size, 
					 int options);
#ifdef WIN32
typedef int (*ptf_init)(const char *, int, int, int);
typedef int (*ptf_initW)(const unsigned short *, int, int);
typedef int (*ptf_close)(int);
typedef int (*ptf_stem)(int, const char *, char*, int, int);
typedef int (*ptf_stemW)(int, const unsigned short *, unsigned short*, int, int);
typedef int (*ptf_get_synonims)(int, const char *, char*, int, int);
typedef int (*ptf_get_synonimsW)(int, const unsigned short *, unsigned short*, int, int);
#endif
