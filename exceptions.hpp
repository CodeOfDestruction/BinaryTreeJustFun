#ifndef EXCEPTIONS_HPP_INCLUDED
#define EXCEPTIONS_HPP_INCLUDED

class nullDeref
{
public:
	const  char*  error;
	nullDeref (const  char*  arg)  :  error(arg)  {  }
	const char* what(){ return error; }
};

#endif // EXCEPTIONS_HPP_INCLUDED
