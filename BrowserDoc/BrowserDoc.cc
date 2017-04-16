#include "../TagBuildrCC/TagBuildr.h"

namespace NodeDOM {
	class BrowserDoc {
		TagBuildr tb;
		string createSection(string);
		string append(string, string, string);
		

	public:
		BrowserDoc(int x, int y) : x_(x), y_(y) {};
		int x_, y_;
		string document(string, string);
		string addBodyContent(string, string);
	};



	string BrowserDoc::createSection(string sectionName) {
		return tb.render(sectionName);
	}

	string BrowserDoc::append(string doc, string targetTag, string content) {

	}

	string BrowserDoc::document(string title, string content) {
		string head = createSection("head");
		string body = createSection("body");

		return tb.render("html", vector<string> {
			head, body
		});
	}

	string BrowserDoc::addBodyContent(string doc, string content) {
		append(doc, "body", content);
	}


}