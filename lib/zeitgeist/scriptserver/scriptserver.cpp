#include <boost/any.hpp>
#include <boost/scoped_array.hpp>
#include <sstream>
#include <salt/fileclasses.h>
#include "scriptserver.h"
#include "../corecontext.h"
#include "../core.h"
#include "../logserver/logserver.h"
#include "../fileserver/fileserver.h"

using namespace boost;
using namespace std;
using namespace zeitgeist;

boost::shared_ptr<CoreContext> gContext;

void getParameterList(VALUE args, Class::TParameterList &params)
{
	int argc = RARRAY(args)->len;

	params.resize(argc);

	for (int i = 0; i<argc; ++i)
	{
		VALUE argument = rb_ary_entry(args, i);

		boost::any var;

		// do type conversion
		switch (TYPE(argument))
		{
			case T_STRING:
				{
					char *c = STR2CSTR(argument);
					var = c;
					//printf("string: '%s'\n",boost::any_cast<char*>(var));
				}
				break;
			case T_FIXNUM:
				{
					int i = FIX2INT(argument);
					var = i;
					//printf("int: '%d'\n", boost::any_cast<int>(var));
				}
				break;
			case T_FLOAT:
				{
					float f = (float)NUM2DBL(argument);
					var = f;
					//printf("float: '%f'\n", boost::any_cast<float>(var));
				}
				break;
			case T_TRUE:
				{
					var = true;
					//printf("bool: 'true'\n");
				}
				break;
			case T_FALSE:
				{
					var = false;
					//printf("bool: 'false'\n");
				}
				break;
		}
		params[i] = var;
	}
}

VALUE selectObject(VALUE self, VALUE path)
{
	shared_ptr<Base> base = gContext->Select(STR2CSTR(path));

	if (base.get() != NULL)
	{
		std::stringstream s;
		s << "ZeitgeistObject.new(" << (unsigned long) base.get() <<")";
		return rb_eval_string(s.str().c_str());
	}
	else
		return Qnil;
}

VALUE selectCall(VALUE self, VALUE functionName, VALUE args)
{
	Class::TParameterList in;

	getParameterList(args, in);

	Class::TCmdProc cmd = gContext->GetObject()->GetClass()->GetCmdProc(STR2CSTR(functionName));

	if (cmd != NULL)
	{
		cmd(static_cast<Object*>(gContext->GetObject().get()), in);
	}
	else
	{
		gContext->GetCore()->GetLogServer()->Error() << "ERROR: Unknown function '" << STR2CSTR(functionName) << "'" << std::endl;
	}

	return Qnil;
}

VALUE thisCall(VALUE self, VALUE objPointer, VALUE functionName, VALUE args)
{
	Class::TParameterList in;

	getParameterList(args, in);
	
	Object *obj = (Object*)NUM2INT(objPointer);
	Class::TCmdProc cmd = obj->GetClass()->GetCmdProc(STR2CSTR(functionName));

	if (cmd != NULL)
	{
		cmd(obj, in);
	}
	else
	{
		gContext->GetCore()->GetLogServer()->Error() << "ERROR: Unknown function '" << STR2CSTR(functionName) << "'" << std::endl;
	}

	return Qnil;
}

VALUE importBundle(VALUE self, VALUE path)
{
	gContext->GetCore()->ImportBundle(STR2CSTR(path));
	return Qnil;
}

VALUE newObject(VALUE self, VALUE className, VALUE pathStr)
{
	shared_ptr<Base> base = gContext->New(STR2CSTR(className), STR2CSTR(pathStr));

	if (base.get() != NULL)
	{
		std::stringstream s;
		s << "ZeitgeistObject.new(" << (unsigned long) base.get() <<")";
		return rb_eval_string(s.str().c_str());
	}
	else
		return Qnil;
}

VALUE deleteObject(VALUE self, VALUE name)
{
	gContext->Delete(STR2CSTR(name));

	return Qnil;
}

VALUE getObject(VALUE self, VALUE path)
{
	shared_ptr<Base> base = gContext->Get(STR2CSTR(path));

	if (base.get() != NULL)
	{
		std::stringstream s;
		s << "ZeitgeistObject.new(" << (unsigned long) base.get() <<")";
		return rb_eval_string(s.str().c_str());
	}
	else
		return Qnil;
}

VALUE listObjects(VALUE self)
{
	gContext->ListObjects();

	return Qnil;
}

VALUE pushd(VALUE self)
{
	gContext->Push();

	return Qnil;
}

VALUE popd(VALUE self)
{
	gContext->Pop();

	return Qnil;
}

VALUE dirs(VALUE self)
{
	gContext->Dir();

	return Qnil;
}

ScriptServer::ScriptServer()
{
	ruby_init();

	// register built-in commands
	rb_define_global_function("selectObject", RUBY_METHOD_FUNC(selectObject), 1);
	rb_define_global_function("selectCall", RUBY_METHOD_FUNC(selectCall), 2);
	rb_define_global_function("thisCall", RUBY_METHOD_FUNC(thisCall), 3);
	rb_define_global_function("importBundle",	RUBY_METHOD_FUNC(importBundle), 1);
	rb_define_global_function("new",	RUBY_METHOD_FUNC(newObject), 2);
	rb_define_global_function("delete",	RUBY_METHOD_FUNC(deleteObject), 1);
	rb_define_global_function("get", RUBY_METHOD_FUNC(getObject), 1);
	rb_define_global_function("ls",	RUBY_METHOD_FUNC(listObjects), 0);
	rb_define_global_function("pushd",	RUBY_METHOD_FUNC(pushd), 0);
	rb_define_global_function("popd",	RUBY_METHOD_FUNC(popd), 0);
	rb_define_global_function("dirs",	RUBY_METHOD_FUNC(dirs), 0);
}

ScriptServer::~ScriptServer()
{
}

void ScriptServer::Init()
{
	// now follows the init script, which sets up the zeitgeist scripting
	// environment within ruby.
	Run("script/zeitgeist.rb");
	
	gContext = GetCore()->CreateContext();
}

bool ScriptServer::Run(const std::string &fileName)
{
	/*int error; 
	rb_load_protect(rb_str_new2(fileName.c_str()), 0, &error);

	if (error)
	{
		VALUE mes = rb_inspect(rb_gv_get("$!"));
		GetLog()->Error().Printf("ERROR: %s\n", RSTRING(mes)->ptr);
		return false;
    }
	return true;*/
	salt::RFile *file = GetFile()->Open(fileName.c_str());

	if (file == NULL) return false;

	boost::scoped_array<char> buffer(new char[file->Size()+1]);
	file->Read(buffer.get(), file->Size());
	buffer[file->Size()] = 0;
	delete file;

	return Eval (buffer.get());
}

bool ScriptServer::Eval(const std::string &command)
{
	int error; 
	rb_eval_string_protect(command.c_str(), &error);
	if (error)
	{
		VALUE mes = rb_inspect(rb_gv_get("$!"));
		GetLog()->Error().Printf("ERROR: %s\n", RSTRING(mes)->ptr);
		return false;
    }
	return true;
}

void ScriptServer::CreateVariable(const std::string &varName, int value)
{
	std::stringstream s;
	// create a string with: "createVariable 'varName', value"
	s << "createVariable '" << varName << "', " << value;
	Eval(s.str());
}

void ScriptServer::CreateVariable(const std::string &varName, float value)
{
	std::stringstream s;
	// create a string with: "createVariable 'ns', 'varName', value"
	s << "createVariable '" << varName << "', " << value;
	Eval(s.str());
}

void ScriptServer::CreateVariable(const std::string &varName, const std::string &value)
{
	std::stringstream s;
	// create a string with: "createVariable 'ns', 'varName', 'value'"
	s << "createVariable '" << varName << "', '" << value << "'";
	Eval(s.str());
}

VALUE ScriptServer::GetVariable(const std::string &varName)
{
	stringstream	s(varName);
	string			current;
	vector<string>	tokens;

	// parse varName
	while(!s.eof())
	{
		getline(s, current,'.');
		if (current.size())
			tokens.push_back(current);
	}
	
	if (tokens.size() != 2)
	{
		GetLog()->Error() << "ERROR: Invalid variable '" << varName << "'" << endl;
		return Qnil;
	}
	else
	{
		// get class
		VALUE ns =	rb_const_get(rb_cObject, rb_intern(tokens[0].c_str()));
		if (NIL_P(ns))
		{
			GetLog()->Error() << "ERROR: Invalid namespace '" << tokens[0] << "'" << endl;
			return false;
		}
		ID var=	rb_intern(tokens[1].c_str());
		return rb_funcall(ns, var, 0);
	}
}

bool ScriptServer::GetVariable(const std::string &varName, int &value)
{
	VALUE val = GetVariable(varName);

	if (NIL_P(val))
	{
		return false;
	}
	else
	{
		value = NUM2INT(val);
		return true;
	}
}

bool ScriptServer::GetVariable(const std::string &varName, bool &value)
{
	VALUE val = GetVariable(varName);

	if (NIL_P(val))
	{
		return false;
	}
	else
	{
		if (TYPE(val) == T_TRUE)
		{
			value = true;
			return true;
		}
		if (TYPE(val) == T_FALSE)
		{
			value = false;
			return true;
		}
		return false;
	}
}

bool ScriptServer::GetVariable(const std::string &varName, std::string &value)
{
	VALUE val = GetVariable(varName);

	if (NIL_P(val))
	{
		return false;
	}
	else
	{
		value = STR2CSTR(val);
		return true;
	}
}

boost::shared_ptr<CoreContext> ScriptServer::GetContext() const
{
	return gContext;
}
