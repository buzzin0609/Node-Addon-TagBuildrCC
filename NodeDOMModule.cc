#include <node.h>
#include "TagBuildrCC/TagBuildr.h"
#include "BrowserDoc/BrowserDoc.cc"


namespace NodeDOM {

	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Object;
	using v8::ObjectTemplate;
	using v8::External;
	using v8::String;
	using v8::Array;
	using v8::Function;
	using v8::Value;
	using v8::Exception;

	vector<string> handleChildren(const FunctionCallbackInfo<Value>& args) {
		vector<string> children;
		if (args[1]->IsString() || args[1]->IsNumber()) {
			children.push_back(std::string(*String::Utf8Value(args[1]->ToString())));
		}

		if (args[1]->IsArray()) {
			Local<Array> tbChildren = Local<Array>::Cast(args[1]);
			unsigned int len = tbChildren->Length();

			for (unsigned int i = 0; i < len; i++) {
				children.push_back(std::string(*String::Utf8Value(tbChildren->Get(i))));
			}
		}

		return children;
	}

	void tagBuildrExport(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		if (args.Length() == 0) {
			isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, "[tagbuildr] Error: no arguments supplied")));
			return;
		}

		if (!args[0]->IsString()) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "[tagbuildr] Error: first argument must be a tag string")));
			return;
		}

		TagBuildr tb;
		vector<string> children;

		if (args.Length() > 1) {
			children = handleChildren(args);
		}
		
		std::string tagString(*String::Utf8Value(args[0]->ToString()));
		
		std::string html = tb.render(tagString, children);
		
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, html.c_str()));

	}

	void World(const v8::FunctionCallbackInfo<Value>& info) {
		info.GetReturnValue().Set(String::NewFromUtf8(info.GetIsolate(), "World"));
	}

	void browserDocExport(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		Local<ObjectTemplate> obj = ObjectTemplate::New(isolate);

		obj->Set(String::NewFromUtf8(isolate, "hello"), v8::FunctionTemplate::New(isolate, World));

		args.GetReturnValue().Set(obj);
	}

	

	
	void init(Local<Object> exports) {
		NODE_SET_METHOD(exports, "tagbuildr", tagBuildrExport);
		NODE_SET_METHOD(exports, "BrowserDoc", tagBuildrExport);
	}

	NODE_MODULE(addon, init)

}